/*
 * ProceedingDialog.h  : Twitter クライアント chirrup
 *      進行状況表示ダイアログ ヘッダーファイル
 *          written by H.Tsujimura  10 Nov 2005 / 4 Apr 2007
 *
 *  「ソーシャルブックマーク管理プログラム」で使っているソースコードを
 *  そのまま流用
 *
 * $Log: /comm/chirrup/ProceedingDialog.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 1     07/04/05 2:06 Tsujimura543
 * 最初の版
 * 
 * ------------------------------------------------------------------------
 * 以下は、bookey/ProceedingDialog.h の変更履歴
 * ------------------------------------------------------------------------
 * 2     06/07/03 23:37 Tsujimura543
 * ProceedingDialog の DestroyWindow() 時に例外が発生することがある件の
 * 暫定対処を実施 (デバッグ版でしか発生しない?)
 * 
 * 1     05/11/10 21:17 Tsujimura543
 * 新規作成
 */

#if !defined(AFX_PROCEEDINGDIALOG_H__3176E431_89B4_48A3_B3B0_030CF818F828__INCLUDED_)
#define AFX_PROCEEDINGDIALOG_H__3176E431_89B4_48A3_B3B0_030CF818F828__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// ProceedingDialog ダイアログ

class ProceedingDialog : public CDialog
{
// コンストラクション
public:
	ProceedingDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ
    void    ChangeDialogText( const char *title, const char *message );
    void    ResetDialogText();

// ダイアログ データ
	//{{AFX_DATA(ProceedingDialog)
	enum { IDD = IDD_PROCEEDING_DIALOG };
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(ProceedingDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(ProceedingDialog)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    ProceedingDialog( ProceedingDialog &dlg );
    ProceedingDialog  operator = ( ProceedingDialog &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_PROCEEDINGDIALOG_H__3176E431_89B4_48A3_B3B0_030CF818F828__INCLUDED_)
