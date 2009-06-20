/*
 * SettingTwitter.h  : Twitter クライアント chirrup
 *      CSettingTwitter クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  7 Jun 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/SettingTwitter.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 8     09/03/31 21:27 Tsujimura543
 * Twitter の OAuth 対応準備 その5
 * 
 * 7     09/03/30 22:37 Tsujimura543
 * Twitter の OAuth 対応準備 その2
 * 
 * 6     07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 5     07/06/13 19:18 Tsujimura543
 * Twitter の Replies の閲覧、ログ出力に対応
 * 
 * 4     07/06/12 17:51 Tsujimura543
 * Twitter と Jaiku で共通化できる部分は共通化し、共通化した部分を
 * CTabDialog に移管
 * 
 * 3     07/06/11 18:39 Tsujimura543
 * Twitter の user_timeline の閲覧をサポート
 * 
 * 2     07/06/07 15:47 Tsujimura543
 * CTabDialog を導入、コードを整理してみた
 * 
 * 1     07/06/07 1:43 Tsujimura543
 * 新規作成 (タブ選択形式の設定ダイアログを新たに用意した)
 */

#if !defined(AFX_SETTINGTWITTER_H__A5999D22_180C_4DC7_BE21_5763B2A73D67__INCLUDED_)
#define AFX_SETTINGTWITTER_H__A5999D22_180C_4DC7_BE21_5763B2A73D67__INCLUDED_

#include "CTabDialog.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSettingTwitter ダイアログ

class CSettingTwitter : public CTabDialog
{
// コンストラクション
public:
	CSettingTwitter(CWnd* pParent = NULL);   // 標準のコンストラクタ

    void    Accept();       // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    LoadSetting();  // 現在の「設定」を取得

    bool    m_useOAuth;
    bool    m_useBASIC;
    CString m_oauthToken;
    CString m_oauthTokenSecret;

// ダイアログ データ
	//{{AFX_DATA(CSettingTwitter)
	enum { IDD = IDD_TAB_TWITTER };
	CString	m_logFile_replies;
	BOOL	m_checkReplies;
	BOOL	m_checkLogFileReplies;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(CSettingTwitter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(CSettingTwitter)
	afx_msg void OnButtonFilespec4();
	afx_msg void OnCheckReplies();
	afx_msg void OnCheckReplies2();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnButtonSetAuth();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    void    SetCheckReplies();
    void    ShowCurrentStatus();

private:
    CSettingTwitter( CSettingTwitter &dlg );
    CSettingTwitter operator = ( CSettingTwitter &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGTWITTER_H__A5999D22_180C_4DC7_BE21_5763B2A73D67__INCLUDED_)
