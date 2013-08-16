// Dialog9.cpp : implementation file
//

#include "stdafx.h"
#include "mfcsystem.h"
#include "Dialog9.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog9 dialog


CDialog9::CDialog9(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog9::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog9)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialog9::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog9)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog9, CDialog)
	//{{AFX_MSG_MAP(CDialog9)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog9 message handlers
