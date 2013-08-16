// Dialog8.cpp : implementation file
//

#include "stdafx.h"
#include "mfcsystem.h"
#include "Dialog8.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog8 dialog


CDialog8::CDialog8(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog8::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog8)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialog8::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog8)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog8, CDialog)
	//{{AFX_MSG_MAP(CDialog8)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog8 message handlers
