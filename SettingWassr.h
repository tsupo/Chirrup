/*
 * SettingWassr.h  : Twitter クライアント chirrup
 *      CSettingWassr クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  14 Jun 2007
 *
 *      Copyright (c) 2007, 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/SettingWassr.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 5     08/07/31 20:59 Tsujimura543
 * SetCheckFriendsTimeline() を追加
 * 
 * 4     08/07/31 19:34 Tsujimura543
 * 「チャンネル」と「画像の投稿」に対応
 * 
 * 3     07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 2     07/06/20 11:21 Tsujimura543
 * 余分な行を削除
 * 
 * 1     07/06/14 16:58 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#if !defined(AFX_SETTINGWASSR_H__8A1786C7_48CB_4EE4_B031_72F4F30972CD__INCLUDED_)
#define AFX_SETTINGWASSR_H__8A1786C7_48CB_4EE4_B031_72F4F30972CD__INCLUDED_

#include "CTabDialog.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSettingWassr ダイアログ

class CSettingWassr : public CTabDialog
{
// コンストラクション
public:
	CSettingWassr(CWnd* pParent = NULL);   // 標準のコンストラクタ

    void    Accept();       // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    LoadSetting();  // 現在の「設定」を取得
    void    SetCheckFriendsTimeline();
    void    SetCheckApplied();

    void    setTimelineInfo( TIMELINE_INFO &s,
                             CString       logFile,
                             BOOL          checkTimeline,
                             BOOL          checkChannel,
                             BOOL          checkLogFile );
    void    getTimelineInfo( TIMELINE_INFO s,
                             CString       &logFile,
                             BOOL          &checkTimeline,
                             BOOL          &checkChannel,
                             BOOL          &checkLogFile );

	CString	m_logFilenameForUpload;
	BOOL	m_writeLogfileForUpload;

// ダイアログ データ
	//{{AFX_DATA(CSettingWassr)
	enum { IDD = IDD_TAB_WASSR };
	BOOL	m_applied;
	BOOL	m_checkChannel;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(CSettingWassr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(CSettingWassr)
	afx_msg void OnButtonSettingUpload();
	afx_msg void OnApplied();
	afx_msg void OnCheckChannel();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCheckFriendsTimeline();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CSettingWassr( CSettingWassr &dlg );
    CSettingWassr   operator = ( CSettingWassr &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGWASSR_H__8A1786C7_48CB_4EE4_B031_72F4F30972CD__INCLUDED_)
