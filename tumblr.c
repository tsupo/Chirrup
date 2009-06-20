/*
 * tumblr.c : Twitter クライアント chirrup
 *      tumblr 関連各種処理群
 *          written by H.Tsujimura  5 Nov 2007
 *
 *      Copyright (c) 2007, 2008, 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/tumblr.c $
 * 
 * 3     09/05/31 20:42 tsupo
 * 1.142版
 * 
 * 16    09/05/29 19:22 Tsujimura543
 * 同一アカウントで複数 tumbleblog を開設している場合の投稿先
 * tumbleblog を指定しての投稿を可能にした
 * 
 * 2     09/05/27 1:29 tsupo
 * xmlRPC 1.266版対応
 * 
 * 15    09/05/26 18:08 Tsujimura543
 * URL ハードコーディング箇所を減らした
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 14    08/02/14 22:48 Tsujimura543
 * 「≪ が &Lt; に化けたり、≫ が &Gt; に化けたりする件の対策」を実施
 * 
 * 13    08/02/13 0:10 Tsujimura543
 * tumblr への Quote 投稿時にコメントもいっしょに投稿できるようにした
 * 
 * 12    07/12/19 18:47 Tsujimura543
 * loginTumblr() を __http_postBASIC() を使う版に移行
 * 
 * 11    07/12/14 14:49 Tsujimura543
 * checkResultOnTumblr() を修正、photo のアップロード数上限到達時の警告
 * にも対応した
 * 
 * 10    07/12/13 19:08 Tsujimura543
 * Gyazo関連の関数群を gyazo.c として分離独立させた
 * 
 * 9     07/12/10 23:04 Tsujimura543
 * postPhotoWithUrlOnTumblr() の caption 省略時の動作を変更
 * 
 * 8     07/12/10 21:21 Tsujimura543
 * postPhotoWithUrlOnTumblr() を追加
 * 
 * 7     07/12/10 18:10 Tsujimura543
 * tumblr への投稿関連処理も fix
 * 
 * 6     07/12/10 16:39 Tsujimura543
 * Gyazo への投稿処理関連を fix
 * 
 * 5     07/12/06 19:50 Tsujimura543
 * Gyazo に画像をアップロードする機能を実装
 * (いずれは別ファイルとして分離する)
 * 
 * 4     07/12/06 1:29 Tsujimura543
 * postPhotoOnTumblr() を追加
 * 
 * 3     07/11/12 19:04 Tsujimura543
 * 投稿失敗時にエラーメッセージを表示可能な場合は、表示するようにした
 * 
 * 2     07/11/07 3:39 Tsujimura543
 * 見ている発言を 引用して Tumblr へ投稿する機能を作成
 * 
 * 1     07/11/05 23:56 Tsujimura543
 * 最初の版
 */


#include <time.h>
#include "xmlRpc.h"
#include "multipart.h"
#include "utility.h"
#include "tumblr.h"
#include "http.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/tumblr.c 3     09/05/31 20:42 tsupo $";
#endif


BOOL
checkResultOnTumblr( const char *response )
{
    int ret = FALSE;

    long    postID = atol( response );
    if ( postID > 0 )
        ret = TRUE; // 投稿成功
    else {
        char    errorString[BUFSIZ];
        char    *p;

        errorString[0] = NUL;
        p = strstr( response, "Tumblr is undergoing maintenance" );
        if ( p )
            strcpy( errorString, "現在、Tumblr はメンテナンス中です" );
        else {
            p = strstr( response,
                        "You've exceeded your daily post limit." );
            if ( !p )
                p = strstr( response,
                            "You've exceeded your daily photo upload limit.");
            if ( p )
                strcpy( errorString,
                        "すでに1日分の投稿回数上限まで投稿しています" );
        }

        if ( errorString[0] ) {
            strcat( errorString, "      " );
            MessageBox( NULL, errorString, "tumblr 投稿失敗",
                        MB_OK|MB_ICONERROR );
        }
    }

    return ( ret );
}

BOOL
postTumblr(
    const char *targetURL,  // (I) tumblr に投稿する記事の URL
    const char *quote,      // (I) tumblr に投稿する記事の「内容」
    const char *title,      // (I) tumblr に投稿する記事の「題名」
    const char *comment,    // (I) tumblr に投稿する記事の「コメント」
    const char *username,   // (I) tumblr に login するときのメールアドレス
    const char *password,   // (I) パスワード
    const char *group )     // (I) 投稿先 tumbleblog ID またはグループ名
{
    BOOL    ret = FALSE;
    char    *request;
    char    *response;
    char    *source;
    char    *p;
    size_t  sz = MAX_CONTENT_SIZE;
    char    *targetTitle;
    char    *targetQuote;
    char    *targetComment = NULL;

    targetTitle = (char *)malloc( strlen(title) * 6 + 1 );
    if ( !targetTitle )
        return ( ret );
    targetQuote = (char *)malloc( strlen(quote) * 6 + 1 );
    if ( !targetQuote ) {
        free( targetTitle );
        return ( ret );
    }

    if ( comment && *comment ) {
        targetComment = (char *)malloc( strlen(comment) * 6 + 1 );
        if ( !targetComment ) {
            free( targetQuote );
            free( targetTitle );
            return ( ret );
        }
    }

    source  = (char *)malloc( sz );
    if ( !source ) {
        if ( targetComment )
            free( targetComment );
        free( targetQuote );
        free( targetTitle );
        return ( ret );
    }
    request  = (char *)malloc( sz );
    if ( !request ) {
        free( source );
        if ( targetComment )
            free( targetComment );
        free( targetQuote );
        free( targetTitle );
        return ( ret );
    }
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        free( source );
        if ( targetComment )
            free( targetComment );
        free( targetQuote );
        free( targetTitle );
        return ( ret );
    }
    memset( request, 0x00, MAX_CONTENT_SIZE );

    p = any2utf( title );
    strcpy( targetTitle, p ? p : title );
    /* ≪ が &Lt; に化けたり、≫ が &Gt; に化けたりする件の対策 */
    if ( strstr( targetTitle, "\342\211\253" ) )    // &raquo;
        replaceString( targetTitle, "\342\211\253", "\302\273" );
    if ( strstr( targetTitle, "\342\211\252" ) )    // &laquo;
        replaceString( targetTitle, "\342\211\252", "\302\253" );
    if ( strchr( targetTitle, '<' ) )
        replaceStringEx( targetTitle );

    p = any2utf( quote );
    strcpy( targetQuote, p ? p : quote );
    /* ≪ が &Lt; に化けたり、≫ が &Gt; に化けたりする件の対策 */
    if ( strstr( targetQuote, "\342\211\253" ) )    // &raquo;
        replaceString( targetQuote, "\342\211\253", "\302\273" );
    if ( strstr( targetQuote, "\342\211\252" ) )    // &laquo;
        replaceString( targetQuote, "\342\211\252", "\302\253" );
    if ( strchr( targetQuote, '<' ) )
        replaceStringEx( targetQuote );

    if ( targetComment ) {
        p = any2utf( comment );
        strcpy( targetComment, p ? p : comment );
        /* ≪ が &Lt; に化けたり、≫ が &Gt; に化けたりする件の対策 */
        if ( strstr( targetComment, "\342\211\253" ) )    // &raquo;
            replaceString( targetComment, "\342\211\253", "\302\273" );
        if ( strstr( targetComment, "\342\211\252" ) )    // &laquo;
            replaceString( targetComment, "\342\211\252", "\302\253" );
        if ( strchr( targetComment, '<' ) )
            replaceStringEx( targetComment );
    }

    sprintf( source,
             "<a href=\"%s\">%s</a>",
             targetURL,
             targetTitle );
    if ( targetComment )
        sprintf( source + strlen(source),
                 "\r\n%s",
                 targetComment );

    sprintf( request,
             "email=%s&"
             "password=%s&"
             "type=quote&"
             "quote=%s&",
             username,
             password,
             encodeURL( targetQuote ) );
    sprintf( request + strlen(request),
             "source=%s&",
             encodeURL( source ) );
    if ( group && *group )
        sprintf( request + strlen(request),
                 "group=%s&",
                 group );
    sprintf( request + strlen(request),
             "generator=%s",
             "Chirrup" );

    setUpReceiveBuffer( response, sz );
    http_post( APIURL_TUMBLR_WRITE,
               "application/x-www-form-urlencoded",
               request, response );

    if ( *response )
        ret = checkResultOnTumblr( response );

    free( response );
    free( request  );
    free( source );
    if ( targetComment )
        free( targetComment );
    free( targetQuote );
    free( targetTitle );

    return ( ret );
}


BOOL
postPhotoOnTumblr(
    const char *filename,   // (I) tumblr に投稿する画像のファイル名
    size_t     filesize,    // (I) tumblr に投稿する画像のファイルサイズ
    const char *caption,    // (I) tumblr に投稿する画像の「説明」
    const char *username,   // (I) tumblr に login するときのメールアドレス
    const char *password,   // (I) パスワード
    const char *group,      // (I)   投稿先 tumbleblog ID またはグループ名
    char       *url )       // (O) アップロード先URL
{
    BOOL    ret = FALSE;
    char    *request;
    char    *response;
    char    *imageData;
    char    *p;
    char    *base;
    char    *tail;
    size_t  sz1 = filesize * 6 + BUFSIZ;
    size_t  sz2 = MAX_CONTENT_SIZE;
    size_t  szz = 0;
    char    *targetCaption;
    FILE    *fp;
    char    contentType[MAX_LOGICALLINELEN];
    char    *separator = getMultiPartID();
    FILEINF fInfo;

    imageData = (char *)malloc( filesize + 1 );
    if ( !imageData ) {
        return ( ret );
    }

    fp = fopen( filename, "rb" );
    if ( !fp ) {
        free( imageData );
        return ( ret );
    }
    fread( imageData, filesize, 1, fp );
    fclose( fp );

    if ( !caption || !(*caption) )
        caption = " ";
    targetCaption = (char *)malloc( strlen(caption) * 6 + 1 );
    if ( !targetCaption ) {
        free( imageData );
        return ( ret );
    }

    request  = (char *)malloc( sz1 );
    if ( !request ) {
        free( targetCaption );
        free( imageData );
        return ( ret );
    }
    response = (char *)malloc( sz2 );
    if ( !response ) {
        free( request );
        free( targetCaption );
        free( imageData );
        return ( ret );
    }
    memset( request, 0x00, sz1 );

    p = any2utf( caption );
    strcpy( targetCaption, p ? p : caption );
    /* ≪ が &Lt; に化けたり、≫ が &Gt; に化けたりする件の対策 */
    if ( strstr( targetCaption, "\342\211\253" ) )    // &raquo;
        replaceString( targetCaption, "\342\211\253", "\302\273" );
    if ( strstr( targetCaption, "\342\211\252" ) )    // &laquo;
        replaceString( targetCaption, "\342\211\252", "\302\253" );
    if ( strchr( targetCaption, '<' ) )
        replaceStringEx( targetCaption );

    // アップロードするファイルの情報をセット
    strcpy( fInfo.type, "application/unknown" );    /* 暫定 */
    strcpy( fInfo.name, filename );

    p = base64( (unsigned char*)imageData, filesize );
    if ( !p ) {
        base64( NULL, 0 );
        free( response );
        free( request );
        free( targetCaption );
        free( imageData );
        return ( ret );
    }
    fInfo.bits = (unsigned char *)p;

    // multipart/form-data の組み立て
    getSendBufferPointer( request, base );
    tail = base;

    sprintf( contentType, "multipart/form-data; boundary=%s", separator );

    strcpy( tail, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "email", 0, username, NULL ) );
    strcat( tail, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "password", 0, password, NULL ) );
    strcat( tail, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "type", 0, "photo", NULL ) );

    szz  =  strlen( tail );
    tail += szz;
    szz  =  0;
    p    =  makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_FILE,
                               "data", 0, (char *)&fInfo, &szz );
    memcpy( tail, p, szz );
    tail += szz;

    strcat( tail,
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "caption", 0, targetCaption, NULL ) );
    if ( group && *group )
        strcat( tail,
                makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                                   "group", 0, group, NULL ) );
    strcat( tail, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "generator", 0, "Chirrup", NULL ) );
    sprintf( tail + strlen( tail ), "--%s--\r\n", separator );
    szz  =  strlen( tail );
    tail += szz;

    makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_BUFFERFREE,
                       NULL, 0, NULL, NULL );

    // リクエスト発行
    setTimeoutTime( DEFAULT_HTTP_TIMEOUT * (1 + (filesize / (1024 * 1024))) );
                                    // サイズに比例したタイムアウト時間を設定
    szz = tail - base;
    setUpSendBuffer( request, szz, base );
    setUpReceiveBuffer( response, sz2 );
    http_post( APIURL_TUMBLR_WRITE,
               contentType,
               request, response );

    if ( *response ) {
        ret = checkResultOnTumblr( response );
        if ( ret && url && group && *group ) {
            if ( strchr( group, '.' ) )
                    sprintf( url, "http://%s/post/%s",
                             group, response );
        }
    }

    base64( NULL, 0 );
    free( response );
    free( request  );
    free( targetCaption );
    free( imageData );

    return ( ret );
}

BOOL
postPhotoWithUrlOnTumblr(
    const char *photoURL,   // (I) tumblr に投稿する画像のURL
    const char *caption,    // (I) tumblr に投稿する画像の「説明」
    const char *username,   // (I) tumblr に login するときのメールアドレス
    const char *password,   // (I) パスワード
    const char *group,      // (I)   投稿先 tumbleblog ID またはグループ名
    char       *url )       // (O) アップロード先URL
{
    BOOL    ret = FALSE;
    char    *p;
    char    *targetCaption;
    char    *request;
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;
    char    tempCaption[MAX_DESCRIPTION_LEN];

    tempCaption[0] = NUL;
    if ( !caption || !(*caption) ) {
        sprintf( tempCaption, "via <a href=\"%s\">%s</a>", photoURL, photoURL );
        caption = tempCaption;
    }
    targetCaption = (char *)malloc( strlen(caption) * 6 + 1 );
    if ( !targetCaption )
        return ( ret );

    request  = (char *)malloc( sz );
    if ( !request ) {
        free( targetCaption );
        return ( ret );
    }
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        free( targetCaption );
        return ( ret );
    }
    memset( request, 0x00, sz );

    p = any2utf( caption );
    strcpy( targetCaption, p ? p : caption );

    /* ≪ が &Lt; に化けたり、≫ が &Gt; に化けたりする件の対策 */
    if ( strstr( targetCaption, "\342\211\253" ) )    // &raquo;
        replaceString( targetCaption, "\342\211\253", "\302\273" );
    if ( strstr( targetCaption, "\342\211\252" ) )    // &laquo;
        replaceString( targetCaption, "\342\211\252", "\302\253" );
    if ( strchr( targetCaption, '<' ) )
        replaceStringEx( targetCaption );

    if ( strstr( targetCaption, "<a " )  )
        strcpy( targetCaption, encodeURL( targetCaption ) );

    sprintf( request,
             "email=%s&"
             "password=%s&"
             "type=photo&"
             "source=%s&",
             username,
             password,
             encodeURL(photoURL) );
    sprintf( request + strlen(request),
             "caption=%s&",
             targetCaption );
    if ( group && *group )
        sprintf( request + strlen(request),
                 "group=%s&",
                 group );
    sprintf( request + strlen(request),
             "generator=%s",
             "Chirrup" );

    setUpReceiveBuffer( response, sz );
    http_post( APIURL_TUMBLR_WRITE,
               "application/x-www-form-urlencoded",
               request, response );

    if ( *response ) {
        ret = checkResultOnTumblr( response );
        if ( ret && url && group && *group ) {
            if ( strchr( group, '.' ) )
                    sprintf( url, "http://%s/post/%s",
                             group, response );
        }
    }

    free( response );
    free( request  );
    free( targetCaption );

    return ( ret );
}


int
getBlogIDsTumblr(
    const char *userName,       // (I) ユーザ名 (メールアドレス)
    const char *password,       // (I) パスワード
    int        *numberOfBlogs,  // (I) 取得する/取得した blog 情報の数
    BLOGINF    *blogInfo )      // (O) 取得した blog 情報
{
    char    cookie[MAX_COOKIE_LEN];
    char    url[MAX_URLLENGTH];
    char    name[MAX_BLOGNAMELENGTH];
    char    id[MAX_BLOGIDLENGTH];
    int     numOfBlogs = 0;
    size_t  sz  = MAX_CONTENT_SIZE;
    BOOL    ret = FALSE;
    char    request[BUFSIZ];
    char    *response = (char *)malloc( sz );

    if ( !response )
        return ( ret );

    cookie[0] = NUL;
    sprintf( request,
             "email=%s&"
             "password=%s",
             userName, password );

    setUpReceiveBuffer( response, sz );
    http_postEx( APIURL_TUMBLR_ACOUNT,
                 "application/x-www-form-urlencoded",
                 request, response, cookie );

    if ( *response ) {
        char    *p = strstr( response, "<tumblelog title=\"" );
        char    *q;
        char    *r;
        char    *s;

        while ( p ) {
            url[0]  = NUL;
            name[0] = NUL;
            id[0]   = NUL;
            blogInfo[numOfBlogs].blogName[0] = NUL;
            blogInfo[numOfBlogs].url[0]      = NUL;
            blogInfo[numOfBlogs].blogID[0]   = NUL;

            p += 18;
            q = strchr( p, '"' );
            r = strstr( p, "/>" );
            if ( !q || !r )
                break;

            if ( q < r ) {
                strncpy( name, p, q - p );
                name[q - p] = NUL;
                s = utf2sjis( name );
                strcpy( blogInfo[numOfBlogs].blogName, s ? s : name );

                p = q + 1;
            }

            q = strstr( p, "url=\"" );
            if ( q && (q < r) ) {
                p = q + 5;
                q = strchr( p, '"' );
                if ( q && (q < r) ) {
                    strncpy( url, p, q - p );
                    url[q - p] = NUL;
                    strcpy( blogInfo[numOfBlogs].url, url );

                    s = strstr( url, "http://" );
                    if ( s ) {
                        strcpy( blogInfo[numOfBlogs].blogID, s + 7 );
                        s = blogInfo[numOfBlogs].blogID;
                        if ( s[strlen(s) - 1] == '/' )
                            s[strlen(s) - 1] = NUL;
                    }

                    p = q + 1;
                }
            }
            else
                strcpy( blogInfo[numOfBlogs].url, "(private)" );

            q = strstr( p, "id=\"" );
            if ( q && (q < r) ) {
                p = q + 4;
                q = strchr( p, '"' );
                if ( q && (q < r) ) {
                    strncpy( id, p, q - p );
                    id[q - p] = NUL;
                    strcpy( blogInfo[numOfBlogs].blogID, id );

                    p = q + 1;
                }
            }

            q = p;
            p = strstr( q, "<tumblelog title=\"" );
            numOfBlogs++;

            if ( numOfBlogs >= *numberOfBlogs )
                break;
        }

        ret = TRUE;
        *numberOfBlogs = numOfBlogs;
    }

    free( response );

    return ( numOfBlogs );
}
