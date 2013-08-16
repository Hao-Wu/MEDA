// Window.h: interface for the CWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDOW_H__68BACE00_E104_11D6_B0C2_00E04C391A51__INCLUDED_)
#define AFX_WINDOW_H__68BACE00_E104_11D6_B0C2_00E04C391A51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//////////////////////////////////////////////////////////////////////
//Windows支持类(class CWindow)
class CWindow  
{
public:
	CWindow();
	virtual ~CWindow();

	void    ShowWaitCursor();//显示等待光标
	void    EndWaitCursor();//结束等待光标
	void    SetWindowCaption(char *Str,int v1=0,int v2=0,int v3=0);//设置窗口标题
	static  int  ShowMessage(const char *msg,const char *title="提示",
		                     UINT flage=MB_ICONINFORMATION);//显示消息框
	static  bool InputStr(CString &Str);//打开选择文件对话框，导入字符串
	static  bool OutputStr(CString &Str);//打开选择文件对话框，导出字符串
	static  bool GetFolder(CString &Folder);//目录选择对话框

	static  bool IsFileExist(const char *File);//检查文件是否存在
	static  bool GetStrFromFile(char *Str,const char *File);//从文件中读取字符串
	static  bool SaveStrToFile(const char *Str,const char *File);//保存字符串到文件中
    static  CString GetFileNameWithExt(const CString &File);//获取文件名(带扩展名)
	static  CString GetFileNameNoExt(const CString &File);//获取文件名(无扩展名)
    static  CString GetExtName(const CString &File);//获取扩展名
    static  CString GetPath(const CString &File);//获取路径

private:
	CWnd		wnd;//窗口类：指向当前活动窗口
	CString	    caption;//保存窗口标题
};

#endif // !defined(AFX_WINDOW_H__68BACE00_E104_11D6_B0C2_00E04C391A51__INCLUDED_)
