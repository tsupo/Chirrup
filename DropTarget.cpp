/*
 * DropTarget.cpp : Twitter クライアント chirrup
 *      非CView ウィンドウにドロップできるようにするための
 *      COleDropTarget の派生クラス インプリメンテーション ファイル
 *          written by H.Tsujimura  10 Dec 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/DropTarget.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     07/12/13 22:26 Tsujimura543
 * 画像のアップロード処理周りを変更(はてなFotolife対応準備、bmpファイル対
 * 応)
 * 
 * 2     07/12/10 22:40 Tsujimura543
 * 画像投稿関連処理のスレッド構成変更に伴う修正を実施
 * 
 * 1     07/12/10 20:24 Tsujimura543
 * 最初の版 (tumblr へ投稿する処理は未実装)
 */

#include "chirrup.h"
#include "chirrupDlg.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/DropTarget.cpp 1     09/05/14 3:50 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChirrupDropTarget

DROPEFFECT
CChirrupDropTarget::OnDragEnter(
                            CWnd*           pWnd,
                            COleDataObject* pDataObject,
                            DWORD           dwKeyState,
                            CPoint          point
                        )
{
    if ( pDataObject->IsDataAvailable(CF_TEXT)  ||
         pDataObject->IsDataAvailable(CF_HDROP)    ) {
        return (dwKeyState & MK_CONTROL) ? DROPEFFECT_COPY : DROPEFFECT_MOVE;
    }

    return ( COleDropTarget::OnDragEnter( pWnd,
                                          pDataObject,
                                          dwKeyState,
                                          point ) );
}

void
CChirrupDropTarget::OnDragLeave( CWnd* pWnd )
{
    COleDropTarget::OnDragLeave( pWnd );
}

DROPEFFECT
CChirrupDropTarget::OnDragOver(
                            CWnd*           pWnd,
                            COleDataObject* pDataObject,
                            DWORD           dwKeyState,
                            CPoint          point
                        )
{
    if ( pDataObject->IsDataAvailable(CF_TEXT)  ||
         pDataObject->IsDataAvailable(CF_HDROP)    ) {
        return (dwKeyState & MK_CONTROL) ? DROPEFFECT_COPY : DROPEFFECT_MOVE;
    }

    return ( COleDropTarget::OnDragOver( pWnd, pDataObject, dwKeyState, point ) );
}

BOOL
CChirrupDropTarget::OnDrop(
                            CWnd*           pWnd,
                            COleDataObject* pDataObject,
                            DROPEFFECT      dropEffect,
                            CPoint          point
                        )
{
    if ( pDataObject->IsDataAvailable(CF_TEXT) ) {
        // ドロップされたデータを取得
        HGLOBAL     hData = pDataObject->GetGlobalData(CF_TEXT);
        ASSERT(hData);
        const char  *ptr  = (const char *)GlobalLock(hData);
        char        url[MAX_URLLENGTH + 1];

        // URL を取り出す
        memset( url, 0x00, MAX_URLLENGTH + 1 );
        strncpy( url, ptr, MAX_URLLENGTH );
        GlobalUnlock(hData);
        GlobalFree(hData);

        // (当該URLが画像なら)tumblr に投稿する
        if ( m_chirrupDlg )
            m_chirrupDlg->PostImage( url );

        return TRUE;
    }

    return ( COleDropTarget::OnDrop( pWnd, pDataObject, dropEffect, point ) );
}

DROPEFFECT
CChirrupDropTarget::OnDropEx(
                            CWnd*           pWnd,
                            COleDataObject* pDataObject,
                            DROPEFFECT      dropDefault,
                            DROPEFFECT      dropList,
                            CPoint          point
                        )
{
    return ( COleDropTarget::OnDropEx( pWnd,
                                       pDataObject,
                                       dropDefault,
                                       dropList,
                                       point ) );
}

DROPEFFECT
CChirrupDropTarget::OnDragScroll(
                            CWnd*  pWnd,
                            DWORD  dwKeyState,
                            CPoint point
                        )
{
    return ( COleDropTarget::OnDragScroll( pWnd, dwKeyState, point ) );
}

BOOL
CChirrupDropTarget::Register( CWnd* pWnd, CChirrupDlg* dlg )
{
    m_chirrupDlg = dlg;
    return ( COleDropTarget::Register(pWnd) );
}
