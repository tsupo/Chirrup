/*
 * paramForThread.h  : Twitter クライアント chirrup
 *      スレッド間通信用構造体 定義ファイル
 *          written by H.Tsujimura  5 Jun 2007 / 10 Dec 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/paramForThread.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     07/12/13 22:26 Tsujimura543
 * 画像のアップロード処理周りを変更(はてなFotolife対応準備、bmpファイル対
 * 応)
 * 
 * 1     07/12/10 22:38 Tsujimura543
 * chirrupDlg.h から分離、独立させた
 */

#if !defined(__PARAM_FOR_THREAD_H__43C46684_644A_4A51_B317_33C70EBB6EB5__INCLUDED_)
#define __PARAM_FOR_THREAD_H__43C46684_644A_4A51_B317_33C70EBB6EB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct paramForUpdateThread {
    CChirrupDlg *dlg;
    CManager    *manager;
    CString     timelineType;
}   PARAM_UPDATE;

typedef struct paramForPostThread   {
    CChirrupDlg *dlg;
    CString     timelineType;
    CString     monologue;
    bool        ret;
}   PARAM_POST;

typedef struct paramForLoadImage    {
    CChirrupDlg         *dlg;
    CTwitterTimeline    *tp;
    CString             cacheDir;
}   PARAM_LOADIMAGE;



typedef enum {
    FTYPE_UNKNOWN = -1,
    FTYPE_JPG     = 1,
    FTYPE_GIF,
    FTYPE_PNG,
    FTYPE_BMP          } CHIRRUP_FTYPE;

typedef struct paramForUploadImage  {
    CChirrupDlg     *dlg;
    CHIRRUP_FTYPE   filetype;
    CString         filename;
    size_t          filesize;
    CString         url;
    CString         caption;
}   PARAM_UPLOADIMAGE;

#endif // !defined(__PARAM_FOR_THREAD_H__43C46684_644A_4A51_B317_33C70EBB6EB5__INCLUDED_)
