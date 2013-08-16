// MFCsystemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCsystem.h"
#include "MFCsystemDlg.h"
#include"Dialog1.h"
#include"Dialog2.h"
#include"Dialog3.h"
#include"Dialog4.h"
#include"Dialog6.h"
#include"Dialog7.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

CDialog1 m_mm1;
CDialog2 m_mm2;
CDialog4 m_mm3;
CDialog3 m_mm4;
CDialog6 m_mm6;
CDialog7 m_mm7;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCsystemDlg dialog

CMFCsystemDlg::CMFCsystemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFCsystemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMFCsystemDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCsystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMFCsystemDlg)
	DDX_Control(pDX, IDC_TAB1, m_tabctrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMFCsystemDlg, CDialog)
	//{{AFX_MSG_MAP(CMFCsystemDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_WM_MOVE()
	ON_WM_CLOSE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCsystemDlg message handlers

BOOL CMFCsystemDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
//	this->ShowWindow(SW_SHOWMAXIMIZED);   

	TCITEM item;
	item.mask=TCIF_TEXT;

	CSize  size;
	size.cx =50;
	size.cy =30;

	m_tabctrl.SetItemSize (size);
	item.pszText="数据加解密";
	m_tabctrl.InsertItem (0,&item);
	item.pszText="文件加解密";
	m_tabctrl.InsertItem (1,&item);

//	item.pszText="文件解密";
//	m_tabctrl.InsertItem (2,&item);

	item.pszText="加密算法演示";
	m_tabctrl.InsertItem (2,&item);


	item.pszText="帮助";
	m_tabctrl.InsertItem (3,&item);


	item.pszText="关于";
	m_tabctrl.InsertItem (4,&item);

	m_mm1.Create (IDD_DIALOG1,&m_tabctrl);//数据加解密 0
	m_mm2.Create (IDD_DIALOG2,&m_tabctrl);//文件夹解密 1
	m_mm3.Create(IDD_DIALOG4,&m_tabctrl);//加密算法演示 2

	m_mm7.Create (IDD_DIALOG7,&m_tabctrl);//关于 3
	m_mm6.Create (IDD_DIALOG6,&m_tabctrl);//帮助 4 

	CRect r;
	m_tabctrl.GetClientRect (&r);

	m_mm1.SetWindowPos (NULL,1,30,1115,800,SWP_SHOWWINDOW);
	m_mm2.SetWindowPos (NULL,1,30,1115,800,SWP_HIDEWINDOW);
	m_mm3.SetWindowPos (NULL,1,30,1115,800,SWP_HIDEWINDOW);
//	m_mm7.SetWindowPos (NULL,1,30,1100,600,SWP_HIDEWINDOW);
	m_mm6.SetWindowPos (NULL,1,30,1115,800,SWP_HIDEWINDOW);

	//m_mm2.SetWindowPos (NULL,10,30,400,100,SWP_HIDEWINDOW);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCsystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCsystemDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCsystemDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMFCsystemDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CRect r;
	m_tabctrl.GetClientRect (&r);


	switch(m_tabctrl.GetCurSel())
{
case 0:
m_mm1.SetWindowPos (NULL,1,30,1115,800,					SWP_SHOWWINDOW);//数据加解密
m_mm2.SetWindowPos (NULL,1,30,r.right ,r.bottom -40,SWP_HIDEWINDOW );  //文件夹解密
m_mm3.SetWindowPos (NULL,1,30,r.right ,r.bottom -40,SWP_HIDEWINDOW );  //加密算法掩饰
m_mm7.SetWindowPos (NULL,1,30,r.right ,r.bottom -40,SWP_HIDEWINDOW );  //关于
m_mm6.SetWindowPos (NULL,1,30,r.right ,r.bottom -40,SWP_HIDEWINDOW );  //帮助
break;
case 1:
m_mm1.SetWindowPos (NULL,1,30,r.right ,r.bottom -40,SWP_HIDEWINDOW);
m_mm2.SetWindowPos (NULL,1,30,1100,800,SWP_SHOWWINDOW );
m_mm3.SetWindowPos (NULL,1,30,r.right ,r.bottom -40,SWP_HIDEWINDOW );  
m_mm7.SetWindowPos (NULL,1,30,r.right ,r.bottom -40,SWP_HIDEWINDOW );    
m_mm6.SetWindowPos (NULL,1,30,r.right ,r.bottom -40,SWP_HIDEWINDOW );  
break;
case 2:
m_mm1.SetWindowPos (NULL,1,30,r.right ,r.bottom -40,SWP_HIDEWINDOW);

m_mm2.SetWindowPos (NULL,1,30,r.right ,r.bottom -40,SWP_HIDEWINDOW );  
m_mm3.SetWindowPos (NULL,1,30,1115,800,SWP_SHOWWINDOW );
m_mm7.SetWindowPos (NULL,1,30,r.right ,r.bottom -40,SWP_HIDEWINDOW );    
m_mm6.SetWindowPos (NULL,1,30,r.right ,r.bottom -40,SWP_HIDEWINDOW );  
break;
case 3:
::ShellExecute(NULL,"open","help\\NewProject.chm",NULL,NULL,SW_SHOW   );
   
break;
case 4:

		m_mm7.SetWindowPos (NULL,550,1,480,190,SWP_SHOWWINDOW );   
	break;
//500,15,400,160
}


	*pResult = 0;
}

void CMFCsystemDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	
	// TODO: Add your message handler code here
	
}

BOOL CMFCsystemDlg::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::PreCreateWindow(cs);
}

void CMFCsystemDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
}

void CMFCsystemDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here


}
