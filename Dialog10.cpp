// Dialog10.cpp : implementation file
//

#include "stdafx.h"
#include "mfcsystem.h"
#include "Dialog10.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog10 dialog


CDialog10::CDialog10(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog10::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog10)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialog10::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog10)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog10, CDialog)
	//{{AFX_MSG_MAP(CDialog10)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog10 message handlers
