/*
 * CImage.cpp : Twitter クライアント chirrup
 *      CImage クラスの定義
 *          written by H.Tsujimura  23 Feb 2007 / 5 Apr 2007
 *
 * $Log: /comm/chirrup/CImage.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 9     08/07/08 14:41 Tsujimura543
 * キャッシュの有効時間を判定するのに使うファイルのタイムスタンプを
 * st_ctime から st_mtime に変更
 * 
 * 8     08/01/07 15:19 Tsujimura543
 * HttpOpen() をリファクタリング
 * 
 * 7     07/12/17 18:46 Tsujimura543
 * ConvertImageFile(), SaveBmpFile(), SavePngFile() を追加
 * 
 * 6     07/12/14 16:07 Tsujimura543
 * http_get() → _http_get() に置換
 * 
 * 5     07/06/07 20:17 Tsujimura543
 * malloc/free を new/delete に置き換えた
 * 
 * 4     07/05/25 18:19 Tsujimura543
 * キャッシュの有効時間を1時間にしてみた。前回の取得から1時間以上経過
 * したファイルは取得し直す(サーバが重い等で取得失敗した場合は、引き続
 * き、今までのファイルを使う)
 * 
 * 3     07/05/22 22:41 Tsujimura543
 * proxy 関連の設定取得・変更が発生する可能性のある処理は CImage
 * の中では使わないようにする
 * 
 * 2     07/04/13 23:27 Tsujimura543
 * CImage::HttpOpen() を修正、キャッシュに画像ファイルが存在すれば、
 * Webアクセスせずに、キャッシュを使うようにした
 * 
 * 1     07/04/13 23:01 Tsujimura543
 * 画像を表示する機能を実現するため、Web で公開されているコードを取り込む
 */

/*
 * 最初は、
 *    http://www.dinop.com/vc/read_jpeg_idg.html
 * を参考に、libjpeg を利用して jpg 画像をビットマップに変換する処理を
 * 実装しようとしていたが、結局
 *    http://hp.vector.co.jp/authors/VA007941/program/no2124.html
 * を見て OleLoadPictureFile() を使うことで、jpg 以外に gif にも対応で
 * きることが判明。libjpeg を使うのはやめて、OleLoadPictureFile() を使
 * うことにした。
 *
 * さらに、png に関しては OleLoadPictureFile() では対応できないので、
 * libpng (+ zlib) を使うことにした。libpng を使うにあたって、
 *    http://cetus.sakura.ne.jp/softlab/software/b2psrc.html
 * の png2bmp のソースコード
 *    png2bmp/bmphed.h
 *    png2bmp/common.h
 *    png2bmp/common.c
 *    png2bmp/png2bmp.c
 * をほとんどそのまま流用させていただいている (png2bmp() を追加するなど、
 * 少し、当方でいじっている)
 */

#include <afx.h>
#include "CImage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <afxctl.h>
#include <sys/stat.h>
#include "ProceedingDialog.h"

extern "C" {
#include "xmlRPC.h"
int png2bmp( const char *inpfile, const char *outfile );
}

char    *
_http_get( const char       *url,
           char             *response,
           ProceedingDialog *pdlg );

BOOL
saveBmp( const char *filename, HBITMAP hBitmap );

BOOL
savePNG( const char *fileName, HBITMAP hBitmap );


#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/CImage.cpp 1     09/05/14 3:50 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HBITMAP CImage::LoadImageFile( CString csFileName )
{
    HBITMAP hBmp = LoadBmpFile( csFileName );

    if ( !hBmp )
        hBmp = LoadPngFile( csFileName );

    return ( hBmp );
}

HBITMAP CImage::LoadBmpFile( CString csFileName )
{
    // ネタ元: http://hp.vector.co.jp/authors/VA007941/program/no2124.html
    // bmp, jpg, gif には対応しているが png や tif には対応していない
    // → png は CImage::LoadPngFile() にて対応。tif は今回は対応しない
    //    ことにする
	LPDISPATCH	    pDispatch;
	COleVariant	    oleFileName(csFileName);	
	OLE_HANDLE	    holeHandle;
	short		    type;
	CPictureHolder	PictureHolder;
    HBITMAP         hBmp = NULL;

	// 画像ファイルをロード
	if ( OleLoadPictureFile( oleFileName, &pDispatch ) >= 0 ) {		
		PictureHolder.SetPictureDispatch( (LPPICTUREDISP)pDispatch );	
		if ( PictureHolder.m_pPict != NULL ) {
			PictureHolder.m_pPict->get_Type( &type );
			if ((type == PICTYPE_BITMAP)                                &&
                (PictureHolder.m_pPict->get_Handle( &holeHandle ) >= 0)   ) {
                hBmp = (HBITMAP)holeHandle;
			}
		}
	}

	return ( hBmp );
}

HBITMAP CImage::LoadPngFile( CString filename )
{
    /* png は以下の処理で対応 */
    // libjpeg はエラーが発生すると abort() しちゃうので、あらかじめ、
    // そのファイルが png ファイルかどうかチェックしてから呼び出すよう
    // にしている (先頭の8バイトが PNG と偶然同じファイルが存在する可
    // 能性はあるけど、その場合は abort() しちゃいます)
    HBITMAP hBmp  = NULL;
    bool    isPNG = false;
    FILE    *fp   = fopen( filename, "rb" );

    // 当該ファイルのフォーマットが PNG かどうかチェックし、PNG だったら
    // libpng を利用してビットマップを生成
    if ( fp ) {
        unsigned char   buf[BUFSIZ];
        fread( buf, 1, BUFSIZ, fp );
        fclose( fp );

        if ( (buf[0] == 0x89) &&
             (buf[1] == 'P')  &&
             (buf[2] == 'N')  &&
             (buf[3] == 'G')  &&
             (buf[4] == 0x0D) &&
             (buf[5] == 0x0A) &&
             (buf[6] == 0x1A) &&
             (buf[7] == 0x0A)    )
            isPNG = true;
    }

    if ( isPNG ) {
        char    tempFileName[BUFSIZ];
        char    *p;

        strcpy( tempFileName, filename );
        p = strrchr( tempFileName, '.' );
        strcpy( p + 1, "bmp" );
        png2bmp( filename, tempFileName );
        hBmp = LoadBmpFile( tempFileName );
    }

	return ( hBmp );
}


bool    CImage::ConvertImageFile( CString srcFilename, CString bmpFilename )
{
    bool    ret = false;

    // GIF, JPEG, PNG 形式のファイルを BMP 形式のファイルに変換する
    HBITMAP bitmap = LoadImageFile( srcFilename );
    if ( bitmap )
        ret = SaveBmpFile( bmpFilename, bitmap );

    return ( ret );
}

bool    CImage::SaveBmpFile( CString filename, HBITMAP bitmap )
{
    bool    ret = false;
    BOOL    res = saveBmp( filename, bitmap );

    ret = res ? true : false;

    return ( ret );
}

bool    CImage::SavePngFile( CString filename, HBITMAP bitmap )
{
    bool    ret = false;
    BOOL    res = savePNG( filename, bitmap );

    ret = res ? true : false;

    return ( ret );
}


HBITMAP CImage::SimpleOpen( CString filename )
{
    // 指定されたファイル名の画像ファイルを読み、ビットマップを生成する
    return LoadImageFile( filename );
}

HBITMAP CImage::HttpOpen( CString url, CString filename /* = _T("") */ )
{
    bool    cached = false;

    // すでに filename で指定された画像ファイルが存在すれば、そのファイル
    // を表示する (Webアクセスはしない)
    if ( filename.GetLength() > 0 ) {
        struct stat s;
        if ( !stat( filename, &s ) ) {
            time_t  t = time( NULL );
            if ( t - s.st_mtime < 60 * 60 )
                return ( LoadImageFile( filename ) );

            cached = true;  // 新しいアイコンの取得に失敗した場合は、引き
                            // 続き、キャッシュ済みアイコンを適用する
        }
    }

    // 指定された URL の画像ファイルを読み、ビットマップを生成する
    char    *response;
    size_t  sz  = 65536 * 256;
    HBITMAP ret = NULL;

    response = new char[sz];
    if ( !response )
        return ret;

    setUpReceiveBuffer( response, sz );
    _http_get( url, response, NULL );
    if ( *response ) {
        size_t  sz = getBinSize();
        if ( sz > 0 ) {
            CString fileName = "tmp.img";
            if ( filename.GetLength() > 0 )
                fileName = filename;

            FILE    *fp = fopen( fileName, "wb" );
            if ( fp ) {
                fwrite( response, sz, 1, fp );
                fclose( fp );

                ret = LoadImageFile( fileName );
                if ( filename.GetLength() == 0 )
                    unlink( fileName );
            }
        }
    }
    else if ( cached )
        ret = LoadImageFile( filename );

    delete [] response;
    encodeURL( NULL );

    return ret;
}
