/*
 * tumblr.h : Twitter クライアント chirrup
 *      tumblr 関連 ヘッダーファイル
 *          written by H.Tsujimura  5 Nov 2007
 *
 *      Copyright (c) 2007, 2008, 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/tumblr.h $
 * 
 * 2     09/05/31 20:42 tsupo
 * 1.142版
 * 
 * 9     09/05/29 19:22 Tsujimura543
 * 同一アカウントで複数 tumbleblog を開設している場合の投稿先
 * tumbleblog を指定しての投稿を可能にした
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 8     08/02/13 0:10 Tsujimura543
 * tumblr への Quote 投稿時にコメントもいっしょに投稿できるようにした
 * 
 * 7     07/12/13 19:01 Tsujimura543
 * Gyazo関連のプロトタイプ宣言を gyazo.h として分離独立させた
 * 
 * 6     07/12/10 21:21 Tsujimura543
 * postPhotoWithUrlOnTumblr() を追加
 * 
 * 5     07/12/10 16:39 Tsujimura543
 * Gyazo への投稿処理関連を fix
 * 
 * 4     07/12/06 19:50 Tsujimura543
 * Gyazo に画像をアップロードする機能を実装
 * (いずれは別ファイルとして分離する)
 * 
 * 3     07/12/06 1:29 Tsujimura543
 * postPhotoOnTumblr() を追加
 * 
 * 2     07/11/07 3:39 Tsujimura543
 * 見ている発言を 引用して Tumblr へ投稿する機能を作成
 * 
 * 1     07/11/05 23:56 Tsujimura543
 * 最初の版
 */

#ifndef __TUMBLR_H__
#define __TUMBLR_H__

#ifdef __cplusplus
extern "C" {
#endif

// tumblr に「発言」の「引用」を投稿する
BOOL
postTumblr(
    const char *targetURL,  // (I) tumblr に投稿する記事の URL
    const char *quote,      // (I) tumblr に投稿する記事の「内容」
    const char *title,      // (I) tumblr に投稿する記事の「題名」
    const char *comment,    // (I) tumblr に投稿する記事の「コメント」
    const char *username,   // (I) tumblr に login するときのメールアドレス
    const char *password,   // (I) パスワード
    const char *group );    // (I) 投稿先 tumbleblog ID またはグループ名

// tumblr に「画像」を投稿する
BOOL
postPhotoOnTumblr(
    const char *filename,   // (I)   tumblr に投稿する画像のファイル名
    size_t     filesize,    // (I)   tumblr に投稿する画像のファイルサイズ
    const char *caption,    // (I)   tumblr に投稿する画像の「説明」
    const char *username,   // (I)   tumblr に login するときのメールアドレス
    const char *password,   // (I)   パスワード
    const char *group,      // (I)   投稿先 tumbleblog ID またはグループ名
    char       *url );      // (O)   アップロード先URL

// tumblr に url 付きで「画像」を投稿する
BOOL
postPhotoWithUrlOnTumblr(
    const char *photoURL,   // (I)   tumblr に投稿する画像のURL
    const char *caption,    // (I)   tumblr に投稿する画像の「説明」
    const char *username,   // (I)   tumblr に login するときのメールアドレス
    const char *password,   // (I)   パスワード
    const char *group,      // (I)   投稿先 tumbleblog ID またはグループ名
    char       *url );      // (O)   アップロード先URL

// tumbleblog 一覧を取得する
int
getBlogIDsTumblr(
    const char *userName,       // (I) ユーザ名 (メールアドレス)
    const char *password,       // (I) パスワード
    int        *numberOfBlogs,  // (I) 取得する/取得した blog 情報の数
    BLOGINF    *blogInfo );     // (O) 取得した blog 情報

#ifdef __cplusplus
}
#endif

#endif  /* __TUMBLR_H__ */
