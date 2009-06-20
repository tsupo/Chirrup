/*
 * twitter.h   : Twitter クライアント chirrup
 *      各サービスのデフォルトユーザアイコンの定義
 *          written by H.Tsujimura  4 Apr 2007 / 18 Jun 2007
 *
 *      Copyright (c) 2007, 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/defaultImage.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 10    08/08/22 20:22 Tsujimura543
 * HATENAHAIKU_DEFAULT_IMAGE を変更
 * 
 * 9     08/08/22 18:42 Tsujimura543
 * 「はてなハイク」対応
 * 
 * 8     08/07/08 12:18 Tsujimura543
 * WASSR_DEFAULT_IMAGE を変更
 * 
 * 7     08/02/07 22:36 Tsujimura543
 * copyright 表示を修正 (2008 を追加)
 * 
 * 6     08/01/07 14:44 Tsujimura543
 * TWITTER_DEFAULT_IMAGE を変更
 * 
 * 5     07/06/27 15:41 Tsujimura543
 * HARUFM_DEFAULT_IMAGE を追加
 * 
 * 4     07/06/20 17:32 Tsujimura543
 * TIMELOG_DEFAULT_IMAGE を追加
 * 
 * 3     07/06/18 19:07 Tsujimura543
 * コメントを修正
 * 
 * 2     07/06/18 18:57 Tsujimura543
 * JAIKU_DEFAULT_IMAGE を 50x50 の画像に変更
 * 
 * 1     07/06/18 18:50 Tsujimura543
 * いろんなヘッダファイルで定義していたデフォルトアイコンの(URLの)定義
 * を一箇所に集めてみた
 */

#ifndef __DEFAULT_IMAGE_H__
#define __DEFAULT_IMAGE_H__

#define TWITTER_DEFAULT_IMAGE   \
   "http://static.twitter.com/images/default_profile_normal.png"
// "http://assets1.twitter.com/images/default_profile_image_normal.gif"

#define JAIKU_DEFAULT_IMAGE   \
    "http://jaiku.com/image/avatar_default_t.jpg"       // 50 x 50
 // "http://jaiku.com/image/avatar_default_u.jpg"       // 30 x 30
 // "http://jaiku.com/image/avatar_default_f.jpg"       // 75 x 75

#define WASSR_DEFAULT_IMAGE   \
    "http://wassr.jp/img/default-profile-img.32.png"    // 32 x 32
 // "http://wassr.jp/img/default-profile-img.64.png"    // 64 x 64
 // "http://wassr.jp/user/default/profile_img.png.32"   //  1 x  1
 // "http://wassr.jp/user/default/profile_img.png.64"   //  1 x  1

#define MOGO2_DEFAULT_IMAGE   \
    "http://mogo2.jp/images/photo01_medium.gif"         // 30 x 30
 // "http://mogo2.jp/images/photo01_small.gif"          // 24 x 24
 // "http://mogo2.jp/images/photo01.gif"                // 140 x 140

#define TIMELOG_DEFAULT_IMAGE   \
    "http://timelog.jp/images/nophoto_m.jpg"            // 35 x 35
 // "http://timelog.jp/images/nophoto_s.jpg"            // 25 x 25
 // "http://timelog.jp/images/nophoto.jpg"              // 75 x 75

#define HARUFM_DEFAULT_IMAGE   \
    "http://haru.fm/userimages/default/large"           // 48 x 48
 // "http://haru.fm/userimages/default/small"           // 24 x 24

#define HATENAHAIKU_DEFAULT_IMAGE   \
    "http://www.hatena.ne.jp/users/re/register/profile.gif" // 64 x 64

#endif  /* __DEFAULT_IMAGE_H__ */
