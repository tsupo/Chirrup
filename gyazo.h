/*
 * gyazo.h : Twitter クライアント chirrup
 *      Gyazo 関連 ヘッダーファイル
 *          written by H.Tsujimura  6 Dec 2007 / 13 Dec 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/gyazo.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 1     07/12/13 19:01 Tsujimura543
 * Gyazo関連のプロトタイプ宣言を tumblr.h から分離独立させた
 */

#ifndef __GYAZO_H__
#define __GYAZO_H__

// Gyazo に「画像」を投稿する
BOOL
postPhotoOnGyazo(
    const char *filename,   // (I)   Gyazo に投稿する画像のファイル名
    size_t     filesize,    // (I)   Gyazo に投稿する画像のファイルサイズ
    char       *gyazoID,    // (I/O) Gyazo ID
    char       *url );      // (O)   アップロード先URL

#endif  /* __GYAZO_H__ */
