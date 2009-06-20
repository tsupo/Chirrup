/*
 * SettingDialog.h  : Twitter クライアント chirrup
 *      CSettingDialog クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  7 Jun 2007
 *
 *      Copyright (c) 2007, 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/SettingDialog.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 17    08/08/22 18:41 Tsujimura543
 * 「はてなハイク」対応
 * 
 * 16    08/07/08 15:45 Tsujimura543
 * OnInitDialog() を宣言する位置を移動
 * 
 * 15    08/07/08 15:41 Tsujimura543
 * ディスプレイの縦方向の大きさ(高さ)が 800px 以下の場合は、表示する
 * ダイアログの大きさを縦方向に小さくするようにしてみた
 * 
 * 14    08/01/09 17:08 Tsujimura543
 * Flickr 対応
 * 
 * 13    07/12/10 16:39 Tsujimura543
 * Gyazo 対応
 * 
 * 12    07/11/26 17:46 Tsujimura543
 * 「proxy設定」タブがactiveになっている状態で起動できるオプションを追加
 * 
 * 11    07/11/26 17:31 Tsujimura543
 * 「proxy設定」をタブの１つとして取り込む
 * 
 * 10    07/11/26 16:02 Tsujimura543
 * リファクタリング
 * 
 * 9     07/11/05 23:35 Tsujimura543
 * tumblr に対応
 * 
 * 8     07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 7     07/08/25 0:14 Tsujimura543
 * 「ついすた」に対応
 * 
 * 6     07/06/27 18:12 Tsujimura543
 * haru.fm に対応
 * 
 * 5     07/06/20 14:06 Tsujimura543
 * Timelog 対応版
 * 
 * 4     07/06/14 21:12 Tsujimura543
 * 「もごもご」に対応
 * 
 * 3     07/06/14 16:58 Tsujimura543
 * Wassr に対応
 * 
 * 2     07/06/07 15:47 Tsujimura543
 * CTabDialog を導入、コードを整理してみた
 * 
 * 1     07/06/07 1:43 Tsujimura543
 * 新規作成 (タブ選択形式の設定ダイアログを新たに用意した)
 */

#if !defined(AFX_SETTINGDIALOG_H__14EE08E8_5445_4DB4_A528_B1D67BA4DBD5__INCLUDED_)
#define AFX_SETTINGDIALOG_H__14EE08E8_5445_4DB4_A528_B1D67BA4DBD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SettingTwitter.h"
#include "SettingJaiku.h"
#include "SettingWassr.h"
#include "SettingMogo2.h"
#include "SettingTimelog.h"
#include "SettingHaruFm.h"
#include "SettingHatenaHaiku.h"
#include "SettingHatena.h"
#include "SettingTumblr.h"
#include "SettingGyazo.h"
#include "SettingFlickr.h"
#include "SettingProxy.h"

/////////////////////////////////////////////////////////////////////////////
// CSettingDialog ダイアログ

class CSettingDialog : public CDialog
{
// コンストラクション
public:
	CSettingDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CSettingDialog)
	enum { IDD = IDD_SETTING_DIALOG };
	CTabCtrl	m_tabSetting;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(CSettingDialog)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
    CChirrupDlg         *m_chirrup;

#define NUM_OF_TABS     12                  // タブの総数
    int                 m_numOfTabs;        // タブの総数

    CDialog             *m_dlg[NUM_OF_TABS];// 各タブに貼り付いているダイアログ
    int                 m_activePage;       // 選択されているタブ
    bool                m_settingProxy; // 「proxy設定」タブをactive状態で起動

    // ダイアログ実体
    CSettingTwitter     m_dlg00;
    CSettingJaiku       m_dlg01;
    CSettingWassr       m_dlg02;
    CSettingMogo2       m_dlg03;
    CSettingTimelog     m_dlg04;
    CSettingHaruFm      m_dlg05;
    CSettingHatenaHaiku m_dlg06;
    CSettingHatena      m_dlg07;
    CSettingTumblr      m_dlg08;
    CSettingGyazo       m_dlg09;
    CSettingFlickr      m_dlg10;
    CSettingProxy       m_dlg11;

    // ダイアログ種別
    enum    {
        CS_TWITTER = 0,
        CS_JAIKU,
        CS_WASSR,
        CS_MOGO2,
        CS_TIMELOG,
        CS_HARUFM,
        CS_HATENAHAIKU,
        CS_HATENA,
        CS_TUMBLR,
        CS_GYAZO,
        CS_FLICKR,
        CS_PROXY
    };

    // タブ切り替え
    int     DispCurrentTab( int activeTab = 0 );

protected:
    // データの正当性チェック
    BOOL    CheckDlgData();

	// メッセージマップ関数
	//{{AFX_MSG(CSettingDialog)
	afx_msg void OnButtonAccept();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CSettingDialog( CSettingDialog &dlg );
    CSettingDialog  operator = ( CSettingDialog &dlg );

    int     m_width;
    int     m_height;
    int     m_base;
    int     m_dialogWidth;
    bool    m_resized;
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGDIALOG_H__14EE08E8_5445_4DB4_A528_B1D67BA4DBD5__INCLUDED_)
