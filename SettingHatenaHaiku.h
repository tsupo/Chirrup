/*
 * SettingHatenaHaiku.h  : はてなハイク クライアント chirrup
 *      CSettingHatenaHaiku クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  22 Aug 2008
 *
 *      Copyright (c) 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/SettingHatenaHaiku.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 1     08/08/22 17:34 Tsujimura543
 * 新規作成
 */

#if !defined(AFX_SETTINGHATENAHAIKU_H__11A61EDE_FEEF_4A64_9643_8D36FDC8300F__INCLUDED_)
#define AFX_SETTINGHATENAHAIKU_H__11A61EDE_FEEF_4A64_9643_8D36FDC8300F__INCLUDED_

#include "CTabDialog.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSettingHatenaHaiku ダイアログ

class CSettingHatenaHaiku : public CTabDialog
{
// コンストラクション
public:
	CSettingHatenaHaiku(CWnd* pParent = NULL);   // 標準のコンストラクタ
    ~CSettingHatenaHaiku();

    void    Accept();       // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    LoadSetting();  // 現在の「設定」を取得

// ダイアログ データ
	//{{AFX_DATA(CSettingHatenaHaiku)
	enum { IDD = IDD_TAB_HATENAHAIKU };
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(CSettingHatenaHaiku)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(CSettingHatenaHaiku)
	afx_msg void OnUrlHatenaHaikuSetting();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    HCURSOR m_hCursor;
    CFont   m_cFont;

private:
    CSettingHatenaHaiku( CSettingHatenaHaiku &dlg );
    CSettingHatenaHaiku  operator = ( CSettingHatenaHaiku &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGHATENAHAIKU_H__11A61EDE_FEEF_4A64_9643_8D36FDC8300F__INCLUDED_)
