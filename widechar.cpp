/*
 * widechar.cpp : Twitter クライアント chirrup
 *      文字化け対策ユーティリティ関数群
 *          written by H.Tsujimura  12 Dec 2007
 *
 *      Copyright (c) 2007, 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      Some Rights Reserved.
 *
 *      UTF8ToUTF16() は
 *          UTF8→UTF16の変換方法
 *              http://hpcgi1.nifty.com/MADIA/Vcbbs/wwwlng.cgi?print+200701/07010007.txt
 *              Blue 2007/01/04(木) 18:52:09
 *      に掲載されているコードを流用させていただいています
 *
 * $Log: /comm/chirrup/widechar.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 13    08/12/04 18:19 Tsujimura543
 * コード整理、安定化作業を実施
 * 
 * 12    08/01/11 20:54 Tsujimura543
 * コメントを修正
 * 
 * 11    08/01/11 20:53 Tsujimura543
 * candidate[] に入れておく文字をさらに1個追加
 * 
 * 10    08/01/07 14:44 Tsujimura543
 * candidate[] に入れておく文字をさらに1個追加
 * (繁体字使用時の文字化け対策)
 * 
 * 9     07/12/26 22:23 Tsujimura543
 * candidate[] に入れておく文字をさらに1個追加
 * 
 * 8     07/12/26 20:50 Tsujimura543
 * candidate[] に入れておく文字をさらに1個追加
 * 
 * 7     07/12/20 17:22 Tsujimura543
 * candidate[] に入れておく文字をさらに追加
 * 
 * 6     07/12/19 22:09 Tsujimura543
 * candidate[] に入れておく文字をさらに1個追加
 * 
 * 5     07/12/19 21:33 Tsujimura543
 * candidate[] に入れておく文字を追加
 * 
 * 4     07/12/19 14:13 Tsujimura543
 * isExistLatin1() を改良。動作確認済み
 * 
 * 3     07/12/17 21:48 Tsujimura543
 * (1) isExistNonAlnum() を isExistLatin1() に変更
 * (2) UTF8ToUTF16() を呼び出す条件を変更
 * 
 * 2     07/12/12 20:37 Tsujimura543
 * isExistNonAlnum() を追加
 * 
 * 1     07/12/12 19:39 Tsujimura543
 * 最初の版
 */

#include <afxwin.h>
#include <comdef.h>
#include "widechar.h"
extern "C" {
#include "utility.h"
}

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/widechar.cpp 1     09/05/14 3:50 tsupo $";
#endif


BOOL
UTF8ToUTF16( const char*& data, const DWORD len, _bstr_t& text )
{
    BOOL result = FALSE;

    text = L"";

    if ( !data )
        return FALSE;
    if ( !len )
        return TRUE;

    const int wlen = ::MultiByteToWideChar( CP_UTF8, 0, data, len, NULL, 0 );
    if ( !wlen )
        return FALSE;

    WCHAR* buff = new WCHAR[wlen + 1];
    if ( ::MultiByteToWideChar( CP_UTF8, 0, data, len, buff, wlen ) ) {
        result = TRUE;
        buff[wlen] = L'\0';
        text = buff;
    }
    delete[] buff;

    return result;
}

static const char candidate[] =
	"鱈叩辿坦棚端単達臓巽探多炭担但樽竪辰旦湛狸邸昼茶眺奪嘆紊尊";

bool
isExistLatin1( const char *s )
{
    bool                ret = false;
    const unsigned char *p  = (const unsigned char *)s;
    const char          *q;
    size_t              sz  = strlen("鱈");

    if ( p ) {
        while ( *p ) {
            if ( *(p + 1) ) {
                for ( q = candidate; *q; q += sz ) {
                    if ( !strncmp( (const char *)p, (const char *)q, sz ) ) {
                        ret = true;
                        break;
                    }
                }

                if ( ret ) {
                    if ( p - 1 >= (const unsigned char *)s ) {
                        if ( *(p - 1) >= 0x80 )
                            ret = false;
                    }
                    if ( *(p + sz) ) {
                        if ( *(p + sz) >= 0x80 )
                            ret = false;
                    }

                    if ( ret )
                        break;  /* Latin-1 文字である可能性が高い */
                }
            }
            p++;
        }
    }

    if ( !ret && s ) {
        bool    kanji = false;

        p = (const unsigned char *)s;
        while ( *p ) {
            if ( !kanji ) {
                if ( iskanji1( *p ) ) {
                    if ( !strncmp( (const char *)p, "縺", 2 ) ||
                         !strncmp( (const char *)p, "繝", 2 ) ||
                         !strncmp( (const char *)p, "繧", 2 )    ) {
                        ret = true; /* UTF-8 → CP932 変換失敗の可能性あり */
                        break;
                    }
                    kanji = true;
                }
            }
            else {
                if ( kanji && !iskanji2( *p ) )
                    break;  /* 矛盾がある */
                kanji = false;
            }

            p++;
        }

        if ( kanji )
            ret = true; /* 矛盾がある */
    }

    return ( ret );
}

CString
RegulateCode(
    const char *orig, // (I) 対象文字列 (UTF-8)
    const char *conv  // (I) 対象文字列を iconv を使って CP932 に変換した結果
  )        
{
    // 本来は文字化けが発生してる場合だけ、UTF8ToUTF16() による変換結果を使え
    // ばいいが、機械的に「文字化けが発生しているかどうか」を判断するのは難し
    // いので、とりあえず、Latin-1 文字が存在する可能性のある場合、UTF-8 → 
    // CP932 の変換に失敗している場合に関して、UTF8ToUTF16() による変換結果を
    // 使うようにしている

    CString result = conv;

    if ( isExistLatin1( conv ) ) {
        const char  *str = orig;
        _bstr_t     bs;
        if ( UTF8ToUTF16( str, strlen( str ), bs ) ) {
            result = (const char *)bs;
        }
    }

    return ( result );
}
