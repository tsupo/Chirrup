/*
 * SettingProxy.cpp : Twitter クライアント chirrup
 *      設定ダイアログ(proxy設定) インプリメンテーション ファイル
 *          written by H.Tsujimura  9 Mar 2007 / 6 Apr 2007 / 26 Nov 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/SettingProxy.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 6     08/12/19 21:27 Tsujimura543
 * まだ m_initialized が false の状態で UpdateDataEx() が呼び出された
 * 場合のことを考慮するようにした
 * 
 * 5     08/12/19 20:50 Tsujimura543
 * UpdateDataEx() を追加
 * 
 * 4     08/07/14 17:56 Tsujimura543
 * m_proxyPortNumber に負の値が入っている状態でダイアログが
 * 呼び出された場合は、いったん m_proxyPortNumber を 0 にする
 * ようにした
 * 
 * 3     07/11/26 18:04 Tsujimura543
 * proxy設定関連移行作業、完了
 * 
 * 2     07/11/26 17:57 Tsujimura543
 * CProxyInfoDialog を廃止し、CSettingProxy に移行
 * 
 * 1     07/11/26 17:30 Tsujimura543
 * 最初の版
 */

#include "chirrup.h"
#include "chirrupDlg.h"
#include "SettingProxy.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/SettingProxy.cpp 1     09/05/14 3:50 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingProxy ダイアログ

CSettingProxy::CSettingProxy(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingProxy::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingProxy)
	m_useProxy = FALSE;
	m_proxyServerName = _T("");
	m_proxyPortNumber = 0;
	m_proxyUserName = _T("");
	m_proxyPassword = _T("");
	//}}AFX_DATA_INIT

    m_initialized = false;
    m_chirrup     = NULL;
}

// 「設定ダイアログ」での「適用」ボタン押下時処理
void CSettingProxy::Accept()
{
    if ( m_initialized && m_chirrup ) {
        m_chirrup->SetProxy( m_useProxy,
                             m_proxyServerName, m_proxyPortNumber,
                             m_proxyUserName, m_proxyPassword );
    }
}

// 現在の「設定」を取得
void CSettingProxy::LoadSetting()
{
    if ( !m_initialized ) {
        if ( m_chirrup ) {
            m_chirrup->GetProxy( m_useProxy,
                                 m_proxyServerName, m_proxyPortNumber,
                                 m_proxyUserName, m_proxyPassword );
        }
    }
}

// 設定しようとしている値のチェック
BOOL CSettingProxy::UpdateDataEx()
{
    if ( !m_initialized )
        return ( TRUE );

    BOOL    ret = TRUE;
    CString str;
    CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_PROXY_PORT_NUMBER);
    p->GetWindowText( str );

    int portNumber =
        (str.GetLength() > 0) && (str[0] >= '1') && (str[0] <= '9')
            ? (unsigned int)atol( str )
            : -1;
    if ( portNumber == -1 ) {
        MessageBox( "proxyサーバのポート番号は 0 ～ 65535 の範囲の整数を"
                    "指定してください  ",
                    "proxyサーバのポート番号",
                    MB_OK|MB_ICONWARNING );
        ret = FALSE;
    }

    return ( ret );
}

void CSettingProxy::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingProxy)
	DDX_Check(pDX, IDC_USE_PROXY, m_useProxy);
	DDX_Text(pDX, IDC_EDIT_PROXY_SERVER_NAME, m_proxyServerName);
	DDV_MaxChars(pDX, m_proxyServerName, 384);
	DDX_Text(pDX, IDC_EDIT_PROXY_PORT_NUMBER, m_proxyPortNumber);
	DDV_MinMaxUInt(pDX, m_proxyPortNumber, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_PROXY_USER_NAME, m_proxyUserName);
	DDV_MaxChars(pDX, m_proxyUserName, 32);
	DDX_Text(pDX, IDC_EDIT_PROXY_PASSWORD, m_proxyPassword);
	DDV_MaxChars(pDX, m_proxyPassword, 32);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSettingProxy, CDialog)
	//{{AFX_MSG_MAP(CSettingProxy)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_USE_PROXY, OnUseProxy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingProxy 追加メソッド

void CSettingProxy::SetCheckProxy()
{
    CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_PROXY_SERVER_NAME);
    p->EnableWindow( m_useProxy );

    p = (CEdit *)GetDlgItem(IDC_EDIT_PROXY_PORT_NUMBER);
    p->EnableWindow( m_useProxy );

    p = (CEdit *)GetDlgItem(IDC_EDIT_PROXY_USER_NAME);
    p->EnableWindow( m_useProxy );

    p = (CEdit *)GetDlgItem(IDC_EDIT_PROXY_PASSWORD);
    p->EnableWindow( m_useProxy );
}

/////////////////////////////////////////////////////////////////////////////
// CSettingProxy メッセージ ハンドラ

void CSettingProxy::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

    if ( bShow ) {
        LoadSetting();

        CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_PROXY_SERVER_NAME);
        p->SetWindowText( m_proxyServerName );

        char    str[BUFSIZ];
        str[0] = NUL;
        if ( m_proxyPortNumber > 0 )
            sprintf( str, "%d", m_proxyPortNumber );
        else                        /* {@@} */
            m_proxyPortNumber = 0;  /* {@@} */
        p = (CEdit *)GetDlgItem(IDC_EDIT_PROXY_PORT_NUMBER);
        p->SetWindowText( str );

        p = (CEdit *)GetDlgItem(IDC_EDIT_PROXY_USER_NAME);
        p->SetWindowText( m_proxyUserName );

        p = (CEdit *)GetDlgItem(IDC_EDIT_PROXY_PASSWORD);
        p->SetWindowText( m_proxyPassword );

        CButton *bp = (CButton *)GetDlgItem( IDC_USE_PROXY );
        bp->SetCheck( m_useProxy );

        SetCheckProxy();

        m_initialized = true;
    }
    else {
        CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_PROXY_SERVER_NAME);
        p->GetWindowText( m_proxyServerName );

        CString str;
        p = (CEdit *)GetDlgItem(IDC_EDIT_PROXY_PORT_NUMBER);
        p->GetWindowText( str );
        m_proxyPortNumber = (unsigned int)atol( str );

        p = (CEdit *)GetDlgItem(IDC_EDIT_PROXY_USER_NAME);
        p->GetWindowText( m_proxyUserName );

        p = (CEdit *)GetDlgItem(IDC_EDIT_PROXY_PASSWORD);
        p->GetWindowText( m_proxyPassword );
    }
}

void CSettingProxy::OnUseProxy() 
{
    CButton *bp = (CButton *)GetDlgItem( IDC_USE_PROXY );
    m_useProxy  = bp->GetCheck();

    SetCheckProxy();
}
