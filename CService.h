/*
 * CService.h   : Twitter クライアント chirrup
 *      各サービスの API を利用するための各種処理群 ヘッダファイル
 *          written by H.Tsujimura  4 Apr 2007 / 28 Apr 2007 / 19 Jun 2007
 *
 *      Copyright (c) 2007, 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/CService.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 26    09/03/31 23:29 Tsujimura543
 * Twitter の OAuth 対応準備 その7
 * 
 * 25    09/03/30 22:19 Tsujimura543
 * Twitter の OAuth 対応準備
 * 
 * 24    09/03/10 22:14 Tsujimura543
 * GetStringFromJSON() にバッファオーバーラン対策を実施
 * 
 * 23    09/03/03 1:30 Tsujimura543
 * 展開対象の短縮URLを増やしてみた
 * 
 * 22    08/02/07 22:36 Tsujimura543
 * copyright 表示を修正 (2008 を追加)
 * 
 * 21    08/01/11 19:53 Tsujimura543
 * ExpandPheedo() を追加
 * 
 * 20    07/12/26 21:32 Tsujimura543
 * リファクタリングを実施
 * 
 * 19    07/12/26 20:10 Tsujimura543
 * z.la で圧縮されている URL の展開処理を追加
 * 
 * 18    07/12/19 18:41 Tsujimura543
 * http関連の関数群を http.h に分離
 * 
 * 17    07/12/19 17:17 Tsujimura543
 * _http_postBASIC() の引数を追加
 * 
 * 16    07/12/19 16:56 Tsujimura543
 * _http_getBASIC() の引数を追加
 * 
 * 15    07/08/25 0:45 Tsujimura543
 * 「ついすた」に対応 (表示)
 * 
 * 14    07/07/23 14:55 Tsujimura543
 * TWITTER_STATUS 構造体に source と sourceURL を追加
 * 
 * 13    07/07/17 18:41 Tsujimura543
 * GetTinyURL() を追加
 * 
 * 12    07/07/05 0:46 Tsujimura543
 * (1) GetStatFromJSON(), GetUserTimeline() の引数を変更
 * (2) TWITTER_USER 構造体の変更(orig_userNameを追加)に伴う修正
 * 
 * 11    07/07/03 14:53 Tsujimura543
 * haru.fm 対応 (動作確認済み)
 * 
 * 10    07/06/25 21:09 Tsujimura543
 * twitterStatus のコピーコンストラクタを追加
 * 
 * 9     07/06/25 18:21 Tsujimura543
 * DeleteReserved(), DeleteReserved2() 関連、コードを整理
 * 
 * 8     07/06/25 17:40 Tsujimura543
 * DeleteReserved(), DeleteReserved2() を追加
 * 
 * 7     07/06/22 17:45 Tsujimura543
 * TWITTER_STATUS に reserved を追加
 * (いまのところ、Timelog のみで使用)
 * 
 * 6     07/06/21 19:15 Tsujimura543
 * SetUserAgent() を CService 内のメソッドに一本化した
 * 
 * 5     07/06/21 13:33 Tsujimura543
 * status ID 格納領域サイズをさらに増やす
 * 
 * 4     07/06/20 19:28 Tsujimura543
 * GetStatusID() を導入
 * 
 * 3     07/06/20 15:44 Tsujimura543
 * status ID の格納領域サイズを増やした [Timelog 対応のため]
 * (Timelog の ID は他サービスの ID より長い)
 * 
 * 2     07/06/19 22:50 Tsujimura543
 * さらに共通化可能な部分を CService に移した
 * 
 * 1     07/06/19 21:19 Tsujimura543
 * 今まで CTwitter 内でやっていた API の呼び出し、実行結果の解析処理のう
 * ち、 Twitter 以外のサービスと共通化できる部分を CService として独立さ
 * せた
 */

#ifndef __C_SERVICE_H__
#define __C_SERVICE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxwin.h>         // MFC のコアおよび標準コンポーネント
#include "resource.h"		// メイン シンボル
#include "ProceedingDialog.h"
#include "defaultImage.h"
extern "C" {
#include "xmlRPC.h"
#include "encryptRSA.h"
}

#define MAX_NUMOFSTATUS     128 /* 暫定値 */
#define MAX_NUMOFFRIENDS    20  /* ダイアログ最下段に表示する friends の数 */
#define ID_UPDATE_TWITTER   0xDEADBEAF
#define MS_UPDATE_TWITTER   (60 * 1000) // デフォルトの更新周期
#define MAX_NUM_OF_DIRECTMESSAGES   20

typedef struct twitterUser  {
    char    id[MAX_KEYLENGTH];
    char    name[MAX_KEYLENGTH];
    char    screenName[MAX_KEYLENGTH];
    char    location[MAX_LOGICALLINELEN];
    char    description[MAX_DESCRIPTION_LEN];
    char    profileImageURL[MAX_URLLENGTH];
    char    url[MAX_URLLENGTH];
    char    lastStatus[MAX_DESCRIPTION_LEN];
    HBITMAP bitmap;

    // for logging
    char    orig_userName[MAX_KEYLENGTH * 2];

    twitterUser()
    {
        id[0]              = NUL;
        name[0]            = NUL;
        screenName[0]      = NUL;
        location[0]        = NUL;
        description[0]     = NUL;
        profileImageURL[0] = NUL;
        url[0]             = NUL;
        lastStatus[0]      = NUL;
        bitmap             = NULL;
        orig_userName[0]   = NUL;
    }
}   TWITTER_USER;

typedef struct twitterStatus    {
    CTime   createdAt;
    char    id[MAX_KEYLENGTH * 2 + 2];
    char    text[MAX_DESCRIPTION_LEN];
    char    source[MAX_KEYLENGTH];     /* {@@} */
    char    sourceURL[MAX_URLLENGTH];  /* {@@} */

    TWITTER_USER    user;

    // for logging
    char    orig_text[MAX_DESCRIPTION_LEN * 2];

    // 各サービスの独自拡張対応用
    void    *reserved;
    void    *reserved2;

    twitterStatus()
    {
        createdAt    = CTime::GetCurrentTime();
        id[0]        = NUL;
        text[0]      = NUL;
        orig_text[0] = NUL;
        source[0]    = NUL;
        sourceURL[0] = NUL;

        memset( &user, 0x00, sizeof ( TWITTER_USER ) );
        reserved  = NULL;
        reserved2 = NULL;
    }

    twitterStatus operator= ( twitterStatus t )
    {
        createdAt = t.createdAt;
        strcpy( id, t.id );
        strcpy( text, t.text );
        strcpy( source, t.source );
        strcpy( sourceURL, t.sourceURL );

        user = t.user;

        strcpy( orig_text, t.orig_text );

        reserved  = t.reserved;
        reserved2 = t.reserved2;

        return ( *this );
    }
}   TWITTER_STATUS;

typedef struct twitterLogging   {
    time_t  createdAt;
    int     createdAt_yyyy;
    int     createdAt_mm;
    int     createdAt_dd;
    int     createdAt_HH;
    int     createdAt_MM;
    int     createdAt_SS;

    char    orig_text[MAX_DESCRIPTION_LEN * 2];
    char    orig_userName[MAX_KEYLENGTH * 2];
}   TWITTER_LOG;

typedef struct  twitterDirectMessage    {
    CTime   createdAt;
    char    id[MAX_KEYLENGTH * 2 + 2];
    char    text[MAX_DESCRIPTION_LEN];

    TWITTER_USER    sender;
    TWITTER_USER    recipient;

    bool    deleted;
}   TWITTER_DIRECT_MESSAGE;

class CTwitterTimeline;

class CService
{
public:
    CService();
    ~CService();

    typedef enum timelineType   {
        FRIENDS_TIMELINE = 1,
        PUBLIC_TIMELINE,
        USER_TIMELINE,
        REPLIES
    }   TIMELINE_TYPE;

    bool    m_useOAuth;
    CString m_username;     // ID または メールアドレス
    CString m_password;     // パスワード または API キー
    CString m_oauthToken;       // OAuth アクセストークン
    CString m_oauthTokenSecret; // OAuth 署名用秘密鍵
    CString m_screenName;   // スクリーン名 (または ユーザ名)
#ifdef  _DEBUG
    CString m_serviceName;
#endif
    CString m_serviceSymbol;

    // 後始末
    virtual void    DeleteReserved( TWITTER_STATUS *sp )  = 0;
    virtual void    DeleteReserved2( TWITTER_STATUS *sp ) = 0;

    // User-Agent を設定
    void    SetUserAgent();

    // 発言を投稿
    virtual bool    PostUpdate( CString          monologue,
                                ProceedingDialog *pdlg ) = 0;

    // friends_timeline を取得
    virtual CString GetFriendsTimeline(
                                CTwitterTimeline *timeline,
                                ProceedingDialog *pdlg ) = 0;
    CString GetFriendsTimeline( const char       *endPointURL,
                                CTwitterTimeline *timeline,
                                ProceedingDialog *pdlg );

    // public_timeline を取得
    virtual CString GetPublicTimeline(
                                CTwitterTimeline *timeline,
                                ProceedingDialog *pdlg ) = 0;
    CString GetPublicTimeline(  const char       *endPointURL,
                                CTwitterTimeline *timeline,
                                ProceedingDialog *pdlg );

    // user_timeline を取得
    virtual CString GetUserTimeline(
                                CTwitterTimeline *timeline,
                                ProceedingDialog *pdlg ) = 0;
    CString GetUserTimeline(    const char       *endPointURL,
                                CTwitterTimeline *timeline,
                                ProceedingDialog *pdlg );

    // 自分のスクリーン名の取得
    virtual CString GetScreenName() = 0;

    // for logging
    void            WriteLog( CTwitterTimeline *timeline );
    long            m_numOfLogs;
    TWITTER_LOG     *m_log;

    // for ついすた
    bool            m_useTwitStar;

protected:
    // timeline を取得
    virtual CString GetTimeline( CString          &messages,
                                 TWITTER_STATUS   **sp,
                                 long             &numOfStats,
                                 TIMELINE_TYPE    t,
                                 const char       *endPointURL,
                                 CTwitterTimeline *timeline,
                                 ProceedingDialog *pdlg )  = 0;
    virtual CString GetStatusID( const char *p,
                                 const char *terminator ) = 0;

    CString         GetStatFromJSON(
                            const char     *p,
                            TWITTER_STATUS **sp,
                            long           &numOfStats );
    virtual void    SetStatFromJSON(
                            const char     *p,
                            const char     *s,
                            TWITTER_STATUS *sp,
                            CString        &message ) = 0;
    virtual void    MakeMessageForScreen(
                            CString        &message,
                            TWITTER_STATUS *sp ) = 0;
    virtual void    MakeMessageForLogging(
                            TWITTER_STATUS *sp ) = 0;

    CString         EscapeQuote( const char *p );
    char            *ExpandTinyURL( char *str );
    char            *ExpandZla( char *str );
    char            *ExpandPheedo( char *str );
    char            *ExpandURL( char *str );
    char            *ExtractURL( char       *str,
                                 size_t     offset,
                                 const char *response,
                                 const char *delimiter ); 

    char            *GetTinyURL( const char *targetURL,
                                 char       *request,
                                 char       *response,
                                 size_t     sz );
    char            *GetTinyURL( char *str );

    char            *GetStringFromJSON( char       *result,
                                        size_t     result_len,
                                        const char *name,
                                        const char *p,
                                        const char *terminator,
                                        bool       raw = false,
                                        char       *origString = NULL );
    int             GetIntegerFromJSON( const char *name,
                                        const char *p,
                                        const char *terminator );
    CTime           GetCreatedAtFromJSON( const char *p,
                                          const char *terminator );
    char            *GetIdFromJSON( const char *p,
                                    const char *terminator );
    char            *GetTextFromJSON( const char *p,
                                      const char *terminator,
                                      char       *origString = NULL );
    TWITTER_USER    GetUserFromJSON( const char *p,
                                     const char *terminator );

    CTime           GetTimeFromXML( const char *p, const char *name );
    TWITTER_USER    GetUserFromXML( const char *p, const char *terminator );
    CString         GetStringFromXML( const char *p,
                                      const char *name,
                                      const char *terminator );
    CString         GetStringFromXML( const char *p,
                                      const char *name,
                                      const char *param,
                                      const char *terminator );

    // 最近の発言のリスト (最大 MAX_NUMOFSTATUS 件)
	CString	        m_messages;     // friends_timeline
    long            m_numOfStats;
    TWITTER_STATUS  *m_stat;

	CString	        m_messages2;    // public_timeline
    long            m_numOfStats2;
    TWITTER_STATUS  *m_stat2;

	CString	        m_messages3;    // user_timeline
    long            m_numOfStats3;
    TWITTER_STATUS  *m_stat3;
};

#endif  /* __C_SERVICE_H__ */
