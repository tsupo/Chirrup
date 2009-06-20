/*
 * capture.h  : Twitter クライアント chirrup
 *      画面キャプチャー関連 ヘッダ ファイル
 *          written by H.Tsujimura  14 Dec 2007 / 17 Dec 2007
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
 *      たぶん、Windows 98 でも動くと思います。Windows 95 の場合は OSR2
 *      以降(もしくは IE5.x が載っている環境)でないと動かないかもしれま
 *      せん。Windows NT の場合は SP6 なら動くと思いますが、それ以前だと
 *      動かないかもしれません(SP4 以降なら大丈夫?)。
 *
 * $Log: /comm/chirrup/capture.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 1     07/12/17 19:50 Tsujimura543
 * 新規作成 (capture関連の変数、関数をクラスとしてまとめてみた)
 */

#if !defined(__CAPTURE_H__A07B8677_638F_45CA_8C84_9324D00DA47B__INCLUDED_)
#define __CAPTURE_H__A07B8677_638F_45CA_8C84_9324D00DA47B__INCLUDED_

class CCapture
{
public:
    CCapture();

    BOOL
    InitInstance( CChirrupDlg *dlg, HWND &hWndForCapture );

    LRESULT CALLBACK
    WindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

private:
    CChirrupDlg         *m_dlgForCapture;
    HINSTANCE           m_hInstForCapture;
    TCHAR               *m_szWindowClass;
    int                 m_ofX;
    int                 m_ofY;
    PARAM_UPLOADIMAGE   m_paramUploadImage; 

    VOID
    DrawRubberband(HDC hdc, LPRECT newRect, BOOL erase);

    CCapture( CCapture &obj );
    CCapture    operator = ( CCapture &obj );
};

#endif  /* __CAPTURE_H__A07B8677_638F_45CA_8C84_9324D00DA47B__INCLUDED_ */
