// Dialog7.cpp : implementation file
//

#include "stdafx.h"
#include "mfcsystem.h"
#include "Dialog7.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog7 dialog


CDialog7::CDialog7(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog7::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog7)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialog7::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog7)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog7, CDialog)
	//{{AFX_MSG_MAP(CDialog7)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog7 message handlers
