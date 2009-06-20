/*
 * savePNG.cpp : Twitter クライアント chirrup
 *      BMPイメージ → PNGファイル変換・保存処理
                                    インプリメンテーション ファイル
 *          written by H.Tsujimura  14 Dec 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      Some Rights Reserved.
 *
 * $Log: /comm/chirrup/savePNG.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     08/12/04 18:19 Tsujimura543
 * コード整理、安定化作業を実施
 * 
 * 2     07/12/15 5:05 Tsujimura543
 * BMP形式のファイルを保存する処理を完全に別のものに入れ替え。
 * 動作確認完了
 * 
 * 1     07/12/15 2:23 Tsujimura543
 * 暫定版 (まだ、ちゃんと動いていない)
 */

#include "chirrup.h"
extern "C" {
int bmp2png( const char *inpfile, const char *outfile );
}

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/savePNG.cpp 1     09/05/14 3:50 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BOOL
saveBmp( const char *filename, HBITMAP hBitmap )
{
    // 出典: http://blog.csdn.net/bobob/archive/2005/02/20/294759.aspx

    if ( !filename || !(*filename) || !hBitmap )
        return FALSE;

    HDC                 hDC;
    int                 iBits;
    WORD                wBitCount;
    DWORD               dwPaletteSize = 0;
    DWORD               dwBmBitsSize  = 0;
    DWORD               dwDIBSize     = 0;
    BITMAP              Bitmap;
    BITMAPFILEHEADER    bmfHdr;
    BITMAPINFOHEADER    bi;
    LPBITMAPINFOHEADER  lpbi;
    HANDLE              hDib, hPal, hOldPal = NULL;
    FILE                *fp;

    hDC   = CreateDC( "DISPLAY", NULL, NULL, NULL );
    iBits = GetDeviceCaps( hDC, BITSPIXEL ) * GetDeviceCaps( hDC, PLANES );
    DeleteDC( hDC );
    if ( iBits <= 1 )
        wBitCount = 1;
    else if ( iBits <= 4 )
        wBitCount = 4;
    else if ( iBits <= 8 )
        wBitCount = 8;
    else
        wBitCount = 24;

    GetObject( hBitmap, sizeof ( Bitmap ), (LPSTR)&Bitmap );
    bi.biSize          = sizeof ( BITMAPINFOHEADER );
    bi.biWidth         = Bitmap.bmWidth;
    bi.biHeight        = Bitmap.bmHeight;
    bi.biPlanes        = 1;
    bi.biBitCount      = wBitCount;
    bi.biCompression   = BI_RGB;
    bi.biSizeImage     = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrImportant  = 0;
    bi.biClrUsed       = 0;

    dwBmBitsSize =
            ((Bitmap.bmWidth * wBitCount + 31) / 32) * 4 *Bitmap.bmHeight;

    hDib  = GlobalAlloc(
                GHND,
                dwBmBitsSize + dwPaletteSize + sizeof ( BITMAPINFOHEADER ) );
    lpbi  = (LPBITMAPINFOHEADER)GlobalLock( hDib );
    *lpbi = bi;

    hPal = GetStockObject( DEFAULT_PALETTE );
    if ( hPal ) { 
        hDC     = ::GetDC( NULL ); 
        hOldPal = ::SelectPalette( hDC, (HPALETTE)hPal, FALSE );
        RealizePalette( hDC );
    }

    GetDIBits( hDC, hBitmap, 0, (UINT) Bitmap.bmHeight,
               (LPSTR)lpbi + sizeof ( BITMAPINFOHEADER ) + dwPaletteSize,
               (BITMAPINFO *)lpbi, DIB_RGB_COLORS );

    if ( hOldPal ) {
        ::SelectPalette( hDC, (HPALETTE)hOldPal, TRUE );
        RealizePalette( hDC );
        ::ReleaseDC( NULL, hDC );
    }

    fp = fopen( filename, "wb" );
    if ( !fp ) {
        GlobalUnlock( hDib );
        GlobalFree( hDib );
        return ( FALSE );
    }

    bmfHdr.bfType = 0x4D42; // "BM"
    dwDIBSize     = sizeof ( BITMAPFILEHEADER ) +
                    sizeof ( BITMAPINFOHEADER ) +
                    dwPaletteSize +
                    dwBmBitsSize;
    bmfHdr.bfSize = dwDIBSize;
    bmfHdr.bfReserved1 = 0;
    bmfHdr.bfReserved2 = 0;
    bmfHdr.bfOffBits = sizeof ( BITMAPFILEHEADER ) +
                       sizeof ( BITMAPINFOHEADER ) +
                       dwPaletteSize;

    fwrite( &bmfHdr, sizeof ( BITMAPFILEHEADER ), 1, fp );
    fwrite( lpbi, sizeof ( BYTE ), dwDIBSize, fp );

    GlobalUnlock( hDib );
    GlobalFree( hDib );
    fclose( fp );

    return TRUE;
}


BOOL
savePNG( const char *fileName, HBITMAP hBitmap )
{
    const char  intermediateFilename[MAX_PATH] = "tempTmp.png";
    BOOL        ret = FALSE;

    ret = saveBmp( fileName, hBitmap );
    if ( ret ) {
        int r = bmp2png( fileName, intermediateFilename );
        ret = !r ? TRUE : FALSE;
    }

    unlink( fileName );
    rename( intermediateFilename, fileName );

    return ( ret );
}
