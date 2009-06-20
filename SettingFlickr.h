/*
 * SettingFlickr.h  : Twitter クライアント chirrup
 *      CSettingFlickr クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  9 Jan 2008
 *
 *      Copyright (c) 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/SettingFlickr.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     09/04/22 21:11 Tsujimura543
 * 「設定」ダイアログからもFlickr認証のアクセストークン(frob)を取得できる
 * ようにした
 * 
 * 3     08/01/10 17:51 Tsujimura543
 * 継承ミスを修正
 * 
 * 2     08/01/10 17:22 Tsujimura543
 * CTabDialog2 を導入し、ソースコードを整理した
 * 
 * 1     08/01/09 17:07 Tsujimura543
 * 新規作成
 */

#if !defined(AFX_SETTINGFLICKR_H__5F242F58_0C7D_4E75_96E1_1FE9DDBBDEAC__INCLUDED_)
#define AFX_SETTINGFLICKR_H__5F242F58_0C7D_4E75_96E1_1FE9DDBBDEAC__INCLUDED_

#include "CTabDialog2.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSettingFlickr ダイアログ

class CSettingFlickr : public CTabDialog2
{
// コンストラクション
public:
	CSettingFlickr(CWnd* pParent = NULL);   // 標準のコンストラクタ

    // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    Accept();

    // 現在の「設定」を取得
    void    LoadSetting();

    CString m_flickrToken;
    CString m_flickrUserName;

// ダイアログ データ
	//{{AFX_DATA(CSettingFlickr)
	enum { IDD = IDD_TAB_FLICKR };
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(CSettingFlickr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージ マップ関数
	//{{AFX_MSG(CSettingFlickr)
	afx_msg void OnButtonGetToken();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    void    ShowCurrentStatus();

private:
    CSettingFlickr( CSettingFlickr &dlg );
    CSettingFlickr  operator = ( CSettingFlickr &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGFLICKR_H__5F242F58_0C7D_4E75_96E1_1FE9DDBBDEAC__INCLUDED_)
