/*
 * chirrup.h  : Twitter クライアント chirrup
 *      メインヘッダーファイル
 *          written by H.Tsujimura  4 Apr 2007
 *
 *      Copyright (c) 2007, 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/chirrup.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 14    09/04/28 20:52 Tsujimura543
 * タイムアウト取得処理が規定時間内に終わらない場合の処理を変更
 * (スレッド強制終了方式ではなく、イベント通知方式を採用)
 * 
 * 13    09/04/15 1:17 Tsujimura543
 * Jaiuku の OAuth 対応準備
 * 
 * 12    09/03/30 22:36 Tsujimura543
 * Twitter の OAuth 対応準備 その2
 * 
 * 11    09/03/30 22:19 Tsujimura543
 * Twitter の OAuth 対応準備
 * 
 * 10    08/09/16 17:40 Tsujimura543
 * 英語モード対応準備
 * 
 * 9     08/02/07 22:36 Tsujimura543
 * copyright 表示を修正 (2008 を追加)
 * 
 * 8     08/01/08 21:07 Tsujimura543
 * flickr 対応準備 (→ 08/01/09 22:27 対応完了)
 * 
 * 7     07/12/20 16:36 Tsujimura543
 * 初期設定ファイルがまだ存在しない状態で起動したときにproxy設定処理が2回
 * 動いてしまう不具合を修正
 * 
 * 6     07/12/17 19:52 Tsujimura543
 * capture 関連の変数、関数を CCapture クラスとしてまとめたことに伴う
 * 修正を実施
 * 
 * 5     07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 4     07/05/11 21:29 Tsujimura543
 * ブラウザで閲覧中の URL を Twitter に送信するとき、その Web ページの
 * タイトルも取得して送信するようにした
 * 
 * 3     07/04/27 19:37 Tsujimura543
 * Twitter API 関連の構造体の定義を Twitter.h へ移動
 * 
 * 2     07/04/24 23:48 Tsujimura543
 * GetUrlInBrowsing() のプロトタイプ宣言を追加
 * 
 * 1     07/04/05 2:06 Tsujimura543
 * 最初の版
 */

#if !defined(AFX_CHIRRUP_H__AAFFDE06_EFA5_46F2_BCE5_C7315B7175AC__INCLUDED_)
#define AFX_CHIRRUP_H__AAFFDE06_EFA5_46F2_BCE5_C7315B7175AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Windows ヘッダーから殆ど使用されないスタッフを除外します。

#ifdef  _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include <afxwin.h>         // MFC のコアおよび標準コンポーネント
#include <afxext.h>         // MFC の拡張部分
#include <afxdtctl.h>		// MFC の Internet Explorer 4 コモン コントロール サポート
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC の Windows コモン コントロール サポート
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "resource.h"		// メイン シンボル
#include "Twitter.h"
#include "chirrupDlg.h"
#include "capture.h"

CString GetUrlInBrowsing( CString &pageTitle );

/////////////////////////////////////////////////////////////////////////////
// CChirrupApp  アプリケーション メイン

class CChirrupApp : public CWinApp
{
public:
	CChirrupApp();

// オーバーライド
	//{{AFX_VIRTUAL(CChirrupApp)
	public:
	virtual BOOL InitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

// インプリメンテーション
    bool        m_isUsedProxy;      // proxy を使うか否か
    CString     m_proxyServer;      // proxy サーバ名
    long        m_proxyPort;        // proxy ポート番号
    CString     m_proxyUserName;    // proxy ユーザ名
    CString     m_proxyPassword;    // proxy パスワード

    CString     m_fKey;
    CString     m_fSecret;
    CString     m_tcKey;
    CString     m_tcSecret;
    CString     m_jcKey;
    CString     m_jcSecret;

	CChirrupDlg	*m_chirrpDlg;
    CCapture    *m_capture;

    HANDLE  m_event;

    LCID    m_langCode; // 言語(0x0409: 英語(アメリカ), 0x0411: 日本語, ……)

	//{{AFX_MSG(CChirrupApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CChirrupApp( CChirrupApp &obj );
    CChirrupApp operator = ( CChirrupApp &obj );
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_CHIRRUP_H__AAFFDE06_EFA5_46F2_BCE5_C7315B7175AC__INCLUDED_)
