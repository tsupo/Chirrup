/*
 * SettingTwitter.cpp : Twitter クライアント chirrup
 *      設定ダイアログ(Twitter) インプリメンテーション ファイル
 *          written by H.Tsujimura  7 Jun 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/SettingTwitter.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 11    09/04/16 17:39 Tsujimura543
 * 認証方法選択ダイアログから戻ってきたときに、ユーザ名とパスワードを
 * 反映させ忘れていたのを反映させるように修正 (OAuth対応時のバグ)
 * 
 * 10    09/03/31 21:27 Tsujimura543
 * Twitter の OAuth 対応準備 その5
 * 
 * 9     09/03/30 22:37 Tsujimura543
 * Twitter の OAuth 対応準備 その2
 * 
 * 8     08/07/16 4:13 Tsujimura543
 * 「同時投稿対象」の設定を「設定」ダイアログでも設定できるようにした
 * 
 * 7     07/07/05 0:41 Tsujimura543
 * (friends_timeline の閲覧をしない設定の場合)Replies のファイル名の設定
 * ができない不具合に対処
 * 
 * 6     07/06/13 19:18 Tsujimura543
 * Twitter の Replies の閲覧、ログ出力に対応
 * 
 * 5     07/06/13 0:12 Tsujimura543
 * (1) TIMELINE_INFO 関連 fix
 * (2) 初期設定ファイル読み書きを新しいログファイル管理仕様に対応させた
 * 
 * 4     07/06/12 17:51 Tsujimura543
 * Twitter と Jaiku で共通化できる部分は共通化し、共通化した部分を
 * CTabDialog に移管
 * 
 * 3     07/06/11 18:39 Tsujimura543
 * Twitter の user_timeline の閲覧をサポート
 * 
 * 2     07/06/07 15:47 Tsujimura543
 * CTabDialog を導入、コードを整理してみた
 * 
 * 1     07/06/07 1:43 Tsujimura543
 * 新規作成 (タブ選択形式の設定ダイアログを新たに用意した)
 */

#include "chirrup.h"
#include "chirrupDlg.h"
#include "SettingTwitter.h"
#include "TwitterAuthSelectDialog.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/SettingTwitter.cpp 1     09/05/14 3:50 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingTwitter ダイアログ

CSettingTwitter::CSettingTwitter(CWnd* pParent /*=NULL*/)
	: CTabDialog(CSettingTwitter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingTwitter)
	m_logFile_replies = _T("");
	m_checkReplies = FALSE;
	m_checkLogFileReplies = FALSE;
	//}}AFX_DATA_INIT

    m_useOAuth = false;
    m_useBASIC = false;
    m_oauthToken       = _T("");
    m_oauthTokenSecret = _T("");
}

void CSettingTwitter::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingTwitter)
	DDX_Text(pDX, IDC_EDIT_LOGFILENAME4, m_logFile_replies);
	DDV_MaxChars(pDX, m_logFile_replies, 1024);
	DDX_Check(pDX, IDC_CHECK_REPLIES, m_checkReplies);
	DDX_Check(pDX, IDC_CHECK_REPLIES2, m_checkLogFileReplies);
	//}}AFX_DATA_MAP
}

// 「設定ダイアログ」での「適用」ボタン押下時処理
void CSettingTwitter::Accept()
{
    if ( m_initialized && m_chirrup ) {
        TIMELINE_INFO sFriendsTimeline;
        TIMELINE_INFO sPublicTimeline;
        TIMELINE_INFO sUserTimeline;
        TIMELINE_INFO sReplies;

        setTimelineInfo( sFriendsTimeline,
                         m_logFile_friendsTimeline,
                         m_checkFriendsTimeline,
                         m_checkLogFileFriendsTimeline );

        setTimelineInfo( sPublicTimeline,
                         m_logFile_publicTimeline,
                         m_checkPublicTimeline,
                         m_checkLogFilePublicTimeline );

        setTimelineInfo( sUserTimeline,
                         m_logFile_userTimeline,
                         m_checkUserTimeline,
                         m_checkLogFileUserTimeline );

        setTimelineInfo( sReplies,
                         m_logFile_replies,
                         m_checkReplies,
                         m_checkLogFileReplies );

        m_chirrup->SetTwitter( m_username, m_password,
                               m_oauthToken, m_oauthTokenSecret,
                               m_useOAuth, m_useBASIC,
                               m_checkMultiPost,
                               sFriendsTimeline,
                               sPublicTimeline,
                               sUserTimeline,
                               sReplies );
    }
}

// 現在の「設定」を取得
void CSettingTwitter::LoadSetting()
{
    if ( !m_initialized ) {
        if ( m_chirrup ) {
            TIMELINE_INFO sFriendsTimeline;
            TIMELINE_INFO sPublicTimeline;
            TIMELINE_INFO sUserTimeline;
            TIMELINE_INFO sReplies;

            BOOL    useOAuth = m_useOAuth ? TRUE : FALSE;
            BOOL    useBASIC = m_useBASIC ? TRUE : FALSE;
            m_chirrup->GetTwitter( m_username, m_password,
                                   m_oauthToken, m_oauthTokenSecret,
                                   useOAuth, useBASIC,
                                   m_checkMultiPost,
                                   sFriendsTimeline,
                                   sPublicTimeline,
                                   sUserTimeline,
                                   sReplies );
            m_useOAuth = useOAuth ? true : false;
            m_useBASIC = useBASIC ? true : false;

            getTimelineInfo( sFriendsTimeline,
                             m_logFile_friendsTimeline,
                             m_checkFriendsTimeline,
                             m_checkLogFileFriendsTimeline );

            getTimelineInfo( sPublicTimeline,
                             m_logFile_publicTimeline,
                             m_checkPublicTimeline,
                             m_checkLogFilePublicTimeline );

            getTimelineInfo( sUserTimeline,
                             m_logFile_userTimeline,
                             m_checkUserTimeline,
                             m_checkLogFileUserTimeline );

            getTimelineInfo( sReplies,
                             m_logFile_replies,
                             m_checkReplies,
                             m_checkLogFileReplies );
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// CSettingTwitter 追加メソッド

void CSettingTwitter::SetCheckReplies()
{
    CButton *bp;
    CEdit   *ep = (CEdit *)GetDlgItem( IDC_EDIT_LOGFILENAME4 );

    if ( m_checkReplies ) {
        ep->SetReadOnly( FALSE );

        bp = (CButton *)GetDlgItem( IDC_CHECK_REPLIES2 );
        bp->EnableWindow( TRUE );

        bp = (CButton *)GetDlgItem( IDC_BUTTON_FILESPEC4 );
        bp->EnableWindow( TRUE );
    }
    else {
        ep->SetReadOnly( TRUE );

        bp = (CButton *)GetDlgItem( IDC_CHECK_REPLIES2 );
        bp->EnableWindow( FALSE );

        bp = (CButton *)GetDlgItem( IDC_BUTTON_FILESPEC4 );
        bp->EnableWindow( FALSE );
    }
}

void CSettingTwitter::ShowCurrentStatus()
{
    CStatic *sp = (CStatic *)GetDlgItem(IDC_CURRENT_AUTH);

    if ( !m_useOAuth && !m_useBASIC )
        sp->SetWindowText( _T("[現在の設定: 未設定]") );
    else if ( m_useOAuth )
        sp->SetWindowText( _T("[現在の設定: OAuth認証を使う]") );
    else
        sp->SetWindowText( _T("[現在の設定: BASIC認証を使う]") );
}

BEGIN_MESSAGE_MAP(CSettingTwitter, CTabDialog)
	//{{AFX_MSG_MAP(CSettingTwitter)
	ON_BN_CLICKED(IDC_BUTTON_FILESPEC4, OnButtonFilespec4)
	ON_BN_CLICKED(IDC_CHECK_REPLIES, OnCheckReplies)
	ON_BN_CLICKED(IDC_CHECK_REPLIES2, OnCheckReplies2)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_SET_AUTH, OnButtonSetAuth)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSettingTwitter::OnShowWindow(BOOL bShow, UINT nStatus) 
{
    CTabDialog::OnShowWindow(bShow, nStatus);

    if ( bShow ) {
        ShowCurrentStatus();

        CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_LOGFILENAME4);
        p->SetWindowText( m_logFile_replies );

        CButton *bp = (CButton *)GetDlgItem( IDC_CHECK_REPLIES );
        bp->SetCheck( m_checkReplies );

        bp = (CButton *)GetDlgItem( IDC_CHECK_REPLIES2 );
        bp->SetCheck( m_checkLogFileReplies );

        SetCheckReplies();
    }
    else {
        CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_LOGFILENAME4);
        p->GetWindowText( m_logFile_replies );
    }	
}

void CSettingTwitter::OnButtonFilespec4() 
{
    InputFileName( m_logFile_replies, IDC_EDIT_LOGFILENAME4 );
}

void CSettingTwitter::OnCheckReplies() 
{
    CButton *bp = (CButton *)GetDlgItem( IDC_CHECK_REPLIES );
    m_checkReplies = bp->GetCheck();

    SetCheckReplies();
}

void CSettingTwitter::OnCheckReplies2() 
{
    CButton *bp = (CButton *)GetDlgItem( IDC_CHECK_REPLIES2 );
    m_checkLogFileReplies = bp->GetCheck();
}

void CSettingTwitter::OnButtonSetAuth() 
{
    TwitterAuthSelectDialog dlg;

    dlg.m_username = m_username;
    dlg.m_password = m_password;
    dlg.m_oauthToken       = m_oauthToken;
    dlg.m_oauthTokenSecret = m_oauthTokenSecret;

    dlg.m_useOAuth = m_useOAuth;
    dlg.m_useBASIC = m_useBASIC;

    int result = dlg.DoModal();
    if ( result == IDOK ) {
        m_username = dlg.m_username;
        m_password = dlg.m_password;

        m_oauthToken       = dlg.m_oauthToken;
        m_oauthTokenSecret = dlg.m_oauthTokenSecret;

        m_useOAuth = dlg.m_useOAuth;
        m_useBASIC = dlg.m_useBASIC;

        CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_USERNAME);
        p->SetWindowText( m_username );

        p = (CEdit *)GetDlgItem(IDC_EDIT_PASSWORD);
        p->SetWindowText( m_password );

        ShowCurrentStatus();
    }
}
