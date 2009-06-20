/*
 * AboutDlg.cpp : Twitter クライアント chirrup
 *      版数(バージョン番号)表示
 *
 *          written by H.Tsujimura  4 Apr 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/AboutDlg.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     09/03/23 21:06 Tsujimura543
 * libpng と zlib の版数も表示するようにした
 * 
 * 3     08/11/27 15:18 Tsujimura543
 * OpenSSL と iconv の版数を表示するようにした
 * 
 * 2     07/06/13 1:25 Tsujimura543
 * ダイアログに表示するバージョン番号情報をリソースファイルから
 * 拾ってくるようにした
 * 
 * 1     07/04/05 2:06 Tsujimura543
 * 最初の版
 */

#include "chirrup.h"
#include "AboutDlg.h"
#include "png.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/AboutDlg.cpp 1     09/05/14 3:50 tsupo $";
#endif

#if (WINVER >= 0x0500)
//#define IDC_HAND    MAKEINTRESOURCE(32649)
#ifdef IDC_HAND
#undef IDC_HAND
#endif
#endif /* WINVER >= 0x0500 */
#define IDC_HAND    IDC_HAND2


/* libpng 版数取得 */
char    *
getLibpngVersion( char *buf, size_t bufSize )
{
    char        *p = buf;
    char        *q;
    size_t      sz = bufSize;
    static char version[BUFSIZ];

    if ( !buf || (bufSize == 0) ) {
        p  = version;
        sz = BUFSIZ;
    }

    q = png_get_copyright(NULL);
    while ( (*q == ' ') || (*q == '\t') || (*q == '\r') || (*q == '\n') )
        q++;
    strncpy( p, q, sz - 1 );
    p[sz - 1] = NUL;

    return ( p );
}

/* zlib 版数取得 */
char    *
getZlibVersion( char *buf, size_t bufSize )
{
    char        *p = buf;
    size_t      sz = bufSize;
    static char version[BUFSIZ];

    sprintf( version, "zlib: %s", zlibVersion() );

    if ( buf && (bufSize > 0) ) {
        strncpy( p, version, sz - 1 );
        p[sz - 1] = NUL;
    }
    else
        p = version;

    return ( p );
}

/////////////////////////////////////////////////////////////////////////////
// アプリケーションのバージョン情報で使われている CAboutDlg ダイアログ

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT

    m_hCursor = AfxGetApp()->LoadCursor( IDC_HAND );
}

CAboutDlg::~CAboutDlg()
{
    m_cFont.DeleteObject();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_MAIL_ADDR, OnMailAddr)
	ON_BN_CLICKED(IDC_WEB_URL, OnWebUrl)
	ON_WM_SETCURSOR()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CAboutDlg::OnMailAddr() 
{
	CString cmd;
	cmd.LoadString( IDS_MAIL_ADDR );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CAboutDlg::OnWebUrl() 
{
	CString cmd;
	cmd.LoadString( IDS_WEB_URL );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

BOOL CAboutDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if ( nHitTest == HTCLIENT ) {
        // Web の URLかメールアドレスにマウスポインタが来たら、
        // 指カーソルを表示する
		DWORD   dwPos = GetMessagePos();
		WORD    wX    = LOWORD( dwPos );
		WORD    wY    = HIWORD( dwPos );
		CPoint  poCursor( wX, wY );
		CRect   rcClient;

        CStatic *s = (CStatic *)GetDlgItem( IDC_MAIL_ADDR );
        s->GetWindowRect( &rcClient );
        if ( (wX >= rcClient.left) && (wX <= rcClient.right)  &&
             (wY >= rcClient.top)  && (wY <= rcClient.bottom)    ) {
			SetCursor( m_hCursor );
            return TRUE;
        }

        s = (CStatic *)GetDlgItem( IDC_WEB_URL );
        s->GetWindowRect( &rcClient );
        if ( (wX >= rcClient.left) && (wX <= rcClient.right)  &&
             (wY >= rcClient.top)  && (wY <= rcClient.bottom)    ) {
			SetCursor( m_hCursor );
            return TRUE;
        }
	}

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

void CAboutDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        // Web の URLとメールアドレスを下線付きで表示する
        LOGFONT tLogFont;
        CFont   *cWndFont;

        cWndFont = GetFont(); 
        cWndFont->GetLogFont( &tLogFont );
        tLogFont.lfUnderline = 1;
        m_cFont.CreateFontIndirect( &tLogFont );

        CStatic *s = (CStatic *)GetDlgItem( IDC_MAIL_ADDR );
        s->SetFont( &m_cFont, TRUE );

        s = (CStatic *)GetDlgItem( IDC_WEB_URL );
        s->SetFont( &m_cFont, TRUE );

    	CString version;
    	version.LoadString( IDS_VERSION );
        CString title = _T("chirrup Version ");
        title += version;

        s = (CStatic *)GetDlgItem( IDC_VERSION );
        s->SetWindowText( title );

        // OpenSSL 版数表示
        char    buf[BUFSIZ];
        size_t  sz = BUFSIZ;

        s = (CStatic *)GetDlgItem( IDC_OPENSSL );
        s->SetWindowText( getOpenSSLversion( buf, sz ) );

        // iconv 版数表示
        s = (CStatic *)GetDlgItem( IDC_ICONV );
        s->SetWindowText( getIconvVersion( buf, sz ) );

        // libpng 版数表示
        s = (CStatic *)GetDlgItem( IDC_LIBPNG );
        s->SetWindowText( getLibpngVersion( buf, sz ) );

        // zlib 版数表示
        s = (CStatic *)GetDlgItem( IDC_ZLIB );
        s->SetWindowText( getZlibVersion( buf, sz ) );
    }
}
