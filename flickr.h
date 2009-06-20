/*
 * flickr.h : Twitter クライアント chirrup
 *      Flickr 関連 ヘッダーファイル
 *          written by H.Tsujimura  9 Jan 2008
 *
 *      Copyright (c) 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/flickr.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     09/04/22 21:11 Tsujimura543
 * 「設定」ダイアログからもFlickr認証のアクセストークン(frob)を取得できる
 * ようにした
 * 
 * 3     08/01/09 22:26 Tsujimura543
 * flickrNSID → flickrUserName に変更
 * 
 * 2     08/01/09 21:58 Tsujimura543
 * 引数 flickrNSID を追加
 * 
 * 1     08/01/09 19:23 Tsujimura543
 * 新規作成
 */

#ifndef __FLICKR_H__
#define __FLICKR_H__

// Flickr に「画像」を投稿する
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
    char       *url );          // (O)   アップロード先URL

// アクセストークンの取得
BOOL
GetAccessTokenOnFlickr(
    const char *flickrKey,      // (I)   Flickr APIキー
    const char *flickrSecret,   // (I)   signature生成時に付加する文字列
    char       *flickrToken,    // (I/O) Flickr トークン
    char       *flickrUserName, // (I/O) Flickr ユーザ名
    char       *flickrNSID );   // (I/O) Flickr NSID

#endif  /* __FLICKR_H__ */
