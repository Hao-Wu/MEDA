// Dialog6.cpp : implementation file
//

#include "stdafx.h"
#include "MFCsystem.h"
#include "Dialog6.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog6 dialog


CDialog6::CDialog6(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog6::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog6)
	//}}AFX_DATA_INIT
}


void CDialog6::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog6)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog6, CDialog)
	//{{AFX_MSG_MAP(CDialog6)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog6 message handlers
