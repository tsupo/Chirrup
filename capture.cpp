/*
 * capture.cpp : Twitter クライアント chirrup
 *      画面キャプチャー関連 インプリメンテーション ファイル
 *          written by H.Tsujimura  14 Dec 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      Some Rights Reserved.
 *
 *      tnj氏の gyazoowin のソースを参考にしています
 *          http://nothing.sh/blog/archives/44
 *
 *      gyazoowin との違いは、gdiplus.dll を使わう代わりに、宮坂賢氏の
 *      bmp2png を使うことで、gdiplus.dll がない環境でも動くようにして
 *      いるところです。有用なソースコードを公開していただいているtnj氏、
 *      宮坂賢氏のお二人に感謝します
 *
 * $Log: /comm/chirrup/capture.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 6     07/12/17 19:51 Tsujimura543
 * capture関連の変数、関数をクラスとしてまとめてみた
 * 
 * 5     07/12/17 18:51 Tsujimura543
 * savePNG() → CImage::SavePngFile() に移行
 * 
 * 4     07/12/15 6:47 Tsujimura543
 * MessageBox() で表示する文言を修正 (デバッグ用)
 * 
 * 3     07/12/15 6:11 Tsujimura543
 * 前回実行時の枠線を消す処理を入れてみた
 * 
 * 2     07/12/15 5:10 Tsujimura543
 * キャプチャに成功し、PNGファイルが生成できるところまで動作を確認。
 * 2回目以降のキャプチャ実行時、前回実行時の破線の枠が残ってしまう現象あり
 * 
 * 1     07/12/15 2:26 Tsujimura543
 * 暫定版 (まだ、うまく動いていないところがある)
 */

#include "chirrup.h"
#include "CImage.h"
#include <sys/stat.h>

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/capture.cpp 1     09/05/14 3:50 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LRESULT CALLBACK
WndProcForCapture( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

// コンストラクタ
CCapture::CCapture() {
    m_dlgForCapture             = NULL;
    m_hInstForCapture           = NULL;
    m_szWindowClass             = NULL;
    m_ofX                       = 0;
    m_ofY                       = 0;
    m_paramUploadImage.dlg      = NULL;
    m_paramUploadImage.filetype = FTYPE_UNKNOWN;
    m_paramUploadImage.filename = _T("");
    m_paramUploadImage.filesize = 0;
    m_paramUploadImage.url      = _T("");
    m_paramUploadImage.caption  = _T("");
}

// 初期化
BOOL
CCapture::InitInstance( CChirrupDlg *dlg, HWND &hWndForCapture )
{
    m_dlgForCapture   = dlg;
    CChirrupApp *ap   = (CChirrupApp *)AfxGetApp();
    m_hInstForCapture = ap->m_hInstance;
    m_szWindowClass   = _T("CHIRRUP");

    WNDCLASSEX wc;

    wc.cbSize        = sizeof ( WNDCLASSEX );
    wc.style         = 0;                           // WM_PAINT を送らない
    wc.lpfnWndProc   = WndProcForCapture;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = m_hInstForCapture;
    wc.hIcon         = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    wc.hCursor       = LoadCursor(NULL, IDC_CROSS); // + のカーソル
    wc.hbrBackground = 0;                           // 背景も設定しない
    wc.lpszMenuName  = 0;
    wc.lpszClassName = m_szWindowClass;
    wc.hIconSm       = NULL;

    RegisterClassEx( &wc );

    int x, y, w, h;

#ifndef SM_XVIRTUALSCREEN
#define SM_XVIRTUALSCREEN       76
#define SM_YVIRTUALSCREEN       77
#define SM_CXVIRTUALSCREEN      78
#define SM_CYVIRTUALSCREEN      79
#endif

    // 仮想スクリーン全体をカバー
    x = GetSystemMetrics(SM_XVIRTUALSCREEN);
    y = GetSystemMetrics(SM_YVIRTUALSCREEN);
    w = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    h = GetSystemMetrics(SM_CYVIRTUALSCREEN);

    // x, y のオフセット値を覚えておく
    m_ofX = x;
    m_ofY = y;

	// 完全に透過したウィンドウを作る
    hWndForCapture =
        CreateWindowEx(
                WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_TOPMOST
#if (_WIN32_WINNT >= 0x0500)
              | WS_EX_NOACTIVATE
#endif
                ,
                m_szWindowClass, NULL, WS_POPUP,
                CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
                NULL, NULL, m_hInstForCapture, NULL );

    // 作れなかった...?
    if ( !hWndForCapture ) {
        dlg->m_inCapturing = false;
        return ( FALSE );
    }
	
    // 全画面を覆う
    ::MoveWindow(hWndForCapture, x, y, w, h, FALSE);

    // nCmdShow を無視 (SW_MAXIMIZE とかされると困る)
    ::ShowWindow(hWndForCapture, SW_SHOW);
    ::UpdateWindow(hWndForCapture);

    return ( TRUE );
}


// ラバーバンドを描画
VOID
CCapture::DrawRubberband(HDC hdc, LPRECT newRect, BOOL erase)
{
    static BOOL firstDraw = TRUE;   // 1 回目は前のバンドの消去を行わない
    static RECT lastRect  = {0};    // 最後に描画したバンド

    // XOR で描画
    int hPreRop = SetROP2( hdc, R2_XORPEN );

    // 点線
    HPEN    hPen = CreatePen( PS_DOT , 1, 0 );
    SelectObject( hdc, hPen );
    SelectObject( hdc, GetStockObject(NULL_BRUSH) );

    if ( !firstDraw ) {
        // 前のを消す
        Rectangle( hdc, lastRect.left, lastRect.top,
                   lastRect.right + 1, lastRect.bottom + 1 );
    }
    else {
        firstDraw = FALSE;
    }

    // 新しい座標を記憶
    lastRect = *newRect;

    if ( !erase ) {
        // 枠を描画
        Rectangle( hdc, lastRect.left, lastRect.top, 
                   lastRect.right + 1, lastRect.bottom + 1 );
    }

    // 後処理
    SetROP2( hdc, hPreRop );
    DeleteObject( hPen );
}

// メッセージループ
LRESULT CALLBACK
CCapture::WindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    HDC         hdc;
    static BOOL onClip   = FALSE;
    static RECT clipRect = {0, 0, 0, 0};

    switch ( message ) {
    case WM_RBUTTONDOWN:
        // キャンセル
        onClip = FALSE;
        if ( m_dlgForCapture )
            m_dlgForCapture->OnEndCapture();
     // DestroyWindow(hWnd);
        break;

    case WM_MOUSEMOVE:
		if ( onClip ) {
			// 新しい座標をセット
			clipRect.right  = LOWORD(lParam) + m_ofX;
			clipRect.bottom = HIWORD(lParam) + m_ofY;
			
			hdc = GetDC(NULL);
			DrawRubberband(hdc, &clipRect, FALSE);
			ReleaseDC(NULL, hdc);
		}
		break;

    case WM_LBUTTONDOWN:
        if ( !onClip ) {
            // クリップ開始
            onClip = TRUE;

            // 前回の線を消す
            HDC hdc = GetDC(NULL);
            DrawRubberband(hdc, &clipRect, TRUE);

            // 初期位置をセット
            clipRect.left = LOWORD(lParam) + m_ofX;
            clipRect.top  = HIWORD(lParam) + m_ofY;

            // マウスをキャプチャ
            SetCapture(hWnd);
        }
        break;

    case WM_LBUTTONUP:
		if ( onClip ) {
            // クリップ終了
            onClip = FALSE;

            // マウスのキャプチャを解除
            ReleaseCapture();

            // 新しい座標をセット
            clipRect.right  = LOWORD(lParam) + m_ofX;
            clipRect.bottom = HIWORD(lParam) + m_ofY;

            // 画面に直接描画，って形
            HDC hdc = GetDC(NULL);

            // 線を消す
            DrawRubberband(hdc, &clipRect, TRUE);

            // 座標チェック
            if ( clipRect.right  < clipRect.left ) {
                int tmp = clipRect.left;
                clipRect.left   = clipRect.right;
                clipRect.right  = tmp;
            }
            if ( clipRect.bottom < clipRect.top  ) {
                int tmp = clipRect.top;
                clipRect.top    = clipRect.bottom;
                clipRect.bottom = tmp;
            }

            // 画像のキャプチャ
            int iWidth, iHeight;
            iWidth  = clipRect.right  - clipRect.left + 1;
            iHeight = clipRect.bottom - clipRect.top  + 1;

            if ( iWidth == 0 || iHeight == 0 ) {
                // 画像になってない, なにもしない
                ReleaseDC(NULL, hdc);
                if ( m_dlgForCapture )
                    m_dlgForCapture->OnEndCapture();
             // DestroyWindow(hWnd);
                break;
            }

            // ビットマップバッファを作成
            HBITMAP newBMP = CreateCompatibleBitmap( hdc, iWidth, iHeight );
            HDC	    newDC  = CreateCompatibleDC( hdc );

            // 関連づけ
            SelectObject( newDC, newBMP );

            // 画像を取得
            BitBlt( newDC, 0, 0, iWidth, iHeight, 
                    hdc, clipRect.left, clipRect.top, SRCCOPY );

            // ウィンドウを隠す!
            ShowWindow( hWnd, SW_HIDE );
			
            // テンポラリファイル名を決定
            TCHAR   tmpDir[MAX_PATH];
            TCHAR   tmpFile[MAX_PATH];
            GetTempPath( MAX_PATH, tmpDir );
            GetTempFileName( tmpDir, TEMPFILE_BASE, 0, tmpFile );

            CImage  image;
            if ( image.SavePngFile( tmpFile, newBMP ) ) {
#ifdef  _DEBUG
                ::MessageBox( NULL,
                              "キャプチャー結果をPNGファイルに保存しました  ",
                              "ファイル保存成功",
                              MB_OK|MB_ICONINFORMATION);
#endif  /* _DEBUG */

                // アップロード
                // 画像ファイルかどうかチェック
                struct stat s;
                if ( !stat( tmpFile, &s ) ) {
                    int             height = 0;
                    int             width  = 0;
                    CHIRRUP_FTYPE   ftype  = m_dlgForCapture->GetImageSize(
                                                    tmpFile, height, width );

                    if ( (height > 0) && (width > 0) ) {
                        m_paramUploadImage.dlg      = m_dlgForCapture;
                        m_paramUploadImage.filetype = ftype;
                        m_paramUploadImage.filename = tmpFile;
                        m_paramUploadImage.filesize = s.st_size;
                        m_paramUploadImage.url      = _T("");
                        m_paramUploadImage.caption  = _T("");

                        // アップロード処理を行なうスレッドを起動
                        m_dlgForCapture->UploadImage( &m_paramUploadImage );
                    }
                }
            }

            // 後始末
         // DeleteFile(tmpFile);
                // 注意: アップロード処理を別スレッドで行なっている(まだ、
                //       アップロード処理中である可能性がある)ため、このタ
                //       イミングでファイルを消すのは避ける

            DeleteDC(newDC);
            DeleteObject(newBMP);

            ReleaseDC(NULL, hdc);

            if ( m_dlgForCapture )
                m_dlgForCapture->OnEndCapture();
         // DestroyWindow(hWnd);
        }
        break;

    case WM_DESTROY:
        if ( m_dlgForCapture )
            m_dlgForCapture->OnEndCapture();
     // PostQuitMessage(0);
        break;

    default:
        return DefWindowProc( hWnd, message, wParam, lParam );
        break;
    }

    return 0;
}


LRESULT CALLBACK
WndProcForCapture( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    CChirrupApp     *ap = (CChirrupApp *)AfxGetApp();
    if ( ap && ap->m_capture )
        return ( ap->m_capture->WindowProc( hWnd, message, wParam, lParam ) );

    return 0;
}
