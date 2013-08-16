// Dialog2.cpp : implementation file
//

#include "stdafx.h"
#include "MFCsystem.h"
#include "Dialog2.h"
#include "MyFileDialog.h"
#include "BigInt.h"
#include "Window.h"
#include "GfL.h"

#ifdef _DEBUG
#define new DEBUG_NEW

#define CHECK(x)			{if( !(x) ) return ;}
#define CHECK_MSG(x,msg)	{if( !(x) ){CWindow::ShowMessage(msg);return ;}}
#define EQUAL(BI,y)			( BI.len==1 && BI.bit[0]==y )


#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog2 dialog


CDialog2::CDialog2(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog2)
	m_input = _T("");
	m_output = _T("");
	m_deskey = _T("");
	m_deskey2 = _T("");
	m_defpath = _T("");
	//}}AFX_DATA_INIT
}


void CDialog2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog2)
	DDX_Text(pDX, IDC_Input, m_input);
	DDX_Text(pDX, IDC_Output, m_output);
	DDX_Text(pDX, IDC_DesKey, m_deskey);
	DDX_Text(pDX, IDC_DesKey2, m_deskey2);
	DDX_Text(pDX, IDC_DefPath, m_defpath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog2, CDialog)
	//{{AFX_MSG_MAP(CDialog2)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_Browse, OnBrowse)
	ON_BN_CLICKED(IDC_DelOrgFileCHECK, OnDelOrgFileCHECK)
	ON_BN_CLICKED(IDC_DelEptFileCHECK, OnDelEptFileCHECK)
	ON_BN_CLICKED(IDC_DelNoteCHECK, OnDelNoteCHECK)
	ON_BN_CLICKED(IDC_Run, OnRun)
	ON_BN_CLICKED(IDC_OutFolder, OnOutFolder)
	ON_BN_CLICKED(IDC_DefPathCHECK, OnDefPathCHECK)
	ON_BN_CLICKED(IDC_DefFolder, OnDefFolder)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog2 message handlers

void CDialog2::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE,NULL,NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,NULL,NULL) ;   
		dlg.DoModal();
	
//		m_Cedit1=dlg.GetPathName();
		UpdateData(false);
	
	
}




BOOL CDialog2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	


//	CheckDlgButton(IDC_DefPathCHECK,BST_CHECKED);
	EnableDefPathCtls(false);

		CheckDlgButton(IDC_DelNoteCHECK,BST_CHECKED);


		
		delnote = true;
	
		delorgfile =false;
	
		deleptfile =false;

		usedefpath=false;
	//oldformat = format = theApp.GetProfileInt("Option","Format",MCS)?true:false;
	//	CheckRadioButton(IDC_MCSRADIO,IDC_DESRADIO,IDC_MCSRADIO);

		run_type = ENCRYPT;
		 format = DES;
	//	if( format == DES )
	//	{
		//	CheckRadioButton(IDC_MCSRADIO,IDC_DESRADIO,IDC_DESRADIO);
		//	EnableDesCtls(true);
		//	EnableMcsCtls(false);
		//}
	UpdateData(false);
	    SetTimer(1,400,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CDialog2::OnBrowse() 
{
	// TODO: Add your control notification handler code here
	

	CString Filter= "所有文件(*.*)|*.*|DES加密文件(*.des)|*.des|文本文件(*.txt)|*.txt|";
		//"DES加密文件(*.des)|*.des||";
	
	CMyFileDialog FileDlg (TRUE, NULL, NULL, OFN_HIDEREADONLY, Filter);
	if (!( FileDlg.DoModal() == IDOK ))
	{
		return ;
	}	
	UpdateData(true);
	m_input = FileDlg.GetPathName();
	m_output = "";
	UpdateData(false);
	
	run_type  = DECRYPT; /////////??????????????????????????????????
	//EnableFormatCtls(false);
	//EnableDesCtls(false);
	//EnableMcsCtls(false);
	SetDlgItemText(IDC_Run,"解密");

	if( m_input.Find(".des")>0 || m_input.Find(".DES")>0 )
	{
		oldformat = DES;
		format    = DES;
		BuildOutputFileName();
		//EnableDesCtls(true);
	}
	else
	{
		run_type = ENCRYPT;
		format   = DES;
		oldformat = DES;

		BuildOutputFileName();
		SetDlgItemText(IDC_Run,"加密");
		
		//EnableFormatCtls(true);
		//if( format == DES )
			//EnableDesCtls(true);
		//else
			//EnableMcsCtls(true);
	}
}

void CDialog2::EnableMcsCtls(bool show)
{
	

}

void CDialog2::EnableDesCtls(bool show) //应该添加此函数体
{

}

void CDialog2::EnableDefPathCtls(bool show)
{
	if(show)
	{
		GetDlgItem(IDC_STATIC123)->EnableWindow(true);
		GetDlgItem(IDC_DefPath)->EnableWindow(true);
		GetDlgItem(IDC_DefFolder)->EnableWindow(true);
	}
	else
	{
		GetDlgItem(IDC_STATIC123)->EnableWindow(false);
		GetDlgItem(IDC_DefPath)->EnableWindow(false);
		GetDlgItem(IDC_DefFolder)->EnableWindow(false);
	}
}

void CDialog2::EnableFormatCtls(bool show) 
{

}

void CDialog2::BuildOutputFileName()
{
	UpdateData(true);
	if( m_input.IsEmpty() )
	{
		m_output = "";
		UpdateData(false);
		return;
	}
	
	CString path= (usedefpath && !m_defpath.IsEmpty()) ? m_defpath : CWindow::GetPath(m_input); 
	CString name= CWindow::GetFileNameNoExt( m_output.IsEmpty() ? m_input : m_output );
	CString ext = CWindow::GetExtName(m_input);
	CString newext = (run_type==DECRYPT) ? "" : (format==MCS) ? "mcs" : "des";
	
	if( path.GetAt( path.GetLength()-1 ) != '\\' )
		path += "\\";
	if( run_type==DECRYPT )
		if( ext.GetLength()>4 && ext.GetAt(ext.GetLength()-4)=='.' )
			ext = ext.Left( ext.GetLength()-4 );
		else
			ext = "";
		
		m_output = path + name;
		if( ext.GetLength() )
			m_output += "." + ext;
		if( newext.GetLength() )
			m_output += "." + newext;
	UpdateData(false);


}

void CDialog2::OnDelOrgFileCHECK() 
{
	// TODO: Add your control notification handler code here
		delorgfile = !delorgfile;
}

void CDialog2::OnDelEptFileCHECK() 
{
	// TODO: Add your control notification handler code here
		deleptfile = !deleptfile;
}

void CDialog2::OnDelNoteCHECK() 
{
	// TODO: Add your control notification handler code here
		delnote = !delnote;
	
}

void CDialog2::OnRun() 
{
	// TODO: Add your control notification handler code here
	//CHECK ( IDYES == MessageBox("真的要进行该操作吗? ","提示",MB_YESNO | MB_ICONQUESTION) )
	if( IDYES!= MessageBox("真的要进行该操作吗?\n\n该操作可能会花费一段时间 ","提示",MB_YESNO | MB_ICONQUESTION) )
		return;
	bool	flage;
	DWORD   time=GetTickCount();
	//	CString str= (run_type==ENCRYPT) ? "加密": "解密",tmp;    //?????????????????????????????????
	
	BuildOutputFileName();
	if( format == DES )
	if( m_deskey != m_deskey2)
	{

		MessageBox("密钥不一致，请重新输入!");
	
		m_deskey="";
		m_deskey2="";
		UpdateData(false);
		return;

	}
if( run_type==ENCRYPT)
	{
		if(format==DES)
		
	
			flage = des.Des2Encrypt(m_output.GetBuffer(0),m_input.GetBuffer(0),
								m_deskey.GetBuffer(0));
	}
	else
	{
		if( format == DES )
		
			flage = des.Des2Decrypt(m_output.GetBuffer(0),m_input.GetBuffer(0),
			m_deskey.GetBuffer(0));
	}

		
		if( flage )
		{
			Str.Format("%s成功! 用时%u秒。",(run_type==ENCRYPT)?"加密":"解密",(GetTickCount()-time)/1000);
		

			MessageBox(Str,"提示",MB_ICONINFORMATION);
			
			if( (run_type==ENCRYPT && delorgfile) ||
				(run_type==DECRYPT && deleptfile) )
			{
				Str.Format("是否删除文件：\n%s",m_input);
				if( !delnote )
					DeleteFile(m_input);
				else if( IDYES==MessageBox(Str,"提示",MB_YESNO | MB_ICONQUESTION) )
					DeleteFile(m_input);
			}
			m_deskey="";
			m_deskey2="";
			UpdateData(false);

	}
}

void CDialog2::OnOutFolder() 
{
	CString		defpath = m_defpath;
	bool        tmp = usedefpath;
    usedefpath = true;
	UpdateData(true);
	CWindow::GetFolder(m_defpath);
	UpdateData(false);
    BuildOutputFileName();
    m_defpath = defpath;
    usedefpath = tmp;
	UpdateData(false);
	
}

void CDialog2::OnDefPathCHECK() 
{
	usedefpath = !usedefpath;
	if( usedefpath )
	{
		EnableDefPathCtls(true);
		BuildOutputFileName();
	}
	else
	{
		EnableDefPathCtls(false);
	}	// TODO: Add your control notification handler code here
	
}

void CDialog2::OnDefFolder() 
{
	// TODO: Add your control notification handler code here

	UpdateData(true);
	CWindow::GetFolder(m_defpath);
	UpdateData(false);
    BuildOutputFileName();
	
}
