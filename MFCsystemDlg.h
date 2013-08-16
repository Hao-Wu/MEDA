// MFCsystemDlg.h : header file
//

#if !defined(AFX_MFCSYSTEMDLG_H__E8F30D4C_FCD1_4CC9_BE26_706B7A74F92C__INCLUDED_)
#define AFX_MFCSYSTEMDLG_H__E8F30D4C_FCD1_4CC9_BE26_706B7A74F92C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMFCsystemDlg dialog

class CMFCsystemDlg : public CDialog
{
// Construction
public:
	CMFCsystemDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMFCsystemDlg)
	enum { IDD = IDD_MFCSYSTEM_DIALOG };
	CTabCtrl	m_tabctrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCsystemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMFCsystemDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCSYSTEMDLG_H__E8F30D4C_FCD1_4CC9_BE26_706B7A74F92C__INCLUDED_)
