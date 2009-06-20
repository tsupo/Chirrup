/*
 * jaiku.h   : Jaiku クライアント chirrup
 *      Jaiku API を利用するための各種処理群 ヘッダファイル
 *          written by H.Tsujimura  28 May 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/jaiku.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 23    09/04/16 3:40 Tsujimura543
 * Jaiku の「発言ID」、「コメントID」の仕様変更に伴う修正を実施
 * 
 * 22    09/04/16 1:40 Tsujimura543
 * Jaiku の OAuth 対応 (つづき)
 * 
 * 21    09/04/15 1:17 Tsujimura543
 * Jaiuku の OAuth 対応準備
 * 
 * 20    07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 19    07/07/05 1:25 Tsujimura543
 * (1) GetUserTimeline() の引数を変更
 * (2) MakeMessageForScreen() と MakeMessageForLogging() を実際に
 *     使うようにした
 * 
 * 18    07/07/05 0:50 Tsujimura543
 * (1) GetStatFromJSON(), GetUserTimeline() の引数を変更
 * (2) TWITTER_USER 構造体の変更(orig_userNameを追加)に伴う修正
 * (3) MakeMessageForScreen() と MakeMessageForLogging() を用意
 * 
 * 17    07/06/25 18:03 Tsujimura543
 * DeleteReserved(), DeleteReserved2() 関連、コードを整理
 * 
 * 16    07/06/25 17:40 Tsujimura543
 * DeleteReserved(), DeleteReserved2() を追加
 * 
 * 15    07/06/21 19:15 Tsujimura543
 * SetUserAgent() を CService 内のメソッドに一本化した
 * 
 * 14    07/06/21 13:33 Tsujimura543
 * status ID 格納領域サイズをさらに増やす
 * 
 * 13    07/06/21 1:07 Tsujimura543
 * status ID 格納領域サイズを増やした
 * 
 * 12    07/06/20 19:28 Tsujimura543
 * GetStatusID() を導入
 * 
 * 11    07/06/20 2:14 Tsujimura543
 * CJaiku を CTwitter の派生クラスから CService の派生クラスに変更
 * (するために純粋仮想関数に対応するダミーの関数を追加)
 * 
 * 10    07/06/19 23:05 Tsujimura543
 * CService 導入に伴う修正を実施
 * 
 * 9     07/06/18 18:51 Tsujimura543
 * デフォルトアイコンの定義を defaultImage.h に移す
 * 
 * 8     07/06/15 23:36 Tsujimura543
 * GetIdFromJSON() を追加
 * 
 * 7     07/06/07 19:56 Tsujimura543
 * リファクタリング
 * 
 * 6     07/06/06 23:11 Tsujimura543
 * ログをファイルに書き出す機能を実装
 * 
 * 5     07/05/29 12:48 Tsujimura543
 * Jaiku の friends_timeline 対応(途中)
 * 
 * 4     07/05/29 6:50 Tsujimura543
 * C1001 エラー対策
 * 
 * 3     07/05/29 5:13 Tsujimura543
 * Jaiku の user_timeline の閲覧に対応
 * 
 * 2     07/05/29 4:34 Tsujimura543
 * Jaiku の public_timeline の閲覧機能、完成 (動作確認済み)
 * 
 * 1     07/05/29 1:47 Tsujimura543
 * 最初の版 (実験版)
 */

#ifndef __JAIKU_H__
#define __JAIKU_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CService.h"

typedef struct jaikuUser    {
    char    nick[MAX_KEYLENGTH];
    char    firstName[MAX_NAMELEN];
    char    lastName[MAX_NAMELEN];
    char    avatar[MAX_URLLENGTH];
    char    url[MAX_URLLENGTH];
    HBITMAP bitmap;
}   JAIKU_USER;

typedef struct jaikuPresence    {
    CTime       createdAt;
    char        createdAtRelative[MAX_DATELENGTH];
    char        id[MAX_KEYLENGTH * 2 + 2];
    char        title[MAX_DESCRIPTION_LEN];     // 投稿内容本文
    char        content[MAX_DESCRIPTION_LEN];   // 投稿場所 (default は location と同じ値)
    char        icon[MAX_URLLENGTH];
    char        url[MAX_URLLENGTH];
    long        comments;                       // 付けられたコメント数
    char        location[MAX_DESCRIPTION_LEN];  // 居住地

    JAIKU_USER  user;

    // for logging
    char        orig_text[MAX_DESCRIPTION_LEN];
}   JAIKU_STATUS;


class CJaiku : public CService
{
public:
    CJaiku();
    ~CJaiku();

    void    DeleteReserved(TWITTER_STATUS *sp);
    void    DeleteReserved2(TWITTER_STATUS *sp);

    CString m_apiKey;   // Jaiku personal_key

    // 発言を投稿
    bool    PostUpdate( CString monologue, ProceedingDialog *pdlg )
    {
        return ( PostPresence( monologue, pdlg ) );
    }
    bool    PostPresence( CString monologue, ProceedingDialog *pdlg );

    // friend_timeline (Overview相当) を取得
    CString GetFriendsTimeline( CTwitterTimeline *timeline,
                                ProceedingDialog *pdlg );

    // public_timeline を取得
    CString GetPublicTimeline( CTwitterTimeline *timeline,
                               ProceedingDialog *pdlg );

    // user_timeline を取得
    CString GetUserTimeline( CTwitterTimeline *timeline,
                             ProceedingDialog *pdlg );

    // 指定ユーザの最新の発言を取得
    JAIKU_USER      ShowUser( const char *userID );

    // 自分のスクリーン名の取得
    CString         GetScreenName();

    // OAuth アクセストークンの取得
    bool    GetAccessToken( const char *consumerKey,
                            const char *consumerSecret,
                            CString    &oauthToken,
                            CString    &oauthTokenSecret );

private:
    void    Jaiku2Twitter( TWITTER_STATUS &ts, JAIKU_STATUS js );
    void    Jaiku2Twitter( TWITTER_USER &tu, JAIKU_USER ju );

    void    Twitter2Jaiku( JAIKU_STATUS *js, TWITTER_STATUS *ts,
                           long numOfStats );
    void    Twitter2Jaiku( JAIKU_USER *ju, TWITTER_USER *tu );

    JAIKU_USER      GetUserFromJSON( const char *p,
                                     const char *terminator );
    char            *GetTitleFromJSON( const char *q,
                                       const char *terminator,
                                       char       *origString /* = NULL */ );
#ifdef  JAIKU_LEGACY_TIMELINE
    int             GetIdFromJSON( const char *q,
                                   const char *terminator,
                                    int        &presence );
#else
    char            *GetIdFromJSON( const char *q,
                                    const char *terminator,
                                    char       *presence );
#endif

    CString         GetJaikuPresenceFromJSON(
                            const char    *p,
                            TIMELINE_TYPE t = FRIENDS_TIMELINE
                        );

    void            SetJaikuPresenceFromJSON(
                            const char   *q,
                            const char   *s,
                            JAIKU_STATUS *sp,
                            CString      &message );
    void            MakeMessageForScreen(
                            CString        &message,
                            TWITTER_STATUS *sp );
    void            MakeMessageForLogging(
                            TWITTER_STATUS *sp );

    CString         GetTimeline(
                            CString          &messages,
                            JAIKU_STATUS     **stat,
                            long             &numOfStats,
                            TIMELINE_TYPE    timelineType,
                            const char       *endPointURL,
                            CTwitterTimeline *timeline,
                            ProceedingDialog *pdlg );

protected:
    JAIKU_STATUS    *m_stat;    // friends_timeline
    JAIKU_STATUS    *m_stat2;   // public_timeline
    JAIKU_STATUS    *m_stat3;   // user_timeline

    CString GetTimeline( CString          &messages,
                         TWITTER_STATUS   **stat,
                         long             &numOfStats,
                         TIMELINE_TYPE    t,
                         const char       *endPointURL,
                         CTwitterTimeline *timeline,
                         ProceedingDialog *pdlg );
    CString GetStatusID( const char *p,
                         const char *terminator );
    void    SetStatFromJSON( const char     *p,
                             const char     *s,
                             TWITTER_STATUS *sp,
                             CString        &message );
    char    *CutWhiteSpaces( char *p );

private:
    // OAuth リクエストトークンの取得
    bool    GetRequestToken( const char *consumerKey,
                             const char *consumerSecret,
                             CString    &oauthToken,
                             CString    &oauthTokenSecret );

    bool    GetToken( const char *response,
                      CString    &oauthToken,
                      CString    &oauthTokenSecret );

    void    MakeOAuthBase( const char *url,
                           const char *method,
                           char       *key,
                           char       *base,
                           char       *param );
    void    MakeOAuthRequest( const char *url,
                              const char *method,
                              char       *request,
                              char       *key,
                              char       *base,
                              char       *param );

    bool    CheckOAuthResult( const char *response );

private:
    CJaiku( CJaiku &obj );
    CJaiku  operator = ( CJaiku &obj );
};


#endif  /* __TWITTER_H__ */