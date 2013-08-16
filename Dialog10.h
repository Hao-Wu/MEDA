#if !defined(AFX_DIALOG10_H__B4BBBD3F_24FB_43BB_A648_34F476142C81__INCLUDED_)
#define AFX_DIALOG10_H__B4BBBD3F_24FB_43BB_A648_34F476142C81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog10.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialog10 dialog

class CDialog10 : public CDialog
{
// Construction
public:
	CDialog10(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog10)
	enum { IDD = IDD_DIALOG10 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog10)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog10)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG10_H__B4BBBD3F_24FB_43BB_A648_34F476142C81__INCLUDED_)
