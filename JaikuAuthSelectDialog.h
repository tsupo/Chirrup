/*
 * JaikuAuthSelectDialog.h  : Jaiku クライアント chirrup
 *      JaikuAuthSelectDialog クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  14 Apr 2009
 *
 *      Copyright (c) 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/JaikuAuthSelectDialog.h $
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
 * 1     09/04/14 23:36 Tsujimura543
 * 最初の版
 */

#if !defined(AFX_JAIKUAUTHSELECTDIALOG_H__311097BB_6721_4E4D_ADF7_CB435EE92C9D__INCLUDED_)
#define AFX_JAIKUAUTHSELECTDIALOG_H__311097BB_6721_4E4D_ADF7_CB435EE92C9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// JaikuAuthSelectDialog ダイアログ

class JaikuAuthSelectDialog : public CDialog
{
// コンストラクション
public:
	JaikuAuthSelectDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ
    ~JaikuAuthSelectDialog();

    bool    m_useOAuth;
    bool    m_useBASIC;
    CString m_oauthToken;
    CString m_oauthTokenSecret;

// ダイアログ データ
	//{{AFX_DATA(JaikuAuthSelectDialog)
	enum { IDD = IDD_JAIKU_AUTH_DIALOG };
	CString	m_username;
	CString	m_password;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(JaikuAuthSelectDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージ マップ関数
	//{{AFX_MSG(JaikuAuthSelectDialog)
	afx_msg void OnButtonGetToken();
	afx_msg void OnRadioBasic();
	afx_msg void OnRadioOauth();
	afx_msg void OnUrlJaikuApiKey();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    void    ShowCurrentStatus( bool rescan = false );

    HCURSOR m_hCursor;
    CFont   m_cFont;

private:
    JaikuAuthSelectDialog( JaikuAuthSelectDialog &dlg );
    JaikuAuthSelectDialog operator = ( JaikuAuthSelectDialog &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_JAIKUAUTHSELECTDIALOG_H__311097BB_6721_4E4D_ADF7_CB435EE92C9D__INCLUDED_)
