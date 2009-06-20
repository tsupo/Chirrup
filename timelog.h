/*
 * timelog.h : Timelog クライアント chirrup
 *      Timelog API を利用するための各種処理群 ヘッダファイル
 *          written by H.Tsujimura  20 Jun 2007
 *
 *      Copyright (c) 2007, 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/timelog.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 14    08/07/16 15:27 Tsujimura543
 * Timelog の「評価」に対応した
 * 
 * 13    08/02/08 23:15 Tsujimura543
 * コピーライト表示を更新
 * 
 * 12    08/02/08 23:14 Tsujimura543
 * tag の最大文字列長を修正 (長いtag出現時に領域破壊が発生、落ちていた)
 * 
 * 11    07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 10    07/07/19 21:23 Tsujimura543
 * タグが長いと落ちてしまう不具合に対処するため、タグ格納用の
 * 領域を増やしてみた
 * 
 * 9     07/07/05 0:50 Tsujimura543
 * (1) GetStatFromJSON(), GetUserTimeline() の引数を変更
 * (2) TWITTER_USER 構造体の変更(orig_userNameを追加)に伴う修正
 * (3) MakeMessageForScreen() と MakeMessageForLogging() を用意
 * 
 * 8     07/06/25 18:47 Tsujimura543
 * tag を表示するようにしてみた
 * 
 * 7     07/06/25 18:09 Tsujimura543
 * DeleteReserved(), DeleteReserved2() を追加
 * 
 * 6     07/06/22 18:00 Tsujimura543
 * 「発言」本文末尾に「> コメント先ユーザ名」を付加するようにした
 * 
 * 5     07/06/21 22:05 Tsujimura543
 * ダイレクトメッセージの送受信処理を実装 (削除は未実装)
 * 
 * 4     07/06/21 19:15 Tsujimura543
 * SetUserAgent() を CService 内のメソッドに一本化した
 * 
 * 3     07/06/20 19:28 Tsujimura543
 * GetStatusID() を導入
 * 
 * 2     07/06/20 17:05 Tsujimura543
 * timeline の取得と status の投稿に関して、動作することを確認
 * 
 * 1     07/06/20 14:06 Tsujimura543
 * 新規作成 (暫定版)
 */

#ifndef __TIMELOG_H__
#define __TIMELOG_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CService.h"

// タグ
typedef struct timelogTags   {
    char    tag[MAX_LOGICALLINELEN * 2 + 1];
    char    orig_tag[MAX_LOGICALLINELEN * 4 + 2];

    timelogTags()
    {
        tag[0]      = NUL;
        orig_tag[0] = NUL;
    }
}   TIMELOG_TAGS;


class CTimelog : public CService
{
public:
    CTimelog();
    ~CTimelog();

    void    DeleteReserved(TWITTER_STATUS *sp);
    void    DeleteReserved2(TWITTER_STATUS *sp);

    // ダイレクトメッセージ (最新の MAX_NUM_OF_DIRECTMESSAGES 件)
    TWITTER_DIRECT_MESSAGE  *m_dm;
    int                     m_numOfMessages;

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

    // ダイレクトメッセージを受信
    TWITTER_DIRECT_MESSAGE  *RecvDirectMessages( int &numOfMessages,
                                                 ProceedingDialog *pdlg );

    // ダイレクトメッセージを送信
    bool    SendDirectMessage( CString userID, CString message );

    // ダイレクトメッセージを削除
    bool    DeleteDirectMessage( const char *messageID );

    // 指定 status を favorites にする (「評価」をつける)
    bool    SetFavorite( const char *statusID );

    // 自分のスクリーン名の取得
    CString GetScreenName();

    CString GetIdFromJSON( const char *p,
                           const char *terminator );

protected:
    // timeline を取得
    CString GetTimeline(
                    CString          &messages,
                    TWITTER_STATUS   **stat,
                    long             &numOfStats,
                    TIMELINE_TYPE    t,
                    const char       *endPointURL,
                    CTwitterTimeline *timeline,
                    ProceedingDialog *pdlg );
    CString GetStatusID( const char *p, const char *terminator );

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

    CTime           GetCreatedAtFromJSON(
                                      const char *p,
                                      const char *terminator );
    TWITTER_USER    GetUserFromJSON(  const char *p,
                                      const char *terminator );
    TWITTER_USER    *GetRecipientUserFromJSON(
                                      const char *p,
                                      const char *terminator );
    TIMELOG_TAGS    *GetTagsFromJSON( const char *p,
                                      const char *terminator );

    char            *GetUserLoginIdFromJSON(
                                      const char *p,
                                      const char *terminator );

    char            *GetTextFromJSON( const char *p,
                                      const char *terminator,
                                      char       *origString /* = NULL */ );

private:
    CTimelog( CTimelog &obj );
    CTimelog    operator = ( CTimelog &obj );
};

#endif  /* __TIMELOG_H__ */