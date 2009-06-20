/*
 * gyazo.c : Twitter クライアント chirrup
 *      Gyazo 関連各種処理群
 *          written by H.Tsujimura  6 Dec 2007 / 13 Dec 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/gyazo.c $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 1     07/12/13 19:14 Tsujimura543
 * Gyazo関連の関数群を tumblr.c から分離独立させた
 */

#include <time.h>
#include "xmlRpc.h"
#include "multipart.h"
#include "utility.h"
#include "gyazo.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/gyazo.c 1     09/05/14 3:50 tsupo $";
#endif


char    *
getIDforGyazo( char *gyazoID )
{
    char    *p = NULL;

    if ( gyazoID ) {
        if ( *gyazoID )
            p = gyazoID;    // すでに設定済みの ID を使いまわす
        else {
            // 最初の投稿実行日時を元に ID を生成、設定する
            char        timebuf[MAX_DATELENGTH];
            struct tm   *dt;
            time_t      now	= time( NULL );

            dt = localtime( &now );
            strftime( timebuf, MAX_DATELENGTH, "%Y%m%d%H%M%S", dt );

            strcpy( gyazoID, timebuf );
            p = gyazoID;
        }
    }

    return ( p );
}

BOOL
postPhotoOnGyazo(
    const char *filename,   // (I)   Gyazo に投稿する画像のファイル名
    size_t     filesize,    // (I)   Gyazo に投稿する画像のファイルサイズ
    char       *gyazoID,    // (I/O) Gyazo ID
    char       *url )       // (O)   アップロード先URL
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

    request  = (char *)malloc( sz1 );
    if ( !request ) {
        free( imageData );
        return ( ret );
    }
    response = (char *)malloc( sz2 );
    if ( !response ) {
        free( request );
        free( imageData );
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
        return ( ret );
    }
    fInfo.bits = (unsigned char *)p;

    // multipart/form-data の組み立て
    getSendBufferPointer( request, base );
    tail = base;

    sprintf( contentType, "multipart/form-data; boundary=%s", separator );

    strcpy( tail, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "id", 0, getIDforGyazo( gyazoID ), NULL ) );

    szz  =  strlen( tail );
    tail += szz;
    szz  =  0;
    p    =  makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_FILE,
                               "imagedata", 0, (char *)&fInfo, &szz );
    memcpy( tail, p, szz );
    tail += szz;

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
    http_post( "http://gyazo.com/upload.cgi",
               contentType,
               request, response );

    if ( *response ) {
        if ( !strncmp( response, "http://gyazo.com/", 17 ) ) {
            ret = TRUE;
            if ( url )
                strcpy( url, response );
        }
    }

    base64( NULL, 0 );
    free( response );
    free( request  );
    free( imageData );

    return ( ret );
}
