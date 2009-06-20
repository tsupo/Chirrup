/*
 * CTabDialog.h : Twitter クライアント chirrup
 *      CTabDialog クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  7 Jun 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/CTabDialog.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 6     08/07/16 4:13 Tsujimura543
 * 「同時投稿対象」の設定を「設定」ダイアログでも設定できるようにした
 * 
 * 5     07/09/06 19:39 Tsujimura543
 * ソースコードを整理
 * 
 * 4     07/06/13 0:12 Tsujimura543
 * (1) TIMELINE_INFO 関連 fix
 * (2) 初期設定ファイル読み書きを新しいログファイル管理仕様に対応させた
 * 
 * 3     07/06/12 17:54 Tsujimura543
 * (1) Twitter と Jaiku で共通化できる部分を CTagDialog に移動
 * (2) 設定項目を追加 (閲覧対象とするか、ログのファイル名に日付を付加
 *     するか)
 * 
 * 2     07/06/07 15:47 Tsujimura543
 * CTabDialog を導入、コードを整理してみた
 * 
 * 1     07/06/07 15:45 Tsujimura543
 * 新規作成 (SettingTwitter, SettingJaiku の共通部分を保持するクラスと
 * して設計。今後の対応サービス増加を少しでも容易にする目的もあり)
 */

#ifndef __TAB_DIALOG_H__
#define __TAB_DIALOG_H__

/////////////////////////////////////////////////////////////////////////////
// CTabDialog ダイアログ

class CTabDialog : public CDialog
{
public:
    CTabDialog( UINT nIDTemplate, CWnd* pParentWnd = NULL );

    // 「設定ダイアログ」での「適用」ボタン押下時処理
    virtual void    Accept() = 0;

    // 現在の「設定」を取得
    virtual void    LoadSetting() = 0;

    // ログファイル名設定
    void    InputFileName( CString &targetFilename, int id );

    void setTimelineInfo( TIMELINE_INFO &s,
                          CString       logFile,
                          BOOL          checkTimeline,
                          BOOL          checkLogFile );
    void getTimelineInfo( TIMELINE_INFO s,
                          CString       &logFile,
                          BOOL          &checkTimeline,
                          BOOL          &checkLogFile );

    CChirrupDlg *m_chirrup;

// ダイアログ データ
	//{{AFX_DATA(CTabDialog)
	CString	m_username;
	CString	m_password;
	CString	m_logFile_friendsTimeline;
	CString	m_logFile_publicTimeline;
	CString	m_logFile_userTimeline;
	BOOL	m_checkFriendsTimeline;
	BOOL	m_checkPublicTimeline;
	BOOL	m_checkUserTimeline;
	BOOL	m_checkLogFileFriendsTimeline;
	BOOL	m_checkLogFilePublicTimeline;
	BOOL	m_checkLogFileUserTimeline;
    BOOL    m_checkMultiPost;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(CTabDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
    bool    m_initialized;

	// メッセージマップ関数
	//{{AFX_MSG(CTabDialog)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnButtonFilespec();
	afx_msg void OnButtonFilespec2();
	afx_msg void OnButtonFilespec3();
	afx_msg void OnCheckFriendsTimeline();
	afx_msg void OnCheckPublicTimeline();
	afx_msg void OnCheckUserTimeline();
	afx_msg void OnCheckPublicTimeline2();
	afx_msg void OnCheckUserTimeline2();
	afx_msg void OnCheckFriendsTimeline2();
	afx_msg void OnCheckMultiPost();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    void SetCheckFriendsTimeline();
    void SetCheckPublicTimeline();
    void SetCheckUserTimeline();
    void SetCheckMultiPost();
};

#endif  /* __TAB_DIALOG_H__ */