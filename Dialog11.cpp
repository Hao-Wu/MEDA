// Dialog11.cpp : implementation file
//

#include "stdafx.h"
#include "mfcsystem.h"
#include "Dialog11.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog11 dialog


CDialog11::CDialog11(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog11::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog11)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialog11::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog11)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog11, CDialog)
	//{{AFX_MSG_MAP(CDialog11)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog11 message handlers
