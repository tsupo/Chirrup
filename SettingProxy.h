/*
 * SettingProxy.h  : Twitter クライアント chirrup
 *      CSettingProxy クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  9 Mar 2007 / 6 Apr 2007 / 26 Nov 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/SettingProxy.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     08/12/19 20:50 Tsujimura543
 * UpdateDataEx() を追加
 * 
 * 3     07/11/26 18:04 Tsujimura543
 * proxy設定関連移行作業、完了
 * 
 * 2     07/11/26 17:57 Tsujimura543
 * CProxyInfoDialog を廃止し、CSettingProxy に移行
 * 
 * 1     07/11/26 17:30 Tsujimura543
 * 最初の版
 */

#if !defined(AFX_SETTINGPROXY_H__EDD3BA49_903D_45FF_8677_BEF6EFAF382B__INCLUDED_)
#define AFX_SETTINGPROXY_H__EDD3BA49_903D_45FF_8677_BEF6EFAF382B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSettingProxy ダイアログ

class CSettingProxy : public CDialog
{
// コンストラクション
public:
	CSettingProxy(CWnd* pParent = NULL);   // 標準のコンストラクタ

    // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    Accept();

    // 現在の「設定」を取得
    void    LoadSetting();

    // 設定しようとしている値のチェック
    BOOL    UpdateDataEx();

    CChirrupDlg *m_chirrup;

// ダイアログ データ
	//{{AFX_DATA(CSettingProxy)
	enum { IDD = IDD_TAB_PROXY };
	BOOL	m_useProxy;
	CString	m_proxyServerName;
	UINT	m_proxyPortNumber;
	CString	m_proxyUserName;
	CString	m_proxyPassword;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(CSettingProxy)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
    bool    m_initialized;

	// メッセージ マップ関数
	//{{AFX_MSG(CSettingProxy)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnUseProxy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    void SetCheckProxy();
    CSettingProxy( CSettingProxy &dlg );
    CSettingProxy   operator = ( CSettingProxy &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGPROXY_H__EDD3BA49_903D_45FF_8677_BEF6EFAF382B__INCLUDED_)
