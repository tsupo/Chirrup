/*
 * chirrupDlg.cpp : Twitter クライアント chirrup
 *      メインダイアログ インプリメンテーション ファイル
 *          written by H.Tsujimura  4 Apr 2007
 *
 *      Copyright (c) 2007, 2008, 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/chirrupDlg.cpp $
 * 
 * 3     09/06/18 1:33 tsupo
 * 2.01版
 * 
 * 211   09/06/16 0:50 Tsujimura543
 * key 読み出しタイミング修正 (アカウント情報未設定状態での起動時、
 * OAuth 認証を選択しても、アクセストークンを取りにいかない不具合
 * に対処)
 * 
 * 2     09/05/31 20:42 tsupo
 * 1.142版
 * 
 * 210   09/05/29 19:22 Tsujimura543
 * 同一アカウントで複数 tumbleblog を開設している場合の投稿先
 * tumbleblog を指定しての投稿を可能にした
 * 
 * 209   09/05/27 18:21 Tsujimura543
 * setSigInfo() の引数を追加
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 208   09/05/12 17:16 Tsujimura543
 * 「スレッド起動時刻」を各タイムライン取得処理を呼び出すタイミングで
 * 上書きするように変更 (サービスごと → タイムラインごと に変更)
 * 
 * 207   09/05/07 13:42 Tsujimura543
 * タイムアウト発生時処理が発動する条件の元となるスレッド起動時刻を
 * 各サービスの取得処理起動ごとに上書きするようにした
 * (他のサービスで発生したタイムアウトで別のサービスが強制終了してしまう
 * のを防止するため)
 * 
 * 206   09/04/28 20:52 Tsujimura543
 * タイムアウト取得処理が規定時間内に終わらない場合の処理を変更
 * (スレッド強制終了方式ではなく、イベント通知方式を採用)
 * 
 * 205   09/04/28 18:24 Tsujimura543
 * メモリリーク調査用のコードを追加 (デバッグビルド版のみ有効)
 * 
 * 204   09/04/22 21:11 Tsujimura543
 * 「設定」ダイアログからもFlickr認証のアクセストークン(frob)を取得できる
 * ようにした
 * 
 * 203   09/04/16 17:14 Tsujimura543
 * 「設定」ダイアログ起動中かどうかを示すフラグの操作を排他制御の下で
 * 実行するようにした
 * 
 * 202   09/04/16 17:09 Tsujimura543
 * 「設定」ダイアログ起動中は、タイマ割り込み発生による「更新」処理
 * (タイムラインの取得)を実行しないようにした
 * 
 * 201   09/04/16 16:11 Tsujimura543
 * 新規インストール時に OAuth 認証設定したあと、スクリーン名の取得に失敗
 * する等、OAuth 対応時に作りこんでしまったバグを修正
 * 
 * 200   09/04/15 1:17 Tsujimura543
 * Jaiuku の OAuth 対応準備
 * 
 * 199   09/03/31 23:29 Tsujimura543
 * Twitter の OAuth 対応準備 その7
 * 
 * 198   09/03/31 21:27 Tsujimura543
 * Twitter の OAuth 対応準備 その5
 * 
 * 197   09/03/30 22:36 Tsujimura543
 * Twitter の OAuth 対応準備 その2
 * 
 * 196   09/03/30 22:20 Tsujimura543
 * Flickr のユーザ名、アクセストークンを設定ファイルに保存するようにした
 * 
 * 195   09/03/27 17:28 Tsujimura543
 * Twitter の OAuth 対応準備
 * 
 * 194   09/03/25 12:22 Tsujimura543
 * 発言投稿後、発言の「キャンセル」ボタンが「発言」ボタンに戻らない不具合
 * を修正
 * 
 * 193   09/03/20 15:54 Tsujimura543
 * 「発言」投稿処理のキャンセル機能を追加
 * 
 * 192   09/03/12 19:28 Tsujimura543
 * 「タイムライン取得スレッドで無限ループ発生時対策」発動時の表示を再調整
 * 
 * 191   09/03/10 17:06 Tsujimura543
 * 2つの ExecuteUpdate() でのタスクトレイアイコンの表示変更タイミング
 * を統一した
 * 
 * 190   09/03/10 15:57 Tsujimura543
 * 「タイムライン取得スレッドで無限ループ発生時対策」を再調整
 * 
 * 189   09/03/09 21:58 Tsujimura543
 * 「タイムライン取得スレッドで無限ループ発生時対策」を修正
 * 
 * 188   09/03/09 21:41 Tsujimura543
 * タイムライン取得スレッド監視処理に「タイムライン取得スレッドで
 * 無限ループ発生時対策」を入れてみた
 * 
 * 187   08/12/22 22:56 Tsujimura543
 * 「いめったー」対応、動作確認終了
 * 
 * 186   08/12/22 22:55 Tsujimura543
 * Twitter のアカウントがある場合は、「いめったー」にスクリーン名を送
 * るようにした(パスワードは送らない)。この結果、imefav にも参加可能と
 * なった
 * 
 * 185   08/12/22 20:54 Tsujimura543
 * 「いめったー」対応
 * 
 * 184   08/12/18 11:11 Tsujimura543
 * CChirrupDlg::CheckKeys() を修正 (ret の値の設定方法を修正)
 * 
 * 183   08/12/04 18:19 Tsujimura543
 * コード整理、安定化作業を実施
 * 
 * 182   08/11/26 22:50 Tsujimura543
 * __TEST__ が define されているときは、API 経由での画像アップロードを
 * 試みるようにした
 * 
 * 181   08/10/21 23:59 Tsujimura543
 * 1.109版
 * 
 * 180   08/10/21 23:50 Tsujimura543
 * 右クリックメニューに、「サポート」、「コミュニティ」、「バージョン情
 * 報」を追加
 * 
 * 179   08/08/22 18:42 Tsujimura543
 * 「はてなハイク」対応
 * 
 * 178   08/08/11 18:11 Tsujimura543
 * _ExecuteUploadImage() を修正(Wassr への同時投稿を「一時的にオフ」に
 * しても同時投稿してしまう不具合の修正)
 * 
 * 177   08/08/02 3:41 Tsujimura543
 * Wassr の参加中のチャンネル一覧表示機能を追加
 * 
 * 176   08/08/01 2:40 Tsujimura543
 * (1) Wassr への画像の投稿に対応
 * (2) 「チャンネル」対応準備
 * 
 * 175   08/07/16 19:30 Tsujimura543
 * タイムライン取得中とそれ以外のときとで、タスクトレイのアイコンを
 * 変えてみるようにした
 * 
 * 174   08/07/16 19:00 Tsujimura543
 * タスクトレイ用のアイコンを新たに用意した(背景を透過にしただけのアイコン)
 * 
 * 173   08/07/16 18:30 Tsujimura543
 * 「メニューが消えずに残ったままになることがある現象への対策」を実施
 * (タスクトレイアイコンの右クリック時に表示するメニューで発生している現象)
 * 
 * 172   08/07/16 15:27 Tsujimura543
 * Timelog の「評価」に対応した
 * 
 * 171   08/07/16 13:49 Tsujimura543
 * m_stNotifyIcon.szTip[] に文字列を格納する際のバッファーオーバーラン
 * 予防策を追加
 * 
 * 170   08/07/16 4:13 Tsujimura543
 * 「同時投稿対象」の設定を「設定」ダイアログでも設定できるようにした
 * 
 * 169   08/07/16 2:16 Tsujimura543
 * タスクトレイアイコンの右クリックメニュー項目を追加 (キャンセルと終了)
 * 
 * 168   08/07/16 1:20 Tsujimura543
 * タスクトレイ常駐機能を実装
 * 
 * 167   08/07/14 14:59 Tsujimura543
 * Twitter の「API制限情報取得API」を呼ぶ回数、タイミングを調整し直した
 * 
 * 166   08/07/08 17:46 Tsujimura543
 * Wassr の friend の add と remove にも対応した
 * 
 * 165   08/07/08 14:51 Tsujimura543
 * Wassr の「イイネ!」に対応
 * 
 * 164   08/06/30 18:50 Tsujimura543
 * Twitter の「API制限状況」を表示するようにしてみた
 * 
 * 163   08/03/26 22:15 Tsujimura543
 * Firefox からの画像ドラッグ対応 (いったんイベントハンドラから抜ける)
 * 
 * 162   08/02/27 20:16 Tsujimura543
 * 「ついったー部SNS支局」のアイコンを追加
 * 
 * 161   08/02/08 23:17 Tsujimura543
 * (1) Wassr のユーザアイコンダブルクリック時の挙動を変更
 * (2) Wassr のユーザアイコンにマウスをもっていったときのtooltip表示内容
 *     を変更
 * -- (1), (2) ともに、スクリーン名ではなく、ユーザ名を使うようにした
 * 
 * 160   08/02/05 23:23 Tsujimura543
 * コードを整理
 * 
 * 159   08/01/31 20:27 Tsujimura543
 * ExtraContextMenu() を修正 (修正ミスを発見、再修正)
 * 
 * 158   08/01/31 18:50 Tsujimura543
 * ユーザアイコン(プロフィールアイコン)の更新機能を on/off できるように
 * してみた
 * 
 * 157   08/01/28 18:40 Tsujimura543
 * ウィンドウサイズを保存、復元できるようにしてみた
 * 
 * 156   08/01/28 14:52 Tsujimura543
 * ついったん、たんぶらんからの警告ダイアログのボタンを Yes/No の二択
 * から OK ボタン1個のみに変更した
 * 
 * 155   08/01/24 15:29 Tsujimura543
 * Gyazo, Flickr, はてなフォトライフの各アイコンを追加
 * 
 * 154   08/01/24 14:55 Tsujimura543
 * CUploadImageDialog の画像同時投稿対象先指定機能に対応
 * 
 * 153   08/01/24 13:22 Tsujimura543
 * 文言修正: 同時登録対象から外す → 同時投稿対象から外す
 * 
 * 152   08/01/23 17:40 Tsujimura543
 * はてなフォトライフ対応
 * 
 * 151   08/01/19 2:10 Tsujimura543
 * SaveSetting() を修正
 * 
 * 150   08/01/19 0:33 Tsujimura543
 * はてなフォトライフ対応準備
 * 
 * 149   08/01/17 19:05 Tsujimura543
 * ソースコードを整理
 * 
 * 148   08/01/17 19:01 Tsujimura543
 * (1) メインダイアログを従来よりもさらに(縦方向に)小さくできるようにして
 *     みた
 * (2) 右クリックメニューに「スクリーンキャプチャ」を追加した
 * 
 * 147   08/01/09 22:27 Tsujimura543
 * Flickr 対応作業、とりあえず終了 (動作確認完了)
 * 
 * 146   08/01/09 19:23 Tsujimura543
 * Flickr 対応
 * 
 * 145   08/01/09 17:10 Tsujimura543
 * Flickr 対応準備 その2
 * 
 * 144   08/01/08 21:07 Tsujimura543
 * flickr 対応準備
 * 
 * 143   07/12/25 18:37 Tsujimura543
 * _ExecuteUploadImage() を修正し、BMP形式以外のファイルのアップロード時に
 * 一時的に作成されるBMPファイルの削除処理を追加
 * 
 * 142   07/12/20 16:36 Tsujimura543
 * 初期設定ファイルがまだ存在しない状態で起動したときにproxy設定処理が2回
 * 動いてしまう不具合を修正
 * 
 * 141   07/12/19 22:08 Tsujimura543
 * tumblr と Gyazo へ同時にファイルをアップロードした場合、tumblr のログ
 * の方にも Gyazo の方の URL が記録されてしまう不具合を修正
 * 
 * 140   07/12/19 18:44 Tsujimura543
 * http 関連関数呼び出しまわりを整理
 * 
 * 139   07/12/19 16:34 Tsujimura543
 * Tumblr と Gyazo にアップロードしたファイルの URL を記録する機能を
 * 追加
 * 
 * 138   07/12/19 16:12 Tsujimura543
 * Tumblr と Gyazo にアップロードしたファイルの URL を記録する機能を
 * 追加するためのプロパティを追加
 * 
 * 137   07/12/17 19:52 Tsujimura543
 * capture 関連の変数、関数を CCapture クラスとしてまとめたことに伴う
 * 修正を実施
 * 
 * 136   07/12/17 19:04 Tsujimura543
 * Gyazo へのアップロード時、BMP だけでなく、GIF や JPG についても PNG
 * に変換してからアップロードするようにした
 * 
 * 135   07/12/15 6:29 Tsujimura543
 * SwitchCapture() を追加
 * 
 * 134   07/12/15 5:29 Tsujimura543
 * キャプチャ機能使用後の一時ファイル削除処理を追加
 * 
 * 133   07/12/15 5:13 Tsujimura543
 * キャプチャー機能実装完了 (まだ、多少の修正を行なう可能性あり)
 * 
 * 132   07/12/15 2:54 Tsujimura543
 * キャプチャー機能、試験実装 (まだ、試行錯誤中)
 * 
 * 131   07/12/14 15:57 Tsujimura543
 * 画像投稿処理まわりを修正。いったんfix
 * 
 * 130   07/12/13 23:01 Tsujimura543
 * 「課題」を追記
 * 
 * 129   07/12/13 22:26 Tsujimura543
 * 画像のアップロード処理周りを変更(はてなFotolife対応準備、bmpファイル対
 * 応)
 * 
 * 128   07/12/13 20:42 Tsujimura543
 * GetImageSize() をリファクタリング
 * 
 * 127   07/12/13 20:28 Tsujimura543
 * GetImageSize() を bmp にも対応させた
 * 
 * 126   07/12/13 18:41 Tsujimura543
 * proxy関連の関数群を proxy.cpp として分離独立させた
 * 
 * 125   07/12/13 18:04 Tsujimura543
 * [暫定] WM_HOTKEY を利用してホットキー(ショートカットキー)を組み込
 *        んでみるテスト
 *   → 子ウィンドウにも引き継がれてしまうため、このままでは使えない
 * 
 * 124   07/12/10 23:05 Tsujimura543
 * 画像投稿後の m_monologue に文字列を設定する処理を修正
 * 
 * 123   07/12/10 22:41 Tsujimura543
 * 画像投稿関連処理のスレッド構成変更に伴う修正を実施
 * 
 * 122   07/12/10 18:10 Tsujimura543
 * tumblr への投稿関連処理も fix
 * 
 * 121   07/12/10 16:39 Tsujimura543
 * Gyazo への投稿処理関連を fix
 * 
 * 120   07/12/06 19:51 Tsujimura543
 * Gyazo にも画像をアップロードできるようにしてみた (暫定版)
 * 
 * 119   07/12/06 4:08 Tsujimura543
 * tumblr への画像ファイルアップロード処理を別スレッド化した
 * 
 * 118   07/12/06 1:59 Tsujimura543
 * tumblr への画像の投稿に対応
 * 
 * 117   07/11/26 21:44 Tsujimura543
 * 「ふぁぼったー」と tumblr のアイコンを追加
 * 
 * 116   07/11/26 20:23 Tsujimura543
 * proxy設定関連、異常系強化
 * 
 * 115   07/11/26 18:04 Tsujimura543
 * proxy設定関連移行作業、完了
 * 
 * 114   07/11/26 18:03 Tsujimura543
 * OnSettingProxy() → DoSettingProxy() に移行
 * 
 * 113   07/11/26 17:57 Tsujimura543
 * CProxyInfoDialog を廃止し、CSettingProxy に移行
 * 
 * 112   07/11/07 3:39 Tsujimura543
 * 見ている発言を 引用して Tumblr へ投稿する機能を作成
 * 
 * 111   07/09/27 21:47 Tsujimura543
 * OnSize() を修正。「他のサービスに同時投稿する」の表示を消す/復活させる
 * 処理が抜けていた
 * 
 * 110   07/09/27 19:49 Tsujimura543
 * ShowFavorites() を追加
 * 
 * 109   07/09/27 18:35 Tsujimura543
 * 「もごすた」に対応した
 * 
 * 108   07/09/26 20:05 Tsujimura543
 * ダイレクトメッセージ表示ダイアログおよびプロフィール表示ダイアログ
 * 表示中もメインダイアログのステータスバーを更新するようにした
 * (ステータスバーをいじろうとしてnullポインタ参照で落ちるバグを回避)
 * 
 * 107   07/09/14 19:13 Tsujimura543
 * リンク部分をマウスオーバーしたときに、URL をステータスバーに表示する
 * ようにした
 * 
 * 106   07/09/14 17:52 Tsujimura543
 * ステータスバーにメッセージを表示できるようにした
 * 
 * 105   07/09/12 21:38 Tsujimura543
 * SetAddrOnMonologue() を導入、リファクタリングを実施
 * 
 * 104   07/09/07 16:23 Tsujimura543
 * PostMessageToFriend() を修正。Timelog に対応しきれていなかったところ
 * を直した
 * 
 * 103   07/08/28 17:59 Tsujimura543
 * SetStaticEdge() を修正
 * 
 * 102   07/08/28 17:08 Tsujimura543
 * (1) 同時登録対象になっているかどうかを視覚的に区別できるように、くぼみ
 *     状態にする/しないエフェクトを施すようにしてみた
 * (2) OnContextMenu() を整理、新しいメソッドを作って処理を分けた
 * (3) ReduceExtra() で Timelog 関連の処理がごっそり抜けていたので追加
 * 
 * 101   07/08/28 1:56 Tsujimura543
 * 同時投稿対象にするサービスを選択できるようにした
 * 
 * 100   07/08/28 0:37 Tsujimura543
 * (1) ReduceExtra() を導入
 * (2) 少しだけソース整理
 * 
 * 99    07/08/28 0:03 Tsujimura543
 * 利用していないサービスに関しては、メモリを常時占有しないようにしてみた
 * (ただし、起動時、設定変更時は一時的に占有が発生する)
 * 
 * 98    07/08/27 22:22 Tsujimura543
 * ユーザ名、パスワードを設定していないサービスに関して、呼ばなくても
 * いい処理を呼んでしまっている箇所を修正
 * 
 * 97    07/08/25 1:53 Tsujimura543
 * 「ついすた」対応 (実際に☆をつける)
 * 
 * 96    07/08/25 0:45 Tsujimura543
 * 「ついすた」に対応 (表示)
 * 
 * 95    07/08/25 0:16 Tsujimura543
 * 「ついすた」に対応 (設定関係)
 * 
 * 94    07/08/17 18:04 Tsujimura543
 * Twitter への「発言」投稿時の最大文字数を 160 バイトから 160文字 に
 * 変更
 * 
 * 93    07/08/13 19:42 Tsujimura543
 * コメントを整理
 * 
 * 92    07/08/13 18:26 Tsujimura543
 * DisplayProfImages() 内から呼び出すアイコン描画処理を別スレッド化で
 * きるようにしてみた (USE_MULTITHREAD_FOR_LOADIMAGE 有効時、別スレッ
 * ド化する)
 * 
 * 91    07/08/13 13:05 Tsujimura543
 * timeline 切り替え時に「Powered by サービス名」の表示を切り替えるのを
 * 忘れていた。表示を切り替えるように修正。
 * 
 * 90    07/08/13 12:06 Tsujimura543
 * 「Powered by サービス名」の表示をするようにした
 * 
 * 89    07/08/09 14:23 Tsujimura543
 * 自分のスクリーン名をキャッシュするようにした
 * 
 * 88    07/07/05 0:40 Tsujimura543
 * ExecuteUpdate( CManager *p ) 経由で Twitter の Replies の取得処理
 * が呼び出されない不具合に対処
 * 
 * 87    07/07/03 18:35 Tsujimura543
 * Haru.fm のアイコンを設置
 * 
 * 86    07/07/03 14:53 Tsujimura543
 * haru.fm 対応 (動作確認済み)
 * 
 * 85    07/06/27 18:13 Tsujimura543
 * haru.fm に対応
 * 
 * 84    07/06/26 16:36 Tsujimura543
 * OnShowWindow() 内でも SwitchTimelineFacilities() を呼ぶようにする
 * (Twitter が閲覧対象外のときの表示がおかしくなる件の対処)
 * 
 * 83    07/06/26 0:29 Tsujimura543
 * CRichEditEx に m_timeline を追加し、Twitter の status リンクへ飛ぶ
 * ための処理を簡略化した
 * 
 * 82    07/06/25 21:13 Tsujimura543
 * CRichEditEx に SetLink() を導入
 * 
 * 81    07/06/23 0:40 Tsujimura543
 * SwitchTimelineFacilities() を導入
 * 
 * 80    07/06/22 23:12 Tsujimura543
 * OnSettingAccount() 内に「砂時計カーソル表示」を追加
 * 
 * 79    07/06/22 23:10 Tsujimura543
 * (1) OnSelchangeComboTimelineType() を修正、UpdateSingle() を使うことで
 *     余分なトラフィックの発生を避けた
 * (2) OnSettingAccount() を修正、閲覧対象を変更したときの timeline の切り
 *     替え処理の動きがおかしかったのを直した
 * 
 * 78    07/06/22 19:38 Tsujimura543
 * 「発言入力欄の最大入力可能バイト数」を調整
 * 
 * 77    07/06/22 19:34 Tsujimura543
 * 発言入力欄の最大入力可能バイト数をサービスごとに変えるように
 * してみた
 * 
 * 76    07/06/22 19:19 Tsujimura543
 * 「発言」投稿成功時、当該サービスのみを対象に timeline を取得するよう
 * にしてみた
 * 
 * 75    07/06/21 22:11 Tsujimura543
 * Timelog のダイレクトメッセージの送受信に対応 (動作確認済み)
 * 
 * 74    07/06/21 14:43 Tsujimura543
 * OnSetfocusMonologue() 相当の処理を RichEditEx.cpp に移動。
 * OnSetfocusMonologue() は削除。
 * 
 * 73    07/06/20 21:49 Tsujimura543
 * ログ表示用のフォントをほんの少しだけ大きくしてみた
 * 
 * 72    07/06/20 21:07 Tsujimura543
 * ログ表示部分に背景色を設定してみた
 * 
 * 71    07/06/20 19:28 Tsujimura543
 * SwitchTitle() を修正
 * 
 * 70    07/06/20 15:48 Tsujimura543
 * InitTimelineInfo() を廃止
 * 
 * 69    07/06/20 14:07 Tsujimura543
 * Timelog 対応版
 * 
 * 68    07/06/20 5:29 Tsujimura543
 * 複数サービス同時投稿時の投稿順序を変更
 * 
 * 67    07/06/20 5:19 Tsujimura543
 * (1) Twitter に CTwitterManager を適用
 * (2) ユーザアイコンの右クリックメニューに「関連Webページを表示」を追加
 * 
 * 66    07/06/20 3:16 Tsujimura543
 * 設定ファイルの読み書き処理を chirrupDlg から CManager と
 * CJaikuManager に移した
 * 
 * 65    07/06/20 1:56 Tsujimura543
 * Jaiku に CJaikuManager を適用
 * 
 * 64    07/06/20 0:31 Tsujimura543
 * Wassr にも CManager を適用
 * 
 * 63    07/06/19 23:12 Tsujimura543
 * (1) CManager を導入し、とりあえず「もごもご」に適用し動作確認をしてみた
 * (2) CService 導入に伴う修正を実施
 * 
 * 62    07/06/18 18:54 Tsujimura543
 * SwitchTitle() を修正、Twitter のアカウントが未設定の場合に Window
 * タイトルが化けることがある不具合に対処
 * 
 * 61    07/06/15 21:23 Tsujimura543
 * 「もごもご」のコメント投稿に対応
 * 
 * 60    07/06/15 19:41 Tsujimura543
 * プロフィールダイアログ起動時に bitmap ハンドルを渡すのをやめた
 * 
 * 59    07/06/15 0:07 Tsujimura543
 * timeline の切り替え時、必要に応じて、「もごもご」のスクリーン名
 * 取得処理を呼び出すようにした
 * 
 * 58    07/06/14 21:12 Tsujimura543
 * 「もごもご」に対応
 * 
 * 57    07/06/14 17:55 Tsujimura543
 * Wassr に対応
 * 
 * 56    07/06/13 19:18 Tsujimura543
 * Twitter の Replies の閲覧、ログ出力に対応
 * 
 * 55    07/06/13 1:27 Tsujimura543
 * (1) ダイアログに表示するバージョン番号情報をリソースファイルから
 *     拾ってくるようにした
 * (2) スクリーン名の表示を Twitter 固定から、Twitter/Jaiku切り替え
 *     表示できるようにした
 * (3) 設定ファイルがまだないときの起動時処理を整理、調整
 * 
 * 54    07/06/13 0:12 Tsujimura543
 * (1) TIMELINE_INFO 関連 fix
 * (2) 初期設定ファイル読み書きを新しいログファイル管理仕様に対応させた
 * 
 * 53    07/06/11 19:58 Tsujimura543
 * Twitter と Jaiku への同時投稿をサポート
 * 
 * 52    07/06/11 18:39 Tsujimura543
 * Twitter の user_timeline の閲覧をサポート
 * 
 * 51    07/06/07 14:12 Tsujimura543
 * コメントを修正
 * 
 * 50    07/06/07 14:11 Tsujimura543
 * 設定ファイルやキャッシュファイルを置くディレクトリのデフォルト値を
 * 「カレントディレクトリ」直下から「chirrup起動時点のカレントディレク
 * トリ」直下に変更
 * 
 * 49    07/06/07 1:50 Tsujimura543
 * コードを整理
 * 
 * 48    07/06/07 1:45 Tsujimura543
 * (1) friends_timeline 以外のタイムラインもログに書き出せるようにした
 * (2) 設定ダイアログをタブ選択形式のものに入れ替えた
 * 
 * 47    07/06/06 23:20 Tsujimura543
 * Jaiku の friends_timeline のログ書き出しにも対応
 * 
 * 46    07/06/06 22:21 Tsujimura543
 * ログファイルの書き出し機能サポートに伴う各種修正を実施
 * 
 * 45    07/06/06 16:27 Tsujimura543
 * 発言投稿処理も別スレッド化してみた
 * 
 * 44    07/06/05 20:32 Tsujimura543
 * Twitter/Jaiku の timeline の取得を完全に別スレッド化してみた
 * 
 * 43    07/06/05 17:33 Tsujimura543
 * Jaiku アイコンを追加
 * 
 * 42    07/06/05 17:06 Tsujimura543
 * RURL 機能廃止、ダイアログデザイン変更
 * 
 * 41    07/06/05 14:44 Tsujimura543
 * PostMonologue() 回りを改修、多少なりとも負荷を減らすようにしてみた
 * 
 * 40    07/06/04 21:11 Tsujimura543
 * friend の add と remove を実装 (for Twitter)
 * 
 * 39    07/06/04 14:51 Tsujimura543
 * _http_get() と _http_post() のプロトタイプ宣言を twitter.h に移動
 * 
 * 38    07/05/29 12:48 Tsujimura543
 * Jaiku の friends_timeline 対応(途中)
 * 
 * 37    07/05/29 6:39 Tsujimura543
 * Twitter のツンデレ状態判定機能(簡易版)を実装
 * 
 * 36    07/05/29 5:43 Tsujimura543
 * Jaiku への投稿をサポート
 * 
 * 35    07/05/29 5:13 Tsujimura543
 * Jaiku の user_timeline の閲覧に対応
 * 
 * 34    07/05/29 3:56 Tsujimura543
 * Jaiku (の public_timeline の閲覧) に対応
 * 
 * 33    07/05/26 0:22 Tsujimura543
 * Twitter と通信する部分を別スレッド化してみた
 * 
 * 32    07/05/25 23:03 Tsujimura543
 * リファクタリング
 * 
 * 31    07/05/25 21:07 Tsujimura543
 * リファクタリング
 * 
 * 30    07/05/25 20:15 Tsujimura543
 * CTwitterTimeline クラス関連の記述を別のファイルに分離、独立させた
 * 
 * 29    07/05/25 17:51 Tsujimura543
 * OnSelchangeComboTimelineType() を改良、瞬時に timeline の切り替えが
 * できるようにした
 * 
 * 28    07/05/25 17:45 Tsujimura543
 * 「chirrup 起動中」ダイアログを追加
 * 
 * 27    07/05/23 22:25 Tsujimura543
 * friends_timeline と public_timeline の表示切替機能を追加
 * 
 * 26    07/05/11 22:40 Tsujimura543
 * 発言入力中に「更新」+「閲覧中のWebページ投稿」があった場合でも、
 * 入力中の発言内容が消えないように対処
 * 
 * 25    07/05/11 21:29 Tsujimura543
 * ブラウザで閲覧中の URL を Twitter に送信するとき、その Web ページの
 * タイトルも取得して送信するようにした
 * 
 * 24    07/04/28 0:24 Tsujimura543
 * (1) メッセージ表示領域をダブルクリックしたときに格納される文字列を
 *     発言入力領域にフォーカスが移ったときに取り出す処理を追加
 * (2) ダイアログのタイトルにスクリーン名を表示するようにした
 * 
 * 23    07/04/27 22:28 Tsujimura543
 * (1) プロクシ関連の設定を保持するメンバーを CChirrupApp に移動
 * (2) 自分のスクリーン名を強調表示するようにしてみた
 * 
 * 22    07/04/27 19:39 Tsujimura543
 * Twitter API 関連の処理を Twitter.cpp に集約したのに伴う修正を実施
 * 
 * 21    07/04/26 20:59 Tsujimura543
 * リファクタリング
 * 
 * 20    07/04/26 20:21 Tsujimura543
 * URL をクリッカブルにしてみた
 * 
 * 19    07/04/26 0:22 Tsujimura543
 * ダイレクトメッセージ閲覧機能を実装
 * 
 * 18    07/04/25 20:39 Tsujimura543
 * メインダイアログを縦方向にリサイズできるようにしてみた
 * 
 * 17    07/04/25 16:20 Tsujimura543
 * ダイレクトメッセージ送信機能を実装
 * 
 * 16    07/04/24 23:49 Tsujimura543
 * ブラウザで閲覧中の URL を送信する機能を実装
 * 
 * 15    07/04/14 3:01 Tsujimura543
 * proxy関連の処理を再修正
 * 
 * 14    07/04/14 2:05 Tsujimura543
 * 右クリックメニューを追加
 * 
 * 13    07/04/14 0:17 Tsujimura543
 * proxy関連の処理を修正 (追加)
 * 
 * 12    07/04/13 23:50 Tsujimura543
 * proxy関連の処理を修正 (設定ダイアログに「いいえ」と答えると無限ループに
 * なってしまうことがある不具合に対処)
 * 
 * 11    07/04/13 23:45 Tsujimura543
 * DisplayProfImages() を修正、「更新」のたびに絵が入れ替わるようにした
 * 
 * 10    07/04/13 23:19 Tsujimura543
 * friends 画像表示機能を付けた (まだ、表示のみ)
 * 
 * 9     07/04/13 18:33 Tsujimura543
 * API のレスポンス(JSON)のフォーマットが変更されたので、新旧両フォーマッ
 * トに対応するように修正してみた
 * 
 * 8     07/04/09 21:07 Tsujimura543
 * 行数が MAX_NUMOFSTATUS を超えるところで落ちてしまう不具合に対処
 * 
 * 7     07/04/09 19:11 Tsujimura543
 * クォーテーションマークが含まれる発言が正しく表示されない不具合に対処
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

#include "chirrup.h"
#include "chirrupDlg.h"
#include "AboutDlg.h"
#include "SettingDialog.h"
#include "FriendDialog.h"
#include "DirectMessage.h"
#include "DirectMessageList.h"
#include "UploadImageDialog.h"
#include "parameter.h"
#include "timelog.h"
#include "wassr.h"
#include "ChannelWassr.h"
#include <direct.h>
extern "C" {
#include "utility.h"
#include "tumblr.h"
#include "gyazo.h"
#include "flickr.h"
#include "hatenaFotolife.h"
}
#include <sys/stat.h>
#include "proxy.h"
#include "http.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/chirrupDlg.cpp 3     09/06/18 1:33 tsupo $";
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

#if (WINVER >= 0x0500)
//#define IDC_HAND    MAKEINTRESOURCE(32649)
#ifdef IDC_HAND
#undef IDC_HAND
#endif
#endif /* WINVER >= 0x0500 */
#define IDC_HAND    IDC_HAND2

/////////////////////////////////////////////////////////////////////////////
// CChirrupDlg ダイアログ

CChirrupDlg::CChirrupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChirrupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChirrupDlg)
	m_monologue = _T("");
	m_periodStr = _T("");
	m_timelineType = _T("");
	m_checkBrowsing = FALSE;
	m_postMulti = FALSE;
	//}}AFX_DATA_INIT

    // 以下の2行はリッチエディットコントロールを使えるようにするおまじない
    AfxEnableControlContainer();
    AfxInitRichEdit();

    m_updateThread       = NULL;
    m_updateThread_Fired = false;
    m_postThread         = NULL;
    m_loadImageThread    = NULL;
    m_uploadImageThread  = NULL;
    m_inSetting          = false;

    m_twitter     = NULL;
    m_jaiku       = NULL;
    m_wassr       = NULL;
    m_mogo2       = NULL;
    m_timelog     = NULL;
    m_haruFm      = NULL;
    m_hatenaHaiku = NULL;

    char    dirname[MAX_PATH];
    dirname[0] = NUL;
    getcwd( dirname, MAX_PATH - 1 );
    if ( dirname[0] )
        strcat( dirname, "/" );
    else
        strcpy( dirname, "./" );
    m_cacheDir    = dirname;
    m_cacheDir   += _T(CACHE_DIRECTORY);
    m_settingDir  = dirname;
    m_settingDir += _T(SETTING_DIRECTORY);

    m_configFilename = _T(SETTING_FILENAME);
    m_period         = MS_UPDATE_TWITTER;    // デフォルトは1分周期で更新

    m_needToSave     = false;
    m_useImetter     = false;
    m_count          = 0;
    m_urlBrowsing    = _T("");
    m_pageTitle      = _T("");

    m_showServiceName = true;
    m_serviceName     = _T( "Powered by Twitter" );
    m_initialized     = false;
    m_twitterHealthy  = true;

    m_postTweet.ret   = false;
    m_postBrowse.ret  = false;

    m_useTwitStar                = false;
    m_hatenaID                   = _T("");
    m_hatenaPassword             = _T("");
    m_useHatenaFotolife          = false;
    m_hatenaFotolifeWriteLogFile = false;
    m_hatenaFotolifeLogFilename  = _T("");

    m_useTumblr          = false;
    m_useTumblr2         = false;
    m_tumblrID           = _T("");
    m_tumblrPassword     = _T("");
    m_tumblrGroup        = _T("");
    m_tumblrName         = _T("");
    m_tumblrWriteLogFile = false;
    m_tumblrLogFilename  = _T("");

    m_useGyazo           = false;
    m_gyazoID[0]         = NUL;
    m_gyazoWriteLogFile  = false;
    m_gyazoLogFilename   = _T("");

    m_useFlickr          = false;
    m_flickrToken[0]     = NUL;
    m_flickrUserName[0]  = NUL;
    m_flickrWriteLogFile = false;
    m_flickrLogFilename  = _T("");

    m_useWassrForUpload          = false;
    m_wassrWriteLogFileForUpload = false;
    m_wassrLogFilenameForUpload  = _T("");

    m_inCapturing        = false;
    m_hWndForCapture     = NULL;

    CChirrupApp *ap = (CChirrupApp *)AfxGetApp();
    m_hIcon   = ap->LoadIcon(IDR_MAINFRAME);
    m_hCursor = ap->LoadCursor( IDC_HAND );

    m_nType     = 0;
    m_cx        = 0;
    m_cy        = 0;
    m_cxInitial = 0;
    m_cyInitial = 0;

    m_updateUserIcon = true;

    m_waitedFilename[0] = NUL;

    InitializeCriticalSection( &m_cs_chirrup );
    _http_startUp();
}


CChirrupDlg::~CChirrupDlg()
{
    if ( m_needToSave )
        SaveSetting();

    if ( m_twitter )
        delete m_twitter;
    if ( m_jaiku )
        delete m_jaiku;
    if ( m_wassr )
        delete m_wassr;
    if ( m_mogo2 )
        delete m_mogo2;
    if ( m_timelog )
        delete m_timelog;
    if ( m_haruFm )
        delete m_haruFm;
    if ( m_hatenaHaiku )
        delete m_hatenaHaiku;

    m_cFont2.DeleteObject();
    m_cFont1.DeleteObject();

    CChirrupApp     *ap = (CChirrupApp *)AfxGetApp();
    if ( ap->m_event ) {
        CloseHandle( ap->m_event );
        ap->m_event = NULL;
    }
    if ( ap->m_capture ) {
        delete ap->m_capture;
        ap->m_capture = NULL;
    }

    _http_shutDown();
    DeleteCriticalSection( &m_cs_chirrup );
}

void CChirrupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChirrupDlg)
	DDX_Control(pDX, IDC_COMBO_TIMELINE_TYPE, m_timelineTypeList);
	DDX_Control(pDX, IDC_RICHEDIT_MESSAGES, m_messageCtrl);
	DDX_Text(pDX, IDC_MONOLOGUE, m_monologue);
	DDV_MaxChars(pDX, m_monologue, 1024);
	DDX_Text(pDX, IDC_PERIOD, m_periodStr);
	DDV_MaxChars(pDX, m_periodStr, 10);
	DDX_CBString(pDX, IDC_COMBO_TIMELINE_TYPE, m_timelineType);
	DDV_MaxChars(pDX, m_timelineType, 32);
	DDX_Check(pDX, IDC_CHECK_BROWSING, m_checkBrowsing);
	DDX_Check(pDX, IDC_CHECK_MULTIPOST, m_postMulti);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChirrupDlg, CDialog)
	//{{AFX_MSG_MAP(CChirrupDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_POST_MONOLOGUE, OnPostMonologue)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_WM_TIMER()
	ON_EN_KILLFOCUS(IDC_PERIOD, OnKillfocusPeriod)
	ON_WM_SETCURSOR()
    ON_NOTIFY(TTN_NEEDTEXT, 0, OnDisplayToolTip)
	ON_BN_CLICKED(IDC_TWITTER, OnTwitter)
	ON_BN_CLICKED(IDC_HATENAGROUP, OnHatenagroup)
	ON_BN_CLICKED(IDC_HATENABOOKMARK, OnHatenabookmark)
	ON_BN_CLICKED(IDC_DELICOUS, OnDelicous)
	ON_BN_CLICKED(IDC_GOOGLEGROUPS, OnGooglegroups)
	ON_BN_CLICKED(IDC_TWITTERWIKI, OnTwitterwiki)
	ON_BN_CLICKED(IDC_TWITTER_CHIRRUP, OnTwitterChirrup)
	ON_BN_CLICKED(IDC_MIXI, OnMixi)
	ON_BN_CLICKED(IDC_MAGNOLIA, OnMagnolia)
	ON_BN_CLICKED(IDC_DIGG, OnDigg)
	ON_BN_CLICKED(IDC_LIVEDOORCLIP, OnLivedoorclip)
	ON_BN_CLICKED(IDC_LIVEDOOR, OnLivedoor)
	ON_BN_CLICKED(IDC_GOOGLE, OnGoogle)
	ON_BN_CLICKED(IDC_YAHOO, OnYahoo)
	ON_BN_CLICKED(IDC_BLOGLINES, OnBloglines)
	ON_BN_CLICKED(IDC_FRIEND001, OnFriend001)
	ON_BN_CLICKED(IDC_FRIEND002, OnFriend002)
	ON_BN_CLICKED(IDC_FRIEND003, OnFriend003)
	ON_BN_CLICKED(IDC_FRIEND004, OnFriend004)
	ON_BN_CLICKED(IDC_FRIEND005, OnFriend005)
	ON_BN_CLICKED(IDC_FRIEND006, OnFriend006)
	ON_BN_CLICKED(IDC_FRIEND007, OnFriend007)
	ON_BN_CLICKED(IDC_FRIEND008, OnFriend008)
	ON_BN_CLICKED(IDC_FRIEND009, OnFriend009)
	ON_BN_CLICKED(IDC_FRIEND010, OnFriend010)
	ON_BN_CLICKED(IDC_FRIEND011, OnFriend011)
	ON_BN_CLICKED(IDC_FRIEND012, OnFriend012)
	ON_BN_CLICKED(IDC_FRIEND013, OnFriend013)
	ON_BN_CLICKED(IDC_FRIEND014, OnFriend014)
	ON_BN_CLICKED(IDC_FRIEND015, OnFriend015)
	ON_BN_CLICKED(IDC_FRIEND016, OnFriend016)
	ON_BN_CLICKED(IDC_FRIEND017, OnFriend017)
	ON_BN_CLICKED(IDC_FRIEND018, OnFriend018)
	ON_BN_CLICKED(IDC_FRIEND019, OnFriend019)
	ON_BN_CLICKED(IDC_FRIEND020, OnFriend020)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_TWITTER_SEARCH, OnTwitterSearch)
	ON_BN_CLICKED(IDC_CHECK_BROWSING, OnCheckBrowsing)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_RECV_DIRECTMESSAGE, OnRecvDirectmessage)
	ON_CBN_SELCHANGE(IDC_COMBO_TIMELINE_TYPE, OnSelchangeComboTimelineType)
	ON_BN_CLICKED(IDC_SETTING_ACCOUNT, OnSettingAccount)
	ON_BN_CLICKED(IDC_JAIKU, OnJaiku)
	ON_BN_CLICKED(IDC_CHECK_MULTIPOST, OnCheckMultipost)
	ON_BN_CLICKED(IDC_MOGO2, OnMogo2)
	ON_BN_CLICKED(IDC_WASSR, OnWassr)
	ON_BN_CLICKED(IDC_TIMELOG, OnTimelog)
	ON_BN_CLICKED(IDC_HARUFM, OnHarufm)
	ON_BN_CLICKED(IDC_EXECUTING, OnExecuting)
	ON_BN_CLICKED(IDC_HATENASTAR, OnHatenastar)
	ON_BN_CLICKED(IDC_FAVOTTER, OnFavotter)
	ON_BN_CLICKED(IDC_TUMBLR, OnTumblr)
	ON_WM_DROPFILES()
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_BN_CLICKED(IDC_START_CAPTURE, OnStartCapture)
	ON_BN_CLICKED(IDC_GYAZO, OnGyazo)
	ON_BN_CLICKED(IDC_HATENAFOTOLIFE, OnHatenaFotolife)
	ON_BN_CLICKED(IDC_FLICKR, OnFlickr)
	ON_BN_CLICKED(IDC_TWITTERSNS, OnTwitterSNS)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_HATENAHAIKU, OnHatenaHaiku)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ユーティリティ

CString
EscapeQuote( const char *p )
{
    CString s = _T("");
    char    *temp = new char[strlen(p) + 1];
    char    *q, *r;

    strcpy( temp, p );
    q = temp;
    do {
        r = strchr( q, '"' );
        if ( !r ) {
            s += q;
            break;
        }
        *r = NUL;
        s += q;
        s += "\"";
        q = r + 1;
    } while ( *q );

    delete [] temp;

    return ( s );
}

/////////////////////////////////////////////////////////////////////////////
// CChirrupDlg 追加メソッド

bool CChirrupDlg::GetStringValue(
                        const char *inputString,
                        const char *targetName,
                        char       *stringValue
                    )
{
    bool        ret = false;
    const char  *p = inputString, *q;
    int         len;

    len = targetName && *targetName ? strlen( targetName ) : 0;

    if ( (len > 0) && !strncmp( p, targetName, len ) ) {
        p += len;
        while ( (*p == ' ') || (*p == '\t') )
            p++;
        q = p + (strlen( p ) - 1);
        while ( (*q == ' ') || (*q == '\t') || (*q == '\r') || (*q == '\n') )
            q--;
        q++;
        strncpy( stringValue, p, q - p );
        stringValue[q - p] = '\0';

        ret = true;
    }

    return ( ret );
}

void    CChirrupDlg::LoadSetting()
{
    CString settingFilename;
    settingFilename =  m_settingDir;
    settingFilename += m_configFilename;

    FILE    *fp = fopen( settingFilename, "r" ) ;
    if ( fp ) {
        char            key[BUFSIZ];
        char            buf[BUFSIZ];
        char            temp[BUFSIZ];
        unsigned char   rsaString[BUFSIZ];
        char            *p;
        CChirrupApp     *ap = (CChirrupApp *)AfxGetApp();

        key[0]       = NUL;
        rsaString[0] = NUL;

        while ( ( p = fgets( buf, BUFSIZ - 1, fp ) ) != NULL ) {
            while ( (*p == ' ') || (*p == '\t') )
                p++;
            while ( *p && (p[strlen( p ) - 1] == '\n') )
                p[strlen( p ) - 1] = NUL;
            if ( !(*p) )
                continue;

            if ( GetStringValue( p, "updatePeriod:", temp ) ) {
                m_period = atol( temp );
                if ( m_period <= 0 )
                    m_period = MS_UPDATE_TWITTER;
                continue;
            }

            if ( evalKey( p, "useProxy", ap->m_isUsedProxy ) )
                continue;
            if ( evalKey( p, "proxyServer", ap->m_proxyServer ) )
                continue;
            if ( evalKey( p, "proxyPort", ap->m_proxyPort ) )
                continue;
            if ( evalKey( p, "proxyUsername", ap->m_proxyUserName ) )
                continue;
            if ( evalKey( p, "proxyPassword", ap->m_proxyPassword ) )
                continue;

            if ( evalKey( p, "postBrowsingPages", m_checkBrowsing ) )
                continue;
            if ( evalKey( p, "postMultiServices", m_postMulti ) )
                continue;
            if ( evalKey( p, "useTwitStar", m_useTwitStar ) )
                continue;
            if ( evalKey( p, "useHatenaFotolife", m_useHatenaFotolife ) )
                continue;
            if ( evalKey( p, "hatenaFotolifeWriteLogFile",
                          m_hatenaFotolifeWriteLogFile ) )
                continue;
            if ( evalKey( p, "hatenaFotolifeLogFilename",
                          m_hatenaFotolifeLogFilename ) )
                continue;

            if ( evalKey( p, "useTumblr",  m_useTumblr ) )
                continue;
            if ( evalKey( p, "useTumblr2", m_useTumblr2 ) )
                continue;
            if ( evalKey( p, "tumblrGroup", m_tumblrGroup ) )
                continue;
            if ( evalKey( p, "tumblrName", m_tumblrName ) )
                continue;
            if ( evalKey( p, "tumblrWriteLogFile", m_tumblrWriteLogFile ) )
                continue;
            if ( evalKey( p, "tumblrLogFilename", m_tumblrLogFilename ) )
                continue;

            if ( evalKey( p, "useGyazo", m_useGyazo ) )
                continue;
            if ( evalKey( p, "gyazoID",  m_gyazoID ) )
                continue;
            if ( evalKey( p, "gyazoWriteLogFile", m_gyazoWriteLogFile ) )
                continue;
            if ( evalKey( p, "gyazoLogFilename", m_gyazoLogFilename ) )
                continue;

            if ( evalKey( p, "useFlickr", m_useFlickr ) )
                continue;
            if ( evalKey( p, "flickrWriteLogFile", m_flickrWriteLogFile ) )
                continue;
            if ( evalKey( p, "flickrLogFilename", m_flickrLogFilename ) )
                continue;

            if ( evalKey( p, "useWassrForUpload", m_useWassrForUpload ) )
                continue;
            if ( evalKey( p, "wassrWriteLogFileForUpload",
                          m_wassrWriteLogFileForUpload ) )
                continue;
            if ( evalKey( p, "wassrLogFilenameForUpload",
                          m_wassrLogFilenameForUpload ) )
                continue;

            if ( evalKey( p, "useImetter", m_useImetter ) )
                continue;
            if ( evalKey( p, "nType", m_nType ) )
                continue;
            if ( evalKey( p, "cx",    m_cx ) )
                continue;
            if ( evalKey( p, "cy",    m_cy ) )
                continue;

            if ( evalKey( p, "updateUserIcon", m_updateUserIcon ) )
                continue;

            if ( key[0] == NUL ) {
                if ( evalKey( p, "encryptedKey", key ) ) {
                    size_t  sz = 0;

                    unbase64( (unsigned char *)key,
                              (unsigned char *)rsaString,
                              &sz );
                    rewind( fp );
                }
                continue;
            }

            if ( EvalKeys( p, rsaString ) )
                continue;
        }
        fclose( fp );
    }

    if ( m_twitter )
        m_twitter->SetLogFileSpec();
    if ( m_jaiku )
        m_jaiku->SetLogFileSpec();
    if ( m_wassr )
        m_wassr->SetLogFileSpec();
    if ( m_mogo2 )
        m_mogo2->SetLogFileSpec();
    if ( m_timelog )
        m_timelog->SetLogFileSpec();
    if ( m_haruFm )
        m_haruFm->SetLogFileSpec();
    if ( m_hatenaHaiku )
        m_hatenaHaiku->SetLogFileSpec();

    SwitchMultiPost();
    SwitchTimelineList();
}

void    CChirrupDlg::SaveSetting()
{
    if ((m_twitter     &&
         (m_twitter->m_useOAuth                   ||
          (m_twitter->m_username.GetLength() > 0)    )               ) ||
        (m_jaiku       &&
         (m_jaiku->m_useOAuth                     ||
          (m_jaiku->m_username.GetLength()   > 0)    )               ) ||
        (m_wassr       && (m_wassr->m_username.GetLength()       > 0)) ||
        (m_mogo2       && (m_mogo2->m_username.GetLength()       > 0)) ||
        (m_timelog     && (m_timelog->m_username.GetLength()     > 0)) ||
        (m_haruFm      && (m_haruFm->m_username.GetLength()      > 0)) ||
        (m_hatenaHaiku && (m_hatenaHaiku->m_username.GetLength() > 0))   ) {
        CString settingFilename;
        settingFilename =  m_settingDir;
        settingFilename += m_configFilename;

        mkdir( m_settingDir );

        char            key[BUFSIZ];
        unsigned char   *rsaString;
        bool            encrypted;
        bool            done = false;
        int             retryCount = 0;
        CChirrupApp     *ap = (CChirrupApp *)AfxGetApp();

        do {
            key[0]    = NUL;
            rsaString = NULL;
            encrypted = false;

            FILE    *fp = fopen( settingFilename, "w" ) ;
            if ( fp ) {
                WriteKeys( fp, key, &rsaString, encrypted );

                fprintf( fp, "updatePeriod: %d\n", m_period );

                writeKey( fp, "useProxy", ap->m_isUsedProxy );
                if ( ap->m_isUsedProxy ) {
                    writeKey( fp, "proxyServer", ap->m_proxyServer );
                    writeKey( fp, "proxyPort", ap->m_proxyPort );

                    if ( ap->m_proxyUserName.GetLength() > 0 ) {
                        writeKey( fp, "proxyUsername", ap->m_proxyUserName );
                        if ( ap->m_proxyPassword.GetLength() > 0 )
                            writeKey( fp, "proxyPassword", ap->m_proxyPassword );
                    }
                }
                else {
                    ap->m_proxyPort = 0;
                    writeKey( fp, "proxyPort", ap->m_proxyPort );
                }

                writeKey( fp, "postBrowsingPages", m_checkBrowsing );
                writeKey( fp, "postMultiServices", m_postMulti );
                writeKey( fp, "useTwitStar",       m_useTwitStar );
                writeKey( fp, "useHatenaFotolife", m_useHatenaFotolife );
                writeKey( fp, "hatenaFotolifeWriteLogFile",
                                               m_hatenaFotolifeWriteLogFile );
                if ( m_hatenaFotolifeLogFilename.GetLength() > 0 )
                    writeKey( fp, "hatenaFotolifeLogFilename",
                                               m_hatenaFotolifeLogFilename );

                writeKey( fp, "useTumblr",         m_useTumblr );
                writeKey( fp, "useTumblr2",        m_useTumblr2 );
                if ( m_tumblrGroup.GetLength() > 0 ) {
                    writeKey( fp, "tumblrGroup",   m_tumblrGroup );
                    if ( m_tumblrName.GetLength() > 0 )
                        writeKey( fp, "tumblrName",    m_tumblrName );
                }
                writeKey( fp, "tumblrWriteLogFile",m_tumblrWriteLogFile );
                if ( m_tumblrLogFilename.GetLength() > 0 )
                    writeKey( fp, "tumblrLogFilename", m_tumblrLogFilename );

                writeKey( fp, "useGyazo",          m_useGyazo );
                if ( m_gyazoID[0] )
                    writeKey( fp, "gyazoID",       m_gyazoID );
                writeKey( fp, "gyazoWriteLogFile", m_gyazoWriteLogFile );
                if ( m_gyazoLogFilename.GetLength() > 0 )
                    writeKey( fp, "gyazoLogFilename", m_gyazoLogFilename );

                writeKey( fp, "useFlickr",         m_useFlickr );
                writeKey( fp, "flickrWriteLogFile",m_flickrWriteLogFile );
                if ( m_flickrLogFilename.GetLength() > 0 )
                    writeKey( fp, "flickrLogFilename", m_flickrLogFilename );

                writeKey( fp, "useWassrForUpload",
                          m_useWassrForUpload );
                writeKey( fp, "wassrWriteLogFileForUpload",
                          m_wassrWriteLogFileForUpload );
                if ( m_wassrLogFilenameForUpload.GetLength() > 0 )
                    writeKey( fp, "wassrLogFilenameForUpload",
                              m_wassrLogFilenameForUpload );

                writeKey( fp, "useImetter", m_useImetter );
                writeKey( fp, "nType", m_nType );
                writeKey( fp, "cx",    m_cx );
                writeKey( fp, "cy",    m_cy );

                writeKey( fp, "updateUserIcon", m_updateUserIcon );

                if ( encrypted && key[0] ) {
                    writeKey( fp, "encryptedKey", key );
                    freeRSAkey( rsaString );
                }
                fclose( fp );
            }

            /* パスワードが decode できることを確認 */
            if ( encrypted && key[0] )
                done = CheckEncodedPassword();
            else
                done = true;

            if ( done == false ) {
                retryCount++;
                if ( retryCount >= 27 )
                    break;
            }
        } while ( done == false );
    }

    m_needToSave = false;
}

void    CChirrupDlg::WriteKeys(
            FILE          *fp,      // (I/O) 書き出し先
            char          *key,     // (I)   公開鍵
            unsigned char **secret, // (I/O) 復号に必要な情報(秘密鍵)
            bool          &done )   // (O)   暗号化処理実行済みか否か
{
    if ( m_twitter )
        m_twitter->WriteKeys( fp, key, secret, done );
    if ( m_jaiku )
        m_jaiku->WriteKeys( fp, key, secret, done );
    if ( m_wassr )
        m_wassr->WriteKeys( fp, key, secret, done );
    if ( m_mogo2 )
        m_mogo2->WriteKeys( fp, key, secret, done );
    if ( m_timelog )
        m_timelog->WriteKeys( fp, key, secret, done );
    if ( m_haruFm )
        m_haruFm->WriteKeys( fp, key, secret, done );
    if ( m_hatenaHaiku )
        m_hatenaHaiku->WriteKeys( fp, key, secret, done );

    char    target[BUFSIZ];

    if ( m_hatenaID.GetLength() > 0 ) {
        sprintf( target, "usernameFor%s", "Hatena" );
        writeKey( fp, target, m_hatenaID );
    }

    if ( m_hatenaPassword.GetLength() > 0 ) {
        sprintf( target, "passwordFor%s", "Hatena" );
        writeKey( fp, target, m_hatenaPassword, key, secret, done );
    }

    if ( m_tumblrID.GetLength() > 0 ) {
        sprintf( target, "usernameFor%s", "Tumblr" );
        writeKey( fp, target, m_tumblrID );
    }

    if ( m_tumblrPassword.GetLength() > 0 ) {
        sprintf( target, "passwordFor%s", "Tumblr" );
        writeKey( fp, target, m_tumblrPassword, key, secret, done );
    }

    CString str = m_flickrUserName;
    if ( str.GetLength() > 0 ) {
        sprintf( target, "usernameFor%s", "Flickr" );
        writeKey( fp, target, str );
    }

    str = m_flickrToken;
    if ( str.GetLength() > 0 ) {
        sprintf( target, "tokenFor%s", "Flickr" );
        writeKey( fp, target, str, key, secret, done );
    }
}

bool    CChirrupDlg::CheckKeys(
                        const char          *p,
                        const unsigned char *rsaString,
                        bool                &ret )
{
    bool    cont = false;
    char    encrypted[BUFSIZ];
    bool    checkPasswordForHatena = true;
    bool    checkPasswordForTumblr = true;
    bool    checkTokenForFlickr    = true;
    bool    checkTwitter           = true;
    bool    checkJaiku             = true;
    bool    checkWassr             = true;
    bool    checkMogo2             = true;
    bool    checkTimelog           = true;
    bool    checkHaruFm            = true;
    bool    checkHatenaHaiku       = true;

    encrypted[0] = NUL;
    if ( m_twitter )
        cont = m_twitter->CheckKeys( p, rsaString, encrypted, checkTwitter );
    if ( cont == false )
        if ( m_jaiku )
            cont = m_jaiku->CheckKeys( p, rsaString, encrypted, checkJaiku );
    if ( cont == false )
        if ( m_wassr )
            cont = m_wassr->CheckKeys( p, rsaString, encrypted, checkWassr );
    if ( cont == false )
        if ( m_mogo2 )
            cont = m_mogo2->CheckKeys( p, rsaString, encrypted, checkMogo2 );
    if ( cont == false )
        if ( m_timelog )
            cont = m_timelog->CheckKeys( p, rsaString, encrypted,
                                         checkTimelog );
    if ( cont == false )
        if ( m_haruFm )
            cont = m_haruFm->CheckKeys( p, rsaString, encrypted,
                                        checkHaruFm );
    if ( cont == false )
        if ( m_hatenaHaiku )
            cont = m_hatenaHaiku->CheckKeys( p, rsaString, encrypted,
                                             checkHatenaHaiku );
    if ( cont == false ) {
        char    target[BUFSIZ];

        sprintf( target, "passwordFor%sEncrypted", "Hatena" );
        if ( evalKey( p, target, encrypted ) ) {
            checkKey( m_hatenaPassword,
                      (unsigned char *)encrypted,
                      rsaString,
                      checkPasswordForHatena );
            cont = true;
        }
    }
    if ( cont == false ) {
        char    target[BUFSIZ];

        sprintf( target, "passwordFor%sEncrypted", "Tumblr" );
        if ( evalKey( p, target, encrypted ) ) {
            checkKey( m_tumblrPassword,
                      (unsigned char *)encrypted,
                      rsaString,
                      checkPasswordForTumblr );
            cont = true;
        }
    }
    if ( cont == false ) {
        char    target[BUFSIZ];

        sprintf( target, "tokenFor%sEncrypted", "Flickr" );
        if ( evalKey( p, target, encrypted ) ) {
            checkKey( m_flickrToken,
                      (unsigned char *)encrypted,
                      rsaString,
                      checkTokenForFlickr );
            cont = true;
        }
    }

    ret &= (checkTwitter & checkJaiku  & checkWassr & checkMogo2 &
            checkTimelog & checkHaruFm & checkHatenaHaiku &
            checkPasswordForHatena & checkPasswordForTumblr &
            checkTokenForFlickr);

    return ( cont );
}

bool    CChirrupDlg::EvalKeys(
                        const char          *p,
                        const unsigned char *rsaString )
{
    bool    ret = false;
    char    encrypted[BUFSIZ];

    encrypted[0] = NUL;
    if ( !m_twitter )
        m_twitter = new CTwitterManager();
    ret = m_twitter->EvalKeys( p, rsaString, encrypted );
    if ( ret == false ) {
        if ( !m_jaiku )
            m_jaiku = new CJaikuManager();
        ret = m_jaiku->EvalKeys( p, rsaString, encrypted );
    }
    if ( ret == false ) {
        if ( !m_wassr )
            m_wassr = new CManager(CTwitterTimeline::SVC_WASSR);
        ret = m_wassr->EvalKeys( p, rsaString, encrypted );
    }
    if ( ret == false ) {
        if ( !m_mogo2 )
            m_mogo2 = new CManager(CTwitterTimeline::SVC_MOGO2);
        ret = m_mogo2->EvalKeys( p, rsaString, encrypted );
    }
    if ( ret == false ) {
        if ( !m_timelog )
            m_timelog = new CManager(CTwitterTimeline::SVC_TIMELOG);
        ret = m_timelog->EvalKeys( p, rsaString, encrypted );
    }
    if ( ret == false ) {
        if ( !m_haruFm )
            m_haruFm = new CManager(CTwitterTimeline::SVC_HARUFM);
        ret = m_haruFm->EvalKeys( p, rsaString, encrypted );
    }
    if ( ret == false ) {
        if ( !m_hatenaHaiku )
            m_hatenaHaiku = new CManager(CTwitterTimeline::SVC_HATENAHAIKU);
        ret = m_hatenaHaiku->EvalKeys( p, rsaString, encrypted );
    }
    if ( ret == false ) {
        char    target[BUFSIZ];

        sprintf( target, "usernameFor%s", "Hatena" );
        if ( evalKey( p, target, m_hatenaID ) )
            ret = true;
        if ( ret == false ) {
            sprintf( target, "passwordFor%sEncrypted", "Hatena" );
            if ( evalKey( p, target, encrypted ) ) {
                extractKey( m_hatenaPassword,
                            (unsigned char *)encrypted,
                            (unsigned char *)rsaString );
                ret = true;
            }
        }
    }
    if ( ret == false ) {
        char    target[BUFSIZ];

        sprintf( target, "usernameFor%s", "Tumblr" );
        if ( evalKey( p, target, m_tumblrID ) )
            ret = true;
        if ( ret == false ) {
            sprintf( target, "passwordFor%sEncrypted", "Tumblr" );
            if ( evalKey( p, target, encrypted ) ) {
                extractKey( m_tumblrPassword,
                            (unsigned char *)encrypted,
                            (unsigned char *)rsaString );
                ret = true;
            }
        }
    }
    if ( ret == false ) {
        char    target[BUFSIZ];

        sprintf( target, "usernameFor%s", "Flickr" );
        if ( evalKey( p, target, m_flickrUserName ) )
            ret = true;
        if ( ret == false ) {
            sprintf( target, "tokenFor%sEncrypted", "Flickr" );
            if ( evalKey( p, target, encrypted ) ) {
                CString str = _T("");
                extractKey( str,
                            (unsigned char *)encrypted,
                            (unsigned char *)rsaString );
                strcpy( m_flickrToken, str );
                ret = true;
            }
        }
    }

    return ( ret );
}

bool
CChirrupDlg::CheckEncodedPassword()
{
    bool            ret = true;
    FILE            *fp;
    char            key[BUFSIZ];
    char            buf[BUFSIZ];
    char            *p;
    unsigned char   rsaString[BUFSIZ];

    key[0]       = NUL;
    rsaString[0] = NUL;

    CString settingFilename;
    settingFilename =  m_settingDir;
    settingFilename += m_configFilename;
    if ( ( fp = fopen( settingFilename, "r" ) ) != NULL ) {
        while ( ( p = fgets( buf, BUFSIZ - 1, fp ) ) != NULL ) {
            while ( (*p == ' ') || (*p == '\t') )
                p++;
            while ( *p && (p[strlen( p ) - 1] == '\n') )
                p[strlen( p ) - 1] = NUL;
            if ( !(*p) )
                continue;

            if ( key[0] == NUL ) {
                if ( evalKey( p, "encryptedKey", key ) ) {
                    size_t  sz = 0;

                    unbase64( (unsigned char *)key,
                              (unsigned char *)rsaString,
                              &sz );
                    rewind( fp );
                }
                continue;
            }

            CheckKeys( p, rsaString, ret );
        }
        fclose( fp );
    }

    return ( ret ); /* true: デコード成功, false: デコード失敗 */
}

bool    CChirrupDlg::IsInner( int id, WORD wX, WORD wY )
{
    CRect   rcClient;
    CStatic *s = (CStatic *)GetDlgItem( id );
    bool    ret = false;

    s->GetWindowRect( &rcClient );
    if ( (wX >= rcClient.left) && (wX <= rcClient.right)  &&
         (wY >= rcClient.top)  && (wY <= rcClient.bottom)    )
        ret = true;

    return ( ret );
}

#ifdef  USE_MULTITHREAD_FOR_LOADIMAGE
UINT
LoadImage( LPVOID pParam )
{
    PARAM_LOADIMAGE *p = (PARAM_LOADIMAGE *)pParam;
    UINT            ret = 0;

    p->tp->MoveTimeline();
    p->tp->LoadTimeline( p->dlg, p->cacheDir );

    return ( ret );
}
#endif  /* USE_MULTITHREAD_FOR_LOADIMAGE */

CWinThread  *
CChirrupDlg::DisplayProfImages( CTwitterTimeline *tp )
{
    CWinThread  *pp = NULL;

    if ( !tp || tp->InitTimeline() == false )
        return ( pp );

    mkdir( m_cacheDir );

#ifdef  USE_MULTITHREAD_FOR_LOADIMAGE
    m_paramLoadImage.dlg      = this;
    m_paramLoadImage.tp       = tp;
    m_paramLoadImage.cacheDir = m_cacheDir;

    pp = AfxBeginThread( LoadImage, (void *)&m_paramLoadImage );
    if ( pp )
        pp->m_bAutoDelete = FALSE;
#else
    tp->MoveTimeline();
    tp->LoadTimeline( this, m_cacheDir );
#endif

    return ( pp );
}

void
CChirrupDlg::DisplayTimeline()
{
    CTwitterTimeline    *tp = GetCurrentTimeline();

    if ( tp ) {
        if ( m_updateUserIcon )
            m_loadImageThread = DisplayProfImages( tp );

        m_messageCtrl.m_serviceType = tp->m_serviceType;
        m_messageCtrl.m_timeline    = tp;

        if ( m_useTwitStar || m_useHatenaFotolife ) {
            m_messageCtrl.m_hatenaID       = m_hatenaID;
            m_messageCtrl.m_hatenaPassword = m_hatenaPassword;
        }
        else {
            m_messageCtrl.m_hatenaID       = _T("");
            m_messageCtrl.m_hatenaPassword = _T("");
        }

        if ( m_useTumblr || m_useTumblr2 ) {
            m_messageCtrl.m_tumblrID       = m_tumblrID;
            m_messageCtrl.m_tumblrPassword = m_tumblrPassword;
            m_messageCtrl.m_tumblrGroup    = m_tumblrGroup;
        }
        else {
            m_messageCtrl.m_tumblrID       = _T("");
            m_messageCtrl.m_tumblrPassword = _T("");
        }

        m_messageCtrl.SetWindowText( tp->m_messages.GetLength() > 0
                                            ? tp->m_messages
                                            : _T("") );
        m_messageCtrl.SetStrong( GetCurrentScreenName() );
        if ( tp->m_messages.GetLength() > 0 ) {
            m_messageCtrl.SetWhity();
            m_messageCtrl.SetLink();
            m_messageCtrl.SetFocus();
        }

        if ( m_loadImageThread ) {
            DWORD   exitCode = 0;
            int     status;

            do {
                status = GetExitCodeThread( m_loadImageThread->m_hThread,
                                            &exitCode );
                if ( status == FALSE )
                    break;
                if ( exitCode == STILL_ACTIVE ) {
                    MSG msg;
                    if ( PeekMessage(&msg, 0, WM_PAINT, WM_PAINT, PM_REMOVE) )
                        DispatchMessage( &msg );
                    Sleep( 500 );
                }
            } while ( exitCode == STILL_ACTIVE );

            delete m_loadImageThread;
            m_loadImageThread = NULL;
        }
    }
}

char *CChirrupDlg::GetSceenNameOfFriend( int idx )
{
    static char         s[MAX_KEYLENGTH];
    int                 index = idx - IDC_FRIEND001;
    CTwitterTimeline    *tp = GetCurrentTimeline();

    strcpy( s, "???" );
    if ( tp && tp->m_users && (tp->m_users)[index].id[0] )
        if ( tp->m_serviceType == CTwitterTimeline::SVC_WASSR )
            strcpy( s, (tp->m_users)[index].name );
        else
            strcpy( s, (tp->m_users)[index].screenName );

    return ( s );
}

void CChirrupDlg::PostMessageToFriend( int idx )
{
    int                 index = idx - IDC_FRIEND001;
    CTwitterTimeline    *tp   = GetCurrentTimeline();

    if ( tp && tp->m_users && (tp->m_users)[index].id[0] ) {
        CString addr = _T("");

        if ( tp->m_serviceType == CTwitterTimeline::SVC_TIMELOG ) {
            int     i;
            bool    found      = false;

            for ( i = 0; i < tp->m_numOfStats; i++ ) {
                if ( !strcmp( (tp->m_users)[index].lastStatus,
                              tp->m_stat[i].text )             ) {
                    found = true;
                    break;
                }
            }

            if ( found ) {
                addr += _T(">>");
                addr += tp->m_stat[i].id;
                addr += _T(" ");
            }
            addr += _T("@");
            addr += (tp->m_users)[index].id; // スクリーン名ではなく、ユーザID
        }
        else if ( tp->m_serviceType == CTwitterTimeline::SVC_WASSR )
            addr = (tp->m_users)[index].name;
        else
            addr = (tp->m_users)[index].screenName;

        CEdit   *cp = (CEdit *)GetDlgItem( IDC_MONOLOGUE );
        SetAddrOnMonologue( addr, cp );

        cp->SetFocus();
        cp->SetSel(0, -1, TRUE);
        cp->SetSel(-1, -1, FALSE);
    }	
}


bool CChirrupDlg::ExecutePost( CString monologue, CString timelineType )
{
    bool    ret  = false;
    bool    ret1 = false;
    bool    ret2 = false;
    bool    ret3 = false;
    bool    ret4 = false;
    bool    ret5 = false;
    bool    ret6 = false;
    bool    ret7 = false;

    CEdit   *cp = (CEdit *)GetDlgItem( IDC_MONOLOGUE );
    CString str;
    cp->GetWindowText( str );
    if ( str == "" )
        return false;

    if ( monologue.GetLength() > 0 ) {
     // CWaitCursor         cur;    // マウスカーソルを砂時計表示
        ProceedingDialog    *pdlg = NULL;

        ShowServiceName( false );
        CStatic *sp = (CStatic *)GetDlgItem( IDC_EXECUTING );
        sp->SetWindowText( "発言を投稿します……" );
        sp->ShowWindow( SW_SHOW );

        if ( m_useImetter ) {
            sp->SetWindowText( "いめったー: 画像を取得中……" );
            GetImageViaImetter( monologue, pdlg );
            sp->SetWindowText( "発言を投稿します……" );
        }

        if ( m_jaiku ) {
            if ( (m_postMulti && m_jaiku->m_simultaneousPost) ||
                 !strncmp( timelineType, "Jaiku:", 6 )           )
                if ( m_jaiku->m_useOAuth                         ||
                     ((m_jaiku->m_username.GetLength() > 0) &&
                      (m_jaiku->m_password.GetLength() > 0)    )    )
                    ret1 = m_jaiku->ExecutePost( monologue, sp, pdlg );
        }
        if ( m_wassr ) {
            if ( (m_postMulti && m_wassr->m_simultaneousPost) ||
                 !strncmp( timelineType, "Wassr:", 6 )           )
                if ( (m_wassr->m_username.GetLength() > 0) &&
                     (m_wassr->m_password.GetLength() > 0)    )
                    ret2 = m_wassr->ExecutePost( monologue, sp, pdlg );
        }
        if ( m_mogo2 ) {
            if ( (m_postMulti && m_mogo2->m_simultaneousPost) ||
                 !strncmp( timelineType, "もごもご:", 9 )        )
                if ( (m_mogo2->m_username.GetLength() > 0) &&
                     (m_mogo2->m_password.GetLength() > 0)    )
                    ret3 = m_mogo2->ExecutePost( monologue, sp, pdlg );
        }
        if ( m_timelog ) {
            if ( (m_postMulti && m_timelog->m_simultaneousPost) ||
                 !strncmp( timelineType, "Timelog:", 8 )           )
                if ( (m_timelog->m_username.GetLength() > 0) &&
                     (m_timelog->m_password.GetLength() > 0)    )
                    ret4 = m_timelog->ExecutePost( monologue, sp, pdlg );
        }
        if ( m_haruFm ) {
            if ( (m_postMulti && m_haruFm->m_simultaneousPost) ||
                 !strncmp( timelineType, "Haru.fm:", 8 )          )
                if ( (m_haruFm->m_username.GetLength() > 0) &&
                     (m_haruFm->m_password.GetLength() > 0)    )
                    ret5 = m_haruFm->ExecutePost( monologue, sp, pdlg );
        }
        if ( m_hatenaHaiku ) {
            if ( (m_postMulti && m_hatenaHaiku->m_simultaneousPost) ||
                 !strncmp( timelineType, "はてなハイク:", 13 )          )
                if ( (m_hatenaHaiku->m_username.GetLength() > 0) &&
                     (m_hatenaHaiku->m_password.GetLength() > 0)    )
                    ret6 = m_hatenaHaiku->ExecutePost( monologue, sp, pdlg );
        }
        if ( m_twitter ) {
            if ( (m_postMulti && m_twitter->m_simultaneousPost) ||
                 !strncmp( timelineType, "Twitter:", 8 )           )
                if ( m_twitter->m_useOAuth                         ||
                     ((m_twitter->m_username.GetLength() > 0) &&
                      (m_twitter->m_password.GetLength() > 0)    )    )
                    ret7 = m_twitter->ExecutePost( monologue, sp, pdlg );
        }

        CButton *bp = (CButton *)GetDlgItem( IDC_POST_MONOLOGUE );
        bp->GetWindowText( str );
        if ( !str.Compare( _T("キャンセル") ) ) {
            cp->SetWindowText( _T("") );
            cp->SetReadOnly( FALSE );
            bp->SetWindowText( m_useImetter ? "いめったー" : "発言" );
        }

        sp->SetWindowText( "" );
        sp->ShowWindow( SW_HIDE );
        ShowServiceName( true );
    }

    ret = (ret1 || ret2 || ret3 || ret4 || ret5 || ret6 || ret7);

    return ( ret );
}

UINT
_ExecutePost( LPVOID pParam )
{
    PARAM_POST  *p  = (PARAM_POST *)pParam;
    CWinThread  *tp;
    UINT        ret = 0;

    if ( p && p->dlg && (p->monologue.GetLength() > 0) ) {
        bool    go = false;

        do {
            p->dlg->EnterCriticalSection();
            tp = p->dlg->m_updateThread;
            p->dlg->LeaveCriticalSection();

            if ( tp )
                Sleep( MS_THREAD_POST_TWITTER / 2 );
            else
                go = true;
        } while ( go == false );

        p->ret = p->dlg->ExecutePost( p->monologue, p->timelineType );
    }

    return ( ret );
}

bool CChirrupDlg::PostMonologue( PARAM_POST *param )
{
    bool        ret = false;
    CWinThread  *p;

    EnterCriticalSection();
    p = m_postThread;
    LeaveCriticalSection();

    if ( p ) {
        if ( param == &(param->dlg->m_postTweet) )
            MessageBox( "いま、ちょっと忙しいの。あとにしてね!    ",
                        "ついったん",
                        MB_OK|MB_ICONWARNING );
        return ( ret );
    }

    EnterCriticalSection();
    m_postThread = AfxBeginThread( _ExecutePost, (void *)param );
    if ( m_postThread ) {
        m_postThread->m_bAutoDelete = FALSE;
        SetTimer( ID_THREAD_POST_TWITTER,
                  MS_THREAD_POST_TWITTER,
                  NULL );
        ret = true;
    }
    LeaveCriticalSection();

    return ( ret );
}


void CChirrupDlg::ShowFriendProfile( int idx )
{
    int                 index = idx - IDC_FRIEND001;
    CFriendDialog       dlg;
    CTwitterTimeline    *tp = GetCurrentTimeline();

    if ( tp && tp->m_users ) {
        dlg.m_user             = (tp->m_users)[index];
        dlg.m_user.bitmap      = NULL; /* @@ */
        dlg.m_cacheDir         = m_cacheDir;
        dlg.m_mode             = CFriendDialog::SHOW_PROFILE;
        dlg.m_username         = _T("");
        dlg.m_password         = _T("");
        dlg.m_useOAuth         = false;
        dlg.m_oauthToken       = _T("");
        dlg.m_oauthTokenSecret = _T("");
        dlg.m_lastStatusCtrl.m_chirrupDlg = this;
        dlg.DoModal();
    }
}

void CChirrupDlg::ShowWebPage( int idx )
{
    int                 index = idx - IDC_FRIEND001;
    CTwitterTimeline    *tp = GetCurrentTimeline();

    if ( tp && tp->m_users ) {
        if ( (tp->m_users)[index].url[0] ) {
            ShellExecute( NULL, "open", (tp->m_users)[index].url,
                          NULL, NULL, SW_SHOWNORMAL );
        }
        else {
            CString cmd = _T("");

            if ( strstr((tp->m_users)[index].profileImageURL, "mogo2.jp") ) {
	            cmd = _T("http://mogo2.jp/");
    	        cmd += (tp->m_users)[index].id;
            }
            else {
	            cmd = _T("http://twitter.com/");
    	        cmd += (tp->m_users)[index].screenName;
            }
            ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
        }
    }
}

void CChirrupDlg::ShowFavorites( int idx )
{
    int                 index = idx - IDC_FRIEND001;
    CTwitterTimeline    *tp = GetCurrentTimeline();
    CString             cmd = _T("");

    if ( tp && tp->m_users ) {
	    cmd = _T("http://twitter.com/");
    	cmd += (tp->m_users)[index].screenName;
        cmd += _T("/favorites");
        ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
    }
}

void CChirrupDlg::SendDirectMessageToFriend( int idx )
{
    int                 index = idx - IDC_FRIEND001;
    CDirectMessage      dlg;
    CTwitterTimeline    *tp = GetCurrentTimeline();

    if ( tp && tp->m_users ) {
        switch ( tp->m_serviceType ) {
        case CTwitterTimeline::SVC_TWITTER:
            if ( m_twitter ) {
                dlg.m_username         = m_twitter->m_username;
                dlg.m_password         = m_twitter->m_password;
                dlg.m_useOAuth         = m_twitter->m_useOAuth;
                dlg.m_oauthToken       = m_twitter->m_oauthToken;
                dlg.m_oauthTokenSecret = m_twitter->m_oauthTokenSecret;
            }
            break;
        case CTwitterTimeline::SVC_TIMELOG:
            if ( m_timelog ) {
                dlg.m_username = m_timelog->m_username;
                dlg.m_password = m_timelog->m_password;
            }
            break;
        default:
            return;
            // statement not reached
            break;
        }

        dlg.m_serviceType = tp->m_serviceType;
        dlg.m_user        = (tp->m_users)[index];
        dlg.m_cacheDir    = m_cacheDir;
        dlg.DoModal();
    }
}

void CChirrupDlg::AddFriend( int idx )
{
    int                 index = idx - IDC_FRIEND001;
    CFriendDialog       dlg;
    CTwitterTimeline    *tp = GetCurrentTimeline();

    if ( tp && tp->m_users && (m_twitter || m_wassr) ) {
        dlg.m_user        = (tp->m_users)[index];
        dlg.m_user.bitmap = NULL; /* @@ */
        dlg.m_cacheDir    = m_cacheDir;
        dlg.m_mode        = CFriendDialog::ADD_FRIEND;

        if ( !strncmp( m_timelineType, "Twitter: ", 9 ) && m_twitter ) {
            dlg.m_username         = m_twitter->m_username;
            dlg.m_password         = m_twitter->m_password;
            dlg.m_useOAuth         = m_twitter->m_useOAuth;
            dlg.m_oauthToken       = m_twitter->m_oauthToken;
            dlg.m_oauthTokenSecret = m_twitter->m_oauthTokenSecret;
        }
        else if ( !strncmp( m_timelineType, "Wassr: ", 7 ) && m_wassr ) {
            dlg.m_username = m_wassr->m_username;
            dlg.m_password = m_wassr->m_password;
        }
        dlg.m_lastStatusCtrl.m_chirrupDlg = this;
        dlg.DoModal();
    }
}

void CChirrupDlg::RemoveFriend( int idx )
{
    int                 index = idx - IDC_FRIEND001;
    CFriendDialog       dlg;
    CTwitterTimeline    *tp = GetCurrentTimeline();

    if ( tp && tp->m_users && (m_twitter || m_wassr) ) {
        dlg.m_user        = (tp->m_users)[index];
        dlg.m_user.bitmap = NULL; /* @@ */
        dlg.m_cacheDir    = m_cacheDir;
        dlg.m_mode        = CFriendDialog::REMOVE_FRIEND;

        if ( !strncmp( m_timelineType, "Twitter: ", 9 ) && m_twitter ) {
            dlg.m_username         = m_twitter->m_username;
            dlg.m_password         = m_twitter->m_password;
            dlg.m_useOAuth         = m_twitter->m_useOAuth;
            dlg.m_oauthToken       = m_twitter->m_oauthToken;
            dlg.m_oauthTokenSecret = m_twitter->m_oauthTokenSecret;
        }
        else if ( !strncmp( m_timelineType, "Wassr: ", 7 ) && m_wassr ) {
            dlg.m_username = m_wassr->m_username;
            dlg.m_password = m_wassr->m_password;
        }
        dlg.m_lastStatusCtrl.m_chirrupDlg = this;
        dlg.DoModal();
    }
}

void CChirrupDlg::GetProxyInfo(
            bool           &p_isUsedProxy,
            CString        &p_proxyServer,
            unsigned short &p_proxyPort,
            CString        &p_proxyUserName,
            CString        &p_proxyPassword
        )
{
    BOOL            useProxy  = FALSE;
    char            proxyServer[MAX_SERVERNAME];
    unsigned short  proxyPort = 0;
    char            proxyUsername[MAX_NAMELEN + 1];
    char            proxyPassword[MAX_NAMELEN + 1];

    setUseProxy( FALSE );
    proxyServer[0]   = NUL;
    proxyUsername[0] = NUL;
    proxyPassword[0] = NUL;
    p_isUsedProxy    = false;

    getProxyInfo( &useProxy,
                  proxyServer,   &proxyPort,
                  proxyUsername, proxyPassword );

    if ( useProxy ) {
        p_isUsedProxy = true;
        p_proxyServer = proxyServer;
        p_proxyPort   = proxyPort;

        if ( proxyUsername[0] ) {
            p_proxyUserName = proxyUsername;
            if ( proxyPassword[0] )
                p_proxyPassword = proxyPassword;
        }
    }
    else
        p_proxyPort = 0;
}

void CChirrupDlg::SwitchMultiPost()
{
    CButton *bp = (CButton *)GetDlgItem( IDC_CHECK_MULTIPOST );

    int flag1 = (m_twitter                                       &&
                 (m_twitter->m_useOAuth                       ||
                  ((m_twitter->m_username.GetLength() > 0) &&
                   (m_twitter->m_password.GetLength() > 0)   )  )  ) ? 1 : 0;
    int flag2 = (m_jaiku                                 &&
                 (m_jaiku->m_useOAuth                         ||
                  ((m_jaiku->m_username.GetLength()   > 0) &&
                   (m_jaiku->m_password.GetLength()   > 0)   )  )  ) ? 1 : 0;
    int flag3 = (m_wassr                                 &&
                 (m_wassr->m_username.GetLength() > 0)   &&
                 (m_wassr->m_password.GetLength() > 0)     ) ? 1 : 0;
    int flag4 = (m_mogo2                                 &&
                 (m_mogo2->m_username.GetLength() > 0)   &&
                 (m_mogo2->m_password.GetLength() > 0)     ) ? 1 : 0;
    int flag5 = (m_timelog                               &&
                 (m_timelog->m_username.GetLength() > 0) &&
                 (m_timelog->m_password.GetLength() > 0)   ) ? 1 : 0;
    int flag6 = (m_haruFm                                &&
                 (m_haruFm->m_username.GetLength() > 0)  &&
                 (m_haruFm->m_password.GetLength() > 0)    ) ? 1 : 0;
    int flag7 = (m_hatenaHaiku                                &&
                 (m_hatenaHaiku->m_username.GetLength() > 0)  &&
                 (m_hatenaHaiku->m_password.GetLength() > 0)    ) ? 1 : 0;

    if ( flag1 + flag2 + flag3 + flag4 + flag5 + flag6 + flag7 >= 2 )
        bp->EnableWindow( TRUE );
    else
        bp->EnableWindow( FALSE );
}

void CChirrupDlg::SwitchTimelineList()
{
    int location = m_timelineTypeList.GetCurSel();
    if ( location >= 0 )
    	m_timelineTypeList.GetLBText( location, m_timelineType );

    m_timelineTypeList.ResetContent();
    if ( m_twitter ) {
        if ( m_twitter->m_sFriendsTimeline.checkTimeline )
            m_timelineTypeList.AddString( "Twitter: Friends" );
        if ( m_twitter->m_sPublicTimeline.checkTimeline )
            m_timelineTypeList.AddString( "Twitter: Public" );
        if ( m_twitter->m_sUserTimeline.checkTimeline )
            m_timelineTypeList.AddString( "Twitter: User" );
        if ( m_twitter->m_sReplies.checkTimeline )
            m_timelineTypeList.AddString( "Twitter: Replies" );
    }

    if ( m_jaiku ) {
        if ( m_jaiku->m_sFriendsTimeline.checkTimeline )
            m_timelineTypeList.AddString( "Jaiku: Friends" );
        if ( m_jaiku->m_sPublicTimeline.checkTimeline )
            m_timelineTypeList.AddString( "Jaiku: Public" );
        if ( m_jaiku->m_sUserTimeline.checkTimeline )
            m_timelineTypeList.AddString( "Jaiku: User" );
    }

    if ( m_wassr ) {
        if ( m_wassr->m_sFriendsTimeline.checkTimeline )
            m_timelineTypeList.AddString( "Wassr: Friends" );
        if ( m_wassr->m_sPublicTimeline.checkTimeline )
            m_timelineTypeList.AddString( "Wassr: Public" );
        if ( m_wassr->m_sUserTimeline.checkTimeline )
            m_timelineTypeList.AddString( "Wassr: User" );
    }

    if ( m_mogo2 ) {
        if ( m_mogo2->m_sFriendsTimeline.checkTimeline )
            m_timelineTypeList.AddString( "もごもご: Friends" );
        if ( m_mogo2->m_sPublicTimeline.checkTimeline )
            m_timelineTypeList.AddString( "もごもご: Public" );
        if ( m_mogo2->m_sUserTimeline.checkTimeline )
            m_timelineTypeList.AddString( "もごもご: User" );
    }

    if ( m_timelog ) {
        if ( m_timelog->m_sFriendsTimeline.checkTimeline )
            m_timelineTypeList.AddString( "Timelog: Friends" );
        if ( m_timelog->m_sPublicTimeline.checkTimeline )
            m_timelineTypeList.AddString( "Timelog: Public" );
        if ( m_timelog->m_sUserTimeline.checkTimeline )
            m_timelineTypeList.AddString( "Timelog: User" );
    }

    if ( m_haruFm ) {
        if ( m_haruFm->m_sFriendsTimeline.checkTimeline )
            m_timelineTypeList.AddString( "Haru.fm: Friends" );
        if ( m_haruFm->m_sPublicTimeline.checkTimeline )
            m_timelineTypeList.AddString( "Haru.fm: Public" );
        if ( m_haruFm->m_sUserTimeline.checkTimeline )
            m_timelineTypeList.AddString( "Haru.fm: User" );
    }

    if ( m_hatenaHaiku ) {
        if ( m_hatenaHaiku->m_sFriendsTimeline.checkTimeline )
            m_timelineTypeList.AddString( "はてなハイク: Friends" );
        if ( m_hatenaHaiku->m_sPublicTimeline.checkTimeline )
            m_timelineTypeList.AddString( "はてなハイク: Public" );
        if ( m_hatenaHaiku->m_sUserTimeline.checkTimeline )
            m_timelineTypeList.AddString( "はてなハイク: User" );
    }

    if ( m_timelineType.GetLength() == 0 )
        m_timelineType = _T("Twitter: Friends");

    location = m_timelineTypeList.FindString( -1, m_timelineType );
    if ( location == -1 )
        if ( m_timelineTypeList.GetCount() > 0 )
            location = 0;
    if ( location >= 0 ) {
        m_timelineTypeList.SetCurSel( location );
    	m_timelineTypeList.GetLBText( location, m_timelineType );
    }
}

void CChirrupDlg::SwitchTimelineFacilities()
{
    CButton *bp = (CButton *)GetDlgItem( IDC_RECV_DIRECTMESSAGE );
    bp->SetWindowText("DM受信");

    CButton *cp = (CButton *)GetDlgItem( IDC_CHECK_BROWSING );
    CEdit   *ep = (CEdit *)GetDlgItem( IDC_MONOLOGUE );

    m_messageCtrl.m_username = _T("");
    m_messageCtrl.m_password = _T("");
    m_messageCtrl.m_twitterUseOAuth         = false;
    m_messageCtrl.m_twitterOauthToken       = _T("");
    m_messageCtrl.m_twitterOauthTokenSecret = _T("");

    if ( !strncmp( m_timelineType, "Jaiku: ", 7 ) &&
         m_jaiku                                  &&
         (m_jaiku->m_useOAuth                         ||
          ((m_jaiku->m_username.GetLength() > 0) &&
           (m_jaiku->m_password.GetLength() > 0)    )    )    )  {
        bp->EnableWindow( FALSE );
        cp->SetWindowText(
                _T("Webブラウザで閲覧中の URL を Jaiku に送信する"));
        ep->SetLimitText( 160 );// 最大 160 バイト (推奨は140バイト以下)

        m_messageCtrl.m_username = m_jaiku->m_username;
        m_messageCtrl.m_password = m_jaiku->m_password;
    }
    else if ( !strncmp( m_timelineType, "Wassr: ", 7 ) &&
              m_wassr                                  &&
              (m_wassr->m_username.GetLength() > 0)    &&
              (m_wassr->m_password.GetLength() > 0)       ) {
        bp->SetWindowText("チャンネル");
        bp->EnableWindow( TRUE );

        cp->SetWindowText(
                _T("Webブラウザで閲覧中の URL を Wassr に送信する"));
        ep->SetLimitText( 256 );    // 暫定的に 256 を設定

        m_messageCtrl.m_username = m_wassr->m_username;
        m_messageCtrl.m_password = m_wassr->m_password;
    }
    else if ( !strncmp( m_timelineType, "もごもご: ", 10 ) &&
              m_mogo2                                      &&
              (m_mogo2->m_username.GetLength() > 0)        &&
              (m_mogo2->m_password.GetLength() > 0)           ) {
        bp->EnableWindow( FALSE );
        cp->SetWindowText(
                _T("Webブラウザで閲覧中の URL を もごもご に送信する"));
        ep->SetLimitText( 256 );    // 暫定的に 256 を設定

        m_messageCtrl.m_username = m_mogo2->m_username;
        m_messageCtrl.m_password = m_mogo2->m_password;
    }
    else if ( !strncmp( m_timelineType, "Timelog: ", 9 ) &&
              m_timelog                                  &&
              (m_timelog->m_username.GetLength() > 0)    &&
              (m_timelog->m_password.GetLength() > 0)       ) {
        bp->EnableWindow( TRUE );
        cp->SetWindowText(
                _T("Webブラウザで閲覧中の URL を Timelog に送信する"));
        ep->SetLimitText( 250 );// API 経由では最大 250 バイト

        m_messageCtrl.m_username = m_timelog->m_username;
        m_messageCtrl.m_password = m_timelog->m_password;
    }
    else if ( !strncmp( m_timelineType, "Haru.fm: ", 9 ) &&
              m_haruFm                                   &&
              (m_haruFm->m_username.GetLength() > 0)     &&
              (m_haruFm->m_password.GetLength() > 0)        ) {
        bp->EnableWindow( FALSE );
        cp->SetWindowText(
                _T("Webブラウザで閲覧中の URL を Haru.fm に送信する"));
        ep->SetLimitText( 256 );    // 暫定的に 256 を設定

        m_messageCtrl.m_username = m_haruFm->m_username;
        m_messageCtrl.m_password = m_haruFm->m_password;
    }
    else if ( !strncmp( m_timelineType, "はてなハイク: ", 14 ) &&
              m_hatenaHaiku                                    &&
              (m_hatenaHaiku->m_username.GetLength() > 0)      &&
              (m_hatenaHaiku->m_password.GetLength() > 0)        ) {
        bp->EnableWindow( FALSE );
        cp->SetWindowText(
                _T("Webブラウザで閲覧中の URL を はてなハイク に送信する"));
        ep->SetLimitText( 256 );    // 暫定的に 256 を設定

        m_messageCtrl.m_username = m_hatenaHaiku->m_username;
        m_messageCtrl.m_password = m_hatenaHaiku->m_password;
    }
    else if ( !strncmp( m_timelineType, "Twitter: ", 9 )          &&
              m_twitter                                           &&
              (m_twitter->m_useOAuth                         ||
               ((m_twitter->m_username.GetLength() > 0) &&
                (m_twitter->m_password.GetLength() > 0)    )    )    )  {
        bp->EnableWindow( TRUE );
        cp->SetWindowText(
                _T("Webブラウザで閲覧中の URL を Twitter に送信する"));
        ep->SetLimitText( 320 );// 最大 160 文字 (推奨は140文字以下)

        m_messageCtrl.m_username = m_twitter->m_username;
        m_messageCtrl.m_password = m_twitter->m_password;
        m_messageCtrl.m_twitterUseOAuth         = m_twitter->m_useOAuth;
        m_messageCtrl.m_twitterOauthToken       = m_twitter->m_oauthToken;
        m_messageCtrl.m_twitterOauthTokenSecret = m_twitter->m_oauthTokenSecret;
    }

    if ( m_showServiceName )
        ShowServiceName( true );
}

void CChirrupDlg::SwitchTitle()
{
    bool    needToSave = false;
    CString screenName = _T("???");

    if ( !isNecessaryToCheckProxyInfo() &&
         m_twitter && (m_twitter->m_screenName.GetLength() == 0) ) {
        m_twitter->GetScreenName();
        needToSave = true;
    }

    if ( !isNecessaryToCheckProxyInfo() &&
         m_jaiku && (m_jaiku->m_screenName.GetLength() == 0) ) {
        m_jaiku->GetScreenName();
        needToSave = true;
    }
    if ( !isNecessaryToCheckProxyInfo() &&
         m_wassr && (m_wassr->m_screenName.GetLength() == 0) ) {
        m_wassr->GetScreenName();
        needToSave = true;
    }
    if ( !isNecessaryToCheckProxyInfo() &&
         m_mogo2 && (m_mogo2->m_screenName.GetLength() == 0) ) {
        m_mogo2->GetScreenName();
        needToSave = true;
    }
    if ( !isNecessaryToCheckProxyInfo() &&
         m_timelog && (m_timelog->m_screenName.GetLength() == 0) ) {
        m_timelog->GetScreenName();
        needToSave = true;
    }
    if ( !isNecessaryToCheckProxyInfo() &&
         m_haruFm && (m_haruFm->m_screenName.GetLength() == 0) ) {
        m_haruFm->GetScreenName();
        needToSave = true;
    }
    if ( !isNecessaryToCheckProxyInfo() &&
         m_hatenaHaiku && (m_hatenaHaiku->m_screenName.GetLength() == 0) ) {
        m_hatenaHaiku->GetScreenName();
        needToSave = true;
    }

    int location = m_timelineTypeList.GetCurSel();
    if ( location >= 0 ) {
    	m_timelineTypeList.GetLBText( location, m_timelineType );
        if ( !strncmp( m_timelineType, "Twitter: ", 9 ) && m_twitter ) {
            screenName = m_twitter->m_screenName.GetLength() > 0
                            ? m_twitter->m_screenName
                            : m_twitter->m_username;
        }
        else if ( !strncmp( m_timelineType, "Jaiku: ", 7 ) && m_jaiku ) {
            screenName = m_jaiku->m_screenName.GetLength() > 0
                            ? m_jaiku->m_screenName
                            : m_jaiku->m_username;
        }
        else if ( !strncmp( m_timelineType, "Wassr: ", 7 ) && m_wassr ) {
            screenName = m_wassr->m_screenName.GetLength() > 0
                            ? m_wassr->m_screenName
                            : m_wassr->m_username;
        }
        else if ( !strncmp( m_timelineType, "もごもご: ", 10 ) && m_mogo2 ) {
            screenName = m_mogo2->m_screenName.GetLength() > 0
                            ? m_mogo2->m_screenName
                            : m_mogo2->m_username;
        }
        else if ( !strncmp( m_timelineType, "Timelog: ", 9 ) && m_timelog ) {
            screenName = m_timelog->m_screenName.GetLength() > 0
                            ? m_timelog->m_screenName
                            : m_timelog->m_username;
        }
        else if ( !strncmp( m_timelineType, "Haru.fm: ", 9 ) && m_haruFm ) {
            screenName = m_haruFm->m_screenName.GetLength() > 0
                            ? m_haruFm->m_screenName
                            : m_haruFm->m_username;
        }
        else if ( !strncmp( m_timelineType, "はてなハイク: ", 14 ) &&
                  m_hatenaHaiku ) {
            screenName = m_hatenaHaiku->m_screenName.GetLength() > 0
                            ? m_hatenaHaiku->m_screenName
                            : m_hatenaHaiku->m_username;
        }
    }
    else {
        if ( m_twitter                                     &&
             (m_twitter->m_useOAuth                   ||
              (m_twitter->m_username.GetLength() > 0)    )    )
            screenName = m_twitter->m_screenName.GetLength() > 0
                            ? m_twitter->m_screenName
                            : m_twitter->m_username;
        else if ( m_jaiku                                    &&
                  (m_jaiku->m_useOAuth                   ||
                   (m_jaiku->m_username.GetLength() > 0)    )   )
            screenName = m_jaiku->m_screenName.GetLength() > 0
                            ? m_jaiku->m_screenName
                            : m_jaiku->m_username;
        else if ( m_wassr && (m_wassr->m_username.GetLength() > 0) )
            screenName = m_wassr->m_screenName.GetLength() > 0
                            ? m_wassr->m_screenName
                            : m_wassr->m_username;
        else if ( m_mogo2 && (m_mogo2->m_username.GetLength() > 0) )
            screenName = m_mogo2->m_screenName.GetLength() > 0
                            ? m_mogo2->m_screenName
                            : m_mogo2->m_username;
        else if ( m_timelog && (m_timelog->m_username.GetLength() > 0) )
            screenName = m_timelog->m_screenName.GetLength() > 0
                            ? m_timelog->m_screenName
                            : m_timelog->m_username;
        else if ( m_haruFm && (m_haruFm->m_username.GetLength() > 0) )
            screenName = m_haruFm->m_screenName.GetLength() > 0
                            ? m_haruFm->m_screenName
                            : m_haruFm->m_username;
        else if ( m_hatenaHaiku && (m_hatenaHaiku->m_username.GetLength() > 0) )
            screenName = m_hatenaHaiku->m_screenName.GetLength() > 0
                            ? m_hatenaHaiku->m_screenName
                            : m_hatenaHaiku->m_username;
    }

    CString version;
    version.LoadString( IDS_VERSION );
    CString title = _T("chirrup Ver ");
    title += version;
    title += _T(" - @");
    title += screenName;
    SetWindowText( title );

    char temp[BUFSIZ];
    size_t sz = sizeof ( m_stNotifyIcon.szTip );
    sprintf( temp, "%s\r\n[%s]", title, (const char *)m_timelineType );
    strncpy( m_stNotifyIcon.szTip, temp, sz - 1 );
    m_stNotifyIcon.szTip[sz - 1] = NUL;
    Shell_NotifyIcon( NIM_MODIFY, &m_stNotifyIcon );

    if ( needToSave ) {
        m_needToSave = true;
        SaveSetting();
    }
}

void CChirrupDlg::SwitchCapture()
{
    CButton *p = (CButton *)GetDlgItem( IDC_START_CAPTURE );
    if ( m_useTumblr2        ||
         m_useGyazo          ||
         m_useFlickr         ||
         m_useHatenaFotolife ||
         m_useWassrForUpload    ) {
        p->EnableWindow( TRUE );
        p->ShowWindow( SW_SHOW );
    }
    else {
        p->EnableWindow( FALSE );
        p->ShowWindow( SW_HIDE );
    }
}

void CChirrupDlg::SwitchImetter()
{
    CButton *bp = (CButton *)GetDlgItem( IDC_POST_MONOLOGUE );
    bp->SetWindowText( m_useImetter ? "いめったー" : "発言" );
}

void CChirrupDlg::SetTwitter(
                    CString username,
                    CString password,
                    CString oauthToken,
                    CString oauthTokenSecret,
                    BOOL useOAuth,
                    BOOL useBASIC,
                    BOOL checkMultiPost,
                    TIMELINE_INFO sFriendsTimeline,
                    TIMELINE_INFO sPublicTimeline,
                    TIMELINE_INFO sUserTimeline,
                    TIMELINE_INFO sReplies
                )
{
    ASSERT( m_twitter );
    m_twitter->SetConfig( username, password,
                          oauthToken, oauthTokenSecret,
                          useOAuth, useBASIC,
                          checkMultiPost,
                          sFriendsTimeline,
                          sPublicTimeline,
                          sUserTimeline,
                          sReplies );
}

void CChirrupDlg::GetTwitter(
                    CString &username,
                    CString &password,
                    CString &oauthToken,
                    CString &oauthTokenSecret,
                    BOOL &useOAuth,
                    BOOL &useBASIC,
                    BOOL &checkMultiPost,
                    TIMELINE_INFO &sFriendsTimeline,
                    TIMELINE_INFO &sPublicTimeline,
                    TIMELINE_INFO &sUserTimeline,
                    TIMELINE_INFO &sReplies
                )
{
    if ( !m_twitter )
        m_twitter = new CTwitterManager();
    m_twitter->GetConfig( username, password,
                          oauthToken, oauthTokenSecret,
                          useOAuth, useBASIC,
                          checkMultiPost,
                          sFriendsTimeline,
                          sPublicTimeline,
                          sUserTimeline,
                          sReplies );
}

void CChirrupDlg::SetJaiku(
                  CString username,
                  CString personalKey,
                  CString oauthToken,
                  CString oauthTokenSecret,
                  BOOL useOAuth,
                  BOOL useBASIC,
                  BOOL checkMultiPost,
                  TIMELINE_INFO sFriendsTimeline,
                  TIMELINE_INFO sPublicTimeline,
                  TIMELINE_INFO sUserTimeline
              )
{
    ASSERT( m_jaiku );
    m_jaiku->SetConfig( username, personalKey,
                        oauthToken, oauthTokenSecret,
                        useOAuth, useBASIC,
                        checkMultiPost,
                        sFriendsTimeline,
                        sPublicTimeline,
                        sUserTimeline );
}

void CChirrupDlg::GetJaiku(
                  CString &username,
                  CString &personalKey,
                  CString &oauthToken,
                  CString &oauthTokenSecret,
                  BOOL &useOAuth,
                  BOOL &useBASIC,
                  BOOL &checkMultiPost,
                  TIMELINE_INFO &sFriendsTimeline,
                  TIMELINE_INFO &sPublicTimeline,
                  TIMELINE_INFO &sUserTimeline
              )
{
    if ( !m_jaiku )
        m_jaiku = new CJaikuManager();
    m_jaiku->GetConfig( username, personalKey,
                        oauthToken, oauthTokenSecret,
                        useOAuth, useBASIC,
                        checkMultiPost,
                        sFriendsTimeline,
                        sPublicTimeline,
                        sUserTimeline );
}

void CChirrupDlg::SetWassr(
                  CString username,
                  CString password,
                  BOOL checkMultiPost,
                  BOOL useWassrForUpload,
                  BOOL writeLogfileForUpload,
                  CString logFilenameForUpload,
                  TIMELINE_INFO sFriendsTimeline,
                  TIMELINE_INFO sPublicTimeline,
                  TIMELINE_INFO sUserTimeline
              )
{
    ASSERT( m_wassr );
    m_wassr->SetConfig( username, password,
                        checkMultiPost,
                        sFriendsTimeline,
                        sPublicTimeline,
                        sUserTimeline );

    m_useWassrForUpload          = useWassrForUpload     ? true : false;
    m_wassrWriteLogFileForUpload = writeLogfileForUpload ? true : false;
    m_wassrLogFilenameForUpload  = logFilenameForUpload;
}

void CChirrupDlg::GetWassr(
                  CString &username,
                  CString &password,
                  BOOL &checkMultiPost,
                  BOOL &useWassrForUpload,
                  BOOL &writeLogfileForUpload,
                  CString &logFilenameForUpload,
                  TIMELINE_INFO &sFriendsTimeline,
                  TIMELINE_INFO &sPublicTimeline,
                  TIMELINE_INFO &sUserTimeline
              )
{
    if ( !m_wassr )
        m_wassr = new CManager(CTwitterTimeline::SVC_WASSR);
    m_wassr->GetConfig( username, password,
                        checkMultiPost,
                        sFriendsTimeline,
                        sPublicTimeline,
                        sUserTimeline );

    useWassrForUpload     = m_useWassrForUpload          ? TRUE : FALSE;
    writeLogfileForUpload = m_wassrWriteLogFileForUpload ? TRUE : FALSE;
    logFilenameForUpload  = m_wassrLogFilenameForUpload;
}

void CChirrupDlg::SetMogo2(
                  CString username,
                  CString password,
                  BOOL checkMultiPost,
                  TIMELINE_INFO sFriendsTimeline,
                  TIMELINE_INFO sPublicTimeline,
                  TIMELINE_INFO sUserTimeline
              )
{
    ASSERT( m_mogo2 );
    m_mogo2->SetConfig( username, password,
                        checkMultiPost,
                        sFriendsTimeline,
                        sPublicTimeline,
                        sUserTimeline );
}

void CChirrupDlg::GetMogo2(
                  CString &username,
                  CString &password,
                  BOOL &checkMultiPost,
                  TIMELINE_INFO &sFriendsTimeline,
                  TIMELINE_INFO &sPublicTimeline,
                  TIMELINE_INFO &sUserTimeline
              )
{
    if ( !m_mogo2 )
        m_mogo2 = new CManager(CTwitterTimeline::SVC_MOGO2);
    m_mogo2->GetConfig( username, password,
                        checkMultiPost,
                        sFriendsTimeline,
                        sPublicTimeline,
                        sUserTimeline );
}

void CChirrupDlg::SetTimelog(
                  CString username,
                  CString password,
                  BOOL checkMultiPost,
                  TIMELINE_INFO sFriendsTimeline,
                  TIMELINE_INFO sPublicTimeline,
                  TIMELINE_INFO sUserTimeline
              )
{
    ASSERT( m_timelog );
    m_timelog->SetConfig( username, password,
                          checkMultiPost,
                          sFriendsTimeline,
                          sPublicTimeline,
                          sUserTimeline );
}

void CChirrupDlg::GetTimelog(
                  CString &username,
                  CString &password,
                  BOOL &checkMultiPost,
                  TIMELINE_INFO &sFriendsTimeline,
                  TIMELINE_INFO &sPublicTimeline,
                  TIMELINE_INFO &sUserTimeline
              )
{
    if ( !m_timelog )
        m_timelog = new CManager(CTwitterTimeline::SVC_TIMELOG);
    m_timelog->GetConfig( username, password,
                          checkMultiPost,
                          sFriendsTimeline,
                          sPublicTimeline,
                          sUserTimeline );
}

void CChirrupDlg::SetHaruFm(
                  CString username,
                  CString password,
                  BOOL checkMultiPost,
                  TIMELINE_INFO sFriendsTimeline,
                  TIMELINE_INFO sPublicTimeline,
                  TIMELINE_INFO sUserTimeline
              )
{
    ASSERT( m_haruFm );
    m_haruFm->SetConfig( username, password,
                         checkMultiPost,
                         sFriendsTimeline,
                         sPublicTimeline,
                         sUserTimeline );
}

void CChirrupDlg::GetHaruFm(
                  CString &username,
                  CString &password,
                  BOOL &checkMultiPost,
                  TIMELINE_INFO &sFriendsTimeline,
                  TIMELINE_INFO &sPublicTimeline,
                  TIMELINE_INFO &sUserTimeline
              )
{
    if ( !m_haruFm )
        m_haruFm = new CManager(CTwitterTimeline::SVC_HARUFM);
    m_haruFm->GetConfig( username, password,
                         checkMultiPost,
                         sFriendsTimeline,
                         sPublicTimeline,
                         sUserTimeline );
}

void CChirrupDlg::SetHatenaHaiku(
                  CString username,
                  CString password,
                  BOOL checkMultiPost,
                  TIMELINE_INFO sFriendsTimeline,
                  TIMELINE_INFO sPublicTimeline,
                  TIMELINE_INFO sUserTimeline
              )
{
    ASSERT( m_hatenaHaiku );
    m_hatenaHaiku->SetConfig( username, password,
                              checkMultiPost,
                              sFriendsTimeline,
                              sPublicTimeline,
                              sUserTimeline );
}

void CChirrupDlg::GetHatenaHaiku(
                  CString &username,
                  CString &password,
                  BOOL &checkMultiPost,
                  TIMELINE_INFO &sFriendsTimeline,
                  TIMELINE_INFO &sPublicTimeline,
                  TIMELINE_INFO &sUserTimeline
              )
{
    if ( !m_hatenaHaiku )
        m_hatenaHaiku = new CManager(CTwitterTimeline::SVC_HATENAHAIKU);
    m_hatenaHaiku->GetConfig( username, password,
                              checkMultiPost,
                              sFriendsTimeline,
                              sPublicTimeline,
                              sUserTimeline );
}

void CChirrupDlg::SetHatena(
                  CString username,
                  CString password,
                  BOOL    useTwitStar,
                  BOOL    useHatenaFotolife,
                  BOOL    writeLogFile,
                  CString logFilename
              )
{
    m_hatenaID                   = username;
    m_hatenaPassword             = password;
    m_useTwitStar                = useTwitStar       ? true : false;
    m_useHatenaFotolife          = useHatenaFotolife ? true : false;
    m_hatenaFotolifeWriteLogFile = writeLogFile      ? true : false;
    m_hatenaFotolifeLogFilename  = logFilename;
}

void CChirrupDlg::GetHatena(
                  CString &username,
                  CString &password,
                  BOOL    &useTwitStar,
                  BOOL    &useHatenaFotolife,
                  BOOL    &writeLogFile,
                  CString &logFilename
              )
{
    username          = m_hatenaID;
    password          = m_hatenaPassword;
    useTwitStar       = m_useTwitStar                ? TRUE : FALSE;
    useHatenaFotolife = m_useHatenaFotolife          ? TRUE : FALSE;
    writeLogFile      = m_hatenaFotolifeWriteLogFile ? TRUE : FALSE;
    logFilename       = m_hatenaFotolifeLogFilename;
}

void CChirrupDlg::SetTumblr(
                  CString username,
                  CString password,
                  CString group,
                  CString blogName,
                  BOOL    useTumblr,
                  BOOL    useTumblr2,
                  BOOL    writeLogFile,
                  CString logFilename
              )
{
    m_tumblrID           = username;
    m_tumblrPassword     = password;
    m_tumblrGroup        = group;
    m_tumblrName         = blogName;
    m_useTumblr          = useTumblr    ? true : false;
    m_useTumblr2         = useTumblr2   ? true : false;
    m_tumblrWriteLogFile = writeLogFile ? true : false;
    m_tumblrLogFilename  = logFilename;
}

void CChirrupDlg::GetTumblr(
                  CString &username,
                  CString &password,
                  CString &group,
                  CString &blogName,
                  BOOL    &useTumblr,
                  BOOL    &useTumblr2,
                  BOOL    &writeLogFile,
                  CString &logFilename
              )
{
    username     = m_tumblrID;
    password     = m_tumblrPassword;
    group        = m_tumblrGroup;
    blogName     = m_tumblrName;
    useTumblr    = m_useTumblr          ? TRUE : FALSE;
    useTumblr2   = m_useTumblr2         ? TRUE : FALSE;
    writeLogFile = m_tumblrWriteLogFile ? TRUE : FALSE;
    logFilename  = m_tumblrLogFilename;
}

void CChirrupDlg::SetGyazo( BOOL    useGyazo,
                            BOOL    writeLogFile,
                            CString logFilename )
{
    m_useGyazo          = useGyazo     ? true : false;
    m_gyazoWriteLogFile = writeLogFile ? true : false;
    m_gyazoLogFilename  = logFilename;
}

void CChirrupDlg::GetGyazo( BOOL    &useGyazo,
                            BOOL    &writeLogFile,
                            CString &logFilename )
{
    useGyazo     = m_useGyazo          ? TRUE : FALSE;
    writeLogFile = m_gyazoWriteLogFile ? TRUE : FALSE;
    logFilename  = m_gyazoLogFilename;
}

void CChirrupDlg::SetFlickr( BOOL    useFlickr,
                             BOOL    writeLogFile,
                             CString logFilename,
                             CString flickrToken,
                             CString flickrUserName )
{
    m_useFlickr          = useFlickr    ? true : false;
    m_flickrWriteLogFile = writeLogFile ? true : false;
    m_flickrLogFilename  = logFilename;
    strcpy( m_flickrToken,    (const char *)flickrToken    );
    strcpy( m_flickrUserName, (const char *)flickrUserName );
}

void CChirrupDlg::GetFlickr( BOOL    &useFlickr,
                             BOOL    &writeLogFile,
                             CString &logFilename,
                             CString &flickrToken,
                             CString &flickrUserName )
{
    useFlickr      = m_useFlickr          ? TRUE : FALSE;
    writeLogFile   = m_flickrWriteLogFile ? TRUE : FALSE;
    logFilename    = m_flickrLogFilename;
    flickrToken    = m_flickrToken;
    flickrUserName = m_flickrUserName;
}

void CChirrupDlg::SetProxy(
                  BOOL    useProxy,
                  CString proxyServerName,
                  UINT    proxyPortNumber,
                  CString proxyUserName,
                  CString proxyPassword
              )
{
    CChirrupApp *ap = (CChirrupApp *)AfxGetApp();

    ap->m_isUsedProxy = useProxy ? true : false;
    if ( useProxy ) {
        ap->m_proxyServer   = proxyServerName;
        ap->m_proxyPort     = proxyPortNumber;
        ap->m_proxyUserName = _T("");
        ap->m_proxyPassword = _T("");

        if ( proxyUserName.GetLength() > 0 ) {
            ap->m_proxyUserName = proxyUserName;
            if ( proxyPassword.GetLength() > 0 )
                ap->m_proxyPassword = proxyPassword;
        }

        setProxyInfo( ap->m_proxyServer,
                      (unsigned short)(ap->m_proxyPort),
                      ap->m_proxyUserName,
                      ap->m_proxyPassword );
    }
    else {
        ap->m_proxyServer   = _T("");
        ap->m_proxyPort     = 0;
        ap->m_proxyUserName = _T("");
        ap->m_proxyPassword = _T("");
    }
    setUseProxy( ap->m_isUsedProxy );
}

void CChirrupDlg::GetProxy(
                  BOOL    &useProxy,
                  CString &proxyServerName,
                  UINT    &proxyPortNumber,
                  CString &proxyUserName,
                  CString &proxyPassword
              )
{
    CChirrupApp *ap = (CChirrupApp *)AfxGetApp();

    if ( ap->m_proxyServer.GetLength() > 0 ) {
        useProxy        = ap->m_isUsedProxy;
        proxyServerName = ap->m_proxyServer;
        proxyPortNumber = ap->m_proxyPort;
        proxyUserName   = _T("");
        proxyPassword   = _T("");

        if ( ap->m_proxyUserName.GetLength() > 0 ) {
            proxyUserName = ap->m_proxyUserName;
            if ( ap->m_proxyPassword.GetLength() > 0 )
                proxyPassword = ap->m_proxyPassword;
        }
    }
    else {
        bool            isUsedProxy = false;
        unsigned short  proxyPort   = 0;
        GetProxyInfo( isUsedProxy,
                      proxyServerName, proxyPort,
                      proxyUserName, proxyPassword );
        proxyPortNumber = proxyPort;
        useProxy        = isUsedProxy;
    }
}

void CChirrupDlg::ShowServiceName( bool mode )
{
    m_showServiceName = mode;

    CStatic *sp = (CStatic *)GetDlgItem( IDC_EXECUTING );
    if ( mode ) {
        CString serviceName = m_serviceName;

        if ( !strncmp( m_timelineType, "Jaiku:", 6 ) )
            serviceName = _T( "Powered by Jaiku" );
        else if ( !strncmp( m_timelineType, "Wassr:", 6 ) )
            serviceName = _T( "Powered by Wassr" );
        else if ( !strncmp( m_timelineType, "もごもご:", 9 ) )
            serviceName = _T( "Powered by もごもご" );
        else if ( !strncmp( m_timelineType, "Timelog:", 8 ) )
            serviceName = _T( "Powered by Timelog" );
        else if ( !strncmp( m_timelineType, "Haru.fm:", 8 ) )
            serviceName = _T( "Powered by Haru.fm" );
        else if ( !strncmp( m_timelineType, "はてなハイク:", 13 ) )
            serviceName = _T( "Powered by はてなハイク" );
     // else if ( !strncmp( m_timelineType, "Twitter:", 8 ) )
     //     serviceName = m_serviceName;

        sp->SetWindowText( serviceName );
        sp->SetFont( &m_cFont2, TRUE ); // 下線付き
    }
    else
        sp->SetFont( &m_cFont1, TRUE ); // 下線なし

    sp->ShowWindow( SW_SHOW );
}

void CChirrupDlg::ReduceExtra()
{
    if ( m_twitter ) {
        SetStaticEdge( IDC_TWITTER, m_twitter->m_simultaneousPost );
        if ( !m_twitter->m_useOAuth                         &&
             ((m_twitter->m_username.GetLength() == 0) ||
              (m_twitter->m_password.GetLength() == 0)    )    ) {
            delete m_twitter;
            m_twitter = NULL;
        }
    }
    if ( m_jaiku ) {
        SetStaticEdge( IDC_JAIKU,   m_jaiku->m_simultaneousPost );
        if ( !m_jaiku->m_useOAuth                         &&
             ((m_jaiku->m_username.GetLength() == 0) ||
              (m_jaiku->m_password.GetLength() == 0)    )    ) {
            delete m_jaiku;
            m_jaiku = NULL;
        }
    }
    if ( m_timelog ) {
        SetStaticEdge( IDC_TIMELOG, m_timelog->m_simultaneousPost );
        if ( (m_timelog->m_username.GetLength() == 0) ||
             (m_timelog->m_password.GetLength() == 0)    ) {
            delete m_timelog;
            m_timelog = NULL;
        }
    }
    if ( m_mogo2 ) {
        SetStaticEdge( IDC_MOGO2,   m_mogo2->m_simultaneousPost );
        if ( (m_mogo2->m_username.GetLength() == 0) ||
             (m_mogo2->m_password.GetLength() == 0)    ) {
            delete m_mogo2;
            m_mogo2 = NULL;
        }
    }
    if ( m_wassr ) {
        SetStaticEdge( IDC_WASSR,   m_wassr->m_simultaneousPost );
        if ( (m_wassr->m_username.GetLength() == 0) ||
             (m_wassr->m_password.GetLength() == 0)    ) {
            delete m_wassr;
            m_wassr = NULL;
        }
    }
    if ( m_haruFm ) {
        SetStaticEdge( IDC_HARUFM,  m_haruFm->m_simultaneousPost );
        if ( (m_haruFm->m_username.GetLength() == 0) ||
             (m_haruFm->m_password.GetLength() == 0)    ) {
            delete m_haruFm;
            m_haruFm = NULL;
        }
    }
    if ( m_hatenaHaiku ) {
        SetStaticEdge( IDC_HATENAHAIKU, m_hatenaHaiku->m_simultaneousPost );
        if ( (m_hatenaHaiku->m_username.GetLength() == 0) ||
             (m_hatenaHaiku->m_password.GetLength() == 0)    ) {
            delete m_hatenaHaiku;
            m_hatenaHaiku = NULL;
        }
    }
}

bool CChirrupDlg::DisplayContextMenuForServices( WORD wX, WORD wY )
{
    bool    done      = false;
    bool    onOff     = false;
    int     targetIDC = 0;

    if ( IsInner( IDC_TWITTER, wX, wY ) ) {
        if ( m_twitter ) {
            targetIDC = IDC_TWITTER;
            onOff     = m_twitter->m_simultaneousPost;
        }
    }
    else if ( IsInner( IDC_JAIKU, wX, wY ) ) {
        if ( m_jaiku ) {
            targetIDC = IDC_JAIKU;
            onOff     = m_jaiku->m_simultaneousPost;
        }
    }
    else if ( IsInner( IDC_TIMELOG, wX, wY ) ) {
        if ( m_timelog ) {
            targetIDC = IDC_TIMELOG;
            onOff     = m_timelog->m_simultaneousPost;
        }
    }
    else if ( IsInner( IDC_MOGO2, wX, wY ) ) {
        if ( m_mogo2 ) {
            targetIDC = IDC_MOGO2;
            onOff     = m_mogo2->m_simultaneousPost;
        }
    }
    else if ( IsInner( IDC_WASSR, wX, wY ) ) {
        if ( m_wassr ) {
            targetIDC = IDC_WASSR;
            onOff     = m_wassr->m_simultaneousPost;
        }
    }
    else if ( IsInner( IDC_HARUFM, wX, wY ) ) {
        if ( m_haruFm ) {
            targetIDC = IDC_HARUFM;
            onOff     = m_haruFm->m_simultaneousPost;
        }
    }
    else if ( IsInner( IDC_HATENAHAIKU, wX, wY ) ) {
        if ( m_hatenaHaiku ) {
            targetIDC = IDC_HATENAHAIKU;
            onOff     = m_hatenaHaiku->m_simultaneousPost;
        }
    }

    if ( targetIDC == 0 )
        return ( done );

    CPoint  cMenuPt;
    GetCursorPos( &cMenuPt );

#define IDC_MENU_SWITCH_ON      1
#define IDC_MENU_SWITCH_OFF     2
    CMenu   menu;
    menu.CreatePopupMenu();
    menu.AppendMenu( MF_STRING, IDC_MENU_SWITCH_ON,
                     "同時投稿対象にする (&S)" );
    menu.AppendMenu( MF_STRING, IDC_MENU_SWITCH_OFF,
                     "同時投稿対象から外す (&X)" );

    if ( onOff )
        menu.EnableMenuItem( IDC_MENU_SWITCH_ON, MF_GRAYED );
    if ( !onOff )
        menu.EnableMenuItem( IDC_MENU_SWITCH_OFF, MF_GRAYED );

    int iCommand =
        menu.TrackPopupMenu(
            TPM_LEFTALIGN | TPM_BOTTOMALIGN | TPM_RETURNCMD | TPM_LEFTBUTTON,
            cMenuPt.x, cMenuPt.y, this, NULL );

    if ( (iCommand == IDC_MENU_SWITCH_ON)  ||
         (iCommand == IDC_MENU_SWITCH_OFF)    ) {
        switch ( targetIDC ) {
        case IDC_TWITTER:
            m_twitter->m_simultaneousPost = !(m_twitter->m_simultaneousPost);
            SetStaticEdge( targetIDC, m_twitter->m_simultaneousPost );
            break;
        case IDC_JAIKU:
            m_jaiku->m_simultaneousPost = !(m_jaiku->m_simultaneousPost);
            SetStaticEdge( targetIDC, m_jaiku->m_simultaneousPost );
            break;
        case IDC_TIMELOG:
            m_timelog->m_simultaneousPost = !(m_timelog->m_simultaneousPost);
            SetStaticEdge( targetIDC, m_timelog->m_simultaneousPost );
            break;
        case IDC_MOGO2:
            m_mogo2->m_simultaneousPost = !(m_mogo2->m_simultaneousPost);
            SetStaticEdge( targetIDC, m_mogo2->m_simultaneousPost );
            break;
        case IDC_WASSR:
            m_wassr->m_simultaneousPost = !(m_wassr->m_simultaneousPost);
            SetStaticEdge( targetIDC, m_wassr->m_simultaneousPost );
            break;
        case IDC_HARUFM:
            m_haruFm->m_simultaneousPost = !(m_haruFm->m_simultaneousPost);
            SetStaticEdge( targetIDC, m_haruFm->m_simultaneousPost );
            break;
        case IDC_HATENAHAIKU:
            m_hatenaHaiku->m_simultaneousPost = !(m_hatenaHaiku->m_simultaneousPost);
            SetStaticEdge( targetIDC, m_hatenaHaiku->m_simultaneousPost );
            break;
        }

        done = true;
    }

    m_needToSave = true;
    menu.DestroyMenu();	

    return ( done );
}

bool CChirrupDlg::DisplayContextMenuForFriends( WORD wX, WORD wY )
{
    bool    done      = false;
    int     targetIDC = 0;
    int     targetIdx = 0;
    int     idx       = 0;
    int     i;

    for ( i = 0; i < MAX_NUMOFFRIENDS; i++ ) {
        idx = IDC_FRIEND001 + i;
        if ( IsInner( idx, wX, wY ) ) {
            targetIDC = idx;
            targetIdx = i;
            break;
        }
    }

    CTwitterTimeline    *tp = GetCurrentTimeline();
    if ( (targetIDC == 0) ||
         !(tp->m_users)   ||
         !((tp->m_users)[targetIdx].id[0]) )
        return ( done );

    CPoint  cMenuPt;
    GetCursorPos( &cMenuPt );

#define IDC_MENU_SHOW_PROFILE           1
#define IDC_MENU_SHOW_WEB_PAGE          2
#define IDC_MENU_SEND_DIRECT_MESSAGE    3
#define IDC_MENU_ADD_FRIEND             4
#define IDC_MENU_REMOVE_FRIEND          5
#define IDC_MENU_SHOW_FAVORITES         6
    CMenu   menu;
    menu.CreatePopupMenu();
    menu.AppendMenu( MF_STRING, IDC_MENU_SHOW_PROFILE,
                     "プロフィールを表示 (&P)" );
    menu.AppendMenu( MF_STRING, IDC_MENU_SHOW_WEB_PAGE,
                     "関連Webページを表示 (&W)" );
    if ( !m_timelineType.Compare( "Twitter: Friends" ) ) {
        menu.AppendMenu( MF_STRING, IDC_MENU_SEND_DIRECT_MESSAGE,
                         "ダイレクトメッセージを送信 (&D)" );
        menu.AppendMenu( MF_STRING, IDC_MENU_REMOVE_FRIEND,
                         "friend 指定を外す (&R)" );
    }
    else 
    if ( !m_timelineType.Compare( "Twitter: Public" ) ) {
        menu.AppendMenu( MF_STRING, IDC_MENU_ADD_FRIEND,
                         "friend にする (&A)" );
    }
    if ( !strncmp( m_timelineType, "Twitter: ", 9 ) )
        menu.AppendMenu( MF_STRING, IDC_MENU_SHOW_FAVORITES,
                         "favorites を見る (&F)" );
    if ( !strncmp( m_timelineType, "Timelog: ", 9 ) )
        menu.AppendMenu( MF_STRING, IDC_MENU_SEND_DIRECT_MESSAGE,
                         "ダイレクトメッセージを送信 (&D)" );
    if ( !m_timelineType.Compare( "Wassr: Friends" ) ) {
        menu.AppendMenu( MF_STRING, IDC_MENU_REMOVE_FRIEND,
                         "購読を解除する (&R)" );
    }
    else 
    if ( !m_timelineType.Compare( "Wassr: Public" ) ) {
        menu.AppendMenu( MF_STRING, IDC_MENU_ADD_FRIEND,
                         "購読する (&A)" );
    }

    int iCommand =
        menu.TrackPopupMenu(
            TPM_LEFTALIGN | TPM_BOTTOMALIGN | TPM_RETURNCMD | TPM_LEFTBUTTON,
            cMenuPt.x, cMenuPt.y, this, NULL );

    switch ( iCommand ) {
    case IDC_MENU_SHOW_PROFILE:
        ShowFriendProfile( targetIDC );
        break;
    case IDC_MENU_SHOW_WEB_PAGE:
        ShowWebPage( targetIDC );
        break;
    case IDC_MENU_SEND_DIRECT_MESSAGE:
        SendDirectMessageToFriend( targetIDC );
        break;
    case IDC_MENU_ADD_FRIEND:
        AddFriend( targetIDC );
        break;
    case IDC_MENU_REMOVE_FRIEND:
        RemoveFriend( targetIDC );
        break;
    case IDC_MENU_SHOW_FAVORITES:
        ShowFavorites( targetIDC );
        break;
    }
    done = true;

    menu.DestroyMenu();	

    return ( done );
}

bool CChirrupDlg::DisplayContextMenuForImetter( WORD wX, WORD wY )
{
    bool    done      = false;
    bool    onOff     = false;
    int     targetIDC = 0;

    if ( IsInner( IDC_POST_MONOLOGUE, wX, wY ) ) {
        targetIDC = IDC_POST_MONOLOGUE;
        onOff     = m_useImetter;
    }

    if ( targetIDC == 0 )
        return ( done );

    CPoint  cMenuPt;
    GetCursorPos( &cMenuPt );

#define IDC_MENU_IMETTER_ON     1
#define IDC_MENU_IMETTER_OFF    2
    CMenu   menu;
    menu.CreatePopupMenu();
    menu.AppendMenu( MF_STRING, IDC_MENU_IMETTER_ON,
                     "「いめったー」ボタンに変更する" );
    menu.AppendMenu( MF_STRING, IDC_MENU_IMETTER_OFF,
                     "「発言」ボタンに戻す" );

    if ( onOff )
        menu.EnableMenuItem( IDC_MENU_IMETTER_ON, MF_GRAYED );
    if ( !onOff )
        menu.EnableMenuItem( IDC_MENU_IMETTER_OFF, MF_GRAYED );

    int iCommand =
        menu.TrackPopupMenu(
            TPM_LEFTALIGN | TPM_BOTTOMALIGN | TPM_RETURNCMD | TPM_LEFTBUTTON,
            cMenuPt.x, cMenuPt.y, this, NULL );

    if ( (iCommand == IDC_MENU_IMETTER_ON)  ||
         (iCommand == IDC_MENU_IMETTER_OFF)    ) {
        switch ( targetIDC ) {
        case IDC_POST_MONOLOGUE:
            m_useImetter = !m_useImetter;
            m_needToSave = true;
            SwitchImetter();
            break;
        }

        done = true;
    }

    menu.DestroyMenu();	

    return ( done );
}

#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
bool CChirrupDlg::ExtraContextMenu( WORD wX, WORD wY )
{
    bool    done  = false;
	CPoint  cMenuPt;
	GetCursorPos( &cMenuPt );

#define IDC_MENU_COPY           1
#define IDC_MENU_CAPTURE        2
#define IDC_MENU_UPDATEICON     3
#define IDC_MENU_CHANGE_SETTING 4
#define IDC_MENU_RESTORE_WINDOW 5
#define IDC_MENU_CANCEL         6
#define IDC_MENU_END_DIALOG     7
#define IDM_ABOUT_SUPPORT       (IDM_ABOUTBOX + 1)
#define IDM_ABOUT_SUPPORT2      (IDM_ABOUTBOX + 2)
#define IDM_ABOUT_COMMUNITY     (IDM_ABOUTBOX + 3)
#define IDM_ABOUT_COMMUNITY2    (IDM_ABOUTBOX + 4)

    CMenu   menu;
    menu.CreatePopupMenu();
    if ( IsIconic() ) {
        menu.AppendMenu( MF_STRING, IDC_MENU_RESTORE_WINDOW,
                         _T("元のサイズに戻す(&R)") );
        menu.AppendMenu( MF_SEPARATOR );
    }
    menu.AppendMenu( MF_STRING, IDC_MENU_CHANGE_SETTING,
                     _T("設定変更(&O)") );
    menu.AppendMenu( MF_STRING, IDC_MENU_COPY,
                     _T("貼り付け(&P)") );
    menu.AppendMenu( MF_STRING, IDC_MENU_CAPTURE,
                     _T("スクリーンキャプチャ(&S)") );
    menu.AppendMenu( MF_STRING, IDC_MENU_UPDATEICON,
                     m_updateUserIcon
                        ? _T("ユーザアイコン更新機能停止(&I)")
                        : _T("ユーザアイコン更新機能再開(&I)") );

    menu.AppendMenu( MF_SEPARATOR );
    CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUT_SUPPORT);
	menu.AppendMenu(MF_STRING, IDM_ABOUT_SUPPORT, strAboutMenu);
	strAboutMenu.LoadString(IDS_ABOUT_SUPPORT2);
	menu.AppendMenu(MF_STRING, IDM_ABOUT_SUPPORT2, strAboutMenu);
	strAboutMenu.LoadString(IDS_ABOUT_COMMUNITY);
	menu.AppendMenu(MF_STRING, IDM_ABOUT_COMMUNITY, strAboutMenu);
	strAboutMenu.LoadString(IDS_ABOUT_COMMUNITY2);
	menu.AppendMenu(MF_STRING, IDM_ABOUT_COMMUNITY2, strAboutMenu);
    menu.AppendMenu( MF_SEPARATOR );
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	menu.AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);

    if ( IsIconic() ) {
        menu.AppendMenu( MF_SEPARATOR );
        menu.AppendMenu( MF_STRING, IDC_MENU_CANCEL,
                         _T("キャンセル(&C)") );
        menu.AppendMenu( MF_STRING, IDC_MENU_END_DIALOG,
                         _T("終了(&X)") );
    }

    if ( !IsClipboardFormatAvailable(CF_TEXT) )
        menu.EnableMenuItem( IDC_MENU_COPY, MF_GRAYED );
    if ( !(m_useTumblr2        ||
           m_useGyazo          ||
           m_useFlickr         ||
           m_useHatenaFotolife ||
           m_useWassrForUpload   ) )
        menu.EnableMenuItem( IDC_MENU_CAPTURE, MF_GRAYED );

                            /* メニューが消えずに残った */
    SetForegroundWindow();  /* ままになることがある現象 */
                            /* への対策                 */
    int iCommand =
        menu.TrackPopupMenu(
            TPM_LEFTALIGN | TPM_BOTTOMALIGN | TPM_RETURNCMD | TPM_LEFTBUTTON,
            cMenuPt.x, cMenuPt.y, this, NULL );
                            /* メニューが消えずに残った */
    PostMessage( WM_NULL ); /* ままになることがある現象 */
                            /* への対策                 */

    switch ( iCommand ) {
    case IDC_MENU_COPY:
	    OnEditPaste();
        done = true;
        break;

    case IDC_MENU_CAPTURE:
	    OnStartCapture();
        done = true;
        break;

    case IDC_MENU_UPDATEICON:
        m_updateUserIcon = !m_updateUserIcon;
        SaveSetting();
        done = true;
        break;

    case IDC_MENU_CHANGE_SETTING:
        OnSettingAccount();
        done = true;
        break;
        
    case IDC_MENU_RESTORE_WINDOW:
        OpenIcon();
        SetForegroundWindow();
        done = true;
        break;

    case IDC_MENU_CANCEL:
        done = true;
        break;

    case IDC_MENU_END_DIALOG:
        done = false;
        break;

    case IDM_ABOUTBOX:
    case IDM_ABOUT_SUPPORT:
    case IDM_ABOUT_SUPPORT2:
    case IDM_ABOUT_COMMUNITY:
    case IDM_ABOUT_COMMUNITY2:
        OnSysCommand(iCommand, 0);
        done = true;
        break;

    default:
        done = true;
        break;
    }

    menu.DestroyMenu();

    return ( done );
}
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif

void CChirrupDlg::SetStaticEdge( int idx, bool status )
{
    CStatic *sp = (CStatic *)GetDlgItem( idx );

    if ( status ) {
        // "くぼみ"状態にする
        sp->ModifyStyleEx( 0, WS_EX_STATICEDGE, SWP_DRAWFRAME );
    }
    else {
        // "くぼみ"状態を解除する
        sp->ModifyStyleEx( WS_EX_STATICEDGE, 0, SWP_DRAWFRAME );

        // "くぼみ"状態 → くぼんでない状態の変化後、アイコンの下部の表示が
        // 乱れるので、再描画しておく
        sp->RedrawWindow();
    }
}

void CChirrupDlg::SetAddrOnMonologue( CString targetUser, CEdit *cp )
{
    CTwitterTimeline    *tp  = GetCurrentTimeline();
    CString             addr = _T("");

    if ( tp->m_serviceType == CTwitterTimeline::SVC_HARUFM ) {
        // for Haru.fm
        addr = _T("#");
        addr += targetUser;
        addr += _T("# ");
    }
    else {
        if ( strncmp( targetUser, ">>", 2 ) != 0 )
            addr = _T("@");
        addr += targetUser;
        addr += _T(" ");
    }

    cp->GetWindowText( m_monologue );
    m_monologue = addr + m_monologue;
    cp->SetWindowText( m_monologue );
}

void CChirrupDlg::SetTargetUserOnMonologue( CString targetUser )
{
    CEdit   *cp = (CEdit *)GetDlgItem( IDC_MONOLOGUE );
    SetAddrOnMonologue( targetUser, cp );

    int loc = m_monologue.GetLength();
    cp->SetSel(loc, loc, TRUE);
    cp->SetSel(-1, -1, FALSE);
}

BOOL CChirrupDlg::SetPaneText(
            int     nIndex,
            LPCTSTR lpszNewText,
            BOOL    bUpdate /* = TRUE */ )
{
    return ( m_status.SetPaneText( nIndex, lpszNewText, bUpdate ) );
}

CHIRRUP_FTYPE
CChirrupDlg::GetImageSize( const char *filename, int& height, int& width )
{
    FILE            *fp;
    const char      *p = strrchr( filename, '.' );
    unsigned char   buf[BUFSIZ];
    CHIRRUP_FTYPE   ftype = FTYPE_UNKNOWN;

    height = width = 0;
    if ( !p )
        return ( ftype );

    if ( !strcmpi( p + 1, "jpg"  ) ||
         !strcmpi( p + 1, "jpeg" )    )
        ftype = FTYPE_JPG;
    else if ( !strcmpi( p + 1, "gif" ) )
        ftype = FTYPE_GIF;
    else if ( !strcmpi( p + 1, "png" ) )
        ftype = FTYPE_PNG;
    else if ( !strcmpi( p + 1, "bmp" ) )
        ftype = FTYPE_BMP;
 // else
 //     return ( ftype );

    if ( ( fp = fopen( filename, "rb" ) ) == NULL )
        return ( FTYPE_UNKNOWN );

    // 拡張子がうそをついているかもしれないので、念のために、画像ファイル
    // の先頭を実際に読んでみて、画像形式を判定する
    fread( buf, 1, BUFSIZ, fp );
    rewind( fp );

    if ( (buf[0] == 0x89) &&
         (buf[1] == 'P')  &&
         (buf[2] == 'N')  &&
         (buf[3] == 'G')  &&
         (buf[4] == 0x0D) &&
         (buf[5] == 0x0A) &&
         (buf[6] == 0x1A) &&
         (buf[7] == 0x0A)    )
        ftype = FTYPE_PNG;
    else
    if ( ( buf[0] == 0377)     &&
         ( buf[1] == 0300)     &&
         ( buf[2] == 0377)     &&
         ((buf[3] == 0340) ||
          (buf[3] == 0341) ||
          (buf[3] == 0356)   )    )
        ftype = FTYPE_JPG;
    else
    if ( (buf[6] == 'J') &&
         (buf[7] == 'F') &&
         (buf[8] == 'I') &&
         (buf[9] == 'F')     )
        ftype = FTYPE_JPG;
    else
    if ( ( buf[0] == 'G')     &&
         ( buf[1] == 'I')     &&
         ( buf[2] == 'F')     &&
         ( buf[3] == '8')     &&
         ((buf[4] == '7') ||
          (buf[4] == '9')   ) &&
         ( buf[5] == 'a')        )
        ftype = FTYPE_GIF;
    else
    if ( (buf[0] == 'B') &&
         (buf[1] == 'M')    )
        ftype = FTYPE_BMP;

    switch ( ftype ) {
    case FTYPE_JPG: {
        /* FF C0, FF C1, FF C2, FF C3 のいずれかの連続する2バイトの後 *
         * 3バイト読み飛ばした直後の                                  *
         *    2バイト               → height                         *
         *    さらにその次の2バイト → width                          */
        int ret, done = FALSE;

        do {
            unsigned char   *p;

            ret = fread( buf, sizeof ( char ), BUFSIZ, fp );
            p = buf;
            for ( int i = 0; i < BUFSIZ - 9; i++, p++ ) {
                if ( (*p == 0xFF) &&
                     (*(p + 1) >= 0xC0) && (*(p + 1) <= 0xC3) ) {
                    p += 5;
                    height = *p * 256 + *(p + 1);
                    width  = *(p + 2) * 256 + *(p + 3);
                    done = TRUE;
                    break;
                }
            }
        } while ( (ret > 0) && (done == FALSE) );
        }
        break;

    case FTYPE_GIF:
        /* width:  7バイト目からの2バイト (7バイト目:下位、 8バイト目:上位) *
         * height: 9バイト目からの2バイト (9バイト目:下位、10バイト目:上位) */
        fread( buf, sizeof ( char ), 16, fp );
        width  = buf[7] * 256 + buf[6];
        height = buf[9] * 256 + buf[8];
        break;

    case FTYPE_PNG:
        /*  width:  17バイト目からの4バイト                   *
         *         (17バイト目: 最上位 ～ 20バイト目: 最下位) *
         *  height: 21バイト目からの4バイト                   *
         *         (21バイト目: 最上位 ～ 24バイト目: 最下位) */
        fread( buf, sizeof ( char ), 32, fp );
        width  = ((((buf[16] * 256) + buf[17]) * 256) + buf[18]) * 256 + buf[19];
        height = ((((buf[20] * 256) + buf[21]) * 256) + buf[22]) * 256 + buf[23];
        break;

    case FTYPE_BMP: {
        /* Windows Bitmap と OS/2 Bitmap の2種類存在し、さらに  *
         * Windows Bitmap には3つの亜種が存在する               *
         * OS/2 Bitmap                                          *
         *    width:  19バイト目からの2バイト                   *
         *           (19バイト目: 最上位 ～ 20バイト目: 最下位) *
         *    height: 21バイト目からの2バイト                   *
         *           (21バイト目: 最上位 ～ 22バイト目: 最下位) *
         * Windows Bitmap (全亜種共通)                          *
         *    width:  19バイト目からの4バイト                   *
         *           (19バイト目: 最上位 ～ 22バイト目: 最下位) *
         *    height: 23バイト目からの4バイト                   *
         *           (23バイト目: 最上位 ～ 26バイト目: 最下位) */
        const size_t    szHeader1 = sizeof ( BITMAPFILEHEADER );
        const size_t    szHeader2 = sizeof ( BITMAPINFOHEADER );
        fread( buf, sizeof ( char ), szHeader1 + szHeader2, fp );

        long    infoHearderSize =
                    ((BITMAPINFOHEADER *) &(buf[szHeader1]))->biSize;
        switch ( infoHearderSize ) {
        case sizeof ( BITMAPCOREHEADER ):   /* OS/2 Bitmap */
            width  = ((BITMAPCOREHEADER *) &(buf[szHeader1]))->bcWidth;
            height = ((BITMAPCOREHEADER *) &(buf[szHeader1]))->bcHeight;
            break;

        case sizeof ( BITMAPINFOHEADER ) :
     // case sizeof ( BITMAPV4HEADER )   :
     // case sizeof ( BITMAPV5HEADER )   :
        default:    /* Windows Bitmap */
            width  = ((BITMAPINFOHEADER *) &(buf[szHeader1]))->biWidth;
            height = ((BITMAPINFOHEADER *) &(buf[szHeader1]))->biHeight;
            break;
        }
        }
        break;
    }

    fclose( fp );
    return ( ftype );
}

void
CChirrupDlg::WriteUploadLog(
                    const char *filename,
                    const char *url,
                    const char *caption
                )
{
    if ( !url || !(*url) )
        return;

    FILE    *fp = fopen( filename, "a" );
    if ( fp ) {
        time_t      t   = time( NULL );
        struct tm   *tm = localtime( &t );

        if ( caption && *caption )
            fprintf( fp, "%s : %s [%04d/%02d/%02d %02d:%02d:%02d]\n",
                     url, caption,
                     tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                     tm->tm_hour, tm->tm_min, tm->tm_sec );
        else
            fprintf( fp, "%s [%04d/%02d/%02d %02d:%02d:%02d]\n",
                     url,
                     tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                     tm->tm_hour, tm->tm_min, tm->tm_sec );

        fclose( fp );
    }
}

bool
CChirrupDlg::SetSigInfo( CString &sKey,    CString &sSecret,
                         const char *sig1, const char *sig2 )
{
    char    key[BUFSIZ];
    char    secret[BUFSIZ];
    BOOL    ret;

    ret = setSigInfo( key, secret, sig1, sig2, "-ts", "up-" );
    if ( ret ) {
        sKey    = key;
        sSecret = secret;
    }

    return ( ret ? true : false );
}

void
CChirrupDlg::GetImageViaImetter( CString &monologue, ProceedingDialog *pdlg )
{
    size_t  sz1 = monologue.GetLength() * 6;
    size_t  sz2 = MAX_URLLENGTH * 2;
    char    *request  = new char[sz1];
    char    *response = new char[sz2];
    char    *p = sjis2utf( (const char *)monologue );

    sprintf( request, "keyword=%s", p ? p : (const char *)monologue );
    if ( m_twitter && m_twitter->m_service ) {
        m_twitter->m_service->SetUserAgent();
        if ( (m_twitter->m_username.GetLength() > 0)             &&
             !strchr( (const char *)m_twitter->m_username, '@' )    )
            sprintf( request + strlen(request),
                     "&account=%s"
                     "&password=",
                     (const char *)m_twitter->m_username );
        else if ( m_twitter->m_screenName.GetLength() > 0 )
            sprintf( request + strlen(request),
                     "&account=%s"
                     "&password=",
                     (const char *)m_twitter->m_screenName );
    }
    setUpReceiveBuffer( response, sz2 );
    _http_post(
        "https://ss2.xrea.com/kanmisikou.net/lab/imagetwit/api/post.php",
        request, response, pdlg );
    if ( *response ) {
        bool    success = false;

        if ( !strncmp( response, "http://" , 7 ) ) {
            monologue += " " ;
            success = true;
        }
        else if ( (*response >= '1') && (*response <= '9') ) {
            monologue +=
                " http://kanmisikou.net/lab/imagetwit/state.php?state=";
            success = true;
        }

        if ( success ) {
            monologue += response;
            monologue += " [いめったー]";
        }
    }

    delete [] response;
    delete [] request;
}

/////////////////////////////////////////////////////////////////////////////
// CChirrupDlg メッセージ ハンドラ

BOOL CChirrupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL) {
        pSysMenu->AppendMenu(MF_SEPARATOR);
        CString strAboutMenu0;
		strAboutMenu0.LoadString(IDS_ABOUT_SUPPORT);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUT_SUPPORT, strAboutMenu0);
		strAboutMenu0.LoadString(IDS_ABOUT_SUPPORT2);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUT_SUPPORT2, strAboutMenu0);
		strAboutMenu0.LoadString(IDS_ABOUT_COMMUNITY);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUT_COMMUNITY, strAboutMenu0);
		strAboutMenu0.LoadString(IDS_ABOUT_COMMUNITY2);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUT_COMMUNITY2, strAboutMenu0);

		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty()) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定

    EnableToolTips(TRUE);

    // ステータスバーを作成
    m_status.Create( this );

    UINT    indicators[] = {
        ID_SEPARATOR,
        ID_SEPARATOR,
    };
    m_status.SetIndicators( indicators, 2 );

    CRect rect_st;
    m_status.GetWindowRect( rect_st );

    CRect   rect;
    GetClientRect( &rect );

    int height     = rect_st.bottom;
    rect_st.top    = rect.bottom - height;
    rect_st.bottom = rect_st.top + height;
    rect_st.left   = rect.left;
    rect_st.right  = rect.right;
    m_status.MoveWindow( rect_st );
    m_status.SetPaneInfo( 0, ID_SEPARATOR, SBPS_NORMAL,
                          (rect_st.right - rect_st.left) * 80 / 100 );
    m_status.SetPaneText( 0, _T(" ") );

    // リサイズに備えて必要な箇所の採寸を済ませておく
    m_cx = m_cxInitial = rect.right;
    m_cy = m_cyInitial = rect.left;

    m_rectBottom = rect;
    m_rectBottom.right  += ADJUST_WIDTH;
    m_rectBottom.bottom += (height + ADJUST_HEIGHT);

    CStatic *sp = (CStatic *)GetDlgItem( IDC_FRIEND020 );
    sp->GetWindowRect( &rect );
    m_rectFriend020 = rect;
    m_rectFriend020.bottom += (height + ADJUST_HEIGHT);

    sp = (CStatic *)GetDlgItem( IDC_FRIEND010 );
    sp->GetWindowRect( &rect );
    m_rectFriend010 = rect;
    m_rectFriend010.bottom += (height + ADJUST_HEIGHT);

    CButton *bp = (CButton *)GetDlgItem( IDC_CHECK_BROWSING );
    bp->GetWindowRect( &rect );
    m_rectCheckBrowsing = rect;
    m_rectCheckBrowsing.bottom += (height + ADJUST_HEIGHT);

    CEdit   *ep = (CEdit *)GetDlgItem( IDC_MONOLOGUE );
    ep->GetWindowRect( &rect );
    m_rectMonologue = rect;
    m_rectMonologue.bottom += (height + ADJUST_HEIGHT);

    bp = (CButton *)GetDlgItem( IDC_POST_MONOLOGUE );
    bp->GetWindowRect( &rect );
    m_rectPostMonologue = rect;
    m_rectPostMonologue.bottom += (height + ADJUST_HEIGHT);

    bp = (CButton *)GetDlgItem( IDC_RECV_DIRECTMESSAGE );
    bp->GetWindowRect( &rect );
    m_rectDirectMessage = rect;
    m_rectDirectMessage.bottom += (height + ADJUST_HEIGHT);

    bp = (CButton *)GetDlgItem( IDC_UPDATE );
    bp->GetWindowRect( &rect );
    m_rectUpdate = rect;
    m_rectUpdate.bottom += (height + ADJUST_HEIGHT);

    CRichEditEx *rp = (CRichEditEx *)GetDlgItem( IDC_RICHEDIT_MESSAGES );
    rp->GetWindowRect( &rect );
    m_rectMessageCtrl = rect;
    m_rectMessageCtrl.bottom += (height + ADJUST_HEIGHT);

    m_initialized   = true;

    // ドロップターゲットへの登録
    m_dropTarget.Register( this, this );

    // タスクトレイに常駐できるようにする
    CChirrupApp *ap = (CChirrupApp *)AfxGetApp();
    m_stNotifyIcon.cbSize = sizeof ( NOTIFYICONDATA );
    m_stNotifyIcon.uID    = 0;
    m_stNotifyIcon.hWnd   = m_hWnd;
    m_stNotifyIcon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    m_stNotifyIcon.hIcon  = ap->LoadIcon( IDI_TASKTRAY_ICON );
    m_stNotifyIcon.uCallbackMessage = WM_APP_TASKTRY;

    CString version;
    version.LoadString( IDS_VERSION );
    CString title = _T("chirrup Ver ");
    title += version;
    strcpy( m_stNotifyIcon.szTip, title );

    Shell_NotifyIcon( NIM_ADD, &m_stNotifyIcon );

	return TRUE;
}

void CChirrupDlg::OnDestroy() 
{
	CDialog::OnDestroy();
    Shell_NotifyIcon( NIM_DELETE, &m_stNotifyIcon );
}

LRESULT CChirrupDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    if ( message == WM_APP_TASKTRY ) {
        if ( lParam == WM_RBUTTONDOWN ) {
            // タスクトレイのアイコンを右クリックしたとき
            DWORD   dwPos = GetMessagePos();
            WORD    wX    = LOWORD( dwPos );
            WORD    wY    = HIWORD( dwPos );

            BOOL    isContinued = ExtraContextMenu( wX, wY );
            PostMessage( WM_NULL );

            if ( !isContinued )
                OnCancel();
        }
        else if ( lParam == WM_LBUTTONDBLCLK ) {
            // タスクトレイのアイコンをダブルクリックしたとき
            OpenIcon();
            SetForegroundWindow();
            PostMessage( WM_NULL );
        }
    }
	
	return CDialog::WindowProc(message, wParam, lParam);
}

void CChirrupDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CString cmd = "";

    switch (nID & 0xFFF0) {
    case IDM_ABOUTBOX:
        switch (nID) {
        case IDM_ABOUTBOX: {
            CAboutDlg dlgAbout;
            dlgAbout.DoModal(); }
            break;

        case IDM_ABOUT_SUPPORT:
            if (cmd.IsEmpty())
    	        cmd.LoadString( IDS_WEB_URL );
            /* fall into ... */
        case IDM_ABOUT_SUPPORT2:
            if (cmd.IsEmpty())
    	        cmd.LoadString( IDS_CHIRRUP_SUPPORT );
            /* fall into ... */
        case IDM_ABOUT_COMMUNITY:
            if (cmd.IsEmpty())
    	        cmd.LoadString( IDS_CHIRRUP_COMMUNITY );
            /* fall into ... */
        case IDM_ABOUT_COMMUNITY2:
            if (cmd.IsEmpty())
    	        cmd.LoadString( IDS_CHIRRUP_COMMUNITY2 );
            ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
            break;
        }
        break;

    default:
		CDialog::OnSysCommand(nID, lParam);
        break;
    }
}

void CChirrupDlg::OnPaint() 
{
	if ( IsIconic() ) {
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);

		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else {
		CDialog::OnPaint();
	}
}

HCURSOR CChirrupDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CChirrupDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

    if ( bShow ) {
        LOGFONT tLogFont;
        CFont   *cWndFont;

        cWndFont = GetFont(); 
        cWndFont->GetLogFont( &tLogFont );
        m_cFont1.CreateFontIndirect( &tLogFont );

        tLogFont.lfUnderline = 1;
        m_cFont2.CreateFontIndirect( &tLogFont );

        CWaitCursor         cur;    // マウスカーソルを砂時計表示
        ProceedingDialog    *pdlg = new ProceedingDialog();

        pdlg->Create( IDD_PROCEEDING_DIALOG );
        pdlg->ChangeDialogText( "起動中",
                                "chirrup 起動中……" );

        bool        needToSave = false;
        CChirrupApp *ap = (CChirrupApp *)AfxGetApp();
		ap->m_chirrpDlg = this;
        ap->m_event = CreateEvent( NULL, TRUE, FALSE, NULL );

        CString sigHead = _T("");
        CString sigTail = _T("");
        sigHead.LoadString( IDS_SIG_HEAD );
        sigTail.LoadString( IDS_SIG_TAIL );
        SetSigInfo( ap->m_fKey, ap->m_fSecret, sigHead, sigTail );

        sigHead.LoadString( IDS_TWITTER_OA001 );
        sigTail.LoadString( IDS_TWITTER_OA002 );
        SetSigInfo( ap->m_tcKey, ap->m_tcSecret, sigHead, sigTail );

        sigHead.LoadString( IDS_JAIKU_OA001 );
        sigTail.LoadString( IDS_JAIKU_OA002 );
        SetSigInfo( ap->m_jcKey, ap->m_jcSecret, sigHead, sigTail );

        sigHead = _T("");
        sigTail = _T("");

        setConfirmProxyInfoFunc( (CONF_FUNC)(-1) );
        LoadSetting();
        if ( ap->m_proxyPort == -1 ) {
            unsigned short  proxyPort = 0;
            ap->m_isUsedProxy = false;
            GetProxyInfo( ap->m_isUsedProxy,
                          ap->m_proxyServer, proxyPort,
                          ap->m_proxyUserName, ap->m_proxyPassword );
            ap->m_proxyPort = proxyPort;
            if ( ap->m_isUsedProxy &&
                 (ap->m_proxyUserName.GetLength() == 0) ) {
                pdlg->ShowWindow( SW_HIDE );
                DoSettingProxy( this );
                pdlg->ShowWindow( SW_SHOW );
                pdlg->ChangeDialogText( "起動中",
                                        "chirrup 起動中……" );
                setProxyInfo( ap->m_proxyServer,
                              (unsigned short)(ap->m_proxyPort),
                              ap->m_proxyUserName,
                              ap->m_proxyPassword );
            }
            m_needToSave = true;
        }
        else {
            if ( ap->m_isUsedProxy )
                setProxyInfo( ap->m_proxyServer,
                              (unsigned short)(ap->m_proxyPort),
                              ap->m_proxyUserName,
                              ap->m_proxyPassword );
        }
        setUseProxy( ap->m_isUsedProxy );
        setConfirmProxyInfoFunc( confirmProxyInfo );

        if ( (!m_twitter                                           ||
              (!m_twitter->m_useOAuth                         &&
               ((m_twitter->m_username.GetLength() == 0) ||
                (m_twitter->m_password.GetLength() == 0)    )    )    ) &&
             (!m_jaiku                                             ||
              (!m_jaiku->m_useOAuth                           &&
               ((m_jaiku->m_username.GetLength() == 0)   ||
                (m_jaiku->m_password.GetLength() == 0)      )    )    ) &&
             (!m_wassr                                     ||
              (m_wassr->m_username.GetLength() == 0)       ||
              (m_wassr->m_password.GetLength() == 0)          ) &&
             (!m_mogo2                                     ||
              (m_mogo2->m_username.GetLength() == 0)       ||
              (m_mogo2->m_password.GetLength() == 0)          ) &&
             (!m_timelog                                   ||
              (m_timelog->m_username.GetLength() == 0)     ||
              (m_timelog->m_password.GetLength() == 0)        ) &&
             (!m_haruFm                                    ||
              (m_haruFm->m_username.GetLength() == 0)      ||
              (m_haruFm->m_password.GetLength() == 0)         ) &&
             (!m_hatenaHaiku                               ||
              (m_hatenaHaiku->m_username.GetLength() == 0) ||
              (m_hatenaHaiku->m_password.GetLength() == 0)    )    ) {
            EnterCriticalSection();
            m_inSetting = true;
            LeaveCriticalSection();

            pdlg->ShowWindow( SW_HIDE );
            CSettingDialog  dlg;
            dlg.m_chirrup = this;
            int ret = dlg.DoModal();
            if ( ret == IDOK )
                needToSave = true;

            EnterCriticalSection();
            m_inSetting = false;
            LeaveCriticalSection();

            pdlg->ShowWindow( SW_SHOW );
            pdlg->ChangeDialogText( "起動中",
                                    "chirrup 起動中……" );
        }

        if ( needToSave ) {
            m_needToSave = true;
            SaveSetting();
            LoadSetting();
        }
        ReduceExtra();
        SwitchCapture();
        SwitchImetter();

        CStatic *sp = (CStatic *)GetDlgItem( IDC_CAT );
        sp->ShowWindow( SW_HIDE );

        m_showServiceName = false;
        sp = (CStatic *)GetDlgItem( IDC_EXECUTING );
        sp->ShowWindow( SW_HIDE );

        CString periodStr = _T("");
        CEdit   *p = (CEdit *)GetDlgItem( IDC_PERIOD );
	    
        char    temp[16];
        temp[0] = NUL;
        m_periodStr = ltoa( m_period / (60 * 1000), temp, 10 );
        p->SetWindowText( m_periodStr );

        CButton *bp = (CButton *)GetDlgItem( IDC_CHECK_BROWSING );
        bp->SetCheck( m_checkBrowsing );

        bp = (CButton *)GetDlgItem( IDC_CHECK_MULTIPOST );
        bp->SetCheck( m_postMulti );
        SwitchMultiPost();

        m_messageCtrl.SetAutoUrlDetect();
        m_messageCtrl.SetBackgroundColor( FALSE, 0x00F0F0F0 );  // 0x00bbggrr

        CFont m_fnt;
        m_fnt.CreatePointFont( 100, "ＭＳ Ｐゴシック" );
        m_messageCtrl.SetFont( &m_fnt );

        SwitchTitle();
        SwitchTimelineFacilities();

        m_pageTitle = _T("");
        if ( m_checkBrowsing )
            m_urlBrowsing = GetUrlInBrowsing( m_pageTitle );
        delete pdlg;

        if ( m_twitter     ||
             m_jaiku       ||
             m_wassr       ||
             m_mogo2       ||
             m_timelog     ||
             m_haruFm      ||
             m_hatenaHaiku    )
            OnUpdate();

        p = (CEdit *)GetDlgItem( IDC_MONOLOGUE );
        p->SetFocus();
        m_messageCtrl.m_chirrupDlg = this;

        if ( (m_cx != m_cxInitial) || (m_cy != m_cyInitial) ) {
            // ウィンドウサイズ復元
            CRect   rect_st;
            m_status.GetWindowRect( rect_st );
            int     adjustHeight = rect_st.bottom - rect_st.top;
            adjustHeight += ADJUST_HEIGHT;  // 補正

            MoveWindow( 0, 0, m_cx, m_cy + adjustHeight, TRUE );
            OnSize( FORTH_REDRAW, m_cx, m_cy );
        }
    }
}


void CChirrupDlg::OnPostMonologue() 
{
    CEdit   *cp = (CEdit *)GetDlgItem( IDC_MONOLOGUE );
    CButton *bp = (CButton *)GetDlgItem( IDC_POST_MONOLOGUE );
    bp->EnableWindow( FALSE );

    CString str;
    bp->GetWindowText( str );
    if ( !str.Compare( _T("キャンセル") ) ) {
        cp->SetWindowText( _T("") );
        cp->SetReadOnly( FALSE );
        bp->SetWindowText( m_useImetter ? "いめったー" : "発言" );
    }
    else {
        cp->GetWindowText( m_monologue );
        if ( m_monologue.GetLength() > 0 ) {
            cp->SetReadOnly( TRUE );

            m_postTweet.dlg          = this;
            m_postTweet.monologue    = m_monologue;
            m_postTweet.timelineType = m_timelineType;
            m_postTweet.ret          = false;

            PostMonologue( &m_postTweet );
            bp->SetWindowText( _T("キャンセル") );
        }
    }

    bp->EnableWindow( TRUE );
}


void CChirrupDlg::ExecuteUpdate( CManager *p )
{
    ProceedingDialog    *pdlg = NULL;
    CChirrupApp         *ap = (CChirrupApp *)AfxGetApp();

    m_stNotifyIcon.hIcon = ap->LoadIcon( IDR_MAINFRAME );
    Shell_NotifyIcon( NIM_MODIFY, &m_stNotifyIcon );

    ShowServiceName( false );
    CStatic *sp = (CStatic *)GetDlgItem( IDC_EXECUTING );
        sp->SetWindowText( "情報を取得します……" );
    sp->ShowWindow( SW_SHOW );

    if ( !(p->m_serviceSymbol.Compare("Twitter")) ) {
        ((CTwitterManager *)p)->ExecuteUpdate(sp, m_useTwitStar, this, pdlg);
        m_serviceName =
            ((CTwitter *)(m_twitter->m_service))->GetRateLimitStatus();
    }
    else
        p->ExecuteUpdate( sp, m_useTwitStar, this, pdlg );

    sp->SetWindowText( "情報取得終了……" );
    DisplayTimeline();

    sp->SetWindowText( "" );
    sp->ShowWindow( SW_HIDE );
    ShowServiceName( true );

    m_stNotifyIcon.hIcon = ap->LoadIcon( IDI_TASKTRAY_ICON );
    Shell_NotifyIcon( NIM_MODIFY, &m_stNotifyIcon );
}

void CChirrupDlg::ExecuteUpdate( CString timelineType )
{
 // CWaitCursor         cur;    // マウスカーソルを砂時計表示
    ProceedingDialog    *pdlg = NULL;
    CChirrupApp         *ap = (CChirrupApp *)AfxGetApp();

    m_stNotifyIcon.hIcon = ap->LoadIcon( IDR_MAINFRAME );
    Shell_NotifyIcon( NIM_MODIFY, &m_stNotifyIcon );

    ShowServiceName( false );
    CStatic *sp = (CStatic *)GetDlgItem( IDC_EXECUTING );
        sp->SetWindowText( "情報を取得します……" );
    sp->ShowWindow( SW_SHOW );

    if ( m_twitter ) {
        if ( m_twitter->m_useOAuth                         ||
             ((m_twitter->m_username.GetLength() > 0) &&
              (m_twitter->m_password.GetLength() > 0)    )    ) {
            m_twitter->ExecuteUpdate( sp, m_useTwitStar, this, pdlg );
            m_twitterHealthy = m_twitter->m_twitterHealthy;
            m_serviceName =
                ((CTwitter *)(m_twitter->m_service))->GetRateLimitStatus();
        }
    }
    if ( m_jaiku ) {
        if ( m_jaiku->m_useOAuth                         ||
             ((m_jaiku->m_username.GetLength() > 0) &&
              (m_jaiku->m_password.GetLength() > 0)    )    ) {
            m_jaiku->ExecuteUpdate( sp, m_useTwitStar, this, pdlg );
        }
    }
    if ( m_wassr ) {
        if ( (m_wassr->m_username.GetLength() > 0) &&
             (m_wassr->m_password.GetLength() > 0)    ) {
            m_wassr->ExecuteUpdate( sp, m_useTwitStar, this, pdlg );
        }
    }
    if ( m_mogo2 ) {
        if ( (m_mogo2->m_username.GetLength() > 0) &&
             (m_mogo2->m_password.GetLength() > 0)    ) {
            m_mogo2->ExecuteUpdate( sp, m_useTwitStar, this, pdlg );
        }
    }
    if ( m_timelog ) {
        if ( (m_timelog->m_username.GetLength() > 0) &&
             (m_timelog->m_password.GetLength() > 0)    ) {
            m_timelog->ExecuteUpdate( sp, m_useTwitStar, this, pdlg );
        }
    }
    if ( m_haruFm ) {
        if ( (m_haruFm->m_username.GetLength() > 0) &&
             (m_haruFm->m_password.GetLength() > 0)    ) {
            m_haruFm->ExecuteUpdate( sp, m_useTwitStar, this, pdlg );
        }
    }
    if ( m_hatenaHaiku ) {
        if ( (m_hatenaHaiku->m_username.GetLength() > 0) &&
             (m_hatenaHaiku->m_password.GetLength() > 0)    ) {
            m_hatenaHaiku->ExecuteUpdate( sp, m_useTwitStar, this, pdlg );
        }
    }

    sp->SetWindowText( "情報取得終了……" );
    DisplayTimeline();

    sp->SetWindowText( "" );
    sp->ShowWindow( SW_HIDE );

    m_stNotifyIcon.hIcon  = ap->LoadIcon( IDI_TASKTRAY_ICON );
    Shell_NotifyIcon( NIM_MODIFY, &m_stNotifyIcon );

    m_count++;
    if ( m_checkBrowsing && ((m_count % 20) == 19) && m_twitterHealthy ) {
        m_pageTitle = _T("");
        CString url = GetUrlInBrowsing( m_pageTitle );

        if ( url.GetLength() > 0 ) {
            if ( url.Compare( m_urlBrowsing ) != 0 ) {
                m_urlBrowsing = url;

                CString monologue = _T("Browsing ");
                if ( m_pageTitle.GetLength() > 0 ) {
                    char    *title = new char [m_pageTitle.GetLength() + 1];
                    strcpy( title, m_pageTitle );
                    monologue += normalizeDescription( title, 80 );
                    monologue += _T(" - ");
                    delete [] title;
                }
                monologue += m_urlBrowsing;
                monologue += _T(" ...");

                m_postBrowse.dlg          = this;
                m_postBrowse.monologue    = monologue;
                m_postBrowse.timelineType = timelineType;
                m_postBrowse.ret          = false;
                PostMonologue( &m_postBrowse );
            }
        }
    }
    if ( m_count >= 1234560 ) /* このマジックナンバー 1234560 は暫定 */
        m_count = 0;

    sp = (CStatic *)GetDlgItem( IDC_CAT );
    sp->ShowWindow( m_twitterHealthy ? SW_HIDE : SW_SHOW );
    ShowServiceName( true );
}

UINT
_ExecuteUpdate( LPVOID pParam )
{
    PARAM_UPDATE    *p  = (PARAM_UPDATE *)pParam;
    UINT            ret = 0;

    if ( p && p->dlg ) {
        if ( p->manager )
            p->dlg->ExecuteUpdate( p->manager );
        else
            p->dlg->ExecuteUpdate( p->timelineType );
    }

    return ( ret );
}


void CChirrupDlg::OnUpdate() 
{
    KillTimer( ID_UPDATE_TWITTER );

    EnterCriticalSection();
    if ( !m_updateThread && !m_postThread ) {
        m_param.dlg              = this;
        m_param.manager          = NULL;
        m_param.timelineType     = m_timelineType;
        m_startTime_updateThread = CTime::GetCurrentTime();
        m_updateThread_Fired     = false;
        m_updateThread = AfxBeginThread( _ExecuteUpdate, (void *)&m_param );
        if ( m_updateThread ) {
            m_updateThread->m_bAutoDelete = FALSE;
            SetTimer( ID_THREAD_UPDATE_TWITTER,
                      MS_THREAD_UPDATE_TWITTER,
                      NULL );
        }
    }
    LeaveCriticalSection();

    SetTimer( ID_UPDATE_TWITTER, m_period, NULL );
}

void CChirrupDlg::UpdateSingle( CManager *manager ) 
{
    KillTimer( ID_UPDATE_TWITTER );

    EnterCriticalSection();
    if ( !m_updateThread && !m_postThread ) {
        m_param.dlg              = this;
        m_param.manager          = manager;
        m_param.timelineType     = m_timelineType;
        m_startTime_updateThread = CTime::GetCurrentTime();
        m_updateThread_Fired     = false;
        m_updateThread = AfxBeginThread( _ExecuteUpdate, (void *)&m_param );
        if ( m_updateThread ) {
            m_updateThread->m_bAutoDelete = FALSE;
            SetTimer( ID_THREAD_UPDATE_TWITTER,
                      MS_THREAD_UPDATE_TWITTER,
                      NULL );
        }
    }
    LeaveCriticalSection();

    SetTimer( ID_UPDATE_TWITTER, m_period, NULL );
}

void CChirrupDlg::UpdateSingle()
{
    CTwitterTimeline    *tp = GetCurrentTimeline();
    switch ( tp->m_serviceType ) {
    case CTwitterTimeline::SVC_JAIKU:
        if ( m_jaiku )
            UpdateSingle( m_jaiku );
        break;

    case CTwitterTimeline::SVC_WASSR:
        if ( m_wassr )
            UpdateSingle( m_wassr );
        break;

    case CTwitterTimeline::SVC_MOGO2:
        if ( m_mogo2 )
            UpdateSingle( m_mogo2 );
        break;

    case CTwitterTimeline::SVC_TIMELOG:
        if ( m_timelog )
            UpdateSingle( m_timelog );
        break;

    case CTwitterTimeline::SVC_HARUFM:
        if ( m_haruFm )
            UpdateSingle( m_haruFm );
        break;

    case CTwitterTimeline::SVC_HATENAHAIKU:
        if ( m_hatenaHaiku )
            UpdateSingle( m_hatenaHaiku );
        break;

    case CTwitterTimeline::SVC_TWITTER:
        if ( m_twitter ) {
            if ( m_twitterHealthy ) {
                UpdateSingle( m_twitter );
                m_twitterHealthy = m_twitter->m_twitterHealthy;
            }
        }
        break;

    default:
        break;
    }
}

void CChirrupDlg::OnTimer(UINT nIDEvent) 
{
    if ( nIDEvent == ID_UPDATE_TWITTER ) {
        if ( m_inSetting ) {
            // 「設定」中は OnUpdate() しない
            KillTimer( ID_UPDATE_TWITTER );
            SetTimer( ID_UPDATE_TWITTER, m_period, NULL );
            return;
        }

        OnUpdate();
        return;
    }
    else if ( nIDEvent == ID_THREAD_UPDATE_TWITTER ) {
        CWinThread  *p;

        KillTimer( nIDEvent );
        EnterCriticalSection();
        p = m_updateThread;
        LeaveCriticalSection();
        if ( p ) {
            DWORD   exitCode = 0;
            int     status;
            CWaitCursor cur;    // マウスカーソルを砂時計表示

            EnterCriticalSection();
            status = GetExitCodeThread( p->m_hThread, &exitCode );
            LeaveCriticalSection();
            if ( (status != FALSE) && (exitCode == STILL_ACTIVE) ) {
                CTime now = CTime::GetCurrentTime();
                if (now - m_startTime_updateThread > 3 * m_period / 1000) {
#ifdef  _DEBUG
                    MessageBox(
                       "規定時間以内にタイムラインの取得ができませんでした  ",
                       "情報取得失敗",
                       MB_OK|MB_ICONINFORMATION );
#endif
                    CStatic *sp = (CStatic *)GetDlgItem( IDC_EXECUTING );
                    sp->SetWindowText( "情報取得失敗……" );
                    sp->ShowWindow( SW_SHOW );

                    CChirrupApp *ap = (CChirrupApp *)AfxGetApp();
                    m_stNotifyIcon.hIcon = ap->LoadIcon( IDI_TASKTRAY_ICON );
                    Shell_NotifyIcon( NIM_MODIFY, &m_stNotifyIcon );

                    if ( ap->m_event ) {
                        if ( !m_updateThread_Fired )
                            SetEvent( ap->m_event ); // fire!
                        else {
                            DWORD   r = WaitForSingleObject( ap->m_event, 0 );
                            if ( r != WAIT_OBJECT_0 )
                                SetEvent( ap->m_event ); // fire, again
                        }
                        m_updateThread_Fired = true;
                    }
                    else {
                        DWORD   stat = p->SuspendThread();
                        if ( stat == 0xFFFFFFFF )
                            MessageBox(
                                "タイムライン取得スレッドで何らかの異常発生?  ",
                                "情報取得失敗",
                                MB_OK|MB_ICONINFORMATION );
                        else {
                            try {
                                p->ExitInstance();
                            }
                            catch (...) {
                                try {
                                    TerminateThread( p->m_hThread, 0 );
                                }
                                catch (...) {           
                                    sp->SetWindowText( "何らかの異常発生" );
                                    sp->ShowWindow( SW_SHOW );
                                }
                            }
                        }

                        try {
                            EnterCriticalSection();
                            delete m_updateThread;
                            m_updateThread = NULL;
                            m_updateThread_Fired = false;
                            LeaveCriticalSection();
                        }
                        catch (...) {
                            MessageBox(
                                "タイムライン取得スレッドを停止しようとして異常が"
                                "発生しました  ",
                                "情報取得失敗",
                                MB_OK|MB_ICONINFORMATION );
                        }

                     // sp->SetWindowText( "" );
                     // sp->ShowWindow( SW_HIDE );

                        return;
                    }
                }
             // SetFocus();
                UpdateWindow(); // CChirrupDlg の再描画
                SetTimer( nIDEvent, MS_THREAD_UPDATE_TWITTER, NULL );
            }
            else {
                EnterCriticalSection();
                delete m_updateThread;
                m_updateThread = NULL;
                m_updateThread_Fired = false;
                LeaveCriticalSection();

                CEdit *p = (CEdit *)GetDlgItem( IDC_MONOLOGUE );
                p->GetWindowText( m_monologue );
                p->SetFocus();
                if ( m_monologue.GetLength() > 0 ) {
                    p->SetSel(0, -1, TRUE);
                    p->SetSel(-1, -1, FALSE);
                }
            }
        }

        return;
    }
    else if ( nIDEvent == ID_THREAD_POST_TWITTER ) {
        CWinThread  *p;

        KillTimer( nIDEvent );
        EnterCriticalSection();
        p = m_postThread;
        LeaveCriticalSection();
        if ( p ) {
            DWORD   exitCode = 0;
            int     status;
            CWaitCursor cur;    // マウスカーソルを砂時計表示

            EnterCriticalSection();
            status = GetExitCodeThread( p->m_hThread, &exitCode );
            LeaveCriticalSection();
            if ( (status != FALSE) && (exitCode == STILL_ACTIVE) ) {
             // SetFocus();
                UpdateWindow(); // CChirrupDlg の再描画
                SetTimer( nIDEvent, MS_THREAD_POST_TWITTER, NULL );
            }
            else {
                bool    r = false;

                EnterCriticalSection();
                delete m_postThread;
                m_postThread = NULL;

                if ( m_postTweet.ret ) {
                    m_postTweet.ret = false;
                    r = true;
                }
                LeaveCriticalSection();

                CEdit *cp = (CEdit *)GetDlgItem( IDC_MONOLOGUE );
                if ( r ) {
                    m_monologue = _T("");
                    cp->SetWindowText( m_monologue );
                }
                cp->SetReadOnly( FALSE );

                CButton *bp = (CButton *)GetDlgItem( IDC_POST_MONOLOGUE );
                bp->EnableWindow( TRUE );

                if ( !m_postMulti )
                    UpdateSingle();
            }
        }

        return;
    }
    else if ( nIDEvent == ID_THREAD_UPLAOD_IMAGE ) {
        CWinThread  *p;

        KillTimer( nIDEvent );
        EnterCriticalSection();
        p = m_uploadImageThread;
        LeaveCriticalSection();
        if ( p ) {
            DWORD   exitCode = 0;
            int     status;
            CWaitCursor cur;    // マウスカーソルを砂時計表示

            EnterCriticalSection();
            status = GetExitCodeThread( p->m_hThread, &exitCode );
            LeaveCriticalSection();
            if ( (status != FALSE) && (exitCode == STILL_ACTIVE) ) {
             // SetFocus();
                UpdateWindow(); // CChirrupDlg の再描画
                SetTimer( nIDEvent, MS_THREAD_UPLAOD_IMAGE, NULL );
            }
            else {
                EnterCriticalSection();
                delete m_uploadImageThread;
                m_uploadImageThread = NULL;
                LeaveCriticalSection();
            }
        }

        return;
    }
    else if ( nIDEvent == ID_WAITED_UPLAOD_IMAGE ) {
        const char  *filename;

        KillTimer( nIDEvent );

        EnterCriticalSection();
        filename = m_waitedFilename;
        LeaveCriticalSection();

        UploadImage( filename );

        EnterCriticalSection();
        m_waitedFilename[0] = NUL;
        LeaveCriticalSection();
    }

	CDialog::OnTimer(nIDEvent);
}

void CChirrupDlg::OnKillfocusPeriod() 
{
    CString periodStr = _T("");
    CEdit   *p = (CEdit *)GetDlgItem( IDC_PERIOD );
    p->GetWindowText( periodStr );
	
    long    period = atol( periodStr );
    if ( (period > 0) && (period < 24 * 60) ) {
        if ( m_period != period * 60 * 1000 ) {
            m_period = period * 60 * 1000;
            KillTimer( ID_UPDATE_TWITTER );
            SetTimer( ID_UPDATE_TWITTER, m_period, NULL );
            m_needToSave = true;
            SaveSetting();
        }

        char    temp[16];

        temp[0] = NUL;
        m_periodStr = ltoa( m_period / (60 * 1000), temp, 10 );
        p->SetWindowText( m_periodStr );
    }
}

void CChirrupDlg::OnTwitter() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_TWITTER );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnHatenagroup() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_HATENAGROUP );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnHatenabookmark() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_HATENABOOKMARK );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnHatenastar() 
{
	CString             cmd;
    CTwitterTimeline    *tlp = GetCurrentTimeline();
    if ( tlp->m_serviceType == CTwitterTimeline::SVC_MOGO2 )
    	cmd.LoadString( IDS_URL_MOGO2STAR );
    else
    	cmd.LoadString( IDS_URL_HATENASTAR );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnDelicous() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_DELICIOUS );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnGooglegroups() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_GOOGLEGROUPS );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnTwitterwiki() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_TWITTERWIKI );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnTwitterChirrup() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_TWITTER_CHIRRUP );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnMixi() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_MIXI );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnDigg() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_DIGG );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnMagnolia() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_MAGNOLIA );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}


void CChirrupDlg::OnLivedoorclip() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_LIVEDOORCLIP );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnLivedoor() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_LIVEDOOR );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnGoogle() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_GOOGLE );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnYahoo() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_YAHOO );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnBloglines() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_BLOGLINES );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnTwitterSearch() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_TWITTER_SEARCH );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnFavotter() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_FAVOTTER );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnTumblr() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_TUMBLR );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnGyazo() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_GYAZO );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnHatenaFotolife() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_HATENAFOTOLIFE );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnFlickr() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_FLICKR );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnJaiku() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_JAIKU );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnMogo2() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_MOGO2 );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnWassr() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_WASSR );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnTimelog() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_TIMELOG );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnHarufm() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_HARUFM );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnHatenaHaiku() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_HATENAHAIKU );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CChirrupDlg::OnTwitterSNS() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_TWITTERSNS );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

BOOL CChirrupDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
    if ( nHitTest == HTCLIENT ) {
        static int targetIDC[] = {
            IDC_TWITTER,
            IDC_TWITTERWIKI,
            IDC_HATENAGROUP,
            IDC_HATENABOOKMARK,
            IDC_HATENASTAR,
            IDC_DELICIOUS,
            IDC_GOOGLEGROUPS,
            IDC_TWITTER_CHIRRUP,
            IDC_MIXI,
            IDC_DIGG,
            IDC_MAGNOLIA,
            IDC_LIVEDOORCLIP,
            IDC_LIVEDOOR,
            IDC_GOOGLE,
            IDC_YAHOO,
            IDC_BLOGLINES,
            IDC_TWITTER_SEARCH,
            IDC_FAVOTTER,
            IDC_TUMBLR,
            IDC_GYAZO,
            IDC_FLICKR,
            IDC_HATENAFOTOLIFE,
            IDC_JAIKU,
            IDC_MOGO2,
            IDC_WASSR,
            IDC_TIMELOG,
            IDC_HARUFM,
            IDC_HATENAHAIKU,
            IDC_TWITTERSNS,
            -1
        };

		DWORD   dwPos = GetMessagePos();
		WORD    wX    = LOWORD( dwPos );
		WORD    wY    = HIWORD( dwPos );

        int i;
        for ( i = 0; targetIDC[i] > 0; i++ ) {
            if ( IsInner( targetIDC[i], wX, wY ) ) {
			    SetCursor( m_hCursor );
                return TRUE;
            }
        }

        for ( i = 0; i < MAX_NUMOFFRIENDS; i++ ) {
            if ( IsInner( IDC_FRIEND001 + i, wX, wY ) ) {
			    SetCursor( m_hCursor );
                return TRUE;
            }
        }

        if ( m_showServiceName ) {
            if ( IsInner( IDC_EXECUTING, wX, wY ) ) {
			    SetCursor( m_hCursor );
                return TRUE;
            }
        }
	}

    SetPaneText( 0, _T(" ") );
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}


#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
void CChirrupDlg::OnDisplayToolTip(NMHDR* pNMHDR, LRESULT* pResult)
{
    TOOLTIPTEXT *tp = (TOOLTIPTEXT *)pNMHDR;

    if ( (tp->uFlags & TTF_IDISHWND) == TTF_IDISHWND ) {
        int id = ::GetDlgCtrlID( (HWND)tp->hdr.idFrom );
        CString text = _T("");

        switch ( id ) {
        case IDC_TWITTER:
            text = _T("Twitter");
            if ( m_twitter ) {
                text += _T(" (同時投稿対象");
                text += m_twitter->m_simultaneousPost ? _T(")") : _T("外)");
            }
            break;
        case IDC_TWITTERWIKI:
            text = _T("Twitter fan Wiki");
            break;
        case IDC_HATENAGROUP:
            text = _T("ついったー部 (はてなグループ)");
            break;
        case IDC_HATENABOOKMARK:
            text = _T("twitter に関する「はてなブックマーク」");
            break;
        case IDC_HATENASTAR: {
            CTwitterTimeline    *tlp = GetCurrentTimeline();
            if ( tlp->m_serviceType == CTwitterTimeline::SVC_MOGO2 )
                text = _T("もごすた");
            else
                text = _T("ついすた"); }
            break;
        case IDC_DELICIOUS:
            text = _T("del.icio.us での twitter に関する話題");
            break;
        case IDC_GOOGLEGROUPS:
            text = _T("Twitter Development Talk (Google Groups)");
            break;
        case IDC_TWITTER_CHIRRUP:
            text = _T("Chirrup ユーザへのお知らせ");
            break;
        case IDC_MIXI:
            text = _T("Twitterコミュニティ (mixi)");
            break;
        case IDC_DIGG:
            text = _T("digg での twitter に関する話題");
            break;
        case IDC_MAGNOLIA:
            text = _T("ma.glolia での twitter に関する話題");
            break;
        case IDC_LIVEDOORCLIP:
            text = _T("livedoor クリップでの twitter に関する話題");
            break;
        case IDC_LIVEDOOR:
            text = _T("livedoor で twitter をブログ検索");
            break;
        case IDC_GOOGLE:
            text = _T("Google で twitter を検索");
            break;
        case IDC_YAHOO:
            text = _T("Yahoo! で twitter を検索");
            break;
        case IDC_BLOGLINES:
            text = _T("Bloglines で twitter をブログ検索");
            break;
        case IDC_TWITTER_SEARCH:
            text = _T("Twitter 検索");
            break;
        case IDC_FAVOTTER:
            text = _T("ふぁぼったー");
            break;
        case IDC_TUMBLR:
            text = _T("tumblr");
            break;
        case IDC_GYAZO:
            text = _T("Gyazo");
            break;
        case IDC_FLICKR:
            text = _T("Flickr");
            break;
        case IDC_HATENAFOTOLIFE:
            text = _T("はてなフォトライフ");
            break;
        case IDC_TWITTERSNS:
            text = _T("ついったー部SNS支局");
            break;
        case IDC_JAIKU:
            text = _T("Jaiku");
            if ( m_jaiku ) {
                text += _T(" (同時投稿対象");
                text += m_jaiku->m_simultaneousPost ? _T(")") : _T("外)");
            }
            break;
        case IDC_MOGO2:
            text = _T("もごもご");
            if ( m_mogo2 ) {
                text += _T(" (同時投稿対象");
                text += m_mogo2->m_simultaneousPost ? _T(")") : _T("外)");
            }
            break;
        case IDC_WASSR:
            text = _T("Wassr");
            if ( m_wassr ) {
                text += _T(" (同時投稿対象");
                text += m_wassr->m_simultaneousPost ? _T(")") : _T("外)");
            }
            break;
        case IDC_TIMELOG:
            text = _T("Timelog");
            if ( m_timelog ) {
                text += _T(" (同時投稿対象");
                text += m_timelog->m_simultaneousPost ? _T(")") : _T("外)");
            }
            break;
        case IDC_HARUFM:
            text = _T("Haru.fm");
            if ( m_haruFm ) {
                text += _T(" (同時投稿対象");
                text += m_haruFm->m_simultaneousPost ? _T(")") : _T("外)");
            }
            break;
        case IDC_HATENAHAIKU:
            text = _T("はてなハイク");
            if ( m_hatenaHaiku ) {
                text += _T(" (同時投稿対象");
                text += m_hatenaHaiku->m_simultaneousPost ? _T(")") : _T("外)");
            }
            break;

        case IDC_CAT:
            text = _T("ツン");
            break;

        case IDC_FRIEND001:
        case IDC_FRIEND002:
        case IDC_FRIEND003:
        case IDC_FRIEND004:
        case IDC_FRIEND005:
        case IDC_FRIEND006:
        case IDC_FRIEND007:
        case IDC_FRIEND008:
        case IDC_FRIEND009:
        case IDC_FRIEND010:
        case IDC_FRIEND011:
        case IDC_FRIEND012:
        case IDC_FRIEND013:
        case IDC_FRIEND014:
        case IDC_FRIEND015:
        case IDC_FRIEND016:
        case IDC_FRIEND017:
        case IDC_FRIEND018:
        case IDC_FRIEND019:
        case IDC_FRIEND020:
            text = GetSceenNameOfFriend( id );
            break;
        }

        if ( text.GetLength() > 0 )
            strcat( tp->szText, text );
    }
}
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif

void CChirrupDlg::OnOK() 
{
    if ( m_needToSave )
        SaveSetting();

    /* 終了せずに処理続行 */
}

void CChirrupDlg::OnCancel() 
{
#ifdef  _DEBUG
    _CrtDumpMemoryLeaks();
#endif

    if ( m_needToSave          ||
         (m_cx != m_cxInitial) ||
         (m_cy != m_cyInitial)    )
        SaveSetting();

    int r = MessageBox( "本当に終了してもいいんですか?  ",
                        "終了確認",
                        MB_YESNO|MB_ICONWARNING );
    if ( r == IDYES )
	    CDialog::OnCancel();
}

void CChirrupDlg::OnFriend001() 
{
    PostMessageToFriend( IDC_FRIEND001 );
}

void CChirrupDlg::OnFriend002() 
{
    PostMessageToFriend( IDC_FRIEND002 );
}

void CChirrupDlg::OnFriend003() 
{
    PostMessageToFriend( IDC_FRIEND003 );
}

void CChirrupDlg::OnFriend004() 
{
    PostMessageToFriend( IDC_FRIEND004 );
}

void CChirrupDlg::OnFriend005() 
{
    PostMessageToFriend( IDC_FRIEND005 );
}

void CChirrupDlg::OnFriend006() 
{
    PostMessageToFriend( IDC_FRIEND006 );
}

void CChirrupDlg::OnFriend007() 
{
    PostMessageToFriend( IDC_FRIEND007 );
}

void CChirrupDlg::OnFriend008() 
{
    PostMessageToFriend( IDC_FRIEND008 );
}

void CChirrupDlg::OnFriend009() 
{
    PostMessageToFriend( IDC_FRIEND009 );
}

void CChirrupDlg::OnFriend010() 
{
    PostMessageToFriend( IDC_FRIEND010 );
}

void CChirrupDlg::OnFriend011() 
{
    PostMessageToFriend( IDC_FRIEND011 );
}

void CChirrupDlg::OnFriend012() 
{
    PostMessageToFriend( IDC_FRIEND012 );
}

void CChirrupDlg::OnFriend013() 
{
    PostMessageToFriend( IDC_FRIEND013 );
}

void CChirrupDlg::OnFriend014() 
{
    PostMessageToFriend( IDC_FRIEND014 );
}

void CChirrupDlg::OnFriend015() 
{
    PostMessageToFriend( IDC_FRIEND015 );
}

void CChirrupDlg::OnFriend016() 
{
    PostMessageToFriend( IDC_FRIEND016 );
}

void CChirrupDlg::OnFriend017() 
{
    PostMessageToFriend( IDC_FRIEND017 );
}

void CChirrupDlg::OnFriend018() 
{
    PostMessageToFriend( IDC_FRIEND018 );
}

void CChirrupDlg::OnFriend019() 
{
    PostMessageToFriend( IDC_FRIEND019 );
}

void CChirrupDlg::OnFriend020() 
{
    PostMessageToFriend( IDC_FRIEND020 );
}

#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
void CChirrupDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
{
    DWORD   dwPos = GetMessagePos();
    WORD    wX    = LOWORD( dwPos );
    WORD    wY    = HIWORD( dwPos );

    bool    done = DisplayContextMenuForServices( wX, wY );
    if ( !done )
        done = DisplayContextMenuForFriends( wX, wY );
    if ( !done )
        done = DisplayContextMenuForImetter( wX, wY );
    if ( !done )
        ExtraContextMenu( wX, wY );
}
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif

void CChirrupDlg::OnCheckBrowsing() 
{
    CButton *p = (CButton *)GetDlgItem( IDC_CHECK_BROWSING );
    int     checked = p->GetCheck();

    m_checkBrowsing = checked == 1 ? TRUE : FALSE;
    m_needToSave    = true;
}

void CChirrupDlg::OnCheckMultipost() 
{
    CButton *p = (CButton *)GetDlgItem( IDC_CHECK_MULTIPOST );
    int     checked = p->GetCheck();

    m_postMulti  = checked == 1 ? TRUE : FALSE;
    m_needToSave = true;
}

void CChirrupDlg::OnSize(UINT nType, int cx, int cy) 
{
    bool    redraw = false;
    if ( nType == FORTH_REDRAW ) {
        redraw = true;
        nType  = 0;
    }

    if ( nType == SIZE_MINIMIZED )
        ShowWindow( SW_HIDE );

	CDialog::OnSize(nType, cx, cy);

    if ( IsIconic() )
        return;

    if( redraw || (IsWindow( GetSafeHwnd() ) && IsWindowVisible()) ) {
        static int targetIDC[] = {
            IDC_SETTING_ACCOUNT,
            IDC_UPDATE,
            IDC_TWITTER,
            IDC_JAIKU,
            IDC_TIMELOG,
            IDC_HATENAGROUP,
            IDC_HATENABOOKMARK,
            IDC_DELICIOUS,
            IDC_GOOGLEGROUPS,
            IDC_TWITTERWIKI,
            IDC_TWITTER_CHIRRUP,
            IDC_MIXI,
            IDC_HATENASTAR,
            IDC_FAVOTTER,
            IDC_GYAZO,
            IDC_HATENAFOTOLIFE,
            -1
        };

        static int targetIDC2[] = {
            IDC_RECV_DIRECTMESSAGE,
            IDC_HATENAHAIKU,
            IDC_MOGO2,
            IDC_WASSR,
            IDC_HARUFM,
            IDC_DIGG,
            IDC_MAGNOLIA,
            IDC_LIVEDOORCLIP,
            IDC_LIVEDOOR,
            IDC_GOOGLE,
            IDC_YAHOO,
            IDC_BLOGLINES,
            IDC_TWITTER_SEARCH,
            IDC_TUMBLR,
            IDC_FLICKR,
            IDC_TWITTERSNS,
            -1
        };

        m_nType = nType;
        m_cx    = cx;
        m_cy    = cy;

        CRect   rect_st;
        m_status.GetWindowRect( rect_st );
        int     adjustHeight = rect_st.bottom - rect_st.top;

        CRect   rect;
        GetClientRect( &rect );

        int height     = rect_st.bottom - rect_st.top;
        rect_st.top    = rect.bottom - height;
        rect_st.bottom = rect_st.top + height;
        rect_st.left   = rect.left;
        rect_st.right  = rect.right;
        m_status.MoveWindow( rect_st );

        rect.bottom += (height + ADJUST_HEIGHT);
        if ( rect.bottom < m_rectFriend020.bottom ) {
            CStatic *sp;
            int     i;

            for ( i = IDC_FRIEND011; i <= IDC_FRIEND020; i++ ) {
                sp = (CStatic *)GetDlgItem( i );
                sp->EnableWindow( FALSE );
                sp->ShowWindow( SW_HIDE );
            }
        }
        else {
            CStatic *sp;
            int     i;

            for ( i = IDC_FRIEND011; i <= IDC_FRIEND020; i++ ) {
                sp = (CStatic *)GetDlgItem( i );
                if ( sp->IsWindowEnabled() )
                    break;

                sp->EnableWindow( TRUE );
                sp->ShowWindow( SW_SHOW );
            }
        }

        if ( rect.bottom < m_rectFriend010.bottom ) {
            CStatic *sp;
            int     i;

            for ( i = IDC_FRIEND001; i <= IDC_FRIEND010; i++ ) {
                sp = (CStatic *)GetDlgItem( i );
                sp->EnableWindow( FALSE );
                sp->ShowWindow( SW_HIDE );
            }
        }
        else {
            CStatic *sp;
            int     i;

            for ( i = IDC_FRIEND001; i <= IDC_FRIEND010; i++ ) {
                sp = (CStatic *)GetDlgItem( i );
                if ( sp->IsWindowEnabled() )
                    break;

                sp->EnableWindow( TRUE );
                sp->ShowWindow( SW_SHOW );
            }
        }

        if ( rect.bottom < m_rectCheckBrowsing.bottom ) {
            CButton *bp = (CButton *)GetDlgItem( IDC_CHECK_BROWSING );
            bp->EnableWindow( FALSE );
            bp->ShowWindow( SW_HIDE );

            bp = (CButton *)GetDlgItem( IDC_CHECK_MULTIPOST );
            bp->EnableWindow( FALSE );
            bp->ShowWindow( SW_HIDE );
        }
        else {
            CButton *bp = (CButton *)GetDlgItem( IDC_CHECK_BROWSING );
            if ( !(bp->IsWindowEnabled()) ) {
                bp->EnableWindow( TRUE );
                bp->ShowWindow( SW_SHOW );
            }

            bp = (CButton *)GetDlgItem( IDC_CHECK_MULTIPOST );
            if ( !(bp->IsWindowEnabled()) ) {
                bp->EnableWindow( TRUE );
                bp->ShowWindow( SW_SHOW );
            }
        }

        if ( rect.bottom < m_rectMonologue.bottom ) {
            CStatic *sp = (CStatic *)GetDlgItem( IDC_STATIC_QUESTION );
            sp->EnableWindow( FALSE );
            sp->ShowWindow( SW_HIDE );

            CButton *bp;
            int i;
            for ( i = 0; targetIDC2[i] != -1; i++ ) {
                bp = (CButton *)GetDlgItem( targetIDC2[i] );
                bp->EnableWindow( FALSE );
                bp->ShowWindow( SW_HIDE );
            }

            int diff = m_rectMonologue.bottom - rect.bottom;

            CRect   rectM;
            CEdit   *ep = (CEdit *)GetDlgItem( IDC_MONOLOGUE );
            ep->GetWindowRect( &rectM );

            CRect   rectM2;
            bp = (CButton *)GetDlgItem( IDC_POST_MONOLOGUE );
            bp->GetWindowRect( &rectM2 );

            int distance = m_rectPostMonologue.left - m_rectMonologue.left;

            int height   = rectM.bottom - rectM.top;
            int width    = rectM.right  - rectM.left;
            rectM.top    = m_rectMonologue.top  - adjustHeight;
            rectM.bottom = rectM.top  + height;
            rectM.left   = m_rectMonologue.left - 4;// なぜか 4 ずれるため補正
            rectM.right  = rectM.left + width;
            rectM.top    -= diff;
            rectM.bottom -= diff;
            ep->MoveWindow( rectM );

            int height2   = rectM2.bottom - rectM2.top;
            int width2    = rectM2.right  - rectM2.left;
            rectM2.top    = m_rectMonologue.top - adjustHeight;
            rectM2.bottom = rectM2.top  + height2;
            rectM2.left   = rectM.left  + distance;
            rectM2.right  = rectM2.left + width2;
            rectM2.top    -= diff;
            rectM2.bottom -= diff;
            bp->MoveWindow( rectM2 );
        }
        else {
            CStatic *sp = (CStatic *)GetDlgItem( IDC_STATIC_QUESTION );
            sp->EnableWindow( TRUE );
            sp->ShowWindow( SW_SHOW );

            CButton *bp;
            int i;
            for ( i = 0; targetIDC2[i] != -1; i++ ) {
                bp = (CButton *)GetDlgItem( targetIDC2[i] );
                bp->EnableWindow( TRUE );
                bp->ShowWindow( SW_SHOW );
            }

            CRect   rectM;
            CEdit   *ep = (CEdit *)GetDlgItem( IDC_MONOLOGUE );
            ep->GetWindowRect( &rectM );

            CRect   rectM2;
            bp = (CButton *)GetDlgItem( IDC_POST_MONOLOGUE );
            bp->GetWindowRect( &rectM2 );

            int distance = m_rectPostMonologue.left - m_rectMonologue.left;

            int height   = rectM.bottom - rectM.top;
            int width    = rectM.right  - rectM.left;
            rectM.top    = m_rectMonologue.top  - adjustHeight;
            rectM.bottom = rectM.top  + height;
            rectM.left   = m_rectMonologue.left - 4;// なぜか 4 ずれるため補正
            rectM.right  = rectM.left + width;
            ep->MoveWindow( rectM );

            int height2   = rectM2.bottom - rectM2.top;
            int width2    = rectM2.right  - rectM2.left;
            rectM2.top    = m_rectMonologue.top - adjustHeight;
            rectM2.bottom = rectM2.top  + height2;
            rectM2.left   = rectM.left  + distance;
            rectM2.right  = rectM2.left + width2;
            bp->MoveWindow( rectM2 );
        }

        if ( rect.bottom < m_rectDirectMessage.bottom ) {
            CButton *bp;
            int i;
            for ( i = 0; targetIDC[i] != -1; i++ ) {
                bp = (CButton *)GetDlgItem( targetIDC[i] );
                bp->EnableWindow( FALSE );
                bp->ShowWindow( SW_HIDE );
            }

            bp = (CButton *)GetDlgItem( IDC_START_CAPTURE );
            bp->EnableWindow( FALSE );
            bp->ShowWindow( SW_HIDE );
        }
        else {
            CButton *bp;
            int i;
            for ( i = 0; targetIDC[i] != -1; i++ ) {
                bp = (CButton *)GetDlgItem( targetIDC[i] );
                bp->EnableWindow( TRUE );
                bp->ShowWindow( SW_SHOW );
            }

            SwitchCapture();
        }

        if ( rect.bottom < m_rectUpdate.bottom ) {
            CRect   rectM;
            m_messageCtrl.GetWindowRect( &rectM );

            int diff     = m_rectUpdate.bottom - rect.bottom;
            int height   = m_rectMessageCtrl.bottom - m_rectMessageCtrl.top
                                - (adjustHeight + ADJUST_HEIGHT);
            rectM.top    = m_rectMessageCtrl.top - adjustHeight;
            rectM.bottom = rectM.top + height;
            rectM.left   = m_rectMessageCtrl.left - 4;
            rectM.right  = m_rectMessageCtrl.right;
            if ( rectM.bottom - diff > adjustHeight )
                rectM.bottom -= diff;

            m_messageCtrl.MoveWindow( rectM );
        }
        else {
            CRect   rectM;
            m_messageCtrl.GetWindowRect( &rectM );

            int height   = m_rectMessageCtrl.bottom - m_rectMessageCtrl.top
                                - (adjustHeight + ADJUST_HEIGHT);
            rectM.top    = m_rectMessageCtrl.top - adjustHeight;
            rectM.bottom = rectM.top + height;
            rectM.left   = m_rectMessageCtrl.left - 4;
            rectM.right  = m_rectMessageCtrl.right;

            m_messageCtrl.MoveWindow( rectM );
        }
    }
}

void CChirrupDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
    if ( m_initialized ) {
        CRect   rect_st;
        m_status.GetWindowRect( rect_st );
        int     adjustHeight = rect_st.bottom - rect_st.top;

        CRect   rectM;
        CEdit   *ep = (CEdit *)GetDlgItem( IDC_MONOLOGUE );
        ep->GetWindowRect( &rectM );
        adjustHeight += ((rectM.bottom - rectM.top) + ADJUST_HEIGHT) * 2;
                            /* 課題: 将来、フォントサイズ可変にしたとき、   */
                            /*       フォントの大きさに合わせてadjustHeight */
                            /*       の値を変えるようにする                 */

        lpMMI->ptMinTrackSize.x = m_rectBottom.right;
        lpMMI->ptMinTrackSize.y = m_rectMessageCtrl.top + adjustHeight;

        lpMMI->ptMaxTrackSize.x = m_rectBottom.right;
        lpMMI->ptMaxTrackSize.y = m_rectBottom.bottom;
    }

	CDialog::OnGetMinMaxInfo(lpMMI);
}

void CChirrupDlg::OnRecvDirectmessage() 
{
    CTwitterTimeline    *tp = GetCurrentTimeline();
    if ( tp->m_serviceType == CTwitterTimeline::SVC_WASSR) {
        int numOfChannels = 0;
        WASSR_CHANNEL_LIST *wp =
            ((CWassr *)(m_wassr->m_service))->GetChannelList( numOfChannels );

        if ( wp ) {
            CChannelWassr dlg;
            dlg.m_wassrChannelList = wp;
            dlg.m_numOfChannels    = numOfChannels;
            dlg.DoModal();

            delete [] wp;
        }
        return;
    }

    CWaitCursor cur;    // マウスカーソルを砂時計表示

    ProceedingDialog    *pdlg = new ProceedingDialog();

    pdlg->Create( IDD_PROCEEDING_DIALOG );
    pdlg->ChangeDialogText( "Twitter",
                            "ダイレクトメッセージ受信中……" );

    TWITTER_DIRECT_MESSAGE  *dm =
                        new TWITTER_DIRECT_MESSAGE[MAX_NUM_OF_DIRECTMESSAGES];
    int     numOfMessages = 0;
    memset( dm, 0x00,
            sizeof ( TWITTER_DIRECT_MESSAGE ) * MAX_NUM_OF_DIRECTMESSAGES );

    switch ( tp->m_serviceType ) {
    case CTwitterTimeline::SVC_TWITTER:
        if ( m_twitter ) {
            ((CTwitter *)(m_twitter->m_service))->m_dm = dm;
            dm = ((CTwitter *)(m_twitter->m_service))->RecvDirectMessages(
                                                         numOfMessages, pdlg);
        }
        break;
    case CTwitterTimeline::SVC_TIMELOG:
        if ( m_timelog ) {
            ((CTimelog *)(m_timelog->m_service))->m_dm = dm;
            dm = ((CTimelog *)(m_timelog->m_service))->RecvDirectMessages(
                                                         numOfMessages, pdlg);
        }
        break;
    }

    if ( dm && (numOfMessages > 0) ) {
        CDirectMessageList  dlg;

        dlg.m_dm            = dm;
        dlg.m_numOfMessages = numOfMessages;
        dlg.m_serviceType   = tp->m_serviceType;
        dlg.m_textCtrl.m_chirrupDlg = this;
        switch ( tp->m_serviceType ) {
        case CTwitterTimeline::SVC_TWITTER:
            if ( m_twitter ) {
                dlg.m_screenName       = m_twitter->m_screenName;
                dlg.m_username         = m_twitter->m_username;
                dlg.m_password         = m_twitter->m_password;
                dlg.m_useOAuth         = m_twitter->m_useOAuth;
                dlg.m_oauthToken       = m_twitter->m_oauthToken;
                dlg.m_oauthTokenSecret = m_twitter->m_oauthTokenSecret;
            }
            break;
        case CTwitterTimeline::SVC_TIMELOG:
            if ( m_timelog ) {
                dlg.m_screenName = m_timelog->m_screenName;
                dlg.m_username   = m_timelog->m_username;
                dlg.m_password   = m_timelog->m_password;
            }
            break;
        }
        dlg.m_cacheDir = m_cacheDir;
        dlg.DoModal();
    }

    delete [] dm;
    delete pdlg;
}

void CChirrupDlg::OnSelchangeComboTimelineType() 
{
    CString preTimelineType = m_timelineType;
    int     location        = m_timelineTypeList.GetCurSel();

    if ( location >= 0 ) {
    	m_timelineTypeList.GetLBText( location, m_timelineType );
        SwitchTimelineFacilities();

        if ( preTimelineType.Compare( m_timelineType ) != 0 ) {
            CWaitCursor cur;    // マウスカーソルを砂時計表示

            CTwitterTimeline    *tp = GetCurrentTimeline();
            if ( tp ) {
                SwitchTitle();
                if ( tp->m_messages.GetLength() == 0 )
                    UpdateSingle();
                else
                    DisplayTimeline();
            }
        }
    }
}

void CChirrupDlg::OnSettingAccount() 
{
    EnterCriticalSection();
    m_inSetting = true;
    LeaveCriticalSection();

    CSettingDialog  dlg;
    dlg.m_chirrup = this;
    int ret = dlg.DoModal();
    if ( ret == IDOK )
        m_needToSave = true;

    if ( m_needToSave )
        SaveSetting();

    CString preTimelineType = m_timelineType;
    LoadSetting();
    ReduceExtra();
    SwitchCapture();

    EnterCriticalSection();
    m_inSetting = false;
    LeaveCriticalSection();

    if ( !preTimelineType.Compare( m_timelineType ) )
        return;

    int location = m_timelineTypeList.FindString( -1, preTimelineType );
    if ( location >= 0 ) {
        m_timelineTypeList.SetCurSel( location );
        m_timelineTypeList.GetLBText( location, m_timelineType );
        return;
    }

    CWaitCursor cur;    // マウスカーソルを砂時計表示
    location = 0;
    m_timelineTypeList.SetCurSel( location );
    m_timelineTypeList.GetLBText( location, m_timelineType );
    SwitchTimelineFacilities();

    CTwitterTimeline    *tp = GetCurrentTimeline();
    if ( tp ) {
        SwitchTitle();
        if ( tp->m_messages.GetLength() == 0 )
            UpdateSingle();
        else
            DisplayTimeline();
    }
}

void CChirrupDlg::OnExecuting() 
{
    if ( m_showServiceName ) {
        CString url = "http://twitter.com/";

        if ( !strncmp( m_timelineType, "Jaiku:", 6 ) )
            url = _T( "http://www.jaiku.com/" );
        else if ( !strncmp( m_timelineType, "Wassr:", 6 ) )
            url = _T( "http://wassr.jp/" );
        else if ( !strncmp( m_timelineType, "もごもご:", 9 ) )
            url = _T( "http://mogo2.jp/" );
        else if ( !strncmp( m_timelineType, "Timelog:", 8 ) )
            url = _T( "http://timelog.jp/" );
        else if ( !strncmp( m_timelineType, "Haru.fm:", 8 ) )
            url = _T( "http://haru.fm/" );
        else if ( !strncmp( m_timelineType, "はてなハイク:", 13 ) )
            url = _T( "http://h.hatena.ne.jp/" );
     // else if ( !strncmp( m_timelineType, "Twitter:", 8 ) )
     //     url = _T( "http://twitter.com/" );

        ShellExecute( NULL, "open", url, NULL, NULL, SW_SHOWNORMAL );
    }
}


bool CChirrupDlg::ExecuteUploadImage(
                    CString       filename,
                    size_t        filesize,
                    CHIRRUP_FTYPE filetype,
                    CString       caption,
                    bool          onGyazo,
                    bool          onFlickr,
                    bool          onTumblr,
                    bool          onHatenaFotolife,
                    bool          onWassr
                )
{
    BOOL    res1 = FALSE;
    BOOL    res2 = FALSE;
    BOOL    res3 = FALSE;
    BOOL    res4 = FALSE;
    BOOL    res5 = FALSE;
    char    url1[MAX_URLLENGTH];
    char    url2[MAX_URLLENGTH];
    char    url3[MAX_URLLENGTH];
    char    url4[MAX_URLLENGTH];
    char    url5[MAX_URLLENGTH];

    ShowServiceName( false );
    CStatic *sp = (CStatic *)GetDlgItem( IDC_EXECUTING );
    CEdit *cp   = (CEdit *)GetDlgItem( IDC_MONOLOGUE );

    if ( onTumblr ) {
        sp->SetWindowText( "tumblr に画像を送信中……" );
        sp->ShowWindow( SW_SHOW );

        url1[0] = NUL;
        res1    = postPhotoOnTumblr( filename, filesize, caption,
                                     m_tumblrID, m_tumblrPassword,
                                     m_tumblrGroup,
                                     url1 );
        sp->SetWindowText( "画像送信終了……" );

        if ( res1 ) {
            // 成功
            MessageBox( "tumblr に投稿しました        ",
                        "tumblr 投稿成功",
                        MB_OK|MB_ICONINFORMATION );

            cp->GetWindowText( m_monologue );
            if ( m_monologue.GetLength() > 0 ) {
                m_monologue += " ";
                m_monologue += url1;
            }
            else
                m_monologue  = url1;
            cp->SetWindowText( m_monologue );
        }
        else
            MessageBox( "tumblr への投稿に失敗しました\r\n\r\n"
                        "このエラーが出ても、実際には投稿に成功していること"
                        "もあります\r\n"
                        "[例えば、tumblr が重くて dashboard への反映が遅れて"
                        "いるとき]   ",
                        "tumblr 投稿失敗",
                        MB_OK|MB_ICONERROR );
    }

    if ( onGyazo ) {
        bool    needToSave = (m_gyazoID[0] == NUL) ? true : false;

        sp->SetWindowText( "Gyazo に画像を送信中……" );
        sp->ShowWindow( SW_SHOW );

        const char  *targetFilename = filename;
        if ( filetype != FTYPE_PNG ) {
            char    filename2[MAX_PATH];
            sprintf( filename2, "%s.png", (const char *)filename );

            CImage  image;
            HBITMAP bitmap = image.LoadImageFile( filename );
            if ( bitmap ) {
                image.SavePngFile( filename2, bitmap );
                DeleteObject( bitmap );

                struct stat s;
                if ( !stat( filename2, &s ) ) {
                    filesize = s.st_size;
                    targetFilename = filename2;
                }
            }
        }

        url2[0] = NUL;
        res2    = postPhotoOnGyazo(targetFilename, filesize, m_gyazoID, url2);
        sp->SetWindowText( "画像送信終了……" );

        if ( res2 ) {
            // 成功
            MessageBox( "Gyazo に投稿しました        ",
                        "Gyazo 投稿成功",
                        MB_OK|MB_ICONINFORMATION );

            cp->GetWindowText( m_monologue );
            if ( m_monologue.GetLength() > 0 ) {
                m_monologue += " ";
                m_monologue += url2;
            }
            else
                m_monologue  = url2;
            cp->SetWindowText( m_monologue );

            if ( needToSave && m_gyazoID[0] )
                m_needToSave = needToSave;
        }
        else
            MessageBox( "Gyazo への投稿に失敗しました    ",
                        "Gyazo 投稿失敗",
                        MB_OK|MB_ICONERROR );

        if ( strcmp( filename, targetFilename ) != 0 )
            unlink( targetFilename );
    }

    if ( onFlickr ) {
        sp->SetWindowText( "Flickr に画像を送信中……" );
        sp->ShowWindow( SW_SHOW );

        char    title[BUFSIZ];
        strcpy( title, "post via Chirrup" );    // 暫定

        CChirrupApp *ap = (CChirrupApp *)AfxGetApp();

        url3[0] = NUL;
        res3    = postPhotoOnFlickr( filename, filesize,
                                     title, caption,
                                     ap->m_fKey, ap->m_fSecret,
                                     m_flickrToken, m_flickrUserName,
                                     url3 );

        sp->SetWindowText( "画像送信終了……" );

        if ( res3 ) {
            // 成功
            MessageBox( "Flickr に投稿しました        ",
                        "Flickr 投稿成功",
                        MB_OK|MB_ICONINFORMATION );

            cp->GetWindowText( m_monologue );
            if ( m_monologue.GetLength() > 0 ) {
                m_monologue += " ";
                m_monologue += url3;
            }
            else
                m_monologue  = url3;
            cp->SetWindowText( m_monologue );
        }
        else
            MessageBox( "Flickr への投稿に失敗しました    ",
                        "Flickr 投稿失敗",
                        MB_OK|MB_ICONERROR );
    }

    if ( onHatenaFotolife ) {
        sp->SetWindowText( "はてなフォトライフに画像を送信中……" );
        sp->ShowWindow( SW_SHOW );

        url4[0] = NUL;
        res4 = postPhotoOnHatenaFotolife(
                        filename, filesize,
                        filetype == FTYPE_JPG ? MITYPE_JPG :
                        filetype == FTYPE_GIF ? MITYPE_GIF :
                        filetype == FTYPE_PNG ? MITYPE_PNG :
                        filetype == FTYPE_BMP ? MITYPE_BMP :
                                                MITYPE_UNKNOWN,
                        caption,
                        m_hatenaID, m_hatenaPassword,
                        url4 );

        sp->SetWindowText( "画像送信終了……" );

        if ( res4 ) {
            // 成功
            MessageBox( "はてなフォトライフに投稿しました        ",
                        "はてなフォトライフ投稿成功",
                        MB_OK|MB_ICONINFORMATION );

            cp->GetWindowText( m_monologue );
            if ( m_monologue.GetLength() > 0 ) {
                m_monologue += " ";
                m_monologue += url4;
            }
            else
                m_monologue  = url4;
            cp->SetWindowText( m_monologue );
        }
        else
            MessageBox( "はてなフォトライフへの投稿に失敗しました    ",
                        "はてなフォトライフ投稿失敗",
                        MB_OK|MB_ICONERROR );
    }

    if ( onWassr ) {
        url5[0] = NUL;
        if ( !m_wassr )
            MessageBox( "Wassr へ投稿するのに必要な設定が完了して"
                        "いません。  ",
                        "Wassr 投稿失敗",
                        MB_OK|MB_ICONERROR );
        else if ((filetype != FTYPE_JPG) && (filetype != FTYPE_PNG))
            MessageBox( "Wassr へ投稿できるのは JPEG か PNG 形式の"
                        "画像だけです。   ",
                        "Wassr 投稿失敗",
                        MB_OK|MB_ICONERROR );
        else {
            sp->SetWindowText( "Wassr に画像を送信中……" );
            sp->ShowWindow( SW_SHOW );

#ifdef  __TEST__
            res5 = ((CWassr *)(m_wassr->m_service))->PostPhotoViaAPI(
                                filename, filesize, caption, url5 );
            if ( !res5 )
                res5 = ((CWassr *)(m_wassr->m_service))->PostPhoto(
                                filename, filesize, caption, url5 );
#else
            res5 = ((CWassr *)(m_wassr->m_service))->PostPhoto(
                                filename, filesize, caption, url5 );
#endif

            sp->SetWindowText( "画像送信終了……" );
        }

        if ( res5 ) {
            // 成功
            MessageBox( "Wassr に投稿しました        ",
                        "Wassr 投稿成功",
                        MB_OK|MB_ICONINFORMATION );

            cp->GetWindowText( m_monologue );
            if ( m_monologue.GetLength() > 0 ) {
                m_monologue += " ";
                m_monologue += url5;
            }
            else
                m_monologue  = url5;
            cp->SetWindowText( m_monologue );
        }
        else
            MessageBox( "Wassr への投稿に失敗しました    ",
                        "Wassr 投稿失敗",
                        MB_OK|MB_ICONERROR );
    }

    if ( res1 || res2 || res3 || res4 || res5 ) {
        if ( caption.GetLength() > 0 ) {
            DeleteHtmlTags( caption );

            cp->GetWindowText( m_monologue );
            if ( m_monologue.GetLength() > 0 ) {
                m_monologue += " ";
                m_monologue += caption;
            }
            else
                m_monologue  = caption;
            cp->SetWindowText( m_monologue );

            if ( res1 &&
                 m_tumblrWriteLogFile &&
                 (m_tumblrLogFilename.GetLength() > 0))
                WriteUploadLog( m_tumblrLogFilename, url1, caption );
            if ( res2 &&
                 m_gyazoWriteLogFile &&
                 (m_gyazoLogFilename.GetLength() > 0) )
                WriteUploadLog( m_gyazoLogFilename, url2, caption );
            if ( res3 &&
                 m_flickrWriteLogFile &&
                 (m_flickrLogFilename.GetLength() > 0) )
                WriteUploadLog( m_flickrLogFilename, url3, caption );
            if ( res4 &&
                 m_hatenaFotolifeWriteLogFile &&
                 (m_hatenaFotolifeLogFilename.GetLength() > 0) )
                WriteUploadLog( m_hatenaFotolifeLogFilename, url4, caption );
            if ( res5 &&
                 m_wassrWriteLogFileForUpload &&
                 (m_wassrLogFilenameForUpload.GetLength() > 0) )
                WriteUploadLog( m_wassrLogFilenameForUpload, url5, caption );
        }
    }

    if ( strstr( filename, TEMPFILE_BASE ) ) {
        const char  *p = strrchr( filename, '.' );
        if ( p && !strcmp( p + 1, "tmp" ) )
            unlink( filename );
    }

    sp->SetWindowText( "" );
    sp->ShowWindow( SW_HIDE );
    ShowServiceName( true );

    return ( (res1 || res2 || res3 || res4 || res5) ? true : false );
}

bool CChirrupDlg::ExecuteUploadImageWithURL(
                    CString targetURL,
                    CString caption
                )
{
    BOOL    res = FALSE;
    char    url[MAX_URLLENGTH];

    ShowServiceName( false );
    CStatic *sp = (CStatic *)GetDlgItem( IDC_EXECUTING );
    CEdit   *cp = (CEdit *)GetDlgItem( IDC_MONOLOGUE );

    if ( m_useTumblr2 ) {
        sp->SetWindowText( "tumblr に画像を投稿中……" );
        sp->ShowWindow( SW_SHOW );

        url[0] = NUL;
        res    = postPhotoWithUrlOnTumblr( targetURL, caption,
                                           m_tumblrID, m_tumblrPassword,
                                           m_tumblrGroup,
                                           url );
        sp->SetWindowText( "画像投稿終了……" );

        if ( res ) {
            // 成功
            MessageBox( "tumblr に投稿しました        ",
                        "tumblr 投稿成功",
                        MB_OK|MB_ICONINFORMATION );

            cp->GetWindowText( m_monologue );
            if ( m_monologue.GetLength() > 0 ) {
                m_monologue += " ";
                m_monologue += url;
            }
            else
                m_monologue  = url;

            if ( caption.GetLength() > 0 ) {
                DeleteHtmlTags( caption );
                if ( m_monologue.GetLength() > 0 ) {
                    m_monologue += " ";
                    m_monologue += caption;
                }
                else
                    m_monologue  = caption;
            }
            cp->SetWindowText( m_monologue );

            if (m_tumblrWriteLogFile && (m_tumblrLogFilename.GetLength() > 0))
                WriteUploadLog( m_tumblrLogFilename, url, caption );
        }
        else
            MessageBox( "tumblr への投稿に失敗しました\r\n\r\n"
                        "このエラーが出ても、実際には投稿に成功していること"
                        "もあります\r\n"
                        "[例えば、tumblr が重くて dashboard への反映が遅れて"
                        "いるとき]   ",
                        "tumblr 投稿失敗",
                        MB_OK|MB_ICONERROR );
    }

    sp->SetWindowText( "" );
    sp->ShowWindow( SW_HIDE );
    ShowServiceName( true );

    return ( res ? true : false );
}


UINT
_ExecuteUploadImage( LPVOID pParam )
{
    PARAM_UPLOADIMAGE   *p  = (PARAM_UPLOADIMAGE *)pParam;
    UINT                ret = 0;

    if ( p && p->dlg ) {
        CUploadImageDialog  dlg;

        dlg.m_gyazo          = p->dlg->m_useGyazo;
        dlg.m_flickr         = p->dlg->m_useFlickr;
        dlg.m_tumblr         = p->dlg->m_useTumblr2;
        dlg.m_hatenaFotolife = p->dlg->m_useHatenaFotolife;
        dlg.m_wassr          = p->dlg->m_useWassrForUpload;

        if ( p->filesize > 0 ) {
            dlg.m_filename   = p->filename;
            dlg.m_targetName = _T("ファイル名");
        }
        else {
            dlg.m_filename   = p->url;
            dlg.m_targetName = _T("URL");

            dlg.m_gyazo          = false;
            dlg.m_flickr         = false;
            dlg.m_hatenaFotolife = false;
            dlg.m_wassr          = false;
        }

        int r = dlg.DoModal();
        if ( r == IDOK ) {
            p->caption = dlg.m_caption;
            if ( p->filesize > 0 )
                p->dlg->ExecuteUploadImage( p->filename, p->filesize,
                                            p->filetype, p->caption,
                                            dlg.m_sim_gyazo,
                                            dlg.m_sim_flickr,
                                            dlg.m_sim_tumblr,
                                            dlg.m_sim_hatenaFotolife,
                                            dlg.m_sim_wassr );
            else
                p->dlg->ExecuteUploadImageWithURL( p->url, p->caption );
        }
        else {
            if ( p->filesize > 0 ) {
                if ( strstr( p->filename, TEMPFILE_BASE ) ) {
                    const char  *q = strrchr( p->filename, '.' );
                    if ( q && !strcmp( q + 1, "tmp" ) ) {
                        unlink( p->filename );

                        char    tmpBmpFile[MAX_PATH];
                        strcpy( tmpBmpFile, p->filename );
                        tmpBmpFile[q - p->filename + 1] = 'b';
                        unlink( tmpBmpFile );
                    }
                }
            }
        }
    }

    return ( ret );
}

void CChirrupDlg::UploadImage( PARAM_UPLOADIMAGE *param )
{
    CWinThread  *p;

    EnterCriticalSection();
    p = m_uploadImageThread;
    LeaveCriticalSection();

    if ( p ) {
        MessageBox( "いま、ちょっと忙しいの。あとにしてね!    ",
                    "たんぶらん",
                    MB_OK|MB_ICONWARNING );
        return;
    }

    EnterCriticalSection();
    m_uploadImageThread = AfxBeginThread(_ExecuteUploadImage, (void *)param);
    if ( m_uploadImageThread ) {
        m_uploadImageThread->m_bAutoDelete = FALSE;
        SetTimer( ID_THREAD_UPLAOD_IMAGE,
                  MS_THREAD_UPLAOD_IMAGE,
                  NULL );
    }
    LeaveCriticalSection();
}

void CChirrupDlg::UploadImage( const char *filename )
{
    if ( !filename[0] )
        return;

    struct stat s;

    if ( !stat( filename, &s ) ) {
        if ( s.st_size > 0 ) {
            // 画像ファイルかどうかチェック
            int             height = 0;
            int             width  = 0;
            CHIRRUP_FTYPE   ftype  = GetImageSize( filename, height, width );
            if ( (height > 0) && (width > 0) ) {
                m_paramUploadImage.dlg      = this;
                m_paramUploadImage.filetype = ftype;
                m_paramUploadImage.filename = filename;
                m_paramUploadImage.filesize = s.st_size;
                m_paramUploadImage.url      = _T("");
                m_paramUploadImage.caption  = _T("");

                UploadImage( &m_paramUploadImage );
            }
        }
    }
}

void CChirrupDlg::PostImage( const char *url )
{
    // (当該URLが画像なら)tumblr に投稿する
    if ( !strncmp( url, "http://",  7 ) ||
         !strncmp( url, "https://", 8 )    ) {
        // ファイルを取得して画像かどうか判定する
        size_t  sz = MAX_CONTENT_SIZE;
        char    *response = new char[sz];

        if ( response ) {
            setUpReceiveBuffer( response, sz );
            _http_get( url, response, NULL );
            if ( *response ) {
                const char  *filename = "./tmpImage.tmp";
                FILE        *fp = fopen( filename, "wb" );
                if ( fp ) {
                    fwrite( response, sizeof ( char ), sz, fp );
                    fclose( fp );

                    int             height = 0;
                    int             width  = 0;
                    CHIRRUP_FTYPE   ftype  = GetImageSize( filename,
                                                           height, width );
                    unlink( filename );

                    if ( (height > 0) && (width > 0) ) {
                        m_paramUploadImage.dlg      = this;
                        m_paramUploadImage.filetype = ftype;
                        m_paramUploadImage.filename = _T("");
                        m_paramUploadImage.filesize = 0;
                        m_paramUploadImage.url      = url;
                        m_paramUploadImage.caption  = _T("");

                        UploadImage( &m_paramUploadImage );
                    }
                }
            }

            delete [] response;
        }
    }
}

void CChirrupDlg::OnDropFiles(HDROP hDropInfo) 
{
    char        filename[MAX_PATH];
    int         num;
    size_t      sz = MAX_PATH;
    struct stat s;
    bool        unresolved = false;

    if ( m_useTumblr2        ||
         m_useGyazo          ||
         m_useFlickr         ||
         m_useHatenaFotolife ||
         m_useWassrForUpload    ) {
        /* ドロップされたファイルの個数を得る */
        num = DragQueryFile( hDropInfo, (UINT)0xFFFFFFFF, NULL, 0 );
        /* ファイルを処理 */
        for ( int i = 0; i < num; i++ ) {
            filename[0] = NUL;
            DragQueryFile( hDropInfo, i, filename, sz );
            if ( filename[0] ) {
                if ( !stat( filename, &s ) ) {
                    // ディレクトリは読み飛ばす
                    if ( (s.st_mode & _S_IFDIR ) == _S_IFDIR )
                        continue;
                    if ( s.st_size == 0 ) {
                        // Firefox からドラッグしてきた画像は、ドロップ
                        // イベント発生時点では大きさ 0バイトのファイル
                        // のままなので、いったん処理を抜けて、何らかの
                        // タイミングでファイルを読み直す必要がある
                        // (イベントハンドラから抜けるまでは大きさ0バイ
                        //  トのまま)
                        unresolved = true;
                        if ( m_waitedFilename[0] == NUL ) {
                            EnterCriticalSection();
                            strcpy( m_waitedFilename, filename );
                            LeaveCriticalSection();
                            SetTimer( ID_WAITED_UPLAOD_IMAGE,
                                      MS_WAITED_UPLAOD_IMAGE,
                                      NULL );
                        }
                        continue;
                    }

                    UploadImage( filename );
                    break;  /* 暫定的に、複数ファイルのアップロード */
                            /* は未対応ということにしておく         */
                }
            }
        }
    }

	CDialog::OnDropFiles(hDropInfo);
}

void CChirrupDlg::OnEditPaste()
{
    if ( !IsClipboardFormatAvailable(CF_TEXT) )
        return;

    HGLOBAL     hData;
    const char  *ptr;
    char        url[MAX_URLLENGTH + 1];

    // クリップボードから URL を取り出す
    OpenClipboard();
    hData = (HGLOBAL)GetClipboardData(CF_TEXT);
    ASSERT(hData);
    ptr = (const char *)GlobalLock(hData);
    memset( url, 0x00, MAX_URLLENGTH + 1 );
    strncpy( url, ptr, MAX_URLLENGTH );
    GlobalUnlock(hData);
 // GlobalFree(hData); ← ここで free してはいけない! (ヒープが不整合を起こす)
    CloseClipboard(); // ← free は CloseClipboard() の中でやっている

    // (当該URLが画像なら)tumblr に投稿する
    PostImage( url );
}

/////////////////////////////////////////////////////////////////////////////
// 以下、画面キャプチャ関連処理

void CChirrupDlg::OnStartCapture() 
{
    CChirrupApp     *ap = (CChirrupApp *)AfxGetApp();
    if ( !(ap->m_capture) )
        ap->m_capture = new CCapture;

    m_inCapturing = !m_inCapturing;
    if ( m_inCapturing ) {
        CButton *p = (CButton *)GetDlgItem( IDC_START_CAPTURE );
        p->EnableWindow( FALSE );

        ap->m_capture->InitInstance( this, m_hWndForCapture );
    }
}

void CChirrupDlg::OnEndCapture()
{
    if ( m_inCapturing ) {
        m_inCapturing = false;

        ::DestroyWindow( m_hWndForCapture );

     // UnregisterClass( m_szWindowClass, m_hInstForCapture );
        m_hWndForCapture = NULL;

        CButton *p = (CButton *)GetDlgItem( IDC_START_CAPTURE );
        p->EnableWindow( TRUE );
    }
}
