/*
 * SettingGyazo.h  : Twitter クライアント chirrup
 *      CSettingGyazo クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  10 Dec 2007
 *
 *      Copyright (c) 2007, 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/SettingGyazo.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     08/01/10 17:22 Tsujimura543
 * CTabDialog2 を導入し、ソースコードを整理した
 * 
 * 2     07/12/19 16:12 Tsujimura543
 * Tumblr と Gyazo にアップロードしたファイルの URL を記録する機能を
 * 追加するためのプロパティを追加
 * 
 * 1     07/12/10 16:38 Tsujimura543
 * 新規作成
 */

#if !defined(AFX_SETTINGGYAZO_H__AF2C6374_830A_4ECF_AEE2_4FEF0B416342__INCLUDED_)
#define AFX_SETTINGGYAZO_H__AF2C6374_830A_4ECF_AEE2_4FEF0B416342__INCLUDED_

#include "CTabDialog2.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSettingGyazo ダイアログ

class CSettingGyazo : public CTabDialog2
{
// コンストラクション
public:
	CSettingGyazo(CWnd* pParent = NULL);   // 標準のコンストラクタ

    // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    Accept();

    // 現在の「設定」を取得
    void    LoadSetting();

// ダイアログ データ
	//{{AFX_DATA(CSettingGyazo)
	enum { IDD = IDD_TAB_GYAZO };
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(CSettingGyazo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージ マップ関数
	//{{AFX_MSG(CSettingGyazo)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CSettingGyazo( CSettingGyazo &dlg );
    CSettingGyazo   operator = ( CSettingGyazo &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGGYAZO_H__AF2C6374_830A_4ECF_AEE2_4FEF0B416342__INCLUDED_)
