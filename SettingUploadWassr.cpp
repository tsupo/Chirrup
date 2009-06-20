/*
 * SettingUploadWassr.cpp : Wassr クライアント chirrup
 *      画像投稿関連設定ダイアログ(Wassr) インプリメンテーション ファイル
 *          written by H.Tsujimura  31 Jul 2008
 *
 *      Copyright (c) 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/SettingUploadWassr.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     08/07/31 20:26 Tsujimura543
 * 「状況に応じた入力可能/不可の切替処理」を修正
 * 
 * 1     08/07/31 17:34 Tsujimura543
 * 新規作成
 */

#include "chirrup.h"
#include "SettingUploadWassr.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/SettingUploadWassr.cpp 1     09/05/14 3:50 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingUploadWassr ダイアログ

CSettingUploadWassr::CSettingUploadWassr(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingUploadWassr::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingUploadWassr)
	m_applied = FALSE;
	m_writeLogfile = FALSE;
	m_logFilename = _T("");
	//}}AFX_DATA_INIT
}

void CSettingUploadWassr::InputFileName( CString &targetFilename, int id )
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

void CSettingUploadWassr::SetCheckApplied()
{
    CButton *bp = (CButton *)GetDlgItem(IDC_WRITE_LOGFILE);
    bp->EnableWindow( m_applied );

    SetCheckWriteLogfile();
}

void CSettingUploadWassr::SetCheckWriteLogfile()
{
    CEdit   *ep = (CEdit *)GetDlgItem(IDC_EDIT_LOGFILENAME_UPLOAD);
    ep->EnableWindow( m_applied && m_writeLogfile );

    CButton *bp = (CButton *)GetDlgItem(IDC_BUTTON_FILESPEC);
    bp->EnableWindow( m_applied && m_writeLogfile );
}

void CSettingUploadWassr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingUploadWassr)
	DDX_Check(pDX, IDC_APPLIED, m_applied);
	DDX_Check(pDX, IDC_WRITE_LOGFILE, m_writeLogfile);
	DDX_Text(pDX, IDC_EDIT_LOGFILENAME_UPLOAD, m_logFilename);
	DDV_MaxChars(pDX, m_logFilename, 256);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSettingUploadWassr, CDialog)
	//{{AFX_MSG_MAP(CSettingUploadWassr)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_WRITE_LOGFILE, OnWriteLogfile)
	ON_BN_CLICKED(IDC_BUTTON_FILESPEC, OnButtonFilespec)
	ON_BN_CLICKED(IDC_APPLIED, OnApplied)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingUploadWassr メッセージ ハンドラ

void CSettingUploadWassr::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        CButton *bp = (CButton *)GetDlgItem( IDC_APPLIED );
        bp->SetCheck( m_applied );

        bp = (CButton *)GetDlgItem( IDC_WRITE_LOGFILE );
        bp->SetCheck( m_writeLogfile );

        CEdit   *ep = (CEdit *)GetDlgItem(IDC_EDIT_LOGFILENAME_UPLOAD);
        ep->SetWindowText( m_logFilename );

        SetCheckApplied();
    }
    else {
        CEdit   *ep = (CEdit *)GetDlgItem(IDC_EDIT_LOGFILENAME_UPLOAD);
        ep->GetWindowText( m_logFilename );
    }
}

void CSettingUploadWassr::OnApplied() 
{
    CButton *bp = (CButton *)GetDlgItem( IDC_APPLIED );
    m_applied = bp->GetCheck();

    SetCheckApplied();
}

void CSettingUploadWassr::OnWriteLogfile() 
{
    CButton *bp = (CButton *)GetDlgItem( IDC_WRITE_LOGFILE );
    m_writeLogfile = bp->GetCheck();

    SetCheckWriteLogfile();
}

void CSettingUploadWassr::OnButtonFilespec() 
{
    InputFileName( m_logFilename, IDC_EDIT_LOGFILENAME_UPLOAD );
}
