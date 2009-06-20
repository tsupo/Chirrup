/*
 * haruFM.cpp : Haru.fm クライアント chirrup
 *      Haru.fm API を利用するための各種処理群
 *          written by H.Tsujimura  27 Jun 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/haruFm.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 19    09/04/28 20:52 Tsujimura543
 * タイムアウト取得処理が規定時間内に終わらない場合の処理を変更
 * (スレッド強制終了方式ではなく、イベント通知方式を採用)
 * 
 * 18    09/03/10 22:14 Tsujimura543
 * GetStringFromJSON() にバッファオーバーラン対策を実施
 * 
 * 17    08/12/04 18:19 Tsujimura543
 * コード整理、安定化作業を実施
 * 
 * 16    08/09/03 19:21 Tsujimura543
 * delete [] response; するタイミングを修正
 * 
 * 15    08/07/14 13:33 Tsujimura543
 * バッファオーバーラン予防策を強化
 * 
 * 14    08/07/14 13:28 Tsujimura543
 * m_loginID が空文字列のまま、タイムラインを取得しに行こうとすることがあ
 * る不具合を修正
 * 
 * 13    07/12/19 18:44 Tsujimura543
 * http 関連関数呼び出しまわりを整理
 * 
 * 12    07/12/19 17:17 Tsujimura543
 * _http_postBASIC() の引数を追加
 * 
 * 11    07/12/14 16:01 Tsujimura543
 * http_get() → _http_get() に置換
 * 
 * 10    07/07/19 21:35 Tsujimura543
 * タイムスタンプ関連の処理を VC++ 6 / VC++ 2005 共通コードに変更
 * 
 * 9     07/07/10 23:08 Tsujimura543
 * 調査用の ASSERT() を入れる [for haru.fm]
 * 
 * 8     07/07/05 22:30 Tsujimura543
 * Haru.fm のコメントツリーの更新に対応
 * 
 * 7     07/07/05 2:27 Tsujimura543
 * GetTimeline() のコンパイル時 warning 4100 を抑制
 * 
 * 6     07/07/05 0:49 Tsujimura543
 * (1) GetStatFromJSON(), GetUserTimeline() の引数を変更
 * (2) TWITTER_USER 構造体の変更(orig_userNameを追加)に伴う修正
 * 
 * 5     07/07/04 18:01 Tsujimura543
 * MakeMessageForScreen() と MakeMessageForLogging() を用意
 * 
 * 4     07/07/04 16:51 Tsujimura543
 * haru.fm のログを(日付をファイル名に付加指定で)出力すると、ログの
 * ファイル名の切り替わるタイミングが16時間ずれる不具合に対処
 * (haru.fm の regDate をそのまま getDateTimeFromDateString() に渡
 *  していたのが原因)
 * 
 * 3     07/07/03 17:45 Tsujimura543
 * タグの表示に対応
 * 
 * 2     07/07/03 14:53 Tsujimura543
 * haru.fm 対応 (動作確認済み)
 * 
 * 1     07/06/27 18:13 Tsujimura543
 * 新規作成 (暫定版)
 */

#include "chirrup.h"
#include "haruFm.h"
#include "twitterTimeline.h"
#include "http.h"
extern "C" {
#include "utility.h"
}

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/haruFm.cpp 1     09/05/14 3:50 tsupo $";
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

CHaruFm::CHaruFm() : CService()
{
#ifdef  _DEBUG
    m_serviceName   = _T("harufm");
#endif
    m_serviceSymbol = _T("HaruFm");
    m_loginID       = _T("");
}

CHaruFm::~CHaruFm()
{
    if ( m_log ) {
        delete [] m_log;
        m_log = NULL;
    }

    int i;
    if ( m_stat ) {
        for ( i = m_numOfStats; i > 0; i-- ) {
            DeleteReserved( &(m_stat[i - 1]) );
            DeleteReserved2( &(m_stat[i - 1]) );
        }
        delete [] m_stat;
        m_stat = NULL;
    }
    if ( m_stat2 ) {
        for ( i = m_numOfStats2; i > 0; i-- ) {
            DeleteReserved( &(m_stat2[i - 1]) );
            DeleteReserved2( &(m_stat2[i - 1]) );
        }
        delete [] m_stat2;
        m_stat2 = NULL;
    }
    if ( m_stat3 ) {
        for ( i = m_numOfStats3; i > 0; i-- ) {
            DeleteReserved( &(m_stat3[i - 1]) );
            DeleteReserved2( &(m_stat3[i - 1]) );
        }
        delete [] m_stat3;
        m_stat3 = NULL;
    }
}

void CHaruFm::DeleteReserved(TWITTER_STATUS *sp)
{
    if ( sp && sp->reserved ) {
        HARUFM_COMMENT_LIST *p = (HARUFM_COMMENT_LIST *)(sp->reserved);
        if ( p->comment )
            delete [] p->comment;
        delete p;
        sp->reserved = NULL;
    }
}

void CHaruFm::DeleteReserved2(TWITTER_STATUS *sp)
{
    if ( sp && sp->reserved2 ) {
        HARUFM_TAG_LIST *p = (HARUFM_TAG_LIST *)(sp->reserved2);
        if ( p->tag )
            delete [] p->tag;
        delete p;
        sp->reserved2 = NULL;
    }
}

/*
 *  Haru.fm API
 */

// 発言を投稿
bool
CHaruFm::PostUpdate( CString monologue, ProceedingDialog *pdlg )
{
    bool        ret = false;
    size_t      sz  = MAX_CONTENT_SIZE;
    size_t      len = monologue.GetLength() * 18;
    char        *request  = new char[37 + len + 1];
    char        *response = new char[sz];
    const char  *url = "http://haru.fm/api";
    char        *p = sjis2utf( monologue );

    if ( request && response ) {
        sprintf( request,
                 "command=write&"
                 "twitter_post=0&"
                 "content=%s",
                 encodeURL( p ? p : monologue ) );
        SetUserAgent();
        setUpReceiveBuffer( response, sz );
        _http_postBASIC( url, m_username, m_password,
                         request, response, NULL, pdlg );
        if ( *response ) {
            if ( strstr( response, "API_WRITE_SUCCESS" ) )
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
CHaruFm::GetFriendsTimeline(
                CTwitterTimeline *timeline,
                ProceedingDialog *pdlg
            )
{
    if ( m_loginID.GetLength() == 0 )
        m_loginID = GetLoginID();

    CString url = "";
    if ( m_loginID.GetLength() > 0 ) {
        url = _T("http://haru.fm/api?command=userNfriend&userid=");
        url += m_loginID;
        url += _T("&format=json");
    }

    return ( CService::GetFriendsTimeline( url, timeline, pdlg ) );
}

// public_timeline を取得
CString
CHaruFm::GetPublicTimeline(
                CTwitterTimeline *timeline,
                ProceedingDialog *pdlg
            )
{
    return ( CService::GetPublicTimeline(
                 "http://haru.fm/api?format=json",
                 timeline,
                 pdlg ) );
}

// user_timeline を取得
CString
CHaruFm::GetUserTimeline(
                CTwitterTimeline *timeline,
                ProceedingDialog *pdlg
            )
{
    if ( m_loginID.GetLength() == 0 )
        m_loginID = GetLoginID();

    CString url = "";
    if ( m_loginID.GetLength() > 0 ) {
        url = _T("http://haru.fm/api?command=userpost&userid=");
        url += m_loginID;
        url += _T("&format=json");
    }

    return ( CService::GetUserTimeline( url, timeline, pdlg ) );
}

// 自分のスクリーン名の取得
CString CHaruFm::GetScreenName()
{
    if ( m_loginID.GetLength() == 0 ) {
        m_loginID = GetLoginID();
        if ( m_loginID.GetLength() == 0 )
            return ( m_username );
    }

    TWITTER_USER    user;
    CString         screenName = _T("");
    size_t          sz  = MAX_CONTENT_SIZE;
    char            *response = new char[sz];
 // bool            ret = false;

    if ( response ) {
        CString url = _T("http://haru.fm/api?command=userpost&userid=");
        url += m_loginID;

        SetUserAgent();
        setUpReceiveBuffer( response, sz );
        _http_get( url, response, NULL );
        if ( *response ) {
            char    *p = strstr( response, "<user>" );
            if ( p ) {
             // ret  = true;
                user = GetUserFromXML(response, response + strlen(response));
                screenName = user.screenName;
            }
        }

        delete [] response;
    }

    return ( screenName.GetLength() > 0 ? screenName : m_username );
}

// 自分の ID の取得
CString CHaruFm::GetLoginID()
{
    TWITTER_USER    user;
    CString         loginID = _T("");
    size_t          sz  = MAX_CONTENT_SIZE;
    char            *response = new char[sz];
 // bool            ret = false;

    if ( response ) {
        CString url = _T("http://haru.fm/api?command=userno&loginid=");
        url += m_username;

        SetUserAgent();
        setUpReceiveBuffer( response, sz );
        _http_get( url, response, NULL );
        if ( *response ) {
            char    *p = strstr( response, "<user>" );
            if ( p ) {
             // ret  = true;
                user = GetUserFromXML(response, response + strlen(response));
                loginID = user.id;
            }
        }

        delete [] response;
    }

    return ( loginID );
}


#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
CString
CHaruFm::GetTimeline(
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
    if ( !endPointURL || (*endPointURL == NUL) )
        return ( messages );

    size_t  sz = MAX_CONTENT_SIZE * 16;
    char    *response = new char[sz];
    if ( response ) {
        CString url = endPointURL;

        SetUserAgent();
        setUpReceiveBuffer( response, sz );
     // if ( t != PUBLIC_TIMELINE )
     //     _http_getBASIC( url, m_username, m_password, response, pdlg );
     // else
            _http_get( url, response, pdlg );
        if ( response[0] ) {
            GetStatFromJSON( response, stat, numOfStats );
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
                                    "CHaruFm::GetTimeline()",
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
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif

CString CHaruFm::GetStatusID(
                        const char *p,
                        const char *terminator
                    )
{
    CString s = GetIdFromJSON( p, terminator );
    return ( s );
}

void CHaruFm::SetStatFromJSON(
                        const char       *q,
                        const char       *s,
                        TWITTER_STATUS   *sp,
                        CString          &message
                    )
{
    long    preCommentCount = 0;
    HARUFM_COMMENT_LIST *lp = (HARUFM_COMMENT_LIST *)(sp->reserved);

    preCommentCount = lp ? lp->preCommentCount : -1;
    if ( preCommentCount >= 0 ) {
        DeleteReserved( sp );
        DeleteReserved2( sp );
    }

    // id, content, regDate
    sp->createdAt = GetCreatedAtFromJSON(q, s);
    strcpy( sp->id, GetIdFromJSON(q, s) );
    strcpy( sp->text,
            GetContentFromJSON( q, s, sp->orig_text ) );

    // user - id, displayName
    sp->user = GetUserFromJSON( q, s );

    // tags
    const char  *p = strstr( q, "\"tags\":[" );
    if ( p && (p < s) ) {
        p += 8;
        const char  *t = strstr( p, "]," );
        if ( t && (t < s) )
            sp->reserved2 = GetTagsFromJSON( p, t );
    }

    // comments
    char    temp[BUFSIZ];
    long    commentCount = 0;
    GetStringFromJSON( temp, BUFSIZ, "commentCount", q, s );
    if ( temp[0] )
        commentCount = atol( temp );
    if ( commentCount > 0 ) {
        const char  *p = strstr( q, "\"comments\":[" );
        if ( p && (p < s) ) {
            p += 12;
            const char  *t = strstr( p, "]," );
            if ( t && (t < s) )
                sp->reserved = GetCommentsFromJSON(
                                        p, t, commentCount, preCommentCount );
        }
    }

    strcpy( sp->user.lastStatus, sp->text );

    MakeMessageForScreen( message, sp );
    MakeMessageForLogging( sp );
}

bool
CHaruFm::OverwriteStatFromJSON(
                        const char     *q,
                        const char     *s,
                        TWITTER_STATUS *sp,
                        CString        &message )
{
    bool    ovewritten = false;
    char    temp[BUFSIZ];
    long    commentCount    = 0;
    long    preCommentCount = 0;

    HARUFM_COMMENT_LIST *lp;

    lp = (HARUFM_COMMENT_LIST *)(sp->reserved);
    preCommentCount = lp ? lp->commentCount : 0;

    GetStringFromJSON( temp, BUFSIZ, "commentCount", q, s );
    if ( temp[0] )
        commentCount = atol( temp );

    if ( commentCount > preCommentCount ) {
        if ( !lp ) {
            lp = new HARUFM_COMMENT_LIST;
            sp->reserved = lp;
        }
        lp->preCommentCount = preCommentCount;
        SetStatFromJSON( q, s, sp, message );
        ovewritten = true;
    }

    return ( ovewritten );
}

TWITTER_USER
CHaruFm::GetUserFromJSON(
                const char *q,
                const char *terminator
            )
{
    TWITTER_USER    u;
    char            temp[BUFSIZ];
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
            if ( *p ) {
                //    "description"
                u.description[0] = NUL;

                //    "location"
                u.location[0] = NUL;

                //    "id"
                id = GetIntegerFromJSON( "\"id\"", p, terminator );
                sprintf( u.id, "%d", id );

                //    "displayName"
                GetStringFromJSON( temp, MAX_KEYLENGTH, "\"displayName\"", p,
                                   terminator, false, temp2 );
                strcpy( u.screenName, temp );
                strcpy( u.name, temp );
                strcpy( u.orig_userName, temp2 );

                //    "profile_image_url"
                sprintf( u.profileImageURL,
                         "http://haru.fm/userimages/%s/large?%s",
                         u.id, u.id );

                //    "url"
                sprintf( u.url, "http://haru.fm/mypost/%s", u.id );
            }
        }
    }

    u.lastStatus[0] = NUL;
    u.bitmap        = NUL;

    return ( u );
}

char            *
CHaruFm::GetContentFromJSON(
                const char *q,
                const char *terminator,
                char       *origString /* = NULL */
            )
{
    Thread static char  temp[BUFSIZ * 16];

    // "content"
    GetStringFromJSON( temp, BUFSIZ * 16, "\"content\"", q,
                       terminator, false, origString );

    // tinyurl を元の URL に展開
    ExpandTinyURL( temp );
    if ( origString && origString[0] ) {
        ExpandTinyURL( origString );
        if ( strchr( origString, '&' ) )
            strcpy( origString, decodeString( origString ) );
    }

    return ( strchr( temp, '&' ) ? decodeString( temp ) : temp );
}

CTime
CHaruFm::GetCreatedAtFromJSON( const char *q, const char *terminator )
{
    CTime   t;
    bool    done = false;
    char    temp[MAX_DATELENGTH];

    // "date"
    GetStringFromJSON( temp, MAX_DATELENGTH, "\"regDate\"", q, terminator );
    if ( temp[0] ) {
        char    *p = strstr( temp, " (GMT+09:00)" );
        if ( p )
            strcpy( p, "+09:00" );

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


HARUFM_COMMENT_LIST *
CHaruFm::GetCommentsFromJSON(
                const char *p,
                const char *terminator,
                long       commentCount,
                long       preCommentCount
            )
{
    HARUFM_COMMENT_LIST *lp = new HARUFM_COMMENT_LIST;
    lp->preCommentCount = preCommentCount;
    lp->commentCount    = commentCount;
    lp->comment         = new HARUFM_COMMENT[commentCount];

    HARUFM_COMMENT  *cp = lp->comment;
    const char      *q  = p;
    char            *r;
    long            count = 0;

    while ( q < terminator ) {
        while ( (q < terminator) && (*q != '{') )
            q++;
        if ( !(*q) )
            break;

        // id
        strcpy( cp[count].id, GetIdFromJSON( q, terminator ) );

        // content
        r = GetContentFromJSON( q, terminator, cp[count].orig_text );
        strcpy( cp[count].text, r );

        // regDate
        cp[count].createdAt = GetCreatedAtFromJSON( q, terminator );

        // user - id, displayName
        TWITTER_USER    u = GetUserFromJSON( q, terminator );
        strcpy( cp[count].userID, u.id );
        strcpy( cp[count].userName, u.screenName );
        strcpy( cp[count].orig_userName, u.orig_userName );

        while ( (q < terminator) && (*++q != '}') )
            ;

        if ( ++count >= commentCount )
            break;
    }

    return ( lp );
}

HARUFM_TAG_LIST     *
CHaruFm::GetTagsFromJSON(
                const char *p,
                const char *terminator
            )
{
    HARUFM_TAG_LIST *lp = NULL;
    long            numOfCount = 0;
    const char      *q = p;
    const char      *r;

    while ( *q && (q < terminator) ) {
        if ( !strncmp( q, "{\"id\":\"", 7 ) ) {
            numOfCount++;
            q += 7;
            r = strchr( q, '}' );
            if ( r )
                q = r + 1;
        }

        q++;
    }

    if ( numOfCount > 0 ) {
        lp = new HARUFM_TAG_LIST;
        lp->numOfTags = numOfCount;
        lp->tag       = new HARUFM_TAGS[numOfCount];

        long    cnt = 0;
        q = p;
        while ( *q && (q < terminator) ) {
            r = strchr( q, '}' );
            if ( !r || (r > terminator) )
                break;

            strcpy( lp->tag[cnt].id, GetIdFromJSON( q, r ) );
            GetStringFromJSON( lp->tag[cnt].tag, MAX_KEYLENGTH, "\"name\"",
                               q, r, false, lp->tag[cnt].orig_tag );
            cnt++;
            if ( cnt >= numOfCount )
                break;
            q = r + 1;
        }
    }

    return ( lp );
}


TWITTER_USER
CHaruFm::GetUserFromXML( const char *p, const char *terminator )
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

        // loginId
        str = GetStringFromXML( q, "loginId", term );
        strcpy( u.name, str );

        // displayName
        str = GetStringFromXML( q, "displayName", term );
        strcpy( u.screenName, str );

        if ( u.screenName[0] ) {
            if ( u.name[0] == NUL )
                strcpy( u.name, u.screenName );
        }
        else {
            if ( u.name[0] )
                strcpy( u.screenName, u.name );
        }

        // location
        u.location[0] = NUL;

        // description
        u.description[0] = NUL;

        // profile_image_url
        sprintf( u.profileImageURL,
                 "http://haru.fm/userimages/%s/large?%s",
                 u.id, u.id );

        // url
        sprintf( u.url, "http://haru.fm/mypost/%s", u.id );

        // status - text
        u.lastStatus[0] = NUL;
    }

    return ( u );
}


void
CHaruFm::MakeMessageForScreen( CString &message, TWITTER_STATUS *sp )
{
    message += EscapeQuote(sp->user.screenName);
    message += _T(": ");
    message += EscapeQuote(sp->text);

    if ( sp->reserved2 ) {
        HARUFM_TAG_LIST *lp = (HARUFM_TAG_LIST *)(sp->reserved2);
        long            cnt = lp->numOfTags;
        HARUFM_TAGS     *tp = lp->tag;

        message += _T(" [tag:");

        int i;
        for ( i = 0; i < cnt; i++ ) {
            message += tp[i].tag;
            if ( i < cnt - 1 )
                message += _T(",");
        }

        message += _T("]");
    }

    message += _T(" [ID: ");
    message += sp->id;
    message += _T("]\r\n");
    ASSERT( strcmp( sp->id, "0" ) != 0 );

    if ( sp->reserved ) {
        HARUFM_COMMENT_LIST *lp;
        HARUFM_COMMENT      *cp;
        long                commentCount;

        lp = (HARUFM_COMMENT_LIST *)(sp->reserved);
        commentCount = lp ? lp->commentCount : 0;
        cp           = lp ? lp->comment      : NULL;

        int i;
        for ( i = 0; i < commentCount; i++ ) {
            message += _T("    → ");
            message += EscapeQuote(cp[i].userName);
            message += _T(": ");
            message += EscapeQuote(cp[i].text);

            message += _T(" [ID: ");
            message += sp->id;
            message += _T("-");
            message += cp[i].id;
            message += _T("]\r\n");
        }
    }
}

void
CHaruFm::MakeMessageForLogging( TWITTER_STATUS *sp )
{
    HARUFM_COMMENT_LIST *lp;
    long    preCommentCount;
    lp = (HARUFM_COMMENT_LIST *)(sp->reserved);
    preCommentCount = lp ? lp->preCommentCount : 0;

    if ( !m_log )
        m_log = new TWITTER_LOG[MAX_NUMOFSTATUS + 1];

    if ( m_log && (m_numOfLogs < MAX_NUMOFSTATUS) ) {
        if ( preCommentCount == -1 ) {
            preCommentCount = 0;
            sprintf( m_log[m_numOfLogs].orig_text,
                     "%s",
                     sp->orig_text );

            if ( sp->reserved2 ) {
                HARUFM_TAG_LIST *lp = (HARUFM_TAG_LIST *)(sp->reserved2);
                long            cnt = lp->numOfTags;
                HARUFM_TAGS     *tp = lp->tag;

                strcat( m_log[m_numOfLogs].orig_text, " [tag:" );

                int i;
                for ( i = 0; i < cnt; i++ ) {
                    strcat( m_log[m_numOfLogs].orig_text, tp[i].orig_tag );
                    if ( i < cnt - 1 )
                        strcat( m_log[m_numOfLogs].orig_text, "," );
                }

                strcat( m_log[m_numOfLogs].orig_text, "]");
            }

            sprintf( m_log[m_numOfLogs].orig_text +
                            strlen(m_log[m_numOfLogs].orig_text),
                     " [ID: %s]",
                     sp->id );

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

        if ( sp->reserved ) {
            HARUFM_COMMENT_LIST *lp;
            HARUFM_COMMENT      *cp;
            long                commentCount;

            lp = (HARUFM_COMMENT_LIST *)(sp->reserved);
            commentCount = lp->commentCount;
            cp           = lp->comment;
            lp->preCommentCount = -1;

            int i;
            for ( i = preCommentCount; i < commentCount; i++ ) {
                if ( m_numOfLogs >= MAX_NUMOFSTATUS )
                    break;
                sprintf( m_log[m_numOfLogs].orig_text,
                         "%s [ID: %s-%s]",
                         cp[i].orig_text, sp->id, cp[i].id );
                sprintf( m_log[m_numOfLogs].orig_userName,
                         "\t%s %s",
                         sjis2utf("→"),
                         cp[i].orig_userName );

                m_log[m_numOfLogs].createdAt = cp[i].createdAt.GetTime();

                struct tm   ttmm;
             // struct tm   *tm = cp[i].createdAt.GetGmtTm( &ttmm );
                struct tm   *tm = cp[i].createdAt.GetLocalTm( &ttmm );

                m_log[m_numOfLogs].createdAt_yyyy = tm->tm_year + 1900;
                m_log[m_numOfLogs].createdAt_mm   = tm->tm_mon + 1;
                m_log[m_numOfLogs].createdAt_dd   = tm->tm_mday;
                m_log[m_numOfLogs].createdAt_HH   = tm->tm_hour;
                m_log[m_numOfLogs].createdAt_MM   = tm->tm_min;
                m_log[m_numOfLogs].createdAt_SS   = tm->tm_sec;

                m_numOfLogs++;
            }
        }
    }
}
