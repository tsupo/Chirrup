/*
 * SettingTumblr.h  : Twitter クライアント chirrup
 *      CSettingTumblr クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  5 Nov 2007
 *
 *      Copyright (c) 2007, 2008, 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/SettingTumblr.h $
 * 
 * 2     09/05/31 20:42 tsupo
 * 1.142版
 * 
 * 5     09/05/29 19:22 Tsujimura543
 * 同一アカウントで複数 tumbleblog を開設している場合の投稿先
 * tumbleblog を指定しての投稿を可能にした
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     08/01/10 19:21 Tsujimura543
 * CTabDialog2 を導入、コードを整理した
 * 
 * 3     07/12/19 16:12 Tsujimura543
 * Tumblr と Gyazo にアップロードしたファイルの URL を記録する機能を
 * 追加するためのプロパティを追加
 * 
 * 2     07/12/06 1:58 Tsujimura543
 * tumblr への画像の投稿に対応
 * 
 * 1     07/11/05 23:35 Tsujimura543
 * 最初の版
 */

#if !defined(AFX_SETTINGTUMBLR_H__CF4D808A_A0F4_40A0_8135_31141219E2A6__INCLUDED_)
#define AFX_SETTINGTUMBLR_H__CF4D808A_A0F4_40A0_8135_31141219E2A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CTabDialog2.h"

#define MAX_BLOGS       30  /* 暫定値 */

/////////////////////////////////////////////////////////////////////////////
// CSettingTumblr ダイアログ

class CSettingTumblr : public CTabDialog2
{
// コンストラクション
public:
	CSettingTumblr(CWnd* pParent = NULL);   // 標準のコンストラクタ

    // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    Accept();

    // 現在の「設定」を取得
    void    LoadSetting();

    void    SetCheckApplied();

    CString m_blogID;

// ダイアログ データ
	//{{AFX_DATA(CSettingTumblr)
	enum { IDD = IDD_TAB_TUMBLR };
	BOOL	m_useTumblr;
	CString	m_username;
	CString	m_password;
	CString	m_blogName;
	//}}AFX_DATA

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSettingTumblr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSettingTumblr)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnUseTumblr();
	afx_msg void OnApplied();
	afx_msg void OnButtonSelectTarget();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CSettingTumblr( CSettingTumblr &dlg );
    CSettingTumblr  operator = ( CSettingTumblr &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGTUMBLR_H__CF4D808A_A0F4_40A0_8135_31141219E2A6__INCLUDED_)
