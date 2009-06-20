/*
 * chirrup.cpp : Twitter クライアント chirrup
 *      CChirrupApp 本体
 *          written by H.Tsujimura  4 Apr 2007
 *
 *      Copyright (c) 2007, 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/chirrup.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 12    09/04/28 20:52 Tsujimura543
 * タイムアウト取得処理が規定時間内に終わらない場合の処理を変更
 * (スレッド強制終了方式ではなく、イベント通知方式を採用)
 * 
 * 11    09/04/15 1:17 Tsujimura543
 * Jaiuku の OAuth 対応準備
 * 
 * 10    09/03/30 22:36 Tsujimura543
 * Twitter の OAuth 対応準備 その2
 * 
 * 9     09/03/30 22:19 Tsujimura543
 * Twitter の OAuth 対応準備
 * 
 * 8     08/09/16 17:40 Tsujimura543
 * 英語モード対応準備
 * 
 * 7     08/02/07 22:36 Tsujimura543
 * copyright 表示を修正 (2008 を追加)
 * 
 * 6     08/01/08 21:07 Tsujimura543
 * flickr 対応準備 (→ 08/01/09 22:27 対応完了)
 * 
 * 5     07/12/20 16:36 Tsujimura543
 * 初期設定ファイルがまだ存在しない状態で起動したときにproxy設定処理が2回
 * 動いてしまう不具合を修正
 * 
 * 4     07/12/17 19:52 Tsujimura543
 * capture 関連の変数、関数を CCapture クラスとしてまとめたことに伴う
 * 修正を実施
 * 
 * 3     07/09/06 19:46 Tsujimura543
 * 余分なコメントを削除
 * 
 * 2     07/04/27 22:28 Tsujimura543
 * プロクシ関連の設定を保持するメンバーを CChirrupApp に移動
 * 
 * 1     07/04/05 2:06 Tsujimura543
 * 最初の版
 */

#include "chirrup.h"
#include "AboutDlg.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/chirrup.cpp 1     09/05/14 3:50 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChirrupApp

BEGIN_MESSAGE_MAP(CChirrupApp, CWinApp)
	//{{AFX_MSG_MAP(CChirrupApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChirrupApp クラスの構築

CChirrupApp::CChirrupApp()
{
    LCID    langCode;
    m_langCode = langCode = getLanguageCode();
    if ( m_langCode != 0x0411 ) {
        m_langCode = 0x0409;  // 「日本語」以外の場合は強制的に「英語」にする
        if ( langCode != m_langCode )
            setLanguageCode( m_langCode );
    }

    m_isUsedProxy   = false;
    m_proxyServer   = _T("");
    m_proxyPort     = -1;
    m_proxyUserName = _T("");
    m_proxyPassword = _T("");
	m_chirrpDlg     = NULL;
    m_capture       = NULL;
    m_event         = NULL;

    m_fKey          = _T("");
    m_fSecret       = _T("");
    m_tcKey         = _T("");
    m_tcSecret      = _T("");
    m_jcKey         = _T("");
    m_jcSecret      = _T("");
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CChirrupApp オブジェクト

CChirrupApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CChirrupApp クラスの初期化

BOOL CChirrupApp::InitInstance()
{
	// 標準的な初期化処理
#ifdef _AFXDLL
	Enable3dControls();			// 共有 DLL 内で MFC を使う場合
#else
	Enable3dControlsStatic();	// MFC と静的にリンクする場合
#endif

	CChirrupDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	return FALSE;
}


#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
void CChirrupApp::WinHelp(DWORD dwData, UINT nCmd) 
{
 // CWinApp::WinHelp(dwData, nCmd);
}
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif

// ダイアログを実行するためのアプリケーション コマンド
void CChirrupApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
