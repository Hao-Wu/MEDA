#if !defined(AFX_DIALOG4_H__7B864F36_6430_4973_8905_74EA2B188944__INCLUDED_)
#define AFX_DIALOG4_H__7B864F36_6430_4973_8905_74EA2B188944__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog4.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialog4 dialog
#include"Dialog8.h"
#include"Dialog9.h"
#include"Dialog10.h"
#include"Dialog11.h"
#include"Dialog12.h"
#include"Dialog13.h"




class CDialog4 : public CDialog
{
// Construction
public:
	BOOL OnEraseBkgnd(CDC* pDC);

//	bool OnEraseBkgnd(CDC* pDC);

	CRect rectStaticClient;
	
	SCROLLINFO horz,vert;
	BOOL	flag, erase;
	int sourcex, sourcey,offsetx,offsety;
	int selecttree,selectcombo;


	CDialog4(CWnd* pParent = NULL);   // standard constructor

	bool  m_ReSizeFlag;
	int	m_OldWidth;
	int	m_OldHeight;



//		CBitmap m_bmp;
// Dialog Data
	//{{AFX_DATA(CDialog4)
	enum { IDD = IDD_DIALOG4 };
	CScrollBar	m_hbar;
	CScrollBar	m_vbar;
	CStatic	m_pic1;
	CEdit	m_medit1;
	CTreeCtrl	m_mtree;
	CString	m_Cedit1;
	CString	m_Cedit3;
	CString	m_Cedit4;
	CString	m_Cedit2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog4)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	CEdit * newedit[3] ;	
	CEdit * affine[4] ;
	CEdit *	vigenere[2];
	CEdit * editplayfair[4] ;
	CEdit * duowenzi[4] ;
	CEdit * des[16] ;
	CEdit * idea[5];
	CEdit * rsa[11];
	CEdit * rc4[3];
	CDC m_dcMem;            // 对话框兼容设备
	CButton   *desbutton[5];

///////////////////////caser





	CDialog8 dialog8;
	CDialog9 dialog9;
	CDialog10 dialog10;
	CDialog11 dialog11;
	CDialog12 dialog12;
	CDialog13 dialog13;




	char plain[BUF_SIZE];
	char cipher[BUF_SIZE];
	char key[1024];



///////////////////////////////////////////////
//////////////////////////////////////////////
	//////中间变量
	
	int i,j,k,t;
	char alpha[26];
	char key1[3];
	char key2[3];
	char affine_tmp[26];

//用以处理palyfair的密钥
	char key26[1024];


////////////////////////DES/////////////
	char strkey[8];
	bool keyblock[64];
	bool keyblock2[64];
	bool subkey[48];
	bool kl_tmp[28];
	bool kr_tmp[28];
	bool kl[28];
	bool kr[28];

	char plainblock[8];
	bool plain64[64];
	bool plain64_ip[64];

	bool plainleft32[32];
	bool plainright32[32];

	bool plain48[48];

	bool cipherleft32[32];
	bool cipherright32[32];
	bool cipher64[64];

	bool cipher16a[16];
	bool cipher16b[16];
	bool cipher16c[16];
	bool cipher16d[16];

		






///////////////////////////////////////////////
	HBITMAP m_hBmpOld;    // 老位图句柄
	HBITMAP m_hBmpNew;    // 来自文件的新位图句柄
   
	BITMAP m_bmInfo;        // 位图信息结构
	CPoint m_pt;            // 位图左上角位置
	CSize m_size;  
//////////////////////////////////////////////////////////////////////////////计数器
	//dai代表选择的哪一个算法

	int caseselect;
//	bool selectcase0;
    int playfaircountnext;
	int caesercount;
	int affinecount;
	int vigenerecount;
	int duowenzicount;
	int descount;
	bool desnext;
	
	int ideacount;
	int rsacount;
	int rc4count;
//	 int playfaircountformer;






	////////////////////////////////////////////////////////////////////////
	// Generated message map functions
	//{{AFX_MSG(CDialog4)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangingTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnChangeEdit4();
	//}}AFX_MSG
	//人工台添加


	afx_msg void Onjiaohuanxuanzebiao1();
	afx_msg void Onjiaohuanxuanzebiao2();


	afx_msg void Onzhihuanbiao();
	afx_msg void Onkuochonghe();


	afx_msg void Onzhihuanhe();
	afx_msg void Ontihuanhe();




	DECLARE_MESSAGE_MAP()



};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG4_H__7B864F36_6430_4973_8905_74EA2B188944__INCLUDED_)
