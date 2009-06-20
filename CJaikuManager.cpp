/*
 * CJaikuManager.cpp : Twitter クライアント chirrup
 *       Jaiku 関連管理情報取扱い機能 インプリメンテーション ファイル
 *          written by H.Tsujimura  20 Jun 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/CJaikuManager.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 10    09/04/16 16:11 Tsujimura543
 * 新規インストール時に OAuth 認証設定したあと、スクリーン名の取得に失敗
 * する等、OAuth 対応時に作りこんでしまったバグを修正
 * 
 * 9     09/04/15 1:17 Tsujimura543
 * Jaiuku の OAuth 対応準備
 * 
 * 8     08/12/04 18:19 Tsujimura543
 * コード整理、安定化作業を実施
 * 
 * 7     07/08/28 16:58 Tsujimura543
 * EvalKeys() を修正(スクリーン名と同時発言対象フラグの復元を追加)
 * 
 * 6     07/08/28 16:55 Tsujimura543
 * WriteKeys() を修正(スクリーン名と同時発言対象フラグの保存を追加)
 * 
 * 5     07/06/26 16:30 Tsujimura543
 * デストラクタに後始末処理を追加
 * 
 * 4     07/06/20 5:17 Tsujimura543
 * CheckKeys() に引数を追加
 * 
 * 3     07/06/20 3:16 Tsujimura543
 * 設定ファイルの読み書き処理を chirrupDlg から CManager と
 * CJaikuManager に移した
 * 
 * 2     07/06/20 2:19 Tsujimura543
 * デストラクタを修正
 * 
 * 1     07/06/20 1:53 Tsujimura543
 * 新規作成 (Jaiku 専用 CManager)
 */

#include "chirrup.h"
#include "chirrupDlg.h"
#include "parameter.h"
#include "jaiku.h"
#include "CJaikuManager.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/CJaikuManager.cpp 1     09/05/14 3:50 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CJaikuManager::CJaikuManager()
    : CManager( CTwitterTimeline::SVC_JAIKU )
{
}

CJaikuManager::~CJaikuManager()
{
    CJaiku  *p = (CJaiku *)m_service;
    int     i;

    if ( m_friendsTimeline.m_stat ) {
        for ( i = m_friendsTimeline.m_numOfStats; i > 0; i-- ) {
            p->DeleteReserved( &(m_friendsTimeline.m_stat[i - 1]) );
            p->DeleteReserved2( &(m_friendsTimeline.m_stat[i - 1]) );
        }
        delete [] m_friendsTimeline.m_stat;
        m_friendsTimeline.m_stat = NULL;
    }
    if ( m_userTimeline.m_stat ) {
        for ( i = m_userTimeline.m_numOfStats; i > 0; i-- ) {
            p->DeleteReserved( &(m_userTimeline.m_stat[i - 1]) );
            p->DeleteReserved2( &(m_userTimeline.m_stat[i - 1]) );
        }
        delete [] m_userTimeline.m_stat;
        m_userTimeline.m_stat = NULL;
    }
    if ( m_publicTimeline.m_stat ) {
        for ( i = m_publicTimeline.m_numOfStats; i > 0; i-- ) {
            p->DeleteReserved( &(m_publicTimeline.m_stat[i - 1]) );
            p->DeleteReserved2( &(m_publicTimeline.m_stat[i - 1]) );
        }
        delete [] m_publicTimeline.m_stat;
        m_publicTimeline.m_stat = NULL;
    }
}

void CJaikuManager::SetConfig(
                            CString username,
                            CString password,
                            CString oauthToken,
                            CString oauthTokenSecret,
                            BOOL useOAuth,
                            BOOL useBASIC,
                            BOOL checkMultiPost,
                            TIMELINE_INFO sFriendsTimeline,
                            TIMELINE_INFO sPublicTimeline,
                            TIMELINE_INFO sUserTimeline
                        )
{
    CManager::SetConfig( username, password,
                         checkMultiPost,
                         sFriendsTimeline,
                         sPublicTimeline,
                         sUserTimeline );
    m_oauthToken       = oauthToken;
    m_oauthTokenSecret = oauthTokenSecret;
    m_useOAuth         = useOAuth ? true : false;
    m_useBASIC         = useBASIC ? true : false;
}


void CJaikuManager::GetConfig(
                            CString &username,
                            CString &password,
                            CString &oauthToken,
                            CString &oauthTokenSecret,
                            BOOL &useOAuth,
                            BOOL &useBASIC,
                            BOOL &checkMultiPost,
                            TIMELINE_INFO &sFriendsTimeline,
                            TIMELINE_INFO &sPublicTimeline,
                            TIMELINE_INFO &sUserTimeline
                        )
{
    CManager::GetConfig( username, password,
                         checkMultiPost,
                         sFriendsTimeline,
                         sPublicTimeline,
                         sUserTimeline );
    oauthToken       = m_oauthToken;
    oauthTokenSecret = m_oauthTokenSecret;
    useOAuth         = m_useOAuth ? TRUE : FALSE;
    useBASIC         = m_useBASIC ? TRUE : FALSE;
}

void CJaikuManager::GetScreenName()
{
    if ( (m_username.GetLength() > 0)                 &&
         (m_useOAuth || (m_password.GetLength() > 0))    ) {
        SetUpUserInfo();
        m_screenName = m_service->GetScreenName();
    }
}

bool CJaikuManager::ExecutePost( 
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
    ret = ((CJaiku *)m_service)->PostPresence( monologue, pdlg );

    return ( ret );
}


void CJaikuManager::WriteKeys(
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
        sprintf( target, "personalKeyFor%s", (const char *)m_serviceSymbol );
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

    CManager::WriteKeys( fp, &m_sFriendsTimeline, "Friends" );
    CManager::WriteKeys( fp, &m_sPublicTimeline,  "Public"  );
    CManager::WriteKeys( fp, &m_sUserTimeline,    "User"    );
}

bool CJaikuManager::CheckKeys(
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

    sprintf( target, "personalKeyFor%sEncrypted",
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

    return ( ret );
}

bool CJaikuManager::EvalKeys(
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
        sprintf( target, "personalKeyFor%sEncrypted",
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
        sprintf( target, "screennameFor%s", (const char *)m_serviceSymbol );
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
        ret = CManager::EvalKeys( &m_sFriendsTimeline, "Friends", p );
    if ( ret == false )
        ret = CManager::EvalKeys( &m_sPublicTimeline,  "Public",  p );
    if ( ret == false )
        ret = CManager::EvalKeys( &m_sUserTimeline,    "User",    p );

    return ( ret );
}
