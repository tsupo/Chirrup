/*
 * http.cpp : Twitter クライアント chirrup
 *      http関連 インプリメンテーション ファイル
 *          written by H.Tsujimura  19 Jun 2007 / 19 Dec 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/http.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     08/03/26 22:15 Tsujimura543
 * 排他制御を強化
 * 
 * 1     07/12/19 18:42 Tsujimura543
 * http関連の関数群を CService.cpp から分離
 */

#include "chirrup.h"
#include "http.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/http.cpp 1     09/05/14 3:50 tsupo $";
#endif


typedef struct param_thread {
    char    *url;
    char    *userName;
    char    *password;
    char    *request;
    char    *response;
    char    *cookie;
}   PARAM_THREAD;

static BOOL             httpInitialized     = FALSE;
static BOOL             executingHTTPthread = FALSE;
static CRITICAL_SECTION cs_executingHTTPthread;

void    _http_startUp()
{
    InitializeCriticalSection( &cs_executingHTTPthread );
    httpInitialized = TRUE;
}

void    _http_shutDown()
{
    DeleteCriticalSection( &cs_executingHTTPthread );
    httpInitialized = FALSE;
}


BOOL    getExecutingHTTPthread()
{
    BOOL    ret;

    EnterCriticalSection( &cs_executingHTTPthread );
    ret = executingHTTPthread;
    LeaveCriticalSection( &cs_executingHTTPthread );

    return ( ret );
}

void    setExecutingHTTPthread( BOOL value )
{
    EnterCriticalSection( &cs_executingHTTPthread );
    executingHTTPthread = value;
    LeaveCriticalSection( &cs_executingHTTPthread );
}


UINT
__http_postBASIC( LPVOID pParam )
{
    PARAM_THREAD    *p    = (PARAM_THREAD *)pParam;
    UINT            ret   = 0;
    int             retry = 100;

    while ( getExecutingHTTPthread() ) {
        retry--;
        if ( retry <= 0 )
            return ( ret );
        Sleep( 500 );
    }

    setExecutingHTTPthread( TRUE );
    if ( p->cookie )
        http_postEx( p->url,
                     "application/x-www-form-urlencoded",
                     p->request, p->response, p->cookie );
    else
        http_postBASIC( p->url, p->userName, p->password,
                        "application/x-www-form-urlencoded",
                        p->request, p->response );
    setExecutingHTTPthread( FALSE );

    return ( ret );
}

char    *
_http_postBASIC( const char       *url,
                 const char       *userName,
                 const char       *password,
                 const char       *request,
                 char             *response,
                 char             *cookie,
                 ProceedingDialog *pdlg )
{
    PARAM_THREAD    param;

    if ( pdlg )
        pdlg->ShowWindow( SW_SHOWNORMAL );

    param.url      = (char *)url;
    param.userName = (char *)userName;
    param.password = (char *)password;
    param.request  = (char *)request;
    param.response = response;
    param.cookie   = cookie;

    // http_postBASIC 実行スレッドを起動
    CWinThread  *tp = AfxBeginThread( __http_postBASIC,
                                      (void *)&param );

    if ( tp ) {
        DWORD       exitCode  = 0;
        int         status;
        CWaitCursor cur;    // マウスカーソルを砂時計表示

        // http_postBASIC 実行スレッドが終了するのを待つ
        tp->m_bAutoDelete = FALSE;
        do {
            status = GetExitCodeThread( tp->m_hThread, &exitCode );
            if ( status == FALSE )
                break;
            if ( exitCode == STILL_ACTIVE ) {
                // CChirrupDlg の再描画
                MSG msg;
                if ( PeekMessage( &msg, 0, WM_PAINT, WM_PAINT, PM_REMOVE ) )
                    DispatchMessage( &msg );

                if ( pdlg ) {
                    // ProceedingDialog の再描画
                    pdlg->SetFocus();
                    pdlg->UpdateWindow();
                }
                Sleep( 200 );
            }
        } while ( exitCode == STILL_ACTIVE );

        delete tp;
    }

    if ( pdlg )
        pdlg->ShowWindow( SW_HIDE );

    return ( response );
}

char    *
_http_post( const char       *url,
            const char       *request,
            char             *response,
            ProceedingDialog *pdlg )
{
    return (_http_postBASIC(url, NULL, NULL, request, response, NULL, pdlg));
}



UINT
__http_getBASIC( LPVOID pParam )
{
    PARAM_THREAD    *p  = (PARAM_THREAD *)pParam;
    UINT            ret = 0;
    int             retry = 100;

    while ( getExecutingHTTPthread() ) {
        retry--;
        if ( retry <= 0 )
            return ( ret );
        Sleep( 500 );
    }

    setExecutingHTTPthread( TRUE );
    http_getBASICEx(p->url, p->userName, p->password, p->response, p->cookie);
    setExecutingHTTPthread( FALSE );

    return ( ret );
}

char    *
_http_getBASIC( const char       *url,
                const char       *userName,
                const char       *password,
                char             *response,
                char             *cookie,
                ProceedingDialog *pdlg )
{
    PARAM_THREAD    param;

    if ( pdlg )
        pdlg->ShowWindow( SW_SHOWNORMAL );

    param.url      = (char *)url;
    param.userName = (char *)userName;
    param.password = (char *)password;
    param.response = response;
    param.cookie   = cookie;

    // http_getBASIC 実行スレッドを起動
    CWinThread  *tp = AfxBeginThread( __http_getBASIC,
                                      (void *)&param );

    if ( tp ) {
        DWORD       exitCode  = 0;
        int         status;
        CWaitCursor cur;    // マウスカーソルを砂時計表示

        // http_getBASIC 実行スレッドが終了するのを待つ
        tp->m_bAutoDelete = FALSE;
        do {
            status = GetExitCodeThread( tp->m_hThread, &exitCode );
            if ( status == FALSE )
                break;
            if ( exitCode == STILL_ACTIVE ) {
                // CChirrupDlg の再描画
                MSG msg;
                if ( PeekMessage( &msg, 0, WM_PAINT, WM_PAINT, PM_REMOVE ) )
                    DispatchMessage( &msg );

                if ( pdlg ) {
                    // ProceedingDialog の再描画
                    pdlg->SetFocus();
                    pdlg->UpdateWindow();
                }
                Sleep( 200 );
            }
        } while ( exitCode == STILL_ACTIVE );

        delete tp;
    }

    if ( pdlg )
        pdlg->ShowWindow( SW_HIDE );

    return ( response );
}

char    *
_http_get( const char       *url,
           char             *response,
           ProceedingDialog *pdlg )
{
    return ( _http_getBASIC( url, NULL, NULL, response, NULL, pdlg ) );
}


char    *
__http_postBASIC( const char *url,
                  const char *userName,
                  const char *password,
                  const char *request,
                  char       *response,
                  char       *cookie )
{
    return ( _http_postBASIC( url,
                              userName, password,
                              request, response, cookie,
                              NULL ) );
}

char    *
__http_getBASIC( const char *url,
                 const char *userName,
                 const char *password,
                 char       *response,
                 char       *cookie )
{
    return ( _http_getBASIC( url,
                             userName, password,
                             response, cookie,
                             NULL ) );
}
