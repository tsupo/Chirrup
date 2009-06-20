/*
 * CImage.h  : Twitter クライアント chirrup
 *      CImage クラスの定義
 *          written by H.Tsujimura  4 Apr 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/CImage.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     07/12/17 18:46 Tsujimura543
 * ConvertImageFile(), SaveBmpFile(), SavePngFile() を追加
 * 
 * 2     07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 1     07/04/13 23:01 Tsujimura543
 * 画像を表示する機能を実現するため、Web で公開されているコードを取り込む
 */

#if !defined(AFX_CJIMAGE_H__A07B8677_638F_45CA_8C84_9324D00DA47B__INCLUDED_)
#define AFX_CJIMAGE_H__A07B8677_638F_45CA_8C84_9324D00DA47B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

class CImage
{
public:
    CImage() {}

    HBITMAP LoadImageFile( CString filename );

    HBITMAP LoadBmpFile( CString filename );
    HBITMAP LoadPngFile( CString filename );
	HBITMAP SimpleOpen( CString filename );
    HBITMAP HttpOpen( CString url, CString filename = _T("") );

    bool    ConvertImageFile( CString srcFilename, CString bmpFilename );
    bool    SaveBmpFile( CString filename, HBITMAP bitmap );
    bool    SavePngFile( CString filename, HBITMAP bitmap );

private:
    HBITMAP LoadPngFileEx( const char *filename );
    CImage( CImage &img );
    CImage  operator = ( CImage &img );
};

#endif // !defined(AFX_CJIMAGE_H__A07B8677_638F_45CA_8C84_9324D00DA47B__INCLUDED_)
