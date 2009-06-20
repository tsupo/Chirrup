/*
 * TumblrEditDialog.h  : Twitter クライアント chirrup
 *      Tumblr(の Quote)投稿内容編集ダイアログ ヘッダーファイル
 *          written by H.Tsujimura  6 Nov 2007
 *
 *      Copyright (c) 2007, 2008, 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/TumblrEditDialog.h $
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
 * 4     09/03/12 19:26 Tsujimura543
 * CTumblrEditDialog ダイアログを二重起動できないようにした
 * 
 * 3     09/03/10 17:48 Tsujimura543
 * CTumblrEditDialog をモーダルダイアログからモードレスダイアログに変更
 * 
 * 2     08/02/12 23:21 Tsujimura543
 * 「コメント」欄を追加
 * 
 * 1     07/11/06 21:46 Tsujimura543
 * 最初の版
 */

#if !defined(AFX_TUMBLREDITDIALOG_H__E83ADE31_D70F_49F6_B5DE_467FFA1F4EA3__INCLUDED_)
#define AFX_TUMBLREDITDIALOG_H__E83ADE31_D70F_49F6_B5DE_467FFA1F4EA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTumblrEditDialog ダイアログ

class CTumblrEditDialog : public CDialog
{
// コンストラクション
protected:
	CTumblrEditDialog(CWnd* pParent = NULL);

public:
    static CTumblrEditDialog    *Instance();

// ダイアログ データ
	//{{AFX_DATA(CTumblrEditDialog)
	enum { IDD = IDD_TUMBLR_DIALOG };
	CString	m_quote;
	CString	m_title;
	CString	m_url;
	CString	m_comment;
	//}}AFX_DATA

    CString m_tumblrID;
    CString m_tumblrPassword;
    CString m_tumblrGroup;

// オーバーライド
	//{{AFX_VIRTUAL(CTumblrEditDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CTumblrEditDialog)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CTumblrEditDialog( CTumblrEditDialog &dlg );
    CTumblrEditDialog   operator = ( CTumblrEditDialog &dlg );

    static CTumblrEditDialog    *m_instance;
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_TUMBLREDITDIALOG_H__E83ADE31_D70F_49F6_B5DE_467FFA1F4EA3__INCLUDED_)
