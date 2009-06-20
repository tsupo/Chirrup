/*
 * BlogIDSelectDlg.cpp : Twitter クライアント chirrup
 *      Blog ID 選択ダイアログ インプリメンテーション ファイル
 *
 *          written by H.Tsujimura  15 Oct 2004 / 2 Mar 2007 / 28 May 2009
 *
 *      Copyright (c) 2004, 2005, 2006, 2007, 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  「ここうさぎ」、「BloGolEe」、「bookey」で使っているソースコードを流用
 *
 * $Log: /comm/chirrup/BlogIDSelectDlg.cpp $
 * 
 * 1     09/05/31 20:28 tsupo
 * VSSサーバ拠点を変更
 * 
 * 1     09/05/29 18:24 Tsujimura543
 * Chirrup 向けの最初の版
 */

#include "chirrup.h"
#include "BlogIDSelectDlg.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/BlogIDSelectDlg.cpp 1     09/05/31 20:28 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBlogIDSelectDlg ダイアログ

CBlogIDSelectDlg::CBlogIDSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBlogIDSelectDlg::IDD, pParent)
{
    m_blogList   = NULL;
    m_numOfBlogs = 0;

	//{{AFX_DATA_INIT(CBlogIDSelectDlg)
	m_blogIDlistIndex = -1;
	//}}AFX_DATA_INIT
}

void CBlogIDSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBlogIDSelectDlg)
	DDX_Control(pDX, IDC_LIST_BLOGID, m_blogIDlist);
	DDX_LBIndex(pDX, IDC_LIST_BLOGID, m_blogIDlistIndex);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBlogIDSelectDlg, CDialog)
	//{{AFX_MSG_MAP(CBlogIDSelectDlg)
	ON_WM_SHOWWINDOW()
	ON_LBN_SELCHANGE(IDC_LIST_BLOGID, OnSelchangeListBlogid)
	ON_LBN_DBLCLK(IDC_LIST_BLOGID, OnDblclkListBlogID)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlogIDSelectDlg 独自追加コード

void    CBlogIDSelectDlg::initialize( BLOGINF *blogList, int numOfBlogs )
{
    if ( blogList && (numOfBlogs > 0) ) {
        if ( m_blogList )
            delete [] m_blogList;
        m_blogList   = new BLOGINF [numOfBlogs];
        m_numOfBlogs = numOfBlogs;

        for ( int i = 0; i < numOfBlogs; i++ )
            m_blogList[i] = blogList[i];
    }
}

void    CBlogIDSelectDlg::initBlogList()
{
    char    *p;

    for ( int i = 0; i < m_numOfBlogs; i++ ) {
        p = utf2sjis( m_blogList[i].blogName );
        m_blogIDlist.AddString( p ? p : m_blogList[i].blogName );
    }
}

/////////////////////////////////////////////////////////////////////////////
// CBlogIDSelectDlg メッセージ ハンドラ

void CBlogIDSelectDlg::OnOK() 
{
    if ( m_blogIDlistIndex == -1 ) {
        // blog ID 未選択の場合
        MessageBox( "blog を選択してください    ",
                    "blog 未選択",
                    MB_OK|MB_ICONWARNING );
        return;
    }
	
	CDialog::OnOK();
}

void CBlogIDSelectDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow && m_blogList ) {
        m_blogIDlist.InitStorage( m_numOfBlogs,
                                  MAX_BLOG_NAME_LENGTH );
        initBlogList();
    }	
}

void CBlogIDSelectDlg::OnSelchangeListBlogid() 
{
    int location = m_blogIDlist.GetCurSel();
    if ( location >= 0 )
        m_blogIDlistIndex = location;
}

void CBlogIDSelectDlg::OnDblclkListBlogID() 
{
    OnSelchangeListBlogid();
    OnOK();
}
