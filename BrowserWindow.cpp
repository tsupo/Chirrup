/*
 * BrowserWindow.cpp : Twitter クライアント chirrup
 * $Log: /comm/chirrup/BrowserWindow.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 6     07/05/11 21:29 Tsujimura543
 * ブラウザで閲覧中の URL を Twitter に送信するとき、その Web ページの
 * タイトルも取得して送信するようにした
 * 
 * 5     07/04/25 15:20 Tsujimura543
 * 取得した url が https で始まる場合は空文字列を返すように仕様を変更
 * 
 * 4     07/04/25 11:54 Tsujimura543
 * (1) GetUrlByDDE() のバグ修正 (リファクタリング時のミスでエンバグしていた)
 * (2) GetUrlByDDE() 内の不要な関数呼び出しを削除
 * 
 * 3     07/04/24 23:44 Tsujimura543
 * インデント修正、不要になったコメントの削除
 * 
 * 2     07/04/24 23:42 Tsujimura543
 * リファクタリング
 * 
 * 1     07/04/24 23:38 Tsujimura543
 * GetUrlInBrowsing() が期待通り動作することを確認
 *
 * 以下の URL で公開されているソースコードのうち、
 *      GetUrlByDDE()
 *      DdeCallback()
 * の2関数を流用させていただいています(当方で少しいじってます)。
 *
 *     http://www.hirax.net/misc/browser_window/BrowserWindow.h
 *     http://www.hirax.net/misc/browser_window/BrowserWindow.cpp
 */

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/BrowserWindow.cpp 1     09/05/14 3:50 tsupo $";
#endif

#include "chirrup.h"
#include <ddeml.h>
extern "C" {
#include "utility.h"
}

//------------jun hirabayashi jun@hirax.net 2006/05/03------------------
#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
HDDEDATA CALLBACK DdeCallback(
                    UINT     uType,
                    UINT     uFmt,
                    HCONV    hconv,
                    HSZ      hsz1,
                    HSZ      hsz2,
                    HDDEDATA hdata,
                    DWORD    dwData1,
                    DWORD    dwData2 )
{
    HDDEDATA ret = NULL;

    switch ( uType ) {
    case XTYP_ADVDATA:
        ret = (HDDEDATA)DDE_FACK;
        break;
    }

    return ( ret );
}
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif


//------最前面Windowの情報更新   --------------------
#define IE_STRING   " - Microsoft Internet Explorer"
#define IE7_STRING  " - Windows Internet Explorer"
#define SLEIPNIR    "Sleipnir - "
#define SLEIPNIR2   " - Sleipnir"
#define FIREFOX     " - Mozilla Firefox"
#define MOZILLA     " - Mozilla"
#define OPERA       " - Opera"
#define FLOCK       " - Flock"
#define NETSCAPE8   " - Netscape Browser"
#define NETSCAPE    " - Netscape"

//------DDE経由で取得------------------------------------
bool GetUrlByDDE( CString browser, CString &URL )
{
    bool    ret    = false;
    DWORD   idInst = 0;
    UINT    result = DdeInitialize( &idInst, DdeCallback,
                                    APPCMD_CLIENTONLY, 0L );

    URL = _T("");
    if ( result == DMLERR_NO_ERROR ) {
        LPSTR   lpszApplication = browser.GetBuffer(0);
        LPSTR   lpszTopic       = "WWW_GetWindowInfo";
        HSZ     hszApplication  = DdeCreateStringHandle(
                                        idInst, lpszApplication, CP_WINANSI );
        HSZ     hszTopic        = DdeCreateStringHandle(
                                        idInst, lpszTopic, CP_WINANSI );
        HSZ     hszItem         = DdeCreateStringHandle(
                                        idInst, "-1", CP_WINANSI );

        if ( hszApplication && hszTopic && hszItem ) {
            HCONV hConv = DdeConnect(idInst, hszApplication, hszTopic, NULL);

            if ( hConv ) {
                HDDEDATA    hData   = DdeClientTransaction(
                                          NULL, 0, hConv, hszItem,
                                          CF_TEXT, XTYP_REQUEST, 1000, NULL );
                if ( hData ) {
                    char    *pStart = (char *)DdeAccessData( hData, NULL );

                    if ( pStart ) {
                        while ( *pStart++ != '"' )
                            ;
                        if ( *pStart ) {
                            char    *pEnd = pStart;
                            while ( *pEnd != '"' )
                                pEnd++;

                            *pEnd = NUL;
                            URL   = pStart;
                            ret   = true;
                        }
                    }
                }

                DdeDisconnect( hConv );
            }
        }

        if ( hszItem )
            DdeFreeStringHandle( idInst, hszItem );
        if ( hszTopic )
            DdeFreeStringHandle( idInst, hszTopic );
        if ( hszApplication )
            DdeFreeStringHandle( idInst, hszApplication );
        DdeUninitialize( idInst );
    }

    return ( ret );
}


CString GetUrlInBrowsing( CString &pageTitle )
{
#define MAX_TITLE_LEN   1024

    char    title[MAX_TITLE_LEN + 2];
 // char    temp[MAX_TITLE_LEN + 2];
    char    *p;
    CString browser = _T("");
    CString URL     = _T("");

    HWND    h = GetTopWindow( NULL );
    while ( h ) {
        title[0] = NUL;
     // temp[0]  = NUL;
        GetWindowText( h, title, MAX_TITLE_LEN );

        if ( title[0] ) {
            // 複数のブラウザを同時に開いている場合は
            // 最初に発見したブラウザを調査対象にする
            if ( (( p = strstr( title, IE_STRING ) ) != NULL) ||
                 (( p = strstr( title, IE7_STRING )) != NULL)    ) {
                browser = "IEXPLORE";
             // strncpy( temp, title, p - title );
             // temp[p - title] = NUL;
                break;
            }
            if ( ( p = strstr( title, SLEIPNIR ) ) != NULL ) {
                browser = "Sleipnir";
             // strcpy( temp, p + strlen(SLEIPNIR) );
                break;
            }
            if ( ( p = strstr( title, SLEIPNIR2 ) ) != NULL ) {
                browser = "Sleipnir2";
             // strncpy( temp, title, p - title );
             // temp[p - title] = NUL;
                break;
            }
            if ( ( p = strstr( title, FIREFOX ) ) != NULL ) {
                browser = "Firefox";
             // strncpy( temp, title, p - title );
             // temp[p - title] = NUL;
                break;
            }
            if ( ( p = strstr( title, MOZILLA ) ) != NULL ) {
                browser = "Mozilla";
             // strncpy( temp, title, p - title );
             // temp[p - title] = NUL;
                break;
            }
            if ( ( p = strstr( title, OPERA ) ) != NULL ) {
                browser = "Opera";
             // strncpy( temp, title, p - title );
             // temp[p - title] = NUL;
                break;
            }
         // if ( ( p = strstr( title, FLOCK ) ) != NULL ) {
         //     browser = "FLOCK"; // "Flock"; // "flock";
         //     strncpy( temp, title, p - title );
         //     temp[p - title] = NUL;
         //     break;  // Flock は GetUrlByDDE() での URL 取得はできない
         // }
            if ( (( p = strstr( title, NETSCAPE8) ) != NULL) || 
                 (( p = strstr( title, NETSCAPE ) ) != NULL)    ) {
                browser = "NETSCAPE";
             // strncpy( temp, title, p - title );
             // temp[p - title] = NUL;
                break;
            }
        }

        h = GetNextWindow( h, GW_HWNDNEXT );
    }

    if ( browser.GetLength() > 0 ) {
     // if ( temp[0] )          // ブラウザを複数起動しているときは、ここで求
     //     pageTitle = temp;   // めた title と GetUrlByDDE() で求めた URL に
                                // 対応する title が一致するとは限らない
        GetUrlByDDE( browser, URL );
        if ( !strncmp( URL, "https", 5 ) )
            URL = _T("");   // https で始まる場合は捨てる
        else
            pageTitle = getTitle( URL );
    }

    return ( URL );
}
