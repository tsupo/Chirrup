/*
 * TumblrEditDialog.cpp : Twitter クライアント chirrup
 *      Tumblr(の Quote)投稿内容編集ダイアログ インプリメンテーション ファイル
 *          written by H.Tsujimura  6 Nov 2007
 *
 *      Copyright (c) 2007, 2008, 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/TumblrEditDialog.cpp $
 * 
 * 3     09/05/31 20:42 tsupo
 * 1.142版
 * 
 * 6     09/05/29 19:22 Tsujimura543
 * 同一アカウントで複数 tumbleblog を開設している場合の投稿先
 * tumbleblog を指定しての投稿を可能にした
 * 
 * 2     09/05/27 1:29 tsupo
 * xmlRPC 1.266版対応
 * 
 * 5     09/05/26 18:08 Tsujimura543
 * URL ハードコーディング箇所を減らした
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     09/03/12 19:26 Tsujimura543
 * CTumblrEditDialog ダイアログを二重起動できないようにした
 * 
 * 3     09/03/10 17:48 Tsujimura543
 * CTumblrEditDialog をモーダルダイアログからモードレスダイアログに変更
 * 
 * 2     08/02/12 23:21 Tsujimura543
 * 「コメント」欄を追加
 * 
 * 1     07/11/06 21:46 Tsujimura543
 * 最初の版
 */

#include "chirrup.h"
#include "TumblrEditDialog.h"
extern "C" {
#include "tumblr.h"
}

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/TumblrEditDialog.cpp 3     09/05/31 20:42 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTumblrEditDialog ダイアログ

CTumblrEditDialog   *CTumblrEditDialog::m_instance = NULL;

CTumblrEditDialog   *CTumblrEditDialog::Instance()
{
    if ( m_instance == NULL )
        m_instance = new CTumblrEditDialog;

    return m_instance;
}

CTumblrEditDialog::CTumblrEditDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTumblrEditDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTumblrEditDialog)
	m_quote = _T("");
	m_title = _T("");
	m_url = _T("");
	m_comment = _T("");
	//}}AFX_DATA_INIT

    Create( IDD_TUMBLR_DIALOG );
}

void CTumblrEditDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTumblrEditDialog)
	DDX_Text(pDX, IDC_EDIT_QUOTE, m_quote);
	DDV_MaxChars(pDX, m_quote, 1024);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_title);
	DDV_MaxChars(pDX, m_title, 256);
	DDX_Text(pDX, IDC_EDIT_URL, m_url);
	DDV_MaxChars(pDX, m_url, 512);
	DDX_Text(pDX, IDC_EDIT_COMMENT, m_comment);
	DDV_MaxChars(pDX, m_comment, 512);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTumblrEditDialog, CDialog)
	//{{AFX_MSG_MAP(CTumblrEditDialog)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTumblrEditDialog メッセージ ハンドラ

void CTumblrEditDialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        CEdit   *p;
        if ( m_quote.GetLength() > 0 ) {
            p = (CEdit *)GetDlgItem( IDC_EDIT_QUOTE );
            p->SetWindowText( m_quote );
        }

        if ( m_comment.GetLength() > 0 ) {
            p = (CEdit *)GetDlgItem( IDC_EDIT_COMMENT );
            p->SetWindowText( m_comment );
        }

        if ( m_url.GetLength() > 0 ) {
            p = (CEdit *)GetDlgItem( IDC_EDIT_URL );
            p->SetWindowText( m_url );
        }

        if ( m_title.GetLength() > 0 ) {
            p = (CEdit *)GetDlgItem( IDC_EDIT_TITLE );
            p->SetWindowText( m_title );
        }
    }
}

void CTumblrEditDialog::OnOK()
{
	if ( (m_quote.GetLength() == 0) ||
         (m_url.GetLength()   == 0)    )
        return;

    CString targetURL     = m_url;
    CString targetContent = m_quote;
    CString tagetTitle    = m_title;

    if ( targetURL.GetLength() == 0 )
        targetURL.LoadString( IDS_URL_TUMBLR );
    if ( tagetTitle.GetLength() == 0 )
        tagetTitle = _T( "Tumblr" );

    if ( targetContent.GetLength() > 0 ) {
        ShowWindow( SW_HIDE );

        CWaitCursor cur;// マウスカーソルを砂時計表示
        BOOL        b;
        b = postTumblr( targetURL,  targetContent,
                        tagetTitle, m_comment,
                        m_tumblrID, m_tumblrPassword,
                        m_tumblrGroup );
        if ( b ) {
            // 成功
            MessageBox( "tumblr に投稿しました        ",
                        "tumblr 投稿成功",
                        MB_OK|MB_ICONINFORMATION );
        }
        else
            MessageBox( "いま、ちょっと忙しいの。"
                        "また、あとでやり直してね!    ",
                        "たんぶらん",
                        MB_OK|MB_ICONWARNING );
    }

    DestroyWindow();
 // CDialog::OnOK();
}

void CTumblrEditDialog::OnCancel() 
{
    DestroyWindow();
 // CDialog::OnCancel();
}

void CTumblrEditDialog::PostNcDestroy() 
{
    delete m_instance;
    m_instance = NULL;
 // CDialog::PostNcDestroy();
}
