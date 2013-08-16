// FileInOut.cpp: implementation of the CFileInOut class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileInOut.h"
#include "Window.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CFileInOut::CFileInOut()
{
	fh_out = fh_in = 0;
}

CFileInOut::~CFileInOut()
{
	CloseFile();
}

///////////////////////////////////////////////////////////////////////////////
// CFileInOut Functions
///////////////////////////////////////////////////////////////////////////////
#define CHECK(x)			{if( !(x) ) return false;}
#define CHECK_MSG(x,msg)	{if( !(x) ){CWindow::ShowMessage(msg);return false;}}

/******************************************************************************/
//	名称：OpenFile
//	功能：打开输入输出文件
//  参数：
//	返回：打开成功返回true，否则返回false
/******************************************************************************/
bool CFileInOut::OpenFile(const char *OutFile,const char *InFile)
{
	// 输入文件!=输出文件
    CHECK_MSG( OutFile && InFile && strcmp(OutFile,InFile), "错误：无输入输出，或输入输出相同!" )
	CHECK_MSG( (fh_in=_lopen(InFile,OF_READ))!=-1, "错误：无法打开输入文件! " )

	if( CWindow::IsFileExist(OutFile) )
	{
		if( IDYES != MessageBox(GetActiveWindow(),"该文件已存在，是否覆盖? ",
			                   "提示",MB_YESNO | MB_ICONQUESTION) )
		{
			_lclose(fh_in);
			return false;
		}
	}
	if( (fh_out=_lcreat(OutFile,0)) == -1 )
	{
		_lclose(fh_in);
		CWindow::ShowMessage("错误：无法创建输出文件! ");
		return	false;
	}

	return	true;
}
/******************************************************************************/
//	名称：CloseFile()
//	功能：关闭输入输出文件
//  参数：
//	返回：
/******************************************************************************/
void CFileInOut::CloseFile()
{
	if( fh_in )
		_lclose(fh_in);
	if( fh_out )
		_lclose(fh_out);
}

/******************************************************************************/
//	名称：RunError
//	功能：错误处理
//  参数：
//	返回：
/******************************************************************************/
void CFileInOut::RunError(const char *OutFile)
{
	CloseFile();
	if(OutFile)
		DeleteFile(OutFile);
}

///////////////////////////////////////////////////////////////////////////////
// End of Files
///////////////////////////////////////////////////////////////////////////////

