/*
 * utility.c : Twitter クライアント chirrup
 *      各種ユーティリティ関数群
 *          written by H.Tsujimura  4 Apr 2007
 *
 *      Copyright (c) 2007, 2008, 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      Some Rights Reserved.
 *
 * $Log: /comm/chirrup/utility.c $
 * 
 * 2     09/05/31 20:42 tsupo
 * 1.142版
 * 
 * 24    09/05/27 19:35 Tsujimura543
 * setSigInfo() を削除 (xmlRPC.dll へ移管)
 * 
 * 23    09/05/27 18:21 Tsujimura543
 * setSigInfo() の引数を追加
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 22    08/12/01 14:28 Tsujimura543
 * getTitle() を2008年11月25日の「はてなブックマークリニューアル」に
 * 合わせて更新
 * 
 * 21    08/03/26 22:16 Tsujimura543
 * http_get() → __http_getBASIC() へ移行
 * 
 * 20    08/02/14 22:41 Tsujimura543
 * replaceStringEx() を追加
 * 
 * 19    08/02/14 20:01 Tsujimura543
 * replaceString() を追加
 * 
 * 18    08/01/08 21:06 Tsujimura543
 * コメントを修正
 * 
 * 17    08/01/08 21:04 Tsujimura543
 * setSigInfo() を追加
 * 
 * 16    07/07/04 16:56 Tsujimura543
 * getDateTimeFromDateString() 内で _timezone の値を書き換えるのは
 * やめる
 * 
 * 15    07/06/26 22:34 Tsujimura543
 * コメントを修正
 * 
 * 14    07/06/26 22:33 Tsujimura543
 * decodeNumericReference() を修正 (もごもごでは、シャープエンコード結果の
 * 末尾に ; が付かないパターンがあるようで、; がないときにメモリ参照エラー
 * で落ちてしまうため、対策を組み込んだ)
 * 
 * 13    07/06/22 17:42 Tsujimura543
 * any2sjis() に stack overflow 対策を追加
 * 
 * 12    07/06/21 18:08 Tsujimura543
 * cutExtra() を追加
 * 
 * 11    07/06/20 14:05 Tsujimura543
 * getDateTimeFromDateString() を Twitter のタイムスタンプ新形式に
 * 対応させた
 * 
 * 10    07/06/07 3:27 Tsujimura543
 * ログファイルのタイムスタンプが9時間もしくは18時間ずれる不具合を修正
 * 
 * 9     07/05/25 21:14 Tsujimura543
 * any2sjis() をまたまた修正
 * 
 * 8     07/05/23 23:07 Tsujimura543
 * any2sjis() をさらに修正
 * 
 * 7     07/05/22 22:42 Tsujimura543
 * 文字化けリカバリ処理を修正
 * 
 * 6     07/05/22 21:03 Tsujimura543
 * Twitter の API の返すタイムスタンプのフォーマットが変わったため、
 * タイムスタンプ取得処理を改修
 * 
 * 5     07/05/11 21:27 Tsujimura543
 * normalizeDescription() と getTitle() を追加
 * 
 * 4     07/04/27 16:37 Tsujimura543
 * コメントを修正
 * 
 * 3     07/04/24 23:48 Tsujimura543
 * CFriendDialog 向けユーティリティ関数を追加 (将来は他でも使う予定)
 * 
 * 2     07/04/09 21:07 Tsujimura543
 * クォーテーションマークが含まれる発言が正しく表示されない不具合に対処
 * 
 * 1     07/04/05 2:06 Tsujimura543
 * 最初の版
 */

#include <time.h>
#include "xmlRPC.h"
#include "utility.h"
#include "http.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/utility.c 2     09/05/31 20:42 tsupo $";
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

/* Unicode(UCS-2BE) (%uXXXX) → UTF-8 (xxyyzz) 変換 */
char    *
convUnicode( unsigned long code )
{
    unsigned short      a, b, c, d;
    Thread  static char codeStr[6];

    if ( code < 0x0080 ) {
        a = (unsigned short)code;
        codeStr[0] = (char)(a & 0xFF);
        codeStr[1] = NUL;
    }
    else if ( code < 0x0800 ) {
        a = (unsigned short)(((code & 0x07C0) >> 6) | 0xC0);
        b = (unsigned short)(( code & 0x003F)       | 0x80);
        codeStr[0] = (char)(a & 0xFF);
        codeStr[1] = (char)(b & 0xFF);
        codeStr[2] = NUL;
    }
    else if ( code < 0x010000 ) {
        a = (unsigned short)(((code & 0xF000) >> 12) | 0xE0);
        b = (unsigned short)(((code & 0x0FC0) >>  6) | 0x80);
        c = (unsigned short)(( code & 0x003F)        | 0x80);
        codeStr[0] = (char)(a & 0xFF);
        codeStr[1] = (char)(b & 0xFF);
        codeStr[2] = (char)(c & 0xFF);
        codeStr[3] = NUL;
    }
    else {
        a = (unsigned short)(((code & 0x001C0000) >> 18) | 0xF0);
        b = (unsigned short)(((code & 0x0003F000) >> 12) | 0x80);
        c = (unsigned short)(((code & 0x00000FC0) >>  6) | 0x80);
        d = (unsigned short)(( code & 0x0000003F)        | 0x80);
        codeStr[0] = (char)(a & 0xFF);
        codeStr[1] = (char)(b & 0xFF);
        codeStr[2] = (char)(c & 0xFF);
        codeStr[3] = (char)(d & 0xFF);
        codeStr[4] = NUL;
    }

    return ( codeStr );
}


char    *
decodeContents( char *contents )
{
    unsigned char   *p = (unsigned char *)contents;
    unsigned char   *q;
    char            *r;

    while ( p && *p ) {
        if ( *p != '\\' ) {
            p++;
            continue;
        }

        p++;
        switch ( *p ) {
     // case '"':
        case '/':
            strcpy( (char *)p - 1, (char *)p );
            break;

        case 'r':
            strcpy( (char *)p - 1, (char *)p );
            *(p - 1) = '\r';
            break;

        case 'n':
            strcpy( (char *)p - 1, (char *)p );
            *(p - 1) = '\n';
            break;

        case 'u':   /* UCS-2 */
            {
                char            *term;
                unsigned long   hex;
                char            tmp[8];

                p++;
                tmp[0] = *p++;
                tmp[1] = *p++;
                tmp[2] = *p++;
                tmp[3] = *p++;
                tmp[4] = NUL;
                hex = strtol( tmp, &term, 16 );
                term = (char *)p;
                q = (unsigned char *)convUnicode( hex );
                p -= 6;
                while ( *q )
                    *p++ = *q++;
                strcpy( (char *)p, term );
            }
            break;

        default:
            p++;
            break;
        }
    }

    while ( ( r = strstr( contents, "&amp;" ) ) != NULL )
        strcpy( r + 1, r + 5 );

    return ( contents );
}

char    *
decodeNumericReference( char *src )
{
    char    *p    = src;
    char    *q;
    char    *temp = (char *)malloc( strlen( src ) + 1 );

    if ( temp ) {
        unsigned long   l;

        temp[0] = NUL;
        while ( *p ) {
            if ( (*p == '&') && (*(p + 1) == '#') ) {
                l = atol( p + 2 );
                strcat( temp, convUnicode( l ) );
                q = strchr( p + 2, ';' );
                if ( !q )
                    strcat( src, ";" );
                p = strchr( p + 2, ';' ) + 1;
            }
            else {
                l = temp[0] ? strlen( temp ) : 0;
                temp[l]     = *p;
                temp[l + 1] = NUL;
                p++;
            }
        }
        strcpy( src, temp );

        free( temp );
    }

    return ( src );
}


time_t
getDateTimeFromDateString(
        const char *date,   /* (I) 日時情報(文字列) */
        int        *yyyy,   /* (O) 年               */
        int        *mm,     /* (O) 月               */
        int        *dd,     /* (O) 日               */
        int        *HH,     /* (O) 時               */
        int        *MM,     /* (O) 分               */
        int        *SS      /* (O) 秒               */
    )
{
    const char  *p = date;
    const char  *q;
    time_t      t = 0;
    struct tm   tm;
    int         i;
    int         dHH = 0, dMM = 0, d = 0;
    BOOL        found = FALSE;
    BOOL        json  = FALSE;
    static char monStr[12][4] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    *yyyy = 0;
    *mm   = 0;
    *dd   = 0;
    *HH   = 0;
    *MM   = 0;
    *SS   = 0;

    /* まず、「年月日」部分を処理 */
    for ( i = 0; i < 12; i++ ) {
        q = strstr( p, monStr[i] );
        if ( q                                 &&
             (*(q - 1) == ' ')                 &&
             (*(q + strlen(monStr[i])) == ' ')    ) {
            found = TRUE;
            break;
        }
    }
    if ( found ) {
        /* RFC 822 形式の日付の場合              */
        /*   例) Tue, 20 May 2003 08:56:02 GMT   */
        /*       20 May 2003 08:56:02 GMT        */
        /*       Tue, 20 May 2003 17:56:02 JST   */
        /*       Tue, 20 May 2003 17:56:02 +0900 */
        /*       Tue, 20 May 2003 17:56:02+0900  */
        /*       Wed, 06 Dec 2006 14:54:02 +0900 */
        /*       Wed, 6 Dec 2006 14:54:02 +0900  */
        /* JSON で使っている日付のフォーマットは微妙に違う */
        /*   例) Wed Apr 04 12:31:49 +0000 2007            */
        /*                                                 */
        /* + 2007年6月20日に Twitter のタイムスタンプの    */
        /*   フォーマットが以下のようなものに変更された    */
        /*       Wed 20 Jun 04:44:12 +0000 2007            */
        while ( *p && ((*p < '0') || (*p > '9')) )
            p++;
        if ( (*p >= '0') && (*p <= '9') ) {
            *dd = *p - '0';
            p++;
            if ( (*p >= '0') && (*p <= '9') ) {
                *dd = *dd * 10 + (*p - '0');
                p++;
            }
        }

        while ( *p && ((*p == ' ') || (*p == '\t')) )
            p++;

        if ( (*p >= 'A') && (*p <= 'Z') ) {
            json = FALSE;
            while ( *p && ((*p < 'A') || (*p > 'Z')) )
                p++;
        }
        else if ( (*p >= '0') && (*p <= '9') )
            json = TRUE;

        *mm = i + 1;

        if ( !json ) {
            while ( *p && ((*p < '0') || (*p > '9')) )
                p++;
            if ( (*p >= '0') && (*p <= '9') ) {
                if ( *(p + 2) != ':' ) {
                    *yyyy = *p - '0';
                    p++;
                    if ( (*p >= '0') && (*p <= '9') ) {
                        *yyyy = *yyyy * 10 + (*p - '0');
                        p++;
                    }
                    if ( (*p >= '0') && (*p <= '9') ) {
                        *yyyy = *yyyy * 10 + (*p - '0');
                        p++;
                    }
                    if ( (*p >= '0') && (*p <= '9') ) {
                        *yyyy = *yyyy * 10 + (*p - '0');
                        p++;
                    }
                }
                else
                    json = TRUE;
            }

            if ( !json ) {
                while ( *p && ((*p < '0') || (*p > '9')) )
                    p++;
            }
        }
    }
    else {
        q = strstr( p, "/200" );        // 2006 ～ 2009
        if ( !q )
            q = strstr( p, "/201" );    // 2010 ～ 2019
        if ( q ) {
            // 05/22/2007 23:59:59 形式

            while ( *p && ((*p < '0') || (*p > '9')) )
                p++;
            if ( (*p >= '0') && (*p <= '9') ) {
                *mm = *p - '0';
                p++;
                if ( (*p >= '0') && (*p <= '9') ) {
                    *mm = *mm * 10 + (*p - '0');
                    p++;
                }
            }

            while ( *p && ((*p < '0') || (*p > '9')) )
                p++;
            if ( (*p >= '0') && (*p <= '9') ) {
                *dd = *p - '0';
                p++;
                if ( (*p >= '0') && (*p <= '9') ) {
                    *dd = *dd * 10 + (*p - '0');
                    p++;
                }
            }

            while ( *p && ((*p < '0') || (*p > '9')) )
                p++;
            if ( (*p >= '0') && (*p <= '9') ) {
                *yyyy = *p - '0';
                p++;
                if ( (*p >= '0') && (*p <= '9') ) {
                    *yyyy = *yyyy * 10 + (*p - '0');
                    p++;
                }
                if ( (*p >= '0') && (*p <= '9') ) {
                    *yyyy = *yyyy * 10 + (*p - '0');
                    p++;
                }
                if ( (*p >= '0') && (*p <= '9') ) {
                    *yyyy = *yyyy * 10 + (*p - '0');
                    p++;
                }
            }
        }
        else {
     // q = strchr( p, 'T' );
     // if ( q &&
     //      (*(q - 1) >= '0') && (*(q - 1) <= '9') &&
     //      (*(q + 1) >= '0') && (*(q + 1) <= '9')    ) {
            /* ISO8601 形式の日付の場合      */
            /* 例) 2003-12-03T23:59:59+09:00 */
            /*     2003-12-03T23:59:59Z      */
            while ( *p && ((*p < '0') || (*p > '9')) )
                p++;
            if ( (*p >= '0') && (*p <= '9') ) {
                *yyyy = *p - '0';
                p++;
                if ( (*p >= '0') && (*p <= '9') ) {
                    *yyyy = *yyyy * 10 + (*p - '0');
                    p++;
                }
                if ( (*p >= '0') && (*p <= '9') ) {
                    *yyyy = *yyyy * 10 + (*p - '0');
                    p++;
                }
                if ( (*p >= '0') && (*p <= '9') ) {
                    *yyyy = *yyyy * 10 + (*p - '0');
                    p++;
                }
            }

            while ( *p && ((*p < '0') || (*p > '9')) )
                p++;
            if ( (*p >= '0') && (*p <= '9') ) {
                *mm = *p - '0';
                p++;
                if ( (*p >= '0') && (*p <= '9') ) {
                    *mm = *mm * 10 + (*p - '0');
                    p++;
                }
            }

            while ( *p && ((*p < '0') || (*p > '9')) )
                p++;
            if ( (*p >= '0') && (*p <= '9') ) {
                *dd = *p - '0';
                p++;
                if ( (*p >= '0') && (*p <= '9') ) {
                    *dd = *dd * 10 + (*p - '0');
                    p++;
                }
            }
        }
    //  else {
    //      /* それ以外の形式の場合 */
    //  }
    }

    /* 次に、「時分秒」部分を処理 */
    while ( *p && ((*p < '0') || (*p > '9')) )
        p++;
    if ( (*p >= '0') && (*p <= '9') ) {
        *HH = *p - '0';
        p++;
        if ( (*p >= '0') && (*p <= '9') ) {
            *HH = *HH * 10 + (*p - '0');
            p++;
        }
    }

    while ( *p && ((*p < '0') || (*p > '9')) )
        p++;
    if ( (*p >= '0') && (*p <= '9') ) {
        *MM = *p - '0';
        p++;
        if ( (*p >= '0') && (*p <= '9') ) {
            *MM = *MM * 10 + (*p - '0');
            p++;
        }
    }

    while ( *p                         &&
            ((*p < '0') || (*p > '9')) &&
            (*p != '-')                &&
            (*p != '+')                &&
            ((*p < 'A') || (*p > 'Z'))    )
        p++;
    if ( (*p >= '0') && (*p <= '9') ) {
        *SS = *p - '0';
        p++;
        if ( (*p >= '0') && (*p <= '9') ) {
            *SS = *SS * 10 + (*p - '0');
            p++;
        }
    }

    while ( *p ) {
        /* 「UTC との時差」部分を処理 */
        if ( (*p == 'Z')             ||
             !strncmp( p, "GMT", 3 ) ||
             !strncmp( p, "UTC", 3 )    ) {
            d   = 1;
            dHH = 0;
            dMM = 0;
            break;  // UTC(なので、特に処理する必要はない)
        }
        else if ( (*p == '-') || (*p == '+') ) {
            /* +09:00 と +0900 の2パターン(':'の有無)ある */
            d = (*p == '-') ? -1 : 1;
            while ( *p && ((*p < '0') || (*p > '9')) )
                p++;
            if ( (*p >= '0') && (*p <= '9') ) {
                dHH = *p - '0';
                p++;
                if ( (*p >= '0') && (*p <= '9') ) {
                    dHH = dHH * 10 + (*p - '0');
                    p++;
                }
            }

            while ( *p && ((*p < '0') || (*p > '9')) )
                p++;
            if ( (*p >= '0') && (*p <= '9') ) {
                dMM = *p - '0';
                p++;
                if ( (*p >= '0') && (*p <= '9') ) {
                    dMM = dMM * 10 + (*p - '0');
                    p++;
                }
            }
            break;
        }
        else if ( ((*p == ' ') || (*p == '\t')) )
            ;
        else {
            // ローカル時間(このプログラムを動かしているPCのタイムゾーンを採用)
            //  -- 本当は、サーバ設置場所のローカル時間を採用する必要がある
#ifdef  WIN32
            if ( _timezone != 0 ) {
                long    tDiff = _timezone;
                d = (tDiff > 0 ) ? 1 : -1;
                if ( d == -1 )
                    tDiff *= d;
                dHH = (tDiff / 60) / 60;
                dMM = (tDiff / 60) % 60;
            }
#else
            /* JST → GMT (とりあえず、日本以外でこのプログラムを使う人の */
            /*             ことは忘れる) [暫定]                           */
            d   = 1;
            dHH = 9;
            dMM = 0;
#endif
        }
        p++;
    }

    if ( json ) {
        while ( *p && ((*p < '0') || (*p > '9')) )
            p++;
        if ( (*p >= '0') && (*p <= '9') ) {
            *yyyy = *p - '0';
            p++;
            if ( (*p >= '0') && (*p <= '9') ) {
                *yyyy = *yyyy * 10 + (*p - '0');
                p++;
            }
            if ( (*p >= '0') && (*p <= '9') ) {
                *yyyy = *yyyy * 10 + (*p - '0');
                p++;
            }
            if ( (*p >= '0') && (*p <= '9') ) {
                *yyyy = *yyyy * 10 + (*p - '0');
                p++;
            }
        }
    }

    if ( *yyyy > 2000 ) {    
        struct tm   *m;

        tm.tm_year = *yyyy - 1900;
        tm.tm_mon  = *mm   - 1;
        tm.tm_mday = *dd;
        tm.tm_hour = *HH;
        tm.tm_min  = *MM;
        tm.tm_sec  = *SS;

        t = timelocal( &tm );
        if ( d != 0 )
            t -= (dHH * 60 + dMM) * 60 * d; // UTC
#ifdef  USE_UTC
        m = gmtime( &t );       // UTC のまま保持
#else
        if ( (d == 0) && (dHH == 0) && (dMM == 0) )
            m = gmtime( &t );
        else
            m = localtime( &t );    // ローカル時間に変換して保持
#endif
        *yyyy = m->tm_year + 1900;
        *mm   = m->tm_mon  + 1;
        *dd   = m->tm_mday;
        *HH   = m->tm_hour;
        *MM   = m->tm_min;
        *SS   = m->tm_sec;
    }

    return ( t );
}


char    *
encodeDateTime( const char *str )
{
    static char timeStr[80];
    const char  *p = str;
    char        *q;

    q = timeStr;
    while ( *p ) {
        if ( *p == ',' ) {
            *q++ = '%';
            *q++ = '2';
            *q   = 'C';
        }
        else if ( *p == ':' ) {
            *q++ = '%';
            *q++ = '3';
            *q   = 'A';
        }
        else if ( *p == ' ' )
            *q = '+';
        else
            *q = *p;
        p++;
        q++;
    }
    *q = NUL;

    return ( timeStr );
}


char    *
getLastStatus( const char *screenName, char *lastStatus )
{
    char    url[MAX_URLLENGTH];
    char    *p, *q;
    char    *response;
    size_t  sz = MAX_DESCRIPTION_LEN;

    sprintf( url,
             "http://api.twittervision.com/user/current_status/%s.xml",
              screenName );

    response = (char *)malloc( sz );
    if ( response ) {
        setUpReceiveBuffer( response, sz );
     // http_get( url, response );
        __http_getBASIC( url, NULL, NULL, response, NULL );
        if ( *response ) {
            p = strstr( response, "<last-status>" );
            if ( p ) {
                p += 13;
                q = strstr( p, "<text>" );
                if ( q ) {
                    p = q + 6;
                    q = strstr( p, "</text>" );
                    if ( q ) {
                        strncpy( lastStatus, p, q - p );
                        lastStatus[q - p] = NUL;

                        decodeNumericReference( lastStatus );
                        p = any2sjis( lastStatus );
                        if ( p )
                            strcpy( lastStatus, p );
                    }
                }
            }
        }

        free( response );
    }

    return ( lastStatus );
}

char    *addCarriageReturn( char *str, int loc )
{
    char    *p = str;
    char    *temp;
    int     len = strlen( str );

    temp = (char *)malloc( len + (len / loc) * 2 + 2 );
    if ( temp ) {
        char    *q    = temp;
        int     cnt   = 0;
        BOOL    kanji = FALSE;

        while ( *p ) {
            if ( !kanji ) {
                if ( cnt >= loc ) {
                    *q++ = '\r';
                    *q++ = '\n';
                    cnt = 0;
                }

                if ( iskanji1( (unsigned char)(*p) ) ) {
                    kanji = TRUE;
                }

                *q++ = *p++;
            }
            else {
                kanji = FALSE;

                *q++ = *p++;
                if ( cnt >= loc ) {
                    *q++ = '\r';
                    *q++ = '\n';
                    cnt = 0;
                }
            }

            cnt++;
        }

        *q = NUL;
        strcpy( str, temp );
        free( temp );
    }

    return ( str );
}

char    *
any2sjis( const char *p )
{
    char                *q, *r, *s;
    Thread  static long depth = 0;;

    depth++;
    if ( depth >= 20 ) {
        // stack overflow で落ちるのを抑制する
        depth--;
        return ( "???" );
    }

    q = utf2sjis( p );
    if ( !q ) {
        // p の charset は UTF-8 ではない
        if ( strstr( p, "\033$@" ) || strstr( p, "\033$B" ) )
            q = jis2sjis( p );
        else {
            q = euc2sjis( p );
            if ( !q ) {
                r = (char *)p;
                while ( (*r == ' ')  || (*r == '\t') ||
                        (*r == '\r') || (*r == '\n')    )
                    r++;
                s = strchr( r, ' ' );
                if ( !s )
                    s = strchr( r, '\t' );
                if ( !s )
                    s = strchr( r, '\r' );
                if ( !s )
                    s = strchr( r, '\n' );
                if ( !s )
                    q = utf2sjisEx( (char *)p );
                else {
                    size_t  sz1 = (s - r);
                    size_t  sz2 = strlen( s );
                    char    *temp1 = (char *)malloc( sz1 * 16 );
                    char    *temp2 = (char *)malloc( sz2 * 16 );
                    if ( temp1 ) {
                        char    *pp;

                        strncpy( temp1, r, sz1 );
                        temp1[sz1] = NUL;
                        pp = any2sjis( temp1 );
                        if ( !pp )
                            pp = "...";
                        else {
                            char    *temp11 = (char *)malloc(strlen(pp) + 1);
                            if ( temp11 ) {
                                strcpy( temp11, pp );
                                free( temp1 );
                                pp = temp1 = temp11;
                            }
                            else
                                pp = "...";
                        }

                        if ( temp2 ) {
                            char    *qq;

                            strcpy( temp2, s );
                            qq = any2sjis( temp2 );
                            if ( !qq )
                                qq = "...";

                            strcpy( (char *)p, pp  );
                            strcat( (char *)p, " " );
                            strcat( (char *)p, qq  );

                            free( temp2 );
                        }
                        else
                            strcpy( (char *)p, pp  );
                        free( temp1 );
                    }
                    q = (char *)p;
                }
            }
        }
    }
    depth--;

    return ( q );
}


#define MAX_DESCRIPTION_LENGTH  160

char *
normalizeDescription( char *description, size_t length )
{
    size_t  max_len1 = MAX_DESCRIPTION_LENGTH;
    size_t  max_len2 = (max_len1 / 3) * 2;

    if ( length > 0 ) {
        max_len1 = (length * 3 / 2);
        max_len2 = length;
    }

    if ( strlen( description ) > max_len2 ) {
        char    *s = description;
        int     kanjiFlag = 0;
        size_t  i = 0;

        while ( *s ) {
            if ( ++i > max_len2 )
                break;
            if ( kanjiFlag == 0 ) {
                if ( iskanji1( *s ) )
                    kanjiFlag = 1;
            }
            else
                kanjiFlag = ((kanjiFlag + 1) % 3);
            *s++;
        }
        switch ( kanjiFlag ) {
        case 0:
            *s = NUL;
            break;
        case 1:
            *(s - 1) = NUL;
            break;
        case 2:
            *(s - 2) = NUL;
            break;
        }

        strcat( description, "..." );
    }

    return ( description );
}


#define BUFFER_SIZE_FOR_GETTITLE    2048

char    *
encodeURLforHatena( const char *url )
{
    Thread  static char url2[BUFFER_SIZE_FOR_GETTITLE];
    char                *p;
    char                *q;

    strcpy( url2, url );
    while ( (p = strchr( url2, '#' )) != NULL ) {
        q = &url2[strlen(url2)];
        while ( q >= p + 1 ) {
            *(q + 2) = *q;
            q--;
        }
        *p++ = '%';
        *p++ = '2';
        *p   = '3';
    }

    return ( url2 );
}

char    *
getTitle(const char *url )
{
    Thread  static char title[BUFFER_SIZE_FOR_GETTITLE];
    char                title2[BUFFER_SIZE_FOR_GETTITLE];
    char                url2[BUFFER_SIZE_FOR_GETTITLE];
    char                *response;
    char                *p, *q;
    BOOL                useHatenaBookmark = FALSE;
    size_t              sz;

    title[0]  = NUL;
    title2[0] = NUL;

    sz = MAX_CONTENT_SIZE;
    response = (char *)malloc( sz );
    if ( !response )
        return ( title );

    sprintf( url2, "http://b.hatena.ne.jp/entry/%s",
             encodeURLforHatena( url ) );

    setUpReceiveBuffer( response, sz );
 // http_get( url2, response );
    __http_getBASIC( url2, NULL, NULL, response, NULL );
    if ( response && response[0] ) {
        if ( !strstr( response,
                      sjis2utf( "未ブックマークエントリー") ) ) {
            p = strstr( response, "<title>" );
            if ( p ) {
                char    *q = strstr( p, " - " );
                if ( q ) {
                    p = q + 3;
                    q = strstr( p, "</" );
                    if ( q ) {
                        strncpy( title2, p, q - p );
                        title2[q - p] = NUL;
                    }
                }
                
                p = title2;
                while ( ( q = strstr( p, "&lt;" ) ) != NULL ) {
                    *q = '<';
                    strcpy( q + 1, q + 4 );
                }
                while ( ( q = strstr( p, "&gt;" ) ) != NULL ) {
                    *q = '>';
                    strcpy( q + 1, q + 4 );
                }
                while ( ( q = strstr( p, "&quot;" ) ) != NULL ) {
                    *q = '"';
                    strcpy( q + 1, q + 6 );
                }
                while ( ( q = strstr( p, "&amp;" ) ) != NULL )
                    strcpy( q + 1, q + 5 );
                while ( ( q = strstr( p, "&#" ) ) != NULL ) {
                    char    *r;
                    long    l;

                    q += 2;
                    r = strchr( q, ';' );
                    if ( !r ) {
                        r = strstr( q, "&#" );
                        if ( !r )
                            break;
                        p = r;
                        continue;
                    }

                    l = atol( q );
                    if ( (l >= ' ') && (l < 0x80) ) {
                        q -= 2;
                        *q = (char)l;
                        strcpy( q + 1, r + 1 );
                        p = q + 1;
                    }
                    else
                        p = r + 1;
                }

                if (!strcmp(title2, sjis2utf("現在メンテナンス中です。") ) ||
                    !strcmp(title2, sjis2utf("Service Not Available")    )   )
                    title2[0] = NUL;
            }

            if ( title2[0] )
                useHatenaBookmark = TRUE;
        }
    }

    setUpReceiveBuffer( response, sz );
 // http_get( url, response );
    __http_getBASIC( url, NULL, NULL, response, NULL );

    if ( response && response[0] ) {
        p = strstr( response, "<title>" );
        if ( !p )
            p = strstr( response, "<title " );
        if ( !p )
            p = strstr( response, "<TITLE>" );
        if ( !p )
            p = strstr( response, "<TITLE " );
        if ( !p )
            p = strstr( response, "<h1>" );
        if ( !p )
            p = strstr( response, "<h1 " );
        if ( !p )
            p = strstr( response, "<H1>" );
        if ( !p )
            p = strstr( response, "<H1 " );
        if ( p ) {
            p++;
            p = strchr( p, '>' );
            p++;
            q = strstr( p + 1, "</" );
            if ( q ) {
                strncpy( title, p, q - p );
                title[q - p] = NUL;

                while ( ( ( p = strchr( title, '\r' ) ) != NULL ) ||
                        ( ( p = strchr( title, '\n' ) ) != NULL )    )
                    strcpy( p, p + 1 );
            }
        }

        if ( title2[0] != NUL )
            strcpy( title, title2 );

        /* asahi.com 対策 #1 */
        while ( ( p = strstr( title, "&#160;" ) ) != NULL ) {
            *p++ = ' ';
            strcpy( p, p + 5 );
        }

        /* asahi.com 対策 #2 */
        if ( ( p = strstr( title, "\xEF\xBF\xBD-\xEF\xBF\xBD" ) ) != NULL ) {
            strcpy( p, " - " );
            strcpy( p + 3, p + 7 );
        }
    }

    if ( !(title[0]) && title2[0] )
        strcpy( title, title2 );

    if ( strstr( response, "charset=UTF-8" ) ||
         strstr( response, "charset=utf-8" ) ||
         useHatenaBookmark                      )
        p = utf2sjisEx( title );
    else if ( strstr( response, "charset=Shift_JIS" ) ||
              strstr( response, "charset=shift_jis" )    )
        p = title;
    else
        p = utf2sjis( title );
    if ( p ) {
        strcpy( title, p );
        if ( strstr( p, "\033$@" ) || strstr( p, "\033$B" ) ) {
            q = jis2sjis( title );
            if ( q )
                strcpy( title, q );
        }
    }
    else {
        q = NULL;
        if ( strstr( response, "charset=iso-8859-1" ) ||
             strstr( response, "charset=ISO-8859-1" )    ) {
            for ( p = title; *p; p++ ) {
                if ( (unsigned char)(*p & 0xFF) >= 0xA0 ) {
                    q = iso8859_1toUtf8( title );
                    if ( q )
                        p = decodeURL( q ); // utf8 → us-ascii 変換を兼ねる
                    break;
                }
            }
        }

        if ( !q )
            p = euc2sjis( title );
        if ( p )
            strcpy( title, p );
    }
    free( response );

    p = title;
    while ( *p ) {
        if ( (*p == '\t') || (*p == '\r') || (*p == '\n' ) )
            *p = ' ';
        p++;
    }

    p = title;
    while ( *p ) {
        while ( (*p == ' ') && (*(p + 1) == ' ') )
            strcpy( p, p + 1);
        p++;
    }

    p = title;
    while ( *p == ' ' )
        strcpy( p, p + 1);

    if ( *p ) {
        p = &(title[strlen(title) - 1]);
        while ( *p == ' ' )
            *p-- = NUL;
    }
    while ( ( p = strstr( title, "&raquo;" ) ) != NULL ) {
        strncpy( p, "≫", 2 );
        strcpy( p + 2, p + 7 );
    }
    while ( ( p = strstr( title, "&laquo;" ) ) != NULL ) {
        strncpy( p, "≪", 2 );
        strcpy( p + 2, p + 7 );
    }

    return ( title );
}

char    *
cutExtra( char *s )
{
    char    *p = &(s[strlen(s) - 1]);
    while ( (p >= s) &&
            ((*p == ' ') || (*p == '\t') || (*p == '\n') || (*p == '\r')) )
        *p-- = NUL;

    return ( s );
}

/* 指定文字列を別の指定文字列に置換する */
BOOL
replaceString( char *target, const char *src, const char *dst )
{
    char    *p = target;
    char    *q;
    BOOL    ret = FALSE;
    int     len = strlen( dst );

    while ( ( q = strstr( p, src ) ) != NULL ) {
        char    *temp;
        int     l = strlen( src );

        temp = (char *)malloc( strlen( p ) - l + strlen( dst ) + 1 );
        if ( temp ) {
            strncpy( temp, p, q - p );
            strcpy( &(temp[q - p]), dst );
            strcat( temp, q + l );

            strcpy( p, temp );
            free( temp );
            ret = TRUE;

            p = q + len;
        }
        else
            break;
    }

    return ( ret );
}

BOOL
replaceStringEx( char *target )
{
    const char  *src = "<";
    const char  *dst = "&lt;";
    char        *p = target;
    char        *q;
    BOOL        ret = FALSE;
    int         len = strlen( dst );

    while ( ( q = strstr( p, src ) ) != NULL ) {
        if ( ((*(q + 1) >= 'a') && (*(q + 1) <= 'z')) ||
             ((*(q + 1) >= 'A') && (*(q + 1) <= 'Z')) ||
             (*(q + 1) == '/')                           ) {
            p = q + 1;
            continue;
        }
        else {
            char    *temp;
            int     l = strlen( src );

            temp = (char *)malloc( strlen( p ) - l + strlen( dst ) + 1 );
            if ( temp ) {
                strncpy( temp, p, q - p );
                strcpy( &(temp[q - p]), dst );
                strcat( temp, q + l );

                strcpy( p, temp );
                free( temp );
                ret = TRUE;

                p = q + len;
            }
            else
                break;
        }
    }

    return ( ret );
}
