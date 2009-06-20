/*
 * FriendDialog.cpp : Twitter クライアント chirrup
 *      プロフィール表示ダイアログ インプリメンテーション ファイル
 *          written by H.Tsujimura  14 Apr 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/FriendDialog.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 17    09/03/31 23:29 Tsujimura543
 * Twitter の OAuth 対応準備 その7
 * 
 * 16    08/07/08 17:46 Tsujimura543
 * Wassr の friend の add と remove にも対応した
 * 
 * 15    07/09/26 20:05 Tsujimura543
 * ダイレクトメッセージ表示ダイアログおよびプロフィール表示ダイアログ
 * 表示中もメインダイアログのステータスバーを更新するようにした
 * (ステータスバーをいじろうとしてnullポインタ参照で落ちるバグを回避)
 * 
 * 14    07/09/06 19:46 Tsujimura543
 * 余分なコメントを削除
 * 
 * 13    07/06/27 18:13 Tsujimura543
 * haru.fm に対応
 * 
 * 12    07/06/20 17:36 Tsujimura543
 * Timelog 対応
 * 
 * 11    07/06/18 18:52 Tsujimura543
 * LoadUserIcon() を導入し、ユーザアイコンの表示処理を一本化した
 * 
 * 10    07/06/15 19:40 Tsujimura543
 * Wassr と もごもご に対応
 * 
 * 9     07/06/04 21:12 Tsujimura543
 * friend の add/remove 成功時のアイコンを ICONERROR から
 * ICONINFORMATION に変更
 * 
 * 8     07/06/04 21:11 Tsujimura543
 * friend の add と remove を実装 (for Twitter)
 * 
 * 7     07/05/29 3:56 Tsujimura543
 * Jaiku (の public_timeline の閲覧) に対応
 * 
 * 6     07/04/27 19:31 Tsujimura543
 * URL が未設定の場合はマウスカーソルの形を指カーソルに変えるのを抑制
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

#include "chirrup.h"
#include "chirrupDlg.h"
#include "FriendDialog.h"
#include "wassr.h"
extern "C" {
#include "utility.h"
}

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/FriendDialog.cpp 1     09/05/14 3:50 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if (WINVER >= 0x0500)
//#define IDC_HAND    MAKEINTRESOURCE(32649)
#ifdef IDC_HAND
#undef IDC_HAND
#endif
#endif /* WINVER >= 0x0500 */
#define IDC_HAND    IDC_HAND2

/////////////////////////////////////////////////////////////////////////////
// CFriendDialog ダイアログ

CFriendDialog::CFriendDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFriendDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFriendDialog)
	//}}AFX_DATA_INIT

    m_hCursor = AfxGetApp()->LoadCursor( IDC_HAND );
    m_user.bitmap      = NULL;
    m_allocated        = false;
    m_mode             = SHOW_PROFILE;
    m_username         = _T("");
    m_password         = _T("");
    m_oauthToken       = _T("");
    m_oauthTokenSecret = _T("");
    m_useOAuth         = false;
}

CFriendDialog::~CFriendDialog()
{
    if ( m_allocated )
        if ( m_user.bitmap )
            DeleteObject( m_user.bitmap );
    m_cFont.DeleteObject();
}

void CFriendDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFriendDialog)
	DDX_Control(pDX, IDC_EDIT_LAST_STATUS, m_lastStatusCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFriendDialog, CDialog)
	//{{AFX_MSG_MAP(CFriendDialog)
	ON_BN_CLICKED(IDC_FRIEND_URL, OnFriendUrl)
	ON_WM_SHOWWINDOW()
	ON_WM_SETCURSOR()
	ON_BN_CLICKED(IDC_PROFILE_ICON, OnProfileIcon)
    ON_NOTIFY(TTN_NEEDTEXT, 0, OnDisplayToolTip)
	ON_BN_CLICKED(IDC_MANAGE_FRIEND, OnManageFriend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFriendDialog メッセージ ハンドラ

BOOL CFriendDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

    EnableToolTips(TRUE);

	return TRUE;
}

void CFriendDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        LOGFONT tLogFont;
        CFont   *cWndFont;

        cWndFont = GetFont(); 
        cWndFont->GetLogFont( &tLogFont );
        tLogFont.lfUnderline = 1;
        m_cFont.CreateFontIndirect( &tLogFont );

        CStatic *s = (CStatic *)GetDlgItem( IDC_PROFILE_ICON );
        CTwitterTimeline::SVC_TYPE  type = CTwitterTimeline::SVC_TWITTER;
        m_allocated = LoadUserIcon( s, &m_user, type, m_cacheDir );

        s = (CStatic *)GetDlgItem( IDC_DESCRIPTION );
        s->SetWindowText( m_user.description );

        s = (CStatic *)GetDlgItem( IDC_NAME );
        s->SetWindowText( m_user.name );

        s = (CStatic *)GetDlgItem( IDC_SCREENNAME );
        s->SetWindowText( m_user.screenName );

        s = (CStatic *)GetDlgItem( IDC_LOCATION );
        s->SetWindowText( m_user.location );

        s = (CStatic *)GetDlgItem( IDC_FRIEND_URL );
        s->SetWindowText( m_user.url );
        s->SetFont( &m_cFont, TRUE );   // URLを下線付きで表示する

        CString title = m_user.screenName;
        title += "さんのプロフィール";
        this->SetWindowText( title );

        char    lastStatus[MAX_DESCRIPTION_LEN];

        if ( m_user.lastStatus[0] )
            strcpy( lastStatus, m_user.lastStatus );
        else {
            lastStatus[0] = NUL;
            getLastStatus( m_user.screenName, lastStatus );
        }

        m_lastStatusCtrl.SetAutoUrlDetect();
        m_lastStatusCtrl.SetWindowText( lastStatus[0]
                                            ? lastStatus
                                            : _T("...") );

        CButton *bp = (CButton *)GetDlgItem( IDC_MANAGE_FRIEND );
        if ( m_mode == SHOW_PROFILE ) {
            bp->ShowWindow( SW_HIDE );
        }
        else {
            bp->ShowWindow( SW_SHOW );
            if ( m_mode == ADD_FRIEND )
                bp->SetWindowText( "friend にする" );
            else
                bp->SetWindowText( "friend から外す" );

            bp = (CButton *)GetDlgItem( IDOK );
            bp->SetWindowText( "キャンセル" );
        }
    }	
}

void CFriendDialog::OnFriendUrl() 
{
    if ( !strncmp( m_user.url, "http://",  7 ) ||
         !strncmp( m_user.url, "https://", 8 )    ) {
	    CString cmd;
	    cmd = m_user.url;
        ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
    }
}

void CFriendDialog::OnProfileIcon() 
{
    CString cmd = _T("");

    if ( strstr( m_user.profileImageURL, "jaiku.com" ) ||
         strstr( m_user.profileImageURL, "wassr.jp" )     ) {
        cmd = m_user.url;
    }
    else if ( strstr( m_user.profileImageURL, "mogo2.jp" ) ) {
	    cmd = _T("http://mogo2.jp/");
    	cmd += m_user.id;
    }
    else if ( strstr( m_user.profileImageURL, "timelog.jp" ) ) {
	    cmd = _T("http://timelog.jp/?");
    	cmd += m_user.id;
    }
    else if ( strstr( m_user.profileImageURL, "haru.fm" ) ) {
	    cmd = _T("http://haru.fm/mypost/");
    	cmd += m_user.id;
    }
    else {
	    cmd = _T("http://twitter.com/");
    	cmd += m_user.screenName;
    }
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

BOOL CFriendDialog::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if ( nHitTest == HTCLIENT ) {
        // URL にマウスポインタが来たら、指カーソルを表示する
		DWORD   dwPos = GetMessagePos();
		WORD    wX    = LOWORD( dwPos );
		WORD    wY    = HIWORD( dwPos );
		CPoint  poCursor( wX, wY );
		CRect   rcClient;

        CStatic *s;
        if ( m_user.url[0] ) {
            s = (CStatic *)GetDlgItem( IDC_FRIEND_URL );
            s->GetWindowRect( &rcClient );
            if ( (wX >= rcClient.left) && (wX <= rcClient.right)  &&
                 (wY >= rcClient.top)  && (wY <= rcClient.bottom)    ) {
			    SetCursor( m_hCursor );
                return TRUE;
            }
        }

        s = (CStatic *)GetDlgItem( IDC_PROFILE_ICON );
        s->GetWindowRect( &rcClient );
        if ( (wX >= rcClient.left) && (wX <= rcClient.right)  &&
             (wY >= rcClient.top)  && (wY <= rcClient.bottom)    ) {
			SetCursor( m_hCursor );
            return TRUE;
        }
	}

    m_lastStatusCtrl.m_chirrupDlg->SetPaneText( 0, _T(" ") );
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
void CFriendDialog::OnDisplayToolTip(NMHDR* pNMHDR, LRESULT* pResult)
{
    TOOLTIPTEXT *tp = (TOOLTIPTEXT *)pNMHDR;

    if ( (tp->uFlags & TTF_IDISHWND) == TTF_IDISHWND ) {
        int id = ::GetDlgCtrlID( (HWND)tp->hdr.idFrom );
        const char  *text = NULL;

        switch ( id ) {
        case IDC_PROFILE_ICON:
            text = m_user.screenName;
            break;
        }

        if ( text && *text )
            strcat( tp->szText, text );
    }
}
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif

void CFriendDialog::OnManageFriend() 
{
    if ( m_mode == SHOW_PROFILE )
        return;

    if ( !m_useOAuth                         &&
         ((m_username.GetLength() == 0) ||
          (m_password.GetLength() == 0)    )    )
        return;

    bool    ret = false;

    if ( strstr( m_user.profileImageURL, "wassr.jp" ) ) {
        CWassr  t;
        t.m_username = m_username;
        t.m_password = m_password;

        if ( m_mode == ADD_FRIEND )
            ret = t.AddFriend( m_user.id );
        else if ( m_mode == REMOVE_FRIEND )
            ret = t.RemoveFriend( m_user.id );
    }
    else {
        CTwitter    t;
        t.m_username         = m_username;
        t.m_password         = m_password;
        t.m_useOAuth         = m_useOAuth;
        t.m_oauthToken       = m_oauthToken;
        t.m_oauthTokenSecret = m_oauthTokenSecret;

        if ( m_mode == ADD_FRIEND )
            ret = t.AddFriend( m_user.id );
        else if ( m_mode == REMOVE_FRIEND )
            ret = t.RemoveFriend( m_user.id );
    }

    if ( ret == false )
        MessageBox( m_mode == ADD_FRIEND
                        ? "friend の add に失敗しました＞＜  "
                        : "friend の remove に失敗しました",
                    m_mode == ADD_FRIEND
                        ? "フレンド追加失敗"
                        : "フレンド削除失敗",
                    MB_OK|MB_ICONERROR );
    else {
        CString msg = m_user.screenName;
        msg += "さんを friend ";
        msg += m_mode == ADD_FRIEND
                ? "にしました。    "
                : "から外しました。    ";

        MessageBox( msg,
                    m_mode == ADD_FRIEND
                        ? "フレンド追加成功"
                        : "フレンド削除成功",
                    MB_OK|MB_ICONINFORMATION );

        m_mode = SHOW_PROFILE;
        CButton *bp = (CButton *)GetDlgItem( IDC_MANAGE_FRIEND );
        bp->ShowWindow( SW_HIDE );

        bp = (CButton *)GetDlgItem( IDOK );
        bp->SetWindowText( "OK" );
    }
}
