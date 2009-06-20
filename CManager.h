/*
 * CManager.h   : Twitter クライアント chirrup
 *      CManager クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  19 Jun 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/CManager.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 12    09/05/12 17:16 Tsujimura543
 * 「スレッド起動時刻」を各タイムライン取得処理を呼び出すタイミングで
 * 上書きするように変更 (サービスごと → タイムラインごと に変更)
 * 
 * 11    09/04/16 16:11 Tsujimura543
 * 新規インストール時に OAuth 認証設定したあと、スクリーン名の取得に失敗
 * する等、OAuth 対応時に作りこんでしまったバグを修正
 * 
 * 10    09/03/31 21:27 Tsujimura543
 * Twitter の OAuth 対応準備 その5
 * 
 * 9     09/03/30 22:19 Tsujimura543
 * Twitter の OAuth 対応準備
 * 
 * 8     08/07/16 4:13 Tsujimura543
 * 「同時投稿対象」の設定を「設定」ダイアログでも設定できるようにした
 * 
 * 7     07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 6     07/08/28 1:56 Tsujimura543
 * 同時投稿対象にするサービスを選択できるようにした
 * 
 * 5     07/08/25 0:45 Tsujimura543
 * 「ついすた」に対応 (表示)
 * 
 * 4     07/06/20 15:46 Tsujimura543
 * InitTimelineInfo() を廃止
 * 
 * 3     07/06/20 5:16 Tsujimura543
 * CheckKeys() に引数を追加
 * 
 * 2     07/06/20 3:16 Tsujimura543
 * 設定ファイルの読み書き処理を chirrupDlg から CManager と
 * CJaikuManager に移した
 * 
 * 1     07/06/19 21:16 Tsujimura543
 * 今まで CChirrupDlg 内でやっていた各サービスを管理、制御する処理を
 * 抽出し CManager として独立させた
 */

#ifndef __C_MANAGER_H__
#define __C_MANAGER_H__

#include "twitterTimeline.h"

class CManager  {
public:
    CManager();
    CManager( CTwitterTimeline::SVC_TYPE serviceType );

    ~CManager();

    CString             m_serviceName;
    CString             m_serviceSymbol;
    CString             m_screenName;
    CString             m_username;
    CString             m_password;
    CString             m_oauthToken;
    CString             m_oauthTokenSecret;
    bool                m_useOAuth;
    bool                m_useBASIC;
    bool                m_simultaneousPost;

    TIMELINE_INFO       m_sFriendsTimeline;
    TIMELINE_INFO       m_sPublicTimeline;
    TIMELINE_INFO       m_sUserTimeline;

    CTwitterTimeline    m_friendsTimeline;
    CTwitterTimeline    m_publicTimeline;
    CTwitterTimeline    m_userTimeline;

    CService            *m_service;

    void    SetConfig( CString username,
                       CString password,
                       BOOL checkMultiPost,
                       TIMELINE_INFO sFriendsTimeline,
                       TIMELINE_INFO sPublicTimeline,
                       TIMELINE_INFO sUserTimeline );
    void    GetConfig( CString &username,
                       CString &password,
                       BOOL &checkMultiPost,
                       TIMELINE_INFO &sFriendsTimeline,
                       TIMELINE_INFO &sPublicTimeline,
                       TIMELINE_INFO &sUserTimeline );

    void    ExecuteUpdate( CStatic          *sp,
                           bool             useTwitStar,
                           CChirrupDlg      *cdlg,
                           ProceedingDialog *pdlg );
    bool    ExecutePost( CString          monologue,
                         CStatic          *sp,
                         ProceedingDialog *pdlg );
    void    GetScreenName();
    void    SetUpUserInfo();

    void    SetLogFileSpec();

    void    WriteKeys( FILE          *fp,
                       char          *key,
                       unsigned char **secret,
                       bool          &done );
    void    WriteKeys( FILE                *fp,
                       const TIMELINE_INFO *t,
                       const char          *timelineType );

    bool    CheckKeys( const char          *p,
                       const unsigned char *rsaString,
                       char                *encrypted,
                       bool                &ret );
    bool    EvalKeys( const char          *p,
                      const unsigned char *rsaString,
                      char                *encrypted );
    bool    EvalKeys( TIMELINE_INFO *t,
                      const char    *timelineType,
                      const char    *p );

    CTwitterTimeline    *GetFriendsTimeline()
    {
        return ( &m_friendsTimeline );
    }

    CTwitterTimeline    *GetPublicTimeline()
    {
        return ( &m_publicTimeline );
    }

    CTwitterTimeline    *GetUserTimeline()
    {
        return ( &m_userTimeline );
    }

private:
    CManager( CManager &obj );
    CManager    operator = ( CManager &obj );
};

#endif  /* __C_MANAGER_H__ */
