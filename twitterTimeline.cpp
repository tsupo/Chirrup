/*
 * twitterTimeline.cpp : Twitter クライアント chirrup
 *      timeline 関連各種処理群
 *          written by H.Tsujimura  4 Apr 2007 / 25 May 2007
 *
 *      Copyright (c) 2007, 2008, 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/twitterTimeline.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 32    09/04/16 19:22 Tsujimura543
 * LoadUserIcon() を修正。ユーザアイコンの表示タイミング、縮小条件・縮小率
 * を変更した
 * 
 * 31    09/03/31 23:29 Tsujimura543
 * Twitter の OAuth 対応準備 その7
 * 
 * 30    08/09/02 18:36 Tsujimura543
 * はてなハイクのアイコン表示がおかしくなる件、対処してみた
 * 
 * 29    08/08/22 20:21 Tsujimura543
 * 「はてなハイク」関連、動作確認終了
 * 
 * 28    08/08/22 18:42 Tsujimura543
 * 「はてなハイク」対応
 * 
 * 27    08/07/31 18:19 Tsujimura543
 * 「チャンネル」に対応
 * 
 * 26    08/07/14 13:54 Tsujimura543
 * アイコンを「表示領域サイズに合わせて画像を縮小表示する」ようにした
 * 
 * 25    08/04/22 22:14 Tsujimura543
 * タイムラインの閲覧はするがログは記録しないという設定の場合でも
 * ログが記録されてしまうことがある不具合に対処
 * 
 * 24    08/02/07 22:36 Tsujimura543
 * copyright 表示を修正 (2008 を追加)
 * 
 * 23    08/01/07 14:55 Tsujimura543
 * 不要になった処理を削除
 * 
 * 22    08/01/07 14:43 Tsujimura543
 * デフォルトアイコンの表示処理を LoadDefaultUserIcon() として
 * 分離。ユーザアイコン取得失敗時もデフォルトアイコンを表示する
 * ようにしてみた
 * 
 * 21    07/11/26 19:42 Tsujimura543
 * LoadTimeline() を修正 (処理打ち切りタイミングを早くした)
 * 
 * 20    07/11/26 19:34 Tsujimura543
 * LoadTimeline() 内で TCP/IP のタイムアウトが発生した場合は、すぐに処理を
 * 打ち切ってリターンするようにした
 * 
 * 19    07/09/13 16:00 Tsujimura543
 * ソースコードを整理
 * 
 * 18    07/09/13 15:55 Tsujimura543
 * InitTimeline() を修正。m_numOfUsers の値が 0 のときでも処理する
 * ようにした
 * 
 * 17    07/07/05 22:29 Tsujimura543
 * LoadUserIcon() 内での画像取得時の http 通信のタイムアウト時間を
 * 15秒にしてみた
 * 
 * 16    07/07/05 16:08 Tsujimura543
 * GetServiceName() を追加
 * 
 * 15    07/07/04 20:06 Tsujimura543
 * m_logFileExtention のデフォルト値を修正 (".txt" → "txt")
 * 
 * 14    07/07/03 13:39 Tsujimura543
 * LoadUserIcon() を Haru.fm に対応させた
 * 
 * 13    07/06/27 18:13 Tsujimura543
 * haru.fm に対応
 * 
 * 12    07/06/21 23:18 Tsujimura543
 * LoadUserIcon() で、Timelog に関しても、ユーザアイコンの URL が不明な
 * ときの対応処理を追加
 * 
 * 11    07/06/21 22:40 Tsujimura543
 * LoadUserIcon() を変更、ユーザアイコンの URL が不明な場合、Twitter
 * の ShowUser API を使ってアイコンの URL を取得するようにした
 * 
 * 10    07/06/21 21:42 Tsujimura543
 * LoadUserIcon() を修正。Timelog のダイレクトメッセージ送信ダイアログ
 * 表示時に期待するアイコンが表示できるようにした
 * 
 * 9     07/06/20 17:36 Tsujimura543
 * Timelog 対応
 * 
 * 8     07/06/18 19:07 Tsujimura543
 * LoadUserIcon() を変更、もごもごのユーザアイコンキャッシュ時の
 * ファイルの頭に M を付けるようにした
 * 
 * 7     07/06/18 18:52 Tsujimura543
 * LoadUserIcon() を導入し、ユーザアイコンの表示処理を一本化した
 * 
 * 6     07/06/13 0:12 Tsujimura543
 * (1) TIMELINE_INFO 関連 fix
 * (2) 初期設定ファイル読み書きを新しいログファイル管理仕様に対応させた
 * 
 * 5     07/06/12 19:49 Tsujimura543
 * ログファイル名の末尾に日付を埋め込むことができるようにした
 * 
 * 4     07/06/06 19:05 Tsujimura543
 * ログをファイルに書き出す機能を実装
 * 
 * 3     07/05/29 3:56 Tsujimura543
 * Jaiku (の public_timeline の閲覧) に対応
 * 
 * 2     07/05/25 23:03 Tsujimura543
 * リファクタリング
 * 
 * 1     07/05/25 20:16 Tsujimura543
 * 新規作成 (chirrupDlg.cpp から分離、独立)
 */

#include "chirrup.h"
#include "chirrupDlg.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/twitterTimeline.cpp 1     09/05/14 3:50 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CTwitterTimeline::CTwitterTimeline()
{
    m_checkTimeline    = false;
    m_checkChannel     = false;
    m_checkLogFile     = false;
    m_logFileBaseName  = _T("timeline");
    m_logFileExtention = _T("txt");

	m_messages         = _T("");
    m_numOfUsers       = 0;
    m_users            = NULL;

    m_stat             = new TWITTER_STATUS[MAX_NUMOFSTATUS];
    m_numOfStats       = 0;

    m_logging          = false;
    m_logFileName[0]   = NUL;
    m_logFp            = NULL;

    m_serviceType      = SVC_TWITTER;
}

CTwitterTimeline::~CTwitterTimeline()
{
    if ( m_logFp )
        FinishLogging();

    if ( m_users ) {
        int i;
        for ( i = 0; i < MAX_NUMOFFRIENDS; i++ ) {
            if ( m_users[i].bitmap )
                DeleteObject( m_users[i].bitmap );
        }
        delete [] m_users;
    }
    if ( m_stat )
        delete [] m_stat;
}


bool
CTwitterTimeline::InitTimeline()
{
    bool    cnt = true;
    int     i;

    if ( m_numOfUsers == 0 ) {
        if ( !m_users ) {
            m_users = new TWITTER_USER[MAX_NUMOFFRIENDS];
            for ( i = 0; i < MAX_NUMOFFRIENDS; i++ ) {
                m_users[i].id[0]   = NUL;
                m_users[i].name[0] = NUL;
                m_users[i].bitmap  = NULL;
            }
        }
    }
    else {
        for ( i = 0; i < MAX_NUMOFFRIENDS; i++ ) {
            m_users[i].id[0]   = NUL;
            m_users[i].name[0] = NUL;
            if ( m_users[i].bitmap )
                DeleteObject( m_users[i].bitmap );
            m_users[i].bitmap  = NULL;
        }
        m_numOfUsers = 0;
    }

    return ( cnt );
}

void
CTwitterTimeline::MoveTimeline()
{
    int i, j;

    for ( i = 0; i < m_numOfStats; i++ ) {
        for ( j = 0; j < MAX_NUMOFFRIENDS; j++ ) {
            if ( m_users[j].id[0] ) {
                if ( !strcmp( m_users[j].id, m_stat[i].user.id ) )
                    break;
            }
            else {
                m_users[j]   = m_stat[i].user;
                m_numOfUsers = j;
                break;
            }
        }
    }
}

void
CTwitterTimeline::LoadTimeline(
                        CChirrupDlg *cp,
                        CString     cacheDir
                    )
{
    CStatic *sp;
    int     i;

    for ( i = 0; i < MAX_NUMOFFRIENDS; i++ ) {
        if ( isNecessaryToCheckProxyInfo() )
            break;
        sp = (CStatic *)cp->GetDlgItem( IDC_FRIEND001 + i );
        LoadUserIcon( sp, &(m_users[i]), m_serviceType, cacheDir );
    }
}


void CTwitterTimeline::SetLogFileSpec( TIMELINE_INFO s )
{
    m_checkTimeline = s.checkTimeline;
    m_checkChannel  = s.checkChannel;
    m_checkLogFile  = s.checkLogFile;

    if ( s.logFileName.GetLength() > 0 ) {
        char    filename[MAX_PATH];
        strcpy( filename, s.logFileName );

        char    *p = strrchr( filename, '.' );
        if ( p ) {
            m_logFileExtention = p + 1;

            char    temp[MAX_PATH];
            strncpy( temp, filename, p - filename );
            temp[p - filename] = NUL;
            m_logFileBaseName = temp;
        }
        else
            m_logFileBaseName = filename;
    }

    if ( (m_checkTimeline || m_checkChannel) &&
         (m_logFileBaseName.GetLength() > 0)    ) {
        StartLogging();
        if ( m_checkLogFile )
            WriteLog( "\r\n*** logging start ***\r\n" );
    }
}


void CTwitterTimeline::StartLogging()
{
    if ( m_logFp )
        FinishLogging();

    if ( m_checkLogFile ) {
        time_t      t   = time( NULL );
        struct tm   *tm = localtime( &t );

        sprintf( m_logFileName,
                 "%s_%04d%02d%02d.%s",
                 (const char *)m_logFileBaseName,
                 tm->tm_year + 1900,
                 tm->tm_mon  + 1,
                 tm->tm_mday,
                 (const char *)m_logFileExtention );
    }
    else
        sprintf( m_logFileName, "%s_%s.%s",
                 (const char *)GetServiceName(),
                 (const char *)m_logFileBaseName,
                 (const char *)m_logFileExtention );

    if ( m_checkLogFile ) {
        m_logFp = fopen( m_logFileName, "ab+" );
        if ( m_logFp )
            m_logging = true;
    }
}

void CTwitterTimeline::FinishLogging()
{
    if ( m_logFp ) {
        fclose( m_logFp );
        m_logFp = NULL;
    }

    m_logging = false;
}

void CTwitterTimeline::WriteLog( const char *str )
{
    if ( m_logging && m_logFp ) {
        fputs( str, m_logFp );

        // 途中でアプリケーション(あるいは OS)がクラッシュしてログファイル
        // が消えてしまう、という事態を避けるために毎回ファイルを閉じて、
        // 開き直す
        FinishLogging();
        StartLogging();
    }
}

CString
CTwitterTimeline::GetServiceName()
{
    CString s = _T("");

    switch ( m_serviceType ) {
    case SVC_TWITTER:
        s = _T("Twitter");
        break;
    case SVC_JAIKU:
        s = _T("Jaiku");
        break;
    case SVC_WASSR:
        s = _T("Wassr");
        break;
    case SVC_MOGO2:
        s = _T("Mogo2");
        break;
    case SVC_TIMELOG:
        s = _T("Timelog");
        break;
    case SVC_HARUFM:
        s = _T("HaruFm");
        break;
    case SVC_HATENAHAIKU:
        s = _T("HatenaHaiku");
        break;
    }

    return ( s );
}


/* utility */
bool
LoadDefaultUserIcon( TWITTER_USER               *u,
                     CTwitterTimeline::SVC_TYPE &type,
                     const char                 *cacheDir )
{
    CImage  img;
    bool    allocated = false;
    char    filename[MAX_PATH];
    char    *defaultImageURL = TWITTER_DEFAULT_IMAGE;

    switch ( type ) {
    case CTwitterTimeline::SVC_JAIKU:
        defaultImageURL = JAIKU_DEFAULT_IMAGE;
        break;
    case CTwitterTimeline::SVC_WASSR:
        defaultImageURL = WASSR_DEFAULT_IMAGE;
        break;
    case CTwitterTimeline::SVC_MOGO2:
        defaultImageURL = MOGO2_DEFAULT_IMAGE;
        break;
    case CTwitterTimeline::SVC_TIMELOG:
        defaultImageURL = TIMELOG_DEFAULT_IMAGE;
        break;
    case CTwitterTimeline::SVC_HARUFM:
        defaultImageURL = HARUFM_DEFAULT_IMAGE;
        break;
    case CTwitterTimeline::SVC_HATENAHAIKU:
        defaultImageURL = HATENAHAIKU_DEFAULT_IMAGE;
        break;
    }

    sprintf( filename,
             "%s%s",
             cacheDir,
             strrchr( defaultImageURL, '/' ) + 1 );

    if ( u->bitmap )
        DeleteObject( u->bitmap );
    u->bitmap = img.HttpOpen( defaultImageURL, filename );
    if ( u->bitmap )
        allocated = true;

    return ( allocated );
}

bool
LoadUserIcon( CStatic                    *sp,
              TWITTER_USER               *u,
              CTwitterTimeline::SVC_TYPE &type,
              const char                 *cacheDir,
              CString                    username         /* = _T("") */,
              CString                    password         /* = _T("") */,
              bool                       useOAuth         /* = false  */,
              CString                    oauthToken       /* = _T("") */,
              CString                    oauthTokenSecret /* = _T("") */ )
{
    CImage  img;
    bool    allocated = false;

    if ( !(u->id[0]) )
        allocated = LoadDefaultUserIcon( u, type, cacheDir );
    else if ( !(u->profileImageURL[0]) ) {
        if ( type == CTwitterTimeline::SVC_TWITTER ) {
            CTwitter        t;
            TWITTER_USER    uu;

            t.m_username          = username;
            t.m_password          = password;
            t.m_useOAuth          = useOAuth;
            t.m_oauthToken        = oauthToken;
            t.m_oauthTokenSecret  = oauthTokenSecret;
            uu.profileImageURL[0] = NUL;
            uu = t.ShowUser( u->id );
            if ( uu.profileImageURL[0] )
                strcpy( u->profileImageURL, uu.profileImageURL );
        }
        else if ( type == CTwitterTimeline::SVC_TIMELOG ) {
            sprintf( u->profileImageURL,
                     "http://timelog.jp/images/user/%s_m.jpg",
                     u->id );
        }
    }

    if ( !(u->bitmap) /* && !allocated */ ) {
        char    *p;
        char    filename[MAX_PATH];

        if ( strstr( u->profileImageURL, "jaiku.com" ) )
            type = CTwitterTimeline::SVC_JAIKU;
        else if ( strstr( u->profileImageURL, "wassr.jp" ) )
            type = CTwitterTimeline::SVC_WASSR;
        else if ( strstr( u->profileImageURL, "mogo2.jp" ) )
            type = CTwitterTimeline::SVC_MOGO2;
        else if ( strstr( u->profileImageURL, "timelog.jp" ) )
            type = CTwitterTimeline::SVC_TIMELOG;
        else if ( strstr( u->profileImageURL, "haru.fm" ) )
            type = CTwitterTimeline::SVC_HARUFM;
        else if ( strstr( u->profileImageURL, "hatena.ne.jp" ) )
            type = CTwitterTimeline::SVC_HATENAHAIKU;

        if ( type == CTwitterTimeline::SVC_JAIKU )
            sprintf( filename,
                     "%sJ%s",
                     cacheDir,
                     u->id );
        else if ( type == CTwitterTimeline::SVC_MOGO2 )
            sprintf( filename,
                     "%sM%s",
                     cacheDir,
                     u->id );
        else if ( type == CTwitterTimeline::SVC_TIMELOG )
            sprintf( filename,
                     "%sTL_%s",
                     cacheDir,
                     u->id );
        else if ( type == CTwitterTimeline::SVC_HARUFM )
            sprintf( filename,
                     "%sHF_%s",
                     cacheDir,
                     u->id );
        else if ( type == CTwitterTimeline::SVC_HATENAHAIKU )
            sprintf( filename,
                     "%sHH_%s",
                     cacheDir,
                     u->id );
        else
            sprintf( filename,
                     "%s%s",
                     cacheDir,
                     u->id );
        p = strrchr( u->profileImageURL, '.' );
        if ( p && (type != CTwitterTimeline::SVC_HARUFM) ) {
            strcat( filename, p );
            p = strrchr( filename, '?' );
            if ( p )
                *p = NUL;
        }
        else {
            if ( (type == CTwitterTimeline::SVC_TIMELOG) ||
                 (type == CTwitterTimeline::SVC_HARUFM)     )
                strcat( filename, ".jpg" );
        }

        setTimeoutTime( 15 );
        u->bitmap = img.HttpOpen( u->profileImageURL, filename );
        setTimeoutTime( DEFAULT_HTTP_TIMEOUT );
        if ( u->bitmap )
            allocated = true;
        else
            allocated = LoadDefaultUserIcon( u, type, cacheDir );
    }

    if ( u->bitmap ) {
        // 画像が大きくてはみ出す場合は縮小する
        int     height = 0;
        int     width  = 0;
        int     maxSq  = 50; /* Jaiku */
        BITMAP  bmp;
        GetObject( u->bitmap, sizeof ( bmp ), (LPSTR)&bmp );
        height = bmp.bmHeight;
        width  = bmp.bmWidth;

        switch ( type ) {
        case CTwitterTimeline::SVC_TWITTER:
        case CTwitterTimeline::SVC_HARUFM:
            maxSq  = 48;
            break;
        case CTwitterTimeline::SVC_JAIKU:
        case CTwitterTimeline::SVC_HATENAHAIKU: /* 64x64 */
            maxSq  = 50;
            break;
        case CTwitterTimeline::SVC_MOGO2:
            maxSq  = 30;
            break;
        case CTwitterTimeline::SVC_TIMELOG:
            maxSq  = 35;
            break;
        case CTwitterTimeline::SVC_WASSR:
            maxSq  = 32;
            break;
        }

        maxSq = (int)(maxSq * 1.02);
        sp->ShowWindow( FALSE );
        sp->SetBitmap( u->bitmap );
        if ( (height > maxSq) || (width > maxSq) ) {
            // 表示領域サイズに合わせて画像を縮小表示する
            int sig = ((max(height, width)) + (maxSq - 1)) / maxSq;
            sp->SetWindowPos( sp->GetTopWindow(),
                              0, 0, width/sig, height/sig,
                              SWP_NOMOVE );
        }
        sp->ShowWindow( TRUE );
    }
    return ( allocated );
}
