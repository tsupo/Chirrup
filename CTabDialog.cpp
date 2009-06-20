/*
 * CTabDialog.cpp : Twitter クライアント chirrup
 *      設定ダイアログ(タブ貼り付け部分共通) インプリメンテーション ファイル
 *          written by H.Tsujimura  7 Jun 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/CTabDialog.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 6     08/07/16 4:13 Tsujimura543
 * 「同時投稿対象」の設定を「設定」ダイアログでも設定できるようにした
 * 
 * 5     07/06/18 22:35 Tsujimura543
 * ユーザ名の最大許容長を32バイトから64バイトへ変更
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

#include "chirrup.h"
#include "chirrupDlg.h"
#include "CTabDialog.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/CTabDialog.cpp 1     09/05/14 3:50 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabDialog ダイアログ

CTabDialog::CTabDialog( UINT nIDTemplate, CWnd* pParentWnd )
	: CDialog(nIDTemplate, pParentWnd)
{
	//{{AFX_DATA_INIT(CTabDialog)
	m_username = _T("");
	m_password = _T("");
	m_logFile_friendsTimeline = _T("");
	m_logFile_publicTimeline = _T("");
	m_logFile_userTimeline = _T("");
	m_checkFriendsTimeline = FALSE;
	m_checkPublicTimeline = FALSE;
	m_checkUserTimeline = FALSE;
	m_checkLogFileFriendsTimeline = FALSE;
	m_checkLogFilePublicTimeline = FALSE;
	m_checkLogFileUserTimeline = FALSE;
    m_checkMultiPost = FALSE;
	//}}AFX_DATA_INIT

    m_initialized = false;
    m_chirrup     = NULL;
}

void CTabDialog::InputFileName( CString &targetFilename, int id )
{
    CFileDialog *fileDlg = NULL;
    CString     fileName;
    CString     fileType;
    const char  *fileExtention;
    const char  *fileDefault = NULL;

    fileExtention = "txt";
    fileType = _T("テキストファイル (*.txt)|*.txt||");

    if ( fileExtention )
        fileDlg = new CFileDialog( FALSE, fileExtention, fileDefault,
                                   OFN_CREATEPROMPT,
                                   fileType );
    if ( fileDlg ) {
        if ( fileDlg->DoModal() == IDOK )
            fileName = fileDlg->GetPathName();
        delete fileDlg;

        if ( fileName.GetLength() > 0 ) {
            targetFilename = fileName;

            CEdit   *p = (CEdit *)GetDlgItem( id );
            p->SetWindowText( targetFilename );
        }
    }
}

void CTabDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabDialog)
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_username);
	DDV_MaxChars(pDX, m_username, 64);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_password);
	DDV_MaxChars(pDX, m_password, 32);
	DDX_Text(pDX, IDC_EDIT_LOGFILENAME, m_logFile_friendsTimeline);
	DDV_MaxChars(pDX, m_logFile_friendsTimeline, 1024);
	DDX_Text(pDX, IDC_EDIT_LOGFILENAME2, m_logFile_publicTimeline);
	DDV_MaxChars(pDX, m_logFile_publicTimeline, 1024);
	DDX_Text(pDX, IDC_EDIT_LOGFILENAME3, m_logFile_userTimeline);
	DDV_MaxChars(pDX, m_logFile_userTimeline, 1024);
	DDX_Check(pDX, IDC_CHECK_FRIENDS_TIMELINE, m_checkFriendsTimeline);
	DDX_Check(pDX, IDC_CHECK_PUBLIC_TIMELINE, m_checkPublicTimeline);
	DDX_Check(pDX, IDC_CHECK_USER_TIMELINE, m_checkUserTimeline);
	DDX_Check(pDX, IDC_CHECK_FRIENDS_TIMELINE2, m_checkLogFileFriendsTimeline);
	DDX_Check(pDX, IDC_CHECK_PUBLIC_TIMELINE2, m_checkLogFilePublicTimeline);
	DDX_Check(pDX, IDC_CHECK_USER_TIMELINE2, m_checkLogFileUserTimeline);
	DDX_Check(pDX, IDC_CHECK_MULTIPOST, m_checkMultiPost);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CTabDialog 追加メソッド

void CTabDialog::SetCheckFriendsTimeline()
{
    CButton *bp;
    CEdit   *ep = (CEdit *)GetDlgItem( IDC_EDIT_LOGFILENAME );

    if ( m_checkFriendsTimeline ) {
        ep->SetReadOnly( FALSE );

        bp = (CButton *)GetDlgItem( IDC_CHECK_FRIENDS_TIMELINE2 );
        bp->EnableWindow( TRUE );

        bp = (CButton *)GetDlgItem( IDC_BUTTON_FILESPEC );
        bp->EnableWindow( TRUE );
    }
    else {
        ep->SetReadOnly( TRUE );

        bp = (CButton *)GetDlgItem( IDC_CHECK_FRIENDS_TIMELINE2 );
        bp->EnableWindow( FALSE );

        bp = (CButton *)GetDlgItem( IDC_BUTTON_FILESPEC );
        bp->EnableWindow( FALSE );
    }
}

void CTabDialog::SetCheckPublicTimeline()
{
    CButton *bp;
    CEdit   *ep = (CEdit *)GetDlgItem( IDC_EDIT_LOGFILENAME2 );

    if ( m_checkPublicTimeline ) {
        ep->SetReadOnly( FALSE );

        bp = (CButton *)GetDlgItem( IDC_CHECK_PUBLIC_TIMELINE2 );
        bp->EnableWindow( TRUE );

        bp = (CButton *)GetDlgItem( IDC_BUTTON_FILESPEC2 );
        bp->EnableWindow( TRUE );
    }
    else {
        ep->SetReadOnly( TRUE );

        bp = (CButton *)GetDlgItem( IDC_CHECK_PUBLIC_TIMELINE2 );
        bp->EnableWindow( FALSE );

        bp = (CButton *)GetDlgItem( IDC_BUTTON_FILESPEC2 );
        bp->EnableWindow( FALSE );
    }
}

void CTabDialog::SetCheckUserTimeline()
{
    CButton *bp;
    CEdit   *ep = (CEdit *)GetDlgItem( IDC_EDIT_LOGFILENAME3 );

    if ( m_checkUserTimeline ) {
        ep->SetReadOnly( FALSE );

        bp = (CButton *)GetDlgItem( IDC_CHECK_USER_TIMELINE2 );
        bp->EnableWindow( TRUE );

        bp = (CButton *)GetDlgItem( IDC_BUTTON_FILESPEC3 );
        bp->EnableWindow( TRUE );
    }
    else {
        ep->SetReadOnly( TRUE );

        bp = (CButton *)GetDlgItem( IDC_CHECK_USER_TIMELINE2 );
        bp->EnableWindow( FALSE );

        bp = (CButton *)GetDlgItem( IDC_BUTTON_FILESPEC3 );
        bp->EnableWindow( FALSE );
    }
}

void CTabDialog::setTimelineInfo(
                        TIMELINE_INFO &s,
                        CString       logFile,
                        BOOL          checkTimeline,
                        BOOL          checkLogFile
                    )
{
    s.logFileName   = logFile;
    s.checkTimeline = checkTimeline ? true : false;
    s.checkLogFile  = checkLogFile  ? true : false;
}

void CTabDialog::getTimelineInfo(
                        TIMELINE_INFO s,
                        CString       &logFile,
                        BOOL          &checkTimeline,
                        BOOL          &checkLogFile
                    )
{
    logFile = s.logFileName;
    checkTimeline = s.checkTimeline ? TRUE : FALSE;
    checkLogFile  = s.checkLogFile  ? TRUE : FALSE;
}

BEGIN_MESSAGE_MAP(CTabDialog, CDialog)
	//{{AFX_MSG_MAP(CTabDialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_FILESPEC, OnButtonFilespec)
	ON_BN_CLICKED(IDC_BUTTON_FILESPEC2, OnButtonFilespec2)
	ON_BN_CLICKED(IDC_BUTTON_FILESPEC3, OnButtonFilespec3)
	ON_BN_CLICKED(IDC_CHECK_FRIENDS_TIMELINE, OnCheckFriendsTimeline)
	ON_BN_CLICKED(IDC_CHECK_PUBLIC_TIMELINE, OnCheckPublicTimeline)
	ON_BN_CLICKED(IDC_CHECK_USER_TIMELINE, OnCheckUserTimeline)
	ON_BN_CLICKED(IDC_CHECK_PUBLIC_TIMELINE2, OnCheckPublicTimeline2)
	ON_BN_CLICKED(IDC_CHECK_USER_TIMELINE2, OnCheckUserTimeline2)
	ON_BN_CLICKED(IDC_CHECK_FRIENDS_TIMELINE2, OnCheckFriendsTimeline2)
	ON_BN_CLICKED(IDC_CHECK_MULTIPOST, OnCheckMultiPost)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabDialog メッセージ ハンドラ

void CTabDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        LoadSetting();

        CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_USERNAME);
        p->SetWindowText( m_username );

        p = (CEdit *)GetDlgItem(IDC_EDIT_PASSWORD);
        p->SetWindowText( m_password );

        CButton *bp = (CButton *)GetDlgItem( IDC_CHECK_MULTIPOST );
        bp->SetCheck( m_checkMultiPost );

        p = (CEdit *)GetDlgItem(IDC_EDIT_LOGFILENAME);
        p->SetWindowText( m_logFile_friendsTimeline );

        p = (CEdit *)GetDlgItem(IDC_EDIT_LOGFILENAME2);
        p->SetWindowText( m_logFile_publicTimeline );

        p = (CEdit *)GetDlgItem(IDC_EDIT_LOGFILENAME3);
        p->SetWindowText( m_logFile_userTimeline );

        bp = (CButton *)GetDlgItem( IDC_CHECK_FRIENDS_TIMELINE );
        bp->SetCheck( m_checkFriendsTimeline );
        
        bp = (CButton *)GetDlgItem( IDC_CHECK_PUBLIC_TIMELINE );
        bp->SetCheck( m_checkPublicTimeline );
        
        bp = (CButton *)GetDlgItem( IDC_CHECK_USER_TIMELINE );
        bp->SetCheck( m_checkUserTimeline );

        bp = (CButton *)GetDlgItem( IDC_CHECK_FRIENDS_TIMELINE2 );
        bp->SetCheck( m_checkLogFileFriendsTimeline );
        
        bp = (CButton *)GetDlgItem( IDC_CHECK_PUBLIC_TIMELINE2 );
        bp->SetCheck( m_checkLogFilePublicTimeline );
        
        bp = (CButton *)GetDlgItem( IDC_CHECK_USER_TIMELINE2 );
        bp->SetCheck( m_checkLogFileUserTimeline );

        SetCheckFriendsTimeline();
        SetCheckPublicTimeline();
        SetCheckUserTimeline();

        m_initialized = true;
    }
    else {
        CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_USERNAME);
        p->GetWindowText( m_username );

        p = (CEdit *)GetDlgItem(IDC_EDIT_PASSWORD);
        p->GetWindowText( m_password );

        p = (CEdit *)GetDlgItem(IDC_EDIT_LOGFILENAME);
        p->GetWindowText( m_logFile_friendsTimeline );

        p = (CEdit *)GetDlgItem(IDC_EDIT_LOGFILENAME2);
        p->GetWindowText( m_logFile_publicTimeline );

        p = (CEdit *)GetDlgItem(IDC_EDIT_LOGFILENAME3);
        p->GetWindowText( m_logFile_userTimeline );
    }
}

void CTabDialog::OnButtonFilespec() 
{
    InputFileName( m_logFile_friendsTimeline, IDC_EDIT_LOGFILENAME );
}

void CTabDialog::OnButtonFilespec2() 
{
    InputFileName( m_logFile_publicTimeline, IDC_EDIT_LOGFILENAME2 );
}

void CTabDialog::OnButtonFilespec3() 
{
    InputFileName( m_logFile_userTimeline, IDC_EDIT_LOGFILENAME3 );
}


void CTabDialog::OnCheckFriendsTimeline() 
{
    CButton *bp = (CButton *)GetDlgItem( IDC_CHECK_FRIENDS_TIMELINE );
    m_checkFriendsTimeline = bp->GetCheck();

    SetCheckFriendsTimeline();
}

void CTabDialog::OnCheckPublicTimeline() 
{
    CButton *bp = (CButton *)GetDlgItem( IDC_CHECK_PUBLIC_TIMELINE );
    m_checkPublicTimeline = bp->GetCheck();

    SetCheckPublicTimeline();
}

void CTabDialog::OnCheckUserTimeline() 
{
    CButton *bp = (CButton *)GetDlgItem( IDC_CHECK_USER_TIMELINE );
    m_checkUserTimeline = bp->GetCheck();

    SetCheckUserTimeline();
}

void CTabDialog::OnCheckFriendsTimeline2() 
{
    CButton *bp = (CButton *)GetDlgItem( IDC_CHECK_FRIENDS_TIMELINE2 );
    m_checkLogFileFriendsTimeline = bp->GetCheck();
}

void CTabDialog::OnCheckPublicTimeline2() 
{
    CButton *bp = (CButton *)GetDlgItem( IDC_CHECK_PUBLIC_TIMELINE2 );
    m_checkLogFilePublicTimeline = bp->GetCheck();
}

void CTabDialog::OnCheckUserTimeline2() 
{
    CButton *bp = (CButton *)GetDlgItem( IDC_CHECK_USER_TIMELINE2 );
    m_checkLogFileUserTimeline = bp->GetCheck();
}

void CTabDialog::OnCheckMultiPost() 
{
    CButton *bp = (CButton *)GetDlgItem( IDC_CHECK_MULTIPOST );
    m_checkMultiPost = bp->GetCheck();
}
