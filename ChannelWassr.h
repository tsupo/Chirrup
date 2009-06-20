/*
 * CChannelWassr.h  : Wassr クライアント chirrup
 *      CChannelWassr クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  1 Aug 2008
 *
 *      Copyright (c) 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/ChannelWassr.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 1     08/08/02 3:40 Tsujimura543
 * 新規作成 (今のところ、単に一覧表示するだけの機能しかない)
 */

#if !defined(AFX_CHANNELWASSR_H__F80A6B8A_FB03_481D_B4E3_E616BAE9EC11__INCLUDED_)
#define AFX_CHANNELWASSR_H__F80A6B8A_FB03_481D_B4E3_E616BAE9EC11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChannelWassr ダイアログ

class CChannelWassr : public CDialog
{
// コンストラクション
public:
	CChannelWassr(CWnd* pParent = NULL);   // 標準のコンストラクタ
    ~CChannelWassr();

    WASSR_CHANNEL_LIST  *m_wassrChannelList;
    long                m_numOfChannels;

// ダイアログ データ
	//{{AFX_DATA(CChannelWassr)
	enum { IDD = IDD_CHANNEL_WASSR };
	CListCtrl	m_listCtr;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(CChannelWassr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
#define CHNLLST_NUM_OF_COLUMNS   2

    CImageList  m_imglst;
    long        m_numOfColumns;

    _TCHAR      *m_columnLabel[CHNLLST_NUM_OF_COLUMNS];
    int         m_columnFmt[CHNLLST_NUM_OF_COLUMNS];
    int         m_columnWidth[CHNLLST_NUM_OF_COLUMNS];

	// メッセージマップ関数
	//{{AFX_MSG(CChannelWassr)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_CHANNELWASSR_H__F80A6B8A_FB03_481D_B4E3_E616BAE9EC11__INCLUDED_)
