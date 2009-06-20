/*
 * SettingHatena.h  : Twitter クライアント chirrup
 *      CSettingHatena クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  24 Aug 2007
 *
 *      Copyright (c) 2007, 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/SettingHatena.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     08/01/19 2:10 Tsujimura543
 * はてなフォトライフ対応
 * 
 * 2     07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 1     07/08/25 0:14 Tsujimura543
 * 最初の版
 */

#if !defined(AFX_SETTINGHATENA_H__451793F9_B9B5_4484_83A7_EC89547F4438__INCLUDED_)
#define AFX_SETTINGHATENA_H__451793F9_B9B5_4484_83A7_EC89547F4438__INCLUDED_

#include "CTabDialog2.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSettingHatena ダイアログ

class CSettingHatena : public CTabDialog2
{
// コンストラクション
public:
	CSettingHatena(CWnd* pParent = NULL);   // 標準のコンストラクタ

    // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    Accept();

    // 現在の「設定」を取得
    void    LoadSetting();

    void    SetCheckApplied();

// ダイアログ データ
	//{{AFX_DATA(CSettingHatena)
	enum { IDD = IDD_TAB_HATENA };
	BOOL	m_useTwitStar;
	CString	m_username;
	CString	m_password;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(CSettingHatena)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(CSettingHatena)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnUseTwitstar();
	afx_msg void OnApplied();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CSettingHatena( CSettingHatena &dlg );
    CSettingHatena  operator = ( CSettingHatena &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGHATENA_H__451793F9_B9B5_4484_83A7_EC89547F4438__INCLUDED_)
