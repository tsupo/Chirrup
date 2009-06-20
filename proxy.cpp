/*
 * proxy.cpp : Twitter クライアント chirrup
 *      プロクシ設定関連 インプリメンテーション ファイル
 *          written by H.Tsujimura  26 Nov 2007 / 13 Dec 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/proxy.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     07/12/20 16:36 Tsujimura543
 * 初期設定ファイルがまだ存在しない状態で起動したときにproxy設定処理が2回
 * 動いてしまう不具合を修正
 * 
 * 2     07/12/13 19:00 Tsujimura543
 * コメントを修正
 * 
 * 1     07/12/13 18:52 Tsujimura543
 * proxy関連の関数群を chirrupDlg.cpp から分離独立させた
 */

#include "chirrup.h"
#include "chirrupDlg.h"
#include "SettingDialog.h"
#include "proxy.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/proxy.cpp 1     09/05/14 3:50 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// proxy関連

#define FILE_CONFIG_PROXY   "./proxy.txt"

void
initProxyInfo()
{
    unlink( FILE_CONFIG_PROXY );
}

bool
checkProxyInfo()
{
    bool    ret = isNecessaryToCheckProxyInfo() ? true : false;

    if ( ret )
        initProxyInfo();

    return ( ret );
}

void DoSettingProxy( CChirrupDlg *p ) 
{
    CChirrupApp *ap = (CChirrupApp *)AfxGetApp();
    setConfirmProxyInfoFunc( (CONF_FUNC)(-1) );
    int r = MessageBox( NULL,
                        "proxyサーバ経由でインターネットを"
                        "利用していますか?",
                        "インターネット利用形態確認",
                        MB_YESNO|MB_ICONQUESTION );

    if ( r == IDYES ) {
        CSettingDialog  dlg;
        dlg.m_settingProxy = true;
		dlg.m_chirrup      = p;

        dlg.DoModal();
        if ( ap->m_isUsedProxy ) {
            FILE    *fp;
            if ( ( fp = fopen( FILE_CONFIG_PROXY, "w" ) ) != NULL ) {
                fprintf( fp, "%s\n", (const char *)ap->m_proxyServer );
                fprintf( fp, "%d\n", ap->m_proxyPort );

                if ( ap->m_proxyUserName.GetLength() > 0 ) {
                    fprintf( fp, "%s\n", (const char *)ap->m_proxyUserName );

                    if ( ap->m_proxyPassword.GetLength() > 0 )
                        fprintf( fp, "%s\n",
                                 (const char *)ap->m_proxyPassword );
                }
                fclose( fp );
            }
        }
        else
            initProxyInfo();
    }
    else
        ap->m_isUsedProxy = false;
}

int confirmProxyInfo( int            *useProxy,
                      char           *proxyServer,
                      unsigned short *proxyPort,
                      char           *proxyUserName,
                      char           *proxyPassword )
{
    int         ret = TRUE;
    CChirrupApp *ap = (CChirrupApp *)AfxGetApp();

    DoSettingProxy( ap->m_chirrpDlg );

    *useProxy = ap->m_isUsedProxy;
    if ( ap->m_proxyServer.GetLength() > 0 )
        strcpy( proxyServer, ap->m_proxyServer );
    else
        *proxyServer = NUL;

    *proxyPort = (unsigned short)(ap->m_proxyPort);

    if ( ap->m_proxyUserName.GetLength() > 0 )
        strcpy( proxyUserName, ap->m_proxyUserName );
    else
        *proxyUserName = NUL;

    if ( ap->m_proxyPassword.GetLength() > 0 )
        strcpy( proxyPassword, ap->m_proxyPassword );
    else
        *proxyPassword = NUL;

    return ( ret );
}
