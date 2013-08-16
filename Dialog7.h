#if !defined(AFX_DIALOG7_H__169A3971_271A_4014_8DAE_37086D621CD3__INCLUDED_)
#define AFX_DIALOG7_H__169A3971_271A_4014_8DAE_37086D621CD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog7.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialog7 dialog

class CDialog7 : public CDialog
{
// Construction
public:
	CDialog7(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog7)
	enum { IDD = IDD_DIALOG7 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog7)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog7)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG7_H__169A3971_271A_4014_8DAE_37086D621CD3__INCLUDED_)
