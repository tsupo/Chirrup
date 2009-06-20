/*
 * BlogIDSelectDlg.h  : Twitter クライアント chirrup
 *      Blog ID 選択ダイアログ ヘッダーファイル
 *          written by H.Tsujimura  15 Oct 2004 / 2 Mar 2007 / 28 May 2009
 *
 *      Copyright (c) 2004, 2005, 2006, 2007, 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  「ここうさぎ」、「BloGolEe」、「bookey」で使っているソースコードを流用
 *
 * $Log: /comm/chirrup/BlogIDSelectDlg.h $
 * 
 * 1     09/05/31 20:28 tsupo
 * VSSサーバ拠点を変更
 * 
 * 1     09/05/29 18:24 Tsujimura543
 * Chirrup 向けの最初の版
 */

#if !defined(AFX_BLOGIDSELECTDLG_H__994887E0_5000_44BC_A119_29BDC0872BE1__INCLUDED_)
#define AFX_BLOGIDSELECTDLG_H__994887E0_5000_44BC_A119_29BDC0872BE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef __cplusplus
extern "C" {
#endif
#include "xmlRPC.h"
#ifdef __cplusplus
}
#endif

#define MAX_BLOG_NAME_LENGTH    MAX_BLOGNAMELENGTH

/////////////////////////////////////////////////////////////////////////////
// CBlogIDSelectDlg ダイアログ

class CBlogIDSelectDlg : public CDialog
{
// コンストラクション
private:
    BLOGINF *m_blogList;
    int     m_numOfBlogs;

    void    initBlogList( void );

public:
	CBlogIDSelectDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

    ~CBlogIDSelectDlg() {
        if ( m_blogList )
            delete [] m_blogList;
    }

    void    initialize( BLOGINF *blogList, int numOfBlogs );

// ダイアログ データ
	//{{AFX_DATA(CBlogIDSelectDlg)
	enum { IDD = IDD_BLOGID_DIALOG };
	CListBox	m_blogIDlist;
	int		m_blogIDlistIndex;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(CBlogIDSelectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(CBlogIDSelectDlg)
	virtual void OnOK();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSelchangeListBlogid();
	afx_msg void OnDblclkListBlogID();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_BLOGIDSELECTDLG_H__994887E0_5000_44BC_A119_29BDC0872BE1__INCLUDED_)
