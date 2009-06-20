/*
 * AboutDlg.h  : Twitter クライアント chirrup
 *      版数(バージョン番号)表示ダイアログ ヘッダーファイル
 *          written by H.Tsujimura  4 Apr 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/AboutDlg.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     07/09/06 19:46 Tsujimura543
 * 余分なコメントを削除
 * 
 * 2     07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 1     07/04/05 2:06 Tsujimura543
 * 最初の版
 */

#if !defined(AFX_CHIRRUP_H__AAFFDE06_EFA5_46F2_BCE5_AF68C87D0A07__INCLUDED_)
#define AFX_CHIRRUP_H__AAFFDE06_EFA5_46F2_BCE5_AF68C87D0A07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// アプリケーションのバージョン情報で使われている CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	~CAboutDlg();

    HCURSOR m_hCursor;
    CFont   m_cFont;

// ダイアログ データ
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnMailAddr();
	afx_msg void OnWebUrl();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CAboutDlg( CAboutDlg &dlg );
    CAboutDlg   operator = ( CAboutDlg &dlg );
};

#endif  // AFX_CHIRRUP_H__AAFFDE06_EFA5_46F2_BCE5_AF68C87D0A07__INCLUDED_
