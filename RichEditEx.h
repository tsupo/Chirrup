/*
 * RichEditEx.h  : Twitter クライアント chirrup
 *      URL クリッカブルなリッチエディットコントロール ヘッダーファイル
 *          written by H.Tsujimura  26 Apr 2007
 *
 *      Copyright (c) 2007, 2008, 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/RichEditEx.h $
 * 
 * 2     09/05/31 20:42 tsupo
 * 1.142版
 * 
 * 38    09/05/29 19:22 Tsujimura543
 * 同一アカウントで複数 tumbleblog を開設している場合の投稿先
 * tumbleblog を指定しての投稿を可能にした
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 37    09/03/31 23:29 Tsujimura543
 * Twitter の OAuth 対応準備 その7
 * 
 * 36    08/08/22 18:42 Tsujimura543
 * 「はてなハイク」対応
 * 
 * 35    08/07/16 15:27 Tsujimura543
 * Timelog の「評価」に対応した
 * 
 * 34    08/07/08 14:51 Tsujimura543
 * Wassr の「イイネ!」に対応
 * 
 * 33    08/02/07 22:36 Tsujimura543
 * copyright 表示を修正 (2008 を追加)
 * 
 * 32    08/02/05 22:38 Tsujimura543
 * Altキーの down/up 検出処理も追加 (今のところ、Altキー関連は未使用)
 * 
 * 31    08/02/05 22:29 Tsujimura543
 * F3キー押下で文末方向検索、Shift+F3で文頭方向検索になるようにしてみた
 * 
 * 30    08/02/05 21:33 Tsujimura543
 * F3キー押下でも「検索」機能を起動できるようにした
 * 
 * 29    08/02/04 18:13 Tsujimura543
 * 検索機能改良
 *   (1) 文頭方向への検索もサポート
 *   (2) 検索用パラメータの一時記憶もサポート
 *   (3) オートスクロール対応
 * 
 * 28    08/02/01 23:11 Tsujimura543
 * ctrl+F による「検索」を試験的に実装
 * 
 * 27    07/11/08 23:53 Tsujimura543
 * Twitter検索、buzztter、Google、Yahoo! との連動(検索)機能を追加
 * 
 * 26    07/11/07 3:39 Tsujimura543
 * 見ている発言を 引用して Tumblr へ投稿する機能を作成
 * 
 * 25    07/09/27 20:57 Tsujimura543
 * 右クリック機能をサポート(選択中の文字列のクリップボードへのコピー、
 * 表示されている文字列の全選択)
 * 
 * 24    07/09/27 18:35 Tsujimura543
 * 「もごすた」に対応した
 * 
 * 23    07/09/18 22:29 Tsujimura543
 * リンクのドラッグを CF_HDROP にした(デスクトップ等フォルダへのドラッグ
 * にも対応した)
 * 
 * 22    07/09/18 18:59 Tsujimura543
 * COleDataSource な変数を、クラス内プロパティからローカル変数に変更
 * 
 * 21    07/09/18 16:59 Tsujimura543
 * リンクのドラッグをサポート (いまのところ CF_TEXT として送出している)
 * 
 * 20    07/09/12 18:30 Tsujimura543
 * OnLButtonDblClk() をリファクタリング
 * 
 * 19    07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 18    07/08/25 1:53 Tsujimura543
 * 「ついすた」対応 (実際に☆をつける)
 * 
 * 17    07/08/17 17:25 Tsujimura543
 * SetLinkTwitter3() を追加
 * 
 * 16    07/08/16 19:53 Tsujimura543
 * Timelog の「発言」の permalink へ飛べるようにした ([link] をクリック)
 * 
 * 15    07/07/23 14:54 Tsujimura543
 * SetLinkTwitter2() を追加
 * 
 * 14    07/07/03 13:51 Tsujimura543
 * Visual Studio 2005 でのビルド結果を反映
 * 
 * 13    07/06/26 19:53 Tsujimura543
 * もごもごのリンクに対応
 * 
 * 12    07/06/26 15:10 Tsujimura543
 * Jaiku のリンクに対応
 * 
 * 11    07/06/26 0:29 Tsujimura543
 * CRichEditEx に m_timeline を追加し、Twitter の status リンクへ飛ぶ
 * ための処理を簡略化した
 * 
 * 10    07/06/26 0:11 Tsujimura543
 * コメントを修正
 * 
 * 9     07/06/26 0:10 Tsujimura543
 * SetLinkTwitter() を追加し、Twitter の status ページへ直接飛べるようにした
 * 
 * 8     07/06/25 23:13 Tsujimura543
 * SetLinkTimelog() を追加
 * 
 * 7     07/06/25 21:12 Tsujimura543
 * SetLink() を追加
 * 
 * 6     07/06/21 14:48 Tsujimura543
 * m_targetUser を廃止
 * 
 * 5     07/06/21 14:45 Tsujimura543
 * 「発言」をダブルクリックしただけで、「発言」入力欄にコメント返し用文字
 * 列を表示できるようにした
 * 
 * 4     07/06/20 21:08 Tsujimura543
 * SetWhity() を追加
 * 
 * 3     07/04/28 0:22 Tsujimura543
 * m_targetUser を追加。ダブルクリックした行に Twitter のスクリーン名が
 * 存在すれば格納するようにした
 * 
 * 2     07/04/27 22:26 Tsujimura543
 * SetStrong() を追加
 * 
 * 1     07/04/26 20:16 Tsujimura543
 * 新規作成
 */

#if !defined(AFX_RICHEDITEX_H__43C46684_644A_4A51_B317_33C70EBB6EB5__INCLUDED_)
#define AFX_RICHEDITEX_H__43C46684_644A_4A51_B317_33C70EBB6EB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxole.h>

/////////////////////////////////////////////////////////////////////////////
// CRichEditEx ウィンドウ

class CRichEditEx : public CRichEditCtrl
{
// コンストラクション
public:
	CRichEditEx();

// アトリビュート
public:
    CChirrupDlg                 *m_chirrupDlg;
    CTwitterTimeline            *m_timeline;
    CTwitterTimeline::SVC_TYPE  m_serviceType;

    CString                     m_username;
    CString                     m_password;
    CString                     m_hatenaID;
    CString                     m_hatenaPassword;
    CString                     m_tumblrID;
    CString                     m_tumblrPassword;
    CString                     m_tumblrGroup;

    CString                     m_twitterOauthToken;
    CString                     m_twitterOauthTokenSecret;
    bool                        m_twitterUseOAuth;

// オペレーション
public:
    void    SetAutoUrlDetect();
    void    SetStrong( CString target );    // 指定文字列を強調表示
    void    SetWhity();                     // メッセージID部分を薄色表示
    void    SetLink();                      // 各種リンクを埋め込む

// オーバーライド
	//{{AFX_VIRTUAL(CRichEditEx)
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CRichEditEx();

private:
    void    SetLinkTimelog();   // tag にリンクを埋め込む
    void    SetLinkTimelog2();  // link にリンクを埋め込む
    void    SetLinkTwitter();   // status ID にリンクを埋め込む
    void    SetLinkTwitter2();  // source にリンクを埋め込む
    void    SetLinkTwitter3();  // ☆ / ★ にリンクを埋め込む
    void    SetLinkJaiku();     // title にリンクを埋め込む
    void    SetLinkMogo2();     // >>messageID にリンクを埋め込む
    void    SetLinkStar( bool useStar ); // ☆ もしくは ★ にリンクを埋め込む
    void    SetLinkStar2();     // ☆ にリンクを埋め込む (for Timelog)

    void    GetTargetUser( CString &targetUser, long startPos );
    bool    DragStart( CString &url );

    void    GetLinkTwitter( CString &url, CString &url2, ENLINK *pLink );
    void    GetLinkJaiku( CString &url, CString &url2 );
    void    GetLinkMogo2( CString &url, CString &url2, ENLINK *pLink );
    void    GetLinkTimelog( CString &url, CString &url2, ENLINK *pLink );
    void    GetLinkHaruFm( CString &url, CString &url2 );
    void    GetLinkWassr( CString &url, CString &url2, ENLINK *pLink );
    void    GetLinkHatenaHaiku( CString &url, CString &url2, ENLINK *pLink );

    void    SetFavoriteOnTwitter( CString &url, ENLINK *pLink );
    void    SetFavoriteOnWassr( CString &url, ENLINK *pLink );
    void    SetFavoriteOnTimelog( CString &url, ENLINK *pLink );
    void    SetHatenaStarOnTwitter( CString &url, CString &url2, ENLINK *pLink );
    void    SetHatenaStarOnMogo2( CString &url, CString &url2, ENLINK *pLink );
    void    SetHatenaStarOnHatenaHaiku( CString &url, CString &url2, ENLINK *pLink );

	// メッセージマップ関数
protected:
	//{{AFX_MSG(CRichEditEx)
#if _MSC_VER >= 1400
	afx_msg BOOL OnLink(NMHDR* pNMHDR, LRESULT* pResult);
#else
	afx_msg void OnLink(NMHDR* pNMHDR, LRESULT* pResult);
#endif
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg LONG OnFind(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
    bool                m_active;
    CString             m_text;

    // 検索関連
    CFindReplaceDialog  *m_findDialog;
    bool                m_findMatchCase;        // 大文字・小文字の区別の有無
    bool                m_findMatchWholeWord;   // 完全一致か部分一致か
    bool                m_findSearchDown;       // 文末方向か文頭方向か
    char                *m_findBuf;

    bool                m_shiftKeyDown;
    bool                m_altKeyDown;

    void    GetTargetURL(
                CString &targetURL,
                CString &targetContent,
                long    startPos
            );
    void    PostTumblr( CString targetURL, CString targetContent );
    void    ExecuteSearch( int cmdType, const char *text );

    void    OnSearchText();

    CRichEditEx( CRichEditEx &obj );
    CRichEditEx operator = ( CRichEditEx &obj );
};

class   CChirrupDropSource : public COleDropSource
{   // m_bDragStarted の値を参照したいだけの目的で作ったクラス
public:
    BOOL    isDragStarted() { return ( m_bDragStarted ); }
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_RICHEDITEX_H__43C46684_644A_4A51_B317_33C70EBB6EB5__INCLUDED_)
