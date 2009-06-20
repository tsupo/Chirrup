/*
 * twitter.h   : Twitter クライアント chirrup
 *      Twitter API を利用するための各種処理群 ヘッダファイル
 *          written by H.Tsujimura  4 Apr 2007 / 28 Apr 2007
 *
 *      Copyright (c) 2007, 2008, 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/twitter.h $
 * 
 * 2     09/06/18 1:33 tsupo
 * 2.01版
 * 
 * 36    09/06/16 0:51 Tsujimura543
 * アクセストークン取得時に返ってくるスクリーン名を利用するようにした
 * 
 * 35    09/06/16 0:01 Tsujimura543
 * Twitter の status ID が singed long で扱える範囲を超えてしまった
 * (2009年6月13日)ための対策として、CService::GetIdFromJSON() を呼ぶ
 * のをやめて、新たに CTwitter::GetIdFromJSON() を用意した
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 34    09/04/09 16:03 Tsujimura543
 * API で取得した発言の trancated が true のときは、当該発言のパーマリンク
 * を GET して、完全な状態の発言を取得するようにした
 * 
 * 33    09/04/07 15:46 Tsujimura543
 * OAuth で "Invalid OAuth Request" が発生したときの処理を追加
 * 
 * 32    09/04/01 3:16 Tsujimura543
 * Twitter の OAuth 対応、完了
 * 
 * 31    09/03/30 23:45 Tsujimura543
 * Twitter の OAuth 対応準備 その3
 * 
 * 30    08/07/14 16:54 Tsujimura543
 * Twitter の「API制限情報取得API」を呼ぶ回数、タイミングを調整し直した
 * 
 * 29    08/06/30 20:10 Tsujimura543
 * long GetRateLimitStatus() を追加
 * 
 * 28    08/06/30 18:49 Tsujimura543
 * GetRateLimitStatus() を追加
 * 
 * 27    08/04/15 21:10 Tsujimura543
 * CutInReplyTo() を追加、in_reply_to: の入れ子構造に対応
 * 
 * 26    07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 25    07/08/17 17:21 Tsujimura543
 * SetFavorite() を追加
 * 
 * 24    07/07/23 14:54 Tsujimura543
 * GetSource() を追加
 * 
 * 23    07/07/05 0:50 Tsujimura543
 * (1) GetStatFromJSON(), GetUserTimeline() の引数を変更
 * (2) TWITTER_USER 構造体の変更(orig_userNameを追加)に伴う修正
 * (3) MakeMessageForScreen() と MakeMessageForLogging() を用意
 * 
 * 22    07/06/25 18:03 Tsujimura543
 * DeleteReserved(), DeleteReserved2() 関連、コードを整理
 * 
 * 21    07/06/25 17:40 Tsujimura543
 * DeleteReserved(), DeleteReserved2() を追加
 * 
 * 20    07/06/21 19:15 Tsujimura543
 * SetUserAgent() を CService 内のメソッドに一本化した
 * 
 * 19    07/06/20 19:28 Tsujimura543
 * GetStatusID() を導入
 * 
 * 18    07/06/19 23:09 Tsujimura543
 * CService を導入し、ソースを整理した
 * 
 * 17    07/06/19 17:38 Tsujimura543
 * GetTwitterScreenName() → GetScreenName() に変更
 * 
 * 16    07/06/18 22:35 Tsujimura543
 * ユーザ名の最大許容長を32バイトから64バイトへ変更
 * 
 * 15    07/06/18 18:51 Tsujimura543
 * デフォルトアイコンの定義を defaultImage.h に移す
 * 
 * 14    07/06/14 18:25 Tsujimura543
 * _http_getBASIC() と _http_postBASIC() のプロトタイプ宣言を
 * twitter.h に移動
 * 
 * 13    07/06/14 17:56 Tsujimura543
 * Wassr に対応
 * 
 * 12    07/06/13 15:55 Tsujimura543
 * 「ダイレクトメッセージの削除」に対応
 * 
 * 11    07/06/13 0:12 Tsujimura543
 * (1) TIMELINE_INFO 関連 fix
 * (2) 初期設定ファイル読み書きを新しいログファイル管理仕様に対応させた
 * 
 * 10    07/06/11 18:39 Tsujimura543
 * Twitter の user_timeline の閲覧をサポート
 * 
 * 9     07/06/07 19:23 Tsujimura543
 * リファクタリング
 * 
 * 8     07/06/06 21:24 Tsujimura543
 * ログをファイルに書き出す機能を実装
 * 
 * 7     07/06/04 21:11 Tsujimura543
 * friend の add と remove を実装 (for Twitter)
 * 
 * 6     07/06/04 14:51 Tsujimura543
 * _http_get() と _http_post() のプロトタイプ宣言を twitter.h に移動
 * 
 * 5     07/05/29 3:56 Tsujimura543
 * Jaiku (の public_timeline の閲覧) に対応
 * 
 * 4     07/05/26 0:22 Tsujimura543
 * Twitter と通信する部分を別スレッド化してみた
 * 
 * 3     07/05/23 22:24 Tsujimura543
 * public_timeline の取得に対応
 * 
 * 2     07/04/27 20:53 Tsujimura543
 * GetTwitterScreenName() を追加
 * 
 * 1     07/04/27 19:36 Tsujimura543
 * 新規作成 (今まで複数のソースに分散していた Twitter API 関連処理を集大成
 * したものとして、CTwitter クラスを用意した)
 */

#ifndef __TWITTER_H__
#define __TWITTER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxwin.h>         // MFC のコアおよび標準コンポーネント
#include "resource.h"		// メイン シンボル
#include "ProceedingDialog.h"
#include "defaultImage.h"
#include "CService.h"

class CTwitter : public CService
{
public:
    CTwitter();
    ~CTwitter();

    void    DeleteReserved(TWITTER_STATUS *sp);
    void    DeleteReserved2(TWITTER_STATUS *sp);

    // ダイレクトメッセージ (最新の MAX_NUM_OF_DIRECTMESSAGES 件)
    TWITTER_DIRECT_MESSAGE  *m_dm;
    int                     m_numOfMessages;

    // 発言を投稿
    bool    PostUpdate( CString monologue, ProceedingDialog *pdlg );

    // friends_timeline を取得
    CString GetFriendsTimeline( CTwitterTimeline *timeline,
                                ProceedingDialog *pdlg );

    // public_timeline を取得
    CString GetPublicTimeline( CTwitterTimeline *timeline,
                               ProceedingDialog *pdlg );

    // user_timeline を取得
    CString GetUserTimeline( CTwitterTimeline *timeline,
                             ProceedingDialog *pdlg );

    // replies を取得
    CString GetReplies( CTwitterTimeline *timeline,
                        ProceedingDialog *pdlg );

    // ダイレクトメッセージを受信
    TWITTER_DIRECT_MESSAGE  *RecvDirectMessages( int &numOfMessages,
                                                 ProceedingDialog *pdlg );

    // ダイレクトメッセージを送信
    bool    SendDirectMessage( CString screenName, CString message );

    // ダイレクトメッセージを削除
    bool    DeleteDirectMessage( const char *messageID );

    // 指定ユーザの最新の発言を取得
    TWITTER_USER    ShowUser( const char *userID );

    // 指定ユーザを friend にする
    bool    AddFriend( const char *userID );

    // 指定ユーザを friend から外す
    bool    RemoveFriend( const char *userID );

    // 指定 status を favorites にする
    bool    SetFavorite( const char *statusID );

    // 自分のスクリーン名の取得
    CString GetScreenName();

    // API制限状況の取得
    CString GetRateLimitStatus();
    long    GetRateLimitStatus( long &rate, long &remain );

    // OAuth アクセストークンの取得
    bool    GetAccessToken( const char *consumerKey,
                            const char *consumerSecret,
                            CString    &oauthToken,
                            CString    &oauthTokenSecret,
                            CString    &screenName );

protected:
    CString GetTimeline(
                    CString          &messages,
                    TWITTER_STATUS   **stat,
                    long             &numOfStats,
                    TIMELINE_TYPE    t,
                    const char       *endPointURL,
                    CTwitterTimeline *timeline,
                    ProceedingDialog *pdlg );
    CString GetIdFromJSON(
                    const char *p,
                    const char *terminator );
    CString GetStatusID(
                    const char *p,
                    const char *terminator );
    char    *GetSource( const char *q,
                        const char *s,
                        char       *sourceURL );
    bool    GetTruncated( const char *q,
                          const char *s );

    void    SetStatFromJSON(
                    const char     *q,
                    const char     *s,
                    TWITTER_STATUS *sp,
                    CString        &message );
    void    MakeMessageForScreen(
                    CString        &message,
                    TWITTER_STATUS *sp );
    void    MakeMessageForLogging(
                    TWITTER_STATUS *sp );

    char    *CutInReplyTo( char *s );

private:
    bool    loginTwitter( const char *username,
                          const char *password,
                          char       *cookie,
                          char       *screenName );

    // OAuth リクエストトークンの取得
    bool    GetRequestToken( const char *consumerKey,
                             const char *consumerSecret,
                             CString    &oauthToken,
                             CString    &oauthTokenSecret );

    bool    GetToken( const char *response,
                      CString    &oauthToken,
                      CString    &oauthTokenSecret );
    bool    GetToken( const char *response,
                      CString    &oauthToken,
                      CString    &oauthTokenSecret,
                      CString    &screenName );

    void    MakeOAuthBase( const char *url,
                           const char *method,
                           char       *key,
                           char       *base,
                           char       *param );
    void    MakeOAuthRequest( const char *url,
                              char       *request,
                              char       *key,
                              char       *base,
                              char       *param );

    bool    CheckOAuthResult( const char *response );

    CString	        m_messages4;    // replies
    long            m_numOfStats4;
    TWITTER_STATUS  *m_stat4;
    long            m_max_remain;
    long            m_remain;
#define TWITTER_MAX_REMAIN  70

private:
    CTwitter( CTwitter &obj );
    CTwitter    operator = ( CTwitter &obj );
};


#endif  /* __TWITTER_H__ */