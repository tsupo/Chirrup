/*
 * UploadImageDialog.cpp : Twitter クライアント chirrup
 *      画像ファイルアップロードダイアログ インプリメンテーション ファイル
 *          written by H.Tsujimura  6 Dec 2007
 *
 *      Copyright (c) 2007, 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/chirrup/UploadImageDialog.cpp $
 * 
 * 1     09/05/14 3:50 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 8     08/07/31 21:12 Tsujimura543
 * Wassr へのアップロードに対応
 * 
 * 7     08/02/07 22:36 Tsujimura543
 * copyright 表示を修正 (2008 を追加)
 * 
 * 6     08/01/24 14:46 Tsujimura543
 * 同時投稿対象切り替え機能を実装
 * 
 * 5     07/12/25 19:13 Tsujimura543
 * プレビュー表示領域サイズの計算式を変更
 * 
 * 4     07/12/19 13:29 Tsujimura543
 * 余分な処理を削除
 * 
 * 3     07/12/19 13:26 Tsujimura543
 * アップロードしようとしている画像ファイルのプレビュー表示を追加
 * 
 * 2     07/12/10 21:26 Tsujimura543
 * m_targetName を追加
 * 
 * 1     07/12/06 4:07 Tsujimura543
 * 新規作成
 */

#include "chirrup.h"
#include "UploadImageDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/UploadImageDialog.cpp 1     09/05/14 3:50 tsupo $";
#endif

#if (WINVER >= 0x0500)
//#define IDC_HAND    MAKEINTRESOURCE(32649)
#ifdef IDC_HAND
#undef IDC_HAND
#endif
#endif /* WINVER >= 0x0500 */
#define IDC_HAND    IDC_HAND2

/////////////////////////////////////////////////////////////////////////////
// CUploadImageDialog ダイアログ

CUploadImageDialog::CUploadImageDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CUploadImageDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUploadImageDialog)
	m_filename = _T("");
	m_caption = _T("");
	//}}AFX_DATA_INIT

    m_targetName = _T("ファイル名");
    m_bitmap     = NULL;

    m_gyazo              = false;
    m_flickr             = false;
    m_tumblr             = false;
    m_hatenaFotolife     = false;
    m_wassr              = false;

    m_sim_gyazo          = false;
    m_sim_flickr         = false;
    m_sim_tumblr         = false;
    m_sim_hatenaFotolife = false;
    m_sim_wassr          = false;

    m_hCursor = AfxGetApp()->LoadCursor( IDC_HAND );
}

CUploadImageDialog::~CUploadImageDialog()
{
    if ( m_bitmap )
        DeleteObject( m_bitmap );
}

void CUploadImageDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUploadImageDialog)
	DDX_Text(pDX, IDC_IMAGE_FILENAME, m_filename);
	DDV_MaxChars(pDX, m_filename, 512);
	DDX_Text(pDX, IDC_CAPTION, m_caption);
	DDV_MaxChars(pDX, m_caption, 2048);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUploadImageDialog, CDialog)
	//{{AFX_MSG_MAP(CUploadImageDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_SETCURSOR()
    ON_NOTIFY(TTN_NEEDTEXT, 0, OnDisplayToolTip)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUploadImageDialog 追加メソッド

bool CUploadImageDialog::IsInner( int id, WORD wX, WORD wY )
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

void CUploadImageDialog::SetStaticEdge( int idx, bool status )
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

/////////////////////////////////////////////////////////////////////////////
// CUploadImageDialog メッセージ ハンドラ

BOOL CUploadImageDialog::OnInitDialog() 
{
    CDialog::OnInitDialog();

    EnableToolTips(TRUE);

    return TRUE;
}

void CUploadImageDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

    if ( bShow ) {
        CEdit   *p;

        if ( m_filename.GetLength() > 0 ) {
            p = (CEdit *)GetDlgItem( IDC_IMAGE_FILENAME );
            p->SetWindowText( m_filename );

            // アップロードしようとしている画像のプレビュー(サムネイル)を表示
            CImage  image;
            int     height = 0;
            int     width  = 0;
            if ( !strncmp( m_filename, "http://",  7 ) ||
                 !strncmp( m_filename, "https://", 8 )    ) {
                m_bitmap = image.HttpOpen( m_filename );
            }
            else {
                m_bitmap = image.LoadImageFile( m_filename );
            }

            if ( m_bitmap ) {
                BITMAP  bmp;
                GetObject( m_bitmap, sizeof ( bmp ), (LPSTR)&bmp );
                height = bmp.bmHeight;
                width  = bmp.bmWidth;

                CStatic *sp = (CStatic *)GetDlgItem( IDC_BITMAP_THUMBNAIL );

                CRect   rect;
                CEdit   *ep = (CEdit *)GetDlgItem( IDC_CAPTION );
                ep->GetWindowRect( &rect );
                int     maxSq = (((rect.bottom - rect.top) - 2) * 12) / 10;

                sp->SetBitmap( m_bitmap );
                if ( (height > maxSq) || (width > maxSq) ) {
                    // 表示領域サイズに合わせて画像を縮小表示する
                    int sig = ((max(height, width)) + (maxSq - 1)) / maxSq;
                    sp->SetWindowPos( sp->GetTopWindow(),
                                      0, 0, width/sig, height/sig,
                                      SWP_NOMOVE );
                }
            }
        }
        if ( m_caption.GetLength() > 0 ) {
            p = (CEdit *)GetDlgItem( IDC_CAPTION );
            p->SetWindowText( m_caption );
        }

        if ( m_targetName.GetLength() > 0 ) {
            CStatic *sp = (CStatic *)GetDlgItem( IDC_TARGET_NAME );
            sp->SetWindowText( m_targetName );
        }

        m_sim_gyazo          = m_gyazo;
        m_sim_flickr         = m_flickr;
        m_sim_tumblr         = m_tumblr;
        m_sim_hatenaFotolife = m_hatenaFotolife;
        m_sim_wassr          = m_wassr;

        SetStaticEdge( IDC_GYAZO,          m_sim_gyazo );
        SetStaticEdge( IDC_FLICKR,         m_sim_flickr );
        SetStaticEdge( IDC_TUMBLR,         m_sim_tumblr );
        SetStaticEdge( IDC_HATENAFOTOLIFE, m_sim_hatenaFotolife );
        SetStaticEdge( IDC_WASSR,          m_sim_wassr );
    }
}

BOOL CUploadImageDialog::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
    if ( nHitTest == HTCLIENT ) {
        static int targetIDC[] = {
            IDC_GYAZO,
            IDC_FLICKR,
            IDC_TUMBLR,
            IDC_HATENAFOTOLIFE,
            IDC_WASSR,
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
    }
	
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
void CUploadImageDialog::OnDisplayToolTip(NMHDR* pNMHDR, LRESULT* pResult)
{
    TOOLTIPTEXT *tp = (TOOLTIPTEXT *)pNMHDR;

    if ( (tp->uFlags & TTF_IDISHWND) == TTF_IDISHWND ) {
        int id = ::GetDlgCtrlID( (HWND)tp->hdr.idFrom );
        CString text = _T("");

        switch ( id ) {
        case IDC_GYAZO:
            text = _T("Gyazo");
            text += _T(" (同時投稿対象");
            text += m_sim_gyazo ? _T(")") : _T("外)");
            break;
        case IDC_FLICKR:
            text = _T("flickr");
            text += _T(" (同時投稿対象");
            text += m_sim_flickr ? _T(")") : _T("外)");
            break;
        case IDC_TUMBLR:
            text = _T("tumblr");
            text += _T(" (同時投稿対象");
            text += m_sim_tumblr ? _T(")") : _T("外)");
            break;
        case IDC_HATENAFOTOLIFE:
            text = _T("はてなフォトライフ");
            text += _T(" (同時投稿対象");
            text += m_sim_hatenaFotolife ? _T(")") : _T("外)");
            break;
        case IDC_WASSR:
            text = _T("Wassr");
            text += _T(" (同時投稿対象");
            text += m_sim_wassr ? _T(")") : _T("外)");
            break;
        }

        if ( text.GetLength() > 0 )
            strcat( tp->szText, text );
    }
}
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif

#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
void CUploadImageDialog::OnContextMenu(CWnd* pWnd, CPoint point) 
{
    DWORD   dwPos     = GetMessagePos();
    WORD    wX        = LOWORD( dwPos );
    WORD    wY        = HIWORD( dwPos );
    bool    onOff     = false;
    int     targetIDC = 0;

    if ( IsInner( IDC_GYAZO, wX, wY ) ) {
        if ( m_gyazo ) {
            targetIDC = IDC_GYAZO;
            onOff     = m_sim_gyazo;
        }
    }
    else if ( IsInner( IDC_FLICKR, wX, wY ) ) {
        if ( m_flickr ) {
            targetIDC = IDC_FLICKR;
            onOff     = m_sim_flickr;
        }
    }
    else if ( IsInner( IDC_TUMBLR, wX, wY ) ) {
        if ( m_tumblr ) {
            targetIDC = IDC_TUMBLR;
            onOff     = m_sim_tumblr;
        }
    }
    else if ( IsInner( IDC_HATENAFOTOLIFE, wX, wY ) ) {
        if ( m_hatenaFotolife ) {
            targetIDC = IDC_HATENAFOTOLIFE;
            onOff     = m_sim_hatenaFotolife;
        }
    }
    else if ( IsInner( IDC_WASSR, wX, wY ) ) {
        if ( m_wassr ) {
            targetIDC = IDC_WASSR;
            onOff     = m_sim_wassr;
        }
    }

    if ( targetIDC == 0 )
        return;

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
        case IDC_GYAZO:
            m_sim_gyazo = !(m_sim_gyazo);
            SetStaticEdge( targetIDC, m_sim_gyazo );
            break;
        case IDC_FLICKR:
            m_sim_flickr = !(m_sim_flickr);
            SetStaticEdge( targetIDC, m_sim_flickr );
            break;
        case IDC_TUMBLR:
            m_sim_tumblr = !(m_sim_tumblr);
            SetStaticEdge( targetIDC, m_sim_tumblr );
            break;
        case IDC_HATENAFOTOLIFE:
            m_sim_hatenaFotolife = !(m_sim_hatenaFotolife);
            SetStaticEdge( targetIDC, m_sim_hatenaFotolife );
            break;
        case IDC_WASSR:
            m_sim_wassr = !(m_sim_wassr);
            SetStaticEdge( targetIDC, m_sim_wassr );
            break;
        }
    }

    menu.DestroyMenu();	
}
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif
