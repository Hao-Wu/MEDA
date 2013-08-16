#if !defined(AFX_DIALOG6_H__24EB15BE_175F_4F01_A66D_9D13119ECF00__INCLUDED_)
#define AFX_DIALOG6_H__24EB15BE_175F_4F01_A66D_9D13119ECF00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog6.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialog6 dialog

class CDialog6 : public CDialog
{
// Construction
public:
	CDialog6(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog6)
	enum { IDD = IDD_DIALOG6 };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog6)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog6)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG6_H__24EB15BE_175F_4F01_A66D_9D13119ECF00__INCLUDED_)
