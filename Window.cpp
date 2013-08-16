// Window.cpp: implementation of the CWindow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "MixedCS.h"
#include "Window.h"
#include "MyFileDialog.h"
#include <shlobj.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CWindow::CWindow()
{
	wnd.m_hWnd = GetActiveWindow();
	wnd.GetWindowText(caption);
}

CWindow::~CWindow()
{
	EndWaitCursor();
	wnd.m_hWnd = 0;//必须置0，否则Windows将关闭当前窗口
}

///////////////////////////////////////////////////////////////////////////////
// CWindows Functions
///////////////////////////////////////////////////////////////////////////////
#define STR_MAXLEN			1000

#define CHECK(x)			{if( !(x) ) return false;}
#define CHECK_MSG(x,msg)	{if( !(x) ) {ShowMessage(msg);return false;}}

/******************************************************************************/
//	名称：ShowWaitCursor()
//	功能：显示等待光标
//  参数：
//	返回：
/******************************************************************************/
void CWindow::ShowWaitCursor()
{
	wnd.m_hWnd = GetActiveWindow();
	wnd.GetWindowText(caption);
	wnd.BeginWaitCursor();
}
/******************************************************************************/
//	名称：EndWaitCursor
//	功能：结束等待光标
//  参数：
//	返回：
/******************************************************************************/
void CWindow::EndWaitCursor()
{
	wnd.EndWaitCursor();
    wnd.SetWindowText(caption);
}
/******************************************************************************/
//	名称：SetWindowCaption
//	功能：设置窗口标题
//  参数：
//	返回：
/******************************************************************************/
void CWindow::SetWindowCaption(char *Str,int v1,int v2,int v3)
{
	CString	    newname;
	newname.Format(Str,v1,v2,v3);
	wnd.SetWindowText(newname);
}
/******************************************************************************/
//	名称：ShowMessage
//	功能：显示消息框
//  参数：
//	返回：
/******************************************************************************/
int CWindow::ShowMessage(const char *msg,const char *title,UINT flage)
{
	CHECK( msg && title )
	return MessageBox(GetActiveWindow(),msg,title,flage);
}
/******************************************************************************/
//	名称：InputKeyStr
//	功能：打开选择文件对话框，导入字符串
//  参数：
//	返回：导入成功返回true，否则返回false
/******************************************************************************/
bool CWindow::InputStr(CString &Str)
{
	CString Filter= "文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||";

	CMyFileDialog FileDlg (TRUE, NULL, NULL, OFN_HIDEREADONLY, Filter);

    CHECK( FileDlg.DoModal()==IDOK )

	char buf[STR_MAXLEN+1];

	CHECK( GetStrFromFile(buf,FileDlg.GetPathName().GetBuffer(0)) )
    Str = buf;

	return true;
}
/******************************************************************************/
//	名称：OutputKeyStr
//	功能：打开选择文件对话框，导出字符串
//  参数：
//	返回：导出成功返回true，否则返回false
/******************************************************************************/
bool CWindow::OutputStr(CString &Str)
{
	CHECK_MSG( !Str.IsEmpty(), "空内容!  " )

	CString Filter= "文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||";

	CMyFileDialog FileDlg(FALSE, "txt", NULL, OFN_HIDEREADONLY, Filter);

    CHECK( FileDlg.DoModal()==IDOK )

	CHECK( SaveStrToFile(Str.GetBuffer(0),FileDlg.GetPathName().GetBuffer(0)) )

	return true;
}
/******************************************************************************/
//	名称：GetFolder
//	功能：目录选择对话框
//  参数：
//	返回：选择成功返回true，否则返回false
/******************************************************************************/
bool CWindow::GetFolder(CString &Folder)
{
	BROWSEINFO	bi; 
	ITEMIDLIST	*pidl; 
    char		Dir[256];

	memset(&bi, 0, sizeof(bi));
	bi.pszDisplayName = Dir; 
	bi.lpszTitle = "请选择目录"; 
	bi.ulFlags = BIF_RETURNONLYFSDIRS; 

	pidl = SHBrowseForFolder(&bi);
	CHECK( pidl!=NULL ) 
	SHGetPathFromIDList(pidl,Dir);
    GlobalFree(pidl);
	Folder = Dir;

	return true;
}
/******************************************************************************/
//	名称：IsFileExist
//	功能：检查文件是否存在
//  参数：
//	返回：存在返回true，否则返回false
/******************************************************************************/
bool CWindow::IsFileExist(const char *File)
{
	HFILE	fh;

	CHECK( File )
	CHECK( (fh=_lopen(File,OF_READ)) != -1 )

	_lclose(fh);
	return	true;
}
/******************************************************************************/
//	名称：GetStrFromFile
//	功能：从文件中读取字符串
//  参数：
//	返回：读取成功返回true，否则返回false
/******************************************************************************/
bool CWindow::GetStrFromFile(char *Str,const char *File)
{
	CHECK( Str && File );

    HFILE	fh;

    CHECK_MSG( (fh=_lopen(File,OF_READ)) != -1, "错误：无法打开文件! " )

	int len = _lread(fh,Str,STR_MAXLEN);
    Str[len] = '\0'; 
   
    _lclose(fh);
	return true;
}
/******************************************************************************/
//	名称：SaveStrToFile
//	功能：保存字符串到文件中
//  参数：
//	返回：保存成功返回true，否则返回false
/******************************************************************************/
bool CWindow::SaveStrToFile(const char *Str,const char *File)
{
	CHECK( Str && File );

    HFILE	fh;

	if( IsFileExist(File) )
		CHECK( IDYES == ShowMessage("该文件已存在，是否覆盖? ","提示",
			                        MB_YESNO | MB_ICONQUESTION) )
    CHECK_MSG( (fh=_lcreat(File,0)) != -1, "错误：无法创建文件! ")
	_lwrite(fh,Str,strlen(Str));

    _lclose(fh);
	return true;
}
/******************************************************************************/
//	名称：GetFileNameWithExt
//	功能：获取文件名(带扩展名)
//  参数：
/******************************************************************************/
CString CWindow::GetFileNameWithExt(const CString &File)
{
    int i,j=File.GetLength();
    CString Name;

	for(i=j-1; i>=0 && File.GetAt(i)!='\\'; --i);
	Name = (i<0 ) ? File : File.Right(j-i-1);

	return Name;
}
/******************************************************************************/
//	名称：GetFileNameNoExt
//	功能：获取文件名(无扩展名)
//  参数：
//	返回：文件名(无扩展名)
/******************************************************************************/
CString CWindow::GetFileNameNoExt(const CString &File)
{
    CString Name = GetFileNameWithExt(File);
	CString Ext  = GetExtName(Name);
	int		len  = Ext.IsEmpty() ? 0 : Ext.GetLength()+1;

	Name = Name.Left(Name.GetLength()-len);

	return Name;
}
/******************************************************************************/
//	名称：GetExtName
//	功能：获取扩展名
//  参数：
//	返回：扩展名
/******************************************************************************/
CString CWindow::GetExtName(const CString &File)
{
    int i,j=File.GetLength();
    CString Ext;

	for(i=0; i<j && File.GetAt(i)!='.'; ++i);
	Ext = i<j ? File.Right(j-i-1) : "";

	return Ext;
}
/******************************************************************************/
//	名称：GetPath
//	功能：获取路径
//  参数：
//	返回：路径
/******************************************************************************/
CString CWindow::GetPath(const CString &File)
{
    int i,j=File.GetLength();
    CString Path;

	for(i=j-1; i>=0 && File.GetAt(i)!='\\'; --i);
	Path = (i<0 ) ? "" : File.Left(i);

	return Path;
}

///////////////////////////////////////////////////////////////////////////////
// End of Files
///////////////////////////////////////////////////////////////////////////////
