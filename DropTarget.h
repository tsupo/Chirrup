/*
 * DropTarget.h  : Twitter クライアント chirrup
 *      非CView ウィンドウにドロップできるようにするための
 *      COleDropTarget の派生クラス ヘッダーファイル
 *          written by H.Tsujimura  10 Dec 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/DropTarget.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     07/12/10 22:40 Tsujimura543
 * 画像投稿関連処理のスレッド構成変更に伴う修正を実施
 * 
 * 2     07/12/10 20:29 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 1     07/12/10 20:12 Tsujimura543
 * 新規作成
 */

#if !defined(AFX_DROPTARGET_H__43C46684_644A_4A51_B317_33C70EBB6EB5__INCLUDED_)
#define AFX_DROPTARGET_H__43C46684_644A_4A51_B317_33C70EBB6EB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CChirrupDropTarget: public COleDropTarget
{
public:
    CChirrupDropTarget():COleDropTarget()
    {
        m_chirrupDlg = NULL;
    }

    ~CChirrupDropTarget()
    {
    }

    DROPEFFECT  OnDragEnter(
                    CWnd*           pWnd,
                    COleDataObject* pDataObject,
                    DWORD           dwKeyState,
                    CPoint          point );

    DROPEFFECT  OnDragOver(
                    CWnd*           pWnd,
                    COleDataObject* pDataObject,
                    DWORD           dwKeyState,
                    CPoint          point );

    BOOL        OnDrop(
                    CWnd*           pWnd,
                    COleDataObject* pDataObject,
                    DROPEFFECT      dropEffect,
                    CPoint          point );

    DROPEFFECT  OnDropEx(
                    CWnd*           pWnd,
                    COleDataObject* pDataObject,
                    DROPEFFECT      dropDefault,
                    DROPEFFECT      dropList,
                    CPoint          point );

    void        OnDragLeave(
                    CWnd* pWnd );

    DROPEFFECT  OnDragScroll(
                    CWnd*  pWnd,
                    DWORD  dwKeyState,
                    CPoint point );

    BOOL        Register( CWnd* pWnd, CChirrupDlg* dlg );
    CChirrupDlg         *m_chirrupDlg;
    PARAM_UPLOADIMAGE   m_paramUploadImage; // for Thread of 'upload image'

private:
    CChirrupDropTarget( CChirrupDropTarget &obj );
    CChirrupDropTarget  operator = ( CChirrupDropTarget &obj );
};

#endif // !defined(AFX_DROPTARGET_H__43C46684_644A_4A51_B317_33C70EBB6EB5__INCLUDED_)
