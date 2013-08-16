#if !defined(AFX_DIALOG11_H__3AB75BC9_2DFB_4E27_8C28_6AC8DF488C03__INCLUDED_)
#define AFX_DIALOG11_H__3AB75BC9_2DFB_4E27_8C28_6AC8DF488C03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog11.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialog11 dialog

class CDialog11 : public CDialog
{
// Construction
public:
	CDialog11(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog11)
	enum { IDD = IDD_DIALOG11 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog11)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog11)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG11_H__3AB75BC9_2DFB_4E27_8C28_6AC8DF488C03__INCLUDED_)
