/*
 * CTabDialog2.h : Twitter クライアント chirrup
 *      CTabDialog2 クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  10 Dec 2007 / 10 Jan 2008
 *
 *      Copyright (c) 2007, 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/CTabDialog2.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     08/01/10 17:20 Tsujimura543
 * コメントを修正
 * 
 * 1     08/01/10 17:19 Tsujimura543
 * 旧SettingGyazo.hを元に新規作成 (SettingGyazo, SettingFlickrの共通部分
 * を保持するクラスとして設計。今後の対応サービス増加を少しでも容易にす
 * る目的もあり)
 */

#ifndef __TAB_DIALOG2_H__
#define __TAB_DIALOG2_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTabDialog2 ダイアログ

class CTabDialog2 : public CDialog
{
// コンストラクション
public:
    CTabDialog2( UINT nIDTemplate, CWnd* pParentWnd = NULL );

    // 「設定ダイアログ」での「適用」ボタン押下時処理
    virtual void    Accept() = 0;

    // 現在の「設定」を取得
    virtual void    LoadSetting() = 0;

    // ログファイル名設定
    void    InputFileName( CString &targetFilename, int id );

    // 画像アップロード対象とするか否かの設定
    void    SetCheckApplied();

    // ログファイルを残すか否かの設定
    void    SetCheckWriteLogfile();

    CChirrupDlg *m_chirrup;

// ダイアログ データ
	//{{AFX_DATA(CTabDialog2)
	BOOL	m_applied;
	BOOL	m_writeLogfile;
	CString	m_logFilename;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(CTabDialog2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
    bool    m_initialized;

	// メッセージ マップ関数
	//{{AFX_MSG(CTabDialog2)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnButtonFilespec();
	afx_msg void OnApplied();
	afx_msg void OnWriteLogfile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif  /* __TAB_DIALOG2_H__ */
