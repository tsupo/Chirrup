/*
 * SettingTimelog.cpp : Twitter クライアント chirrup
 *      設定ダイアログ(Timelog) インプリメンテーション ファイル
 *          written by H.Tsujimura  20 Jun 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/SettingTimelog.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     08/07/16 4:13 Tsujimura543
 * 「同時投稿対象」の設定を「設定」ダイアログでも設定できるようにした
 * 
 * 1     07/06/20 11:20 Tsujimura543
 * 新規作成
 */

#include "chirrup.h"
#include "chirrupDlg.h"
#include "SettingTimelog.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/SettingTimelog.cpp 1     09/05/14 3:50 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingTimelog ダイアログ

CSettingTimelog::CSettingTimelog(CWnd* pParent /*=NULL*/)
	: CTabDialog(CSettingTimelog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingTimelog)
	//}}AFX_DATA_INIT
}

// 「設定ダイアログ」での「適用」ボタン押下時処理
void CSettingTimelog::Accept()
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

        m_chirrup->SetTimelog( m_username, m_password,
                               m_checkMultiPost,
                               sFriendsTimeline,
                               sPublicTimeline,
                               sUserTimeline );
    }
}

// 現在の「設定」を取得
void CSettingTimelog::LoadSetting()
{
    if ( !m_initialized ) {
        if ( m_chirrup ) {
            TIMELINE_INFO sFriendsTimeline;
            TIMELINE_INFO sPublicTimeline;
            TIMELINE_INFO sUserTimeline;

            m_chirrup->GetTimelog( m_username, m_password,
                                   m_checkMultiPost,
                                   sFriendsTimeline,
                                   sPublicTimeline,
                                   sUserTimeline );

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
    }
}

void CSettingTimelog::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingTimelog)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSettingTimelog, CTabDialog)
	//{{AFX_MSG_MAP(CSettingTimelog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
