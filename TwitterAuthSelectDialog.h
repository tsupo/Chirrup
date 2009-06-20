/*
 * TwitterAuthSelectDialog.h  : Twitter クライアント chirrup
 *      TwitterAuthSelectDialog クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  31 Mar 2009
 *
 *      Copyright (c) 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/TwitterAuthSelectDialog.h $
 * 
 * 2     09/05/15 2:34 tsupo
 * 「1.140版→1.141版」での変更点を取り込む
 * 
 * 2     09/05/14 14:52 Tsujimura543
 * ユーザ名未設定状態で本ダイアログを起動したとき、ユーザ名を入力後、
 * ラジオボタンをクリックすると、ユーザ名の欄がクリアされてしまう不具合
 * に対処
 *
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 1     09/03/31 20:12 Tsujimura543
 * 最初の版
 */

#if !defined(AFX_TWITTERAUTHSELECTDIALOG_H__3AF04211_4EFA_4331_B597_3226D621FF1E__INCLUDED_)
#define AFX_TWITTERAUTHSELECTDIALOG_H__3AF04211_4EFA_4331_B597_3226D621FF1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// TwitterAuthSelectDialog ダイアログ

class TwitterAuthSelectDialog : public CDialog
{
// コンストラクション
public:
	TwitterAuthSelectDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

    bool    m_useOAuth;
    bool    m_useBASIC;
    CString m_oauthToken;
    CString m_oauthTokenSecret;

// ダイアログ データ
	//{{AFX_DATA(TwitterAuthSelectDialog)
	enum { IDD = IDD_TWITTER_AUTH_DIALOG };
	CString	m_username;
	CString	m_password;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(TwitterAuthSelectDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージ マップ関数
	//{{AFX_MSG(TwitterAuthSelectDialog)
	afx_msg void OnButtonGetToken();
	afx_msg void OnRadioBasic();
	afx_msg void OnRadioOauth();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    void    ShowCurrentStatus( bool rescan = false );

private:
    TwitterAuthSelectDialog( TwitterAuthSelectDialog &dlg );
    TwitterAuthSelectDialog operator = ( TwitterAuthSelectDialog &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_TWITTERAUTHSELECTDIALOG_H__3AF04211_4EFA_4331_B597_3226D621FF1E__INCLUDED_)
