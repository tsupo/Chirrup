/*
 * CManager.cpp : Twitter クライアント chirrup
 *       各サービス毎の各種管理情報取扱い機能 インプリメンテーション ファイル
 *          written by H.Tsujimura  19 Jun 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/CManager.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 28    09/05/12 17:16 Tsujimura543
 * 「スレッド起動時刻」を各タイムライン取得処理を呼び出すタイミングで
 * 上書きするように変更 (サービスごと → タイムラインごと に変更)
 * 
 * 27    09/04/16 16:11 Tsujimura543
 * 新規インストール時に OAuth 認証設定したあと、スクリーン名の取得に失敗
 * する等、OAuth 対応時に作りこんでしまったバグを修正
 * 
 * 26    09/04/16 1:33 Tsujimura543
 * Jaiku の OAuth にも対応した
 * 
 * 25    09/03/31 23:29 Tsujimura543
 * Twitter の OAuth 対応準備 その7
 * 
 * 24    09/03/31 21:39 Tsujimura543
 * Twitter の OAuth 対応準備 その6
 * 
 * 23    09/03/31 21:27 Tsujimura543
 * Twitter の OAuth 対応準備 その5
 * 
 * 22    09/03/30 22:19 Tsujimura543
 * Twitter の OAuth 対応準備
 * 
 * 21    08/12/04 18:19 Tsujimura543
 * コード整理、安定化作業を実施
 * 
 * 20    08/08/22 18:42 Tsujimura543
 * 「はてなハイク」対応
 * 
 * 19    08/07/31 18:34 Tsujimura543
 * 「チャンネル」に対応
 * 
 * 18    08/07/16 4:13 Tsujimura543
 * 「同時投稿対象」の設定を「設定」ダイアログでも設定できるようにした
 * 
 * 17    07/08/30 18:07 Tsujimura543
 * コメントを整理
 * 
 * 16    07/08/30 18:04 Tsujimura543
 * 「自分のスクリーン名をキャッシュする」ようにしたのと「利用していない
 * サービスのメモリ確保をやめる」ようにした影響で、Jaiku の m_apiKey の
 * 初期化が行なわれないまま、(少なくとも最初の1回は)処理が行なわれること
 * が判明。最初のtimeline取得のタイミングで明示的に初期化するようにした
 * 
 * 15    07/08/28 1:56 Tsujimura543
 * 同時投稿対象にするサービスを選択できるようにした
 * 
 * 14    07/08/25 0:45 Tsujimura543
 * 「ついすた」に対応 (表示)
 * 
 * 13    07/08/17 23:01 Tsujimura543
 * SetConfig() を修正。ユーザ名もパスワードも変更していない場合は
 * GetScreenName() を呼ばないようにした (呼ぶ必要がない)
 * 
 * 12    07/08/09 14:23 Tsujimura543
 * 自分のスクリーン名をキャッシュするようにした
 * 
 * 11    07/07/05 2:15 Tsujimura543
 * friends_timeline のログファイル名が未設定の場合、他の timeline のログ
 * ファイル名の設定が保存されない不具合に対処
 * 
 * 10    07/07/05 0:38 Tsujimura543
 * ExecuteUpdate() の2引数版の方を改良
 * 
 * 9     07/06/27 18:13 Tsujimura543
 * haru.fm に対応
 * 
 * 8     07/06/25 19:13 Tsujimura543
 * ~CManager() を修正、各サービス毎のデストラクタを明示的に
 * 呼び出すようにした
 * 
 * 7     07/06/22 22:49 Tsujimura543
 * コンストラクタを修正、serviceType の値を代入する処理が抜けていた
 * 
 * 6     07/06/20 15:46 Tsujimura543
 * InitTimelineInfo() を廃止
 * 
 * 5     07/06/20 14:07 Tsujimura543
 * Timelog 対応版
 * 
 * 4     07/06/20 5:16 Tsujimura543
 * CheckKeys() に引数を追加
 * 
 * 3     07/06/20 3:16 Tsujimura543
 * 設定ファイルの読み書き処理を chirrupDlg から CManager と
 * CJaikuManager に移した
 * 
 * 2     07/06/20 1:55 Tsujimura543
 * Jaiku 専用部分を CJaikuManager へ分離
 * 
 * 1     07/06/19 21:16 Tsujimura543
 * 今まで CChirrupDlg 内でやっていた各サービスを管理、制御する処理を
 * 抽出し CManager として独立させた
 */

#include "chirrup.h"
#include "chirrupDlg.h"
#include "parameter.h"
#include "twitter.h"
#include "jaiku.h"
#include "wassr.h"
#include "mogo2.h"
#include "timelog.h"
#include "haruFm.h"
#include "hatenaHaiku.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/CManager.cpp 1     09/05/14 3:50 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CManager::CManager()
{
    m_serviceName      = _T("");
    m_screenName       = _T("");
    m_username         = _T("");
    m_password         = _T("");
    m_oauthToken       = _T("");
    m_oauthTokenSecret = _T("");
    m_service          = NULL;
    m_useOAuth         = false;
    m_useBASIC         = false;
    m_simultaneousPost = false;
}

CManager::CManager( CTwitterTimeline::SVC_TYPE serviceType )
{
    m_serviceName      = _T("");
    m_screenName       = _T("");
    m_username         = _T("");
    m_password         = _T("");
    m_oauthToken       = _T("");
    m_oauthTokenSecret = _T("");
    m_useOAuth         = false;
    m_useBASIC         = false;
    m_service          = NULL;

    switch ( serviceType ) {
    case CTwitterTimeline::SVC_TWITTER:
        m_serviceName   = _T("Twitter");
        m_serviceSymbol = _T("Twitter");
        m_service       = new CTwitter;
        break;

    case CTwitterTimeline::SVC_JAIKU:
        m_serviceName   = _T("Jaiku");
        m_serviceSymbol = _T("Jaiku");
        m_service       = new CJaiku;
        break;

    case CTwitterTimeline::SVC_WASSR:
        m_serviceName   = _T("Wassr");
        m_serviceSymbol = _T("Wassr");
        m_service       = new CWassr;
        break;

    case CTwitterTimeline::SVC_MOGO2:
        m_serviceName   = _T("もごもご");
        m_serviceSymbol = _T("Mogo2");
        m_service       = new CMogo2;
        break;

    case CTwitterTimeline::SVC_TIMELOG:
        m_serviceName   = _T("Timelog");
        m_serviceSymbol = _T("Timelog");
        m_service       = new CTimelog;
        break;

    case CTwitterTimeline::SVC_HARUFM:
        m_serviceName   = _T("Haru.fm");
        m_serviceSymbol = _T("HaruFm");
        m_service       = new CHaruFm;
        break;

    case CTwitterTimeline::SVC_HATENAHAIKU:
        m_serviceName   = _T("はてなハイク");
        m_serviceSymbol = _T("HatenaHaiku");
        m_service       = new CHatenaHaiku;
        break;
    }

    m_simultaneousPost              = false;
    m_friendsTimeline.m_serviceType = serviceType;
    m_userTimeline.m_serviceType    = serviceType;
    m_publicTimeline.m_serviceType  = serviceType;
}


CManager::~CManager()
{
    m_friendsTimeline.FinishLogging();
    m_publicTimeline.FinishLogging();
    m_userTimeline.FinishLogging();

    if ( m_service ) {
        if ( !m_serviceSymbol.Compare("Twitter") ) {
            CTwitter    *p = (CTwitter *)m_service;
            delete p;
            m_service = NULL;
        }
        else if ( !m_serviceSymbol.Compare("Jaiku") ) {
            CJaiku  *p = (CJaiku *)m_service;
            delete p;
            m_service = NULL;
        }
        else if ( !m_serviceSymbol.Compare("Wassr") ) {
            CWassr  *p = (CWassr *)m_service;
            delete p;
            m_service = NULL;
        }
        else if ( !m_serviceSymbol.Compare("Mogo2") ) {
            CMogo2  *p = (CMogo2 *)m_service;
            delete p;
            m_service = NULL;
        }
        else if ( !m_serviceSymbol.Compare("Timelog") ) {
            CTimelog    *p = (CTimelog *)m_service;
            delete p;
            m_service = NULL;
        }
        else if ( !m_serviceSymbol.Compare("HaruFm") ) {
            CHaruFm *p = (CHaruFm *)m_service;
            delete p;
            m_service = NULL;
        }
        else if ( !m_serviceSymbol.Compare("HatenaHaiku") ) {
            CHatenaHaiku    *p = (CHatenaHaiku *)m_service;
            delete p;
            m_service = NULL;
        }
        else {
            delete m_service;
            m_service = NULL;
        }
    }
}

void CManager::SetConfig(
                  CString username,
                  CString password,
                  BOOL checkMultiPost,
                  TIMELINE_INFO sFriendsTimeline,
                  TIMELINE_INFO sPublicTimeline,
                  TIMELINE_INFO sUserTimeline
              )
{
    bool    needToReset = false;
    if ( m_username.Compare( username ) ||
         m_password.Compare( password )    )
        needToReset = true;
    m_service->m_username = m_username = username;
    m_service->m_password = m_password = password;

    if ( needToReset ) {
        // screen名 (再)設定
        GetScreenName();
    }

    m_simultaneousPost = checkMultiPost ? true : false;
    m_sFriendsTimeline = sFriendsTimeline;
    m_sPublicTimeline  = sPublicTimeline;
    m_sUserTimeline    = sUserTimeline;
}

void CManager::GetConfig(
                  CString &username,
                  CString &password,
                  BOOL &checkMultiPost,
                  TIMELINE_INFO &sFriendsTimeline,
                  TIMELINE_INFO &sPublicTimeline,
                  TIMELINE_INFO &sUserTimeline
              )
{
    username = m_username;
    password = m_password;
    checkMultiPost   = m_simultaneousPost ? TRUE : FALSE;
    sFriendsTimeline = m_sFriendsTimeline;
    sPublicTimeline  = m_sPublicTimeline;
    sUserTimeline    = m_sUserTimeline;
}


void CManager::ExecuteUpdate(
                    CStatic          *sp,
                    bool             useTwitStar,
                    CChirrupDlg      *cdlg,
                    ProceedingDialog *pdlg
                )
{
    if ( m_sFriendsTimeline.checkTimeline ||
         m_sFriendsTimeline.checkChannel  ||
         m_sPublicTimeline.checkTimeline  ||
         m_sUserTimeline.checkTimeline       ) {
        CString msg = m_serviceName;
        msg += _T(": 情報取得中……");
        sp->SetWindowText( msg );

        SetUpUserInfo();
        m_service->m_useTwitStar = useTwitStar;

        CTwitterTimeline    *tp1 = NULL;
        CTwitterTimeline    *tp2 = NULL;
        CTwitterTimeline    *tp3 = NULL;

        if ( m_useOAuth                          ||
             ( (m_username.GetLength() > 0) &&
               (m_password.GetLength() > 0)    )    ) {
            m_service->m_useOAuth = m_useOAuth;
            if ( m_useOAuth ) {
                m_service->m_oauthToken       = m_oauthToken;
                m_service->m_oauthTokenSecret = m_oauthTokenSecret;
            }

            tp1 = GetPublicTimeline();
            tp2 = GetFriendsTimeline();
            tp3 = GetUserTimeline();
        }

        if ( tp1 && m_sPublicTimeline.checkTimeline ) {
            cdlg->m_startTime_updateThread = CTime::GetCurrentTime();
            tp1->m_messages = m_service->GetPublicTimeline( tp1, pdlg );
        }

        if ( tp2 &&
             (m_sFriendsTimeline.checkTimeline ||
              m_sFriendsTimeline.checkChannel    ) ) {
            cdlg->m_startTime_updateThread = CTime::GetCurrentTime();
            if ( (tp1 && m_sPublicTimeline.checkTimeline) )
                Sleep( 1000 );
            tp2->m_messages = m_service->GetFriendsTimeline( tp2, pdlg );
        }

        if ( tp3 && m_sUserTimeline.checkTimeline ) {
            cdlg->m_startTime_updateThread = CTime::GetCurrentTime();
            if ( (tp1 && m_sPublicTimeline.checkTimeline) ||
                 (tp2 &&
                  (m_sFriendsTimeline.checkTimeline ||
                   m_sFriendsTimeline.checkChannel    )     ) )
                Sleep( 1000 );
            tp3->m_messages = m_service->GetUserTimeline( tp3, pdlg );
        }
    }
}

bool CManager::ExecutePost( 
                    CString          monologue,
                    CStatic          *sp,
                    ProceedingDialog *pdlg
                )
{
    bool    ret = false;
    CString msg = m_serviceName;
    msg += _T(": 発言を投稿中……");
    sp->SetWindowText( msg );

    SetUpUserInfo();
    ret = m_service->PostUpdate( monologue, pdlg );

    return ( ret );
}

void CManager::GetScreenName()
{
    if ( m_useOAuth                          ||
         ( (m_username.GetLength() > 0) &&
           (m_password.GetLength() > 0)    )    ) {
        SetUpUserInfo();
        m_screenName = m_service->GetScreenName();
    }
}

void CManager::SetUpUserInfo()
{
    m_service->m_useOAuth           = m_useOAuth;
    m_service->m_username           = m_username;
    if ( !m_serviceSymbol.Compare("Jaiku") )
        ((CJaiku *)m_service)->m_apiKey = m_password;
    else
        m_service->m_password           = m_password;
    m_service->m_oauthToken         = m_oauthToken;
    m_service->m_oauthTokenSecret   = m_oauthTokenSecret;
}

void CManager::SetLogFileSpec()
{
    m_friendsTimeline.SetLogFileSpec( m_sFriendsTimeline );
    m_publicTimeline.SetLogFileSpec( m_sPublicTimeline );
    m_userTimeline.SetLogFileSpec( m_sUserTimeline );
}


void CManager::WriteKeys(
                    FILE          *fp,
                    char          *key,
                    unsigned char **secret,
                    bool          &done )
{
    char    target[BUFSIZ];

    if ( m_username.GetLength() > 0 ) {
        sprintf( target, "usernameFor%s", (const char *)m_serviceSymbol );
        writeKey( fp, target, m_username );
    }

    if ( m_password.GetLength() > 0 ) {
        sprintf( target, "passwordFor%s", (const char *)m_serviceSymbol );
        writeKey( fp, target, m_password, key, secret, done );
    }

    if ( m_useOAuth || m_useBASIC ) {
        sprintf( target, "useOAuthFor%s", (const char *)m_serviceSymbol );
        writeKey( fp, target, m_useOAuth );

        sprintf( target, "useBasicFor%s", (const char *)m_serviceSymbol );
        writeKey( fp, target, m_useBASIC );
    }

    if ( m_oauthToken.GetLength() > 0 ) {
        sprintf( target, "oauthTokenFor%s", (const char *)m_serviceSymbol );
        writeKey( fp, target, m_oauthToken, key, secret, done );
    }
    if ( m_oauthTokenSecret.GetLength() > 0 ) {
        sprintf( target, "oauthTokenSecretFor%s",
                 (const char *)m_serviceSymbol );
        writeKey( fp, target, m_oauthTokenSecret, key, secret, done );
    }

    if ( m_screenName.GetLength() > 0 ) {
        sprintf( target, "screennameFor%s", (const char *)m_serviceSymbol );
        writeKey( fp, target, m_screenName );
    }

    sprintf( target, "simultaneousPostAs%s", (const char *)m_serviceSymbol );
    writeKey( fp, target, m_simultaneousPost );

    WriteKeys( fp, &m_sFriendsTimeline, "Friends" );
    WriteKeys( fp, &m_sPublicTimeline,  "Public"  );
    WriteKeys( fp, &m_sUserTimeline,    "User"    );
}

void CManager::WriteKeys(
                    FILE                *fp,
                    const TIMELINE_INFO *t,
                    const char          *timelineType )
{
    char    target[BUFSIZ];

    sprintf( target, "check%sTimelineFor%s",
             timelineType, (const char *)m_serviceSymbol );
    writeKey( fp, target, t->checkTimeline );

    sprintf( target, "check%sChannelFor%s",
             timelineType, (const char *)m_serviceSymbol );
    writeKey( fp, target, t->checkChannel );

    if ( t->logFileName.GetLength() > 0 ) {
        sprintf( target, "logFileNameOf%sTimelineFor%s",
                 timelineType, (const char *)m_serviceSymbol );
        writeKey( fp, target, t->logFileName );
    }

    sprintf( target, "checkLogFileOf%sTimelineFor%s",
             timelineType, (const char *)m_serviceSymbol );
    writeKey( fp, target, t->checkLogFile );
}

bool CManager::CheckKeys(
                        const char          *p,
                        const unsigned char *rsaString,
                        char                *encrypted,
                        bool                &ret )
{
    bool    cont = false;
    char    target[BUFSIZ];
    bool    checkPassword         = true;
    bool    checkOauthToken       = true;
    bool    checkOauthTokenSecret = true;

    sprintf( target, "passwordFor%sEncrypted",
             (const char *)m_serviceSymbol );
    if ( evalKey( p, target, encrypted ) ) {
        checkKey( m_password,
                  (unsigned char *)encrypted,
                  rsaString,
                  checkPassword );
        cont = true;
    }

    if ( cont == false ) {
        sprintf( target, "oauthTokenFor%sEncrypted",
                 (const char *)m_serviceSymbol );
        if ( evalKey( p, target, encrypted ) ) {
            checkKey( m_oauthToken,
                      (unsigned char *)encrypted,
                      rsaString,
                      checkOauthToken );
            cont = true;
        }
    }

    if ( cont == false ) {
        sprintf( target, "oauthTokenSecretFor%sEncrypted",
                 (const char *)m_serviceSymbol );
        if ( evalKey( p, target, encrypted ) ) {
            checkKey( m_oauthTokenSecret,
                      (unsigned char *)encrypted,
                      rsaString,
                      checkOauthTokenSecret );
            cont = true;
        }
    }

    ret &= (checkPassword & checkOauthToken & checkOauthTokenSecret);

    return ( cont );
}

bool CManager::EvalKeys(
                    const char          *p,
                    const unsigned char *rsaString,
                    char                *encrypted )
{
    bool    ret = false;
    char    target[BUFSIZ];

    sprintf( target, "usernameFor%s", (const char *)m_serviceSymbol );
    if ( evalKey( p, target, m_username ) )
        ret = true;
    if ( ret == false ) {
        sprintf( target, "passwordFor%sEncrypted",
                 (const char *)m_serviceSymbol );
        if ( evalKey( p, target, encrypted ) ) {
            extractKey( m_password,
                        (unsigned char *)encrypted,
                        (unsigned char *)rsaString );
            ret = true;
        }
    }

    if ( ret == false ) {
        sprintf( target, "useOAuthFor%s",
                 (const char *)m_serviceSymbol );
        if ( evalKey( p, target, m_useOAuth ) )
            ret = true;
    }
    if ( ret == false ) {
        sprintf( target, "useBasicFor%s",
                 (const char *)m_serviceSymbol );
        if ( evalKey( p, target, m_useBASIC ) )
            ret = true;
    }

    if ( ret == false ) {
        sprintf( target, "oauthTokenFor%sEncrypted",
                 (const char *)m_serviceSymbol );
        if ( evalKey( p, target, encrypted ) ) {
            extractKey( m_oauthToken,
                        (unsigned char *)encrypted,
                        (unsigned char *)rsaString );
            ret = true;
        }
    }
    if ( ret == false ) {
        sprintf( target, "oauthTokenSecretFor%sEncrypted",
                 (const char *)m_serviceSymbol );
        if ( evalKey( p, target, encrypted ) ) {
            extractKey( m_oauthTokenSecret,
                        (unsigned char *)encrypted,
                        (unsigned char *)rsaString );
            ret = true;
        }
    }

    if ( ret == false ) {
        sprintf( target, "screennameFor%s",
                 (const char *)m_serviceSymbol );
        if ( evalKey( p, target, m_screenName ) )
            ret = true;
    }
    if ( ret == false ) {
        sprintf( target, "simultaneousPostAs%s",
                 (const char *)m_serviceSymbol );
        if ( evalKey( p, target, m_simultaneousPost ) )
            ret = true;
    }
    if ( ret == false )
        ret = EvalKeys( &m_sFriendsTimeline, "Friends", p );
    if ( ret == false )
        ret = EvalKeys( &m_sPublicTimeline,  "Public",  p );
    if ( ret == false )
        ret = EvalKeys( &m_sUserTimeline,    "User",    p );

    return ( ret );
}

bool CManager::EvalKeys(
                    TIMELINE_INFO *t,
                    const char    *timelineType,
                    const char    *p )
{
    bool    ret = false;
    char    target[BUFSIZ];

    if ( ret == false ) {
        sprintf( target, "check%sTimelineFor%s",
                 timelineType, (const char *)m_serviceSymbol );
        if ( evalKey( p, target, t->checkTimeline ) )
            ret = true;
    }

    if ( ret == false ) {
        sprintf( target, "check%sChannelFor%s",
                 timelineType, (const char *)m_serviceSymbol );
        if ( evalKey( p, target, t->checkChannel ) )
            ret = true;
    }

    if ( ret == false ) {
        sprintf( target, "logFileNameOf%sTimelineFor%s",
                 timelineType, (const char *)m_serviceSymbol );
        if ( evalKey( p, target, t->logFileName ) )
            ret = true;
    }

    if ( ret == false ) {
        sprintf( target, "checkLogFileOf%sTimelineFor%s",
                 timelineType, (const char *)m_serviceSymbol );
        if ( evalKey( p, target, t->checkLogFile ) )
            ret = true;
    }

    return ( ret );
}

