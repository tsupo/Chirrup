/*
 * TwitterAuthSelectDialog.cpp : Twitter クライアント chirrup
 *      Twitter認証方法設定ダイアログ インプリメンテーション ファイル
 *          written by H.Tsujimura  31 Mar 2009
 *
 *      Copyright (c) 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/TwitterAuthSelectDialog.cpp $
 * 
 * 3     09/06/18 1:33 tsupo
 * 2.01版
 * 
 * 6     09/06/16 0:51 Tsujimura543
 * アクセストークン取得時に返ってくるスクリーン名を利用するようにした
 * 
 * 2     09/05/15 2:34 tsupo
 * 「1.140版→1.141版」での変更点を取り込む
 * 
 * 5     09/05/14 14:52 Tsujimura543
 * ユーザ名未設定状態で本ダイアログを起動したとき、ユーザ名を入力後、
 * ラジオボタンをクリックすると、ユーザ名の欄がクリアされてしまう不具合
 * に対処
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     09/04/01 22:10 Tsujimura543
 * リファクタリング実施
 * 
 * 3     09/04/01 3:16 Tsujimura543
 * Twitter の OAuth 対応、完了
 * 
 * 2     09/03/31 21:26 Tsujimura543
 * 動作確認完了
 * 
 * 1     09/03/31 20:12 Tsujimura543
 * 最初の版
 */

#include "chirrup.h"
#include "TwitterAuthSelectDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TwitterAuthSelectDialog ダイアログ

TwitterAuthSelectDialog::TwitterAuthSelectDialog(CWnd* pParent /*=NULL*/)
	: CDialog(TwitterAuthSelectDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(TwitterAuthSelectDialog)
	m_username = _T("");
	m_password = _T("");
	//}}AFX_DATA_INIT

    m_useOAuth         = false;
    m_useBASIC         = false;
    m_oauthToken       = _T("");
    m_oauthTokenSecret = _T("");
}

void TwitterAuthSelectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TwitterAuthSelectDialog)
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_username);
	DDV_MaxChars(pDX, m_username, 64);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_password);
	DDV_MaxChars(pDX, m_password, 32);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(TwitterAuthSelectDialog, CDialog)
	//{{AFX_MSG_MAP(TwitterAuthSelectDialog)
	ON_BN_CLICKED(IDC_BUTTON_GET_TOKEN, OnButtonGetToken)
	ON_BN_CLICKED(IDC_RADIO_BASIC, OnRadioBasic)
	ON_BN_CLICKED(IDC_RADIO_OAUTH, OnRadioOauth)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TwitterAuthSelectDialog 追加メソッド

void TwitterAuthSelectDialog::ShowCurrentStatus( bool rescan /* = FALSE */ )
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
    p->EnableWindow( m_useBASIC );

    p = (CEdit *)GetDlgItem(IDC_EDIT_PASSWORD);
    if ( rescan )
        p->GetWindowText( m_password );
    p->SetWindowText( m_password );
    p->EnableWindow( m_useBASIC );
}

/////////////////////////////////////////////////////////////////////////////
// TwitterAuthSelectDialog メッセージ ハンドラ

void TwitterAuthSelectDialog::OnButtonGetToken() 
{
    CWaitCursor cur;    // マウスカーソルを砂時計表示
    CTwitter    t;
    CChirrupApp *ap = (CChirrupApp *)AfxGetApp();
    CString     screenName = _T("");

    t.GetAccessToken( ap->m_tcKey, ap->m_tcSecret,
                      m_oauthToken, m_oauthTokenSecret,
                      screenName );

    if ( screenName.GetLength() > 0 )
        if ( m_username.GetLength() == 0 )
            m_username = screenName;

    ShowCurrentStatus();
}

void TwitterAuthSelectDialog::OnRadioBasic() 
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

void TwitterAuthSelectDialog::OnRadioOauth() 
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

void TwitterAuthSelectDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

    if ( bShow )
        ShowCurrentStatus();
}
