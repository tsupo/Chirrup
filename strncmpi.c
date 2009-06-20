/*
 *	strncmpi.c
 *			by H.Tsujimura
 *		compare strings with ingnoring lower/upper case
 *
 * History:
 * $Log: /makeRSS/xmlRPC/misc/strncmpi.c $
 * 
 * 2     06/10/03 18:56 Tsujimura543
 * 長らく K&R スタイルのまま放置していたのを、ANSI C スタイルに書き直した
 * 
 * 1     04/07/07 11:24 Tsujimura543
 * Revision 1.50  91/11/23 19:58:22  tsuporone
 * for ANEW library
 * 
 * Revision 1.1  91/04/27  15:05:24  tuzimura
 * Initial revision
 */

#ifndef	lint
static char	*rcs_id =
"$Header: /makeRSS/xmlRPC/misc/strncmpi.c 2     06/10/03 18:56 Tsujimura543 $";
#endif

int
strncmpi( const char *s, const char *t, int n )
{
    int ret = 0;
    int i, j;

    while ( *s && *t && ( n > 0 ) ) {
        i = *s++;
        j = *t++;
        if ( i != j ) {
            if ( ( i >= 'a' ) && ( i <= 'z' ) ) {
#if	0
                i = i - 'a' + 'A';
#else
                i &= ~0x20;
#endif
            }
            if ( ( j >= 'a' ) && ( j <= 'z' ) ) {
#if	0
                j = j - 'a' + 'A';
#else
                j &= ~0x20;
#endif
            }
            if ( i != j ) {
                ret = i - j;
                break;
            }
        }
        n--;
    }

    if ( ( ret == 0 ) && ( n > 0 ) ) {
        if ( *s )
            ret = *s;
        if ( *t )
            ret = -(*t);
    }

    return ( ret );
}
