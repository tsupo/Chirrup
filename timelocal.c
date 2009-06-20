/*
 *  timelocal.c
 *
 *      Copyright (c) 1995, 2005 H.Tsujimura
 *      written by H.Tsujimura  13 Jun 1995
 *
 *      timelocal() は localtime() の逆関数で BSD 系 UNIX 由来の関数である。
 *      本 timelocal.c は timelocal() を独自に実装したものである。
 *
 * $Log: /makeRSS/clcoo/timelocal.c $
 * 
 * 2     06/09/29 18:57 Tsujimura543
 * RCS(VSS)の Header 情報を埋め込み忘れていたので、改めて埋め込んでみた
 * 
 * 1     05/06/06 15:57 Tsujimura543
 * datetime.c から timelocal() を分離
 */

#include <time.h>

#ifndef	lint
static char	*rcs_id =
"$Header: /makeRSS/clcoo/timelocal.c 2     06/09/29 18:57 Tsujimura543 $";
#endif

#define	isleapyear(y)	(((y)%4 == 0) && (((y)%100 != 0) || ((y)%400 == 0)))

static int  mdays[] = {
    31, 28, 31, 30, 31, 30,
    31, 31, 30, 31, 30, 31
};

time_t
timelocal( struct tm *tm )
{
    long    day = 0L, t;
    int     yy, mm, dd;

    yy = tm->tm_year + 1900;
    mm = tm->tm_mon  + 1;
    dd = tm->tm_mday;
    t  = (tm->tm_hour * 60L + tm->tm_min) * 60L + tm->tm_sec;
    day = dd;
    mm--;
    while ( yy >= 1970 ) {
        while ( mm >= 1 ) {
            day += mdays[mm-1];
            if ( mm == 2 )
                if ( isleapyear( yy ) )
                    day++;
            mm--;
        }
        yy--;
        mm = 12;
    }
    return ( (time_t)((day - 1L) * 24L * 60L * 60L + t) );
}
