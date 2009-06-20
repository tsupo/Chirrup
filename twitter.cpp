/*
 * twitter.cpp : Twitter クライアント chirrup
 *      Twitter API を利用するための各種処理群
 *          written by H.Tsujimura  4 Apr 2007 / 28 Apr 2007
 *
 *      Copyright (c) 2007, 2008, 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/twitter.cpp $
 * 
 * 2     09/06/18 1:33 tsupo
 * 2.01版
 * 
 * 87    09/06/16 0:51 Tsujimura543
 * アクセストークン取得時に返ってくるスクリーン名を利用するようにした
 * 
 * 86    09/06/16 0:01 Tsujimura543
 * Twitter の status ID が singed long で扱える範囲を超えてしまった
 * (2009年6月13日)ための対策として、CService::GetIdFromJSON() を呼ぶ
 * のをやめて、新たに CTwitter::GetIdFromJSON() を用意した
 * 
 * 85    09/06/11 18:53 Tsujimura543
 * Twitter の OAuth が 1.0 から 1.0a へ移行したのに伴う修正
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 84    09/04/28 20:52 Tsujimura543
 * タイムアウト取得処理が規定時間内に終わらない場合の処理を変更
 * (スレッド強制終了方式ではなく、イベント通知方式を採用)
 * 
 * 83    09/04/28 18:24 Tsujimura543
 * メモリリーク調査用のコードを追加 (デバッグビルド版のみ有効)
 * 
 * 82    09/04/10 17:10 Tsujimura543
 * SetStatFromJSON() 内の trancated 関連処理を修正 (URL の末尾が ... に
 * なっているものを本来の URL に展開するための処理を追加)
 * 
 * 81    09/04/09 22:38 Tsujimura543
 * public_timeline 以外のタイムライン取得時、count=60 を指定するようにした
 * (1回のAPIで60件取得するようにした)
 * 
 * 80    09/04/09 18:17 Tsujimura543
 * コメント修正
 * 
 * 79    09/04/09 18:16 Tsujimura543
 * OAuth 認証エラーが発生しているかどうかを判定するのに http レスポンス
 * コードが 401 かどうかも見るようにしてみた
 * 
 * 78    09/04/09 17:55 Tsujimura543
 * CheckOAuthResult() で表示する MessageBox の表示内容を修正
 * (title と本文が逆になっていた)
 * 
 * 77    09/04/09 17:50 Tsujimura543
 * OAuth 認証エラー時のレスポンス仕様変更に伴う修正を実施
 * 
 * 76    09/04/09 17:18 Tsujimura543
 * SetStatFromJSON() をリファクタリング
 * 
 * 75    09/04/09 16:03 Tsujimura543
 * API で取得した発言の trancated が true のときは、当該発言のパーマリンク
 * を GET して、完全な状態の発言を取得するようにした
 * 
 * 74    09/04/08 20:45 Tsujimura543
 * GetReplies() で呼び出す API を replies から mentions に移行した
 * 
 * 73    09/04/07 15:46 Tsujimura543
 * OAuth で "Invalid OAuth Request" が発生したときの処理を追加
 * 
 * 72    09/04/01 22:10 Tsujimura543
 * リファクタリング実施
 * 
 * 71    09/04/01 3:16 Tsujimura543
 * Twitter の OAuth 対応、完了
 * 
 * 70    09/03/30 23:58 Tsujimura543
 * Twitter の OAuth 対応準備 その4
 * 
 * 69    09/03/30 23:45 Tsujimura543
 * Twitter の OAuth 対応準備 その3
 * 
 * 68    09/03/10 22:14 Tsujimura543
 * GetStringFromJSON() にバッファオーバーラン対策を実施
 * 
 * 67    08/12/04 18:19 Tsujimura543
 * コード整理、安定化作業を実施
 * 
 * 66    08/09/03 19:21 Tsujimura543
 * delete [] response; するタイミングを修正
 * 
 * 65    08/08/18 18:59 Tsujimura543
 * 発言の冒頭に「>>メッセージID」と書くで、指定したメッセージへの
 * replyを投稿できるようにした
 * 
 * 64    08/08/11 11:23 Tsujimura543
 * AddFriend, RemoveFriend, SetFavorite, DeleteDirectMessage を GET
 * メソッドから POST メソッドに変更 (API の仕様変更に拠る)
 * 
 * 63    08/07/16 13:34 Tsujimura543
 * loginTwitter() を「Twitter 日本語版」にも対応させた
 * 
 * 62    08/07/14 16:54 Tsujimura543
 * Twitter の「API制限情報取得API」を呼ぶ回数、タイミングを調整し直した
 * 
 * 61    08/06/30 20:10 Tsujimura543
 * long GetRateLimitStatus() を追加
 * 
 * 60    08/06/30 18:49 Tsujimura543
 * GetRateLimitStatus() を追加
 * 
 * 59    08/04/22 21:20 Tsujimura543
 * CutInReplyTo() を修正
 * 
 * 58    08/04/15 21:10 Tsujimura543
 * CutInReplyTo() を追加、in_reply_to: の入れ子構造に対応
 * 
 * 57    07/12/19 18:44 Tsujimura543
 * http 関連関数呼び出しまわりを整理
 * 
 * 56    07/12/19 17:35 Tsujimura543
 * (1) http_postEx() → _http_postBASIC() へ移行
 * (2) http_getEx(), http_getBASICEx() → _http_getBASIC() へ移行
 * 
 * 55    07/12/19 16:56 Tsujimura543
 * _http_getBASIC() の引数を追加
 * 
 * 54    07/12/14 16:27 Tsujimura543
 * (1) http_getBASIC() → _http_getBASIC() に置換
 * (2) http_postBASIC() → _http_postBASIC() に置換
 * 
 * 53    07/11/26 20:03 Tsujimura543
 * isNecessaryToCheckProxyInfo() を使って、エラー発生時の処理を書き直した
 * 
 * 52    07/09/26 20:18 Tsujimura543
 * コメントを整理
 * 
 * 51    07/09/26 20:16 Tsujimura543
 * replaceEntityStrings() のメモリ解放処理をダイレクトメッセージ受信処理
 * にも入れておく
 * 
 * 50    07/09/26 20:13 Tsujimura543
 * ダイレクトメッセージにも replaceEntityStrings() を適用するようにした
 * 
 * 49    07/09/11 15:45 Tsujimura543
 * SetFavorite() でコールする API の URL を変えてみた(ら、うまくいった)。
 * (公式の API 仕様書の URL が間違っている?)
 * 
 * 48    07/09/07 19:40 Tsujimura543
 * 表示用文字列整形時に replaceEntityStrings() を導入。実体参照を近似文字
 * で表現可能な場合は、近似文字に置換するようにした
 * 
 * 47    07/08/31 18:30 Tsujimura543
 * 「favorites/create API による favorites のセット」を試験的に導入
 * (2007年8月31日18時現在、まだ、API は実装されてないのか、Page Not Found
 *  が返ってくるため、API 実行失敗時は、従来の favorites 登録処理を実行す
 *  るようにしている)
 * 
 * 46    07/08/25 1:53 Tsujimura543
 * 「ついすた」対応 (実際に☆をつける)
 * 
 * 45    07/08/25 0:45 Tsujimura543
 * 「ついすた」に対応 (表示)
 * 
 * 44    07/08/17 17:21 Tsujimura543
 * SetFavorite() を追加
 * 
 * 43    07/08/13 12:05 Tsujimura543
 * デバッグ用の ASSERT() [のうち、不要になったもの]を削除
 * 
 * 42    07/08/06 17:30 Tsujimura543
 * (1) timeline の JSON 内の各要素の出現順序に依存しないように、JSON
 *     解釈処理を書き直した
 * (2) JSON 中の &quot; 等の表現方法が変わったのに対応
 * 
 * 41    07/07/23 15:00 Tsujimura543
 * (1) 取得した timeline に souce という項目が増えたのに対応
 * (2) timeline の JSON が createdAt ではなく user で始まる場合にも対応
 * 
 * 40    07/07/19 21:35 Tsujimura543
 * タイムスタンプ関連の処理を VC++ 6 / VC++ 2005 共通コードに変更
 * 
 * 39    07/07/18 10:41 Tsujimura543
 * MakeMessageForLogging() を呼ぶ箇所が消えていたのを復活させた
 * 
 * 38    07/07/17 18:52 Tsujimura543
 * ソースを整理
 * 
 * 37    07/07/17 18:43 Tsujimura543
 * GetTinyURL() を使い、自分で tinyurl 化してから投稿するようにしてみた
 * (URL に # が含まれる場合、Twitter 自身の tinyurl 処理では # 以降が
 *  消された形で tinyurl 化されてしまう、という問題があるため)
 * 
 * 36    07/07/10 22:32 Tsujimura543
 * 「発言」の POST 時のパラメータに source=API名 を追加してみた
 * 
 * 35    07/07/05 0:50 Tsujimura543
 * (1) GetStatFromJSON(), GetUserTimeline() の引数を変更
 * (2) TWITTER_USER 構造体の変更(orig_userNameを追加)に伴う修正
 * (3) MakeMessageForScreen() と MakeMessageForLogging() を用意
 * 
 * 34    07/07/03 13:46 Tsujimura543
 * Visual Studio 2005 でのビルド結果を反映
 * 
 * 33    07/06/26 16:01 Tsujimura543
 * PostUpdate() 内で確保する request のサイズを修正
 * 
 * 32    07/06/25 23:22 Tsujimura543
 * status ID を表示、ログ出力するようにしてみた
 * 
 * 31    07/06/25 21:10 Tsujimura543
 * memcpy() を使っていたところをコピーコンストラクタを使うように修正
 * 
 * 30    07/06/25 18:24 Tsujimura543
 * 不要なコードを削除
 * 
 * 29    07/06/25 18:03 Tsujimura543
 * DeleteReserved(), DeleteReserved2() 関連、コードを整理
 * 
 * 28    07/06/21 19:15 Tsujimura543
 * SetUserAgent() を CService 内のメソッドに一本化した
 * 
 * 27    07/06/21 13:36 Tsujimura543
 * PostUpdate() 内で確保している request のサイズが小さすぎる場合が
 * あることが判明。サイズの計算を修正した
 * 
 * 26    07/06/20 19:28 Tsujimura543
 * GetStatusID() を導入
 * 
 * 25    07/06/19 23:09 Tsujimura543
 * CService を導入し、ソースを整理した
 * 
 * 24    07/06/19 17:38 Tsujimura543
 * GetTwitterScreenName() → GetScreenName() に変更
 * 
 * 23    07/06/18 17:25 Tsujimura543
 * ExpandTinyURL() を修正、tinyurl がサービス停止中あるいは
 * 500 エラーを返してくる場合にretryし続ける不具合に対処
 * 
 * 22    07/06/14 22:58 Tsujimura543
 * GetStringFromJSON() を修正 (Wassr対策)
 * 
 * 21    07/06/13 21:05 Tsujimura543
 * 1つの発言中に tinyurl が複数含まれる場合に、最初の tinyurl しか展開
 * せず、残りはそのままになる不具合に対処
 * 
 * 20    07/06/13 19:18 Tsujimura543
 * Twitter の Replies の閲覧、ログ出力に対応
 * 
 * 19    07/06/13 15:55 Tsujimura543
 * 「ダイレクトメッセージの削除」に対応
 * 
 * 18    07/06/13 3:07 Tsujimura543
 * 不要になったコードを削除
 * 
 * 17    07/06/13 3:02 Tsujimura543
 * tinyurl 展開処理を変更 (tinyurl の preview 機能を利用するように
 * してみた)
 * 
 * 16    07/06/11 18:39 Tsujimura543
 * Twitter の user_timeline の閲覧をサポート
 * 
 * 15    07/06/07 19:23 Tsujimura543
 * リファクタリング
 * 
 * 14    07/06/07 3:27 Tsujimura543
 * ログファイルのタイムスタンプが9時間もしくは18時間ずれる不具合を修正
 * 
 * 13    07/06/06 23:18 Tsujimura543
 * ログに記録する日時を UTC からローカル時間に変更
 * 
 * 12    07/06/06 21:24 Tsujimura543
 * ログをファイルに書き出す機能を実装
 * 
 * 11    07/06/05 20:31 Tsujimura543
 * _http_XXX() 系関数の引数 pdlg が NULL でもいいようにしてみた
 * 
 * 10    07/06/04 21:11 Tsujimura543
 * friend の add と remove を実装 (for Twitter)
 * 
 * 9     07/05/29 5:43 Tsujimura543
 * Jaiku への投稿をサポート
 * 
 * 8     07/05/29 3:56 Tsujimura543
 * Jaiku (の public_timeline の閲覧) に対応
 * 
 * 7     07/05/26 0:22 Tsujimura543
 * Twitter と通信する部分を別スレッド化してみた
 * 
 * 6     07/05/25 21:06 Tsujimura543
 * tinyurl 展開機能を追加
 * 
 * 5     07/05/23 22:24 Tsujimura543
 * public_timeline の取得に対応
 * 
 * 4     07/05/11 22:18 Tsujimura543
 * (1) 発言が重複して表示されてしまうことがある不具合に対処
 * (2) Twitter 側から送られてくる timeline に抜けがある場合に備えて、
 *     24時間分余分に timeline を取得して、補完できるようにしてみた
 * 
 * 3     07/05/11 21:28 Tsujimura543
 * utf2sjis() を any2sjis() に置き換えた
 * 
 * 2     07/04/27 20:53 Tsujimura543
 * GetTwitterScreenName() を追加
 * 
 * 1     07/04/27 19:36 Tsujimura543
 * 新規作成 (今まで複数のソースに分散していた Twitter API 関連処理を集大成
 * したものとして、CTwitter クラスを用意した)
 */

#include "chirrup.h"
#include "twitter.h"
#include "twitterTimeline.h"
#include "http.h"
extern "C" {
#include "utility.h"
#include "sha1.h"
}
#include "InputPinDialog.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/twitter.cpp 2     09/06/18 1:33 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

CTwitter::CTwitter() : CService()
{
    m_numOfMessages = 0;
    m_dm            = NULL;

    m_numOfStats4   = 0;
    m_stat4         = NULL;

#ifdef  _DEBUG
    m_serviceName   = _T("twitter");
#endif
    m_serviceSymbol = _T("Twitter");
    m_max_remain    = TWITTER_MAX_REMAIN;
    m_remain        = TWITTER_MAX_REMAIN;
}

CTwitter::~CTwitter()
{
    if ( m_stat4 ) {
        delete [] m_stat4;
        m_stat4 = NULL;
    }
}

void CTwitter::DeleteReserved( TWITTER_STATUS *sp )
{
    if ( sp && sp->reserved ) {
    }
}

void CTwitter::DeleteReserved2( TWITTER_STATUS *sp )
{
    if ( sp && sp->reserved2 ) {
    }
}

/*
 *  Twitter API
 */

// 発言を投稿
bool
CTwitter::PostUpdate( CString monologue, ProceedingDialog *pdlg )
{
    bool        ret = false;
    size_t      sz  = MAX_CONTENT_SIZE;
    size_t      len = monologue.GetLength() * 18;
    char        *request  = new char[7 + 64 + len + 1 + MAX_KEYLENGTH];
    char        *response = new char[sz];
    const char  *url = "http://twitter.com/statuses/update.xml";
    char        rid[MAX_KEYLENGTH];
    char        *p;

    rid[0] = NUL;
    if ( !strncmp( monologue, ">>", 2 ) ) {
        strncpy( rid, ((const char *)monologue) + 2, MAX_KEYLENGTH - 2 );
        rid[MAX_KEYLENGTH - 2] = NUL;
        p = strchr( rid, ' ' );
        if ( p ) {
            *p = NUL;
            monologue = strchr( monologue, ' ' ) + 1;
        }
    }
    p = sjis2utf( monologue );

    if ( request && response ) {
        if ( m_useOAuth ) {
            // OAuth 認証
            char    *request0 = new char[sz];
            char    key[MAX_KEYLENGTH * 2];
            char    base[MAX_CONTENT_SIZE];
            char    param[MAX_CONTENT_SIZE];

            key[0]   = NUL;
            base[0]  = NUL;
            param[0] = NUL;
            if ( rid[0] )
                sprintf( param,
                         "in_reply_to_status_id=%s&",
                         rid );
            MakeOAuthBase( url, "POST", key, base, param );

            sprintf( request0, "%s", p ? p : (const char *)monologue );
            p = GetTinyURL( request0 );
            sprintf( request0,
                     "&"
                     "source=%s&"
                     "status=%s",
                     "Chirrup",
                     encodeURLi( p ? p : monologue, FALSE ) );
            strcat( param, request0 );

            MakeOAuthRequest( url, request0, key, base, param );

            SetUserAgent();
            setUpReceiveBuffer( response, sz );
            _http_postBASIC( request0, NULL, NULL, "", response, NULL, NULL );
            delete [] request0;
        }
        else {
            // BASIC 認証
            sprintf( request, "%s", p ? p : (const char *)monologue );
            p = GetTinyURL( request );
            sprintf( request,
                     "status=%s&"
                     "source=%s",
                     encodeURL( p ? p : monologue ),
                     "Chirrup" );
            if ( rid[0] )
                sprintf( request + strlen(request),
                         "&in_reply_to_status_id=%s",
                         rid );
            SetUserAgent();
            setUpReceiveBuffer( response, sz );
            _http_postBASIC( url, m_username, m_password,
                             request, response, NULL, pdlg );
        }
        if ( *response ) {
            if ( strstr( response, "<created_at>" ) )
                ret = true;
            else if ( m_useOAuth )
                CheckOAuthResult( response );
        }
    }

    if ( response )
        delete [] response;
    if ( request )
        delete [] request;

    return ( ret );
}


CString
CTwitter::GetTimeline(
                CString          &messages,
                TWITTER_STATUS   **stat,
                long             &numOfStats,
                TIMELINE_TYPE    t,
                const char       *endPointURL,
                CTwitterTimeline *timeline,
                ProceedingDialog *pdlg
            )
{
    CChirrupApp *ap = (CChirrupApp *)AfxGetApp();

#ifdef  _DEBUG
    _CrtMemState s1, s2, s3;
    _CrtMemCheckpoint( &s1 );
#endif

    if ( timeline->m_numOfStats > 0 ) {
        if ( !(*stat) ) {
            *stat = new TWITTER_STATUS[MAX_NUMOFSTATUS];
            numOfStats = 0;
        }
        int i;
        for ( i = 0; i < timeline->m_numOfStats; i++ )
            (*stat)[i] = (timeline->m_stat)[i];
        numOfStats = timeline->m_numOfStats;
    }

    if ( m_remain > 0 ) {
        size_t  sz = MAX_CONTENT_SIZE * 16;
        char    *response = new char[sz];
        if ( response ) {
            CString url = endPointURL;
            if ( *stat ) {
                CTime   t;

                t = (*stat)[0].createdAt;
                t -= 24 * 60 * 60;  // 24時間前を指定 (Twitterのログ抜け対策)
                url += "?since=";
                url += encodeDateTime(t.Format("%a, %d %b %Y %H:%M:%S GMT"));
                    // Tue%2C+27+Mar+2007+22%3A55%3A48+GMT
            }

            SetUserAgent();
            setUpReceiveBuffer( response, sz );
            if ( t != PUBLIC_TIMELINE ) {
                if ( m_useOAuth ) {
                    // OAuth 認証
                    char    *request = new char[sz];
                    char    targetURL[MAX_URLLENGTH];
                    char    since[MAX_URLLENGTH];
                    char    *p = strstr( url, "?since=" );
                    if ( p ) {
                        strncpy( targetURL, url, p - url );
                        targetURL[p - url] = NUL;
                        strcpy( since, p + 7 );

                        p = decodeURL( since );
                        char    *q;
                        do {
                            q = strchr( p, '+' );
                            if ( q )
                                *q = ' ';
                        } while ( q );
                        strcpy( since, p );
                    }
                    else {
                        strcpy( targetURL, url );
                        since[0] = NUL;
                    }

                    char    key[MAX_KEYLENGTH * 2];
                    char    base[MAX_CONTENT_SIZE];
                    char    param[MAX_CONTENT_SIZE];

                    key[0]   = NUL;
                    base[0]  = NUL;
                    param[0] = NUL;
                    strcpy( param, "count=60&" );
                    MakeOAuthBase( targetURL, "GET", key, base, param );

                    if ( since[0] )
                        sprintf( param + strlen(param),
                                 "&"
                                 "since=%s",
                                 encodeURLi( since, FALSE ) );
                    MakeOAuthRequest( targetURL, request, key, base, param );

                    SetUserAgent();
                    setUpReceiveBuffer( response, sz );
                    _http_getBASIC(request, NULL, NULL, response, NULL, NULL);
                    delete [] request;
                }
                else {
                    // BASIC 認証
                    url += strchr( url, '?' ) ? "&" : "?";
                    url += "count=60";  // 200件まで指定可能(だけど控え目に)
                    _http_getBASIC( url, m_username, m_password, response,
                                    NULL, pdlg );
                }
            }
            else
                _http_get( url, response, pdlg );
                    // PUBLIC_TIMELINEは最大20件までしか取得できない
            if ( response[0] ) {
                char    *p  = response;
                bool    ret = true;
                if ( (t != PUBLIC_TIMELINE) && m_useOAuth )
                    ret = CheckOAuthResult( p );
                if ( ret == true ) {
                    if ( strstr( p, "\"in_reply_to\":{\"" ) ) {
#ifdef  _DEBUG
                        FILE    *fp = fopen( "./twitter_orig.json", "w" );
                        if ( fp ) {
                            fputs( p, fp );
                            fclose( fp );
                        }
#endif
                        p = CutInReplyTo( (char *)p );
                    }

                    GetStatFromJSON( response, stat, numOfStats );
                    WriteLog( timeline );
                }

                int i;
                messages = _T("");
                for ( i = 0; i < numOfStats; i++ ) {
                    if ( ap->m_event ) {
                        DWORD   r = WaitForSingleObject( ap->m_event, 0 );
                        if ( r == WAIT_OBJECT_0 ) {
                            // 作業中断
                            ResetEvent( ap->m_event );
#ifdef  _DEBUG
                            MessageBox( NULL,
                                        "作業中断",
                                        "CTwitter::GetTimeline()",
                                        MB_OK|MB_ICONWARNING );
#endif
                            break;
                        }
                    }

                    MakeMessageForScreen( messages, &((*stat)[i]) );
                    if ( messages.GetLength() >= (MAX_CONTENT_SIZE / 2) )
                        break;
                }
            }

            replaceEntityStrings( NULL, CHARSET_UNKNOWN );
            delete [] response;
        }
    }

    timeline->m_numOfStats = numOfStats;
    if ( timeline->m_numOfStats > 0 ) {
        int i;
        for ( i = 0; i < numOfStats; i++ )
            (timeline->m_stat)[i] = (*stat)[i];
    }

#ifdef  _DEBUG
    _CrtMemCheckpoint( &s2 );
if ( _CrtMemDifference( &s3, &s1, &s2 ) )
   _CrtMemDumpStatistics( &s3 );
#endif
    return ( messages );
}

// friends_timeline を取得
CString
CTwitter::GetFriendsTimeline(
                CTwitterTimeline *timeline,
                ProceedingDialog *pdlg
            )
{
    GetTimeline( m_messages,
                 &m_stat,
                 m_numOfStats,
                 FRIENDS_TIMELINE,
                 "http://twitter.com/statuses/friends_timeline.json",
                 timeline,
                 pdlg );

    return ( m_messages );
}

// public_timeline を取得
CString
CTwitter::GetPublicTimeline(
                CTwitterTimeline *timeline,
                ProceedingDialog *pdlg
            )
{
    GetTimeline( m_messages2,
                 &m_stat2,
                 m_numOfStats2,
                 PUBLIC_TIMELINE,
                 "http://twitter.com/statuses/public_timeline.json",
                 timeline,
                 pdlg );

    return ( m_messages2 );
}

// user_timeline を取得
CString
CTwitter::GetUserTimeline(
                CTwitterTimeline *timeline,
                ProceedingDialog *pdlg
            )
{
    GetTimeline( m_messages3,
                 &m_stat3,
                 m_numOfStats3,
                 USER_TIMELINE,
                 "http://twitter.com/statuses/user_timeline.json",
                 timeline,
                 pdlg );

    return ( m_messages3 );
}

// replies (mentions) を取得
CString
CTwitter::GetReplies(
                CTwitterTimeline *timeline,
                ProceedingDialog *pdlg
            )
{
    GetTimeline( m_messages4,
                 &m_stat4,
                 m_numOfStats4,
                 REPLIES,
              // "http://twitter.com/statuses/replies.json",
                 "http://twitter.com/statuses/mentions.json",
                 timeline,
                 pdlg );

    return ( m_messages4 );
}


// ダイレクトメッセージを受信
TWITTER_DIRECT_MESSAGE  *
CTwitter::RecvDirectMessages( int &numOfMessages, ProceedingDialog *pdlg )
{
    const char  *url = "http://twitter.com/direct_messages.xml";
    size_t      sz   = MAX_CONTENT_SIZE * MAX_NUM_OF_DIRECTMESSAGES;
    char        *response = new char[sz];

    m_numOfMessages = 0;

    if ( !m_dm || !response ) {
        numOfMessages = m_numOfMessages;
        return ( NULL );
    }

    if ( m_useOAuth ) {
        // OAuth 認証
        char    *request = new char[sz];
        char    key[MAX_KEYLENGTH * 2];
        char    base[MAX_CONTENT_SIZE];
        char    param[MAX_CONTENT_SIZE];

        key[0]   = NUL;
        base[0]  = NUL;
        param[0] = NUL;
        MakeOAuthBase( url, "GET", key, base, param );
        MakeOAuthRequest( url, request, key, base, param );

        SetUserAgent();
        setUpReceiveBuffer( response, sz );
        _http_getBASIC( request, NULL, NULL, response, NULL, NULL );
        delete [] request;
    }
    else {
        // BASIC 認証
        SetUserAgent();
        setUpReceiveBuffer( response, sz );
        _http_getBASIC( url, m_username, m_password, response, NULL, pdlg );
    }
    if ( *response ) {
        if ( strstr( response, "<created_at>" ) ) {
            char    *p, *q, *r, *s;
            CString temp;

         // failure = false;
            p = response;
            while ( *p ) {
                q = strstr( p, "<direct_message>" );
                if ( !q )
                    break;
                p = q + 17;
                r = strstr( p, "</direct_message>" );
                if ( !r )
                    break;

                // id
                temp = GetStringFromXML( p, "id", r );
                strcpy( m_dm[m_numOfMessages].id, temp );

                // text
                temp = GetStringFromXML( p, "text", r );
                strcpy( m_dm[m_numOfMessages].text, temp );
                s = strchr( m_dm[m_numOfMessages].text, '&' );
                if ( s && strchr( s + 1, ';' ) )
                    strcpy( m_dm[m_numOfMessages].text,
                            replaceEntityStrings( m_dm[m_numOfMessages].text,
                                                  CHARSET_SHIFTJIS ) );

                // sender_id
                temp = GetStringFromXML( p, "sender_id", r );
                strcpy( m_dm[m_numOfMessages].sender.id, temp );

                // recipient_id
                temp = GetStringFromXML( p, "recipient_id", r );
                strcpy( m_dm[m_numOfMessages].recipient.id, temp );

                // created_at
                m_dm[m_numOfMessages].createdAt =
                                            GetTimeFromXML( p, "created_at" );

                // sender_screen_name
                temp = GetStringFromXML( p, "sender_screen_name", r );
                strcpy( m_dm[m_numOfMessages].sender.screenName, temp );

                // recipient_screen_name
                temp = GetStringFromXML( p, "recipient_screen_name", r );
                strcpy( m_dm[m_numOfMessages].recipient.screenName, temp );

                // deleted
                m_dm[m_numOfMessages].deleted = false;

                m_numOfMessages++;
                if ( m_numOfMessages >= MAX_NUM_OF_DIRECTMESSAGES )
                    break;
            }
        }
        else if ( m_useOAuth )
            CheckOAuthResult( response );
    }
    replaceEntityStrings( NULL, CHARSET_UNKNOWN );
    delete [] response;

    numOfMessages = m_numOfMessages;

    return ( m_dm );
}


// ダイレクトメッセージを送信
bool
CTwitter::SendDirectMessage( CString screenName, CString message )
{
    bool    ret = false;
    size_t  sz  = MAX_CONTENT_SIZE;
    size_t  len = strlen( screenName ) + (message.GetLength() * 3 / 2) * 6;
    char    *request  = new char[len + 1];
    char    *response = new char[sz];

    if ( request && response ) {
        const char  *url = "http://twitter.com/direct_messages/new.xml";
        char        *p = sjis2utf( message );

        if ( m_useOAuth ) {
            // OAuth 認証
            char    *request0 = new char[sz];
            char    key[MAX_KEYLENGTH * 2];
            char    base[MAX_CONTENT_SIZE];
            char    param[MAX_CONTENT_SIZE];

            key[0]   = NUL;
            base[0]  = NUL;
            param[0] = NUL;
            MakeOAuthBase( url, "POST", key, base, param );

            sprintf( param + strlen(param),
                     "&"
                     "text=%s&",
                     encodeURLi( p ? p : message, FALSE ) );
            sprintf( param + strlen(param),
                     "user=%s",
                     encodeURLi( screenName, FALSE ) );

            MakeOAuthRequest( url, request0, key, base, param );

            SetUserAgent();
            setUpReceiveBuffer( response, sz );
            _http_postBASIC( request0, NULL, NULL, "", response, NULL, NULL );
            delete [] request0;
        }
        else {
            // BASIC 認証
            sprintf( request,
                     "user=%s&",
                     encodeURL( screenName ) );
            sprintf( request + strlen( request ),
                     "text=%s",
                     encodeURL( p ? p : message ) );
            SetUserAgent();
            setUpReceiveBuffer( response, sz );
            _http_postBASIC( url, m_username, m_password,
                             request, response, NULL, NULL );
        }
        if ( *response ) {
            if ( strstr( response, "<created_at>" ) )
                ret = true;
            else if ( m_useOAuth )
                CheckOAuthResult( response );
        }
    }

    if ( response )
        delete [] response;
    if ( request )
        delete [] request;

    return ( ret );
}


// ダイレクトメッセージを削除
bool
CTwitter::DeleteDirectMessage( const char *messageID )
{
    bool    ret = false;
    size_t  sz  = MAX_CONTENT_SIZE;
    char    *request  = new char[sz];
    char    *response = new char[sz];
    char    url[MAX_URLLENGTH];

    if ( request && response ) {
        sprintf( request, "id=%s", messageID );
        sprintf( url,
                 "http://twitter.com/direct_messages/destroy/%s.xml",
                 messageID );
        if ( m_useOAuth ) {
            // OAuth 認証
            char    key[MAX_KEYLENGTH * 2];
            char    base[MAX_CONTENT_SIZE];
            char    param[MAX_CONTENT_SIZE];

            key[0]   = NUL;
            base[0]  = NUL;
            param[0] = NUL;
            MakeOAuthBase( url, "POST", key, base, param );
            MakeOAuthRequest( url, request, key, base, param );

            SetUserAgent();
            setUpReceiveBuffer( response, sz );
            _http_postBASIC( request, NULL, NULL, "", response, NULL, NULL );
        }
        else {
            // BASIC 認証
            SetUserAgent();
            setUpReceiveBuffer( response, sz );
            _http_postBASIC( url, m_username, m_password,
                             request, response, NULL, NULL );
        }
        if ( *response ) {
            if ( strstr( response, "<direct_message>" ) )
                ret = true;
            else if ( strstr( response,
                              "No direct message with that ID found." ) )
                MessageBox(
                    NULL,
                    "そのダイレクトメッセージはすでに削除されています  ",
                    "ダイレクトメッセージ削除済み",
                    MB_OK|MB_ICONWARNING );
            else if ( m_useOAuth )
                CheckOAuthResult( response );
        }
    }

    if ( response )
        delete [] response;
    if ( request )
        delete [] request;

    return ( ret );
}


// 指定ユーザの最新の発言を取得
TWITTER_USER
CTwitter::ShowUser( const char *userID )
{
    TWITTER_USER    user;
    size_t          sz  = MAX_CONTENT_SIZE;
    char            *response = new char[sz];
    char            url[MAX_URLLENGTH];
 // bool            ret = false;

    if ( response ) {
        sprintf( url,
                 "http://twitter.com/users/show/%s.xml",
                 userID );
        if ( m_useOAuth ) {
            // OAuth 認証
            char    *request = new char[sz];
            char    key[MAX_KEYLENGTH * 2];
            char    base[MAX_CONTENT_SIZE];
            char    param[MAX_CONTENT_SIZE];

            key[0]   = NUL;
            base[0]  = NUL;
            param[0] = NUL;
            MakeOAuthBase( url, "GET", key, base, param );
            MakeOAuthRequest( url, request, key, base, param );

            SetUserAgent();
            setUpReceiveBuffer( response, sz );
            _http_getBASIC( request, NULL, NULL, response, NULL, NULL );
            delete [] request;
        }
        else {
            // BASIC 認証
            SetUserAgent();
            setUpReceiveBuffer( response, sz );
            _http_getBASIC( url, m_username, m_password, response, NULL, NULL );
        }
        if ( *response ) {
            char    *p = strstr( response, "<profile_image_url>" );
            if ( p ) {
             // ret  = true;
                user = GetUserFromXML(response, response + strlen(response));
            }
            else if ( m_useOAuth )
                CheckOAuthResult( response );
        }

        delete [] response;
    }

    return ( user );
}

// 指定ユーザを friend にする
bool CTwitter::AddFriend( const char *userID )
{
    size_t  sz  = MAX_CONTENT_SIZE;
    char    *request  = new char[sz];
    char    *response = new char[sz];
    char    url[MAX_URLLENGTH];
    bool    ret = false;

    if ( request && response ) {
        sprintf( request, "id=%s", userID );
        sprintf( url,
                 "http://twitter.com/friendships/create/%s.xml",
                 userID );
        if ( m_useOAuth ) {
            // OAuth 認証
            char    key[MAX_KEYLENGTH * 2];
            char    base[MAX_CONTENT_SIZE];
            char    param[MAX_CONTENT_SIZE];

            key[0]   = NUL;
            base[0]  = NUL;
            param[0] = NUL;
            MakeOAuthBase( url, "POST", key, base, param );
            MakeOAuthRequest( url, request, key, base, param );

            SetUserAgent();
            setUpReceiveBuffer( response, sz );
            _http_postBASIC( request, NULL, NULL, "", response, NULL, NULL );
        }
        else {
            // BASIC 認証
            SetUserAgent();
            setUpReceiveBuffer( response, sz );
            _http_postBASIC( url, m_username, m_password,
                             request, response, NULL, NULL );
        }
        if ( *response ) {
            char    *p = strstr( response, "<profile_image_url>" );
            if ( p )
                ret  = true;
            else if ( m_useOAuth )
                CheckOAuthResult( response );
        }
    }

    if ( response )
        delete [] response;
    if ( request )
        delete [] request;

    return ( ret );
}

// 指定ユーザを friend から外す
bool CTwitter::RemoveFriend( const char *userID )
{
    size_t  sz  = MAX_CONTENT_SIZE;
    char    *request  = new char[sz];
    char    *response = new char[sz];
    char    url[MAX_URLLENGTH];
    bool    ret = false;

    if ( response ) {
        sprintf( request, "id=%s", userID );
        sprintf( url,
                 "http://twitter.com/friendships/destroy/%s.xml",
                 userID );
        if ( m_useOAuth ) {
            // OAuth 認証
            char    key[MAX_KEYLENGTH * 2];
            char    base[MAX_CONTENT_SIZE];
            char    param[MAX_CONTENT_SIZE];

            key[0]   = NUL;
            base[0]  = NUL;
            param[0] = NUL;
            MakeOAuthBase( url, "POST", key, base, param );
            MakeOAuthRequest( url, request, key, base, param );

            SetUserAgent();
            setUpReceiveBuffer( response, sz );
            _http_postBASIC( request, NULL, NULL, "", response, NULL, NULL );
        }
        else {
            // BASIC 認証
            SetUserAgent();
            setUpReceiveBuffer( response, sz );
            _http_postBASIC( url, m_username, m_password,
                             request, response, NULL, NULL );
        }
        if ( *response ) {
            char    *p = strstr( response, "<profile_image_url>" );
            if ( p )
                ret  = true;
            else if ( m_useOAuth )
                CheckOAuthResult( response );
        }
    }

    if ( response )
        delete [] response;
    if ( request )
        delete [] request;

    return ( ret );
}

// 指定 status を favorites にする
bool CTwitter::SetFavorite( const char *statusID )
{
    size_t  sz  = MAX_CONTENT_SIZE;
    char    *request  = new char[sz];
    char    *response = new char[sz];
    char    url[MAX_URLLENGTH];
    bool    ret = false;

    if ( request && response ) {
        // favorites/create API による favorites のセット
        if ( m_useOAuth ) {
            // OAuth 認証
            sprintf( url,
                     "http://twitter.com/favorites/create/%s.json",
                     statusID );

            char    key[MAX_KEYLENGTH * 2];
            char    base[MAX_CONTENT_SIZE];
            char    param[MAX_CONTENT_SIZE];

            key[0]   = NUL;
            base[0]  = NUL;
            param[0] = NUL;
            MakeOAuthBase( url, "POST", key, base, param );
            MakeOAuthRequest( url, request, key, base, param );

            SetUserAgent();
            setUpReceiveBuffer( response, sz );
            _http_postBASIC( request, NULL, NULL, "", response, NULL, NULL );
        }
        else {
            // BASIC 認証
            SetUserAgent();
            setUpReceiveBuffer( response, sz );
            sprintf( request, "id=%s", statusID );
            sprintf( url,
                     "http://twitter.com/favorites/create/%s.json",
                     statusID );
            _http_postBASIC( url, m_username, m_password,
                             request, response, NULL, NULL );
        }
        if ( *response ) {
            if ( strstr( response, "created_at" ) )
                ret = true;
            else if ( m_useOAuth )
                CheckOAuthResult( response );
        }
    }

    if ( response )
        delete [] response;
    if ( request )
        delete [] request;

    return ( ret );
}

// 自分のスクリーン名の取得
CString CTwitter::GetScreenName()
{
    TWITTER_USER    user;
    CString         screenName = _T("");
    size_t          sz  = MAX_CONTENT_SIZE;
    char            *response = new char[sz];
    char            url[MAX_URLLENGTH];
    char            *targetURL =
                        "http://twitter.com/statuses/user_timeline.xml";

    if ( response ) {
        if ( m_useOAuth ) {
            // OAuth 認証
            char    *request = new char[sz];
            char    key[MAX_KEYLENGTH * 2];
            char    base[MAX_CONTENT_SIZE];
            char    param[MAX_CONTENT_SIZE];

            key[0]   = NUL;
            base[0]  = NUL;
            param[0] = NUL;

            sprintf( param,
                     "count=%d&",
                     1 );
            MakeOAuthBase( targetURL, "GET", key, base, param );
            MakeOAuthRequest( targetURL, request, key, base, param );

            SetUserAgent();
            setUpReceiveBuffer( response, sz );
            _http_getBASIC( request, NULL, NULL, response, NULL, NULL );
            delete [] request;
        }
        else {
            // BASIC 認証
            sprintf( url,
                     "%s?"
                     "count=%d",
                     targetURL, 1 );
            SetUserAgent();
            setUpReceiveBuffer( response, sz );
            _http_getBASIC(url, m_username, m_password, response, NULL, NULL);
        }
        if ( *response ) {
            char    *p = strstr( response, "<screen_name>" );
            if ( p ) {
             // ret  = true;
                user = GetUserFromXML(response, response + strlen(response));
                screenName = user.screenName;
            }
            else if ( m_useOAuth )
                CheckOAuthResult( response );
        }

        if ( (screenName.GetLength() == 0)  &&
             !isNecessaryToCheckProxyInfo()    ) {
            char    cookie[MAX_COOKIE_LEN];
            char    sname[MAX_KEYLENGTH];

            cookie[0] = NUL;
            sname[0]  = NUL;
            loginTwitter( m_username, m_password, cookie, sname );
            screenName = sname;
        }

        delete [] response;
    }

    return ( screenName );
}

// API制限状況の取得
CString
CTwitter::GetRateLimitStatus()
{
    CString limitStatus = _T("");
    long    remain = m_remain;
    long    rate   = m_max_remain;

    GetRateLimitStatus( rate, remain );

    if ( rate > 0 ) {
        char    buf[64];
        memset( buf, 0x00, 64 );

        limitStatus  = _T("API制限: ");
        limitStatus += ltoa( rate, buf, 10 );
        limitStatus += _T("回/時 -- 残り: ");
        limitStatus += ltoa( remain, buf, 10 );
        limitStatus += _T("回");

        m_remain = remain;
    }

    return ( limitStatus );
}

long
CTwitter::GetRateLimitStatus( long &rate, long &remain )
{
    size_t      sz  = MAX_CONTENT_SIZE;
    char        *response = new char[sz];
    const char  *targetURL =
                    "http://twitter.com/account/rate_limit_status.xml";

    if ( response ) {
        if ( m_useOAuth ) {
            // OAuth 認証
            char    *request = new char[sz];
            char    key[MAX_KEYLENGTH * 2];
            char    base[MAX_CONTENT_SIZE];
            char    param[MAX_CONTENT_SIZE];

            key[0]   = NUL;
            base[0]  = NUL;
            param[0] = NUL;
            MakeOAuthBase( targetURL, "GET", key, base, param );
            MakeOAuthRequest( targetURL, request, key, base, param );

            SetUserAgent();
            setUpReceiveBuffer( response, sz );
            _http_getBASIC( request, NULL, NULL, response, NULL, NULL );
            delete [] request;
        }
        else {
            // BASIC 認証
            SetUserAgent();
            setUpReceiveBuffer( response, sz );
            _http_getBASIC( "http://twitter.com/account/rate_limit_status.xml",
                            m_username, m_password, response, NULL, NULL );
        }
        if ( *response ) {
            char    *p = strstr( response, "<hourly-limit" );
            if ( p ) {
                char    *q = p + 12;

                p = strchr( q, '>' );
                if ( p++ ) {
                    if ( (*p >= '1') && (*p <= '9') )
                        rate = atol( p );
                    else
                        rate = 0;
                }
            }

            p = strstr( response, "<remaining-hits" );
            if ( p ) {
                char    *q = p + 15;

                p = strchr( q, '>' );
                if ( p++ ) {
                    if ( (*p == '-') || ((*p >= '1') && (*p <= '9')) )
                        remain = atol( p );
                    else
                        remain = 0;
                }
            }

            if ( m_useOAuth )
                CheckOAuthResult( response );
        }
        else {
            rate   = 0;
            remain = 0;
        }

        delete [] response;
    }

    return ( remain );
}


bool
CTwitter::loginTwitter(
                const char *username,
                const char *password,
                char       *cookie,
                char       *screenName
            )
{
    bool    ret = false;
    size_t  sz  = MAX_CONTENT_SIZE;
    char    request[BUFSIZ];
    char    *response = new char[sz];

    if ( response ) {
        sprintf( request,
                 "username_or_email=%s&"
                 "password=%s&"
                 "remember_me=1",
                 username, password );
        SetUserAgent();
        setUpReceiveBuffer( response, sz );
        _http_postBASIC( "https://twitter.com/sessions",
                         NULL, NULL,
                         request, response, cookie, NULL );
        if ( *response ) {
            char    *p = strstr(response, "Welcome back, <strong><a href=\"");
            char    *q;

            if ( p ) {
                ret = true;

                p += 31;
                if ( !strncmp( p, "http://twitter.com/", 19 ) )
                    p += 19;
                else if ( *p == '/' )
                    p++;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( screenName, p, q - p );
                    screenName[q - p] = NUL;
                }
            }
            else {
                // 日本語版
                p = strstr( response, sjis2utf(">プロフィール</a>") );
                if ( p ) {
                    while ( p >= response ) {
                        if ( *p != '<' ) {
                            p--;
                            continue;
                        }
                        if (!strncmp(p,"<a href=\"http://twitter.com/",28)) {
                            ret = true;
                            p += 28;
                            q = strchr( p, '"' );
                            if ( q ) {
                                strncpy( screenName, p, q - p );
                                screenName[q - p] = NUL;
                            }
                            break;
                        }
                    }
                }
            }
        }

        delete [] response;
    }

    return ( ret );
}

/*
 *  ユーティリティメソッド群 
 */

void CTwitter::SetStatFromJSON(
                        const char     *q,
                        const char     *s,
                        TWITTER_STATUS *sp,
                        CString        &message
                    )
{
    bool    first     = false;
    bool    trancated = false;

    if ( !strncmp( q, "\"user\"", 6 ) ) {
        const char  *r;

        sp->user = GetUserFromJSON( q, s );
        first = true;
        r = strstr( q, "}," );
        if ( r && (r < s) )
            q = r + 2;
    }

    sp->createdAt = GetCreatedAtFromJSON(q, s);
    trancated = GetTruncated( q, s );
    strcpy( sp->source, GetSource( q, s, sp->sourceURL ) );
    strcpy( sp->id,     GetStatusID(q, s) );
    strcpy( sp->text,   GetTextFromJSON( q, s, sp->orig_text ) );

    if ( strchr( sp->text, '&' ) ) {
        strcpy( sp->text, decodeString( sp->text ) );

        char    *p = strchr( sp->text, '&' );
        if ( p && strchr( p + 1, ';' ) )
            strcpy( sp->text,
                    replaceEntityStrings( sp->text, CHARSET_SHIFTJIS ) );
    }
    if ( strchr( sp->orig_text, '&' ) ) {
        strcpy( sp->orig_text, decodeString( sp->orig_text ) );

        char    *p = strchr( sp->orig_text, '&' );
        if ( p && strchr( p + 1, ';' ) )
            strcpy( sp->orig_text,
                    replaceEntityStrings( sp->orig_text, CHARSET_UTF8 ) );
    }

    if ( !first )
        sp->user = GetUserFromJSON( q, s );

    if ( trancated ) {
        // GET sp->id
        CString statusURL = _T("http://twitter.com/");
        statusURL += sp->user.screenName;
        statusURL += _T("/statuses/");
        statusURL += sp->id;

        size_t  sz   = MAX_CONTENT_SIZE * MAX_NUM_OF_DIRECTMESSAGES;
        char    *response = new char[sz];
#if 0
        if ( m_useOAuth ) {
            // OAuth 認証
            char    *request = new char[sz];
            char    key[MAX_KEYLENGTH * 2];
            char    base[MAX_CONTENT_SIZE];
            char    param[MAX_CONTENT_SIZE];

            key[0]   = NUL;
            base[0]  = NUL;
            param[0] = NUL;
            MakeOAuthBase( statusURL, "GET", key, base, param );
            MakeOAuthRequest( statusURL, request, key, base, param );

            SetUserAgent();
            setUpReceiveBuffer( response, sz );
            _http_getBASIC( request, NULL, NULL, response, NULL, NULL );
                // ↑ 「そんな API はない」という意味のエラーになる
            delete [] request;
        }

        if ( !m_useOAuth ||
             (strstr( response, "Invalid" ) && m_password.GetLength() > 0) ) {
            // BASIC 認証
            SetUserAgent();
            setUpReceiveBuffer( response, sz );
            _http_getBASIC( statusURL, m_username, m_password, response,
                            NULL, NULL );
        }
#else
        if ( (m_username.GetLength() > 0) &&
             (m_password.GetLength() > 0)    ) {
            SetUserAgent();
            setUpReceiveBuffer( response, sz );
            _http_getBASIC( statusURL, m_username, m_password, response,
                            NULL, NULL );
        }
#endif
        if ( *response ) {
            char    *p = strstr( response,
                                 "<span class=\"status-body\">"
                                 "<span class=\"entry-content\">" );
            if ( p ) {
                p += 54;

                char  *q = strstr( p, "</span>" );
                if ( q ) {
                    char    temp[MAX_DESCRIPTION_LEN * 2];
                    strncpy( temp, p, q - p );
                    temp[q - p] = NUL;

                    if ( strchr( temp, '<' ) ) {
                        char    *r, *s, *t;
                        bool    done = true;

                        // <a href="http://example.com/">http://exa...</a> の
                        // ように末尾を ... にされてしまっている URL を本来の
                        // URL に展開するための処理
                        //   ただし、<a href="/example">@example</a> のような
                        //   相対 URL は展開対象とはしない
                        p = temp;
                        do {
                            done = true;
                            q = strstr( p, "<a " );
                            if ( q ) {
                                r = q + 3;
                                s = strstr( r, "href=\"http" );
                                if ( s ) {
                                    r = s + 6; // 6 = strlen("href=\"");
                                    s = strchr( r, '"' );
                                    if ( s ) {
                                        t = strstr( s + 1, "</a>" );
                                        if ( t ) {
                                            t += 4;
                                            strncpy( q, r, s - r );
                                            strcpy( q + (s - r), t );

                                            p = q + (s - r);
                                            done = false;
                                        }
                                    }
                                }
                                else {
                                    s = strstr( r, "</a>" );
                                    if ( s ) {
                                        p = s + 4;
                                        done = false;
                                    }
                                }
                            }
                        } while ( !done && !(*p) );

                        /* html タグの除去 */
                        p = temp;
                        while ( ( q = strchr( p, '<' ) ) != NULL ) {
                            if ( (r = strchr(q + 1, '>')) != NULL )
                                strcpy( q, r + 1 );
                            else {
                                *q = NUL;
                                break;
                            }
                        }
                    }

                    strcpy( sp->orig_text,
                            replaceEntityStrings( temp, CHARSET_UTF8 ) );
                    strcpy( temp, ExpandTinyURL( sp->orig_text ) );
                    strcpy( sp->text, any2sjis( temp ) );
                }
            }
        }

        delete [] response;
    }

    MakeMessageForScreen( message, sp );
    strcpy( sp->user.lastStatus, sp->text );
    MakeMessageForLogging( sp );
}

CString CTwitter::GetIdFromJSON( const char *p, const char *terminator )
{
    // Twitter の status ID が singed long で扱える範囲を超えてしまった
    // (2009年6月13日)ための対策として、CService::GetIdFromJSON() を呼ぶ
    // のをやめて、新たに CTwitter::GetIdFromJSON() を用意した
    char    statusID[MAX_KEYLENGTH * 2 + 2];
    CString id;

    // "id"
    statusID[0] = NUL;
    char    *q = strchr( p, ':' );
    if ( q && (q < terminator) ) {
        q++;

        char    *r = strchr( q, ',' );
        if ( r && (r < terminator) ) {
            strncpy( statusID, q, r - q );
            statusID[r - q] = NUL;
        }
    }

    id = statusID;

    return ( id );
}

CString CTwitter::GetStatusID(
                        const char *p,
                        const char *terminator
                    )
{
    const char  *q  = p;
    const char  *r1 = strstr( q, "\"user\"" );
    const char  *r2 = strstr( q, "\"id\"" );

    if ( r1 && r2 && (r1 < terminator) && (r2 < terminator) ) {
        if ( r2 > r1 ) {
            r1 = strstr( r2 + 4 , "\"id\"" );
            if ( r1 && (r1 < terminator) )
                q = r1;
        }
    }

    CString s = GetIdFromJSON( q, terminator );
    return ( s );
}

char    *
CTwitter::GetSource(
                const char *q,
                const char *s,
                char       *sourceURL
            )
{
    Thread static char  temp[BUFSIZ * 2];
    GetStringFromJSON( temp, BUFSIZ * 2, "\"source\"", q, s );

    char    *p = strstr( temp, "<a href=\"" );
    if ( p ) {
        char    *q;

        p += 9;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( sourceURL, p, q - p );
            sourceURL[q - p] = NUL;

            p = strchr( q + 1, '>' );
            if ( p ) {
                p++;
                q = strstr( p, "</a>" );
                if ( q ) {
                    *q = NUL;
                    strcpy( temp, p );
                }
            }
        }
        else
            sourceURL[0] = NUL;
    }
    else
        sourceURL[0] = NUL;

    return ( temp );
}

bool
CTwitter::GetTruncated(
                const char *q,
                const char *s
            )
{
    bool    ret = false;
    Thread static char  temp[BUFSIZ * 2];
    GetStringFromJSON( temp, BUFSIZ * 2, "\"truncated\"", q, s );

    char    *p = strstr( temp, "true" );
    if ( p )
        ret = true;
    else {
        p = strstr( temp, "false" );
        if ( p )
            ret = false;
    }

    return ( ret );
}

void
CTwitter::MakeMessageForScreen(
            CString        &message,
            TWITTER_STATUS *sp )
{
    message += sp->user.screenName;
    message += _T(": ");
    message += EscapeQuote(sp->text);

    message += _T(" ☆");
    if ( m_useTwitStar )
        message += _T(" / ★");
    message += _T("[ID: ");
    message += sp->id;
    message += _T("]");

    if ( sp->source[0] ) {
        message += _T(" (from ");
        if ( sp->sourceURL[0] )
            message += _T("*");
        message += sp->source;
        if ( sp->sourceURL[0] )
            message += _T("*");
        message += _T(")");
    }

    message += _T("\r\n");
}

void
CTwitter::MakeMessageForLogging( TWITTER_STATUS *sp )
{
    if ( !m_log )
        m_log = new TWITTER_LOG[MAX_NUMOFSTATUS + 1];

    if ( m_log && (m_numOfLogs < MAX_NUMOFSTATUS) ) {
        sprintf( m_log[m_numOfLogs].orig_text,
                 "%s [ID: %s]",
                 sp->orig_text, sp->id );
        if ( sp->source[0] ) {
            sprintf( m_log[m_numOfLogs].orig_text +
                        strlen(m_log[m_numOfLogs].orig_text),
                     " (from %s)",
                     sp->source );
        }

        strcpy( m_log[m_numOfLogs].orig_userName, sp->user.orig_userName );

        m_log[m_numOfLogs].createdAt = sp->createdAt.GetTime();

        struct tm   ttmm;
     // struct tm   *tm = sp->createdAt.GetGmtTm( &ttmm );
        struct tm   *tm = sp->createdAt.GetLocalTm( &ttmm );

        m_log[m_numOfLogs].createdAt_yyyy = tm->tm_year + 1900;
        m_log[m_numOfLogs].createdAt_mm   = tm->tm_mon + 1;
        m_log[m_numOfLogs].createdAt_dd   = tm->tm_mday;
        m_log[m_numOfLogs].createdAt_HH   = tm->tm_hour;
        m_log[m_numOfLogs].createdAt_MM   = tm->tm_min;
        m_log[m_numOfLogs].createdAt_SS   = tm->tm_sec;
        m_numOfLogs++;
    }
}


char    *
CTwitter::CutInReplyTo( char *s )
{
    const char  *inReplyTo = "\"in_reply_to\":{";
    int         len = strlen( inReplyTo );
    int         cnt = 0;
    char        *t, *u;

    do {
        t = strstr( s, inReplyTo );
        if ( !t )
            break;

        u   = t + len;
        cnt = 1;

        bool quote = false;
        while ( *u ) {
            if ( quote ) {
                if ( *u == '\\' )
                    u++;
                else if ( *u == '"' )
                    quote = false;
                u++;
                continue;
            }

            if ( *u == '\\' )
                u++;
            else if ( *u == '"' )
                quote = true;
            else if ( *u == '{' )
                cnt++;
            else if ( *u == '}' ) {
                cnt--;
                if ( cnt == 0 ) {
                    u++;
                    if ( *u == ',' )
                        u++;
                    break;
                }
            }

            u++;
        }

        strcpy( t, u );
    } while ( t );

    return ( s );
}

bool
CTwitter::GetToken(
        const char *response,
        CString    &oauthToken,
        CString    &oauthTokenSecret
    )
{
    CString screenName = _T("");
    return ( GetToken( response, oauthToken, oauthTokenSecret, screenName ) );
}

bool
CTwitter::GetToken(
        const char *response,
        CString    &oauthToken,
        CString    &oauthTokenSecret,
        CString    &screenName
    )
{
    bool    ret = false;

    if ( response && *response ) {
        char    oauth_token[BUFSIZ];
        char    oauth_token_secret[BUFSIZ];
        char    screen_name[BUFSIZ];

        char    *p = strstr( response, "oauth_token=" );
        if ( p ) {
            p += 12;

            char    *q = strchr( p, '&' );
            if ( q ) {
                strncpy( oauth_token, p, q - p );
                oauth_token[q - p] = NUL;
            }
            else {
                strcpy( oauth_token, p );
            }

            oauthToken = oauth_token;
        }

        p = strstr( response, "oauth_token_secret=" );
        if ( p ) {
            p += 19;

            char    *q = strchr( p, '&' );
            if ( q ) {
                strncpy( oauth_token_secret, p, q - p );
                oauth_token_secret[q - p] = NUL;
            }
            else {
                strcpy( oauth_token_secret, p );
            }

            oauthTokenSecret = oauth_token_secret;
        }

        p = strstr( response, "screen_name=" );
        if ( p ) {
            p += 12;

            char    *q = strchr( p, '&' );
            if ( q ) {
                strncpy( screen_name, p, q - p );
                screen_name[q - p] = NUL;
            }
            else {
                strcpy( screen_name, p );
            }

            screenName = screen_name;
        }

        if ( (oauthToken.GetLength()       > 0) &&
             (oauthTokenSecret.GetLength() > 0)    )
            ret = true;
    }

    return ( ret );
}


bool
CTwitter::GetRequestToken(
        const char *consumerKey,
        const char *consumerSecret,
        CString    &oauthToken,
        CString    &oauthTokenSecret
    )
{
    bool    ret = false;

    time_t  t  = time( NULL );
    size_t  sz = MAX_CONTENT_SIZE * 16;
    char    base[MAX_CONTENT_SIZE];
    char    param[MAX_CONTENT_SIZE];
    char    nonce[MAX_KEYLENGTH];
    char    key[MAX_KEYLENGTH * 2];

    char    *request  = new char[sz];
    char    *response = new char[sz];

    CString targetURL = _T("");
    targetURL.LoadString(IDS_URL_TWITTER_REQUEST_TOKEN);

    strcpy( nonce, getNonce(NULL) );

    sprintf( key, "%s&", encodeURLi( consumerSecret, FALSE ) );

    sprintf( base,
             "GET&"
             "%s&",
             encodeURLi( targetURL, FALSE ) );
    sprintf( param,
             "oauth_consumer_key=%s&"
             "oauth_nonce=%s&"
             "oauth_signature_method=HMAC-SHA1&"
             "oauth_timestamp=%ld&"
             "oauth_version=1.0",
             consumerKey,
             nonce,
             t );

    MakeOAuthRequest( targetURL, request, key, base, param );

    SetUserAgent();
    setUpReceiveBuffer( response, sz );
    _http_getBASIC( request, NULL, NULL, response, NULL, NULL );
    ret = GetToken( response, oauthToken, oauthTokenSecret );

    delete [] response;
    delete [] request;

    return ( ret );
}

bool
CTwitter::GetAccessToken(
        const char *consumerKey,
        const char *consumerSecret,
        CString    &oauthToken,
        CString    &oauthTokenSecret,
        CString    &screenName
    )
{
    bool    ret = false;

    if ( !consumerKey    || !(*consumerKey)    ||
         !consumerSecret || !(*consumerSecret)    )
        return ( ret );

    // request token 取得
    CString _oauthToken       = _T("");
    CString _oauthTokenSecret = _T("");
    if ( !GetRequestToken( consumerKey, consumerSecret,
                           _oauthToken, _oauthTokenSecret ) )
        return ( ret );        

    // ブラウザ起動 -- ユーザにアクセス許可を求める
    CString targetURL = _T("");
    targetURL.LoadString(IDS_URL_TWITTER_AUTHORIZE);

    char    url[MAX_URLLENGTH];
    sprintf( url, "%s?oauth_token=%s", targetURL, _oauthToken );
    ShellExecute( NULL, "open", url, NULL, NULL, SW_SHOWNORMAL );

    // ユーザの許可待ち
#ifdef  BEFORE_20090610
    // OAuth 1.0
    int r = MessageBox( NULL,
            "Chirrup が Twitter にアクセスする許可を与えてください。\r\n"
            "許可を与え終わったら、OK ボタンを押してください。\r\n"
            "許可を与えたくない場合は キャンセル ボタンを押してください。  ",
            "Twitter へのアクセス許可", MB_OKCANCEL|MB_ICONINFORMATION );
    if ( r != IDOK ) {
        MessageBox( NULL,
                    "Twitter へのアクセスを中止します。  ",
                    "アクセス中止", MB_OK|MB_ICONWARNING );
        return ( ret );
    }
#else   /* !BEFORE_20090610 */
    // OAuth 1.0a
    InputPinDialog  dlg;

    int r = dlg.DoModal();
    if ( (r != IDOK) || (dlg.m_pin.GetLength() < 6) )
        return ( ret );
#endif  /* !BEFORE_20090610 */

    // access token 取得
    time_t  t  = time( NULL );
    size_t  sz = MAX_CONTENT_SIZE * 16;
    char    base[MAX_CONTENT_SIZE];
    char    param[MAX_CONTENT_SIZE];
    char    nonce[MAX_KEYLENGTH];
    char    key[MAX_KEYLENGTH * 2];

    char    *request  = new char[sz];
    char    *response = new char[sz];

    targetURL = _T("");
    targetURL.LoadString(IDS_URL_TWITTER_ACCESS_TOKEN);

    strcpy( nonce, getNonce(NULL) );

    sprintf( key,
             "%s&",
             encodeURLi( consumerSecret, FALSE ) );
    sprintf( key + strlen(key),
             "%s",
             encodeURLi( _oauthTokenSecret, FALSE ) );

    sprintf( base,
             "GET&"
             "%s&",
             encodeURLi( targetURL, FALSE ) );

#ifdef  BEFORE_20090610
    // OAuth 1.0
    sprintf( param,
             "oauth_consumer_key=%s&"
             "oauth_nonce=%s&"
             "oauth_signature_method=HMAC-SHA1&"
             "oauth_timestamp=%ld&"
             "oauth_token=%s&"
             "oauth_version=1.0",
             consumerKey,
             nonce,
             t,
             _oauthToken );
#else   /* !BEFORE_20090610 */
    // OAuth 1.0a
    sprintf( param,
             "oauth_consumer_key=%s&"
             "oauth_nonce=%s&"
             "oauth_signature_method=HMAC-SHA1&"
             "oauth_timestamp=%ld&"
             "oauth_token=%s&"
             "oauth_verifier=%s&"
             "oauth_version=1.0",
             consumerKey,
             nonce,
             t,
             _oauthToken,
             (const char *)dlg.m_pin );
#endif  /* !BEFORE_20090610 */

    MakeOAuthRequest( targetURL, request, key, base, param );

    SetUserAgent();
    setUpReceiveBuffer( response, sz );
    _http_getBASIC( request, NULL, NULL, response, NULL, NULL );
    ret = GetToken( response, oauthToken, oauthTokenSecret, screenName );

    if ( ret ) {
        m_oauthToken       = oauthToken;
        m_oauthTokenSecret = oauthTokenSecret;
    }

    delete [] response;
    delete [] request;

    return ( ret );
}


void
CTwitter::MakeOAuthBase(
        const char *url,
        const char *method,
        char       *key,
        char       *base,
        char       *param
    )
{
    CChirrupApp *ap = (CChirrupApp *)AfxGetApp();
    time_t      t   = time( NULL );
    char        nonce[MAX_KEYLENGTH];

    strcpy( nonce, getNonce(NULL) );

    sprintf( key,
             "%s&",
             encodeURLi( ap->m_tcSecret, FALSE ) );
    sprintf( key + strlen(key),
             "%s",
             encodeURLi( m_oauthTokenSecret, FALSE ) );

    sprintf( base,
             "%s&"
             "%s&",
             method,
             encodeURLi( url, FALSE ) );

    sprintf( param[0] ? param + strlen(param) : param,
             "oauth_consumer_key=%s&"
             "oauth_nonce=%s&"
             "oauth_signature_method=HMAC-SHA1&"
             "oauth_timestamp=%ld&"
             "oauth_token=%s&"
             "oauth_version=1.0",
             ap->m_tcKey,
             nonce,
             t,
             m_oauthToken );
}


void
CTwitter::MakeOAuthRequest(
        const char *url,
        char       *request,
        char       *key,
        char       *base,
        char       *param
    )
{
    char    digest[SHA1HashSize * 4];

    sprintf( base + strlen(base),
             "%s",
             encodeURLi(param, FALSE) );

    memset( digest, 0x00, SHA1HashSize );
    hmac_sha1( (unsigned char *)base, strlen(base),
               (unsigned char *)key, strlen(key),
               digest );
    strcpy( digest, base64( (unsigned char *)digest, SHA1HashSize ) );

    sprintf( request,
             "%s?"
             "%s&"
             "oauth_signature=%s",
             url,
             param,
             encodeURLi( digest, TRUE ) );
}


bool
CTwitter::CheckOAuthResult( const char *response )
{
    bool    ret = true;
    unsigned short responseCode = getStatusCode();

    if ( (responseCode == 401) ||
         strstr( response, "Invalid OAuth Request" ) ||
         strstr( response, "Failed to validate oauth signature or token" ) ) {
        MessageBox( NULL,
                    "OAuth 認証に失敗しました。\r\n"
                    "このエラーが頻繁に出るようであれば、"
                    "アクセストークンを取得し直してください。  ",
                    "OAuth 認証エラー",
                    MB_OK|MB_ICONERROR );
        ret = false;
    }

    return ( ret );
}
