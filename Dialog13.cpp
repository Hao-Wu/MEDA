// Dialog13.cpp : implementation file
//

#include "stdafx.h"
#include "mfcsystem.h"
#include "Dialog13.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog13 dialog


CDialog13::CDialog13(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog13::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog13)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialog13::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog13)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog13, CDialog)
	//{{AFX_MSG_MAP(CDialog13)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog13 message handlers
