/*
 * parameter.h : ソーシャルブックマーク管理プログラム
 *      CParameter クラスの定義
 *          written by H.Tsujimura  13 Oct 2005, 5 Jul 2006 / 4 Apr 2007
 *
 *  「ソーシャルブックマーク管理プログラム」で使っているソースコードを
 *  そのまま流用
 *
 * $Log: /comm/chirrup/parameter.h $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     08/01/28 17:00 Tsujimura543
 * evalKey() と writeKey() の unsigned long 版を追加
 * 
 * 1     07/04/05 3:33 Tsujimura543
 * bookey のソースを流用
 * 
 * ------------------------------------------------------------------------
 * 以下は、bookey/parameter.h の変更履歴
 * ------------------------------------------------------------------------
 * 5     07/01/18 0:53 Tsujimura543
 * デバッグ用のコード(の名残)を削除
 * 
 * 4     06/08/21 21:06 Tsujimura543
 * authType の値を「初期設定ファイル」に保存するようにした
 * 
 * 3     06/07/05 17:49 Tsujimura543
 * CUserInfo 導入によるリファクタリング第12段階、終了
 * 
 * 2     06/07/05 13:59 Tsujimura543
 * 必要最小限のものだけ見せるようにする
 * 
 * 1     06/07/05 13:10 Tsujimura543
 * 初期設定ファイルから読み取った内容を解析、格納、照合する処理、
 * 初期設定ファイルへ書き出す処理を bookeyView.cpp から分離独立
 * させた
 */

#ifndef __PARAMETER_H__
#define __PARAMETER_H__

/*
 * 暗号化済み parameter を復号する
 */

void
extractKey(
    CString             &param,         // (O) 復号済みデータ
    const unsigned char *encrypted,     // (I) 復号したい(暗号化済み)データ
    const unsigned char *rsaString );   // (I) 復号に必要な情報(秘密鍵)


/*
 * 暗号化済み parameter が正常に復号できることを確認する
 */

void
checkKey(
    const char          *value,        // (I) 暗号化前のデータ
    const unsigned char *encrypted,    // (I) 暗号化済みデータ
    const unsigned char *rsaString,    // (I) 復号に必要な情報(秘密鍵)
    bool                &ret );        // (O) 復号できることを保証できるか否か


/*
 * (初期設定ファイルから読み取った)parameter の抽出
 */

bool
evalKey(
    const char *context,    // (I) 初期設定ファイルから読み取った文字列
    const char *name,       // (I) parameter の名前
    char       *value );    // (O) parameter の値(文字列)

bool
evalKey(
    const char *context,    // (I) 初期設定ファイルから読み取った文字列
    const char *name,       // (I) parameter の名前
    CString    &value );    // (O) parameter の値(CString)

bool
evalKey(
    const char *context,    // (I) 初期設定ファイルから読み取った文字列
    const char *name,       // (I) parameter の名前
    BOOL       &value );    // (O) parameter の値(BOOL)

bool
evalKey(
    const char *context,    // (I) 初期設定ファイルから読み取った文字列
    const char *name,       // (I) parameter を象徴する名前
    bool       &value );    // (O) parameter の値(bool)

bool
evalKey(
    const char *context,    // (I) 初期設定ファイルから読み取った文字列
    const char *name,       // (I) parameter を象徴する名前
    long       &value );    // (O) parameter の値(long)

bool
evalKey(
    const char    *context, // (I) 初期設定ファイルから読み取った文字列
    const char    *name,    // (I) parameter を象徴する名前
    unsigned long &value ); // (O) parameter の値(unsigned long)

/*
 * 初期設定ファイルへの parameter の書き出し
 */

void
writeKey(
    FILE       *fp,         // (I/O) 書き出し先
    const char *name,       // (I) parameter の名前
    const char *value );    // (I) parameter の値(文字列)

void
writeKey(
    FILE       *fp,         // (I/O) 書き出し先
    const char *name,       // (I) parameter の名前
    BOOL       value );     // (I) parameter の値(BOOL)

void
writeKey(
    FILE       *fp,         // (I/O) 書き出し先
    const char *name,       // (I) parameter の名前
    long       value );     // (I) parameter の値(long)

void
writeKey(
    FILE          *fp,      // (I/O) 書き出し先
    const char    *name,    // (I) parameter の名前
    unsigned long value );  // (I) parameter の値(long)

void
writeKey(
    FILE          *fp,      // (I/O) 書き出し先
    const char    *name,    // (I)   parameter を象徴する名前
    const char    *value,   // (I)   parameter の値(文字列) [暗号化対象]
    char          *key,     // (I)   公開鍵
    unsigned char **secret, // (I/O) 復号に必要な情報(秘密鍵)
    bool          &done );  // (O)   暗号化処理実行済みか否か

#endif  /* __PARAMETER_H__ */
