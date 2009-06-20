/*
 * SettingFlickr.cpp : Twitter クライアント chirrup
 *      設定ダイアログ(Flickr) インプリメンテーション ファイル
 *          written by H.Tsujimura  9 Jan 2008
 *
 *      Copyright (c) 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/SettingFlickr.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     09/04/22 21:11 Tsujimura543
 * 「設定」ダイアログからもFlickr認証のアクセストークン(frob)を取得できる
 * ようにした
 * 
 * 2     08/01/10 17:22 Tsujimura543
 * CTabDialog2 を導入し、ソースコードを整理した
 * 
 * 1     08/01/09 17:07 Tsujimura543
 * 新規作成
 */

#include "chirrup.h"
#include "chirrupDlg.h"
#include "SettingFlickr.h"
extern "C" {
#include "flickr.h"
}

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/SettingFlickr.cpp 1     09/05/14 3:50 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingFlickr ダイアログ

CSettingFlickr::CSettingFlickr(CWnd* pParent /*=NULL*/)
	: CTabDialog2(CSettingFlickr::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingFlickr)
	//}}AFX_DATA_INIT

    m_flickrToken    = _T("");
    m_flickrUserName = _T("");
}

// 「設定ダイアログ」での「適用」ボタン押下時処理
void CSettingFlickr::Accept()
{
    if ( m_initialized && m_chirrup ) {
        m_chirrup->SetFlickr( m_applied, m_writeLogfile, m_logFilename,
                              m_flickrToken, m_flickrUserName );
    }
}

// 現在の「設定」を取得
void CSettingFlickr::LoadSetting()
{
    if ( !m_initialized ) {
        if ( m_chirrup ) {
            m_chirrup->GetFlickr( m_applied, m_writeLogfile, m_logFilename,
                                  m_flickrToken, m_flickrUserName );
        }
    }
}

void CSettingFlickr::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog2::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingFlickr)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSettingFlickr, CTabDialog2)
	//{{AFX_MSG_MAP(CSettingFlickr)
	ON_BN_CLICKED(IDC_BUTTON_GET_TOKEN, OnButtonGetToken)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingFlickr 追加メソッド

void CSettingFlickr::ShowCurrentStatus()
{
    CString status;
    CStatic *sp = (CStatic *)GetDlgItem( IDC_TOKEN_STATUS );
    if ( (m_flickrToken.GetLength()    > 0) &&
         (m_flickrUserName.GetLength() > 0)    )
	    status.LoadString( IDS_ACCESSTOKEN_ACQUIRED );
    else
	    status.LoadString( IDS_ACCESSTOKEN_UNTAKEN );
    sp->SetWindowText( status );
}

/////////////////////////////////////////////////////////////////////////////
// CSettingFlickr メッセージ ハンドラ

void CSettingFlickr::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CTabDialog2::OnShowWindow(bShow, nStatus);

    if ( bShow ) {
        ShowCurrentStatus();
    }
}

void CSettingFlickr::OnButtonGetToken() 
{
    CChirrupApp *ap = (CChirrupApp *)AfxGetApp();
    char        token[MAX_CATIDLENGTH];     // flickr トークン
    char        username[MAX_CATIDLENGTH];  // flickr ユーザ名
    char        nsid[MAX_LOGICALLINELEN];   // flickr NSID

	token[0]    = NUL;
	username[0] = NUL;
	nsid[0]     = NUL;
    BOOL ret = GetAccessTokenOnFlickr( ap->m_fKey, ap->m_fSecret,
                                       token, username, nsid );
    if ( ret ) {
        m_flickrToken    = token;
        m_flickrUserName = username[0] ? username : nsid;
    }
    else
        MessageBox( "アクセストークンの取得に失敗しました。  ",
                    "Flickr 認証", MB_OK|MB_ICONERROR );

    ShowCurrentStatus();
}
