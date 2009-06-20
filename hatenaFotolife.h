/*
 * hatenaFotolife.h : Twitter クライアント chirrup
 *      はてなフォトライフ 関連 ヘッダーファイル
 *          written by H.Tsujimura  19 Jan 2008
 *
 *      Copyright (c) 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/hatenaFotolife.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     08/01/23 17:39 Tsujimura543
 * 実装 + 動作確認、完了
 * 
 * 1     08/01/19 0:30 Tsujimura543
 * 最初の版
 */

#ifndef __HATENA_FOTOLIFE_H__
#define __HATENA_FOTOLIFE_H__

#define HATENA_F_ENDPOINT_URL "http://f.hatena.ne.jp/atom"

typedef enum {
    MITYPE_UNKNOWN = -1,
    MITYPE_JPG     = 1,
    MITYPE_GIF,
    MITYPE_PNG,
    MITYPE_BMP
}   MIMAGE_TYPE;

/* WSSE の生成 */
char    *makeWSSE( const char *username, const char *password, char *buffer,
                   int blogKind );


// はてなフォトライフ に「画像」を投稿する
BOOL
postPhotoOnHatenaFotolife(
    const char  *filename,       // (I) 投稿する画像のファイル名
    size_t      filesize,        // (I) 投稿する画像のファイルサイズ
    MIMAGE_TYPE filetype,        // (I) 投稿する画像のファイル種別
    const char  *title,          // (I) 投稿する画像の「題名」
    const char  *hatenaID,       // (I) はてな ID
    const char  *hatenaPassword, // (I) はてな パスワード
    char        *url );          // (O) アップロード先URL

#endif  /* __HATENA_FOTOLIFE_H__ */
