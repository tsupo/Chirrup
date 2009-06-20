/*
 * wassr.h   : Wassr クライアント chirrup
 *      Wassr API を利用するための各種処理群 ヘッダファイル
 *          written by H.Tsujimura  14 Jun 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/wassr.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 18    08/11/21 15:35 Tsujimura543
 * PostPhotoViaAPI() を追加
 * 
 * 17    08/08/02 2:23 Tsujimura543
 * GetChannelList() を追加
 * 
 * 16    08/08/01 4:35 Tsujimura543
 * 画像の投稿も「チャンネル」対応した
 * 
 * 15    08/08/01 2:39 Tsujimura543
 * Wassr への画像の投稿に対応
 * 
 * 14    08/07/08 14:51 Tsujimura543
 * Wassr の「イイネ!」に対応
 * 
 * 13    07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 12    07/07/05 0:50 Tsujimura543
 * (1) GetStatFromJSON(), GetUserTimeline() の引数を変更
 * (2) TWITTER_USER 構造体の変更(orig_userNameを追加)に伴う修正
 * (3) MakeMessageForScreen() と MakeMessageForLogging() を用意
 * 
 * 11    07/06/25 18:03 Tsujimura543
 * DeleteReserved(), DeleteReserved2() 関連、コードを整理
 * 
 * 10    07/06/25 17:40 Tsujimura543
 * DeleteReserved(), DeleteReserved2() を追加
 * 
 * 9     07/06/21 19:15 Tsujimura543
 * SetUserAgent() を CService 内のメソッドに一本化した
 * 
 * 8     07/06/20 19:28 Tsujimura543
 * GetStatusID() を導入
 * 
 * 7     07/06/19 23:01 Tsujimura543
 * CService を導入し、ソースコードを整理した
 * 
 * 6     07/06/18 18:51 Tsujimura543
 * デフォルトアイコンの定義を defaultImage.h に移す
 * 
 * 5     07/06/15 17:37 Tsujimura543
 * Wassr 特有の文字化け(絵文字が原因だと思われる)対策を追加
 * 
 * 4     07/06/14 21:11 Tsujimura543
 * ログ出力時の「スクリーン名」が UTF-8 になっていなかった不具合を修正
 * 
 * 3     07/06/14 19:17 Tsujimura543
 * ソースを整理
 * 
 * 2     07/06/14 19:06 Tsujimura543
 * friends_timeline と user_timeline を合成して、Twitter 互換の
 * friends_timeline を生成する処理を追加
 * 
 * 1     07/06/14 17:55 Tsujimura543
 * 新規作成 (暫定版)
 */

#ifndef __WASSR_H__
#define __WASSR_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CService.h"

typedef struct WassrChennelList {
    char  image_url[MAX_URLLENGTH]; // チャンネルアイコンのURL
    char  title[MAX_CATNAMELENGTH]; // チャンネル名
    char  name_en[MAX_NAMELEN];     // チャンネルID (英語名)
}   WASSR_CHANNEL_LIST;

class CWassr : public CService
{
public:
    CWassr();
    ~CWassr();

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

    // 指定ユーザを friend にする
    bool    AddFriend( const char *userID );

    // 指定ユーザを friend から外す
    bool    RemoveFriend( const char *userID );

    // 指定 status を favorites にする (「イイネ!」をつける)
    bool    SetFavorite( const char *statusID );

    // 自分のスクリーン名の取得
    CString GetScreenName();

    // 画像を投稿
    BOOL
    PostPhoto(
        const char  *filename, // (I) 投稿する画像のファイル名
        size_t      filesize,  // (I) 投稿する画像のファイルサイズ
        const char  *caption,  // (I) 投稿する画像といっしょに投稿する「発言」
        char        *url );    // (O) アップロード先URL

    BOOL
    PostPhotoViaAPI(
        const char  *filename, // (I) 投稿する画像のファイル名
        size_t      filesize,  // (I) 投稿する画像のファイルサイズ
        const char  *caption,  // (I) 投稿する画像といっしょに投稿する「発言」
        char        *url );    // (O) アップロード先URL

    // 参加中のチャンネルの一覧の取得
    WASSR_CHANNEL_LIST  *GetChannelList( int &numOfChannels );

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

    CTime           GetCreatedAtFromJSON( const char *p,
                                          const char *terminator );
    CString         GetIdFromJSON( const char *p,
                                   const char *terminator );
    CString         GetHtmlFromJSON( const char *p,
                                     const char *terminator );
    TWITTER_USER    GetUserFromJSON( const char *p,
                                     const char *terminator,
                                     const char *userName );

    long            GetEpochFromJSON( const char *p,
                                      const char *terminator );
    char            *GetUserLoginIdFromJSON(
                                      const char *p,
                                      const char *terminator );

    char            *Regulize( char *text, const char *origText );

private:
    bool    loginWassr( const char *username,
                        const char *password,
                        char       *cookie,
                        char       *key,
                        const char *channel,
                        char       *channel_rid );

    BOOL    readImageData( const char *filename,
                           size_t filesize,
                           FILEINF *fInfo );
    size_t  makeRequestForPhoto(
                        char          *request,
                        char          *contentType,
                        const char    *key,
                        const char    *caption,
                        const char    *channel_rid,
                        const FILEINF *fInfo );

    char    *getPhotoURL( const char *response,
                          const char *channel,
                          char       *url );

    BOOL
    PostPhoto(
        const char *filename,// (I)   投稿する画像のファイル名
        size_t     filesize, // (I)   投稿する画像のファイルサイズ
        const char *caption, // (I)   投稿する画像といっしょに投稿する「発言」
        char       *url,     // (O)   アップロード先URL
        char       *cookie,  // (I/O) クッキー
        const char *key,            // (I) CSRF対策キー
        const char *channel,        // (I) チャンネル名
        const char *channel_rid );  // (I) チャンネルID


    size_t  makeRequestForPhotoViaAPI(
                        char          *request,
                        char          *contentType,
                        const char    *key,
                        const char    *caption,
                        const char    *channel_rid,
                        const FILEINF *fInfo );

    BOOL
    PostPhotoViaAPI(
        const char *filename,  // (I) 投稿する画像のファイル名
        size_t     filesize,   // (I) 投稿する画像のファイルサイズ
        const char *caption,   // (I) 投稿する画像といっしょに投稿する「発言」
        const char *rid,       // (I) 今回投稿する「発言」の返信対象「発言ID」
        char       *url,       // (O) アップロード先URL
        const char *channel ); // (I) チャンネル名

private:
    CWassr( CWassr &obj );
    CWassr  operator = ( CWassr &obj );
};

#endif  /* __WASSR_H__ */