/*
 * SettingMogo2.h  : Twitter クライアント chirrup
 *      CSettingMogo2 クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  14 Jun 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/SettingMogo2.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 1     07/06/14 19:46 Tsujimura543
 * 新規作成
 */

#if !defined(AFX_SETTINGMOGO2_H__5BB4F9EC_25AE_4C92_97D0_C3EF0F2A3CF4__INCLUDED_)
#define AFX_SETTINGMOGO2_H__5BB4F9EC_25AE_4C92_97D0_C3EF0F2A3CF4__INCLUDED_

#include "CTabDialog.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSettingMogo2 ダイアログ

class CSettingMogo2 : public CTabDialog
{
// コンストラクション
public:
	CSettingMogo2(CWnd* pParent = NULL);   // 標準のコンストラクタ

    void    Accept();       // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    LoadSetting();  // 現在の「設定」を取得

// ダイアログ データ
	//{{AFX_DATA(CSettingMogo2)
	enum { IDD = IDD_TAB_MOGO2 };
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(CSettingMogo2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(CSettingMogo2)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CSettingMogo2( CSettingMogo2 &dlg );
    CSettingMogo2   operator = ( CSettingMogo2 &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGMOGO2_H__5BB4F9EC_25AE_4C92_97D0_C3EF0F2A3CF4__INCLUDED_)
