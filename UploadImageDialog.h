/*
 * TumblrEditDialog.h  : Twitter クライアント chirrup
 *      画像ファイルアップロードダイアログ ヘッダーファイル
 *          written by H.Tsujimura  6 Dec 2007
 *
 *      Copyright (c) 2007, 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/UploadImageDialog.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 7     08/07/31 21:12 Tsujimura543
 * Wassr へのアップロードに対応
 * 
 * 6     08/02/07 22:36 Tsujimura543
 * copyright 表示を修正 (2008 を追加)
 * 
 * 5     08/01/24 14:46 Tsujimura543
 * 同時投稿対象切り替え機能を実装
 * 
 * 4     07/12/19 13:26 Tsujimura543
 * アップロードしようとしている画像ファイルのプレビュー表示を追加
 * 
 * 3     07/12/10 21:26 Tsujimura543
 * m_targetName を追加
 * 
 * 2     07/12/06 4:08 Tsujimura543
 * 余分なコメントを削除
 * 
 * 1     07/12/06 4:07 Tsujimura543
 * 新規作成
 */

#if !defined(AFX_UPLOADIMAGEDIALOG_H__611D9141_FB80_42D5_8B21_EB7984C25B3A__INCLUDED_)
#define AFX_UPLOADIMAGEDIALOG_H__611D9141_FB80_42D5_8B21_EB7984C25B3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUploadImageDialog ダイアログ

class CUploadImageDialog : public CDialog
{
// コンストラクション
public:
	CUploadImageDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ
    ~CUploadImageDialog();

    CString m_targetName;

    bool    m_gyazo;
    bool    m_flickr;
    bool    m_tumblr;
    bool    m_hatenaFotolife;
    bool    m_wassr;

    bool    m_sim_gyazo;
    bool    m_sim_flickr;
    bool    m_sim_tumblr;
    bool    m_sim_hatenaFotolife;
    bool    m_sim_wassr;

// ダイアログ データ
	//{{AFX_DATA(CUploadImageDialog)
	enum { IDD = IDD_UPLOAD_IMAGE_DIALOG };
	CString	m_filename;
	CString	m_caption;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(CUploadImageDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
    HBITMAP m_bitmap;
    HCURSOR m_hCursor;

    bool    IsInner( int id, WORD wX, WORD wY );
    void    SetStaticEdge( int idx, bool status );

	// メッセージ マップ関数
	//{{AFX_MSG(CUploadImageDialog)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnDisplayToolTip(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_UPLOADIMAGEDIALOG_H__611D9141_FB80_42D5_8B21_EB7984C25B3A__INCLUDED_)
