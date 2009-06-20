/*
 * DirectMessage.cpp : Twitter クライアント chirrup
 *      ダイレクトメッセージ送信ダイアログ インプリメンテーション ファイル
 *          written by H.Tsujimura  25 Apr 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/DirectMessage.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 12    09/03/31 23:29 Tsujimura543
 * Twitter の OAuth 対応準備 その7
 * 
 * 11    07/06/21 22:42 Tsujimura543
 * ダイレクトメッセージ閲覧ダイアログ経由でダイレクトメッセージ送信
 * ダイアログが呼び出された場合でも、期待するユーザアイコンを表示
 * できるようにした (Twitter に関して)
 * 
 * 10    07/06/21 22:11 Tsujimura543
 * Timelog のダイレクトメッセージの送受信に対応 (動作確認済み)
 * 
 * 9     07/06/21 19:46 Tsujimura543
 * Timelog にも対応
 * 
 * 8     07/06/18 18:52 Tsujimura543
 * LoadUserIcon() を導入し、ユーザアイコンの表示処理を一本化した
 * 
 * 7     07/05/29 3:56 Tsujimura543
 * Jaiku (の public_timeline の閲覧) に対応
 * 
 * 6     07/05/23 22:22 Tsujimura543
 * URL の直書きはやめて、マクロ TWITTER_DEFAULT_IMAGE を使う
 * ようにした
 * 
 * 5     07/04/27 19:39 Tsujimura543
 * Twitter API 関連の処理を Twitter.cpp に集約したのに伴う修正を実施
 * 
 * 4     07/04/26 15:50 Tsujimura543
 * プロフィールアイコンにツールチップ表示を追加
 * 
 * 3     07/04/26 0:22 Tsujimura543
 * CDirectMessageList ダイアログ経由で呼び出された場合にも問題なく
 * 処理できるようにした
 * 
 * 2     07/04/25 21:07 Tsujimura543
 * リファクタリング
 * 
 * 1     07/04/25 16:18 Tsujimura543
 * 最初の版
 */

#include "chirrup.h"
#include "chirrupDlg.h"
#include "timelog.h"
#include "DirectMessage.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/DirectMessage.cpp 1     09/05/14 3:50 tsupo $";
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
// CDirectMessage ダイアログ

CDirectMessage::CDirectMessage(CWnd* pParent /*=NULL*/)
	: CDialog(CDirectMessage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDirectMessage)
	m_directMessage = _T("");
	//}}AFX_DATA_INIT

    m_hCursor = AfxGetApp()->LoadCursor( IDC_HAND );
    m_user.bitmap      = NULL;
    m_allocated        = false;
    m_useOAuth         = false;
    m_oauthToken       = _T("");
    m_oauthTokenSecret = _T("");

    m_serviceType      = CTwitterTimeline::SVC_TWITTER;
}

CDirectMessage::~CDirectMessage()
{
    if ( m_allocated )
        if ( m_user.bitmap )
            DeleteObject( m_user.bitmap );
    m_cFont.DeleteObject();
}

void CDirectMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDirectMessage)
	DDX_Text(pDX, IDC_EDIT_DIRECTMESSAGE, m_directMessage);
	DDV_MaxChars(pDX, m_directMessage, 160);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDirectMessage, CDialog)
	//{{AFX_MSG_MAP(CDirectMessage)
	ON_WM_SHOWWINDOW()
	ON_WM_SETCURSOR()
    ON_NOTIFY(TTN_NEEDTEXT, 0, OnDisplayToolTip)
	ON_BN_CLICKED(IDC_PROFILE_ICON, OnProfileIcon)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirectMessage メッセージ ハンドラ

BOOL CDirectMessage::OnInitDialog() 
{
    CDialog::OnInitDialog();

    EnableToolTips(TRUE);

    return TRUE;
}

void CDirectMessage::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

    if ( bShow ) {
        LOGFONT tLogFont;
        CFont   *cWndFont;

        cWndFont = GetFont(); 
        cWndFont->GetLogFont( &tLogFont );
        tLogFont.lfUnderline = 1;
        m_cFont.CreateFontIndirect( &tLogFont );

        CStatic *s  = (CStatic *)GetDlgItem( IDC_PROFILE_ICON );
        m_allocated = LoadUserIcon( s, &m_user, m_serviceType, m_cacheDir,
                                    m_username, m_password,
                                    m_useOAuth,
                                    m_oauthToken, m_oauthTokenSecret );

        CString title = m_user.screenName;
        title += "さんにダイレクトメッセージを送信";
        this->SetWindowText( title );
    }	
}

BOOL CDirectMessage::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if ( nHitTest == HTCLIENT ) {
        // URL にマウスポインタが来たら、指カーソルを表示する
		DWORD   dwPos = GetMessagePos();
		WORD    wX    = LOWORD( dwPos );
		WORD    wY    = HIWORD( dwPos );
		CPoint  poCursor( wX, wY );
		CRect   rcClient;

        CStatic *s = (CStatic *)GetDlgItem( IDC_PROFILE_ICON );
        s->GetWindowRect( &rcClient );
        if ( (wX >= rcClient.left) && (wX <= rcClient.right)  &&
             (wY >= rcClient.top)  && (wY <= rcClient.bottom)    ) {
			SetCursor( m_hCursor );
            return TRUE;
        }
	}

    return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

void CDirectMessage::OnOK() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_DIRECTMESSAGE );
    p->GetWindowText( m_directMessage );
    if ( m_directMessage.GetLength() > 0 ) {
        CWaitCursor cur;    // マウスカーソルを砂時計表示
        bool        ret = false;

        if ( m_serviceType == CTwitterTimeline::SVC_TWITTER ) {
            CTwitter    t;
            t.m_username         = m_username;
            t.m_password         = m_password;
            t.m_useOAuth         = m_useOAuth;
            t.m_oauthToken       = m_oauthToken;
            t.m_oauthTokenSecret = m_oauthTokenSecret;

            ret = t.SendDirectMessage(m_user.screenName, m_directMessage);
        }
        else if ( m_serviceType == CTwitterTimeline::SVC_TIMELOG ) {
            CTimelog    t;
            t.m_username = m_username;
            t.m_password = m_password;

            ret = t.SendDirectMessage(m_user.id, m_directMessage);
        }
        if ( ret == false )
            MessageBox( "ダイレクトメッセージの送信に失敗しました＞＜  ",
                        "ダイレクトメッセージ送信失敗",
                        MB_OK|MB_ICONERROR );

        CDialog::OnOK();
    }
}

void CDirectMessage::OnProfileIcon() 
{
	CString cmd;

    if ( m_serviceType == CTwitterTimeline::SVC_TWITTER ) {
        cmd = _T("http://twitter.com/");
    	cmd += m_user.screenName;
    }
    else if ( m_serviceType == CTwitterTimeline::SVC_TIMELOG ) {
        cmd = _T("http://timelog.jp/?");
    	cmd += m_user.id;
    }
    else
        return;

    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
void CDirectMessage::OnDisplayToolTip(NMHDR* pNMHDR, LRESULT* pResult)
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
