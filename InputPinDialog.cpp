/*
 * InputPinDialog.cpp  : Twitter クライアント chirrup
 *      (OAuth の) PIN 入力ダイアログ インプリメンテーション ファイル
 *          written by H.Tsujimura  11 Jun 2009
 *
 * $Log: /comm/chirrup/InputPinDialog.cpp $
 * 
 * 1     09/06/18 1:25 tsupo
 * VSSサーバ拠点を変更
 * 
 * 2     09/06/16 0:47 Tsujimura543
 * PIN が 0 で始まる6桁の数字の場合にも対応
 * 
 * 1     09/06/11 18:52 Tsujimura543
 * 新規作成 (bookey 用に作成したソースを流用)
 */

#include "chirrup.h"
#include "InputPinDialog.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/chirrup/InputPinDialog.cpp 1     09/06/18 1:25 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// InputPinDialog ダイアログ

InputPinDialog::InputPinDialog(CWnd* pParent /*=NULL*/)
	: CDialog(InputPinDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(InputPinDialog)
	m_pin = _T("");
	//}}AFX_DATA_INIT
}

void InputPinDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(InputPinDialog)
	DDX_Text(pDX, IDC_EDIT_PIN, m_pin);
	DDV_MaxChars(pDX, m_pin, 12);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(InputPinDialog, CDialog)
	//{{AFX_MSG_MAP(InputPinDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// InputPinDialog メッセージ ハンドラ

void InputPinDialog::OnOK() 
{
    long    num = 0;
    CString str = "";
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_PIN );
    p->GetWindowText( str );
    if ( str.GetLength() > 0 )
        num = atol( str );
    if ( str.GetLength() < 6 ) {
        // 注: 0 で始まる6桁の数字もあり得る(ことがわかった)
        CString ttl = _T("");
        CString msg = _T("");

        ttl.LoadString(IDS_TTL_INPUT_PIN);
        msg.LoadString(IDS_TXT_INPUT_PIN);
        MessageBox( msg, ttl, MB_OK|MB_ICONWARNING );
        return;
    }

    char    buf[64];
    m_pin  = _T("00000");
    m_pin += ltoa( num, buf, 10 );
    m_pin  = m_pin.Right(6);

	CDialog::OnOK();
}
