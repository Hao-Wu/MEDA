#if !defined(AFX_DIALOG1_H__D94F7C50_838E_492D_962C_AFC63F437F12__INCLUDED_)
#define AFX_DIALOG1_H__D94F7C50_838E_492D_962C_AFC63F437F12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialog1 dialog

class CDialog1 : public CDialog
{
// Construction
public:
		char m_FileName[MAX_PATH] ; 
//	bool OpenFile();
//	bool SaveDlg(char* FileName);
	CDialog1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog1)
	enum { IDD = IDD_DIALOG1 };
	CEdit	m_medit3;
	CComboBox	m_mcomb2;
	CComboBox	m_mcomb1;
	CString	m_Cedit1;
	CString	m_Cedit2;
	CString	m_Cedit3;
	CString	m_Cedit4;
	CString	m_Cedit5;
	CString	m_Cedit6;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog1)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton2();
	afx_msg void OnButton4();
	afx_msg void OnButton3();
	afx_msg void OnButton5();
	afx_msg void OnButton1();
	afx_msg void OnButton6();
	afx_msg void OnDoubleclickedButton1();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG1_H__D94F7C50_838E_492D_962C_AFC63F437F12__INCLUDED_)
