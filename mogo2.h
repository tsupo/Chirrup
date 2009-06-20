/*
 * mogo2.h  : もごもご クライアント chirrup
 *      もごもご API を利用するための各種処理群 ヘッダファイル
 *          written by H.Tsujimura  14 Jun 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/mogo2.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 12    07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 11    07/07/05 0:50 Tsujimura543
 * (1) GetStatFromJSON(), GetUserTimeline() の引数を変更
 * (2) TWITTER_USER 構造体の変更(orig_userNameを追加)に伴う修正
 * (3) MakeMessageForScreen() と MakeMessageForLogging() を用意
 * 
 * 10    07/06/25 18:03 Tsujimura543
 * DeleteReserved(), DeleteReserved2() 関連、コードを整理
 * 
 * 9     07/06/25 17:40 Tsujimura543
 * DeleteReserved(), DeleteReserved2() を追加
 * 
 * 8     07/06/21 19:15 Tsujimura543
 * SetUserAgent() を CService 内のメソッドに一本化した
 * 
 * 7     07/06/20 19:28 Tsujimura543
 * GetStatusID() を導入
 * 
 * 6     07/06/19 23:01 Tsujimura543
 * CService を導入し、ソースコードを整理した
 * 
 * 5     07/06/19 17:39 Tsujimura543
 * GetMogo2ScreenName() → GetScreenName() に変更
 * 
 * 4     07/06/18 18:51 Tsujimura543
 * デフォルトアイコンの定義を defaultImage.h に移す
 * 
 * 3     07/06/15 23:53 Tsujimura543
 * MOGO2_DEFAULT_IMAGE の定義を変更
 * 
 * 2     07/06/15 19:15 Tsujimura543
 * friends_timeline 対策、追加
 * 
 * 1     07/06/14 23:00 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#ifndef __MOGO2_H__
#define __MOGO2_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CService.h"

class CMogo2 : public CService
{
public:
    CMogo2();
    ~CMogo2();

    void    DeleteReserved(TWITTER_STATUS *sp);
    void    DeleteReserved2(TWITTER_STATUS *sp);

    // 発言を投稿
    bool    PostUpdate( CString monologue, ProceedingDialog *pdlg );

    // friend_timeline を取得
    CString GetFriendsTimeline( CTwitterTimeline *timeline,
                                ProceedingDialog *pdlg );

    // public_timeline を取得
    CString GetPublicTimeline( CTwitterTimeline *timeline,
                               ProceedingDialog *pdlg );

    // user_timeline を取得
    CString GetUserTimeline( CTwitterTimeline *timeline,
                             ProceedingDialog *pdlg );

    // 自分のスクリーン名の取得
    CString GetScreenName();

protected:
    CString GetTimeline( CString          &messages,
                         TWITTER_STATUS   **stat,
                         long             &numOfStats,
                         TIMELINE_TYPE    t,
                         const char       *endPointURL,
                         CTwitterTimeline *timeline,
                         ProceedingDialog *pdlg );
    CString GetStatusID( const char *p,
                         const char *terminator );

    void            SetStatFromJSON(
                            const char     *p,
                            const char     *s,
                            TWITTER_STATUS *sp,
                            CString        &message );
    void            MakeMessageForScreen(
                            CString        &message,
                            TWITTER_STATUS *sp );
    void            MakeMessageForLogging(
                            TWITTER_STATUS *sp );

    TWITTER_USER    GetUserFromJSON( const char *p,
                                     const char *terminator );

private:
    CMogo2( CMogo2 &obj );
    CMogo2  operator = ( CMogo2 &obj );
};

#endif  /* __MOGO2_H__ */