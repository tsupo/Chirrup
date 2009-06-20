/*
 * flickr.c : Twitter クライアント chirrup
 *      Flickr 関連各種処理群
 *          written by H.Tsujimura  9 Jan 2008
 *
 *      Copyright (c) 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/flickr.c $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 6     09/04/22 21:31 Tsujimura543
 * GetAccessTokenOnFlickr() 内で「許可を与える」のをやめたときにMessageBox
 * で表示する文言を変更
 * 
 * 5     09/04/22 21:11 Tsujimura543
 * 「設定」ダイアログからもFlickr認証のアクセストークン(frob)を取得できる
 * ようにした
 * 
 * 4     08/12/04 18:19 Tsujimura543
 * コード整理、安定化作業を実施
 * 
 * 3     08/01/23 17:41 Tsujimura543
 * 異常系処理を修正
 * 
 * 2     08/01/09 23:33 Tsujimura543
 * process global な static なメモリ領域を thread local な static
 * に変更した
 * 
 * 1     08/01/09 23:01 Tsujimura543
 * 最初の版 (動作確認済み)
 */

#include <time.h>
#include "xmlRpc.h"
#include "multipart.h"
#include "utility.h"
#include "flickr.h"
#include "MD5.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/flickr.c 1     09/05/14 3:50 tsupo $";
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

char *
ToLower( char *p )
{
    char    *s = p;
    while ( *s ) {
        if ( (*s >= 'A') && (*s <= 'Z') )
            *s = (char)((*s - 'A') + 'a');
        s++;
    }

    return ( p );
}


// api.flickr.com/services/upload 用 signature 生成処理
char    *
getSinganureForFlickr(
        const char *secret,
        const char *flickrKey,
        const char *flickrToken,
        const char *title,
        const char *description
    )
{
    char                *p = NULL;
    Thread static char  signature[BUFSIZ];

    signature[0] = NUL;
    strcpy( signature, secret );

    sprintf( signature + strlen(signature),
             "api_key%s",
             flickrKey );

    sprintf( signature + strlen(signature),
             "auth_token%s",
             flickrToken );

    if ( description ) {
        if ( *description )
            sprintf( signature + strlen(signature),
                     "description%s",
                     description );
        else
            strcat( signature, "description" );
    }

    if ( title ) {
        if ( *title )
            sprintf( signature + strlen(signature),
                     "title%s",
                     title );
        else
            strcat( signature, "title" );
    }

    p = MD5(signature);
    if ( p )
        strcpy( signature, ToLower( p ) );
    else
        signature[0] = NUL;

    return ( signature );
}

// flickr.auth.getFrob 用 signature 生成処理
char    *
getSinganureForGetFrob(
        const char *flickrSecret,
        const char *flickrKey
    )
{
    char                *p = NULL;
    Thread static char  signature[BUFSIZ];

    signature[0] = NUL;
    strcpy( signature, flickrSecret );

    sprintf( signature + strlen(signature),
             "api_key%s",
             flickrKey );

    sprintf( signature + strlen(signature),
             "method%s",
             "flickr.auth.getFrob" );

    p = MD5(signature);
    if ( p )
        strcpy( signature, ToLower( p ) );
    else
        signature[0] = NUL;

    return ( signature );
}

// flickr.com/services/auth 用 signature 生成処理 (write 許可指定)
char    *
getSinganureForAuth(
        const char *flickrSecret,
        const char *flickrKey,
        const char *frob
    )
{
    char                *p = NULL;
    Thread static char  signature[BUFSIZ];

    signature[0] = NUL;
    strcpy( signature, flickrSecret );

    sprintf( signature + strlen(signature),
             "api_key%s",
             flickrKey );

    sprintf( signature + strlen(signature),
             "frob%s",
             frob );

    sprintf( signature + strlen(signature),
             "perms%s",
             "write" );

    p = MD5(signature);
    if ( p )
        strcpy( signature, ToLower( p ) );
    else
        signature[0] = NUL;

    return ( signature );
}

// flickr.auth.getToken 用 signature 生成処理
char    *
getSinganureForGetToken(
        const char *flickrSecret,
        const char *flickrKey,
        const char *frob
    )
{
    char                *p = NULL;
    Thread static char  signature[BUFSIZ];

    signature[0] = NUL;
    strcpy( signature, flickrSecret );

    sprintf( signature + strlen(signature),
             "api_key%s",
             flickrKey );

    sprintf( signature + strlen(signature),
             "frob%s",
             frob );

    sprintf( signature + strlen(signature),
             "method%s",
             "flickr.auth.getToken" );

    p = MD5(signature);
    if ( p )
        strcpy( signature, ToLower( p ) );
    else
        signature[0] = NUL;

    return ( signature );
}


// frob の取得
char    *
getFlickrFROB(
        const char *flickrKey,
        const char *flickrSecret,
        char       *frob
    )
{
    char    req[BUFSIZ];
    char    url[BUFSIZ + BUFSIZ];
    char    res[BUFSIZ + BUFSIZ];
    size_t  sz = BUFSIZ + BUFSIZ;

    // flickr.auth.getFrob
    sprintf( req,
             "method=flickr.auth.getFrob&"
             "api_key=%s&"
             "api_sig=%s",
             flickrKey,
             getSinganureForGetFrob( flickrSecret, flickrKey ) );
    sprintf( url, "http://flickr.com/services/rest/?%s", req );

    setUpReceiveBuffer( res, sz );
    http_get( url, res );
    if ( *res ) {
        char    *p;

        p = strstr( res, "<frob>" );
        if ( p ) {
            char    *q;

            p += 6;
            q = strstr( p, "</frob>" );
            if ( q ) {
                strncpy( frob, p, q - p );
                frob[q - p] = NUL;
            }
        }
    }

    return ( frob );
}

// 「Flickr トークン」の取得
char    *
getFlickrToken(
        const char *flickrKey,
        const char *flickrSecret,
        const char *frob,
        char       *flickrToken,
        char       *flickrNSID
    )
{
    char    req[BUFSIZ];
    char    url[BUFSIZ + BUFSIZ];
    char    res[BUFSIZ + BUFSIZ];
    size_t  sz = BUFSIZ + BUFSIZ;
    int     retry = 20;
    BOOL    done  = FALSE;

    // flickr.auth.getToken
    sprintf( req,
             "method=flickr.auth.getToken&"
             "api_key=%s&"
             "frob=%s&"
             "api_sig=%s",
             flickrKey,
             frob,
             getSinganureForGetToken( flickrSecret, flickrKey, frob ) );
    sprintf( url, "http://flickr.com/services/rest/?%s", req );

    do {
        setUpReceiveBuffer( res, sz );
        http_get( url, res );
        if ( *res ) {
            char    *p;

            p = strstr( res, "<token>" );
            if ( p ) {
                char    *q;

                p += 7;
                q = strstr( p, "</token>" );
                if ( q ) {
                    strncpy( flickrToken, p, q - p );
                    flickrToken[q - p] = NUL;
                    done = TRUE;
                }
            }

            p = strstr( res, " nsid=\"" );
            if ( p ) {
                char    *q;

                p += 7;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( flickrNSID, p, q - p );
                    flickrNSID[q - p] = NUL;
                }
            }

            if ( done )
                break;
        }
        retry--;
        if ( retry > 0 )
            Sleep( 2000 );
    } while ( retry > 0 );

    return ( flickrToken );
}

// 「Flickr ユーザ名」の取得
char    *
getFlickrUserName(
        const char *flickrKey,
        const char *flickrNSID,
        char       *flickrUserName
    )
{
    char    req[BUFSIZ];
    char    url[BUFSIZ + BUFSIZ];
    char    res[BUFSIZ + BUFSIZ];
    size_t  sz = BUFSIZ + BUFSIZ;

    // flickr.people.getInfo (指定 NSID のユーザ情報の取得)
    sprintf( req,
             "method=flickr.people.getInfo&"
             "api_key=%s&"
             "user_id=%s",
             flickrKey,
             flickrNSID ); // このAPIは api_sig 不要
    sprintf( url, "http://flickr.com/services/rest/?%s", req );

    setUpReceiveBuffer( res, sz );
    http_get( url, res );
    if ( *res ) {
        char    *p;

        p = strstr( res, "<photosurl>http://www.flickr.com/photos/" );
        if ( p ) {
            char    *q;

            p += 40;
            q = strstr( p, "/</photosurl>" );
            if ( q ) {
                strncpy( flickrUserName, p, q - p );
                flickrUserName[q - p] = NUL;
            }
        }
    }

    return ( flickrUserName );
}


// 画像ファイルを Flickr に投稿する
BOOL
postPhotoOnFlickr(
    const char *filename,       // (I)   Flickr に投稿する画像のファイル名
    size_t     filesize,        // (I)   Flickr に投稿する画像のファイルサイズ
    const char *title,          // (I)   Flickr に投稿する画像の「題名」
    const char *caption,        // (I)   Flickr に投稿する画像の「説明」
    const char *flickrKey,      // (I)   Flickr APIキー
    const char *flickrSecret,   // (I)   signature生成時に付加する文字列
    char       *flickrToken,    // (I/O) Flickr トークン
    char       *flickrUserName, // (I/O) Flickr ユーザ名
    char       *url )           // (O)   アップロード先URL
{
    BOOL    ret = FALSE;
    char    *request;
    char    *response;
    char    *imageData;
    char    *signature;
    char    *targetTitle;
    char    *targetCaption;
    char    *p;
    char    *base;
    char    *tail;
    size_t  sz1 = filesize * 6 + BUFSIZ;
    size_t  sz2 = MAX_CONTENT_SIZE;
    size_t  szz = 0;
    FILE    *fp;
    char    contentType[MAX_LOGICALLINELEN];
    char    *separator = getMultiPartID();
    FILEINF fInfo;
    BOOL    r;

    char    flickrNSID[256];

    if ( !flickrToken || !flickrUserName )
        return ( ret );

    // Flickr 認証
    flickrNSID[0] = NUL;
    r = GetAccessTokenOnFlickr( flickrKey,   flickrSecret,
                                flickrToken, flickrUserName, flickrNSID );
    if ( !r )
        return ( ret );

    // signature 生成
    if ( !title || !(*title) ) {
        p = strrchr( filename, '/' );
        if ( !p )
            p = strrchr( filename, '\\' );
        if ( !p )
            p = strrchr( filename, ':' );
        if ( p ) {
            p++;
            title = p;
        }
        else
            title = " ";
    }
    targetTitle = (char *)malloc( strlen(title) * 6 + 1 );
    if ( !targetTitle ) {
        return ( ret );
    }

    if ( !caption || !(*caption) )
        caption = " ";
    targetCaption = (char *)malloc( strlen(caption) * 6 + 1 );
    if ( !targetCaption ) {
        free( targetTitle );
        return ( ret );
    }

    p = any2utf( title );
    strcpy( targetTitle, p ? p : title );

    p = any2utf( caption );
    strcpy( targetCaption, p ? p : caption );

    signature = getSinganureForFlickr( flickrSecret,
                                       flickrKey, flickrToken,
                                       targetTitle, targetCaption );

    // アップロード
    imageData = (char *)malloc( filesize + 1 );
    if ( !imageData ) {
        free( targetCaption );
        free( targetTitle );
        return ( ret );
    }

    fp = fopen( filename, "rb" );
    if ( !fp ) {
        free( imageData );
        free( targetCaption );
        free( targetTitle );
        return ( ret );
    }
    fread( imageData, filesize, 1, fp );
    fclose( fp );

    request  = (char *)malloc( sz1 );
    if ( !request ) {
        free( imageData );
        free( targetCaption );
        free( targetTitle );
        return ( ret );
    }
    response = (char *)malloc( sz2 );
    if ( !response ) {
        free( request );
        free( imageData );
        free( targetCaption );
        free( targetTitle );
        return ( ret );
    }
    memset( request, 0x00, sz1 );

    // アップロードするファイルの情報をセット
    strcpy( fInfo.type, "application/unknown" );    /* 暫定 */
    strcpy( fInfo.name, filename );

    p = base64( (unsigned char*)imageData, filesize );
    if ( !p ) {
        base64( NULL, 0 );
        free( response );
        free( request );
        free( imageData );
        free( targetCaption );
        free( targetTitle );
        return ( ret );
    }
    fInfo.bits = (unsigned char *)p;

    // multipart/form-data の組み立て
    getSendBufferPointer( request, base );
    tail = base;

    sprintf( contentType, "multipart/form-data; boundary=%s", separator );
    strcpy( tail, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "api_key", 0, flickrKey, NULL ) );
    strcat( tail, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "auth_token", 0, flickrToken, NULL ) );
    strcat( tail, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "api_sig", 0, signature, NULL ) );

    szz  =  strlen( tail );
    tail += szz;
    szz  =  0;
    p    =  makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_FILE,
                               "photo", 0, (char *)&fInfo, &szz );
    memcpy( tail, p, szz );
    tail += szz;

    if ( title ) {
        if ( *title )
            strcpy( tail, 
                    makeMultiPartItem(
                                separator, MULITIPART_ITEM_TYPE_STRING,
                                "title", 0, targetTitle, NULL ) );
        else
            strcpy( tail, 
                    makeMultiPartItem(
                                separator, MULITIPART_ITEM_TYPE_STRING,
                                "title", 0, "", NULL ) );
        szz  =  strlen( tail );
        tail += szz;
    }

    if ( caption ) {
        if ( *caption )
            strcpy( tail, 
                    makeMultiPartItem(
                                separator, MULITIPART_ITEM_TYPE_STRING,
                                "description", 0, targetCaption, NULL ) );
        else
            strcpy( tail, 
                    makeMultiPartItem(
                                separator, MULITIPART_ITEM_TYPE_STRING,
                                "description", 0, "", NULL ) );
        szz  =  strlen( tail );
        tail += szz;
    }

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
    http_post( "http://api.flickr.com/services/upload/",
               contentType,
               request, response );

    if ( *response ) {
        p = strstr( response, "<photoid>" );
        if ( p ) {
            ret = TRUE;

            if ( url ) {
                char    *q;
                char    photoID[BUFSIZ];

                p += 9;
                q = strstr( p, "</photoid>" );
                if ( q ) {
                    strncpy( photoID, p, q - p );
                    photoID[q - p] = NUL;
                    sprintf( url, "http://www.flickr.com/photos/%s/%s/",
                             flickrUserName[0] ? flickrUserName : flickrNSID,
                             photoID );
                }
            }
        }
    }

    base64( NULL, 0 );
    free( response );
    free( request  );
    free( imageData );
    free( targetCaption );
    free( targetTitle );

    return ( ret );
}


// アクセストークンの取得
BOOL
GetAccessTokenOnFlickr(
    const char *flickrKey,      // (I)   Flickr APIキー
    const char *flickrSecret,   // (I)   signature生成時に付加する文字列
    char       *flickrToken,    // (I/O) Flickr トークン
    char       *flickrUserName, // (I/O) Flickr ユーザ名
    char       *flickrNSID )    // (I/O) Flickr NSID
{
    BOOL    ret = FALSE;
    int     r;
    char    frob[2048];

    flickrNSID[0] = NUL;
    frob[0]       = NUL;

    if ( !flickrToken || !flickrUserName )
        return ( ret );

    // Flickr 認証
    if ( !(*flickrToken) || !(*flickrUserName) ) {
        char    authURL[BUFSIZ + BUFSIZ];

        // frob の取得
        getFlickrFROB( flickrKey, flickrSecret, frob );
        if ( !(frob[0]) )
            return ( ret );

        // ブラウザ起動 -- ユーザにアクセス許可を求める
        sprintf( authURL,
                 "http://flickr.com/services/auth/?"
                 "api_key=%s&"
                 "perms=write&"
                 "frob=%s&"
                 "api_sig=%s",
                 flickrKey,
                 frob,
                 getSinganureForAuth( flickrSecret, flickrKey, frob ) );

        ShellExecute( NULL, "open", authURL, NULL, NULL, SW_SHOWNORMAL );

        // ユーザの許可待ち
        r = MessageBox( NULL,
            "Chirrup が Flickr にアクセスする許可を与えてください。\r\n"
            "許可を与え終わったら、OK ボタンを押してください。\r\n"
            "許可を与えたくない場合は キャンセル ボタンを押してください。  ",
            "Flickr へのアクセス許可", MB_OKCANCEL|MB_ICONINFORMATION );
        if ( r != IDOK ) {
            MessageBox( NULL,
                        "Flickr 認証用アクセストークンの取得を中止します。  ",
                        "Flickr 認証", MB_OK|MB_ICONWARNING );
            return ( ret );
        }

        // token 取得
        getFlickrToken( flickrKey, flickrSecret, frob,
                        flickrToken, flickrNSID );
        if ( !(*flickrToken) )
            return ( ret );
    }

    // Flickr ユーザ名の取得 (アップロード先 URL を確定するために必要)
    if ( !(*flickrUserName) ) {
        if ( flickrNSID && *flickrNSID )
            getFlickrUserName( flickrKey, flickrNSID, flickrUserName );
        else
            strcpy( flickrUserName, flickrNSID );
    }

    if ( *flickrToken && *flickrUserName )
        ret = TRUE;

    return ( ret );
}
