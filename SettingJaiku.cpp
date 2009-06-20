/*
 * SettingJaiku.cpp : Twitter クライアント chirrup
 *      設定ダイアログ(Jaiku) インプリメンテーション ファイル
 *          written by H.Tsujimura  7 Jun 2007
 *
 *      Copyright (c) 2007, 2008, 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/SettingJaiku.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 9     09/04/16 17:39 Tsujimura543
 * 認証方法選択ダイアログから戻ってきたときに、ユーザ名とパスワードを
 * 反映させ忘れていたのを反映させるように修正 (OAuth対応時のバグ)
 * 
 * 8     09/04/16 1:31 Tsujimura543
 * ShowCurrentStatus() で表示する文言を修正
 * 
 * 7     09/04/15 1:17 Tsujimura543
 * Jaiuku の OAuth 対応準備
 * 
 * 6     08/07/16 4:13 Tsujimura543
 * 「同時投稿対象」の設定を「設定」ダイアログでも設定できるようにした
 * 
 * 5     07/08/31 19:22 Tsujimura543
 * 「personal_key の取得方法」に関するヒントを表示するようにした
 * 
 * 4     07/06/13 0:12 Tsujimura543
 * (1) TIMELINE_INFO 関連 fix
 * (2) 初期設定ファイル読み書きを新しいログファイル管理仕様に対応させた
 * 
 * 3     07/06/12 17:51 Tsujimura543
 * Twitter と Jaiku で共通化できる部分は共通化し、共通化した部分を
 * CTabDialog に移管
 * 
 * 2     07/06/07 15:47 Tsujimura543
 * CTabDialog を導入、コードを整理してみた
 * 
 * 1     07/06/07 1:43 Tsujimura543
 * 新規作成 (タブ選択形式の設定ダイアログを新たに用意した)
 */

#include "chirrup.h"
#include "chirrupDlg.h"
#include "SettingJaiku.h"
#include "JaikuAuthSelectDialog.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/SettingJaiku.cpp 1     09/05/14 3:50 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingJaiku ダイアログ

CSettingJaiku::CSettingJaiku(CWnd* pParent /*=NULL*/)
	: CTabDialog(CSettingJaiku::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingJaiku)
	//}}AFX_DATA_INIT

    m_useOAuth = false;
    m_useBASIC = false;
    m_oauthToken       = _T("");
    m_oauthTokenSecret = _T("");
}

// 「設定ダイアログ」での「適用」ボタン押下時処理
void CSettingJaiku::Accept()
{
    if ( m_initialized && m_chirrup ) {
        TIMELINE_INFO sFriendsTimeline;
        TIMELINE_INFO sPublicTimeline;
        TIMELINE_INFO sUserTimeline;

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

        m_chirrup->SetJaiku( m_username, m_password,
                             m_oauthToken, m_oauthTokenSecret,
                             m_useOAuth, m_useBASIC,
                             m_checkMultiPost,
                             sFriendsTimeline,
                             sPublicTimeline,
                             sUserTimeline );
    }
}

// 現在の「設定」を取得
void CSettingJaiku::LoadSetting()
{
    if ( !m_initialized ) {
        if ( m_chirrup ) {
            TIMELINE_INFO sFriendsTimeline;
            TIMELINE_INFO sPublicTimeline;
            TIMELINE_INFO sUserTimeline;

            BOOL    useOAuth = m_useOAuth ? TRUE : FALSE;
            BOOL    useBASIC = m_useBASIC ? TRUE : FALSE;
            m_chirrup->GetJaiku( m_username, m_password,
                                 m_oauthToken, m_oauthTokenSecret,
                                 useOAuth, useBASIC,
                                 m_checkMultiPost,
                                 sFriendsTimeline,
                                 sPublicTimeline,
                                 sUserTimeline );
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
        }

        ShowCurrentStatus();
    }
}

void CSettingJaiku::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingJaiku)
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_password);
	DDV_MaxChars(pDX, m_password, 64);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSettingJaiku 追加メソッド

void CSettingJaiku::ShowCurrentStatus()
{
    CStatic *sp = (CStatic *)GetDlgItem(IDC_CURRENT_AUTH);

    if ( !m_useOAuth && !m_useBASIC )
        sp->SetWindowText( _T("[現在の設定: 未設定]") );
    else if ( m_useOAuth )
        sp->SetWindowText( _T("[現在の設定: OAuth認証を使う]") );
    else
        sp->SetWindowText( _T("[現在の設定: 従来の認証を使う]") );
}

BEGIN_MESSAGE_MAP(CSettingJaiku, CTabDialog)
	//{{AFX_MSG_MAP(CSettingJaiku)
	ON_BN_CLICKED(IDC_BUTTON_SET_AUTH, OnButtonSetAuth)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingJaiku メッセージ ハンドラ

void CSettingJaiku::OnButtonSetAuth() 
{
    JaikuAuthSelectDialog dlg;

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
