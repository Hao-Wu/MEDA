// Dialog12.cpp : implementation file
//

#include "stdafx.h"
#include "mfcsystem.h"
#include "Dialog12.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog12 dialog


CDialog12::CDialog12(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog12::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog12)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialog12::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog12)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog12, CDialog)
	//{{AFX_MSG_MAP(CDialog12)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog12 message handlers
