/*
 * DirectMessage.h : Twitter クライアント chirrup
 *      ダイレクトメッセージ送信ダイアログ ヘッダーファイル
 *          written by H.Tsujimura  25 Apr 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/DirectMessage.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 6     09/03/31 23:29 Tsujimura543
 * Twitter の OAuth 対応準備 その7
 * 
 * 5     07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 4     07/06/21 19:46 Tsujimura543
 * Timelog にも対応
 * 
 * 3     07/04/27 19:39 Tsujimura543
 * Twitter API 関連の処理を Twitter.cpp に集約したのに伴う修正を実施
 * 
 * 2     07/04/26 15:50 Tsujimura543
 * プロフィールアイコンにツールチップ表示を追加
 * 
 * 1     07/04/25 16:18 Tsujimura543
 * 最初の版
 */

#if !defined(AFX_DIRECTMESSAGE_H__B02D011D_95DF_4DC4_A3BB_54C9EE30D64B__INCLUDED_)
#define AFX_DIRECTMESSAGE_H__B02D011D_95DF_4DC4_A3BB_54C9EE30D64B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDirectMessage ダイアログ

class CDirectMessage : public CDialog
{
// コンストラクション
public:
	CDirectMessage(CWnd* pParent = NULL);   // 標準のコンストラクタ
    ~CDirectMessage();

    HCURSOR                     m_hCursor;
    CFont                       m_cFont;
    TWITTER_USER                m_user;
    CString                     m_cacheDir;
    bool                        m_allocated;

    CString                     m_username;
    CString                     m_password;
    CString                     m_oauthToken;
    CString                     m_oauthTokenSecret;
    bool                        m_useOAuth;
    CTwitterTimeline::SVC_TYPE  m_serviceType;

// ダイアログ データ
	//{{AFX_DATA(CDirectMessage)
	enum { IDD = IDD_DIRECTMESSAGE_DIALOG };
	CString	m_directMessage;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(CDirectMessage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// メッセージマップ関数
	//{{AFX_MSG(CDirectMessage)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnProfileIcon();
    afx_msg void OnDisplayToolTip(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CDirectMessage( CDirectMessage &dlg );
    CDirectMessage  operator = ( CDirectMessage &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_DIRECTMESSAGE_H__B02D011D_95DF_4DC4_A3BB_54C9EE30D64B__INCLUDED_)
