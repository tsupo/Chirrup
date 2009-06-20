/*
 * hatenaHaiku.h  : はてなハイク クライアント chirrup
 *      はてなハイク API を利用するための各種処理群 ヘッダファイル
 *          written by H.Tsujimura  22 Aug 2008
 *
 *      Copyright (c) 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/hatenaHaiku.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     08/09/02 18:38 Tsujimura543
 * 今回の修正に伴うタイムライン表示関連の動作確認、終わり
 * 
 * 3     08/09/02 18:28 Tsujimura543
 * 取得結果(JSON)が whitespace を使って整形されたものに変更された
 * 関係でタイムライン抽出がうまく動かなくなってしまったため、
 * CutWhiteSpaces() を追加することで対処した
 * 
 * 2     08/08/22 19:55 Tsujimura543
 * 動作確認終了
 * 
 * 1     08/08/22 18:42 Tsujimura543
 * 新規作成
 */

#ifndef __HATENA_HAIKU_H__
#define __HATENA_HAIKU_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CService.h"

class CHatenaHaiku : public CService
{
public:
    CHatenaHaiku();
    ~CHatenaHaiku();

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
    CString GetIdFromJSON( const char *p,
                           const char *terminator );

    char    *GetSource( const char *q, const char *s, char *sourceURL );
    char    *CutWhiteSpaces( char *p );

private:
    CHatenaHaiku( CHatenaHaiku &obj );
    CHatenaHaiku  operator = ( CHatenaHaiku &obj );
};

#endif  /* __HATENA_HAIKU_H__ */