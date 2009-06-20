/*
 * JaikuAuthSelectDialog.cpp : Jaiku クライアント chirrup
 *      Jaiku認証方法設定ダイアログ インプリメンテーション ファイル
 *          written by H.Tsujimura  14 Apr 2009
 *
 *      Copyright (c) 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/JaikuAuthSelectDialog.cpp $
 * 
 * 2     09/05/15 2:34 tsupo
 * 「1.140版→1.141版」での変更点を取り込む
 * 
 * 3     09/05/14 14:52 Tsujimura543
 * ユーザ名未設定状態で本ダイアログを起動したとき、ユーザ名を入力後、
 * ラジオボタンをクリックすると、ユーザ名の欄がクリアされてしまう不具合
 * に対処
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     09/04/16 3:40 Tsujimura543
 * Jaiku の「発言ID」、「コメントID」の仕様変更に伴う修正を実施
 * 
 * 1     09/04/14 23:36 Tsujimura543
 * 最初の版
 */

#include "chirrup.h"
#include "Jaiku.h"
#include "JaikuAuthSelectDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if (WINVER >= 0x0500)
//#define IDC_HAND    MAKEINTRESOURCE(32649)
#ifdef IDC_HAND
#undef IDC_HAND
#endif
#endif /* WINVER >= 0x0500 */
#define IDC_HAND    IDC_HAND2

/////////////////////////////////////////////////////////////////////////////
// JaikuAuthSelectDialog ダイアログ

JaikuAuthSelectDialog::JaikuAuthSelectDialog(CWnd* pParent /*=NULL*/)
	: CDialog(JaikuAuthSelectDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(JaikuAuthSelectDialog)
	m_username = _T("");
	m_password = _T("");
	//}}AFX_DATA_INIT

    m_useOAuth         = false;
    m_useBASIC         = false;
    m_oauthToken       = _T("");
    m_oauthTokenSecret = _T("");

    m_hCursor = AfxGetApp()->LoadCursor( IDC_HAND );
}

JaikuAuthSelectDialog::~JaikuAuthSelectDialog()
{
    m_cFont.DeleteObject();
}

void JaikuAuthSelectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(JaikuAuthSelectDialog)
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_username);
	DDV_MaxChars(pDX, m_username, 32);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_password);
	DDV_MaxChars(pDX, m_password, 64);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(JaikuAuthSelectDialog, CDialog)
	//{{AFX_MSG_MAP(JaikuAuthSelectDialog)
	ON_BN_CLICKED(IDC_BUTTON_GET_TOKEN, OnButtonGetToken)
	ON_BN_CLICKED(IDC_RADIO_BASIC, OnRadioBasic)
	ON_BN_CLICKED(IDC_RADIO_OAUTH, OnRadioOauth)
	ON_BN_CLICKED(IDC_URL_JAIKU_APIKEY, OnUrlJaikuApiKey)
	ON_WM_SHOWWINDOW()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// JaikuAuthSelectDialog 追加メソッド

void JaikuAuthSelectDialog::ShowCurrentStatus( bool rescan /* = FALSE */ )
{
    CButton *bp = (CButton *)GetDlgItem( IDC_BUTTON_GET_TOKEN );
    bp->EnableWindow( m_useOAuth );

    bp = (CButton *)GetDlgItem( IDC_RADIO_OAUTH );
    bp->SetCheck( m_useOAuth ? 1 : 0 );

    bp = (CButton *)GetDlgItem( IDC_RADIO_BASIC );
    bp->SetCheck( m_useBASIC ? 1 : 0 );

    CString status;
    CStatic *sp = (CStatic *)GetDlgItem( IDC_TOKEN_STATUS );
    if ( (m_oauthToken.GetLength()       > 0) &&
         (m_oauthTokenSecret.GetLength() > 0)    )
	    status.LoadString( IDS_ACCESSTOKEN_ACQUIRED );
    else
	    status.LoadString( IDS_ACCESSTOKEN_UNTAKEN );
    sp->SetWindowText( status );

    CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_USERNAME);
    if ( rescan )
        p->GetWindowText( m_username );
    p->SetWindowText( m_username );
    p->EnableWindow( TRUE );

    p = (CEdit *)GetDlgItem(IDC_EDIT_PASSWORD);
    if ( rescan )
        p->GetWindowText( m_password );
    p->SetWindowText( m_password );
    p->EnableWindow( m_useBASIC );
}

/////////////////////////////////////////////////////////////////////////////
// JaikuAuthSelectDialog メッセージ ハンドラ

void JaikuAuthSelectDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

    if ( bShow ) {
        ShowCurrentStatus();

	    CString str;
	    str.LoadString( IDS_URL_JAIKU_APIKEY );

        LOGFONT tLogFont;
        CFont   *cWndFont;

        cWndFont = GetFont(); 
        cWndFont->GetLogFont( &tLogFont );
        tLogFont.lfUnderline = 1;
        m_cFont.CreateFontIndirect( &tLogFont );

        CStatic *s = (CStatic *)GetDlgItem( IDC_URL_JAIKU_APIKEY );
        s->SetWindowText( str );
        s->SetFont( &m_cFont, TRUE );
    }
}

void JaikuAuthSelectDialog::OnButtonGetToken() 
{
    CWaitCursor cur;    // マウスカーソルを砂時計表示
    CJaiku      j;
    CChirrupApp *ap = (CChirrupApp *)AfxGetApp();

    j.GetAccessToken( ap->m_jcKey, ap->m_jcSecret,
                      m_oauthToken, m_oauthTokenSecret );

    ShowCurrentStatus();
}

void JaikuAuthSelectDialog::OnRadioBasic() 
{
    if ( m_useBASIC ) {
        m_useBASIC = false;
        m_useOAuth = true;
    }
    else {
        m_useBASIC = true;
        m_useOAuth = false;
    }

    ShowCurrentStatus( true );
}

void JaikuAuthSelectDialog::OnRadioOauth() 
{
    if ( m_useOAuth ) {
        m_useBASIC = true;
        m_useOAuth = false;
    }
    else {
        m_useBASIC = false;
        m_useOAuth = true;
    }

    ShowCurrentStatus( true );
}

void JaikuAuthSelectDialog::OnUrlJaikuApiKey() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_JAIKU_APIKEY );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

BOOL JaikuAuthSelectDialog::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if ( nHitTest == HTCLIENT ) {
        // Web の URLかメールアドレスにマウスポインタが来たら、
        // 指カーソルを表示する
		DWORD   dwPos = GetMessagePos();
		WORD    wX    = LOWORD( dwPos );
		WORD    wY    = HIWORD( dwPos );
		CPoint  poCursor( wX, wY );
		CRect   rcClient;

        CStatic *s = (CStatic *)GetDlgItem( IDC_URL_JAIKU_APIKEY );
        s->GetWindowRect( &rcClient );
        if ( (wX >= rcClient.left) && (wX <= rcClient.right)  &&
             (wY >= rcClient.top)  && (wY <= rcClient.bottom)    ) {
			SetCursor( m_hCursor );
            return TRUE;
        }
	}

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}
