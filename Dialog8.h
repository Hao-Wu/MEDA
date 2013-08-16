#if !defined(AFX_DIALOG8_H__1930D610_961E_4705_91D0_5804A2E3854B__INCLUDED_)
#define AFX_DIALOG8_H__1930D610_961E_4705_91D0_5804A2E3854B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog8.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialog8 dialog

class CDialog8 : public CDialog
{
// Construction
public:
	CDialog8(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog8)
	enum { IDD = IDD_DIALOG8 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog8)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog8)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG8_H__1930D610_961E_4705_91D0_5804A2E3854B__INCLUDED_)
