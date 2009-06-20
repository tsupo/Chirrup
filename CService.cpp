/*
 * CService.cpp : Twitter クライアント chirrup
 *      各サービスの API を利用するための各種処理群
 *          written by H.Tsujimura  4 Apr 2007 / 28 Apr 2007 / 19 Jun 2007
 *
 *      Copyright (c) 2007, 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/CService.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 54    09/04/28 20:52 Tsujimura543
 * タイムアウト取得処理が規定時間内に終わらない場合の処理を変更
 * (スレッド強制終了方式ではなく、イベント通知方式を採用)
 * 
 * 53    09/04/28 18:23 Tsujimura543
 * ExpandZla() の無限ループ対策を追加
 * 
 * 52    09/04/16 14:43 Tsujimura543
 * ExpandURL() の展開対象 URL を追加
 * 
 * 51    09/04/01 3:16 Tsujimura543
 * Twitter の OAuth 対応、完了
 * 
 * 50    09/03/31 23:29 Tsujimura543
 * Twitter の OAuth 対応準備 その7
 * 
 * 49    09/03/30 22:19 Tsujimura543
 * Twitter の OAuth 対応準備
 * 
 * 48    09/03/10 22:54 Tsujimura543
 * ExpandZla() 内で無限ループすることがある不具合を修正
 * 
 * 47    09/03/10 22:51 Tsujimura543
 * ExpandTinyURL() 内で無限ループすることがある不具合を修正
 * 
 * 46    09/03/10 22:14 Tsujimura543
 * GetStringFromJSON() にバッファオーバーラン対策を実施
 * 
 * 45    09/03/10 17:07 Tsujimura543
 * GetStringFromJSON() 内の無限ループが発生する可能性のある
 * 処理を修正
 * 
 * 44    09/03/09 20:10 Tsujimura543
 * ExpandURL() 内に無限ループ防止対策を入れてみた
 * 
 * 43    09/03/06 19:58 Tsujimura543
 * ExpandURL() の展開対象 URL を追加
 * 
 * 42    09/03/03 21:37 Tsujimura543
 * ExpandURL() の展開対象 URL を追加
 * 
 * 41    09/03/03 20:56 Tsujimura543
 * GetStatFromJSON() を修正 (暫定対処)
 * 
 * 40    09/03/03 1:30 Tsujimura543
 * 展開対象の短縮URLを増やしてみた
 * 
 * 39    08/12/04 18:19 Tsujimura543
 * コード整理、安定化作業を実施
 * 
 * 38    08/11/17 11:36 Tsujimura543
 * CService::GetTinyURL() [4引数版] を修正
 * (tinyurl の返すレスポンスのフォーマット変更に対応)
 * 
 * 37    08/08/22 18:42 Tsujimura543
 * 「はてなハイク」対応
 * 
 * 36    08/03/26 22:17 Tsujimura543
 * http_get(), http_post() → _http_get(), _http_post() へ移行
 * 
 * 35    08/02/07 22:36 Tsujimura543
 * copyright 表示を修正 (2008 を追加)
 * 
 * 34    08/01/11 19:52 Tsujimura543
 * (1) ExpandPheedo() を追加
 * (2) ExtractURL() で前後に余分な空白文字をつけけなくてもよい場合は
 *     つけないように直した
 * 
 * 33    07/12/26 21:32 Tsujimura543
 * リファクタリングを実施
 * 
 * 32    07/12/26 20:15 Tsujimura543
 * ExpandZla() を修正、余分な変数、処理を削除
 * 
 * 31    07/12/26 20:10 Tsujimura543
 * z.la で圧縮されている URL の展開処理を追加
 * 
 * 30    07/12/19 18:41 Tsujimura543
 * http関連の関数群を http.cpp に分離
 * 
 * 29    07/12/19 17:28 Tsujimura543
 * __http_postBASIC() を http_postEx() の置き換えにも使えるようにした
 * 
 * 28    07/12/19 17:17 Tsujimura543
 * _http_postBASIC() の引数を追加
 * 
 * 27    07/12/19 16:56 Tsujimura543
 * _http_getBASIC() の引数を追加
 * 
 * 26    07/12/12 19:09 Tsujimura543
 * RegulateCode() を導入。UTF-8 には存在するが CP932 には存在しない文字
 * について、文字化け状態になるのを可能な限り防ぐようにしてみた
 * 
 * 25    07/08/25 0:45 Tsujimura543
 * 「ついすた」に対応 (表示)
 * 
 * 24    07/08/14 19:34 Tsujimura543
 * GetStatFroJSON() の haru.fm 対応部分を修正
 * ("embeds" の後に "embedTag" がある場合の考慮が抜けていた)
 * 
 * 23    07/08/14 19:14 Tsujimura543
 * GetStatFromJSON() を修正、haru.fm の JSON に "embeds" が含まれる
 * ケースに対応
 * 
 * 22    07/07/17 21:34 Tsujimura543
 * GetStatFromJSON() を修正、haru.fm の JSON に "images" が含まれる
 * ケースに対応
 * 
 * 21    07/07/17 18:41 Tsujimura543
 * GetTinyURL() を追加
 * 
 * 20    07/07/10 23:08 Tsujimura543
 * 調査用の ASSERT() を入れる [for haru.fm]
 * 
 * 19    07/07/06 17:04 Tsujimura543
 * 念のために、OverwriteStatFromJSON() を呼び出す前に、当該
 * サービスが Haru.fm なのかどうかチェックするようにした
 * 
 * 18    07/07/05 22:30 Tsujimura543
 * Haru.fm のコメントツリーの更新に対応
 * 
 * 17    07/07/05 0:46 Tsujimura543
 * (1) GetStatFromJSON(), GetUserTimeline() の引数を変更
 * (2) TWITTER_USER 構造体の変更(orig_userNameを追加)に伴う修正
 * 
 * 16    07/07/03 14:53 Tsujimura543
 * haru.fm 対応 (動作確認済み)
 * 
 * 15    07/06/27 18:13 Tsujimura543
 * haru.fm に対応
 * 
 * 14    07/06/25 23:12 Tsujimura543
 * reserve, reserve2 まわりを修正
 * 
 * 13    07/06/25 18:21 Tsujimura543
 * DeleteReserved(), DeleteReserved2() 関連、コードを整理
 * 
 * 12    07/06/25 17:40 Tsujimura543
 * DeleteReserved(), DeleteReserved2() を追加
 * 
 * 11    07/06/22 18:08 Tsujimura543
 * TWITTER_STATUS に reserved を追加したのに伴う修正を実施
 * 
 * 10    07/06/21 23:56 Tsujimura543
 * ExpandTinyURL() を修正、&amp; → & に置換する処理を追加
 * 
 * 9     07/06/21 22:10 Tsujimura543
 * GetStringFromXML() を修正、&# を含まない文字列も Shift_JIS に変換
 * するようにした
 * 
 * 8     07/06/21 19:15 Tsujimura543
 * SetUserAgent() を CService 内のメソッドに一本化した
 * 
 * 7     07/06/21 18:16 Tsujimura543
 * status ID 格納領域でメモリオーバーランが発生する可能性が
 * あることが判明したため、対策を実施
 * 
 * 6     07/06/20 19:28 Tsujimura543
 * GetStatusID() を導入
 * 
 * 5     07/06/20 17:04 Tsujimura543
 * GetStatFromJSON() を Timelog にも対応させた
 * 
 * 4     07/06/20 15:45 Tsujimura543
 * Timelog 対応
 * 
 * 3     07/06/20 0:29 Tsujimura543
 * ExpandTinyURL() を修正、tinyurl の num 部分が 6文字でないパターン
 * にも対処
 * 
 * 2     07/06/19 22:50 Tsujimura543
 * さらに共通化可能な部分を CService に移した
 * 
 * 1     07/06/19 21:19 Tsujimura543
 * 今まで CTwitter 内でやっていた API の呼び出し、実行結果の解析処理のう
 * ち、 Twitter 以外のサービスと共通化できる部分を CService として独立さ
 * せた
 */

#include "chirrup.h"
#include "CService.h"
#include "timelog.h"
#include "twitterTimeline.h"
#include "haruFm.h"
extern "C" {
#include "utility.h"
}
#include "widechar.h"
#include "http.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/CService.cpp 1     09/05/14 3:50 tsupo $";
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

CService::CService()
{
    m_useOAuth         = false;
	m_messages         = _T("");
    m_username         = _T("");
    m_password         = _T("");
    m_oauthToken       = _T("");
    m_oauthTokenSecret = _T("");
    m_screenName       = _T("");

    m_numOfStats    = 0;
    m_stat          = NULL;
    m_numOfStats2   = 0;
    m_stat2         = NULL;
    m_numOfStats3   = 0;
    m_stat3         = NULL;

    m_numOfLogs     = 0;
    m_log           = NULL;

    m_useTwitStar   = false;

#ifdef  _DEBUG
    m_serviceName   = _T("");
#endif
    m_serviceSymbol = _T("");
}

CService::~CService()
{
    if ( m_log ) {
        delete [] m_log;
        m_log = NULL;
    }

    if ( m_stat ) {
        delete [] m_stat;
        m_stat = NULL;
    }
    if ( m_stat2 ) {
        delete [] m_stat2;
        m_stat2 = NULL;
    }
    if ( m_stat3 ) {
        delete [] m_stat3;
        m_stat3 = NULL;
    }
}


// User-Agent を設定
void
CService::SetUserAgent()
{
    CString version;
    version.LoadString(IDS_VERSION);

    CString userAgent = _T("Chirrup/" );
    userAgent += version;
    userAgent += _T("\r\n"
        "X-");
    userAgent += m_serviceSymbol;
    userAgent += _T("-Client: Chirrup\r\n"
        "X-");
    userAgent += m_serviceSymbol;
    userAgent += _T("-Client-Version: ");
    userAgent += version;
    userAgent += _T("\r\n"
        "X-");
    userAgent += m_serviceSymbol;
    userAgent += _T("-Client-URL: "
            "http://watcher.moe-nifty.com/memo/files/chirrup.xml");

    setUserAgent( userAgent );
}


// friends_timeline を取得
CString
CService::GetFriendsTimeline(
                const char       *endPointURL,
                CTwitterTimeline *timeline,
                ProceedingDialog *pdlg
            )
{
    GetTimeline( m_messages,
                 &m_stat,
                 m_numOfStats,
                 FRIENDS_TIMELINE,
                 endPointURL,
                 timeline,
                 pdlg );

    return ( m_messages );
}

// public_timeline を取得
CString
CService::GetPublicTimeline(
                const char       *endPointURL,
                CTwitterTimeline *timeline,
                ProceedingDialog *pdlg
            )
{
    GetTimeline( m_messages2,
                 &m_stat2,
                 m_numOfStats2,
                 PUBLIC_TIMELINE,
                 endPointURL,
                 timeline,
                 pdlg );

    return ( m_messages2 );
}

// user_timeline を取得
CString
CService::GetUserTimeline(
                const char       *endPointURL,
                CTwitterTimeline *timeline,
                ProceedingDialog *pdlg
            )
{
    GetTimeline( m_messages3,
                 &m_stat3,
                 m_numOfStats3,
                 USER_TIMELINE,
                 endPointURL,
                 timeline,
                 pdlg );

    return ( m_messages3 );
}

/*
 *  ユーティリティメソッド群 
 */

CString CService::GetStatFromJSON(
                        const char     *p,
                        TWITTER_STATUS **sp,
                        long           &status
                    )
{
    CString         message = _T("");
    const char      *q, *s;
    const char      *delim  = "}}";
    const char      *delim2 = "},{";
    const char      *delim3 = "}]";
    const char      *delim4 = "}\n,\n{";
    const char      *delim5 = "\"embedTag\":";  // for haru.fm
    int             cnt     = 0;
    bool            update  = true;
    bool            overwritten = false;
    char            id[MAX_KEYLENGTH * 2 + 2];
    char            msg[MAX_DESCRIPTION_LEN];
    CChirrupApp     *ap = (CChirrupApp *)AfxGetApp();

    if ( !sp )
        return ( message );

    m_numOfLogs = 0;

    q = decodeContents( (char *)p );
#ifdef  _DEBUG
    FILE    *fp = NULL;

    if ( !strcmp( m_serviceName, "twitter" ) )
        fp = fopen( "./twitter.json", "w" );
    else if ( !strcmp( m_serviceName, "wassr" ) )
        fp = fopen( "./wassr.json", "w" );
    else if ( !strcmp( m_serviceName, "mogo2" ) )
        fp = fopen( "./mogo2.json", "w" );
    else if ( !strcmp( m_serviceName, "timelog" ) )
        fp = fopen( "./timelog.json", "w" );
    else if ( !strcmp( m_serviceName, "harufm" ) )
        fp = fopen( "./harufm.json", "w" );
    else if ( !strcmp( m_serviceName, "hatenaHaiku" ) )
        fp = fopen( "./hatenaHaiku.json", "w" );
    if ( fp ) {
        fputs( q, fp );
        fclose( fp );
    }
#endif

    while ( q && *q ) {
        if ( (*q == '{') || (*q == '[') )
            break;
        q++;
    }

    while ( q && *q ) {
        if ( ap->m_event ) {
            DWORD   r = WaitForSingleObject( ap->m_event, 0 );
            if ( r == WAIT_OBJECT_0 ) {
                // 作業中断
                ResetEvent( ap->m_event );
#ifdef  _DEBUG
                MessageBox( NULL,
                            "作業中断",
                            "CService::GetStatFromJSON()",
                            MB_OK|MB_ICONWARNING );
#endif
                break;
            }
        }

        msg[0]      = NUL;
        overwritten = false;

        if ( !(*sp) ) {
            *sp = new TWITTER_STATUS[MAX_NUMOFSTATUS];
            status = 0;
            update = false;
        }

        if ( *q == '[' )
            q++;
        if ( *q == ',' )
            q++;
        if ( *q == '{' )
            q++;

        s = strstr( q, delim5 );
        if ( !s ) {
            s = strstr( q, delim );
            if ( s ) {
                // text 中に "{{ (>_<) }}" のような文字列がある場合に
                // 誤爆してしまう件の対策
                const char  *pp = s + strlen( delim );
                if ( (*pp != ',') && (*pp != ']') )
                    s = NULL;
            }
        }
        if ( !s )
            s = strstr( q, delim2 );
        if ( !s )
            s = strstr( q, delim3 );
        if ( !s )
            s = strstr( q, delim4 );
        if ( !s || ((size_t)(s - q) <= strlen(delim5)) )
            break;

        if ( update ) {
            int     i;
            bool    found = false;

            strcpy( id, GetStatusID(q, s) );
            ASSERT( strcmp( id, "0" ) != 0 );

            for ( i = 0; i < status; i++ ) {
                // 重複チェック
                ASSERT( strcmp( (*sp)[i].id, "0" ) != 0 );
                if ( !strcmp( id, (*sp)[i].id ) ) {
                    found = true;
                    break;
                }
            }

            if ( found ) {
                if ( !strncmp( s, delim5, strlen(delim5) ) ) {
                    if ( !m_serviceSymbol.Compare("HaruFm") ) {
                        CHaruFm *p  = (CHaruFm *)this;
                        overwritten = p->OverwriteStatFromJSON(
                                                q, s, &((*sp)[i]), message );
                    }
                    if ( !overwritten ) {
                        const char  *t = strstr( s, "},{" );
                        if ( t )
                            q = t + 2;
                        else {
                            const char  *u = strstr( s, "\"images\":[" );
                            if ( !u )
                                u = strstr( s, "\"embeds\":[" );

                            t = strstr( s, "\"}" );
                            if ( u && (u < t) ) {
                                t = strstr( s, "]}" );
                                if (t &&
                                    !strncmp(t + 3, delim5, strlen(delim5))) {
                                    t += (3 + strlen(delim5));
                                    t = strstr( t, "\"}" );
                                }
                            }
                            if ( t )
                                q = t + 2;
                            else
                                q = s + strlen(delim5);
                        }
                        continue;
                    }
                }
                else {
                    q = s + 2;
                    continue;
                }
            }
            else {
                for ( i = status; i > cnt; i-- ) {
                    if ( i >= MAX_NUMOFSTATUS )
                        continue;
                    (*sp)[i] = (*sp)[i - 1];
                }

                (*sp)[cnt].reserved  = NULL;
                (*sp)[cnt].reserved2 = NULL;
                SetStatFromJSON( q, s, &((*sp)[cnt]), message );
                cnt++;
            }
        }
        else
            SetStatFromJSON( q, s, &((*sp)[status]), message );

        if ( !strncmp( s, delim5, strlen(delim5) ) ) {
            // for Haru.fm
            const char  *t = strstr( s, "},{" );
            if ( t )
                q = t + 2;
            else {
                const char  *u = strstr( s, "\"images\":[" );
                if ( !u )
                    u = strstr( s, "\"embeds\":[" );

                t = strstr( s, "\"}" );
                if ( u && (u < t) ) {
                    t = strstr( s, "]}" );
                    if ( t && !strncmp( t + 3, delim5, strlen(delim5) ) ) {
                        t += (3 + strlen(delim5));
                        t = strstr( t, "\"}" );
                    }
                }
                if ( t )
                    q = t + 2;
                else
                    q = s + strlen(delim5);
            }
        }
        else
            q = s + 2;
        if ( !overwritten ) {
            if ( update && (status >= MAX_NUMOFSTATUS) )
                status = MAX_NUMOFSTATUS - 1;
            status++;
        }
        if ( ((!update) && (status >= MAX_NUMOFSTATUS))    ||
             (message.GetLength() >= MAX_CONTENT_SIZE / 2)    )
            break;
    }

    return ( message );
}


char    *
CService::GetStringFromJSON(
                char       *result,
                size_t     result_len,
                const char *name,
                const char *q,
                const char *terminator,
                bool       raw         /* = false */,
                char       *origString /* = NULL  */
            )
{
    const char  *p, *r;
    char        *pp;

    if ( result_len == 0 )
        result_len = MAX_DESCRIPTION_LEN;

    result[0] = NUL;
    if ( origString )
        origString[0] = NUL;

    p = strstr( q, name );
    if ( p && (p < terminator) ) {
        p += strlen( name );
        while ( (p < terminator) && *p && (*p != ':') )
            p++;
        if ( *p == ':' ) {
            if ( strncmp( p + 1, "null", 4 ) ) {
                do {
                    while ( (p < terminator) && *p && (*p != '"') )
                        p++;
                    if ( (*p == '"') && (*(p - 1) == '\\') )
                        p++;
                    else
                        break;
                } while ( (p < terminator) && *p );
                if ( *p == '"' )
                    p++;

                q = p;
                do {
                    r = strchr( q, '"' );
                    if ( r && (*r == '"') && (*(r - 1) == '\\') )
                        q = r + 1;
                } while ( r && (*r == '"') && (*(r - 1) == '\\') );
                if ( r ) {
                    size_t  l = r - p;
                    if ( l >= result_len )
                        l = result_len - 1;
                    strncpy( result, p, l );
                    result[l] = NUL;

                    if ( origString )
                        strcpy( origString, result );
                    if ( raw == false ) {
                        p = any2sjis( result );
                        if ( p )
                            strcpy( result, p );
                    }
                }
            }
        }
    }

    if ( result[0] ) {
        while ( (( pp = strstr( result, "\\\"" ) ) != NULL) ||
                (( pp = strstr( result, "\\\\" ) ) != NULL) ||
                (( pp = strstr( result, "\r\r" ) ) != NULL) ||
                (( pp = strstr( result, "\n\n" ) ) != NULL) ||
                (( pp = strstr( result, "\\\n" ) ) != NULL)    )
            strcpy( pp, pp + 1 );
        cutExtra( result );
    }
    if ( origString && origString[0] ) {
        while ( (( pp = strstr( origString, "\\\"" ) ) != NULL) ||
                (( pp = strstr( origString, "\\\\" ) ) != NULL) ||
                (( pp = strstr( origString, "\r\r" ) ) != NULL) ||
                (( pp = strstr( origString, "\n\n" ) ) != NULL) ||
                (( pp = strstr( origString, "\\\n" ) ) != NULL)    )
            strcpy( pp, pp + 1 );
        cutExtra( origString );
    }

    return ( result );
}

int
CService::GetIntegerFromJSON(
        const char *name,
        const char *q,
        const char *terminator )
{
    const char  *p;
    int         result = 0;

    p = strstr( q, name );
    if ( p && (p < terminator) ) {
        p += strlen( name );
        while ( (p < terminator) && *p && (*p != ':') )
            p++;
        if ( *p == ':' ) {
            p++;
            while ( (*p == '"') || (*p == ' ' ) )   // for Jaiku
                p++;                                // for Jaiku
            result = atol( p );
        }
    }

    return ( result );
}


CTime
CService::GetCreatedAtFromJSON( const char *q, const char *terminator )
{
    CTime   t;
    bool    done = false;
    char    temp[MAX_DATELENGTH];

    // "created_at"
    GetStringFromJSON(temp, MAX_DATELENGTH, "\"created_at\"", q, terminator);
    if ( temp[0] ) {
        int yyyy, mm, dd, HH, MM, SS;

        getDateTimeFromDateString( temp,
                                   &yyyy, &mm, &dd,
                                   &HH,   &MM, &SS );
        t = CTime( yyyy, mm, dd, HH, MM, SS, 0 );
        done = true;
    }

    if ( !done )
        t = CTime::GetCurrentTime();

    return ( t );
}

char    *
CService::GetIdFromJSON( const char *q, const char *terminator )
{
    Thread static char  temp[MAX_KEYLENGTH * 2 + 2];
    int                 id;

    // "id"
    id = GetIntegerFromJSON( "\"id\"", q, terminator );
    sprintf( temp, "%d", id );

    return ( temp );
}

char            *
CService::GetTextFromJSON(
                const char *q,
                const char *terminator,
                char       *origString /* = NULL */
            )
{
    Thread static char  temp[BUFSIZ * 16];

    // "text"
    GetStringFromJSON( temp, BUFSIZ * 16, "\"text\"", q, terminator,
                       false, origString );
    strcpy( temp, RegulateCode( origString, temp ) );

    // tinyurl を元の URL に展開
    ExpandTinyURL( temp );
    if ( origString && origString[0] )
        ExpandTinyURL( origString );

    return ( temp );
}

TWITTER_USER
CService::GetUserFromJSON( const char *q, const char *terminator )
{
    TWITTER_USER    u;
    char            temp[MAX_DESCRIPTION_LEN];
    char            temp2[BUFSIZ];
    const char      *p;

    // "user"
    temp[0] = NUL;
    p = strstr( q, "\"user\"" );
    if ( p && (p < terminator) ) {
        int id;

        p += 6;
        while ( (p < terminator) && *p && (*p != ':') )
            p++;
        if ( *p == ':' ) {
            while ( (p < terminator) && *p && (*p != '{') )
                p++;

            //    "name"
            GetStringFromJSON(temp, MAX_KEYLENGTH, "\"name\"", p, terminator);
            strcpy( u.name, temp );

            //    "profile_image_url"
            GetStringFromJSON( temp, MAX_URLLENGTH, "\"profile_image_url\"",
                               p, terminator, true );
            strcpy( u.profileImageURL, temp );

            //    "description"
            GetStringFromJSON( temp, MAX_DESCRIPTION_LEN, "\"description\"",
                               p, terminator );
            strcpy( u.description, temp );

            //    "location"
            GetStringFromJSON( temp, MAX_LOGICALLINELEN, "\"location\"",
                               p, terminator );
            strcpy( u.location, temp );

            //    "id"
            id = GetIntegerFromJSON( "\"id\"", p, terminator );
            sprintf( u.id, "%d", id );

            //    "screen_name"
            GetStringFromJSON( temp, MAX_KEYLENGTH, "\"screen_name\"",
                               p, terminator, false, temp2 );
            strcpy( u.screenName, temp );
            strcpy( u.orig_userName, temp2 );

            //    "url"
            GetStringFromJSON(temp, MAX_URLLENGTH, "\"url\"", p, terminator);
            strcpy( u.url, temp );
        }
    }

    u.lastStatus[0] = NUL;
    u.bitmap        = NUL;

    return ( u );
}

TWITTER_USER
CService::GetUserFromXML( const char *p, const char *terminator )
{
    TWITTER_USER    u;
    const char      *q, *term;
    CString         str;

    memset( &u, 0x00, sizeof ( TWITTER_USER ) );

    // "user"
    q = strstr( p, "<user>" );
    if ( q && (q < terminator) ) {
        q += 6;
        term = strstr( q, "</user>" );
        if ( term > terminator )
            term = terminator;

        // id
        str = GetStringFromXML( q, "id", term );
        strcpy( u.id, str );

        // name
        str = GetStringFromXML( q, "name", term );
        strcpy( u.name, str );

        // screen_name
        str = GetStringFromXML( q, "screen_name", term );
        strcpy( u.screenName, str );

        // location
        str = GetStringFromXML( q, "location", term );
        strcpy( u.location, str );

        // description
        str = GetStringFromXML( q, "description", term );
        strcpy( u.description, str );

        // profile_image_url
        str = GetStringFromXML( q, "profile_image_url", term );
        strcpy( u.profileImageURL, str );

        // url
        str = GetStringFromXML( q, "url", term );
        strcpy( u.url, str );

        // status - text
        str = GetStringFromXML( q, "status", "text", term );
        strcpy( u.lastStatus, str );
    }

    return ( u );
}

CTime   CService::GetTimeFromXML( const char *p, const char *name )
{
    CTime   t;
    CString timeStr;
    bool    done = false;

    // "created_at"
    timeStr = GetStringFromXML( p, name, p + strlen(p) );
    if ( timeStr.GetLength() > 0 ) {
        int yyyy, mm, dd, HH, MM, SS;

        getDateTimeFromDateString( timeStr,
                                   &yyyy, &mm, &dd,
                                   &HH,   &MM, &SS );
        t = CTime( yyyy, mm, dd, HH, MM, SS, 0 );
        done = true;
    }

    if ( !done )
        t = CTime::GetCurrentTime();

    return ( t );
}

CString CService::GetStringFromXML(
                        const char *p,
                        const char *name,
                        const char *terminator )
{
    CString     str = _T("");
    size_t      len = strlen(name);
    char        *s  = new char[len + 3];
    char        *e  = new char[len + 4];
    const char  *q, *r;

    if ( !s || !e ) {
        if ( e )
            delete [] e;
        if ( s )
            delete [] s;
        return ( str );
    }

    len += 2;
    sprintf( s, "<%s>", name );
    sprintf( e, "</%s>", name );
    q = strstr( p, s );
    if ( q && (q < terminator) ) {
        r = q + len;
        q = strstr( r, e );
        if ( q ) {
            char    *temp = new char[(q - r) + 1];
            if ( temp ) {
                strncpy( temp, r, q - r );
                temp[q - r] = NUL;

                if ( !strncmp( temp, "<![CDATA[", 9 ) ) {
                    strcpy( temp, temp + 9 );
                    char    *pp = strstr( temp, "]]>" );
                    if ( pp )
                        *pp = NUL;
                 // strcpy( temp, decodeURL( temp ) );
                }

                if ( strstr( temp, "&#" ) )
                    q = decodeNumericReference( temp );
                else
                    q = temp;
                r = any2sjis( q );
                str = r ? r : q;

                delete [] temp;
            }
        }
    }

    delete [] e;
    delete [] s;

    return ( str );
}

CString CService::GetStringFromXML(
                        const char *p,
                        const char *name,
                        const char *param,
                        const char *terminator )
{
    CString     str = _T("");
    size_t      len = strlen(name);
    char        *s  = new char[len + 3];
    char        *e  = new char[len + 4];
    const char  *q, *r;

    if ( !s || !e ) {
        if ( e )
            delete [] e;
        if ( s )
            delete [] s;
        return ( str );
    }

    len += 2;
    sprintf( s, "<%s>", name );
    sprintf( e, "</%s>", name );
    q = strstr( p, s );
    if ( q && (q < terminator) ) {
        q += len;
        r = strstr( q, e );
        if ( r ) {
            char    *temp = new char[(r - q) + 1];
            if ( temp ) {
                strncpy( temp, q, r - q );
                temp[r - q] = NUL;

                str = GetStringFromXML( temp, param, temp + strlen(temp) );

                delete [] temp;
            }
        }
    }

    delete [] e;
    delete [] s;

    return ( str );
}


CString
CService::EscapeQuote( const char *p )
{
    CString s = _T("");
    char    *temp = new char[strlen(p) + 1];
    char    *q, *r;

    strcpy( temp, p );
    q = temp;
    do {
        r = strchr( q, '"' );
        if ( !r ) {
            s += q;
            break;
        }
        *r = NUL;
        s += q;
        s += "\"";
        q = r + 1;
    } while ( *q );

    delete [] temp;

    return ( s );
}

char    *
CService::ExtractURL(
                char       *str,
                size_t     offset,
                const char *response,
                const char *delimiter
            )
{
    char    url2[MAX_URLLENGTH * 16];

    strncpy( url2, response, delimiter - response );
    url2[delimiter - response] = NUL;

    char    *r;
    do {
        r = strstr( url2, "&amp;" );
        if ( r )
            strcpy( r + 1, r + 5 );
    } while ( r );

    char    *buf = new char[strlen(str + offset) + 1];

    strcpy( buf, str + offset );

 // size_t  sz = strlen( url2 );
    if ( *(str - 1) != ' ' ) {
        strcpy( str, " " );
        strcat( str, url2 );
    }
    else
        strcpy( str, url2 );
    if ( *buf != ' ' )
        strcat( str, " " );
    strcat( str, buf );

    delete [] buf;

    return ( str );
}

// Z.la を元の URL に展開
char    *
CService::ExpandZla( char *str )
{
    char    *p  = strstr( str, "http://z.la/" );
    char    *q;
    size_t  sz  = BUFSIZ * 16;
    size_t  len = 0;
    char    response[BUFSIZ * 16];
    char    url[MAX_URLLENGTH * 16];
    char    url2[MAX_URLLENGTH * 16];
    char    *preP = NULL;
    int     error = 0;
    static char lastURL[MAX_URLLENGTH * 16];
    static char lastURL2[MAX_URLLENGTH * 16];
    CChirrupApp *ap = (CChirrupApp *)AfxGetApp();

    while ( p && (strlen( p + 12 ) >= 5) ) {
        if ( ap->m_event ) {
            DWORD   r = WaitForSingleObject( ap->m_event, 0 );
            if ( r == WAIT_OBJECT_0 ) {
                // 作業中断
                ResetEvent( ap->m_event );
#ifdef  _DEBUG
                MessageBox( NULL,
                            "作業中断",
                            "CService::ExpandZla()",
                            MB_OK|MB_ICONWARNING );
#endif
                break;
            }
        }

        memset( url, NUL, MAX_URLLENGTH );
        strncpy( url, p, 12 + 8 );
        url[12 + 8] = NUL;

        q = &(url[12]);
        while ( *q ) {
            if ( ((*q >= '0') && (*q <= '9')) ||
                 ((*q >= 'a') && (*q <= 'z')) ||
                 ((*q >= 'A') && (*q <= 'Z'))    ) {
                q++;
                continue;
            }
            *q = NUL;
            break;
        }
        len = strlen( url );

        if ( !strcmp( url, lastURL ) )
            ExtractURL( p, len, lastURL2, lastURL2 + strlen( lastURL2 ) );
        else {
            error = 0;
            sprintf( url2, "http://z.la/?surl=%s", url );

            sz = BUFSIZ * 16;
            setUpReceiveBuffer( response, sz );
         // http_get( url2, response );
            _http_get( url2, response, NULL );
            if ( *response ) {
                q = strstr( response, "<div class=\"beforurl\">" ); // 圧縮前URL
                if ( q ) {
                    char    *r;

                    q += 22;
                    r = strchr( q, '<' );
                    if ( r ) {
                        ExtractURL( p, len, q, r );
                        strcpy( lastURL, url );
                        strncpy( lastURL2, q, r - q );
                        lastURL2[r - q] = NUL;
                    }
                    else
                        error++;
                }
                else
                    error++;
            }
            else
                error++;

            if ( error )
                break;
        }

        p = strstr( str, "http://z.la/" );
        if ( p && (p == preP) )
            break;  /* 無限ループ回避 */
        if ( p ) {
            char    c = *(p + strlen("http://z.la/"));

            if ( !(((c >= '0') && (c <= '9')) ||
                   ((c >= 'a') && (c <= 'z')) ||
                   ((c >= 'A') && (c <= 'Z'))   ) )
                break;
            preP = p;
        }
    }

    return ( str );
}

// pheedo なフィード購読者向けURLを本来のURLに展開
char    *
CService::ExpandPheedo( char *str )
{
    char    *p    = strstr( str, "/click.phdo?" );
    char    *q;
    char    *base = str;
    size_t  sz    = BUFSIZ * 16;
    size_t  len   = 0;
    char    response[BUFSIZ * 16];
    char    url[MAX_URLLENGTH * 16];
    char    url2[MAX_URLLENGTH * 16];
    static char lastURL[MAX_URLLENGTH * 16];
    static char lastURL2[MAX_URLLENGTH * 16];
    CChirrupApp *ap = (CChirrupApp *)AfxGetApp();

    do {
        if ( ap->m_event ) {
            DWORD   r = WaitForSingleObject( ap->m_event, 0 );
            if ( r == WAIT_OBJECT_0 ) {
                // 作業中断
                ResetEvent( ap->m_event );
#ifdef  _DEBUG
                MessageBox( NULL,
                            "作業中断",
                            "CService::ExpandPheedo()",
                            MB_OK|MB_ICONWARNING );
#endif
                break;
            }
        }

        while ( (p >= base) &&
                ( ((*p >= 'a') && (*p <= 'z')) ||
                  ((*p >= 'A') && (*p <= 'Z')) ||
                  ((*p >= '0') && (*p <= '9')) ||
                  (*p == '.') ||
                  (*p == '/') ||
                  (*p == '#') ||
                  (*p == '_') ||
                  (*p == '-') ||
                  (*p == ';') ||
                  (*p == '=') ||
                  (*p == '&') ||
                  (*p == '%')                     ) ) {
            p--;
        }
        if ( (*p == ':') && (p >= base + 4) ) {
            if ( !strncmp( p - 4, "http", 4 ) )
                p -= 4;
            else if ( !strncmp( p - 5, "https", 5 ) )
                p -= 5;
            else
                p = NULL;
        }
        else
            p = NULL;

        if ( !p )
            break;

        memset( url, NUL, MAX_URLLENGTH );
        strncpy( url, p, MAX_URLLENGTH );
        url[MAX_URLLENGTH - 1] = NUL;

        q = strstr( url, "/click.phdo?" );
        if ( !q )
            break;
        q += 12;
        while ( *q ) {
            if ( ((*q >= '0') && (*q <= '9')) ||
                 ((*q >= 'a') && (*q <= 'z')) ||
                 ((*q >= 'A') && (*q <= 'Z')) ||
                  (*q == '.') ||
                  (*q == '/') ||
                  (*q == '#') ||
                  (*q == '_') ||
                  (*q == '-') ||
                  (*q == ';') ||
                  (*q == '=') ||
                  (*q == '&') ||
                  (*q == '%')                     ) {
                q++;
                continue;
            }
            *q = NUL;
            break;
        }
        len = strlen( url );

        if ( !strcmp( url, lastURL ) )
            strcpy( url2, lastURL2 );
        else {
            sz = BUFSIZ * 16;
            setUpReceiveBuffer( response, sz );
         // http_get( url, response );
            _http_get( url, response, NULL );
            if ( *response ) {
                url2[0] = NUL;
                getCurrentLocation( url2 );

                if ( !strcmp( url, url2 ) )
                    break;

                strcpy( lastURL,  url  );
                strcpy( lastURL2, url2 );
            }
            else
                break;
        }

        // url を url2 に置換
        ExtractURL( p, len, url2, url2 + strlen( url2 ) );
        base = p + strlen( url2 );
        p    = strstr( base, "/click.phdo?" );
    } while ( p );

    return ( str );
}

// 各種「短縮系URL」を元の URL に展開
char    *
CService::ExpandURL( char *str )
{
    static char *shortUrls[] = {
        "http://bit.ly/",
        "http://ff.im/",
        "http://is.gd/",
        "http://short.ie/",
        "http://url.ie/",
        "http://url.im/",
        "http://twurl.nl/",
        "http://ping.fm/",
        "http://uris.jp/",
        "http://s3nt.com/",
        "http://muti.co.za/r/",
        "http://cli.gs/",
        "http://rubyurl.com/",
        "http://fon.gs/",
        "http://tr.im/",
        "http://plurk.com/p/",
        "http://www.plurk.com/p/",
        "http://migre.me/",
        "http://ow.ly/",
        "http://pop.ly/",
        "http://0rz.tw/",
        "http://www.qurl.com/",
        "http://ehow.com/",
        "http://www.easyurl.jp/",
        "http://easyurl.jp/",
        "http://b23.ru/",
        "http://jdem.cz/",
        "http://tumblr.com/x",

        "http://gsfn.us/t/",
        "http://twtad.com/",
        "http://chilp.it/?",
        "http://bkite.com/",
        "http://blip.fm/",
        "http://short.to/",
        "http://imgur.com/",
        "http://twitthis.com/",
        "http://uurl.in/",
        "http://kissa.be/",

        "http://adjix.com/",
        "http://dwarfurl.com/",
        "http://idek.net/",
        "http://ln-s.net/",
        "http://loopt.us/",
        "http://piurl.com/",
        "http://poprl.com/",
        "http://qlnk.net/",
        "http://reallytinyurl.com/",
        "http://smallr.com/",
        "http://snipr.com/",
        "http://snipurl.com/",
        "http://snurl.com/",
        "http://ub0.cc/",
        "http://ur1.ca/",
        "http://urlx.ie/",
        "http://xrl.us/",
        "http://yep.it/",
        "http://zi.ma/",
        "http://zurl.ws/",
        "http://zz.tc/",
        "http://geopo.at/",
        "http://urltea.com/",
        "http://roo.to/",
        "http://kat.cc/",
        "http://symy.jp/",
        "http://mooo.jp/",
        "http://ttu.cc/",
        "http://mo-v.jp/",
        "http://jpan.jp/",
        "http://5jp.net/",
        "http://s-url.net/",
        "http://qqa.jp/",
        "http://qrl.jp/",
        "http://www3.to/",
        "http://www1.to/",
        "http://3w.to/",
        "http://aim.to/",
        "http://url.sh/",
        "http://nihongourl.nu/",
        "http://www.nihongourl.nu/",
        "http://get-shorty.com/",
        "http://feeds.reuters.com/~r/",
        "http://feedproxy.google.com/~r/",
        NULL
    };
    char    *p, *q, *r;
    int     n;
    size_t  sz    = BUFSIZ * 16;
    size_t  len   = 0;
    char    response[BUFSIZ * 16];
    char    url[MAX_URLLENGTH * 16];
    char    url2[MAX_URLLENGTH * 16];
    static char lastURL[MAX_URLLENGTH * 16];
    static char lastURL2[MAX_URLLENGTH * 16];
    int         lastShortUrl = -2;
    int         lastCnt = 0;
    CChirrupApp *ap = (CChirrupApp *)AfxGetApp();

    lastShortUrl = -1;
    for ( n = 0, p = shortUrls[n]; p; n++, p = shortUrls[n] ) {
        if ( ap->m_event ) {
            DWORD   r = WaitForSingleObject( ap->m_event, 0 );
            if ( r == WAIT_OBJECT_0 ) {
                // 作業中断
                ResetEvent( ap->m_event );
#ifdef  _DEBUG
                MessageBox( NULL,
                            "作業中断",
                            "CService::ExpandURL()",
                            MB_OK|MB_ICONWARNING );
#endif
                break;
            }
        }

        q = strstr( str, p );
        if ( q ) {
            memset( url, NUL, MAX_URLLENGTH );
            strncpy( url, q, MAX_URLLENGTH );
            url[MAX_URLLENGTH - 1] = NUL;

            r = url + strlen(shortUrls[n]);
            while ( *r ) {
                if ( ((*r >= '0') && (*r <= '9')) ||
                     ((*r >= 'a') && (*r <= 'z')) ||
                     ((*r >= 'A') && (*r <= 'Z')) ||
                      (*r == '.') ||
                      (*r == '/') ||
                      (*r == '#') ||
                      (*r == '_') ||
                      (*r == '-') ||
                      (*r == '~') || /* @@ */
                      (*r == ';') ||
                      (*r == '=') ||
                      (*r == '&') ||
                      (*r == '%')                     ) {
                    r++;
                    continue;
                }
                *r = NUL;
                break;
            }
            if ( url[strlen( url ) - 1] == '.' )
                url[strlen( url ) - 1] = NUL;
            len = strlen( url );

            if ( !strcmp( url, lastURL ) )
                strcpy( url2, lastURL2 );
            else {
                sz = BUFSIZ * 16;
                setUpReceiveBuffer( response, sz );
                _http_get( url, response, NULL );
                if ( *response ) {
                    url2[0] = NUL;
                    getCurrentLocation( url2 );

                    if ( !strcmp( url, url2 ) )
                        break;

                    strcpy( lastURL,  url  );
                    strcpy( lastURL2, url2 );
                }
                else
                    break;
            }

            // url を url2 に置換
            ExtractURL( q, len, url2, url2 + strlen( url2 ) );

            if (n == lastShortUrl) {
                lastCnt++;
                if (lastCnt >= 3)
                    break;
            }
            else
                lastCnt = 0;

            lastShortUrl = n;
            n = -1;
        }
    }

    return ( str );
}

// tinyurl を元の URL に展開
char    *
CService::ExpandTinyURL( char *str )
{
    char    *p  = strstr( str, "http://tinyurl.com/" );
    char    *q;
    char    *preP = NULL;
    size_t  sz  = BUFSIZ * 16;
    size_t  len = 0;
    char    response[BUFSIZ * 16];
    char    url[MAX_URLLENGTH * 16];
    char    url2[MAX_URLLENGTH * 16];
    bool    done  = false;
    int     error = 0;
    CChirrupApp *ap = (CChirrupApp *)AfxGetApp();
    static char lastURL[MAX_URLLENGTH * 16];
    static char lastURL2[MAX_URLLENGTH * 16];
    Thread static long  depth = 0;

    depth++;
    if (depth >= 20) {
        depth--;
        return ( str );
    }

    while ( p &&
            (strlen( p + 19 ) >= 2)             &&
            (strncmp( p + 19, "api-", 4 ) != 0) &&
            !strstr( p + 19, "php?url=" )          ) {
        if ( ap->m_event ) {
            DWORD   r = WaitForSingleObject( ap->m_event, 0 );
            if ( r == WAIT_OBJECT_0 ) {
                // 作業中断
                ResetEvent( ap->m_event );
#ifdef  _DEBUG
                MessageBox( NULL,
                            "作業中断",
                            "CService::ExpandTinyURL()",
                            MB_OK|MB_ICONWARNING );
#endif
                break;
            }
        }

        memset( url, NUL, MAX_URLLENGTH );
        strncpy( url, p, 19 + 8 );
        url[19 + 8] = NUL;

        q = &(url[19]);
        while ( *q ) {
            if ( ((*q >= '0') && (*q <= '9')) ||
                 ((*q >= 'a') && (*q <= 'z')) ||
                 ((*q >= 'A') && (*q <= 'Z'))    ) {
                q++;
                continue;
            }
            *q = NUL;
            break;
        }
        len = strlen( url );

        if ( !strcmp( url, lastURL ) )
            ExtractURL( p, len, lastURL2, lastURL2 + strlen(lastURL2) );
        else {
            done  = false;
            error = 0;
            sprintf( url2, "http://tinyurl.com/preview.php?num=%s", url + 19 );

            sz = BUFSIZ * 16;
            setUpReceiveBuffer( response, sz );
         // http_get( url2, response );
            _http_get( url2, response, NULL );
            if ( *response ) {
                q = strstr( response, "<a id=\"redirecturl\" href=\"" );
                if ( q ) {
                    char    *r;

                    q += 26;
                    r = strchr( q, '"' );
                    if ( r ) {
                        ExtractURL( p, len, q, r );

                        strcpy( lastURL, url );
                        strncpy( lastURL2, q, r - q );
                        lastURL2[r - q] = NUL;
                        done = true;
                    }
                }
                else
                    error++;
            }
            else
                error++;

            if ( !done ) {
                sz = BUFSIZ * 4;
                setUpReceiveBuffer( response, sz );
             // http_get( url, response );
                _http_get( url, response, NULL );
                if ( !(*response) )
                    error++;
                else {
                    if ( strstr( response, "<h1>Error: " ) )
                        error++;
                    else {
                        strcpy( lastURL, url );
                        getCurrentLocation( url );
                        if ( url[0] ) {
                            ExtractURL( p, len, url, url + strlen(url) );
                            strcpy( lastURL2, url );
                        }
                        else {
                            lastURL[0]  = NUL;
                            lastURL2[0] = NUL;
                        }
                    }
                }
            }

            if ( error )
                break;
        }

        p = strstr( str, "http://tinyurl.com/" );
        if ( p && (p == preP) )
            break;  /* 無限ループ回避 */

        if ( p ) {
            char    c = *(p + strlen("http://tinyurl.com/"));

            if ( !(((c >= '0') && (c <= '9')) ||
                   ((c >= 'a') && (c <= 'z')) ||
                   ((c >= 'A') && (c <= 'Z'))   ) )
                break;

            preP = p;
        }
    }

    if ( strstr( str, "http://z.la/" ) )
        ExpandZla( str );

    if ( strstr( str, "/click.phdo?" ) )
        ExpandPheedo( str );

    if ( strstr( str, "http://" ) )
        ExpandURL( str );

    depth--;
    return ( str );
}


// URL を tinyurl で圧縮
char    *
CService::GetTinyURL(
                const char *targetURL,
                char       *request,
                char       *response,
                size_t     sz
            )
{
    char    url[MAX_URLLENGTH * 16];

    if ( !strchr( targetURL, '#' ) &&
         !strchr( targetURL, '?' )    ) {
        sprintf( url,
                 "http://tinyurl.com/api-create.php?url=%s", targetURL );

        setUpReceiveBuffer( response, sz );
     // http_get( url, response );
        _http_get( url, response, NULL );
        if ( response[0] ) {
            char    *p = strstr( response, "http" );

            if ( p && (response < p) )
                strcpy( response, p );

            p = strchr( response, '\r' );
            if ( !p )
                p = strchr( response, '\n' );
            if ( p )
                *p = NUL;
        }
    }
    else {
        strcpy( url, "http://tinyurl.com/create.php" );
        sprintf( request, "url=%s", encodeURL(targetURL) );
        setUpReceiveBuffer( response, sz );
     // http_post( url, "application/x-www-form-urlencoded",
     //            request, response );
        _http_post( url,  request, response, NULL );
        if ( *response ) {
            char    *p = strstr( response,
                                 "<input type=hidden name=tinyurl value=\"" );
            if ( p )
                p += 39;
            else {
                char *q = strstr( response, "<h1>TinyURL was created!</h1>" );
                if ( !q )
                    q = strstr( response, "<blockquote" );
                if ( q ) {
                    p = strstr( q, "[<a href=\"" );
                    if ( p )
                        p += 10;
                }
            }
            if ( p ) {
                char    *q = strchr( p, '"' );
                if ( q ) {
                    strncpy( response, p, q - p );
                    response[q - p] = NUL;
                }
            }
            else
                response[0] = NUL;
        }
    }

    return ( response[0] ? response : NULL );
}

char    *
CService::GetTinyURL( char *str )
{
    char    *p = str;
    char    *q;
    char    targetURL[MAX_URLLENGTH * 8];
    char    *request;
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE * 20;

    request  = new char[MAX_CONTENT_SIZE];
    if ( !request ) 
        return ( str );
    response = new char[sz];
    if ( !response ) {
        delete [] request;
        return ( str );
    }

    while ( *p ) {
        q = strstr( p, "http://" );
        if ( !q )
            q = strstr( p, "https://" );
        if ( !q )
            break;

        p = q;
        q = strstr( p, "://" ) + 3;
        if ( !strncmp( q, "tinyurl.com", 11 ) ) {
            p = q + 11;
            continue;
        }

        while ( *q ) {
            if ( ((unsigned char)(*q) <= ' ') ||
                 ((unsigned char)(*q) > 0x7F)    )
                break;
            q++;
        }
        strncpy( targetURL, p, q - p );
        targetURL[q - p] = NUL;
        if ( targetURL[0] ) {
            char    *r = GetTinyURL( targetURL, request, response, sz );
            if ( r && *r && (strlen(r) < (size_t)(q - p)) ) {
                strcpy( p, r );
                strcat( p, q );
                p += strlen(r);
            }
            else
                p = q;
        }
        else
            break;
    }

    delete [] response;
    delete [] request;

    return ( str );
}


// TWITTER_STATUS のソート (日時の昇順に並び替える)
int
compareLog( const void *elem1, const void *elem2 )
{
    TWITTER_LOG  *sp1 = (TWITTER_LOG *)elem1;
    TWITTER_LOG  *sp2 = (TWITTER_LOG *)elem2;

    int ret = (int)(sp1->createdAt - sp2->createdAt);
    if ( ret == 0 )
        ret = strcmp( sp1->orig_userName, sp2->orig_userName );

    return ( ret );
}

// ログをファイルに書き出す
void
CService::WriteLog( CTwitterTimeline *timeline )
{
    int     i;
    if ( m_log && (m_numOfLogs > 0) ) {
        qsort( (void *)(&m_log[0]), (size_t)m_numOfLogs,
               sizeof ( TWITTER_LOG ), compareLog );

        char    msg[MAX_DESCRIPTION_LEN];
        if ( timeline && timeline->m_logging ) {
            for ( i = 0; i < m_numOfLogs; i++ ) {
                sprintf( msg,
                         "%s: %s [%04d-%02d-%02d %02d:%02d:%02d]\r\n",
                         m_log[i].orig_userName,
                         m_log[i].orig_text,
                         m_log[i].createdAt_yyyy,
                         m_log[i].createdAt_mm,
                         m_log[i].createdAt_dd,
                         m_log[i].createdAt_HH,
                         m_log[i].createdAt_MM,
                         m_log[i].createdAt_SS );
                timeline->WriteLog( msg );
            }
        }
    }
}

