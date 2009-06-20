/*
 * SettingHatena.cpp : Twitter クライアント chirrup
 *      設定ダイアログ(Hatena) インプリメンテーション ファイル
 *          written by H.Tsujimura  24 Aug 2007
 *
 *      Copyright (c) 2007, 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/SettingHatena.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     08/01/19 2:10 Tsujimura543
 * はてなフォトライフ対応
 * 
 * 1     07/08/25 0:14 Tsujimura543
 * 最初の版
 */

#include "chirrup.h"
#include "chirrupDlg.h"
#include "SettingHatena.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/SettingHatena.cpp 1     09/05/14 3:50 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingHatena ダイアログ

CSettingHatena::CSettingHatena(CWnd* pParent /*=NULL*/)
	: CTabDialog2(CSettingHatena::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingHatena)
	m_useTwitStar = FALSE;
	m_username = _T("");
	m_password = _T("");
	//}}AFX_DATA_INIT
}

// 「設定ダイアログ」での「適用」ボタン押下時処理
void CSettingHatena::Accept()
{
    if ( m_initialized && m_chirrup ) {
        m_chirrup->SetHatena( m_username, m_password,
                              m_useTwitStar, m_applied,
                              m_writeLogfile, m_logFilename );
    }
}

// 現在の「設定」を取得
void CSettingHatena::LoadSetting()
{
    if ( !m_initialized ) {
        if ( m_chirrup ) {
            m_chirrup->GetHatena( m_username, m_password,
                                  m_useTwitStar, m_applied,
                                  m_writeLogfile, m_logFilename );
        }
    }
}

void CSettingHatena::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog2::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingHatena)
	DDX_Check(pDX, IDC_USE_TWITSTAR, m_useTwitStar);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_username);
	DDV_MaxChars(pDX, m_username, 64);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_password);
	DDV_MaxChars(pDX, m_password, 64);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSettingHatena, CTabDialog2)
	//{{AFX_MSG_MAP(CSettingHatena)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_USE_TWITSTAR, OnUseTwitstar)
	ON_BN_CLICKED(IDC_APPLIED, OnApplied)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingHatena 追加メソッド

void CSettingHatena::SetCheckApplied()
{
    CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_USERNAME);
    p->EnableWindow( m_useTwitStar || m_applied );

    p = (CEdit *)GetDlgItem(IDC_EDIT_PASSWORD);
    p->EnableWindow( m_useTwitStar || m_applied );

    CButton *bp = (CButton *)GetDlgItem(IDC_WRITE_LOGFILE);
    bp->EnableWindow( m_applied );

    SetCheckWriteLogfile();
}

/////////////////////////////////////////////////////////////////////////////
// CSettingHatena メッセージ ハンドラ

void CSettingHatena::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CTabDialog2::OnShowWindow(bShow, nStatus);

    if ( bShow ) {
        CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_USERNAME);
        p->SetWindowText( m_username );

        p = (CEdit *)GetDlgItem(IDC_EDIT_PASSWORD);
        p->SetWindowText( m_password );

        CButton *bp = (CButton *)GetDlgItem( IDC_USE_TWITSTAR );
        bp->SetCheck( m_useTwitStar );

        SetCheckApplied();
    }
    else {
        CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_USERNAME);
        p->GetWindowText( m_username );

        p = (CEdit *)GetDlgItem(IDC_EDIT_PASSWORD);
        p->GetWindowText( m_password );
    }
}

void CSettingHatena::OnUseTwitstar() 
{
    CButton *bp = (CButton *)GetDlgItem( IDC_USE_TWITSTAR );
    m_useTwitStar = bp->GetCheck();

    SetCheckApplied();
}

void CSettingHatena::OnApplied() 
{
    CButton *bp = (CButton *)GetDlgItem( IDC_APPLIED );
    m_applied = bp->GetCheck();

    SetCheckApplied();
}
