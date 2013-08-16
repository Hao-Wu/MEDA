#if !defined(AFX_DIALOG12_H__53A0F02F_2A0F_426F_8305_5190FDF49051__INCLUDED_)
#define AFX_DIALOG12_H__53A0F02F_2A0F_426F_8305_5190FDF49051__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog12.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialog12 dialog

class CDialog12 : public CDialog
{
// Construction
public:
	CDialog12(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog12)
	enum { IDD = IDD_DIALOG12 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog12)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog12)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG12_H__53A0F02F_2A0F_426F_8305_5190FDF49051__INCLUDED_)
