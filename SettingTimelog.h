/*
 * SettingTimelog.h  : Twitter クライアント chirrup
 *      CSettingTimelog クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  20 Jun 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/SettingTimelog.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 2     07/06/20 11:21 Tsujimura543
 * 余分な行を削除
 * 
 * 1     07/06/20 11:20 Tsujimura543
 * 新規作成
 */

#if !defined(AFX_SETTINGTIMELOG_H__F048AB2C_F829_4B57_B7E8_03140C24D958__INCLUDED_)
#define AFX_SETTINGTIMELOG_H__F048AB2C_F829_4B57_B7E8_03140C24D958__INCLUDED_

#include "CTabDialog.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSettingTimelog ダイアログ

class CSettingTimelog : public CTabDialog
{
// コンストラクション
public:
	CSettingTimelog(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CSettingTimelog)
	enum { IDD = IDD_TAB_TIMELOG };
	//}}AFX_DATA

    void    Accept();       // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    LoadSetting();  // 現在の「設定」を取得

// オーバーライド
	//{{AFX_VIRTUAL(CSettingTimelog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(CSettingTimelog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CSettingTimelog( CSettingTimelog &dlg );
    CSettingTimelog operator = ( CSettingTimelog &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGTIMELOG_H__F048AB2C_F829_4B57_B7E8_03140C24D958__INCLUDED_)
