#if !defined(AFX_DIALOG2_H__8D2538FD_8446_4A7A_8A94_D980F592BDCE__INCLUDED_)
#define AFX_DIALOG2_H__8D2538FD_8446_4A7A_8A94_D980F592BDCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialog2 dialog
#include "Des2.h"
class CDialog2 : public CDialog
{
// Construction
public:
	void BuildOutputFileName();
	void EnableFormatCtls(bool show);
	void EnableDefPathCtls(bool show);
	void EnableDesCtls(bool show);
	void EnableMcsCtls(bool show);
	CDialog2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog2)
	enum { IDD = IDD_DIALOG2 };
	CString	m_input;
	CString	m_output;
	CString	m_deskey;
	CString	m_deskey2;
	CString	m_defpath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	   bool		run_type;
	   	enum		{ENCRYPT,DECRYPT};
		bool        format,oldformat;
		enum        {DES,MCS};

		bool        deleptfile,delorgfile,delnote;

		CDes        des;
		CString     Str;
		bool        usedefpath;

	// Generated message map functions
	//{{AFX_MSG(CDialog2)
	afx_msg void OnButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowse();
	afx_msg void OnDelOrgFileCHECK();
	afx_msg void OnDelEptFileCHECK();
	afx_msg void OnDelNoteCHECK();
	afx_msg void OnRun();
	afx_msg void OnOutFolder();
	afx_msg void OnDefPathCHECK();
	afx_msg void OnDefFolder();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG2_H__8D2538FD_8446_4A7A_8A94_D980F592BDCE__INCLUDED_)
