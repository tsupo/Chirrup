/*
 * utility.h  : Twitter クライアント chirrup
 *      各種ユーティリティ関数群 ヘッダーファイル
 *          written by H.Tsujimura  4 Apr 2007
 *
 *      Copyright (c) 2007, 2008, 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/utility.h $
 * 
 * 2     09/05/31 20:42 tsupo
 * 1.142版
 * 
 * 12    09/05/27 19:35 Tsujimura543
 * setSigInfo() を削除 (xmlRPC.dll へ移管)
 * 
 * 11    09/05/27 18:21 Tsujimura543
 * setSigInfo() の引数を追加
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 10    08/02/14 22:41 Tsujimura543
 * replaceStringEx() を追加
 * 
 * 9     08/02/14 20:01 Tsujimura543
 * replaceString() を追加
 * 
 * 8     08/01/08 21:06 Tsujimura543
 * コメントを修正
 * 
 * 7     08/01/08 21:04 Tsujimura543
 * setSigInfo() を追加
 * 
 * 6     07/11/08 23:52 Tsujimura543
 * any2utf() のプロトタイプ宣言を追加
 * 
 * 5     07/06/21 18:08 Tsujimura543
 * cutExtra() を追加
 * 
 * 4     07/05/11 21:27 Tsujimura543
 * normalizeDescription() と getTitle() を追加
 * 
 * 3     07/04/27 16:37 Tsujimura543
 * コメントを修正
 * 
 * 2     07/04/24 23:48 Tsujimura543
 * CFriendDialog 向けユーティリティ関数を追加 (将来は他でも使う予定)
 * 
 * 1     07/04/05 2:06 Tsujimura543
 * 最初の版
 */

#ifndef __UTILITY_H__
#define __UTILITY_H__

char    *
convUnicode( unsigned long code );

char    *
decodeContents( char *contents );

char    *
decodeNumericReference( char *src );

char    *
any2sjis( const char *p );

char    *
cutExtra( char *s );

time_t
getDateTimeFromDateString(
        const char *date,   /* (I) 日時情報(文字列) */
        int        *yyyy,   /* (O) 年               */
        int        *mm,     /* (O) 月               */
        int        *dd,     /* (O) 日               */
        int        *HH,     /* (O) 時               */
        int        *MM,     /* (O) 分               */
        int        *SS      /* (O) 秒               */
    );

time_t
timelocal( struct tm *tm );

char    *
encodeDateTime( const char *str );

char    *
getLastStatus( const char *screenName, char *lastStatus );

char    *
addCarriageReturn( char *str, int loc );

char *
normalizeDescription( char *description, size_t length );

char    *
getTitle(const char *url );

char    *
any2utf( const char *p );

BOOL
replaceString( char *target, const char *src, const char *dst );

BOOL
replaceStringEx( char *target );

#ifndef	iskanji1
#define	iskanji1(s)	((((s)>=0x81) && ((s)<=0x9f)) || \
			 (((s)>=0xe0) && ((s)<=0xfc)))
#endif
#ifndef	iskanji2
#define	iskanji2(s)	((((s)>=0x40) && ((s)<=0x7e)) || \
			 (((s)>=0x80) && ((s)<=0xfc)))
#endif

#endif  /* __UTILITY_H__ */
