/*
 * SettingJaiku.h  : Twitter クライアント chirrup
 *      CSettingJaiku クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  7 Jun 2007
 *
 *      Copyright (c) 2007, 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/SettingJaiku.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 6     09/04/15 1:17 Tsujimura543
 * Jaiuku の OAuth 対応準備
 * 
 * 5     07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 4     07/08/31 19:22 Tsujimura543
 * 「personal_key の取得方法」に関するヒントを表示するようにした
 * 
 * 3     07/06/12 17:51 Tsujimura543
 * Twitter と Jaiku で共通化できる部分は共通化し、共通化した部分を
 * CTabDialog に移管
 * 
 * 2     07/06/07 15:47 Tsujimura543
 * CTabDialog を導入、コードを整理してみた
 * 
 * 1     07/06/07 1:43 Tsujimura543
 * 新規作成 (タブ選択形式の設定ダイアログを新たに用意した)
 */

#if !defined(AFX_SETTINGJAIKU_H__2BDA6908_8B32_443C_917D_B20CB677A6CB__INCLUDED_)
#define AFX_SETTINGJAIKU_H__2BDA6908_8B32_443C_917D_B20CB677A6CB__INCLUDED_

#include "CTabDialog.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSettingJaiku ダイアログ

class CSettingJaiku : public CTabDialog
{
// コンストラクション
public:
	CSettingJaiku(CWnd* pParent = NULL);   // 標準のコンストラクタ

    void    Accept();       // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    LoadSetting();  // 現在の「設定」を取得

    bool    m_useOAuth;
    bool    m_useBASIC;
    CString m_oauthToken;
    CString m_oauthTokenSecret;

// ダイアログ データ
	//{{AFX_DATA(CSettingJaiku)
	enum { IDD = IDD_TAB_JAIKU };
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(CSettingJaiku)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(CSettingJaiku)
	afx_msg void OnButtonSetAuth();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    void    ShowCurrentStatus();

private:
    CSettingJaiku( CSettingJaiku &dlg );
    CSettingJaiku   operator = ( CSettingJaiku &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGJAIKU_H__2BDA6908_8B32_443C_917D_B20CB677A6CB__INCLUDED_)
