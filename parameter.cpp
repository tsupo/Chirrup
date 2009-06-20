/*
 * parameter.cpp : Twitter クライアント chirrup
 *      CParameter クラスの定義
 *          written by H.Tsujimura  13 Oct 2005, 5 Jul 2006 / 4 Apr 2007
 *
 * $Log: /comm/chirrup/parameter.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     08/01/28 17:00 Tsujimura543
 * evalKey() と writeKey() の unsigned long 版を追加
 * 
 * 2     07/12/05 23:18 Tsujimura543
 * unbase64() の引数追加に伴う修正を実施
 * 
 * 1     07/04/05 3:33 Tsujimura543
 * bookey のソースを流用
 * 
 * ------------------------------------------------------------------------
 * 以下は、bookey/parameter.cpp の変更履歴
 * ------------------------------------------------------------------------
 * 9     07/03/27 19:16 Tsujimura543
 * proxy情報を手動で設定するためのボタンを追加
 * 
 * 8     07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 7     07/01/18 0:37 Tsujimura543
 * デバッグ用のコード(の名残)を削除
 * 
 * 6     07/01/17 23:53 Tsujimura543
 * デバッグ用のコードを削除
 * 
 * 5     06/08/21 21:06 Tsujimura543
 * authType の値を「初期設定ファイル」に保存するようにした
 * 
 * 4     06/07/05 20:50 Tsujimura543
 * コードを整理
 * 
 * 3     06/07/05 17:49 Tsujimura543
 * CUserInfo 導入によるリファクタリング第12段階、終了
 * 
 * 2     06/07/05 14:02 Tsujimura543
 * コードを整理
 * 
 * 1     06/07/05 13:10 Tsujimura543
 * 初期設定ファイルから読み取った内容を解析、格納、照合する処理、
 * 初期設定ファイルへ書き出す処理を bookeyView.cpp から分離独立
 * させた
 */

#include "chirrup.h"
#include "parameter.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/parameter.cpp 1     09/05/14 3:50 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*
 *  指定 parameter を暗号化する
 */

void
encodeParameter(
    FILE          *fp,          // (I/O) 暗号化済みデータ出力先
    const char    *param,       // (I)   暗号化対象データ本体
    const char    *paramName,   // (I)   暗号化対象データ名
    char          *key,         // (I)   暗号生成に利用する公開鍵
    unsigned char **rsaString,  // (O)   復号に必要な情報(秘密鍵)
    bool          &encrypted )  // (O)   暗号化に成功したか否か
{
    int           len;
    unsigned char *cryptedString = NULL;

    len = encodeByRSA( param, rsaString, &cryptedString );
    if ( len > 0 ) {
        encrypted = true;
        if ( !(key[0]) )
            strcpy( key, base64(*rsaString, strlen((char *)*rsaString)) );
        fprintf( fp, "%sEncrypted: %s\n",
                 paramName,
                 base64( cryptedString, len ) );
        freeRSAbuffer( (char *)cryptedString );
    }
    else
        fprintf( fp, "%s: %s\n", paramName, param );
}


/*
 *  指定 parameter を復号する
 */

void
decodeParameter(
    CString             &param,           // (O) 復号済みデータ
    const unsigned char *encryptedString, // (I) 復号したい(暗号化済み)データ
    const unsigned char *rsaString )      // (I) 復号に必要な情報(秘密鍵)
{
    char            *p;
    unsigned char   targetString[BUFSIZ];   // 復号対象バイト列
    int             len = -1;               // 復号結果(文字列)の長さ
    size_t          sz  = 0;

    targetString[0] = NUL;
    p = unbase64( encryptedString, targetString, &sz );
    if ( p ) {
        char    *decodedString = NULL;      // 復号結果格納領域へのポインタ

        if ( targetString[0] )
            len = decodeByRSA( &decodedString, rsaString,
                               (unsigned char *)targetString,
                               strlen( (char *)targetString ) );
        if ( len >= 0 ) {
            param = decodedString;
            freeRSAbuffer( decodedString );
        }
    }
}


/*
 * 暗号化済み parameter が正常に復号できることを確認する
 */

void
checkKey(
    const char          *value,        // (I) 暗号化前のデータ
    const unsigned char *encrypted,    // (I) 暗号化済みデータ
    const unsigned char *rsaString,    // (I) 復号に必要な情報(秘密鍵)
    bool                &ret )         // (O) 復号できることを保証できるか否か
{
    if ( encrypted[0] ) {
        CString param;

        decodeParameter( param,
                         (unsigned char *)encrypted,
                         (unsigned char *)rsaString );
        // param(暗号化済みデータを復号したもの) と bookmark.m_password (暗号
        // 化する前のデータ) を照合し、両者が一致すれば、(復号可能な形で)暗号
        // 化に成功しているものと判断する [復号に失敗する暗号化済みデータが生
        // 成されることがあるため、暗号化済みデータが正常に復号できることをあ
        // らかじめ確認しておきたい]
        if ( (param.GetLength() == 0)      ||
             (param.Compare( value ) != 0)    ) {
            ret = false;    // 照合結果不一致 (この暗号化済みデータは採用でき
                            // ない)
        }
    }
}


/*
 * 暗号化済み parameter を復号する
 */

void
extractKey(
    CString             &param,         // (O) 復号済みデータ
    const unsigned char *encrypted,     // (I) 復号したい(暗号化済み)データ
    const unsigned char *rsaString )    // (I) 復号に必要な情報(秘密鍵)
{
    if ( encrypted[0] )
        decodeParameter( param,
                         (unsigned char *)encrypted,
                         (unsigned char *)rsaString );
}


/*
 * (初期設定ファイルから読み取った)parameter の抽出
 */

bool
evalKey(
    const char *context,    // (I) 初期設定ファイルから読み取った文字列
    const char *name,       // (I) parameter の名前
    char       *value )     // (O) parameter の値(文字列)
{
    bool    ret = false;
    char    target[BUFSIZ];
    int     len;

    sprintf( target, "%s: ", name );
    len = strlen( target );

    if ( !strncmp( context, target, len ) ) {
        strcpy( value, context + len );
        ret = true;
    }

    return ( ret );
}

bool
evalKey(
    const char *context,    // (I) 初期設定ファイルから読み取った文字列
    const char *name,       // (I) parameter の名前
    CString    &value )     // (O) parameter の値(文字列)
{
    bool    ret = false;
    char    target[BUFSIZ];
    int     len;

    sprintf( target, "%s: ", name );
    len = strlen( target );

    if ( !strncmp( context, target, len ) ) {
        value = context + len;
        ret = true;
    }

    return ( ret );
}

bool
evalKey(
    const char *context,    // (I) 初期設定ファイルから読み取った文字列
    const char *name,       // (I) parameter を象徴する名前
    bool       &value )     // (O) parameter の値(bool)
{
    bool    ret = false;
    char    target[BUFSIZ];
    int     len;

    sprintf( target, "%s: ", name );
    len = strlen( target );

    if ( !strncmp( context, target, len ) ) {
        value = !strncmpi( context + len, "TRUE", 4 ) ? true : false;
        ret = true;
    }

    return ( ret );
}

bool
evalKey(
    const char *context,    // (I) 初期設定ファイルから読み取った文字列
    const char *name,       // (I) parameter の名前
    BOOL       &value )     // (O) parameter の値(BOOL)
{
    bool    ret = false;
    char    target[BUFSIZ];
    int     len;

    sprintf( target, "%s: ", name );
    len = strlen( target );

    if ( !strncmp( context, target, len ) ) {
        value = !strncmp( context + len, "TRUE", 4 ) ? TRUE : FALSE;
        ret = true;
    }

    return ( ret );
}

bool
evalKey(
    const char *context,    // (I) 初期設定ファイルから読み取った文字列
    const char *name,       // (I) parameter の名前
    long       &value )     // (O) parameter の値(long)
{
    bool    ret = false;
    char    target[BUFSIZ];
    int     len;

    sprintf( target, "%s: ", name );
    len = strlen( target );

    if ( !strncmp( context, target, len ) ) {
        value = atol( context + len );
        ret = true;
    }

    return ( ret );
}

bool
evalKey(
    const char    *context, // (I) 初期設定ファイルから読み取った文字列
    const char    *name,    // (I) parameter の名前
    unsigned long &value )  // (O) parameter の値(unsigned long)
{
    bool    ret = false;
    char    target[BUFSIZ];
    int     len;

    sprintf( target, "%s: ", name );
    len = strlen( target );

    if ( !strncmp( context, target, len ) ) {
        value = (unsigned long)atol( context + len );
        ret = true;
    }

    return ( ret );
}


/*
 * 初期設定ファイルへの parameter の書き出し
 */

void
writeKey(
    FILE       *fp,     // (I/O) 書き出し先
    const char *name,   // (I)   parameter の名前
    const char *value ) // (I)   parameter の値(文字列)
{
    fprintf( fp, "%s: %s\n", name, value );
}

void
writeKey(
    FILE       *fp,     // (I/O) 書き出し先
    const char *name,   // (I)   parameter の名前
    CString    value )  // (I)   parameter の値(CString)
{
    if ( value.GetLength() > 0 )
        fprintf( fp, "%s: %s\n",
                 name,
                 (const char *)value );
}

void
writeKey(
    FILE       *fp,     // (I/O) 書き出し先
    const char *name,   // (I)   parameter の名前
    BOOL       value )  // (I)   parameter の値(BOOL)
{
    fprintf( fp, "%s: %s\n",
             name, value ? "TRUE" : "FALSE" );
}

void
writeKey(
    FILE       *fp,     // (I/O) 書き出し先
    const char *name,   // (I)   parameter の名前
    long       value )  // (I)   parameter の値(long)
{
    fprintf( fp, "%s: %ld\n", name, value );
}

void
writeKey(
    FILE          *fp,      // (I/O) 書き出し先
    const char    *name,    // (I)   parameter の名前
    unsigned long value )   // (I)   parameter の値(unsigned long)
{
    fprintf( fp, "%s: %lu\n", name, value );
}

void
writeKey(
    FILE          *fp,      // (I/O) 書き出し先
    const char    *name,    // (I)   parameter を象徴する名前
    const char    *value,   // (I)   parameter の値(文字列) [暗号化対象]
    char          *key,     // (I)   公開鍵
    unsigned char **secret, // (I/O) 復号に必要な情報(秘密鍵)
    bool          &done )   // (O)   暗号化処理実行済みか否か
{
    if ( value && *value && (strlen( value ) > 0) )
        encodeParameter( fp,
                         value,
                         name,
                         key, secret, done );
}
