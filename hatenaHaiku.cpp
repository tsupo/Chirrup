/*
 * hatenaHaiku.cpp : はてなハイク クライアント chirrup
 *      はてなハイク API を利用するための各種処理群
 *          written by H.Tsujimura  22 Aug 2008
 *
 *      Copyright (c) 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/hatenaHaiku.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 11    09/04/28 20:52 Tsujimura543
 * タイムアウト取得処理が規定時間内に終わらない場合の処理を変更
 * (スレッド強制終了方式ではなく、イベント通知方式を採用)
 * 
 * 10    09/04/10 17:20 Tsujimura543
 * GetTimeline() に例外発生時対策(暫定)を追加
 * 
 * 9     09/03/10 22:14 Tsujimura543
 * GetStringFromJSON() にバッファオーバーラン対策を実施
 * 
 * 8     08/12/04 18:19 Tsujimura543
 * コード整理、安定化作業を実施
 * 
 * 7     08/09/04 19:27 Tsujimura543
 * はてなハイク の source (from XXX) に対応
 * 
 * 6     08/09/03 19:21 Tsujimura543
 * delete [] response; するタイミングを修正
 * 
 * 5     08/09/02 18:38 Tsujimura543
 * 今回の修正に伴うタイムライン表示関連の動作確認、終わり
 * 
 * 4     08/09/02 18:28 Tsujimura543
 * 取得結果(JSON)が whitespace を使って整形されたものに変更された
 * 関係でタイムライン抽出がうまく動かなくなってしまったため、
 * CutWhiteSpaces() を追加することで対処した
 * 
 * 3     08/08/22 20:32 Tsujimura543
 * reply の投稿に対応
 * 
 * 2     08/08/22 19:55 Tsujimura543
 * 動作確認終了
 * 
 * 1     08/08/22 18:42 Tsujimura543
 * 新規作成
 */

#include "chirrup.h"
#include "hatenaHaiku.h"
#include "twitterTimeline.h"
#include "http.h"
extern "C" {
#include "utility.h"
}

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/hatenaHaiku.cpp 1     09/05/14 3:50 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

CHatenaHaiku::CHatenaHaiku() : CService()
{
#ifdef  _DEBUG
    m_serviceName   = _T("hatenaHaiku");
#endif
    m_serviceSymbol = _T("HanenaHaiku");
}

CHatenaHaiku::~CHatenaHaiku()
{
}

void CHatenaHaiku::DeleteReserved(TWITTER_STATUS *sp)
{
    if ( sp && sp->reserved ) {
    }
}

void CHatenaHaiku::DeleteReserved2(TWITTER_STATUS *sp)
{
    if ( sp && sp->reserved2 ) {
    }
}

/*
 *  はてなハイク API
 */

// 発言を投稿
bool
CHatenaHaiku::PostUpdate( CString monologue, ProceedingDialog *pdlg )
{
    bool        ret = false;
    size_t      sz  = MAX_CONTENT_SIZE;
    size_t      len = monologue.GetLength() * 18;
    char        *request  = new char[7 + len + 1];
    char        *response = new char[sz];
    const char  *url = "http://h.hatena.ne.jp/api/statuses/update.json";
    char        rid[MAX_KEYLENGTH];
    char        *p;

    rid[0] = NUL;
    if ( !strncmp( monologue, ">>", 2 ) ) {
        strncpy( rid, ((const char *)monologue) + 2, MAX_KEYLENGTH - 2 );
        rid[MAX_KEYLENGTH - 2] = NUL;
        p = strchr( rid, ' ' );
        if ( p ) {
            *p = NUL;
            monologue = strchr( monologue, ' ' ) + 1;
        }
    }
    p = sjis2utf( monologue );

    if ( request && response ) {
        sprintf( request,
                 "status=%s&"
                 "source=%s",
                 encodeURL( p ? p : monologue ),
                 "Chirrup" );
        if ( rid[0] )
            sprintf( request + strlen(request),
                     "&in_reply_to_status_id=%s",
                     rid );
        SetUserAgent();
        setUpReceiveBuffer( response, sz );
        _http_postBASIC( url, m_username, m_password,
                         request, response, NULL, pdlg );
        if ( *response ) {
            if ( strstr( response, "\"created_at\"" ) )
                ret = true;
        }
    }

    if ( response )
        delete [] response;
    if ( request )
        delete [] request;

    return ( ret );
}

// friends_timeline を取得
CString
CHatenaHaiku::GetFriendsTimeline(
                CTwitterTimeline *timeline,
                ProceedingDialog *pdlg
            )
{
    return ( CService::GetFriendsTimeline(
                 "http://h.hatena.ne.jp/api/statuses/friends_timeline.json",
                 timeline,
                 pdlg ) );
}

// public_timeline を取得
CString
CHatenaHaiku::GetPublicTimeline(
                CTwitterTimeline *timeline,
                ProceedingDialog *pdlg
            )
{
    return ( CService::GetPublicTimeline(
                 "http://h.hatena.ne.jp/api/statuses/public_timeline.json",
                 timeline,
                 pdlg ) );
}

// user_timeline を取得
CString
CHatenaHaiku::GetUserTimeline(
                CTwitterTimeline *timeline,
                ProceedingDialog *pdlg
            )
{
    return ( CService::GetUserTimeline( 
                     "http://h.hatena.ne.jp/api/statuses/user_timeline.json",
                     timeline,
                     pdlg ) );
}

// 自分のスクリーン名の取得
CString CHatenaHaiku::GetScreenName()
{
    TWITTER_USER    user;
    CString         screenName = _T("");
    size_t          sz  = MAX_CONTENT_SIZE;
    char            *response = new char[sz];
    char            url[MAX_URLLENGTH];
 // bool            ret = false;

    if ( response ) {
        strcpy( url, "http://h.hatena.ne.jp/api/statuses/user_timeline.xml" );
        SetUserAgent();
        setUpReceiveBuffer( response, sz );
        _http_getBASIC( url, m_username, m_password, response, NULL, NULL );
        if ( *response ) {
            char    *p = strstr( response, "<screen_name>" );
            if ( p ) {
             // ret  = true;
                user = GetUserFromXML(response, response + strlen(response));
                screenName = user.screenName;
            }
        }

        delete [] response;
    }

    return ( screenName );
}



CString
CHatenaHaiku::GetTimeline(
                CString          &messages,
                TWITTER_STATUS   **stat,
                long             &numOfStats,
                TIMELINE_TYPE    t,
                const char       *endPointURL,
                CTwitterTimeline *timeline,
                ProceedingDialog *pdlg
            )
{
    CChirrupApp *ap = (CChirrupApp *)AfxGetApp();

    if ( timeline->m_numOfStats > 0 ) {
        if ( !(*stat) ) {
            *stat = new TWITTER_STATUS[MAX_NUMOFSTATUS];
            numOfStats = 0;
        }
        int i;
        for ( i = 0; i < timeline->m_numOfStats; i++ )
            (*stat)[i] = (timeline->m_stat)[i];
        numOfStats = timeline->m_numOfStats;
    }

    size_t  sz = MAX_CONTENT_SIZE * 16;
    char    *response = new char[sz];
    if ( response ) {
        CString url = endPointURL;
        if ( *stat ) {
            CTime   time   = CTime( 2000, 1, 1, 0, 0, 0, 0 );
            CTime   recent = time;

            int i;
            for ( i = 0; i < timeline->m_numOfStats; i++ ) {
                time = (*stat)[i].createdAt;
                if ( (time - recent).GetTotalSeconds() > 0 )
                    recent = time;
            }

            recent -= 24 * 60 * 60;
            url += "?since=";
            url += encodeDateTime(recent.Format("%a, %d %b %Y %H:%M:%S GMT"));
                // Tue%2C+27+Mar+2007+22%3A55%3A48+GMT
        }

        SetUserAgent();
        setUpReceiveBuffer( response, sz );
        if ( t != PUBLIC_TIMELINE )
            _http_getBASIC(url, m_username, m_password, response, NULL, pdlg);
        else
            _http_get( url, response, pdlg );
        if ( response[0] ) {
            CutWhiteSpaces( response );

            bool    error = false;
            try {
                GetStatFromJSON( response, stat, numOfStats );
            }
            catch (...) {
                error = true;
            }

            if ( !error ) {
                WriteLog( timeline );

                int i;
                messages = _T("");
                for ( i = 0; i < numOfStats; i++ ) {
                    if ( ap->m_event ) {
                        DWORD   r = WaitForSingleObject( ap->m_event, 0 );
                        if ( r == WAIT_OBJECT_0 ) {
                            // 作業中断
                            ResetEvent( ap->m_event );
#ifdef  _DEBUG
                            MessageBox( NULL,
                                        "作業中断",
                                        "CHatenaHaiku::GetTimeline()",
                                        MB_OK|MB_ICONWARNING );
#endif
                            break;
                        }
                    }

                    MakeMessageForScreen( messages, &((*stat)[i]) );
                    if ( messages.GetLength() >= (MAX_CONTENT_SIZE / 2) )
                        break;
                }
            }
        }

        delete [] response;
    }

    timeline->m_numOfStats = numOfStats;
    if ( timeline->m_numOfStats > 0 ) {
        int i;
        for ( i = 0; i < numOfStats; i++ )
            (timeline->m_stat)[i] = (*stat)[i];
    }

    return ( messages );
}

CString CHatenaHaiku::GetStatusID(
                        const char *p,
                        const char *terminator
                    )
{
    const char  *q  = p;
    const char  *r1 = strstr( q, "\"user\"" );
    const char  *r2 = strstr( q, "\"id\"" );

    if ( r1 && r2 && (r1 < terminator) && (r2 < terminator) ) {
        if ( r2 > r1 ) {
            r1 = strstr( r2 + 4 , "\"id\"" );
            if ( r1 && (r1 < terminator) )
                q = r1;
        }
    }

    CString s = GetIdFromJSON( q, terminator );
    return ( s );
}

CString
CHatenaHaiku::GetIdFromJSON( const char *p, const char *terminator )
{
    char    msgid[MAX_KEYLENGTH * 2 + 2];
    CString id;

    // "id"
    msgid[0] = NUL;
    GetStringFromJSON(msgid, MAX_KEYLENGTH * 2 + 2, "\"id\"", p, terminator);
    id = msgid;

    return ( id );
}

void CHatenaHaiku::SetStatFromJSON(
                        const char       *q,
                        const char       *s,
                        TWITTER_STATUS   *sp,
                        CString          &message
                    )
{
    bool    first = false;

    if ( !strncmp( q, "\"user\"", 6 ) ) {
        const char  *r;

        sp->user = GetUserFromJSON( q, s );
        first = true;
        r = strstr( q, "}," );
        if ( r && (r < s) )
            q = r + 2;
    }

    sp->createdAt = GetCreatedAtFromJSON(q, s);
    strcpy( sp->source, GetSource( q, s, sp->sourceURL ) );
    strcpy( sp->id,     GetStatusID(q, s) );
    strcpy( sp->text,   GetTextFromJSON( q, s, sp->orig_text ) );

    if ( strchr( sp->text, '&' ) ) {
        strcpy( sp->text, decodeString( sp->text ) );

        char    *p = strchr( sp->text, '&' );
        if ( p && strchr( p + 1, ';' ) )
            strcpy( sp->text,
                    replaceEntityStrings( sp->text, CHARSET_SHIFTJIS ) );
    }
    if ( strchr( sp->orig_text, '&' ) ) {
        strcpy( sp->orig_text, decodeString( sp->orig_text ) );

        char    *p = strchr( sp->orig_text, '&' );
        if ( p && strchr( p + 1, ';' ) )
            strcpy( sp->orig_text,
                    replaceEntityStrings( sp->orig_text, CHARSET_UTF8 ) );
    }

    if ( !first )
        sp->user = GetUserFromJSON( q, s );

    MakeMessageForScreen( message, sp );
    strcpy( sp->user.lastStatus, sp->text );
    MakeMessageForLogging( sp );
}

TWITTER_USER
CHatenaHaiku::GetUserFromJSON(
                const char *q,
                const char *terminator
            )
{
    TWITTER_USER    u;
    char            temp[BUFSIZ * 2];
    char            temp2[BUFSIZ * 4];
    const char      *p;

    // "user"
    temp[0] = NUL;
    p = strstr( q, "\"user\"" );
    if ( p && (p < terminator) ) {
        p += 6;
        while ( (p < terminator) && *p && (*p != ':') )
            p++;
        if ( *p == ':' ) {
            while ( (p < terminator) && *p && (*p != '{') )
                p++;

            //    "profile_image_url"
            GetStringFromJSON( temp, MAX_URLLENGTH, "\"profile_image_url\"",
                               p, terminator, true );
            strcpy( u.profileImageURL, temp );

            //    "description"
            GetStringFromJSON( temp, BUFSIZ * 2, "\"description\"",
                               p, terminator );
            strcpy( u.description, temp );

            //    "location"
            u.location[0] = NUL;

            //    "id"
            GetStringFromJSON( temp, MAX_KEYLENGTH, "\"id\"", p, terminator );
            strcpy( u.id, temp );

            //    "screen_name"
            GetStringFromJSON( temp, MAX_KEYLENGTH, "\"screen_name\"",
                               p, terminator, false, temp2 );
            strcpy( u.screenName, temp );
            strcpy( u.name, temp );
            strcpy( u.orig_userName, temp2 );

            //    "url"
            GetStringFromJSON( temp, MAX_URLLENGTH, "\"url\"", p, terminator );
            strcpy( u.url, temp );
        }
    }

    u.lastStatus[0] = NUL;
    u.bitmap        = NUL;

    return ( u );
}

char    *
CHatenaHaiku::GetSource(
                const char *q,
                const char *s,
                char       *sourceURL
            )
{
    Thread static char  temp[BUFSIZ * 2];
    GetStringFromJSON( temp, BUFSIZ * 2, "\"source\"", q, s );

#if 0
    char    *p = strstr( temp, "<a href=\"" );
    if ( p ) {
        char    *q;

        p += 9;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( sourceURL, p, q - p );
            sourceURL[q - p] = NUL;

            p = strchr( q + 1, '>' );
            if ( p ) {
                p++;
                q = strstr( p, "</a>" );
                if ( q ) {
                    *q = NUL;
                    strcpy( temp, p );
                }
            }
        }
        else
            sourceURL[0] = NUL;
    }
    else
        sourceURL[0] = NUL;
#else
    sourceURL[0] = NUL;
    if ( temp[0]                 &&
         strcmp( temp, "web")    &&
         strcmp( temp, "mobile") &&
         strcmp( temp, "mail")   &&
         strcmp( temp, "IM")        )
        sprintf( sourceURL, "http://h.hatena.ne.jp/keyword/%s", temp );
#endif

    return ( temp );
}


void
CHatenaHaiku::MakeMessageForScreen(
            CString        &message,
            TWITTER_STATUS *sp )
{
    message += EscapeQuote(sp->user.screenName);
    message += _T(": ");
    message += EscapeQuote(sp->text);

    message += _T(" ");
    if ( m_useTwitStar )
        message += _T("★");
    message += _T("[ID: ");
    message += sp->id;
    message += _T("]");

    if ( sp->source[0] ) {
        message += _T(" (from ");
        if ( sp->sourceURL[0] )
            message += _T("*");
        message += sp->source;
        if ( sp->sourceURL[0] )
            message += _T("*");
        message += _T(")");
    }

    message += _T("\r\n");
}

void
CHatenaHaiku::MakeMessageForLogging( TWITTER_STATUS *sp )
{
    if ( !m_log )
        m_log = new TWITTER_LOG[MAX_NUMOFSTATUS + 1];

    if ( m_log && (m_numOfLogs < MAX_NUMOFSTATUS) ) {
        sprintf( m_log[m_numOfLogs].orig_text,
                 "%s [ID: %s]",
                 sp->orig_text, sp->id );
        strcpy( m_log[m_numOfLogs].orig_userName, sp->user.orig_userName );

        m_log[m_numOfLogs].createdAt = sp->createdAt.GetTime();

        struct tm   ttmm;
     // struct tm   *tm = sp->createdAt.GetGmtTm( &ttmm );
        struct tm   *tm = sp->createdAt.GetLocalTm( &ttmm );

        m_log[m_numOfLogs].createdAt_yyyy = tm->tm_year + 1900;
        m_log[m_numOfLogs].createdAt_mm   = tm->tm_mon + 1;
        m_log[m_numOfLogs].createdAt_dd   = tm->tm_mday;
        m_log[m_numOfLogs].createdAt_HH   = tm->tm_hour;
        m_log[m_numOfLogs].createdAt_MM   = tm->tm_min;
        m_log[m_numOfLogs].createdAt_SS   = tm->tm_sec;
        m_numOfLogs++;
    }
}


char    *
CHatenaHaiku::CutWhiteSpaces( char *p )
{
    char    *ret = p;
    char    *q, *r;

    while ( ( q = strstr( p, "\n   " ) ) != NULL ) {
        r = q + 4;
        while ( (*r == ' ') || (*r == '\t') || (*r == '\r') || (*r == '\n') )
            r++;

        strcpy( q, r );
    }

    return ( ret );
}

