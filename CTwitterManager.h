/*
 * CTwitterManager.h : Twitter クライアント chirrup
 *      CTwitterManager クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  20 Jun 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/CTwitterManager.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 8     09/05/12 17:16 Tsujimura543
 * 「スレッド起動時刻」を各タイムライン取得処理を呼び出すタイミングで
 * 上書きするように変更 (サービスごと → タイムラインごと に変更)
 * 
 * 7     09/03/31 21:27 Tsujimura543
 * Twitter の OAuth 対応準備 その5
 * 
 * 6     09/03/30 22:37 Tsujimura543
 * Twitter の OAuth 対応準備 その2
 * 
 * 5     08/07/16 4:13 Tsujimura543
 * 「同時投稿対象」の設定を「設定」ダイアログでも設定できるようにした
 * 
 * 4     07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 3     07/08/25 0:45 Tsujimura543
 * 「ついすた」に対応 (表示)
 * 
 * 2     07/08/06 17:31 Tsujimura543
 * Twitter の API 実行回数制限に抵触するのを防ぐ仕組みを導入
 * 
 * 1     07/06/20 5:17 Tsujimura543
 * 新規作成 (Twitter 専用 CManager)
 */

#ifndef __C_TWITTER_MANAGER_H__
#define __C_TWITTER_MANAGER_H__

#include "CManager.h"

class CTwitterManager : public CManager
{
public:
    CTwitterManager();
    ~CTwitterManager();

    TIMELINE_INFO       m_sReplies;
    CTwitterTimeline    m_replies;
    bool                m_twitterHealthy;
    time_t              m_lastUpdated;

    void    SetConfig( CString username,
                       CString password,
                       CString oauthToken,
                       CString oauthTokenSecret,
                       BOOL useOAuth,
                       BOOL useBASIC,
                       BOOL checkMultiPost,
                       TIMELINE_INFO sFriendsTimeline,
                       TIMELINE_INFO sPublicTimeline,
                       TIMELINE_INFO sUserTimeline,
                       TIMELINE_INFO sReplies );
    void    GetConfig( CString &username,
                       CString &password,
                       CString &oauthToken,
                       CString &oauthTokenSecret,
                       BOOL &useOAuth,
                       BOOL &useBASIC,
                       BOOL &checkMultiPost,
                       TIMELINE_INFO &sFriendsTimeline,
                       TIMELINE_INFO &sPublicTimeline,
                       TIMELINE_INFO &sUserTimeline,
                       TIMELINE_INFO &sReplies );

    void    ExecuteUpdate( CStatic          *sp,
                           bool             useTwitStar,
                           CChirrupDlg      *cdlg,
                           ProceedingDialog *pdlg );
    void    SetLogFileSpec();

    void    WriteKeys( FILE          *fp,
                       char          *key,
                       unsigned char **secret,
                       bool          &done );
    bool    EvalKeys( const char          *p,
                      const unsigned char *rsaString,
                      char                *encrypted );

    CTwitterTimeline    *GetReplies()
    {
        return ( &m_replies );
    }

private:
    CTwitterManager( CTwitterManager &obj );
    CTwitterManager operator = ( CTwitterManager &obj );
};

#endif  /* __C_TWITTER_MANAGER_H__ */
