/*
 * CSettingUploadWassr.h  : Wassr クライアント chirrup
 *      CSettingUploadWassr クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  31 Jul 2008
 *
 *      Copyright (c) 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/SettingUploadWassr.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     08/07/31 20:30 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 2     08/07/31 20:26 Tsujimura543
 * 「状況に応じた入力可能/不可の切替処理」を修正
 * 
 * 1     08/07/31 17:34 Tsujimura543
 * 新規作成
 */

#if !defined(AFX_SETTINGUPLOADWASSR_H__B4430269_93D1_4DF9_ADCE_80A53556266B__INCLUDED_)
#define AFX_SETTINGUPLOADWASSR_H__B4430269_93D1_4DF9_ADCE_80A53556266B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSettingUploadWassr ダイアログ

class CSettingUploadWassr : public CDialog
{
// コンストラクション
public:
	CSettingUploadWassr(CWnd* pParent = NULL);   // 標準のコンストラクタ

    // ログファイル名設定
    void    InputFileName( CString &targetFilename, int id );

    // 画像アップロード対象とするか否かの設定
    void    SetCheckApplied();

    // ログファイルを残すか否かの設定
    void    SetCheckWriteLogfile();

// ダイアログ データ
	//{{AFX_DATA(CSettingUploadWassr)
	enum { IDD = IDD_SETTING_UPLOAD_WASSR };
	BOOL	m_applied;
	BOOL	m_writeLogfile;
	CString	m_logFilename;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(CSettingUploadWassr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(CSettingUploadWassr)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnWriteLogfile();
	afx_msg void OnButtonFilespec();
	afx_msg void OnApplied();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CSettingUploadWassr( CSettingUploadWassr &dlg );
    CSettingUploadWassr operator = ( CSettingUploadWassr &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGUPLOADWASSR_H__B4430269_93D1_4DF9_ADCE_80A53556266B__INCLUDED_)
