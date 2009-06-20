/*
 * widechar.h  : Twitter クライアント chirrup
 *      文字化け対策ユーティリティ関数群 ヘッダーファイル
 *          written by H.Tsujimura  12 Dec 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/widechar.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 1     07/12/12 19:39 Tsujimura543
 * 最初の版
 */

#ifndef __WIDE_CHAR_H__
#define __WIDE_CHAR_H__

// UTF-8 には存在するが CP932 には存在しない文字について、
// 文字化け状態になるのを防ぐための関数

CString
RegulateCode(
    const char *orig, // (I) 対象文字列 (UTF-8)
    const char *conv  // (I) 対象文字列を iconv を使って CP932 に変換した結果
  );

#endif  /* __WIDE_CHAR_H__ */
