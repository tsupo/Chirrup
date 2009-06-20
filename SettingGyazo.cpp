/*
 * SettingGyazo.cpp : Twitter クライアント chirrup
 *      設定ダイアログ(Gyazo) インプリメンテーション ファイル
 *          written by H.Tsujimura  10 Dec 2007
 *
 *      Copyright (c) 2007, 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/SettingGyazo.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     08/01/10 17:22 Tsujimura543
 * CTabDialog2 を導入し、ソースコードを整理した
 * 
 * 2     07/12/19 16:12 Tsujimura543
 * Tumblr と Gyazo にアップロードしたファイルの URL を記録する機能を
 * 追加するためのプロパティを追加
 * 
 * 1     07/12/10 16:38 Tsujimura543
 * 新規作成
 */

#include "chirrup.h"
#include "chirrupDlg.h"
#include "SettingGyazo.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/SettingGyazo.cpp 1     09/05/14 3:50 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingGyazo ダイアログ

CSettingGyazo::CSettingGyazo(CWnd* pParent /*=NULL*/)
	: CTabDialog2(CSettingGyazo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingGyazo)
	//}}AFX_DATA_INIT
}

// 「設定ダイアログ」での「適用」ボタン押下時処理
void CSettingGyazo::Accept()
{
    if ( m_initialized && m_chirrup ) {
        m_chirrup->SetGyazo( m_applied, m_writeLogfile, m_logFilename );
    }
}

// 現在の「設定」を取得
void CSettingGyazo::LoadSetting()
{
    if ( !m_initialized ) {
        if ( m_chirrup ) {
            m_chirrup->GetGyazo( m_applied, m_writeLogfile, m_logFilename );
        }
    }
}

void CSettingGyazo::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog2::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingGyazo)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSettingGyazo, CTabDialog2)
	//{{AFX_MSG_MAP(CSettingGyazo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
