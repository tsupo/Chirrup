/*
 * SettingHaruFm.h  : Twitter クライアント chirrup
 *      CSettingHaruFm クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  27 Jun 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/SettingHaruFm.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 1     07/06/27 14:11 Tsujimura543
 * 新規作成
 */

#if !defined(AFX_SETTINGHARUFM_H__96BD8761_6129_4B7F_A9B3_07EE821E884B__INCLUDED_)
#define AFX_SETTINGHARUFM_H__96BD8761_6129_4B7F_A9B3_07EE821E884B__INCLUDED_

#include "CTabDialog.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSettingHaruFm ダイアログ

class CSettingHaruFm : public CTabDialog
{
// コンストラクション
public:
	CSettingHaruFm(CWnd* pParent = NULL);   // 標準のコンストラクタ

    void    Accept();       // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    LoadSetting();  // 現在の「設定」を取得

// ダイアログ データ
	//{{AFX_DATA(CSettingHaruFm)
	enum { IDD = IDD_TAB_HARUFM };
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(CSettingHaruFm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(CSettingHaruFm)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CSettingHaruFm( CSettingHaruFm &dlg );
    CSettingHaruFm  operator = ( CSettingHaruFm &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGHARUFM_H__96BD8761_6129_4B7F_A9B3_07EE821E884B__INCLUDED_)
