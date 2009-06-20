/*
 * twitStar.h : Twitter クライアント chirrup
 *      ついすた関連 ヘッダーファイル
 *          written by H.Tsujimura  24 Aug 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/twitStar.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 1     07/08/24 22:29 Tsujimura543
 * 最初の版
 */

#ifndef __TWIT_STAR_H__
#define __TWIT_STAR_H__

// targetURL で指定したWebページに ☆ をつける
BOOL
setHatenaStar( const char *targetURL,   // (I) ☆をつけたいWebページURL
               const char *username,    // (I) はてなID
               const char *password );  // (I) パスワード

#endif  /* __TWIT_STAR_H__ */
