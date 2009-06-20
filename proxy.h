/*
 * proxy.h : Twitter クライアント chirrup
 *      プロクシ設定関連 ヘッダー ファイル
 *          written by H.Tsujimura  26 Nov 2007 / 13 Dec 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/proxy.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     07/12/20 16:36 Tsujimura543
 * 初期設定ファイルがまだ存在しない状態で起動したときにproxy設定処理が2回
 * 動いてしまう不具合を修正
 * 
 * 2     07/12/13 19:00 Tsujimura543
 * コメントを修正
 * 
 * 1     07/12/13 18:51 Tsujimura543
 * proxy関連のプロトタイプ宣言を chirrupDlg.h から分離独立させた
 */

#ifndef __PROXY_H__
#define __PROXY_H__

// proxy設定ダイアログを使った設定変更
void    DoSettingProxy( CChirrupDlg *p );

// proxy設定情報を新規設定あるいは設定変更する必要があると(xmlRPC.dll 内
// の http 通信関連関数群内で)判断されたときに呼び出される(呼び出してもら
// いたい)関数
int     confirmProxyInfo( int            *useProxy,
                          char           *proxyServer,
                          unsigned short *proxyPort,
                          char           *proxyUserName,
                          char           *proxyPassword );

#endif  /* __PROXY_H__ */
