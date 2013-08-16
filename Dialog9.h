#if !defined(AFX_DIALOG9_H__4AEFC3BF_7EAE_441C_812A_37630EB7B777__INCLUDED_)
#define AFX_DIALOG9_H__4AEFC3BF_7EAE_441C_812A_37630EB7B777__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog9.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialog9 dialog

class CDialog9 : public CDialog
{
// Construction
public:
	CDialog9(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog9)
	enum { IDD = IDD_DIALOG9 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog9)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog9)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG9_H__4AEFC3BF_7EAE_441C_812A_37630EB7B777__INCLUDED_)
