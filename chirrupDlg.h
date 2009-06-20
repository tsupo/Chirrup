/*
 * chirrupDlg.h  : Twitter クライアント chirrup
 *      メインダイアログ ヘッダーファイル
 *          written by H.Tsujimura  4 Apr 2007
 *
 *      Copyright (c) 2007, 2008, 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/chirrupDlg.h $
 * 
 * 2     09/05/31 20:42 tsupo
 * 1.142版
 * 
 * 111   09/05/29 19:22 Tsujimura543
 * 同一アカウントで複数 tumbleblog を開設している場合の投稿先
 * tumbleblog を指定しての投稿を可能にした
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 110   09/04/28 20:52 Tsujimura543
 * タイムアウト取得処理が規定時間内に終わらない場合の処理を変更
 * (スレッド強制終了方式ではなく、イベント通知方式を採用)
 * 
 * 109   09/04/22 21:11 Tsujimura543
 * 「設定」ダイアログからもFlickr認証のアクセストークン(frob)を取得できる
 * ようにした
 * 
 * 108   09/04/16 17:09 Tsujimura543
 * 「設定」ダイアログ起動中は、タイマ割り込み発生による「更新」処理
 * (タイムラインの取得)を実行しないようにした
 * 
 * 107   09/04/15 1:17 Tsujimura543
 * Jaiuku の OAuth 対応準備
 * 
 * 106   09/03/31 21:27 Tsujimura543
 * Twitter の OAuth 対応準備 その5
 * 
 * 105   09/03/30 22:37 Tsujimura543
 * Twitter の OAuth 対応準備 その2
 * 
 * 104   09/03/09 21:43 Tsujimura543
 * タイムライン取得スレッド監視処理に「タイムライン取得スレッドで
 * 無限ループ発生時対策」を入れてみた
 * 
 * 103   08/12/22 20:54 Tsujimura543
 * 「いめったー」対応
 * 
 * 102   08/08/22 18:42 Tsujimura543
 * 「はてなハイク」対応
 * 
 * 101   08/08/01 2:40 Tsujimura543
 * (1) Wassr への画像の投稿に対応
 * (2) 「チャンネル」対応準備
 * 
 * 100   08/07/16 4:13 Tsujimura543
 * 「同時投稿対象」の設定を「設定」ダイアログでも設定できるようにした
 * 
 * 99    08/07/16 1:20 Tsujimura543
 * タスクトレイ常駐機能を実装
 * 
 * 98    08/07/14 14:59 Tsujimura543
 * Twitter の「API制限情報取得API」を呼ぶ回数、タイミングを調整し直した
 * 
 * 97    08/03/26 22:15 Tsujimura543
 * Firefox からの画像ドラッグ対応 (いったんイベントハンドラから抜ける)
 * 
 * 96    08/02/27 20:16 Tsujimura543
 * 「ついったー部SNS支局」のアイコンを追加
 * 
 * 95    08/01/31 18:50 Tsujimura543
 * ユーザアイコン(プロフィールアイコン)の更新機能を on/off できるように
 * してみた
 * 
 * 94    08/01/28 18:40 Tsujimura543
 * ウィンドウサイズを保存、復元できるようにしてみた
 * 
 * 93    08/01/24 15:29 Tsujimura543
 * Gyazo, Flickr, はてなフォトライフの各アイコンを追加
 * 
 * 92    08/01/24 14:55 Tsujimura543
 * CUploadImageDialog の画像同時投稿対象先指定機能に対応
 * 
 * 91    08/01/19 0:33 Tsujimura543
 * はてなフォトライフ対応準備
 * 
 * 90    08/01/17 19:01 Tsujimura543
 * メインダイアログを従来よりもさらに(縦方向に)小さくできるようにしてみた
 * 
 * 89    08/01/09 22:27 Tsujimura543
 * Flickr 対応作業、とりあえず終了 (動作確認完了)
 * 
 * 88    08/01/09 17:10 Tsujimura543
 * Flickr 対応準備 その2
 * 
 * 87    08/01/08 21:07 Tsujimura543
 * flickr 対応準備
 * 
 * 86    07/12/19 16:34 Tsujimura543
 * Tumblr と Gyazo にアップロードしたファイルの URL を記録する機能を
 * 追加
 * 
 * 85    07/12/19 16:12 Tsujimura543
 * Tumblr と Gyazo にアップロードしたファイルの URL を記録する機能を
 * 追加するためのプロパティを追加
 * 
 * 84    07/12/15 6:29 Tsujimura543
 * SwitchCapture() を追加
 * 
 * 83    07/12/15 5:15 Tsujimura543
 * キャプチャー機能実装完了
 * 
 * 82    07/12/15 2:54 Tsujimura543
 * キャプチャー機能、試験実装 (まだ、試行錯誤中)
 * 
 * 81    07/12/14 16:44 Tsujimura543
 * DeleteHtmlTags() を追加
 * 
 * 80    07/12/13 22:26 Tsujimura543
 * 画像のアップロード処理周りを変更(はてなFotolife対応準備、bmpファイル対
 * 応)
 * 
 * 79    07/12/13 18:40 Tsujimura543
 * proxy関連のプロトタイプ宣言を proxy.h として分離独立させた
 * 
 * 78    07/12/13 18:04 Tsujimura543
 * [暫定] WM_HOTKEY を利用してホットキー(ショートカットキー)を組み込
 *        んでみるテスト
 *   → 子ウィンドウにも引き継がれてしまうため、このままでは使えない
 * 
 * 77    07/12/10 22:39 Tsujimura543
 * スレッド間通信用構造体の定義を paramForThread.h として分離独立させた
 * 
 * 76    07/12/10 16:39 Tsujimura543
 * Gyazo への投稿処理関連を fix
 * 
 * 75    07/12/06 4:08 Tsujimura543
 * tumblr への画像ファイルアップロード処理を別スレッド化した
 * 
 * 74    07/12/06 1:59 Tsujimura543
 * tumblr への画像の投稿に対応
 * 
 * 73    07/11/26 21:44 Tsujimura543
 * 「ふぁぼったー」と tumblr のアイコンを追加
 * 
 * 72    07/11/26 20:23 Tsujimura543
 * proxy設定関連、異常系強化
 * 
 * 71    07/11/26 18:04 Tsujimura543
 * proxy設定関連移行作業、完了
 * 
 * 70    07/11/26 18:03 Tsujimura543
 * OnSettingProxy() → DoSettingProxy() に移行
 * 
 * 69    07/11/26 17:57 Tsujimura543
 * CProxyInfoDialog を廃止し、CSettingProxy に移行
 * 
 * 68    07/11/07 3:39 Tsujimura543
 * 見ている発言を 引用して Tumblr へ投稿する機能を作成
 * 
 * 67    07/09/27 19:49 Tsujimura543
 * ShowFavorites() を追加
 * 
 * 66    07/09/14 17:52 Tsujimura543
 * ステータスバーにメッセージを表示できるようにした
 * 
 * 65    07/09/12 21:38 Tsujimura543
 * SetAddrOnMonologue() を導入、リファクタリングを実施
 * 
 * 64    07/09/06 19:42 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 63    07/08/28 17:04 Tsujimura543
 * ソースコード中のコメントを整理
 * 
 * 62    07/08/28 17:02 Tsujimura543
 * (1) DisplayContextMenuForServices() と DisplayContextMenuForFriends()
 *     を追加し、OnContextMenu() を整理
 * (2) SetStaticEdge() を追加
 * 
 * 61    07/08/28 0:37 Tsujimura543
 * (1) ReduceExtra() を導入
 * (2) 少しだけソース整理
 * 
 * 60    07/08/25 0:16 Tsujimura543
 * 「ついすた」に対応 (設定関係)
 * 
 * 59    07/08/13 18:25 Tsujimura543
 * DisplayProfImages() 内から呼び出すアイコン描画処理を別スレッド化できる
 * ようにしてみた
 * 
 * 58    07/08/13 12:06 Tsujimura543
 * 「Powered by サービス名」の表示をするようにした
 * 
 * 57    07/07/03 18:35 Tsujimura543
 * Haru.fm のアイコンを設置
 * 
 * 56    07/06/27 18:13 Tsujimura543
 * haru.fm に対応
 * 
 * 55    07/06/25 21:12 Tsujimura543
 * インクルードファイルのインクルード順序を変更
 * 
 * 54    07/06/23 0:40 Tsujimura543
 * SwitchTimelineFacilities() を導入
 * 
 * 53    07/06/22 23:06 Tsujimura543
 * UpdateSingle() [引数なし] を追加
 * 
 * 52    07/06/22 19:19 Tsujimura543
 * 「発言」投稿成功時、当該サービスのみを対象に timeline を取得するよう
 * にしてみた
 * 
 * 51    07/06/21 14:43 Tsujimura543
 * OnSetfocusMonologue() 相当の処理を RichEditEx.cpp に移動。
 * OnSetfocusMonologue() は削除。
 * 
 * 50    07/06/20 15:48 Tsujimura543
 * InitTimelineInfo() を廃止
 * 
 * 49    07/06/20 14:07 Tsujimura543
 * Timelog 対応版
 * 
 * 48    07/06/20 5:19 Tsujimura543
 * (1) Twitter に CTwitterManager を適用
 * (2) ユーザアイコンの右クリックメニューに「関連Webページを表示」を追加
 * 
 * 47    07/06/20 1:56 Tsujimura543
 * Jaiku に CJaikuManager を適用
 * 
 * 46    07/06/20 0:31 Tsujimura543
 * Wassr にも CManager を適用
 * 
 * 45    07/06/19 23:12 Tsujimura543
 * (1) CManeger を導入し、とりあえず「もごもご」に適用し動作確認をしてみた
 * (2) CService 導入に伴う修正を実施
 * 
 * 44    07/06/15 0:07 Tsujimura543
 * timeline の切り替え時、必要に応じて、「もごもご」のスクリーン名
 * 取得処理を呼び出すようにした
 * 
 * 43    07/06/14 21:12 Tsujimura543
 * 「もごもご」に対応
 * 
 * 42    07/06/14 17:55 Tsujimura543
 * Wassr に対応
 * 
 * 41    07/06/13 19:18 Tsujimura543
 * Twitter の Replies の閲覧、ログ出力に対応
 * 
 * 40    07/06/13 1:27 Tsujimura543
 * (1) ダイアログに表示するバージョン番号情報をリソースファイルから
 *     拾ってくるようにした
 * (2) スクリーン名の表示を Twitter 固定から、Twitter/Jaiku切り替え
 *     表示できるようにした
 * (3) 設定ファイルがまだないときの起動時処理を整理、調整
 * 
 * 39    07/06/13 0:12 Tsujimura543
 * (1) TIMELINE_INFO 関連 fix
 * (2) 初期設定ファイル読み書きを新しいログファイル管理仕様に対応させた
 * 
 * 38    07/06/11 19:58 Tsujimura543
 * Twitter と Jaiku への同時投稿をサポート
 * 
 * 37    07/06/11 18:39 Tsujimura543
 * Twitter の user_timeline の閲覧をサポート
 * 
 * 36    07/06/07 14:12 Tsujimura543
 * コメントを修正
 * 
 * 35    07/06/07 14:11 Tsujimura543
 * 設定ファイルやキャッシュファイルを置くディレクトリのデフォルト値を
 * 「カレントディレクトリ」直下から「chirrup起動時点のカレントディレク
 * トリ」直下に変更
 * 
 * 34    07/06/07 1:44 Tsujimura543
 * friends_timeline 以外のタイムラインもログに書き出せるようにした
 * 
 * 33    07/06/06 22:21 Tsujimura543
 * ログファイルの書き出し機能サポートに伴う各種修正を実施
 * 
 * 32    07/06/06 16:27 Tsujimura543
 * 発言投稿処理も別スレッド化してみた
 * 
 * 31    07/06/05 20:32 Tsujimura543
 * Twitter/Jaiku の timeline の取得を完全に別スレッド化してみた
 * 
 * 30    07/06/05 17:33 Tsujimura543
 * Jaiku アイコンを追加
 * 
 * 29    07/06/05 17:06 Tsujimura543
 * RURL 機能廃止、ダイアログデザイン変更
 * 
 * 28    07/06/05 14:44 Tsujimura543
 * PostMonologue() 回りを改修、多少なりとも負荷を減らすようにしてみた
 * 
 * 27    07/06/04 21:11 Tsujimura543
 * friend の add と remove を実装 (for Twitter)
 * 
 * 26    07/05/29 12:48 Tsujimura543
 * Jaiku の friends_timeline 対応(途中)
 * 
 * 25    07/05/29 6:39 Tsujimura543
 * Twitter のツンデレ状態判定機能(簡易版)を実装
 * 
 * 24    07/05/29 5:13 Tsujimura543
 * Jaiku の user_timeline の閲覧に対応
 * 
 * 23    07/05/29 3:56 Tsujimura543
 * Jaiku (の public_timeline の閲覧) に対応
 * 
 * 22    07/05/25 20:15 Tsujimura543
 * CTwitterTimeline クラス関連の記述を別のファイルに分離、独立させた
 * 
 * 21    07/05/25 17:51 Tsujimura543
 * OnSelchangeComboTimelineType() を改良、瞬時に timeline の切り替えが
 * できるようにした
 * 
 * 20    07/05/23 22:25 Tsujimura543
 * friends_timeline と public_timeline の表示切替機能を追加
 * 
 * 19    07/05/11 22:40 Tsujimura543
 * 発言入力中に「更新」+「閲覧中のWebページ投稿」があった場合でも、
 * 入力中の発言内容が消えないように対処
 * 
 * 18    07/05/11 21:29 Tsujimura543
 * ブラウザで閲覧中の URL を Twitter に送信するとき、その Web ページの
 * タイトルも取得して送信するようにした
 * 
 * 17    07/04/28 0:23 Tsujimura543
 * OnSetfocusMonologue() を追加
 * 
 * 16    07/04/27 22:28 Tsujimura543
 * プロクシ関連の設定を保持するメンバーを CChirrupApp に移動
 * 
 * 15    07/04/27 19:39 Tsujimura543
 * Twitter API 関連の処理を Twitter.cpp に集約したのに伴う修正を実施
 * 
 * 14    07/04/26 20:21 Tsujimura543
 * URL をクリッカブルにしてみた
 * 
 * 13    07/04/26 0:22 Tsujimura543
 * ダイレクトメッセージ閲覧機能を実装
 * 
 * 12    07/04/25 20:39 Tsujimura543
 * メインダイアログを縦方向にリサイズできるようにしてみた
 * 
 * 11    07/04/24 23:49 Tsujimura543
 * ブラウザで閲覧中の URL を送信する機能を実装
 * 
 * 10    07/04/14 3:01 Tsujimura543
 * proxy関連の処理を再修正
 * 
 * 9     07/04/14 2:05 Tsujimura543
 * 右クリックメニューを追加
 * 
 * 8     07/04/13 23:19 Tsujimura543
 * friends 画像表示機能を付けた (まだ、表示のみ)
 * 
 * 7     07/04/09 21:07 Tsujimura543
 * 行数が MAX_NUMOFSTATUS を超えるところで落ちてしまう不具合に対処
 * 
 * 6     07/04/07 0:51 Tsujimura543
 * コードを整理
 * 
 * 5     07/04/07 0:45 Tsujimura543
 * リターンキーを押下すると、chirrup が終了してしまっていたのを、終了しな
 * いようにした(リターンキーの空打ちは無視するようにした)
 * 
 * 4     07/04/06 23:42 Tsujimura543
 * (1) Twitter に送信する http リクエストのヘッダに X-Twitter-Client: 等を
 *     付加するようにした (クライアント情報XML は
 *       http://watcher.moe-nifty.com/memo/files/chirrup.xml
 *     に設置)
 * (2) プロキシサーバ情報を手動で設定できるようにした
 * (3) ボタンをいっぱい付けてみた
 * 
 * 3     07/04/05 3:03 Tsujimura543
 * 暫定的に使っていたマジックナンバーをちゃんとした値にする
 * 
 * 2     07/04/05 2:51 Tsujimura543
 * 更新周期を変更できるようにした
 * 
 * 1     07/04/05 2:06 Tsujimura543
 * 最初の版
 */

#if !defined(AFX_CHIRRUPDLG_H__5843E218_092A_47EB_AA1F_F176B490916A__INCLUDED_)
#define AFX_CHIRRUPDLG_H__5843E218_092A_47EB_AA1F_F176B490916A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CImage.h"
#include "twitterTimeline.h"
#include "RichEditEx.h"
#include "CManager.h"
#include "CTwitterManager.h"
#include "CJaikuManager.h"
#include "paramForThread.h"
#include "DropTarget.h"

#define TEMPFILE_BASE   _T("chp")

/////////////////////////////////////////////////////////////////////////////
// CChirrupDlg ダイアログ

class CChirrupDlg : public CDialog
{
// 構築
public:
	CChirrupDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ
    ~CChirrupDlg();

    CChirrupDropTarget  m_dropTarget;   //  OLE DnD のドロップターゲット

    // for Thread of updating timeline
    CWinThread      *m_updateThread;
    volatile bool   m_updateThread_Fired;
    CTime       m_startTime_updateThread;
    void        ExecuteUpdate( CManager *p );
    void        ExecuteUpdate( CString timelineType );
#       define      ID_THREAD_UPDATE_TWITTER    0xCAFEBABE
#       define      MS_THREAD_UPDATE_TWITTER    (MS_UPDATE_TWITTER / 20)

    // for Thread of posting monologue
    CWinThread  *m_postThread;
    bool        ExecutePost( CString monologue, CString timelineType );
#       define      ID_THREAD_POST_TWITTER      0xBEC0FFEE
#       define      MS_THREAD_POST_TWITTER      (MS_UPDATE_TWITTER / 20)

    // for Thread of uploading image file
    CWinThread  *m_uploadImageThread;
    bool        ExecuteUploadImage( CString       filename,
                                    size_t        filesize,
                                    CHIRRUP_FTYPE filetype,
                                    CString       caption,
                                    bool          onGyazo,
                                    bool          onFlickr,
                                    bool          onTumblr,
                                    bool          onHatenaFotolife,
                                    bool          onWassr );
    bool        ExecuteUploadImageWithURL( CString url,
                                           CString caption );
#       define      ID_THREAD_UPLAOD_IMAGE      0xBEEFCACE
#       define      MS_THREAD_UPLAOD_IMAGE      (MS_UPDATE_TWITTER / 20)

#       define      ID_WAITED_UPLAOD_IMAGE      0xDEADCAFE
#       define      MS_WAITED_UPLAOD_IMAGE      (MS_UPDATE_TWITTER / 20)

    void    EnterCriticalSection()
    {
        ::EnterCriticalSection( &m_cs_chirrup );
    }

    void    LeaveCriticalSection()
    {
        ::LeaveCriticalSection( &m_cs_chirrup );
    }

    void    SetTwitter( CString username,
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
    void    GetTwitter( CString &username,
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

    void    SetJaiku( CString username,
                      CString personalKey,
                      CString oauthToken,
                      CString oauthTokenSecret,
                      BOOL useOAuth,
                      BOOL useBASIC,
                      BOOL checkMultiPost,
                      TIMELINE_INFO sFriendsTimeline,
                      TIMELINE_INFO sPublicTimeline,
                      TIMELINE_INFO sUserTimeline );
    void    GetJaiku( CString &username,
                      CString &personalKey,
                      CString &oauthToken,
                      CString &oauthTokenSecret,
                      BOOL &useOAuth,
                      BOOL &useBASIC,
                      BOOL &checkMultiPost,
                      TIMELINE_INFO &sFriendsTimeline,
                      TIMELINE_INFO &sPublicTimeline,
                      TIMELINE_INFO &sUserTimeline );

    void    SetWassr( CString username,
                      CString password,
                      BOOL checkMultiPost,
                      BOOL useWassrForUpload,
                      BOOL writeLogfileForUpload,
                      CString logFilenameForUpload,
                      TIMELINE_INFO sFriendsTimeline,
                      TIMELINE_INFO sPublicTimeline,
                      TIMELINE_INFO sUserTimeline );
    void    GetWassr( CString &username,
                      CString &password,
                      BOOL &checkMultiPost,
                      BOOL &useWassrForUpload,
                      BOOL &writeLogfileForUpload,
                      CString &logFilenameForUpload,
                      TIMELINE_INFO &sFriendsTimeline,
                      TIMELINE_INFO &sPublicTimeline,
                      TIMELINE_INFO &sUserTimeline );

    void    SetMogo2( CString username,
                      CString password,
                      BOOL checkMultiPost,
                      TIMELINE_INFO sFriendsTimeline,
                      TIMELINE_INFO sPublicTimeline,
                      TIMELINE_INFO sUserTimeline );
    void    GetMogo2( CString &username,
                      CString &password,
                      BOOL &checkMultiPost,
                      TIMELINE_INFO &sFriendsTimeline,
                      TIMELINE_INFO &sPublicTimeline,
                      TIMELINE_INFO &sUserTimeline );

    void    SetTimelog( CString username,
                        CString password,
                        BOOL checkMultiPost,
                        TIMELINE_INFO sFriendsTimeline,
                        TIMELINE_INFO sPublicTimeline,
                        TIMELINE_INFO sUserTimeline );
    void    GetTimelog( CString &username,
                        CString &password,
                        BOOL &checkMultiPost,
                        TIMELINE_INFO &sFriendsTimeline,
                        TIMELINE_INFO &sPublicTimeline,
                        TIMELINE_INFO &sUserTimeline );

    void    SetHaruFm( CString username,
                       CString password,
                       BOOL checkMultiPost,
                       TIMELINE_INFO sFriendsTimeline,
                       TIMELINE_INFO sPublicTimeline,
                       TIMELINE_INFO sUserTimeline );
    void    GetHaruFm( CString &username,
                       CString &password,
                       BOOL &checkMultiPost,
                       TIMELINE_INFO &sFriendsTimeline,
                       TIMELINE_INFO &sPublicTimeline,
                       TIMELINE_INFO &sUserTimeline );

    void    SetHatenaHaiku( CString username,
                            CString password,
                            BOOL checkMultiPost,
                            TIMELINE_INFO sFriendsTimeline,
                            TIMELINE_INFO sPublicTimeline,
                            TIMELINE_INFO sUserTimeline );
    void    GetHatenaHaiku( CString &username,
                            CString &password,
                            BOOL &checkMultiPost,
                            TIMELINE_INFO &sFriendsTimeline,
                            TIMELINE_INFO &sPublicTimeline,
                            TIMELINE_INFO &sUserTimeline );

    void    SetHatena( CString username,
                       CString password,
                       BOOL    useTwitStar,
                       BOOL    useHatenaFotolife,
                       BOOL    writeLogFile,
                       CString logFilename );
    void    GetHatena( CString &username,
                       CString &password,
                       BOOL    &useTwitStar,
                       BOOL    &useHatenaFotolife,
                       BOOL    &writeLogFile,
                       CString &logFilename );

    void    SetTumblr( CString username,
                       CString password,
                       CString group,
                       CString blogName,
                       BOOL    useTumblr,
                       BOOL    useTumblr2,
                       BOOL    writeLogFile,
                       CString logFilename );
    void    GetTumblr( CString &username,
                       CString &password,
                       CString &group,
                       CString &blogName,
                       BOOL    &useTumblr,
                       BOOL    &useTumblr2,
                       BOOL    &writeLogFile,
                       CString &logFilename );

    void    SetGyazo( BOOL    useGyazo,
                      BOOL    writeLogFile,
                      CString logFilename );
    void    GetGyazo( BOOL    &useGyazo,
                      BOOL    &writeLogFile,
                      CString &logFilename );

    void    SetFlickr( BOOL    useFlickr,
                       BOOL    writeLogFile,
                       CString logFilename,
                       CString flickrToken,
                       CString flickrUserName );
    void    GetFlickr( BOOL    &useFlickr,
                       BOOL    &writeLogFile,
                       CString &logFilename,
                       CString &flickrToken,
                       CString &flickrUserName );

    void    SetProxy( BOOL    useProxy,
                      CString proxyServerName,
                      UINT    proxyPortNumber,
                      CString proxyUserName,
                      CString proxyPassword );
    void    GetProxy( BOOL    &useProxy,
                      CString &proxyServerName,
                      UINT    &proxyPortNumber,
                      CString &proxyUserName,
                      CString &proxyPassword );

// ダイアログ データ
	//{{AFX_DATA(CChirrupDlg)
	enum { IDD = IDD_CHIRRUP_DIALOG };
	CComboBox	m_timelineTypeList;
	CRichEditEx	m_messageCtrl;
	CString	m_monologue;
	CString	m_periodStr;
	BOOL	m_checkBrowsing;
	CString	m_timelineType;
	BOOL	m_postMulti;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CChirrupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
    bool    m_useTumblr;    // tumblr を使うかどうか

    void    SetTargetUserOnMonologue( CString targetUser );
    BOOL    SetPaneText(int nIndex, LPCTSTR lpszNewText, BOOL bUpdate = TRUE);

    void    UploadImage( PARAM_UPLOADIMAGE *param );
    void    UploadImage( const char *filename );
    void    PostImage( const char *url );
    CHIRRUP_FTYPE   GetImageSize( const char *filename,
                                  int& height, int& width );

    // 画面キャプチャ
    bool    m_useHatenaFotolife;// はてなFOTOLIFEを使うか否か
    bool    m_useTumblr2;       // tumblr への画像アップロード機能を使うか否か
    bool    m_useGyazo;         // Gyazo への画像アップロード機能を使うか否か
    bool    m_useFlickr;        // Flickr への画像アップロード機能を使うか否か
    bool    m_useWassrForUpload;// Wassr への画像アップロード機能を使うか否か

    bool    m_inCapturing;
    void    OnEndCapture();

#define ADJUST_HEIGHT   4
#define ADJUST_WIDTH    8
#define FORTH_REDRAW    (UINT)(0xFFFF)

protected:
    CTwitterManager *m_twitter;
    CJaikuManager   *m_jaiku;
    CManager        *m_wassr;
    CManager        *m_mogo2;
    CManager        *m_timelog;
    CManager        *m_haruFm;
    CManager        *m_hatenaHaiku;

    // 共通
	HICON       m_hIcon;
    HCURSOR     m_hCursor;
    CStatusBar  m_status;

    CString     m_settingDir;
    CString     m_cacheDir;
    CString     m_configFilename;

    int         m_period;   // 更新周期
    bool        m_needToSave;
    bool        m_useImetter;   // 「いめったー」画像つきで投稿するか否か

    CString     m_urlBrowsing;  // ブラウザで閲覧中の URL
    CString     m_pageTitle;    // ブラウザで閲覧中のページの title
    int         m_count;

    CRect       m_rectBottom;
    CRect       m_rectFriend020;
    CRect       m_rectFriend010;
    CRect       m_rectCheckBrowsing;
    CRect       m_rectMonologue;
    CRect       m_rectPostMonologue;
    CRect       m_rectDirectMessage;
    CRect       m_rectUpdate;
    CRect       m_rectMessageCtrl;
    bool        m_initialized;
    bool        m_twitterHealthy;

    // ついすた (+ もごすた) / はてなFOTOLIFE
    bool        m_useTwitStar;      // ついすた機能を使うかどうか
    CString     m_hatenaID;         // はてなID
    CString     m_hatenaPassword;   // パスワード
    bool        m_hatenaFotolifeWriteLogFile;   // ログを残すか否か
    CString     m_hatenaFotolifeLogFilename;    // ログファイル名

    // tumblr
    CString     m_tumblrID;           // メールアドレス
    CString     m_tumblrPassword;     // パスワード
    CString     m_tumblrName;         // 投稿対象tumbleblog またはグループ名
    CString     m_tumblrGroup;        // 投稿対象tumbleblog IDまたはグループ名
    bool        m_tumblrWriteLogFile; // ログを残すか否か
    CString     m_tumblrLogFilename;  // ログファイル名

    // Gyazo
    char        m_gyazoID[MAX_DATELENGTH];  // Gyazo ID (テンポラリ)
    bool        m_gyazoWriteLogFile;        // ログを残すか否か
    CString     m_gyazoLogFilename;         // ログファイル名

    // Flickr
    char        m_flickrToken[MAX_CATIDLENGTH];     // flickr トークン
    char        m_flickrUserName[MAX_CATIDLENGTH];  // flickr ユーザ名
    bool        m_flickrWriteLogFile;               // ログを残すか否か
    CString     m_flickrLogFilename;                // ログファイル名

    // Wassr (画像)
    bool        m_wassrWriteLogFileForUpload;   // ログを残すか否か
    CString     m_wassrLogFilenameForUpload;    // ログファイル名

    // 画面キャプチャ
    HWND        m_hWndForCapture;
    HINSTANCE   m_hInstForCapture;

#define CACHE_DIRECTORY     "cache/"
#define SETTING_DIRECTORY   "setting/"
#define SETTING_FILENAME    "chirrup.inf"
    void    LoadSetting();
    void    SaveSetting();

    bool    GetStringValue(
                const char *inputString,
                const char *targetName,
                char       *stringValue );

    void    WriteKeys(
                FILE          *fp,      // (I/O) 書き出し先
                char          *key,     // (I/O) 公開鍵
                unsigned char **secret, // (I/O) 復号に必要な情報(秘密鍵)
                bool          &done );  // (O)   暗号化処理実行済みか否か

    bool    CheckKeys(
                const char          *p,
                const unsigned char *rsaString,
                bool                &ret );

    bool    EvalKeys(
                const char          *p,
                const unsigned char *rsaString );

    bool    CheckEncodedPassword();
    void    GetProxyInfo( bool           &p_isUsedProxy,
                          CString        &p_proxyServer,
                          unsigned short &p_proxyPort,
                          CString        &p_proxyUserName,
                          CString        &p_proxyPassword );

    bool            IsInner( int id, WORD wX, WORD wY );

    CWinThread      *DisplayProfImages( CTwitterTimeline *tp );
    void            DisplayTimeline();

    void            PostMessageToFriend( int idx );
    char            *GetSceenNameOfFriend( int idx );
    void            ShowFriendProfile( int idx );
    void            ShowWebPage( int idx );
    void            SendDirectMessageToFriend( int idx );
    void            AddFriend( int idx );
    void            RemoveFriend( int idx );
    void            ShowFavorites( int idx );

    bool            PostMonologue( PARAM_POST *param );

    void            UpdateSingle( CManager *manager );
    void            UpdateSingle();

	// メッセージマップ関数
	//{{AFX_MSG(CChirrupDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPostMonologue();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnUpdate();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKillfocusPeriod();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnDisplayToolTip(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTwitter();
	afx_msg void OnHatenagroup();
	afx_msg void OnHatenabookmark();
	afx_msg void OnDelicous();
	afx_msg void OnGooglegroups();
	afx_msg void OnTwitterwiki();
	afx_msg void OnTwitterChirrup();
	afx_msg void OnMixi();
	afx_msg void OnMagnolia();
	afx_msg void OnDigg();
	afx_msg void OnLivedoorclip();
	afx_msg void OnLivedoor();
	afx_msg void OnGoogle();
	afx_msg void OnYahoo();
	afx_msg void OnBloglines();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnFriend001();
	afx_msg void OnFriend002();
	afx_msg void OnFriend003();
	afx_msg void OnFriend004();
	afx_msg void OnFriend005();
	afx_msg void OnFriend006();
	afx_msg void OnFriend007();
	afx_msg void OnFriend008();
	afx_msg void OnFriend009();
	afx_msg void OnFriend010();
	afx_msg void OnFriend011();
	afx_msg void OnFriend012();
	afx_msg void OnFriend013();
	afx_msg void OnFriend014();
	afx_msg void OnFriend015();
	afx_msg void OnFriend016();
	afx_msg void OnFriend017();
	afx_msg void OnFriend018();
	afx_msg void OnFriend019();
	afx_msg void OnFriend020();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnTwitterSearch();
	afx_msg void OnCheckBrowsing();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnRecvDirectmessage();
	afx_msg void OnSelchangeComboTimelineType();
	afx_msg void OnSettingAccount();
	afx_msg void OnJaiku();
	afx_msg void OnCheckMultipost();
	afx_msg void OnMogo2();
	afx_msg void OnWassr();
	afx_msg void OnTimelog();
	afx_msg void OnHarufm();
	afx_msg void OnExecuting();
	afx_msg void OnHatenastar();
	afx_msg void OnFavotter();
	afx_msg void OnTumblr();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnEditPaste();
	afx_msg void OnStartCapture();
	afx_msg void OnGyazo();
	afx_msg void OnHatenaFotolife();
	afx_msg void OnFlickr();
	afx_msg void OnTwitterSNS();
	afx_msg void OnDestroy();
	afx_msg void OnHatenaHaiku();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CRITICAL_SECTION    m_cs_chirrup; // スレッド間での排他制御用
    PARAM_UPDATE        m_param;      // for Thread of updating timeline
    PARAM_POST          m_postTweet;  // for Thread of posting monologue
    PARAM_POST          m_postBrowse; // for Thread of posting 'browsing info'
    PARAM_LOADIMAGE     m_paramLoadImage;   // for Thread of 'loading images'
    PARAM_UPLOADIMAGE   m_paramUploadImage; // for Thread of 'upload image'
    CWinThread          *m_loadImageThread;
    volatile bool       m_inSetting;
    bool                m_showServiceName;
    CString             m_serviceName;
    CFont               m_cFont1;
    CFont               m_cFont2;

    char                m_waitedFilename[MAX_PATH];

    unsigned long       m_nType;
    long                m_cx;
    long                m_cy;
    long                m_cxInitial;
    long                m_cyInitial;

    bool                m_updateUserIcon;

    CTwitterTimeline    *GetCurrentTimeline()
    {
        CTwitterTimeline    *tp =
            !m_timelineType.Compare( "Jaiku: Public" )
                                        ? &(m_jaiku->m_publicTimeline)
                                        :
            !m_timelineType.Compare( "Jaiku: User" )
                                        ? &(m_jaiku->m_userTimeline)
                                        :
            !m_timelineType.Compare( "Jaiku: Friends" )
                                        ? &(m_jaiku->m_friendsTimeline)
                                        :
            !m_timelineType.Compare( "Wassr: Public" )
                                        ? &(m_wassr->m_publicTimeline)
                                        :
            !m_timelineType.Compare( "Wassr: User" )
                                        ? &(m_wassr->m_userTimeline)
                                        :
            !m_timelineType.Compare( "Wassr: Friends" )
                                        ? &(m_wassr->m_friendsTimeline)
                                        :
            !m_timelineType.Compare( "もごもご: Public" )
                                        ? &(m_mogo2->m_publicTimeline)
                                        :
            !m_timelineType.Compare( "もごもご: User" )
                                        ? &(m_mogo2->m_userTimeline)
                                        :
            !m_timelineType.Compare( "もごもご: Friends" )
                                        ? &(m_mogo2->m_friendsTimeline)
                                        :
            !m_timelineType.Compare( "Timelog: Public" )
                                        ? &(m_timelog->m_publicTimeline)
                                        :
            !m_timelineType.Compare( "Timelog: User" )
                                        ? &(m_timelog->m_userTimeline)
                                        :
            !m_timelineType.Compare( "Timelog: Friends" )
                                        ? &(m_timelog->m_friendsTimeline)
                                        :
            !m_timelineType.Compare( "Haru.fm: Public" )
                                        ? &(m_haruFm->m_publicTimeline)
                                        :
            !m_timelineType.Compare( "Haru.fm: User" )
                                        ? &(m_haruFm->m_userTimeline)
                                        :
            !m_timelineType.Compare( "Haru.fm: Friends" )
                                        ? &(m_haruFm->m_friendsTimeline)
                                        :
            !m_timelineType.Compare( "はてなハイク: Public" )
                                        ? &(m_hatenaHaiku->m_publicTimeline)
                                        :
            !m_timelineType.Compare( "はてなハイク: User" )
                                        ? &(m_hatenaHaiku->m_userTimeline)
                                        :
            !m_timelineType.Compare( "はてなハイク: Friends" )
                                        ? &(m_hatenaHaiku->m_friendsTimeline)
                                        :
            !m_timelineType.Compare( "Twitter: Replies" )
                                        ? &(m_twitter->m_replies)
                                        :
            !m_timelineType.Compare( "Twitter: User" )
                                        ? &(m_twitter->m_userTimeline)
                                        :
            !m_timelineType.Compare( "Twitter: Public" )
                                        ? &(m_twitter->m_publicTimeline)
                                        : &(m_twitter->m_friendsTimeline);

        return ( tp );
    }

    CString GetCurrentScreenName()
    {
        CString s =
            !strncmp( m_timelineType, "Jaiku: ", 7 )
                                        ? m_jaiku->m_screenName
                                        :
            !strncmp( m_timelineType, "Wassr: ", 7 )
                                        ? m_wassr->m_screenName
                                        :
            !strncmp( m_timelineType, "もごもご: ", 10 )
                                        ? m_mogo2->m_screenName
                                        :
            !strncmp( m_timelineType, "Timelog: ", 9 )
                                        ? m_timelog->m_screenName
                                        :
            !strncmp( m_timelineType, "Haru.fm: ", 9 )
                                        ? m_haruFm->m_screenName
                                        :
            !strncmp( m_timelineType, "はてなハイク: ", 9 )
                                        ? m_hatenaHaiku->m_screenName
                                        : m_twitter->m_screenName;

        return ( s );
    }

    void    SwitchMultiPost();
    void    SwitchTimelineList();
    void    SwitchTimelineFacilities();
    void    SwitchTitle();
    void    SwitchCapture();
    void    SwitchImetter();

    void    ShowServiceName( bool mode );
    void    ReduceExtra();

    bool    DisplayContextMenuForServices( WORD wX, WORD wY );
    bool    DisplayContextMenuForFriends( WORD wX, WORD wY );
    bool    DisplayContextMenuForImetter( WORD wX, WORD wY );
    bool    ExtraContextMenu( WORD wX, WORD wY );
    void    SetStaticEdge( int idx, bool status );
    void    SetAddrOnMonologue( CString targetUser, CEdit *cp );

private:
    CChirrupDlg( CChirrupDlg &dlg );
    CChirrupDlg operator = ( CChirrupDlg &dlg );

    void    DeleteHtmlTags( CString &targetString )
    {
        size_t  sz = targetString.GetLength();
        if ( strchr( targetString, '<' ) ) {
            /* html タグの除去 */
            char    *temp = new char[sz + 1];

            if ( temp ) {
                strcpy( temp, targetString );

                char        *p = temp;
                char        *q;
                const char  *r;
                while ( ( q = strchr( p, '<' ) ) != NULL ) {
                    if ( (r = strchr(q + 1, '>')) != NULL )
                        strcpy( q, r + 1 );
                    else {
                        *q = NUL;
                        break;
                    }
                }

                targetString = temp;
                delete [] temp;
            }
        }
    }

    void    WriteUploadLog( const char *filename,
                            const char *url,
                            const char *caption );
    bool    SetSigInfo( CString &sKey,    CString &sSecret,
                        const char *sig1, const char *sig2 );

    void    GetImageViaImetter( CString &monologue, ProceedingDialog *pdlg );

    // タスクトレイアイコン関連
    NOTIFYICONDATA  m_stNotifyIcon;
#define WM_APP_TASKTRY  (WM_APP + 0x0BED)  
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_CHIRRUPDLG_H__5843E218_092A_47EB_AA1F_F176B490916A__INCLUDED_)
