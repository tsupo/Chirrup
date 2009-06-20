/*
 * CJaikuManager.h   : Twitter クライアント chirrup
 *      CJaikuManager クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  20 Jun 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/CJaikuManager.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 5     09/04/15 1:17 Tsujimura543
 * Jaiuku の OAuth 対応準備
 * 
 * 4     07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 3     07/06/20 5:17 Tsujimura543
 * CheckKeys() に引数を追加
 * 
 * 2     07/06/20 3:16 Tsujimura543
 * 設定ファイルの読み書き処理を chirrupDlg から CManager と
 * CJaikuManager に移した
 * 
 * 1     07/06/20 1:53 Tsujimura543
 * 新規作成 (Jaiku 専用 CManager)
 */

#ifndef __C_JAIKU_MANAGER_H__
#define __C_JAIKU_MANAGER_H__

#include "CManager.h"

class CJaikuManager : public CManager
{
public:
    CJaikuManager();
    ~CJaikuManager();

    void    SetConfig( CString username,
                       CString password,
                       CString oauthToken,
                       CString oauthTokenSecret,
                       BOOL useOAuth,
                       BOOL useBASIC,
                       BOOL checkMultiPost,
                       TIMELINE_INFO sFriendsTimeline,
                       TIMELINE_INFO sPublicTimeline,
                       TIMELINE_INFO sUserTimeline );
    void    GetConfig( CString &username,
                       CString &password,
                       CString &oauthToken,
                       CString &oauthTokenSecret,
                       BOOL &useOAuth,
                       BOOL &useBASIC,
                       BOOL &checkMultiPost,
                       TIMELINE_INFO &sFriendsTimeline,
                       TIMELINE_INFO &sPublicTimeline,
                       TIMELINE_INFO &sUserTimeline );

    bool    ExecutePost( CString          monologue,
                         CStatic          *sp,
                         ProceedingDialog *pdlg );
    void    GetScreenName();

    void    WriteKeys( FILE          *fp,
                       char          *key,
                       unsigned char **secret,
                       bool          &done );
    bool    CheckKeys( const char          *p,
                       const unsigned char *rsaString,
                       char                *encrypted,
                       bool                &ret );
    bool    EvalKeys( const char          *p,
                      const unsigned char *rsaString,
                      char                *encrypted );

private:
    CJaikuManager( CJaikuManager &obj );
    CJaikuManager   operator = ( CJaikuManager &obj );
};

#endif  /* __C_JAIKU_MANAGER_H__ */
