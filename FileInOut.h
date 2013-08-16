// FileInOut.h: interface for the CFileInOut class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEINOUT_H__581E2920_E13B_11D6_B0C2_00E04C391A51__INCLUDED_)
#define AFX_FILEINOUT_H__581E2920_E13B_11D6_B0C2_00E04C391A51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//////////////////////////////////////////////////////////////////////
//输入输出文件类(class CFileInOut)
class CFileInOut  
{
public:
	CFileInOut();
	virtual ~CFileInOut();
	bool    OpenFile(const char *OutFile,const char *InFile);//打开输入输出文件
	void    CloseFile();//关闭输入输出文件
	void    RunError(const char *OutFile);//错误处理

protected:
    HFILE	fh_out,fh_in;//输入输出文件句柄
};

#endif // !defined(AFX_FILEINOUT_H__581E2920_E13B_11D6_B0C2_00E04C391A51__INCLUDED_)
