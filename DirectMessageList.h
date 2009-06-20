/*
 * DirectMessageList.h : Twitter クライアント chirrup
 *      ダイレクトメッセージ閲覧ダイアログ ヘッダーファイル
 *          written by H.Tsujimura  25 Apr 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/DirectMessageList.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 12    09/03/31 23:29 Tsujimura543
 * Twitter の OAuth 対応準備 その7
 * 
 * 11    07/11/06 21:45 Tsujimura543
 * コメントを修正
 * 
 * 10    07/09/26 20:05 Tsujimura543
 * ダイレクトメッセージ表示ダイアログおよびプロフィール表示ダイアログ
 * 表示中もメインダイアログのステータスバーを更新するようにした
 * (ステータスバーをいじろうとしてnullポインタ参照で落ちるバグを回避)
 * 
 * 9     07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 8     07/06/22 17:42 Tsujimura543
 * 「受信者」も表示するようにした
 * 
 * 7     07/06/21 22:11 Tsujimura543
 * Timelog のダイレクトメッセージの送受信に対応 (動作確認済み)
 * 
 * 6     07/06/21 20:26 Tsujimura543
 * Twitter以外にも対応(できるようにした)
 * 
 * 5     07/06/13 15:53 Tsujimura543
 * ダイレクトメッセージの削除機能を追加
 * 
 * 4     07/04/27 19:39 Tsujimura543
 * Twitter API 関連の処理を Twitter.cpp に集約したのに伴う修正を実施
 * 
 * 3     07/04/26 20:42 Tsujimura543
 * リファクタリング
 * 
 * 2     07/04/26 20:40 Tsujimura543
 * ダイレクトメッセージの本文に URL が含まれる場合、クリックできるようにした
 * 
 * 1     07/04/26 0:20 Tsujimura543
 * 新規作成
 */

#if !defined(AFX_DIRECTMESSAGELIST_H__ACC3DBA8_23E8_474C_A441_F9A0654727A2__INCLUDED_)
#define AFX_DIRECTMESSAGELIST_H__ACC3DBA8_23E8_474C_A441_F9A0654727A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDirectMessageList ダイアログ

class CDirectMessageList : public CDialog
{
// コンストラクション
public:
	CDirectMessageList(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDirectMessageList)
	enum { IDD = IDD_DIRECTMESSAGE_LIST_DIALOG };
	CRichEditEx	m_textCtrl;
	CString	m_sender;
	CString	m_dateTime;
	CString	m_recipient;
	//}}AFX_DATA

    CTwitterTimeline::SVC_TYPE  m_serviceType;
    TWITTER_DIRECT_MESSAGE      *m_dm;
    int                         m_numOfMessages;
    int                         m_currentIndex;

    CString                     m_cacheDir;
    CString                     m_screenName;
    CString                     m_username;
    CString                     m_password;

    CString                     m_oauthToken;
    CString                     m_oauthTokenSecret;
    bool                        m_useOAuth;

// オーバーライド
	//{{AFX_VIRTUAL(CDirectMessageList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
    void    DisplayDirectMessage( int index );

	CString m_text;

	// メッセージマップ関数
	//{{AFX_MSG(CDirectMessageList)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnButtonNext();
	afx_msg void OnButtonPrev();
	afx_msg void OnButtonReply();
	afx_msg void OnButtonDelete();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CDirectMessageList( CDirectMessageList &dlg );
    CDirectMessageList  operator = ( CDirectMessageList &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_DIRECTMESSAGELIST_H__ACC3DBA8_23E8_474C_A441_F9A0654727A2__INCLUDED_)
