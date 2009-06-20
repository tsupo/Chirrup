/*
 * FriendDialog.h  : Twitter クライアント chirrup
 *      プロフィール表示ダイアログ ヘッダーファイル
 *          written by H.Tsujimura  14 Apr 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/FriendDialog.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 9     09/03/31 23:29 Tsujimura543
 * Twitter の OAuth 対応準備 その7
 * 
 * 8     07/11/06 21:45 Tsujimura543
 * コメントを修正
 * 
 * 7     07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 6     07/06/04 21:11 Tsujimura543
 * friend の add と remove を実装 (for Twitter)
 * 
 * 5     07/04/26 20:56 Tsujimura543
 * 「最近の発言」に URL が含まれる場合は、クリックできるようにした
 * 
 * 4     07/04/26 15:50 Tsujimura543
 * プロフィールアイコンにツールチップ表示を追加
 * 
 * 3     07/04/24 23:47 Tsujimura543
 * コメントを修正
 * 
 * 2     07/04/23 16:45 Tsujimura543
 * (1) 「最近の発言」を表示するようにした
 * (2) ユーザのアイコンをクリックすると、そのユーザの Twitter ページに飛べる
 *     ようにした
 * 
 * 1     07/04/14 2:05 Tsujimura543
 * 最初の版
 */

#if !defined(AFX_FRIENDDIALOG_H__DB3048A5_DEBF_4446_ACF8_8EB460D8B0C5__INCLUDED_)
#define AFX_FRIENDDIALOG_H__DB3048A5_DEBF_4446_ACF8_8EB460D8B0C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFriendDialog ダイアログ

class CFriendDialog : public CDialog
{
// コンストラクション
public:
	CFriendDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ
	~CFriendDialog();

    HCURSOR         m_hCursor;
    CFont           m_cFont;
    TWITTER_USER    m_user;     // profile 表示対象ユーザ
    CString         m_cacheDir;
    bool            m_allocated;
    enum dialogMode {
        SHOW_PROFILE,
        ADD_FRIEND,
        REMOVE_FRIEND
    }               m_mode;
    CString         m_username;
    CString         m_password;
    CString         m_oauthToken;
    CString         m_oauthTokenSecret;
    bool            m_useOAuth;

// ダイアログ データ
	//{{AFX_DATA(CFriendDialog)
	enum { IDD = IDD_PROFILE_DIALOG };
	CRichEditEx	m_lastStatusCtrl;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(CFriendDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(CFriendDialog)
	afx_msg void OnFriendUrl();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnProfileIcon();
    afx_msg void OnDisplayToolTip(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnManageFriend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CFriendDialog( CFriendDialog &dlg );
    CFriendDialog   operator = ( CFriendDialog &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_FRIENDDIALOG_H__DB3048A5_DEBF_4446_ACF8_8EB460D8B0C5__INCLUDED_)
