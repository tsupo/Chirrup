/*
 * twitStar.c : Twitter クライアント chirrup
 *      ついすた関連各種処理群
 *          written by H.Tsujimura  24 Aug 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/twitStar.c $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 5     08/12/04 18:19 Tsujimura543
 * コード整理、安定化作業を実施
 * 
 * 4     07/12/19 18:46 Tsujimura543
 * http関連の関数を __http_getBASIC(), __http_postBASIC() に移行
 * 
 * 3     07/09/27 18:35 Tsujimura543
 * 「もごすた」に対応した
 * 
 * 2     07/08/27 17:17 Tsujimura543
 * はてなスターに渡す title を「ついすた」 Greasemonkey の仕様にあわせた
 * 
 * 1     07/08/24 22:29 Tsujimura543
 * 最初の版
 */


#include <time.h>
#include "xmlRpc.h"
#include "twitStar.h"
#include "http.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/twitStar.c 1     09/05/14 3:50 tsupo $";
#endif


BOOL
loginHatenaStar(
    const char *username,   // (I) はてなID
    const char *password,   // (I) パスワード
    char       *cookie )    // (O) クッキー
{
    int     ret = FALSE;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 2;

    static char     saveUserName[MAX_USERIDLEN + 1];
    static char     savePassword[MAX_PASSWDLEN + 1];
    static char     saveCookie[MAX_COOKIE_LEN];
    static time_t   firstTime = 0;
    BOOL            refresh = FALSE;

    if ( !cookie || !username || !password )
         return ( ret );

    // キャッシュチェック
    if ( firstTime == 0 ) {
        firstTime = time( NULL );
        refresh   = TRUE;
    }
    else {
        time_t  now = time( NULL );
        if ( now - firstTime >= 1 * 60 * 60 )
            refresh = TRUE; /* キャッシュの有効時間を1時間とする */
        else if ( ( strcmp( username, saveUserName ) != 0 ) ||
                  ( strcmp( password, savePassword ) != 0 )    )
            refresh = TRUE;
    }

    if ( refresh == TRUE ) {
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
    }
    else {
        strcpy( cookie, saveCookie );
        ret = TRUE;     /* ログイン成功 */
        return ( ret );
    }

    // ログイン処理
    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) {
        firstTime = 0;
        return ( ret );
    }
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        firstTime = 0;
        return ( ret );
    }
    memset( request, 0x00, MAX_CONTENT_SIZE );

    strcpy( url,
            "https://www.hatena.ne.jp/login?"
            "location=http%3A%2F%2Fs.hatena.ne.jp%2F" );
    setUpReceiveBuffer( response, sz );
    __http_getBASIC( url, NULL, NULL, response, cookie );

    strcpy( url, "https://www.hatena.ne.jp/login" );
    setTargetURL( url );
    sprintf( request,
             "name=%s&"
             "password=%s&"
             "persistent=1&"
             "location=http://s.hatena.ne.jp/",
             username, password );
    setUpReceiveBuffer( response, sz );
    __http_postBASIC( url, NULL, NULL, request, response, cookie );
    if ( *response ) {
        if ( strstr( response, sjis2utf("ログイン中です") ) != NULL ) {
            setUpReceiveBuffer( response, sz );
            __http_getBASIC( "http://s.hatena.ne.jp/", NULL, NULL,
                             response, cookie );
            if ( *response ) {
                if ( strstr( response, sjis2utf(">ログアウト</a>") ) != NULL )
                    ret = TRUE;     /* ログイン成功 */
            }
        }
    }

    free( response );
    free( request  );

    // キャッシュを更新
    if ( ret == TRUE ) {
        /* キャッシュに保存 */
        strcpy( saveUserName, username );
        strcpy( savePassword, password );
        strcpy( saveCookie, cookie );
    }
    else {
        /* キャッシュを破棄 */
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
    }

    return ( ret );
}


char    *
any2utf( const char *p )
{
    char    *q;

    q = utf2sjis( p );
    if ( q )
        q = (char *)p;  // すでに UTF-8 変換済み
    else {
        // p の charset は UTF-8 ではない
        if ( strstr( p, "\033$@" ) || strstr( p, "\033$B" ) )
            q = jis2utf( p );
        else {
            q = euc2sjis( p );
            if ( q )
                q = euc2utf( p );
            if ( !q )
                q = sjis2utf( p );
            if ( !q && p ) {
                /* 以下、Vox 対策 */
                char    *r = (char *)malloc( strlen(p) * 12 + 1 );
                if ( r ) {
                    char    *s;

                    strcpy( r, p );
                    s = utf2sjisEx( r );    /* (主として) &ccedil; 対策 */
                    if ( s )
                        q = sjis2utf( s );
                    free( r );
                }
            }
            if ( !q )
                q = (char *)p;
        }
    }

    return ( q );
}

char    *
getTitleForTwitStar( const char *url )
{
    // この処理自体は、Twitter 以外の Webサイトに対しても、はてなスターに
    // 投票する(☆をつける)ことができるように配慮して書いておく
    static char title[MAX_CONTENT_SIZE];
    char        *response;
    char        *p, *q;
    size_t      sz;

    title[0] = NUL;
    sz       = MAX_CONTENT_SIZE;
    response = (char *)malloc( sz );
    if ( !response )
        return ( title );

    setUpReceiveBuffer( response, sz );
    __http_getBASIC( url, NULL, NULL, response, NULL );
    if ( *response ) {
        // title 要素を取得
        p = strstr( response, "<title>" );
        if ( !p )
            p = strstr( response, "<title " );
        if ( !p )
            p = strstr( response, "<TITLE>" );
        if ( !p )
            p = strstr( response, "<TITLE " );
        if ( !p )
            p = strstr( response, "<h1>" );
        if ( !p )
            p = strstr( response, "<h1 " );
        if ( !p )
            p = strstr( response, "<H1>" );
        if ( !p )
            p = strstr( response, "<H1 " );
        if ( p ) {
            p++;
            p = strchr( p, '>' );
            p++;
            q = strstr( p + 1, "</" );
            if ( q ) {
                strncpy( title, p, q - p );
                title[q - p] = NUL;

                while ( ( ( p = strchr( title, '\r' ) ) != NULL ) ||
                        ( ( p = strchr( title, '\n' ) ) != NULL )    )
                    strcpy( p, p + 1 );
            }
        }

        /* for Twitter */
        if ( !strncmp( title, "Twitter / ", 10 ) ) {
            p = title + 10;
            q = strchr( p, ':' );
            if ( q ) {
                q++;
                if ( !strcmp( q, " " ) ) {
                    // protected user
                    char    username[BUFSIZ];

                    q--;
                    strncpy( username, p, q - p );
                    username[q - p] = NUL;
                    sprintf( title,
                             "%s is only giving updates to friends.",
                             username );
                }
                else {
                    strcpy( title, q );

                    // 「ついすた」 Greasemonkey と仕様をあわせるため、
                    // Twitter の発言本文を取得する
                    // (http://d.hatena.ne.jp/os0x/20070823/1187832762 を参照)
                    p = strstr( response, "<div class=\"desc\">" );
                    if ( p ) {
                        p += 18;
                        q = strstr( p, "<p>" );
                        if ( q ) {
                            p = q + 3;
                            while ( (*p == ' ')  || (*p == '\t') ||
                                    (*p == '\r') || (*p == '\r')    )
                                p++;
                            q = strstr( p, "</p>" );
                            if ( q ) {
                                while ( (q > p)                  &&
                                        ((*(q - 1) == ' ')  ||
                                         (*(q - 1) == '\t') ||
                                         (*(q - 1) == '\r') ||
                                         (*(q - 1) == '\r')    )    )
                                    q--;
                            }
                            strncpy( title, p, q - p );
                            title[q - p] = NUL;
                            if ( strchr( title, '<' ) ) {
                                /* html タグの除去 */
                                const char  *r;

                                p = title;
                                while ( ( q = strchr( p, '<' ) ) != NULL ) {
                                    if ( (r = strchr(q + 1, '>')) != NULL )
                                        strcpy( q, r + 1 );
                                    else {
                                        *q = NUL;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        else {
            // for もごもご
            p = strstr( title, sjis2utf("｜ミニブログ「もごもご」") );
            if ( p )
                *p = NUL;
        }

        /* asahi.com 対策 #1 */
        while ( ( p = strstr( title, "&#160;" ) ) != NULL ) {
            *p++ = ' ';
            strcpy( p, p + 5 );
        }

        /* asahi.com 対策 #2 */
        if ( ( p = strstr( title, "\xEF\xBF\xBD-\xEF\xBF\xBD" ) ) != NULL ) {
            strcpy( p, " - " );
            strcpy( p + 3, p + 7 );
        }
    }

    free( response );

    // UTF-8 以外の文字コードの場合、UTF-8 に変換する
    if ( strstr( title, "\033$@" ) || strstr( title, "\033$B" ) ) {
        p = jis2sjis( title );
        if ( p )
            strcpy( title, p );
    }

    p = any2utf( title );
    if ( p )
        strcpy( title, p );

    // 余分なホワイトスペースを除去
    p = title;
    while ( *p ) {
        if ( (*p == '\t') || (*p == '\r') || (*p == '\n' ) )
            *p = ' ';
        p++;
    }

    p = title;
    while ( *p ) {
        while ( (*p == ' ') && (*(p + 1) == ' ') )
            strcpy( p, p + 1);
        p++;
    }

    p = title;
    while ( *p == ' ' )
        strcpy( p, p + 1);

    if ( *p ) {
        p = &(title[strlen(title) - 1]);
        while ( *p == ' ' )
            *p-- = NUL;
    }

    return ( title );
}

// targetURL で指定したWebページに ☆ をつける
BOOL
setHatenaStar( const char *targetURL,   // (I) ☆をつけたいWebページURL
               const char *username,    // (I) はてなID
               const char *password )   // (I) パスワード
{
    size_t  sz = MAX_CONTENT_SIZE;
    char    *request;
    char    *response;
    char    *url;
    char    cookie[MAX_COOKIE_LEN];
    BOOL    r;
    BOOL    ret = FALSE;

    memset( cookie, 0x00, MAX_COOKIE_LEN );
    request  = (char *)malloc( sz );
    if ( !request )
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    url = (char *)malloc( strlen( targetURL ) + MAX_CONTENT_SIZE );
    if ( !url ) {
        free( response );
        free( request );
        return ( ret );
    }

    // はてなスターにログイン
    r = loginHatenaStar( username, password, cookie );
    if ( r ) {
        time_t      t = time( NULL );
        struct tm   *tm = localtime( &t );
        char        timeStr[BUFSIZ];

        strftime( timeStr, BUFSIZ - 1,
                  "%a %b %d %H:%M:%S UTC+0900 %Y", tm );

        // rks を取得
        setUpReceiveBuffer( response, sz );
        sprintf( url,
                 "http://s.hatena.ne.jp/entries.json?"
                 "uri=%s&"
                 "callback=Ten.JSONP.callback&",
                 encodeURL( targetURL ) );
        sprintf( url + strlen(url),
                 "%s",
                 encodeURL( timeStr ) );
        __http_getBASIC( url, NULL, NULL, response, cookie );
        if ( *response ) {
            char        rks[BUFSIZ];
            char        title[BUFSIZ];
            const char  *p, *q;

            p = strstr( response, "\"rks\":\"" );
            if ( p ) {
                p += 7;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( rks, p, q - p );
                    rks[q - p] = NUL;
                }

                // ☆をつける
                t = time( NULL );
                tm = localtime( &t );
                strftime( timeStr, BUFSIZ - 1,
                          "%a %b %d %H:%M:%S UTC+0900 %Y", tm );

                strcpy( title, getTitleForTwitStar( targetURL ) );

                setUpReceiveBuffer( response, sz );
                sprintf( url,
                         "http://s.hatena.ne.jp/star.add.json?uri=%s&",
                         encodeURL( targetURL ) );
                sprintf( url + strlen(url),
                         "title=%s&"
                         "rks=%s&"
                         "callback=Ten.JSONP.callback&",
                         encodeURL( title ), rks );
                sprintf( url + strlen(url),
                         "%s",
                         encodeURL( timeStr ) );
                __http_getBASIC( url, NULL, NULL, response, cookie );
                if ( *response ) {
                    if ( strstr( response, username )      ||
                         strstr( response, "\"name\":\"" )    )
                        ret = TRUE;
                }
            }
        }
    }

    free( url );
    free( response );
    free( request );

    return ( ret );
}
