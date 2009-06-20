/*
 * twitterTimeline.h : Twitter クライアント chirrup
 *      timeline 関連各種処理群 ヘッダファイル
 *          written by H.Tsujimura  4 Apr 2007 / 25 May 2007
 *
 *      Copyright (c) 2007, 2008, 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/twitterTimeline.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 12    09/03/31 23:29 Tsujimura543
 * Twitter の OAuth 対応準備 その7
 * 
 * 11    08/08/22 18:42 Tsujimura543
 * 「はてなハイク」対応
 * 
 * 10    08/07/31 18:19 Tsujimura543
 * 「チャンネル」に対応
 * 
 * 9     07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 8     07/07/05 16:08 Tsujimura543
 * GetServiceName() を追加
 * 
 * 7     07/06/21 22:40 Tsujimura543
 * LoadUserIcon() を変更、ユーザアイコンの URL が不明な場合、Twitter
 * の ShowUser API を使ってアイコンの URL を取得するようにした
 * 
 * 6     07/06/20 15:47 Tsujimura543
 * timelineSetting 構造体のコンストラクタを追加
 * 
 * 5     07/06/18 18:52 Tsujimura543
 * LoadUserIcon() を導入し、ユーザアイコンの表示処理を一本化した
 * 
 * 4     07/06/13 0:12 Tsujimura543
 * (1) TIMELINE_INFO 関連 fix
 * (2) 初期設定ファイル読み書きを新しいログファイル管理仕様に対応させた
 * 
 * 3     07/06/12 19:49 Tsujimura543
 * ログファイル名の末尾に日付を埋め込むことができるようにした
 * 
 * 2     07/06/06 19:05 Tsujimura543
 * ログをファイルに書き出す機能を実装
 * 
 * 1     07/05/25 20:15 Tsujimura543
 * 新規作成 (chirrupDlg.h から分離、独立)
 */

#ifndef __TWITTER_TIMELINE_H__
#define __TWITTER_TIMELINE_H__


class CChirrupDlg;

typedef struct timelineSetting  {
    CString logFileName;
    bool    checkTimeline;
    bool    checkLogFile;
    bool    checkChannel;

    timelineSetting()
    {
        logFileName   = _T("");
        checkTimeline = false;
        checkLogFile  = false;
        checkChannel  = false;
    }
}   TIMELINE_INFO;


class CTwitterTimeline {
public:
    CTwitterTimeline();
    ~CTwitterTimeline();

    typedef enum serviceType   {
        SVC_TWITTER = 1,
        SVC_JAIKU,
        SVC_WASSR,
        SVC_MOGO2,
        SVC_TIMELOG,
        SVC_HARUFM,
        SVC_HATENAHAIKU
    }   SVC_TYPE;
    SVC_TYPE        m_serviceType;

    // 設定
    bool            m_checkTimeline;    // 閲覧対象とするか否か
    bool            m_checkChannel;     // 参加中のチャンネルも閲覧対象とするか否か
    bool            m_checkLogFile;     // basename に日付を付加するか否か
    CString         m_logFileBaseName;  // ログファイル basename
    CString         m_logFileExtention; // ログファイル 拡張子

    // user
    long            m_numOfUsers;
    TWITTER_USER    *m_users;

    // status
    long            m_numOfStats;
    TWITTER_STATUS  *m_stat;
	CString	        m_messages;

    // logging
    bool            m_logging;
    char            m_logFileName[MAX_PATH];
    FILE            *m_logFp;

    bool            InitTimeline();
    void            MoveTimeline();
    void            LoadTimeline( CChirrupDlg *cp, CString cacheDir );

    void            SetLogFileSpec( TIMELINE_INFO s );
    CString         GetServiceName();

    void            StartLogging();
    void            FinishLogging();
    void            WriteLog( const char *str );

private:
    CTwitterTimeline( CTwitterTimeline &obj );
    CTwitterTimeline    operator = ( CTwitterTimeline &obj );
};

bool
LoadUserIcon( CStatic                    *sp,
              TWITTER_USER               *u,
              CTwitterTimeline::SVC_TYPE &type,
              const char                 *cacheDir,
              CString                    username = _T(""),
              CString                    password = _T(""),
              bool                       useOAuth = false,
              CString                    oauthToken       = _T(""),
              CString                    oauthTokenSecret = _T("") );

#endif  /* __TWITTER_TIMELINE_H__ */