// Dialog4.cpp : implementation file
//

#include "StdAfx.h"
#include "MFCsystem.h"
#include "Dialog4.h"
#include "global.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog4 dialog


// Construction/Destruction
const static char IP_Table[64] = {
	58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17,  9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
};


// final permutation IP^-1 
const static char IPR_Table[64] = {
	40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
		38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
		36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
		34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41,  9, 49, 17, 57, 25
};

// 扩充盒:E盒
static const char E_Table[48] = {
	32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
		8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
		24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1
};

// 置换盒:P盒 
const static char P_Table[32] = {
	16, 7, 20, 21, 29, 12, 28, 17, 1,  15, 23, 26, 5,  18, 31, 10,
		2,  8, 24, 14, 32, 27, 3,  9,  19, 13, 30, 6,  22, 11, 4,  25
};

//pc1 ,64位密钥压缩变换为56位密钥
const static char PC1_Table[56] = {	
    4, 12, 20, 28, 5, 13, 21, 29, 37, 45, 53, 61, 6, 14,
		57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
		10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
		63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
};

//pc2,56位密钥压缩变换为48为密钥Ki
const static char PC2_Table[48] = {
	
	23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
		41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
		44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32,
		14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10
};

// pc1在各轮次左移的位数
static const char LOOP_Table[16] = 
{
	1 , 1 , 2 , 2 , 2 , 2 , 2 , 2 ,
		1 , 2 , 2 , 2 , 2 , 2 , 2 , 1
} ;


// 替换盒:S盒(共8个) 
const static char S_Box[8][4][16] = {
	// S1 
	14,	 4,	13,	 1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
		0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
		4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
		15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13,
		// S2 
		15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
		3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
		0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
		13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9,
		// S3 
		10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
		13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
		13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
		1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12,
		// S4 
		7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
		13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
		10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
		3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14,
		// S5 
		2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
		14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
		4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
		11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3,
		// S6 
		12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
		10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
		9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
		4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13,
		// S7 
		4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
		13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
		1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
		6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12,
		// S8 
		13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
		1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
		7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
		2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
};



//	CBitmap m_bmp;
CDialog4::CDialog4(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog4::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog4)
	m_Cedit1 = _T("");
	m_Cedit3 = _T("");
	m_Cedit4 = _T("");
	m_Cedit2 = _T("");
	//}}AFX_DATA_INIT
}


void CDialog4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog4)
	DDX_Control(pDX, IDC_HBAR, m_hbar);
	DDX_Control(pDX, IDC_VBAR, m_vbar);
	DDX_Control(pDX, IDC_PIC, m_pic1);
	DDX_Control(pDX, IDC_EDIT1, m_medit1);
	DDX_Control(pDX, IDC_TREE1, m_mtree);
	DDX_Text(pDX, IDC_EDIT1, m_Cedit1);
	DDX_Text(pDX, IDC_EDIT3, m_Cedit3);
	DDX_Text(pDX, IDC_EDIT4, m_Cedit4);
	DDX_Text(pDX, IDC_EDIT2, m_Cedit2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog4, CDialog)
	//{{AFX_MSG_MAP(CDialog4)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnSelchangedTree1)
	ON_NOTIFY(TVN_SELCHANGING, IDC_TREE1, OnSelchangingTree1)
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeEdit4)
	//}}AFX_MSG_MAP



	
	ON_BN_CLICKED(IDC_BTNCHANGESELECT1, Onjiaohuanxuanzebiao1)
	ON_BN_CLICKED(IDC_BTNCHANGESELECT2, Onjiaohuanxuanzebiao2)


	ON_BN_CLICKED(IDC_BTNZHIHUANBIAO, Onzhihuanbiao)
	ON_BN_CLICKED(IDC_BTNKUOCHONGHE, Onkuochonghe)
	ON_BN_CLICKED(IDC_BTNZHIHUANHE, Onzhihuanhe)
	ON_BN_CLICKED(IDC_BTNTIHUANHE, Ontihuanhe)

//	ON_BN_CLICKED(ID_MYBUT3, OnMybut3)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog4 message handlers

BOOL CDialog4::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here


	

//	VERIFY(m_bmp.LoadBitmap(IDB_BITMAP2));
//	m_pic1.SetBitmap(m_bmp);


	//创建树形结构，及其节点////////////////////////////////////////////////////////////???????????????????????????????


	CString userTreeHeader[4]={"经典加密法","流加密法","块加密法","公钥加密法"};
	HTREEITEM userItem[4];
	for(int i=0;i<4;i++)
	{
		userItem[i]=m_mtree.InsertItem(userTreeHeader[i],0,0,TVI_ROOT);
		m_mtree.SetItemData(userItem[i],(DWORD(i+11)));
	}

	HTREEITEM userSpecifics=m_mtree.InsertItem("凯撒加密法",2,2,userItem[0]);
	m_mtree.SetItemData(userSpecifics,(DWORD)0);



	userSpecifics=m_mtree.InsertItem("多文字加密法",3,3,userItem[0]);
	m_mtree.SetItemData(userSpecifics,(DWORD)1);




	userSpecifics=m_mtree.InsertItem("Vigenere加密法",3,3,userItem[0]);
	m_mtree.SetItemData(userSpecifics,(DWORD)2);

	userSpecifics=m_mtree.InsertItem("Playfair加密法",3,3,userItem[0]);
	m_mtree.SetItemData(userSpecifics,(DWORD)3);

	userSpecifics=m_mtree.InsertItem("置换加密法",3,3,userItem[0]);
	m_mtree.SetItemData(userSpecifics,(DWORD)4);


	userSpecifics=m_mtree.InsertItem("affine",3,3,userItem[0]);
	m_mtree.SetItemData(userSpecifics,(DWORD)5);


	userSpecifics=m_mtree.InsertItem("RC4",3,3,userItem[1]);
	m_mtree.SetItemData(userSpecifics,(DWORD)6);


	userSpecifics=m_mtree.InsertItem("DES",3,3,userItem[2]);
	m_mtree.SetItemData(userSpecifics,(DWORD)7);

		userSpecifics=m_mtree.InsertItem("IDEA",3,3,userItem[2]);
	m_mtree.SetItemData(userSpecifics,(DWORD)8);

		userSpecifics=m_mtree.InsertItem("RSA",3,3,userItem[3]);
	m_mtree.SetItemData(userSpecifics,(DWORD)9);


		//////////////////////////////////////////////////////////////?????????????????????????????????????



	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC( &dc );

	//滚动条的隐藏////////////////////////////////////////////////////////////???????????????????????????????
	m_vbar.ShowWindow(false);//隐藏垂直滚动条


	//滚动条的隐藏////////////////////////////////////////////////////////////???????????????????????????????



	//l两个静态按钮的隐藏////////////////////////////////////////////////////////////???????????????????????????????
GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);//就可以隐藏，为SW_SHOW可以是显示。IDC_BUTTON4
GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);
	//l两个静态按钮的隐藏////////////////////////////////////////////////////////////???????????????????????????????

	m_hbar.ShowWindow(false);





	des[0] = new CEdit;
	des[1]=new CEdit;
	des[2]=new CEdit;
	des[3]=new CEdit;
	des[4]=new CEdit;
	des[5]=new CEdit;
	des[6]=new CEdit;
	des[7]=new CEdit;
	des[8]=new CEdit;
	des[9]=new CEdit;
	des[10]=new CEdit;
	des[11]=new CEdit;
	des[12]=new CEdit;
	des[13]=new CEdit;
	des[14]=new CEdit;


	
	desbutton[0]=new CButton;
	desbutton[1]=new CButton;
	desbutton[2]=new CButton;
	desbutton[3]=new CButton;
	desbutton[4]=new CButton;


		desbutton[0]->Create( "交换选择列表 1", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(570,194,669,219), this, IDC_BTNCHANGESELECT1 );
		desbutton[1]->Create( "交换选择列表 2", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(561,391,677,415), this, IDC_BTNCHANGESELECT2 );
					
		desbutton[2]->Create( "置换表", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(595,84,659,113), this, IDC_BTNZHIHUANBIAO );
		desbutton[3]->Create( "扩充盒 E盒", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(710,231,784,253), this, IDC_BTNKUOCHONGHE );
					//desbutton[4]->Create( "替换盒 S盒", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(674,370,817,394), this, IDC_BTNTIHUANHE );

		desbutton[4]->Create( "置换盒 P盒", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(675,420,819,442), this, IDC_BTNZHIHUANHE );

		desbutton[0]->ShowWindow (false);
		desbutton[1]->ShowWindow (false);
		desbutton[2]->ShowWindow (false);
		desbutton[3]->ShowWindow (false);
		desbutton[4]->ShowWindow (false);

		rsa[0]=new CEdit();
		rsa[1]=new CEdit();
		rsa[2]=new CEdit();
		rsa[3]=new CEdit();
		rsa[4]=new CEdit();
		rsa[5]=new CEdit();
		rsa[6]=new CEdit();
		rsa[7]=new CEdit();
		rsa[8]=new CEdit();
		rsa[9]=new CEdit();
		rsa[10]=new CEdit();
		
	rsa[0]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(546,137,770,160) , this , IDC_EDIT2) ;
	
	

	rsa[1]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(546,165,770,186) , this , IDC_EDIT2) ;

	
	rsa[2]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(546,195,770,218) , this , IDC_EDIT2) ;


	
	rsa[3]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(546,246,770,266) , this , IDC_EDIT2) ;


	
	rsa[4]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(546,326,770,348) , this , IDC_EDIT2) ;

		rsa[5]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER,  CRect(538,107,763,127) , this , IDC_EDIT2) ;
	
	

	rsa[6]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(538,134,763,155) , this , IDC_EDIT2) ;

	
	rsa[7]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(540,265,765,288) , this , IDC_EDIT2) ;


	
	rsa[8]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(540,387,766,408), this , IDC_EDIT2) ;


	
	rsa[9]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER,  CRect(540,411,768,431), this , IDC_EDIT2) ;

	rsa[10]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(540,494,766,518) , this , IDC_EDIT2) ;





	rsa[0]->ShowWindow (false);
	rsa[1]->ShowWindow (false);
	rsa[2]->ShowWindow (false);
	rsa[3]->ShowWindow (false);
	rsa[4]->ShowWindow (false);

	rsa[5]->ShowWindow (false);
	rsa[6]->ShowWindow (false);
	rsa[7]->ShowWindow (false);
	rsa[8]->ShowWindow (false);
	rsa[9]->ShowWindow (false);

	rsa[10]->ShowWindow (false);

















	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog4::OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	HTREEITEM SelItem;
	SelItem =m_mtree.GetSelectedItem();   //获取选中的子项
	DWORD m;
	m=m_mtree.GetItemData(SelItem);  //度子项的值

		//l选择每个节点后的结果////////////////////////////////////////////////////////////???????????????????????????????
	switch(m)
	{
	case 0:
			m_Cedit3=m_mtree.GetItemText(SelItem);
			m_Cedit3=m_Cedit3+" 演示流程";
		
			MessageBox(m_Cedit3);


			selecttree=0;


			UpdateData(false);
			break;
	case 1:
		m_Cedit3=m_mtree.GetItemText(SelItem);
		m_Cedit3=m_Cedit3+"	演示流程";
		MessageBox(m_Cedit3);


			selecttree=1;



		UpdateData(false);
		break;
	case 2:
		m_Cedit3=m_mtree.GetItemText(SelItem);
		m_Cedit3=m_Cedit3+"	演示流程";
		MessageBox(m_Cedit3);




			selecttree=2;





		UpdateData(false);
		break;
	case 3:
		m_Cedit3=m_mtree.GetItemText(SelItem);
		m_Cedit3=m_Cedit3+"	演示流程";
		MessageBox(m_Cedit3);




			selecttree=3;

		UpdateData(false);
		break;
	case 4:
		m_Cedit3=m_mtree.GetItemText(SelItem);
		m_Cedit3=m_Cedit3+"	演示流程";
		MessageBox(m_Cedit3);
		
			selecttree=4;
		UpdateData(false);
		break;
	case 5:
		m_Cedit3=m_mtree.GetItemText(SelItem);
		m_Cedit3=m_Cedit3+"	演示流程";
		MessageBox(m_Cedit3);
		UpdateData(false);
		
			selecttree=5;
		break;
	case 6:
		m_Cedit3=m_mtree.GetItemText(SelItem);
		m_Cedit3=m_Cedit3+"	演示流程";
		MessageBox(m_Cedit3);
		UpdateData(false);
		
			selecttree=6;
		break;
	case 7:
		m_Cedit3=m_mtree.GetItemText(SelItem);
		m_Cedit3=m_Cedit3+"	演示流程";
		MessageBox(m_Cedit3);
		UpdateData(false);
		
			selecttree=7;
		break;
	case 8:
		m_Cedit3=m_mtree.GetItemText(SelItem);
		m_Cedit3=m_Cedit3+"	演示流程";
		MessageBox(m_Cedit3);
		UpdateData(false);
		
			selecttree=8;
		break;

	case 9:
			m_Cedit3=m_mtree.GetItemText(SelItem);
			m_Cedit3=m_Cedit3+"	演示流程";
			MessageBox(m_Cedit3);
			UpdateData(false);
			
			selecttree=9;
			break;

	}
//l选择每个节点后的结果////////////////////////////////////////////////////////////???????????????????????????????


	*pResult = 0;
}

void CDialog4::OnSelchangingTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CDialog4::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
//	 CPaintDC dc(this);
//	 CPaintDC dc(this);
	  dc.BitBlt(offsetx,offsety,m_size.cx,m_size.cy, 
                   &m_dcMem, sourcex, sourcey,SRCCOPY);
	  erase=false;//恢复重画背景
	  CDialog::OnPaint();
	 // CDialog::OnPaint();
	// Do not call CDialog::OnPaint() for painting messages
}

void CDialog4::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	switch (nSBCode)
	{
	case SB_TOP:
	sourcey = 0;
	break;
	case SB_BOTTOM:
	sourcey = INT_MAX;
	break;
	case SB_THUMBTRACK:
	sourcey = nPos;
	break;
	}
	m_vbar.SetScrollPos(sourcey);
	erase=true; //防止重画背景
	InvalidateRect(&rectStaticClient);


	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CDialog4::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
		switch (nSBCode)
	{
	case SB_TOP:
	sourcex = 0;
	break;
	case SB_BOTTOM:
	sourcex = INT_MAX;
	break;
	case SB_THUMBTRACK:
	sourcex= nPos;
	break;
	}	
	m_hbar.SetScrollPos(sourcex);
	erase=true;//防止重画背景
	InvalidateRect(&rectStaticClient);


	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}




BOOL CDialog4::OnEraseBkgnd(CDC *pDC)
{
if(erase)
		return false;
	else
	return CDialog::OnEraseBkgnd(pDC);
}




//selectcase0=false;

//affine//
char key1_temp[3]={'\0'};

	
void CDialog4::OnButton1() 
{
	// TODO: Add your control notification handler code here
	



				UpdateData(true);

				if(m_Cedit4!=""){
					MessageBox("此为密文显示区,输入文本无效!");
					m_Cedit4="";
				UpdateData(false);




	}

	
			UpdateData(true);

			//重设每一个算法  下一步的计数器///////////////////////////////////////
			playfaircountnext=0;
			caesercount=0;
			affinecount=0;
			vigenerecount=0;
			duowenzicount=0;
			descount=0;
			ideacount=0;
			rsacount=0;
			rc4count=0;
		//	desnext=false;


			// playfaircountformer=5;



	memset(plain,0,BUF_SIZE);
	memset(cipher,0,BUF_SIZE);
	memset(key,0,1024);

	memset(alpha,0,26);
	
	












		 ///////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////清空所有的动态空间







////////////////////////////////////////////////////////////////////


	switch(selecttree){

		case 0:

					if (m_Cedit1=="" || m_Cedit2==""  )
					{
						MessageBox("请输入明文和密钥!     ","提示");
						return;
					}
					if (atoi(m_Cedit2)==0)
					{
						MessageBox("密钥为正整数!          ","提示");
						
						return;
					}



													switch(caseselect){
													case 1:

														newedit[0]->ShowWindow (false);
														newedit[1]->ShowWindow (false);
														newedit[2]->ShowWindow (false);
															break;

													case 2:
														duowenzi[0]->ShowWindow (false);
														duowenzi[1]->ShowWindow (false);
														duowenzi[2]->ShowWindow (false);
														duowenzi[3]->ShowWindow (false);





														break;
													case 3:
														vigenere[0]->ShowWindow (false);
														vigenere[1]->ShowWindow (false);



														break;
													case 4:
														editplayfair[0]->ShowWindow (false);
														editplayfair[1]->ShowWindow (false);
														editplayfair[2]->ShowWindow (false);


														break;
													case 5:



														break;
													case 6:
														affine[0]->ShowWindow (false);
														affine[1]->ShowWindow (false);
														affine[2]->ShowWindow (false);
														affine[3]->ShowWindow (false);




														break;

													case 7:
														rc4[0]->ShowWindow (false);
														rc4[1]->ShowWindow (false);
														rc4[2]->ShowWindow (false);



														break;

													case 8:
														des[0]->ShowWindow (false);
														des[1]->ShowWindow (false);
														des[2]->ShowWindow (false);
														des[3]->ShowWindow (false);
														des[4]->ShowWindow (false);
														des[5]->ShowWindow (false);
														desbutton[0]->ShowWindow (false);
														desbutton[1]->ShowWindow (false);


														if(desnext==true){
														des[6]->ShowWindow (false);
														des[7]->ShowWindow (false);
														des[8]->ShowWindow (false);
														des[9]->ShowWindow (false);
														
														des[10]->ShowWindow (false);
														des[11]->ShowWindow (false);
														des[12]->ShowWindow (false);
														des[13]->ShowWindow (false);
														des[14]->ShowWindow (false);
														desbutton[2]->ShowWindow (false);
														desbutton[3]->ShowWindow (false);
														//desbutton[4]->ShowWindow (false);
														desbutton[4]->ShowWindow (false);
														}
																		




														break;

													case 9:
														idea[0]->ShowWindow (false);
														idea[1]->ShowWindow (false);
														idea[2]->ShowWindow (false);
														idea[3]->ShowWindow (false);
														idea[4]->ShowWindow (false);



														break;

													case 10:
														rsa[0]->ShowWindow (false);
														rsa[1]->ShowWindow (false);
														rsa[2]->ShowWindow (false);
														rsa[3]->ShowWindow (false);
														rsa[4]->ShowWindow (false);
														rsa[5]->ShowWindow (false);
														rsa[6]->ShowWindow (false);
														rsa[7]->ShowWindow (false);
														rsa[8]->ShowWindow (false);
														rsa[9]->ShowWindow (false);
														rsa[10]->ShowWindow (false);




														break;

													case 11:



														break;

											
													}







											m_hBmpNew =	 (HBITMAP) LoadImage(NULL, "Picture\\caeser.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
											if( m_hBmpNew == NULL )
											{
											 AfxMessageBox("Load Image Failed");
											}
											else
											{
											  m_pic1.GetClientRect( &rectStaticClient );//得到控件的客户区
											  rectStaticClient.NormalizeRect();
											  m_size.cx=rectStaticClient.Size().cx;
											  m_size.cy=rectStaticClient.Size().cy;
											  m_size.cx = rectStaticClient.Width();    // zero based
											  m_size.cy = rectStaticClient.Height();    // zero based
											  m_pic1.ClientToScreen( &rectStaticClient );//转换到屏幕坐标
             								  ScreenToClient( &rectStaticClient);//控件屏幕坐标转换到相对于对话框的客户坐标
											  m_pt.x = rectStaticClient.left;
											  m_pt.y = rectStaticClient.top;
											  GetObject( m_hBmpNew , sizeof(BITMAP), &m_bmInfo );
											  VERIFY(m_hBmpOld = (HBITMAP)SelectObject(m_dcMem, m_hBmpNew )  );
											  offsetx= m_pt.x;
											  offsety=m_pt.y;

											  m_vbar.MoveWindow(offsetx+m_size.cx,offsety,18,m_size.cy);
											  m_hbar.MoveWindow(offsetx,offsety+m_size.cy,m_size.cx,18);
											  horz.cbSize = sizeof(SCROLLINFO);
											  horz.fMask = SIF_ALL;
											  horz.nMin = 0;
											  horz.nMax = m_bmInfo.bmWidth-m_size.cx;
											  horz.nPage =0;
											  horz.nPos = 0;
											  horz.nTrackPos=0;
											  if(m_bmInfo.bmWidth<=m_size.cx)
											  {
												if((m_size.cx-m_bmInfo.bmWidth)==0)
													offsetx= m_pt.x;
												else
													offsetx= m_pt.x+((m_size.cx-m_bmInfo.bmWidth)/2);
												m_vbar.MoveWindow(offsetx+m_bmInfo.bmWidth,offsety,18,m_size.cy);
												m_hbar.ShowWindow(false);
											  }
											 else
											  m_hbar.ShowWindow(true);
											 m_hbar.SetScrollInfo(&horz);


											 vert.cbSize = sizeof(SCROLLINFO);
											 vert.fMask = SIF_ALL;
											 vert.nMin = 0;
											 vert.nMax = m_bmInfo.bmHeight-(m_size.cy);
											 vert.nPage = 0;
											 vert.nTrackPos=0;
											 if(m_bmInfo.bmHeight<=m_size.cy)
											 {
												if((m_size.cy-m_bmInfo.bmHeight)==0)
													offsety= m_pt.y;
												else
													offsety= m_pt.y+((m_size.cy-m_bmInfo.bmHeight)/2);
												m_hbar.MoveWindow(offsetx,offsety+m_bmInfo.bmHeight,m_size.cx,18);
												m_vbar.ShowWindow(false);
											 }
											 else
											  m_vbar.ShowWindow(true);
											m_vbar.SetScrollInfo(&vert);


											InvalidateRect(&rectStaticClient);
											}
											//desnext=false





											newedit[0] = new CEdit() ;
											newedit[1] = new CEdit() ;
											newedit[2] = new CEdit() ;
										//	newedit[3] = new CEdit() ;
											newedit[0]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER|ES_MULTILINE|ES_AUTOVSCROLL, CRect(680,345,845,375) , this , IDC_EDIT2) ;
											
											newedit[1]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER|ES_MULTILINE|ES_AUTOVSCROLL, CRect(540,111,572,150) , this , IDC_EDIT2) ;
										//	newedit[0]->SetLimitText (m_medit1.GetLimitText ());

											
											newedit[2]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER|ES_MULTILINE|ES_AUTOVSCROLL, CRect(540,199,570,522) , this , IDC_EDIT2) ;

											GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_SHOW);//就可以隐藏，为SW_SHOW可以是显示。

											GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_SHOW);




											strncpy(plain , m_Cedit1.GetBuffer(m_Cedit1.GetLength()) , m_Cedit1.GetLength()) ;	
											strncpy(key , m_Cedit2.GetBuffer(m_Cedit2.GetLength()) , m_Cedit2.GetLength()) ;
											 Caeser(plain,cipher,atoi(key) );
											 strcpy(alpha,"abcdefghijklmnopqrstuvwxyz");
	 //alpha[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};


											 



											 for(i=0;i<26;i ++ )
											 {
												if ( alpha[i]+atoi(key) <='z')
												 alpha[i]=alpha[i]+atoi(key);
												else
													alpha[i]=(alpha[i]+atoi(key)-'a')%26+'a'+1;
											 }


											caseselect=1;

									break;
		case 1:


							
							if (m_Cedit1=="" || m_Cedit2==""  )
							{
								MessageBox("请输入明文和密钥!  ","提示");
								return;
							}
							
							if ( m_Cedit2.GetLength()!=5)
							{
								MessageBox("密钥长度为5!            ","提示");
								return;
							}	


							switch(caseselect){
									case 1:

										newedit[0]->ShowWindow (false);
										newedit[1]->ShowWindow (false);
										newedit[2]->ShowWindow (false);
											break;

									case 2:
										duowenzi[0]->ShowWindow (false);
										duowenzi[1]->ShowWindow (false);
										duowenzi[2]->ShowWindow (false);
										duowenzi[3]->ShowWindow (false);





										break;
									case 3:
										vigenere[0]->ShowWindow (false);
										vigenere[1]->ShowWindow (false);



										break;
									case 4:
										editplayfair[0]->ShowWindow (false);
										editplayfair[1]->ShowWindow (false);
										editplayfair[2]->ShowWindow (false);


										break;
									case 5:



										break;
									case 6:
										affine[0]->ShowWindow (false);
										affine[1]->ShowWindow (false);
										affine[2]->ShowWindow (false);
										affine[3]->ShowWindow (false);




										break;

									case 7:
										rc4[0]->ShowWindow (false);
										rc4[1]->ShowWindow (false);
										rc4[2]->ShowWindow (false);




										break;

									case 8:
										des[0]->ShowWindow (false);
										des[1]->ShowWindow (false);
										des[2]->ShowWindow (false);
										des[3]->ShowWindow (false);
										des[4]->ShowWindow (false);
										des[5]->ShowWindow (false);
										desbutton[0]->ShowWindow (false);
										desbutton[1]->ShowWindow (false);
										
														if(desnext==true){
														des[6]->ShowWindow (false);
														des[7]->ShowWindow (false);
														des[8]->ShowWindow (false);
														des[9]->ShowWindow (false);
														
														des[10]->ShowWindow (false);
														des[11]->ShowWindow (false);
														des[12]->ShowWindow (false);
														des[13]->ShowWindow (false);
														des[14]->ShowWindow (false);
														desbutton[2]->ShowWindow (false);
														desbutton[3]->ShowWindow (false);
														//desbutton[4]->ShowWindow (false);
														desbutton[4]->ShowWindow (false);
														}
					


										break;

									case 9:
										idea[0]->ShowWindow (false);
														idea[1]->ShowWindow (false);
														idea[2]->ShowWindow (false);
														idea[3]->ShowWindow (false);
														idea[4]->ShowWindow (false);



										break;

									case 10:
									rsa[0]->ShowWindow (false);
														rsa[1]->ShowWindow (false);
														rsa[2]->ShowWindow (false);
														rsa[3]->ShowWindow (false);
														rsa[4]->ShowWindow (false);
														rsa[5]->ShowWindow (false);
														rsa[6]->ShowWindow (false);
														rsa[7]->ShowWindow (false);
														rsa[8]->ShowWindow (false);
														rsa[9]->ShowWindow (false);
														rsa[10]->ShowWindow (false);



										break;

									case 11:



										break;

							
									}



									m_hBmpNew =	 (HBITMAP) LoadImage(NULL, "Picture\\duowenzi.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
									if( m_hBmpNew == NULL )
									{
									 AfxMessageBox("Load Image Failed");
									}
									else
									{
									  m_pic1.GetClientRect( &rectStaticClient );//得到控件的客户区
									  rectStaticClient.NormalizeRect();
									  m_size.cx=rectStaticClient.Size().cx;
									  m_size.cy=rectStaticClient.Size().cy;
									  m_size.cx = rectStaticClient.Width();    // zero based
									  m_size.cy = rectStaticClient.Height();    // zero based
									  m_pic1.ClientToScreen( &rectStaticClient );//转换到屏幕坐标
             						  ScreenToClient( &rectStaticClient);//控件屏幕坐标转换到相对于对话框的客户坐标
									  m_pt.x = rectStaticClient.left;
									  m_pt.y = rectStaticClient.top;
									  GetObject( m_hBmpNew , sizeof(BITMAP), &m_bmInfo );
									  VERIFY(m_hBmpOld = (HBITMAP)SelectObject(m_dcMem, m_hBmpNew )  );
									  offsetx= m_pt.x;
									  offsety=m_pt.y;

									  m_vbar.MoveWindow(offsetx+m_size.cx,offsety,18,m_size.cy);
									  m_hbar.MoveWindow(offsetx,offsety+m_size.cy,m_size.cx,18);
									  horz.cbSize = sizeof(SCROLLINFO);
									  horz.fMask = SIF_ALL;
									  horz.nMin = 0;
									  horz.nMax = m_bmInfo.bmWidth-m_size.cx;
									  horz.nPage =0;
									  horz.nPos = 0;
									  horz.nTrackPos=0;
									  if(m_bmInfo.bmWidth<=m_size.cx)
									  {
										if((m_size.cx-m_bmInfo.bmWidth)==0)
											offsetx= m_pt.x;
										else
											offsetx= m_pt.x+((m_size.cx-m_bmInfo.bmWidth)/2);
										m_vbar.MoveWindow(offsetx+m_bmInfo.bmWidth,offsety,18,m_size.cy);
										m_hbar.ShowWindow(false);
									  }
									 else
									  m_hbar.ShowWindow(true);
									 m_hbar.SetScrollInfo(&horz);
									 vert.cbSize = sizeof(SCROLLINFO);
									 vert.fMask = SIF_ALL;
									 vert.nMin = 0;
									 vert.nMax = m_bmInfo.bmHeight-(m_size.cy);
									 vert.nPage = 0;
									 vert.nTrackPos=0;
									 if(m_bmInfo.bmHeight<=m_size.cy)
									 {
										if((m_size.cy-m_bmInfo.bmHeight)==0)
											offsety= m_pt.y;
										else
											offsety= m_pt.y+((m_size.cy-m_bmInfo.bmHeight)/2);
										m_hbar.MoveWindow(offsetx,offsety+m_bmInfo.bmHeight,m_size.cx,18);
										m_vbar.ShowWindow(false);
									 }
									 else
									  m_vbar.ShowWindow(true);
									m_vbar.SetScrollInfo(&vert);


									InvalidateRect(&rectStaticClient);
									}



												
									duowenzi[0] = new CEdit() ;
									duowenzi[1] = new CEdit() ;
									duowenzi[2] = new CEdit() ;
									duowenzi[3] = new CEdit() ;

									duowenzi[0]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(598,65,832,108) , this , IDC_EDIT2) ;
							

									duowenzi[1]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(418,137,573,168) , this , IDC_EDIT2) ;
									duowenzi[2]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(634,246,672,398) , this , IDC_EDIT2) ;
									duowenzi[3]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(670,214,797,248) , this , IDC_EDIT2) ;
								


										
									GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_SHOW);//就可以隐藏，为SW_SHOW可以是显示。

									GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_SHOW);

									caseselect=2;


									strncpy(plain , m_Cedit1.GetBuffer(m_Cedit1.GetLength()) , m_Cedit1.GetLength()) ;	
									strncpy(key , m_Cedit2.GetBuffer(m_Cedit2.GetLength()) , m_Cedit2.GetLength()) ;
									

									strncpy(keystream , m_Cedit2.GetBuffer(m_Cedit2.GetLength()) , m_Cedit2.GetLength()) ;
									encrypt(plain,key,cipher);




				break;
		



case 2 :

	
					if (m_Cedit1=="" || m_Cedit2==""  )
					{
						MessageBox("请输入明文和密钥!","提示");
						return;
					}


							switch(caseselect){
											case 1:

												newedit[0]->ShowWindow (false);
												newedit[1]->ShowWindow (false);
												newedit[2]->ShowWindow (false);
													break;

											case 2:
											duowenzi[0]->ShowWindow (false);
											duowenzi[1]->ShowWindow (false);
											duowenzi[2]->ShowWindow (false);
											duowenzi[3]->ShowWindow (false);




												break;
											case 3:
											vigenere[0]->ShowWindow (false);
											vigenere[1]->ShowWindow (false);




												break;
											case 4:
												editplayfair[0]->ShowWindow (false);
												editplayfair[1]->ShowWindow (false);
												editplayfair[2]->ShowWindow (false);


												break;
											case 5:



												break;
											case 6:
												affine[0]->ShowWindow (false);
												affine[1]->ShowWindow (false);
												affine[2]->ShowWindow (false);
												affine[3]->ShowWindow (false);




												break;

											case 7:
												rc4[0]->ShowWindow (false);
												rc4[1]->ShowWindow (false);
												rc4[2]->ShowWindow (false);



												break;

											case 8:
												des[0]->ShowWindow (false);
											des[1]->ShowWindow (false);
											des[2]->ShowWindow (false);
											des[3]->ShowWindow (false);
											des[4]->ShowWindow (false);
											des[5]->ShowWindow (false);
											desbutton[0]->ShowWindow (false);
											desbutton[1]->ShowWindow (false);
											
														if(desnext==true){
														des[6]->ShowWindow (false);
														des[7]->ShowWindow (false);
														des[8]->ShowWindow (false);
														des[9]->ShowWindow (false);
														
														des[10]->ShowWindow (false);
														des[11]->ShowWindow (false);
														des[12]->ShowWindow (false);
														des[13]->ShowWindow (false);
														des[14]->ShowWindow (false);
														desbutton[2]->ShowWindow (false);
														desbutton[3]->ShowWindow (false);
														//desbutton[4]->ShowWindow (false);
														desbutton[4]->ShowWindow (false);
														}
					


												break;

											case 9:
												idea[0]->ShowWindow (false);
														idea[1]->ShowWindow (false);
														idea[2]->ShowWindow (false);
														idea[3]->ShowWindow (false);
														idea[4]->ShowWindow (false);



												break;

											case 10:
											rsa[0]->ShowWindow (false);
														rsa[1]->ShowWindow (false);
														rsa[2]->ShowWindow (false);
														rsa[3]->ShowWindow (false);
														rsa[4]->ShowWindow (false);
														rsa[5]->ShowWindow (false);
														rsa[6]->ShowWindow (false);
														rsa[7]->ShowWindow (false);
														rsa[8]->ShowWindow (false);
														rsa[9]->ShowWindow (false);
														rsa[10]->ShowWindow (false);
												break;

											case 11:



												break;

									
											}





										m_hBmpNew =	 (HBITMAP) LoadImage(NULL, "Picture\\vigenere.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
										if( m_hBmpNew == NULL )
										{
										 AfxMessageBox("Load Image Failed");
										}
										else
										{
										  m_pic1.GetClientRect( &rectStaticClient );//得到控件的客户区
										  rectStaticClient.NormalizeRect();
										  m_size.cx=rectStaticClient.Size().cx;
										  m_size.cy=rectStaticClient.Size().cy;
										  m_size.cx = rectStaticClient.Width();    // zero based
										  m_size.cy = rectStaticClient.Height();    // zero based
										  m_pic1.ClientToScreen( &rectStaticClient );//转换到屏幕坐标
             							  ScreenToClient( &rectStaticClient);//控件屏幕坐标转换到相对于对话框的客户坐标
										  m_pt.x = rectStaticClient.left;
										  m_pt.y = rectStaticClient.top;
										  GetObject( m_hBmpNew , sizeof(BITMAP), &m_bmInfo );
										  VERIFY(m_hBmpOld = (HBITMAP)SelectObject(m_dcMem, m_hBmpNew )  );
										  offsetx= m_pt.x;
										  offsety=m_pt.y;

										  m_vbar.MoveWindow(offsetx+m_size.cx,offsety,18,m_size.cy);
										  m_hbar.MoveWindow(offsetx,offsety+m_size.cy,m_size.cx,18);
										  horz.cbSize = sizeof(SCROLLINFO);
										  horz.fMask = SIF_ALL;
										  horz.nMin = 0;
										  horz.nMax = m_bmInfo.bmWidth-m_size.cx;
										  horz.nPage =0;
										  horz.nPos = 0;
										  horz.nTrackPos=0;
										  if(m_bmInfo.bmWidth<=m_size.cx)
										  {
											if((m_size.cx-m_bmInfo.bmWidth)==0)
												offsetx= m_pt.x;
											else
												offsetx= m_pt.x+((m_size.cx-m_bmInfo.bmWidth)/2);
											m_vbar.MoveWindow(offsetx+m_bmInfo.bmWidth,offsety,18,m_size.cy);
											m_hbar.ShowWindow(false);
										  }
										 else
										  m_hbar.ShowWindow(true);
										 m_hbar.SetScrollInfo(&horz);
										 vert.cbSize = sizeof(SCROLLINFO);
										 vert.fMask = SIF_ALL;
										 vert.nMin = 0;
										 vert.nMax = m_bmInfo.bmHeight-(m_size.cy);
										 vert.nPage = 0;
										 vert.nTrackPos=0;
										 if(m_bmInfo.bmHeight<=m_size.cy)
										 {
											if((m_size.cy-m_bmInfo.bmHeight)==0)
												offsety= m_pt.y;
											else
												offsety= m_pt.y+((m_size.cy-m_bmInfo.bmHeight)/2);
											m_hbar.MoveWindow(offsetx,offsety+m_bmInfo.bmHeight,m_size.cx,18);
											m_vbar.ShowWindow(false);
										 }
										 else
										  m_vbar.ShowWindow(true);
										m_vbar.SetScrollInfo(&vert);


										InvalidateRect(&rectStaticClient);
										}




										vigenere[0] = new CEdit();
										vigenere[1] = new CEdit();
										vigenere[0]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(499,36,733,69) , this , IDC_EDIT2) ;
										//	newedit[0]->SetLimitText (m_medit1.GetLimitText ());

										vigenere[1]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(498,75,732,108) , this , IDC_EDIT2) ;
									


										GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_SHOW);//就可以隐藏，为SW_SHOW可以是显示。

										GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_SHOW);
										caseselect=3;

										strncpy(plain , m_Cedit1.GetBuffer(m_Cedit1.GetLength()) , m_Cedit1.GetLength()) ;	
										strncpy(key , m_Cedit2.GetBuffer(m_Cedit2.GetLength()) , m_Cedit2.GetLength()) ;
										Vigenere_en(plain,cipher,key);

			break;



	case 3:

			
			if (m_Cedit1=="" || m_Cedit2==""  )
			{
				MessageBox("请输入明文和密钥!","提示");
				return;
			}
			
			if ( (*m_Cedit1<'a' && *m_Cedit1>'Z') || *m_Cedit1<'A' ||*m_Cedit1>'z')
			{
				MessageBox("明文须为字母串!");
				return;
			}
			
			if ( (*m_Cedit2<'a' && *m_Cedit2>'Z') || *m_Cedit2<'A' ||*m_Cedit2>'z')
			{
				MessageBox("密钥须为字母串!");
				return;
								}
									switch(caseselect){
												case 1:

													newedit[0]->ShowWindow (false);
													newedit[1]->ShowWindow (false);
													newedit[2]->ShowWindow (false);
														break;

												case 2:
												duowenzi[0]->ShowWindow (false);
												duowenzi[1]->ShowWindow (false);
												duowenzi[2]->ShowWindow (false);
												duowenzi[3]->ShowWindow (false);




													break;
												case 3:
												vigenere[0]->ShowWindow (false);
												vigenere[1]->ShowWindow (false);




													break;
												case 4:
													editplayfair[0]->ShowWindow (false);
													editplayfair[1]->ShowWindow (false);
													editplayfair[2]->ShowWindow (false);


													break;
												case 5:



													break;
												case 6:
													affine[0]->ShowWindow (false);
													affine[1]->ShowWindow (false);
													affine[2]->ShowWindow (false);
													affine[3]->ShowWindow (false);




													break;

												case 7:
												rc4[0]->ShowWindow (false);
												rc4[1]->ShowWindow (false);
												rc4[2]->ShowWindow (false);



													break;

												case 8:
													des[0]->ShowWindow (false);
												des[1]->ShowWindow (false);
												des[2]->ShowWindow (false);
												des[3]->ShowWindow (false);
												des[4]->ShowWindow (false);
												des[5]->ShowWindow (false);
												desbutton[0]->ShowWindow (false);
												desbutton[1]->ShowWindow (false);
											
														if(desnext==true){
														des[6]->ShowWindow (false);
														des[7]->ShowWindow (false);
														des[8]->ShowWindow (false);
														des[9]->ShowWindow (false);
														
														des[10]->ShowWindow (false);
														des[11]->ShowWindow (false);
														des[12]->ShowWindow (false);
														des[13]->ShowWindow (false);
														des[14]->ShowWindow (false);
														desbutton[2]->ShowWindow (false);
														desbutton[3]->ShowWindow (false);
														//desbutton[4]->ShowWindow (false);
														desbutton[4]->ShowWindow (false);
														}
					

													break;

												case 9:
													idea[0]->ShowWindow (false);
														idea[1]->ShowWindow (false);
														idea[2]->ShowWindow (false);
														idea[3]->ShowWindow (false);
														idea[4]->ShowWindow (false);



													break;

												case 10:
												rsa[0]->ShowWindow (false);
														rsa[1]->ShowWindow (false);
														rsa[2]->ShowWindow (false);
														rsa[3]->ShowWindow (false);
														rsa[4]->ShowWindow (false);
														rsa[5]->ShowWindow (false);
														rsa[6]->ShowWindow (false);
														rsa[7]->ShowWindow (false);
														rsa[8]->ShowWindow (false);
														rsa[9]->ShowWindow (false);
														rsa[10]->ShowWindow (false);

													break;

												case 11:



													break;

										
												}

									m_hBmpNew =	 (HBITMAP) LoadImage(NULL, "Picture\\playfair.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
									if( m_hBmpNew == NULL )
									{
									 AfxMessageBox("Load Image Failed");
									}
									else
									{
									  m_pic1.GetClientRect( &rectStaticClient );//得到控件的客户区
									  rectStaticClient.NormalizeRect();
									  m_size.cx=rectStaticClient.Size().cx;
									  m_size.cy=rectStaticClient.Size().cy;
									  m_size.cx = rectStaticClient.Width();    // zero based
									  m_size.cy = rectStaticClient.Height();    // zero based
									  m_pic1.ClientToScreen( &rectStaticClient );//转换到屏幕坐标
             						  ScreenToClient( &rectStaticClient);//控件屏幕坐标转换到相对于对话框的客户坐标
									  m_pt.x = rectStaticClient.left;
									  m_pt.y = rectStaticClient.top;
									  GetObject( m_hBmpNew , sizeof(BITMAP), &m_bmInfo );
									  VERIFY(m_hBmpOld = (HBITMAP)SelectObject(m_dcMem, m_hBmpNew )  );
									  offsetx= m_pt.x;
									  offsety=m_pt.y;

									  m_vbar.MoveWindow(offsetx+m_size.cx,offsety,18,m_size.cy);
									  m_hbar.MoveWindow(offsetx,offsety+m_size.cy,m_size.cx,18);
									  horz.cbSize = sizeof(SCROLLINFO);
									  horz.fMask = SIF_ALL;
									  horz.nMin = 0;
									  horz.nMax = m_bmInfo.bmWidth-m_size.cx;
									  horz.nPage =0;
									  horz.nPos = 0;
									  horz.nTrackPos=0;
									  if(m_bmInfo.bmWidth<=m_size.cx)
									  {
										if((m_size.cx-m_bmInfo.bmWidth)==0)
											offsetx= m_pt.x;
										else
											offsetx= m_pt.x+((m_size.cx-m_bmInfo.bmWidth)/2);
										m_vbar.MoveWindow(offsetx+m_bmInfo.bmWidth,offsety,18,m_size.cy);
										m_hbar.ShowWindow(false);
									  }
									 else
									  m_hbar.ShowWindow(true);
									 m_hbar.SetScrollInfo(&horz);
									 vert.cbSize = sizeof(SCROLLINFO);
									 vert.fMask = SIF_ALL;
									 vert.nMin = 0;
									 vert.nMax = m_bmInfo.bmHeight-(m_size.cy);
									 vert.nPage = 0;
									 vert.nTrackPos=0;
									 if(m_bmInfo.bmHeight<=m_size.cy)
									 {
										if((m_size.cy-m_bmInfo.bmHeight)==0)
											offsety= m_pt.y;
										else
											offsety= m_pt.y+((m_size.cy-m_bmInfo.bmHeight)/2);
										m_hbar.MoveWindow(offsetx,offsety+m_bmInfo.bmHeight,m_size.cx,18);
										m_vbar.ShowWindow(false);
									 }
									 else
									  m_vbar.ShowWindow(true);
									m_vbar.SetScrollInfo(&vert);


									InvalidateRect(&rectStaticClient);
									}

					//editplayfair
							//			newedit[0]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(700,60,940,105) , this , IDC_EDIT2) ;
					//	newedit[0]->SetLimitText (m_medit1.GetLimitText ());

					//	newedit[1]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(520,130,675,165) , this , IDC_EDIT2) ;

								editplayfair[0]=new CEdit() ;
								editplayfair[0]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(570,130,760,168) , this , IDC_EDIT2) ;
								editplayfair[1]=new CEdit() ;
								editplayfair[1]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(405,176,525,205) , this , IDC_EDIT2) ;

								editplayfair[2]=new CEdit() ;
								editplayfair[2]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(608,212,722,319) , this , IDC_EDIT2) ;

								GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_SHOW);//就可以隐藏，为SW_SHOW可以是显示。

								GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_SHOW);
								caseselect=4;



								strncpy(plain , m_Cedit1.GetBuffer(m_Cedit1.GetLength()) , m_Cedit1.GetLength()) ;	
								strncpy(key , m_Cedit2.GetBuffer(m_Cedit2.GetLength()) , m_Cedit2.GetLength()) ;

								strncpy(key26,key,strlen(key));


								Playfair_encrypt(plain,cipher,key);
								
								
								
								
								
						break;


case 4:







			break;





case 5:






									switch(caseselect){
								case 1:

									newedit[0]->ShowWindow (false);
									newedit[1]->ShowWindow (false);
									newedit[2]->ShowWindow (false);
										break;

								case 2:
										duowenzi[0]->ShowWindow (false);
										duowenzi[1]->ShowWindow (false);
										duowenzi[2]->ShowWindow (false);
										duowenzi[3]->ShowWindow (false);




									break;
								case 3:
									vigenere[0]->ShowWindow (false);
									vigenere[1]->ShowWindow (false);






									break;
								case 4:
									editplayfair[0]->ShowWindow (false);
									editplayfair[1]->ShowWindow (false);
									editplayfair[2]->ShowWindow (false);


									break;
								case 5:



									break;
								case 6:
									affine[0]->ShowWindow (false);
									affine[1]->ShowWindow (false);
									affine[2]->ShowWindow (false);
									affine[3]->ShowWindow (false);


									break;

								case 7:

												rc4[0]->ShowWindow (false);
												rc4[1]->ShowWindow (false);
												rc4[2]->ShowWindow (false);


									break;

								case 8:
									des[0]->ShowWindow (false);
										des[1]->ShowWindow (false);
										des[2]->ShowWindow (false);
										des[3]->ShowWindow (false);
										des[4]->ShowWindow (false);
										des[5]->ShowWindow (false);
										desbutton[0]->ShowWindow (false);
										desbutton[1]->ShowWindow (false);
										
														if(desnext==true){
														des[6]->ShowWindow (false);
														des[7]->ShowWindow (false);
														des[8]->ShowWindow (false);
														des[9]->ShowWindow (false);
														
														des[10]->ShowWindow (false);
														des[11]->ShowWindow (false);
														des[12]->ShowWindow (false);
														des[13]->ShowWindow (false);
														des[14]->ShowWindow (false);
														desbutton[2]->ShowWindow (false);
														desbutton[3]->ShowWindow (false);
														//desbutton[4]->ShowWindow (false);
														desbutton[4]->ShowWindow (false);
														}
					


									break;

								case 9:
									idea[0]->ShowWindow (false);
									idea[1]->ShowWindow (false);
									idea[2]->ShowWindow (false);
									idea[3]->ShowWindow (false);
									idea[4]->ShowWindow (false);



									break;

								case 10:
								rsa[0]->ShowWindow (false);
														rsa[1]->ShowWindow (false);
														rsa[2]->ShowWindow (false);
														rsa[3]->ShowWindow (false);
														rsa[4]->ShowWindow (false);
														rsa[5]->ShowWindow (false);
														rsa[6]->ShowWindow (false);
														rsa[7]->ShowWindow (false);
														rsa[8]->ShowWindow (false);
														rsa[9]->ShowWindow (false);
														rsa[10]->ShowWindow (false);

									break;

								case 11:



									break;

						
								}

								//memset(key1,0,3);
								//memset(key2,0,3);
								strcpy(key1,"\0");
								strcpy(key2,"\0");
								
								
								
								
								
								strncpy(plain , m_Cedit1.GetBuffer(m_Cedit1.GetLength()) , m_Cedit1.GetLength()) ;	
								strncpy(key , m_Cedit2.GetBuffer(m_Cedit2.GetLength()) , m_Cedit2.GetLength()) ;
								
								if ( (key[1] == ',') || (key[1] =='，') )//密钥a是个位数
								{
									key1[0]=key[0];
									key2[0]=key[2];
									key2[1]=key[3];
								}
								else if( (key[2] == ',') || (key[2] =='，') )
								{//密钥a是两位数
									key1[0]=key[0];
									key1[1]=key[1];
									key2[0]=key[3];
									key2[1]=key[4];
								}
								else
								{
									MessageBox("密钥输入不合法\n请输入密钥a , b并以逗号隔开\na必须为3、5、7、9、11、13、15、17、19、21、23、25\nb必须为0-25之间的整数","提示");
									m_Cedit2="";
									UpdateData(false);
									
									return;
								}
								UpdateData(true);
								
								
									

							m_hBmpNew =	 (HBITMAP) LoadImage(NULL, "Picture\\affine.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
							if( m_hBmpNew == NULL )
							{
							 AfxMessageBox("Load Image Failed");
							}
							else
							{
							  m_pic1.GetClientRect( &rectStaticClient );//得到控件的客户区
							  rectStaticClient.NormalizeRect();
							  m_size.cx=rectStaticClient.Size().cx;
							  m_size.cy=rectStaticClient.Size().cy;
							  m_size.cx = rectStaticClient.Width();    // zero based
							  m_size.cy = rectStaticClient.Height();    // zero based
							  m_pic1.ClientToScreen( &rectStaticClient );//转换到屏幕坐标
             				  ScreenToClient( &rectStaticClient);//控件屏幕坐标转换到相对于对话框的客户坐标
							  m_pt.x = rectStaticClient.left;
							  m_pt.y = rectStaticClient.top;
							  GetObject( m_hBmpNew , sizeof(BITMAP), &m_bmInfo );
							  VERIFY(m_hBmpOld = (HBITMAP)SelectObject(m_dcMem, m_hBmpNew )  );
							  offsetx= m_pt.x;
							  offsety=m_pt.y;

							  m_vbar.MoveWindow(offsetx+m_size.cx,offsety,18,m_size.cy);
							  m_hbar.MoveWindow(offsetx,offsety+m_size.cy,m_size.cx,18);
							  horz.cbSize = sizeof(SCROLLINFO);
							  horz.fMask = SIF_ALL;
							  horz.nMin = 0;
							  horz.nMax = m_bmInfo.bmWidth-m_size.cx;
							  horz.nPage =0;
							  horz.nPos = 0;
							  horz.nTrackPos=0;
							  if(m_bmInfo.bmWidth<=m_size.cx)
							  {
								if((m_size.cx-m_bmInfo.bmWidth)==0)
									offsetx= m_pt.x;
								else
									offsetx= m_pt.x+((m_size.cx-m_bmInfo.bmWidth)/2);
								m_vbar.MoveWindow(offsetx+m_bmInfo.bmWidth,offsety,18,m_size.cy);
								m_hbar.ShowWindow(false);
							  }
							 else
							  m_hbar.ShowWindow(true);
							 m_hbar.SetScrollInfo(&horz);
							 vert.cbSize = sizeof(SCROLLINFO);
							 vert.fMask = SIF_ALL;
							 vert.nMin = 0;
							 vert.nMax = m_bmInfo.bmHeight-(m_size.cy);
							 vert.nPage = 0;
							 vert.nTrackPos=0;
							 if(m_bmInfo.bmHeight<=m_size.cy)
							 {
								if((m_size.cy-m_bmInfo.bmHeight)==0)
									offsety= m_pt.y;
								else
									offsety= m_pt.y+((m_size.cy-m_bmInfo.bmHeight)/2);
								m_hbar.MoveWindow(offsetx,offsety+m_bmInfo.bmHeight,m_size.cx,18);
								m_vbar.ShowWindow(false);
							 }
							 else
							  m_vbar.ShowWindow(true);
							m_vbar.SetScrollInfo(&vert);


							InvalidateRect(&rectStaticClient);
							}

						//editplayfair
								//			newedit[0]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(700,60,940,105) , this , IDC_EDIT2) ;
						//	newedit[0]->SetLimitText (m_medit1.GetLimitText ());

						//	newedit[1]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(520,130,675,165) , this , IDC_EDIT2) ;

								affine[0]=new CEdit() ;
								affine[0]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(387,338,552,370) , this , IDC_EDIT2) ;
								
								
								affine[1]=new CEdit() ;
								affine[1]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(665,135,693,170) , this , IDC_EDIT2) ;

								affine[2]=new CEdit() ;
								affine[2]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(705,136,733,169) , this , IDC_EDIT2) ;


								affine[3]=new CEdit() ;
								affine[3]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(559,384,863,416) , this , IDC_EDIT2) ;

								GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_SHOW);//就可以隐藏，为SW_SHOW可以是显示。

								GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_SHOW);



								caseselect=6;



										memcpy(key1_temp,key1,3);
										encipher(plain , cipher, atoi(key1), atoi(key2) );
										
										strcpy(alpha,"abcdefghijklmnopqrstuvwxyz");

										encipher(alpha , affine_tmp, atoi(key1_temp), atoi(key2) );

										//MessageBox(CString(affine_tmp));




								break;

	case 6:


						if (m_Cedit1=="" || m_Cedit2==""  )
						{
								MessageBox("请输入明文和密钥!","提示");
								return;
						}


						switch(caseselect){
													case 1:

														newedit[0]->ShowWindow (false);
														newedit[1]->ShowWindow (false);
														newedit[2]->ShowWindow (false);
															break;

													case 2:
														duowenzi[0]->ShowWindow (false);
														duowenzi[1]->ShowWindow (false);
														duowenzi[2]->ShowWindow (false);
														duowenzi[3]->ShowWindow (false);





														break;
													case 3:
														vigenere[0]->ShowWindow (false);
														vigenere[1]->ShowWindow (false);



														break;
													case 4:
														editplayfair[0]->ShowWindow (false);
														editplayfair[1]->ShowWindow (false);
														editplayfair[2]->ShowWindow (false);


														break;
													case 5:



														break;
													case 6:
														affine[0]->ShowWindow (false);
														affine[1]->ShowWindow (false);
														affine[2]->ShowWindow (false);
														affine[3]->ShowWindow (false);




														break;

													case 7:

												rc4[0]->ShowWindow (false);
												rc4[1]->ShowWindow (false);
												rc4[2]->ShowWindow (false);


														break;

													case 8:
														des[0]->ShowWindow (false);
														des[1]->ShowWindow (false);
														des[2]->ShowWindow (false);
														des[3]->ShowWindow (false);
														des[4]->ShowWindow (false);
														des[5]->ShowWindow (false);
														desbutton[0]->ShowWindow (false);
														desbutton[1]->ShowWindow (false);
														
														if(desnext==true){
														des[6]->ShowWindow (false);
														des[7]->ShowWindow (false);
														des[8]->ShowWindow (false);
														des[9]->ShowWindow (false);
														
														des[10]->ShowWindow (false);
														des[11]->ShowWindow (false);
														des[12]->ShowWindow (false);
														des[13]->ShowWindow (false);
														des[14]->ShowWindow (false);
														desbutton[2]->ShowWindow (false);
														desbutton[3]->ShowWindow (false);
														//desbutton[4]->ShowWindow (false);
														desbutton[4]->ShowWindow (false);
														}
								




														break;

													case 9:
														idea[0]->ShowWindow (false);
														idea[1]->ShowWindow (false);
														idea[2]->ShowWindow (false);
														idea[3]->ShowWindow (false);
														idea[4]->ShowWindow (false);



														break;

													case 10:
														rsa[0]->ShowWindow (false);
														rsa[1]->ShowWindow (false);
														rsa[2]->ShowWindow (false);
														rsa[3]->ShowWindow (false);
														rsa[4]->ShowWindow (false);
														rsa[5]->ShowWindow (false);
														rsa[6]->ShowWindow (false);
														rsa[7]->ShowWindow (false);
														rsa[8]->ShowWindow (false);
														rsa[9]->ShowWindow (false);
														rsa[10]->ShowWindow (false);




														break;

													case 11:



														break;

											
													}

													
											m_hBmpNew =	 (HBITMAP) LoadImage(NULL, "Picture\\RC4.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
											if( m_hBmpNew == NULL )
											{
											 AfxMessageBox("Load Image Failed");
											}
											else
											{
											  m_pic1.GetClientRect( &rectStaticClient );//得到控件的客户区
											  rectStaticClient.NormalizeRect();
											  m_size.cx=rectStaticClient.Size().cx;
											  m_size.cy=rectStaticClient.Size().cy;
											  m_size.cx = rectStaticClient.Width();    // zero based
											  m_size.cy = rectStaticClient.Height();    // zero based
											  m_pic1.ClientToScreen( &rectStaticClient );//转换到屏幕坐标
             								  ScreenToClient( &rectStaticClient);//控件屏幕坐标转换到相对于对话框的客户坐标
											  m_pt.x = rectStaticClient.left;
											  m_pt.y = rectStaticClient.top;
											  GetObject( m_hBmpNew , sizeof(BITMAP), &m_bmInfo );
											  VERIFY(m_hBmpOld = (HBITMAP)SelectObject(m_dcMem, m_hBmpNew )  );
											  offsetx= m_pt.x;
											  offsety=m_pt.y;

											  m_vbar.MoveWindow(offsetx+m_size.cx,offsety,18,m_size.cy);
											  m_hbar.MoveWindow(offsetx,offsety+m_size.cy,m_size.cx,18);
											  horz.cbSize = sizeof(SCROLLINFO);
											  horz.fMask = SIF_ALL;
											  horz.nMin = 0;
											  horz.nMax = m_bmInfo.bmWidth-m_size.cx;
											  horz.nPage =0;
											  horz.nPos = 0;
											  horz.nTrackPos=0;
											  if(m_bmInfo.bmWidth<=m_size.cx)
											  {
												if((m_size.cx-m_bmInfo.bmWidth)==0)
													offsetx= m_pt.x;
												else
													offsetx= m_pt.x+((m_size.cx-m_bmInfo.bmWidth)/2);
												m_vbar.MoveWindow(offsetx+m_bmInfo.bmWidth,offsety,18,m_size.cy);
												m_hbar.ShowWindow(false);
											  }
											 else
											  m_hbar.ShowWindow(true);
											 m_hbar.SetScrollInfo(&horz);


											 vert.cbSize = sizeof(SCROLLINFO);
											 vert.fMask = SIF_ALL;
											 vert.nMin = 0;
											 vert.nMax = m_bmInfo.bmHeight-(m_size.cy);
											 vert.nPage = 0;
											 vert.nTrackPos=0;
											 if(m_bmInfo.bmHeight<=m_size.cy)
											 {
												if((m_size.cy-m_bmInfo.bmHeight)==0)
													offsety= m_pt.y;
												else
													offsety= m_pt.y+((m_size.cy-m_bmInfo.bmHeight)/2);
												m_hbar.MoveWindow(offsetx,offsety+m_bmInfo.bmHeight,m_size.cx,18);
												m_vbar.ShowWindow(false);
											 }
											 else
											  m_vbar.ShowWindow(true);
											m_vbar.SetScrollInfo(&vert);


											InvalidateRect(&rectStaticClient);
											}





											rc4[0] = new CEdit() ;
											rc4[1] = new CEdit() ;
											rc4[2] = new CEdit() ;
									
											rc4[0]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER|ES_MULTILINE|ES_AUTOVSCROLL, CRect(452,299,572,365) , this , IDC_EDIT2) ;

											rc4[1]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER|ES_MULTILINE|ES_AUTOVSCROLL, CRect(575,127,753,153) , this , IDC_EDIT2) ;



											rc4[2]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER|ES_MULTILINE|ES_AUTOVSCROLL, CRect(625,236,736,437) , this , IDC_EDIT2) ;





											GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_SHOW);//就可以隐藏，为SW_SHOW可以是显示。

											GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_SHOW);
											
											strncpy(plain , m_Cedit1.GetBuffer(m_Cedit1.GetLength()) , m_Cedit1.GetLength()) ;	
											strncpy(key , m_Cedit2.GetBuffer(m_Cedit2.GetLength()) , m_Cedit2.GetLength()) ;
											strcpy(origin_keystream,key);
											RC4_process(origin_keystream,keystream);
											RC4_enstring(plain,cipher,key);

								caseselect=7;
			break;

		case 7:

												if (m_Cedit1=="" || m_Cedit2==""  )
												{
													MessageBox("请输入明文和密钥!","提示");
													return;
												}
			


															switch(caseselect){
														case 1:

															newedit[0]->ShowWindow (false);
															newedit[1]->ShowWindow (false);
															newedit[2]->ShowWindow (false);
																break;

														case 2:
																duowenzi[0]->ShowWindow (false);
																duowenzi[1]->ShowWindow (false);
																duowenzi[2]->ShowWindow (false);
																duowenzi[3]->ShowWindow (false);




															break;
														case 3:
															vigenere[0]->ShowWindow (false);
															vigenere[1]->ShowWindow (false);






															break;
														case 4:
															editplayfair[0]->ShowWindow (false);
															editplayfair[1]->ShowWindow (false);
															editplayfair[2]->ShowWindow (false);


															break;
														case 5:



															break;
														case 6:
															affine[0]->ShowWindow (false);
															affine[1]->ShowWindow (false);
															affine[2]->ShowWindow (false);
															affine[3]->ShowWindow (false);


															break;

														case 7:

												rc4[0]->ShowWindow (false);
												rc4[1]->ShowWindow (false);
												rc4[2]->ShowWindow (false);


															break;

														case 8:
														des[0]->ShowWindow (false);
														des[1]->ShowWindow (false);
														des[2]->ShowWindow (false);
														des[3]->ShowWindow (false);
														des[4]->ShowWindow (false);
														des[5]->ShowWindow (false);


														desbutton[0]->ShowWindow (false);
														desbutton[1]->ShowWindow (false);
														
														if(desnext==true){
														des[6]->ShowWindow (false);
														des[7]->ShowWindow (false);
														des[8]->ShowWindow (false);
														des[9]->ShowWindow (false);
														
														des[10]->ShowWindow (false);
														des[11]->ShowWindow (false);
														des[12]->ShowWindow (false);
														des[13]->ShowWindow (false);
														des[14]->ShowWindow (false);
														desbutton[2]->ShowWindow (false);
														desbutton[3]->ShowWindow (false);
														//desbutton[4]->ShowWindow (false);
														desbutton[4]->ShowWindow (false);
														}
					


															break;

														case 9:
															idea[0]->ShowWindow (false);
														idea[1]->ShowWindow (false);
														idea[2]->ShowWindow (false);
														idea[3]->ShowWindow (false);
														idea[4]->ShowWindow (false);



															break;

														case 10:
														rsa[0]->ShowWindow (false);
														rsa[1]->ShowWindow (false);
														rsa[2]->ShowWindow (false);
														rsa[3]->ShowWindow (false);
														rsa[4]->ShowWindow (false);
														rsa[5]->ShowWindow (false);
														rsa[6]->ShowWindow (false);
														rsa[7]->ShowWindow (false);
														rsa[8]->ShowWindow (false);
														rsa[9]->ShowWindow (false);
														rsa[10]->ShowWindow (false);


															break;

														case 11:



															break;

												
														}

													m_hBmpNew =	 (HBITMAP) LoadImage(NULL, "Picture\\DES_1.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
													if( m_hBmpNew == NULL )
													{
													 AfxMessageBox("Load Image Failed");
													}
													else
													{
													  m_pic1.GetClientRect( &rectStaticClient );//得到控件的客户区
													  rectStaticClient.NormalizeRect();
													  m_size.cx=rectStaticClient.Size().cx;
													  m_size.cy=rectStaticClient.Size().cy;
													  m_size.cx = rectStaticClient.Width();    // zero based
													  m_size.cy = rectStaticClient.Height();    // zero based
													  m_pic1.ClientToScreen( &rectStaticClient );//转换到屏幕坐标
             										  ScreenToClient( &rectStaticClient);//控件屏幕坐标转换到相对于对话框的客户坐标
													  m_pt.x = rectStaticClient.left;
													  m_pt.y = rectStaticClient.top;
													  GetObject( m_hBmpNew , sizeof(BITMAP), &m_bmInfo );
													  VERIFY(m_hBmpOld = (HBITMAP)SelectObject(m_dcMem, m_hBmpNew )  );
													  offsetx= m_pt.x;
													  offsety=m_pt.y;

													  m_vbar.MoveWindow(offsetx+m_size.cx,offsety,18,m_size.cy);
													  m_hbar.MoveWindow(offsetx,offsety+m_size.cy,m_size.cx,18);
													  horz.cbSize = sizeof(SCROLLINFO);
													  horz.fMask = SIF_ALL;
													  horz.nMin = 0;
													  horz.nMax = m_bmInfo.bmWidth-m_size.cx;
													  horz.nPage =0;
													  horz.nPos = 0;
													  horz.nTrackPos=0;
													  if(m_bmInfo.bmWidth<=m_size.cx)
													  {
														if((m_size.cx-m_bmInfo.bmWidth)==0)
															offsetx= m_pt.x;
														else
															offsetx= m_pt.x+((m_size.cx-m_bmInfo.bmWidth)/2);
														m_vbar.MoveWindow(offsetx+m_bmInfo.bmWidth,offsety,18,m_size.cy);
														m_hbar.ShowWindow(false);
													  }
													 else
													  m_hbar.ShowWindow(true);
													 m_hbar.SetScrollInfo(&horz);
													 vert.cbSize = sizeof(SCROLLINFO);
													 vert.fMask = SIF_ALL;
													 vert.nMin = 0;
													 vert.nMax = m_bmInfo.bmHeight-(m_size.cy);
													 vert.nPage = 0;
													 vert.nTrackPos=0;
													 if(m_bmInfo.bmHeight<=m_size.cy)
													 {
														if((m_size.cy-m_bmInfo.bmHeight)==0)
															offsety= m_pt.y;
														else
															offsety= m_pt.y+((m_size.cy-m_bmInfo.bmHeight)/2);
														m_hbar.MoveWindow(offsetx,offsety+m_bmInfo.bmHeight,m_size.cx,18);
														m_vbar.ShowWindow(false);
													 }
													 else
													  m_vbar.ShowWindow(true);
													m_vbar.SetScrollInfo(&vert);


													InvalidateRect(&rectStaticClient);
													}
													desnext=false;

												//editplayfair
														//			newedit[0]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(700,60,940,105) , this , IDC_EDIT2) ;
												//	newedit[0]->SetLimitText (m_medit1.GetLimitText ());

												//	newedit[1]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(520,130,675,165) , this , IDC_EDIT2) ;

												des[0]=new CEdit() ;
												des[0]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(496,112,739,137) , this , IDC_EDIT2) ;
												
												
												des[1]=new CEdit() ;
												des[1]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(428,244,580,265) , this , IDC_EDIT2) ;

												des[2]=new CEdit() ;
												des[2]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(654,244,808,264) , this , IDC_EDIT2) ;


												des[3]=new CEdit() ;
												des[3]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(428,302,580,322) , this , IDC_EDIT2) ;


												des[4]=new CEdit() ;
												des[4]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(654,302,808,322) , this , IDC_EDIT2) ;




												des[5]=new CEdit() ;
												des[5]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(505,455,733,477) , this , IDC_EDIT2) ;
												
												///////////////////////////////////////////////////////////////////////////
														
												desbutton[0]->ShowWindow (true);
												desbutton[1]->ShowWindow (true);
												
												
												
										



												GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_SHOW);//就可以隐藏，为SW_SHOW可以是显示。

												GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_SHOW);\
												desnext=false;
												caseselect=8;






												strncpy(plain , m_Cedit1.GetBuffer(m_Cedit1.GetLength()) , m_Cedit1.GetLength()) ;	
												strncpy(key , m_Cedit2.GetBuffer(m_Cedit2.GetLength()) , m_Cedit2.GetLength()) ;
												memcpy(strkey,key,8);
												StartDes(cipher, plain, strlen(plain), key, strlen(key), 0, 0,NULL,NULL,NULL );
												//处理第一张图片中的显示
												ByteToBit(keyblock,strkey,64);
												Transform(keyblock2,keyblock,PC1_Table,56);
												memcpy(kl,keyblock2,28);
												memcpy(kr,keyblock2+28,28);
												memcpy(kl_tmp,keyblock2,28);
												memcpy(kr_tmp,keyblock2+28,28);
												RotateL(kl,28,LOOP_Table[0]);
												RotateL(kr,28,LOOP_Table[0]);
												memcpy(keyblock2,kl,28);
												memcpy(keyblock2+28,kr,28);
												Transform(subkey , keyblock2 , PC2_Table ,48);
												
												//处理第二张图片里的显示

												memcpy(plainblock,plain,8);
												ByteToBit(plain64,plainblock,64);//把8字节明文块转化为64位明文比特流
												Transform(plain64_ip,plain64,IP_Table,64);//通过置换表
												memcpy(plainleft32,plain64_ip,32);
												memcpy(plainright32,plain64_ip+32,32);
												memcpy(cipherleft32,plainright32,32);//cipherleft32可以显示在两个编辑框中
												
												Transform(plain48,plainright32,E_Table,48);//E盒,产生的plain48显示
												
												F_func(plainright32,subkey);//F函数
												Xor(plainright32, plainleft32, 32);//异或后产生右32位密文
												memcpy(cipherright32,plainright32,32);//右32位密文

												memcpy(cipher64,cipherleft32,32);
												memcpy(cipher64+32,cipherright32,32);//一轮加密之后得到64位密文块
	
												break;

	
case 8:
						if (m_Cedit1=="" || m_Cedit2==""  )
						{
							MessageBox("请输入明文和密钥!","提示");
							return;
						}

						switch(caseselect){
													case 1:

														newedit[0]->ShowWindow (false);
														newedit[1]->ShowWindow (false);
														newedit[2]->ShowWindow (false);
															break;

													case 2:
														duowenzi[0]->ShowWindow (false);
														duowenzi[1]->ShowWindow (false);
														duowenzi[2]->ShowWindow (false);
														duowenzi[3]->ShowWindow (false);





														break;
													case 3:
														vigenere[0]->ShowWindow (false);
														vigenere[1]->ShowWindow (false);



														break;
													case 4:
														editplayfair[0]->ShowWindow (false);
														editplayfair[1]->ShowWindow (false);
														editplayfair[2]->ShowWindow (false);


														break;
													case 5:



														break;
													case 6:
														affine[0]->ShowWindow (false);
														affine[1]->ShowWindow (false);
														affine[2]->ShowWindow (false);
														affine[3]->ShowWindow (false);




														break;

													case 7:

												rc4[0]->ShowWindow (false);
												rc4[1]->ShowWindow (false);
												rc4[2]->ShowWindow (false);


														break;

													case 8:
														des[0]->ShowWindow (false);
														des[1]->ShowWindow (false);
														des[2]->ShowWindow (false);
														des[3]->ShowWindow (false);
														des[4]->ShowWindow (false);
														des[5]->ShowWindow (false);
														desbutton[0]->ShowWindow (false);
														desbutton[1]->ShowWindow (false);
													
														if(desnext==true){
														des[6]->ShowWindow (false);
														des[7]->ShowWindow (false);
														des[8]->ShowWindow (false);
														des[9]->ShowWindow (false);
														
														des[10]->ShowWindow (false);
														des[11]->ShowWindow (false);
														des[12]->ShowWindow (false);
														des[13]->ShowWindow (false);
														des[14]->ShowWindow (false);
														desbutton[2]->ShowWindow (false);
														desbutton[3]->ShowWindow (false);
														//desbutton[4]->ShowWindow (false);
														desbutton[4]->ShowWindow (false);
														}
					

														break;

													case 9:
														idea[0]->ShowWindow (false);
														idea[1]->ShowWindow (false);
														idea[2]->ShowWindow (false);
														idea[3]->ShowWindow (false);
														idea[4]->ShowWindow (false);



														break;

													case 10:
													rsa[0]->ShowWindow (false);
														rsa[1]->ShowWindow (false);
														rsa[2]->ShowWindow (false);
														rsa[3]->ShowWindow (false);
														rsa[4]->ShowWindow (false);
														rsa[5]->ShowWindow (false);
														rsa[6]->ShowWindow (false);
														rsa[7]->ShowWindow (false);
														rsa[8]->ShowWindow (false);
														rsa[9]->ShowWindow (false);
														rsa[10]->ShowWindow (false);


														break;

													case 11:



														break;

											
													}


				m_hBmpNew =	 (HBITMAP) LoadImage(NULL, "Picture\\IDEA.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
													if( m_hBmpNew == NULL )
													{
													 AfxMessageBox("Load Image Failed");
													}
													else
													{
													  m_pic1.GetClientRect( &rectStaticClient );//得到控件的客户区
													  rectStaticClient.NormalizeRect();
													  m_size.cx=rectStaticClient.Size().cx;
													  m_size.cy=rectStaticClient.Size().cy;
													  m_size.cx = rectStaticClient.Width();    // zero based
													  m_size.cy = rectStaticClient.Height();    // zero based
													  m_pic1.ClientToScreen( &rectStaticClient );//转换到屏幕坐标
             										  ScreenToClient( &rectStaticClient);//控件屏幕坐标转换到相对于对话框的客户坐标
													  m_pt.x = rectStaticClient.left;
													  m_pt.y = rectStaticClient.top;
													  GetObject( m_hBmpNew , sizeof(BITMAP), &m_bmInfo );
													  VERIFY(m_hBmpOld = (HBITMAP)SelectObject(m_dcMem, m_hBmpNew )  );
													  offsetx= m_pt.x;
													  offsety=m_pt.y;

													  m_vbar.MoveWindow(offsetx+m_size.cx,offsety,18,m_size.cy);
													  m_hbar.MoveWindow(offsetx,offsety+m_size.cy,m_size.cx,18);
													  horz.cbSize = sizeof(SCROLLINFO);
													  horz.fMask = SIF_ALL;
													  horz.nMin = 0;
													  horz.nMax = m_bmInfo.bmWidth-m_size.cx;
													  horz.nPage =0;
													  horz.nPos = 0;
													  horz.nTrackPos=0;
													  if(m_bmInfo.bmWidth<=m_size.cx)
													  {
														if((m_size.cx-m_bmInfo.bmWidth)==0)
															offsetx= m_pt.x;
														else
															offsetx= m_pt.x+((m_size.cx-m_bmInfo.bmWidth)/2);
														m_vbar.MoveWindow(offsetx+m_bmInfo.bmWidth,offsety,18,m_size.cy);
														m_hbar.ShowWindow(false);
													  }
													 else
													  m_hbar.ShowWindow(true);
													 m_hbar.SetScrollInfo(&horz);
													 vert.cbSize = sizeof(SCROLLINFO);
													 vert.fMask = SIF_ALL;
													 vert.nMin = 0;
													 vert.nMax = m_bmInfo.bmHeight-(m_size.cy);
													 vert.nPage = 0;
													 vert.nTrackPos=0;
													 if(m_bmInfo.bmHeight<=m_size.cy)
													 {
														if((m_size.cy-m_bmInfo.bmHeight)==0)
															offsety= m_pt.y;
														else
															offsety= m_pt.y+((m_size.cy-m_bmInfo.bmHeight)/2);
														m_hbar.MoveWindow(offsetx,offsety+m_bmInfo.bmHeight,m_size.cx,18);
														m_vbar.ShowWindow(false);
													 }
													 else
													  m_vbar.ShowWindow(true);
													m_vbar.SetScrollInfo(&vert);


													InvalidateRect(&rectStaticClient);
													}

												//editplayfair
														//			newedit[0]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(700,60,940,105) , this , IDC_EDIT2) ;
												//	newedit[0]->SetLimitText (m_medit1.GetLimitText ());

												//	newedit[1]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(520,130,675,165) , this , IDC_EDIT2) ;

												idea[0]=new CEdit() ;
												idea[0]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(470,45,775,68) , this , IDC_EDIT2) ;
												
												
												idea[1]=new CEdit() ;
												idea[1]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(485,470,532,491) , this , IDC_EDIT2) ;

												idea[2]=new CEdit() ;
												idea[2]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(569,470,615,491) , this , IDC_EDIT2) ;


												idea[3]=new CEdit() ;
												idea[3]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(636,470,685,491) , this , IDC_EDIT2) ;


												idea[4]=new CEdit() ;
												idea[4]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(710,470,759,491) , this , IDC_EDIT2) ;


												GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_SHOW);//就可以隐藏，为SW_SHOW可以是显示。

												GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_SHOW);



												strncpy(plain , m_Cedit1.GetBuffer(m_Cedit1.GetLength()) , m_Cedit1.GetLength()) ;	
												strncpy(key , m_Cedit2.GetBuffer(m_Cedit2.GetLength()) , m_Cedit2.GetLength()) ;
												memcpy(strkey,key,8);
												StartDes(cipher, plain, strlen(plain), key, strlen(key), 0, 0,NULL,NULL,NULL );
												ByteToBit(keyblock,strkey,64);//keyblock显示
												memcpy(cipher16a,keyblock+32,16);
												memcpy(cipher16b,keyblock+48,16);
												memcpy(cipher16c,keyblock,16);
												memcpy(cipher16d,keyblock+16,16);


														caseselect=9;
			
														break;
		case 9:

					
			if (m_Cedit1=="" || m_Cedit2==""  )
			{
				MessageBox("请输入明文和密钥!","提示");
				return;
			}
			
			if (atoi(m_Cedit3)==0)
			{
				MessageBox("请在密钥处输入大素数的长度","提示");
				return;
			}
			

											switch(caseselect){
													case 1:

														newedit[0]->ShowWindow (false);
														newedit[1]->ShowWindow (false);
														newedit[2]->ShowWindow (false);
															break;

													case 2:
														duowenzi[0]->ShowWindow (false);
														duowenzi[1]->ShowWindow (false);
														duowenzi[2]->ShowWindow (false);
														duowenzi[3]->ShowWindow (false);





														break;
													case 3:
														vigenere[0]->ShowWindow (false);
														vigenere[1]->ShowWindow (false);



														break;
													case 4:
														editplayfair[0]->ShowWindow (false);
														editplayfair[1]->ShowWindow (false);
														editplayfair[2]->ShowWindow (false);


														break;
													case 5:



														break;
													case 6:
														affine[0]->ShowWindow (false);
														affine[1]->ShowWindow (false);
														affine[2]->ShowWindow (false);
														affine[3]->ShowWindow (false);




														break;

													case 7:


												rc4[0]->ShowWindow (false);
												rc4[1]->ShowWindow (false);
												rc4[2]->ShowWindow (false);

														break;

													case 8:
														des[0]->ShowWindow (false);
														des[1]->ShowWindow (false);
														des[2]->ShowWindow (false);
														des[3]->ShowWindow (false);
														des[4]->ShowWindow (false);
														des[5]->ShowWindow (false);
														desbutton[0]->ShowWindow (false);
														desbutton[1]->ShowWindow (false);
														
														if(desnext==true){
														des[6]->ShowWindow (false);
														des[7]->ShowWindow (false);
														des[8]->ShowWindow (false);
														des[9]->ShowWindow (false);
														
														des[10]->ShowWindow (false);
														des[11]->ShowWindow (false);
														des[12]->ShowWindow (false);
														des[13]->ShowWindow (false);
														des[14]->ShowWindow (false);
														desbutton[2]->ShowWindow (false);
														desbutton[3]->ShowWindow (false);
														//desbutton[4]->ShowWindow (false);
														desbutton[4]->ShowWindow (false);
														}
					



														break;

													case 9:
														idea[0]->ShowWindow (false);
														idea[1]->ShowWindow (false);
														idea[2]->ShowWindow (false);
														idea[3]->ShowWindow (false);
														idea[4]->ShowWindow (false);



														break;

													case 10:
														rsa[0]->ShowWindow (false);
														rsa[1]->ShowWindow (false);
														rsa[2]->ShowWindow (false);
														rsa[3]->ShowWindow (false);
														rsa[4]->ShowWindow (false);
														rsa[5]->ShowWindow (false);
														rsa[6]->ShowWindow (false);
														rsa[7]->ShowWindow (false);
														rsa[8]->ShowWindow (false);
														rsa[9]->ShowWindow (false);
														rsa[10]->ShowWindow (false);
														break;

													case 11:



														break;

											
													}
													
				m_hBmpNew =	 (HBITMAP) LoadImage(NULL, "Picture\\RSA_1.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
													if( m_hBmpNew == NULL )
													{
													 AfxMessageBox("Load Image Failed");
													}
													else
													{
													  m_pic1.GetClientRect( &rectStaticClient );//得到控件的客户区
													  rectStaticClient.NormalizeRect();
													  m_size.cx=rectStaticClient.Size().cx;
													  m_size.cy=rectStaticClient.Size().cy;
													  m_size.cx = rectStaticClient.Width();    // zero based
													  m_size.cy = rectStaticClient.Height();    // zero based
													  m_pic1.ClientToScreen( &rectStaticClient );//转换到屏幕坐标
             										  ScreenToClient( &rectStaticClient);//控件屏幕坐标转换到相对于对话框的客户坐标
													  m_pt.x = rectStaticClient.left;
													  m_pt.y = rectStaticClient.top;
													  GetObject( m_hBmpNew , sizeof(BITMAP), &m_bmInfo );
													  VERIFY(m_hBmpOld = (HBITMAP)SelectObject(m_dcMem, m_hBmpNew )  );
													  offsetx= m_pt.x;
													  offsety=m_pt.y;

													  m_vbar.MoveWindow(offsetx+m_size.cx,offsety,18,m_size.cy);
													  m_hbar.MoveWindow(offsetx,offsety+m_size.cy,m_size.cx,18);
													  horz.cbSize = sizeof(SCROLLINFO);
													  horz.fMask = SIF_ALL;
													  horz.nMin = 0;
													  horz.nMax = m_bmInfo.bmWidth-m_size.cx;
													  horz.nPage =0;
													  horz.nPos = 0;
													  horz.nTrackPos=0;
													  if(m_bmInfo.bmWidth<=m_size.cx)
													  {
														if((m_size.cx-m_bmInfo.bmWidth)==0)
															offsetx= m_pt.x;
														else
															offsetx= m_pt.x+((m_size.cx-m_bmInfo.bmWidth)/2);
														m_vbar.MoveWindow(offsetx+m_bmInfo.bmWidth,offsety,18,m_size.cy);
														m_hbar.ShowWindow(false);
													  }
													 else
													  m_hbar.ShowWindow(true);
													 m_hbar.SetScrollInfo(&horz);
													 vert.cbSize = sizeof(SCROLLINFO);
													 vert.fMask = SIF_ALL;
													 vert.nMin = 0;
													 vert.nMax = m_bmInfo.bmHeight-(m_size.cy);
													 vert.nPage = 0;
													 vert.nTrackPos=0;
													 if(m_bmInfo.bmHeight<=m_size.cy)
													 {
														if((m_size.cy-m_bmInfo.bmHeight)==0)
															offsety= m_pt.y;
														else
															offsety= m_pt.y+((m_size.cy-m_bmInfo.bmHeight)/2);
														m_hbar.MoveWindow(offsetx,offsety+m_bmInfo.bmHeight,m_size.cx,18);
														m_vbar.ShowWindow(false);
													 }
													 else
													  m_vbar.ShowWindow(true);
													m_vbar.SetScrollInfo(&vert);


													InvalidateRect(&rectStaticClient);
													}

												//editplayfair
														//			newedit[0]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(700,60,940,105) , this , IDC_EDIT2) ;
												//	newedit[0]->SetLimitText (m_medit1.GetLimitText ());

												//	newedit[1]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(520,130,675,165) , this , IDC_EDIT2) ;

												
													rsa[0]->ShowWindow (true);
													rsa[1]->ShowWindow (true);
													rsa[2]->ShowWindow (true);
													rsa[3]->ShowWindow (true);
													rsa[4]->ShowWindow (true);



													rsa[0]->SetWindowText ("");
													rsa[1]->SetWindowText ("");
													rsa[2]->SetWindowText ("");
													rsa[3]->SetWindowText ("");
													rsa[4]->SetWindowText ("");




												GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_SHOW);//就可以隐藏，为SW_SHOW可以是显示。

												GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_SHOW);

														caseselect=10;

											strncpy(plain , m_Cedit1.GetBuffer(m_Cedit1.GetLength()) , m_Cedit1.GetLength()) ;	
											strncpy(key , m_Cedit2.GetBuffer(m_Cedit2.GetLength()) , m_Cedit2.GetLength()) ;
											RSA_Encrypt(plain,  cipher, atoi(key) ,false);

			break;



		}
////////?????????????????????????????????????????????????????????????????????

/*
	newedit[0] = new CEdit() ;
	newedit[1] = new CEdit() ;
	newedit[2] = new CEdit() ;
	newedit[3] = new CEdit() ;

	newedit[0]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(700,60,940,105) , this , IDC_EDIT2) ;
//	newedit[0]->SetLimitText (m_medit1.GetLimitText ());

	newedit[1]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(520,130,675,165) , this , IDC_EDIT2) ;
	


*/
//////////////////????????????????????????????????????????????????????????



			}
//////////////////////////?????????????????????????????????????

















//int playfaircount=-1;
CString a="zhang jie ";
CString b="nin  hao";

CString c="zhong hua ";

CString d="ren min  ";


CString minwen="  xian shi  mi  wen   ";

///////////////////////caser









void CDialog4::OnButton2() 
{
	// TODO: Add your control notification handler code here


	UpdateData(true);
	////cichu此处添加计数器的代码////////////////////////////////////////////////////
	// ci此数字为图片中的多画框中的个数+2
	if(playfaircountnext!=5)
	playfaircountnext=playfaircountnext+1;


	if(caesercount!=5){
		caesercount=caesercount+1;
	
	}

	if(affinecount!=6){
		affinecount=affinecount+1;

	}
	if(vigenerecount!=4){
		vigenerecount=vigenerecount+1;
	
	}
	if(duowenzicount!=6){
		duowenzicount=duowenzicount+1;
	}
	if(descount!=23){
		descount=descount+1;
	}
	if(ideacount!=4){
		ideacount=ideacount+1;
	}
	if(rsacount!=14){
		rsacount=rsacount+1;
	}
	if(rc4count!=5){
		rc4count=rc4count+1;
	}

	//caeser显示字母表使用
	char row[79]={'\0'};


	//多文字显示密钥所用
	char str1[6]={'\0'};
	char str2[26]={'\0'};
	char str3[31]={'\0'};
	int p;

	char keymodify[26]={'\0'};
	char keymatrix[26]="abcdefghijlmnopqrstuvwxyz";
	char keymatrixmo[200]={'\0'};
	//////////playfair
	char letters[26]="ABCDEFGHIKLMNOPQRSTUVWXYZ";//用于填充矩阵
	int flag[25]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//标记字母是否已在矩阵中，与letters数组对应
	//char ch[5][5];//5X5矩阵


	char tempt16[16];
	char tempt[28];
	char tempt2[48];
	char tempt32a[32];
	char tempt32b[32];
	char tempt64[64];


	switch(selecttree){
	case 0:
			
	
								switch(caesercount){

								case 1:
									newedit[0]->SetWindowText (m_Cedit1);



										break;
								case 2:

									newedit[1]->SetWindowText (m_Cedit2);


									break;
								case 3:
									j=0;
									for (i=0;i<26;i++)
									{
										row[j]=alpha[i];
										row[j+1]='\r';
										row[j+2]='\n';
										j=j+3;
									}
									newedit[2]->SetWindowText (CString(row));
									break;
								case 4:
									m_Cedit4=CString(cipher);

									UpdateData(false);


									break;
								case 5:



							/////////////////////////////////一下不能动zh一直到break是显示另一张图片
									MessageBox("演示完毕");
							

									GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);//就可以隐藏，为SW_SHOW可以是显示。IDC_BUTTON4
									GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);
									m_hBmpNew =	 (HBITMAP) LoadImage(NULL, "Picture\\z.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
										if( m_hBmpNew == NULL )
										{
										 AfxMessageBox("Load Image Failed");
										}
										else
										{
										  m_pic1.GetClientRect( &rectStaticClient );//得到控件的客户区
										  rectStaticClient.NormalizeRect();
										  m_size.cx=rectStaticClient.Size().cx;
										  m_size.cy=rectStaticClient.Size().cy;
										  m_size.cx = rectStaticClient.Width();    // zero based
										  m_size.cy = rectStaticClient.Height();    // zero based
										  m_pic1.ClientToScreen( &rectStaticClient );//转换到屏幕坐标
             							  ScreenToClient( &rectStaticClient);//控件屏幕坐标转换到相对于对话框的客户坐标
										  m_pt.x = rectStaticClient.left;
										  m_pt.y = rectStaticClient.top;
										  GetObject( m_hBmpNew , sizeof(BITMAP), &m_bmInfo );
										  VERIFY(m_hBmpOld = (HBITMAP)SelectObject(m_dcMem, m_hBmpNew )  );
										  offsetx= m_pt.x;
										  offsety=m_pt.y;

										  m_vbar.MoveWindow(offsetx+m_size.cx,offsety,18,m_size.cy);
										  m_hbar.MoveWindow(offsetx,offsety+m_size.cy,m_size.cx,18);
										  horz.cbSize = sizeof(SCROLLINFO);
										  horz.fMask = SIF_ALL;
										  horz.nMin = 0;
										  horz.nMax = m_bmInfo.bmWidth-m_size.cx;
										  horz.nPage =0;
										  horz.nPos = 0;
										  horz.nTrackPos=0;
										  if(m_bmInfo.bmWidth<=m_size.cx)
										  {
											if((m_size.cx-m_bmInfo.bmWidth)==0)
												offsetx= m_pt.x;
											else
												offsetx= m_pt.x+((m_size.cx-m_bmInfo.bmWidth)/2);
											m_vbar.MoveWindow(offsetx+m_bmInfo.bmWidth,offsety,18,m_size.cy);
											m_hbar.ShowWindow(false);
										  }
										 else
										  m_hbar.ShowWindow(true);
										 m_hbar.SetScrollInfo(&horz);


										 vert.cbSize = sizeof(SCROLLINFO);
										 vert.fMask = SIF_ALL;
										 vert.nMin = 0;
										 vert.nMax = m_bmInfo.bmHeight-(m_size.cy);
										 vert.nPage = 0;
										 vert.nTrackPos=0;
										 if(m_bmInfo.bmHeight<=m_size.cy)
										 {
											if((m_size.cy-m_bmInfo.bmHeight)==0)
												offsety= m_pt.y;
											else
												offsety= m_pt.y+((m_size.cy-m_bmInfo.bmHeight)/2);
											m_hbar.MoveWindow(offsetx,offsety+m_bmInfo.bmHeight,m_size.cx,18);
											m_vbar.ShowWindow(false);
										 }
										 else
										  m_vbar.ShowWindow(true);
										m_vbar.SetScrollInfo(&vert);


										InvalidateRect(&rectStaticClient);
										}

						////////////////////////////////////////////////
									//清除动态生成的控件

										newedit[0]->ShowWindow (false);
										newedit[1]->ShowWindow (false);
										newedit[2]->ShowWindow (false);
										m_Cedit1="";
										m_Cedit2="";
										m_Cedit4="";
										UpdateData(false);
										break;


											}

					break;
					//////////////////////////////////////
	case 1:




					switch(duowenzicount){

										case 1:
											duowenzi[0]->SetWindowText (m_Cedit1);



												break;
										case 2:

											duowenzi[1]->SetWindowText (m_Cedit2);
											//CString string1;
											//string1.Mid ();

											break;
										case 3:

											strncpy(str1 , m_Cedit2.GetBuffer(m_Cedit2.GetLength()) , m_Cedit2.GetLength()) ;
											j=0;
											for (i=0; i<strlen(str1);i++)
											{
												str2[j]=str1[i];
												str2[j+1]='\r';
												str2[j+2]='\n';
												str2[j+3]='\r';
												str2[j+4]='\n';
												j=j+5;
											}
											duowenzi[2]->SetWindowText (CString(str2));


											break;
										case 4:
											strncpy(str1 , m_Cedit2.GetBuffer(m_Cedit2.GetLength()) , m_Cedit2.GetLength()) ;
											j=0;
											for(i=0;i<strlen(str1);i++)
											{
												str3[j]=str1[i];
												str3[j+1]=' ';
												str3[j+2]=' ';
												str3[j+3]=' ';
												str3[j+4]=' ';
												str3[j+5]=' ';
												j=j+6;
											}
											duowenzi[3]->SetWindowText (CString(str3));
										


											break;
										case 5:
											m_Cedit4=CString(cipher);
												
											UpdateData(false);

											break;
										case 6:



									/////////////////////////////////一下不能动zh一直到break是显示另一张图片
											MessageBox("演示完毕");
									

											GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);//就可以隐藏，为SW_SHOW可以是显示。IDC_BUTTON4
											GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);
											m_hBmpNew =	 (HBITMAP) LoadImage(NULL, "Picture\\z.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
												if( m_hBmpNew == NULL )
												{
												 AfxMessageBox("Load Image Failed");
												}
												else
												{
												  m_pic1.GetClientRect( &rectStaticClient );//得到控件的客户区
												  rectStaticClient.NormalizeRect();
												  m_size.cx=rectStaticClient.Size().cx;
												  m_size.cy=rectStaticClient.Size().cy;
												  m_size.cx = rectStaticClient.Width();    // zero based
												  m_size.cy = rectStaticClient.Height();    // zero based
												  m_pic1.ClientToScreen( &rectStaticClient );//转换到屏幕坐标
             									  ScreenToClient( &rectStaticClient);//控件屏幕坐标转换到相对于对话框的客户坐标
												  m_pt.x = rectStaticClient.left;
												  m_pt.y = rectStaticClient.top;
												  GetObject( m_hBmpNew , sizeof(BITMAP), &m_bmInfo );
												  VERIFY(m_hBmpOld = (HBITMAP)SelectObject(m_dcMem, m_hBmpNew )  );
												  offsetx= m_pt.x;
												  offsety=m_pt.y;

												  m_vbar.MoveWindow(offsetx+m_size.cx,offsety,18,m_size.cy);
												  m_hbar.MoveWindow(offsetx,offsety+m_size.cy,m_size.cx,18);
												  horz.cbSize = sizeof(SCROLLINFO);
												  horz.fMask = SIF_ALL;
												  horz.nMin = 0;
												  horz.nMax = m_bmInfo.bmWidth-m_size.cx;
												  horz.nPage =0;
												  horz.nPos = 0;
												  horz.nTrackPos=0;
												  if(m_bmInfo.bmWidth<=m_size.cx)
												  {
													if((m_size.cx-m_bmInfo.bmWidth)==0)
														offsetx= m_pt.x;
													else
														offsetx= m_pt.x+((m_size.cx-m_bmInfo.bmWidth)/2);
													m_vbar.MoveWindow(offsetx+m_bmInfo.bmWidth,offsety,18,m_size.cy);
													m_hbar.ShowWindow(false);
												  }
												 else
												  m_hbar.ShowWindow(true);
												 m_hbar.SetScrollInfo(&horz);


												 vert.cbSize = sizeof(SCROLLINFO);
												 vert.fMask = SIF_ALL;
												 vert.nMin = 0;
												 vert.nMax = m_bmInfo.bmHeight-(m_size.cy);
												 vert.nPage = 0;
												 vert.nTrackPos=0;
												 if(m_bmInfo.bmHeight<=m_size.cy)
												 {
													if((m_size.cy-m_bmInfo.bmHeight)==0)
														offsety= m_pt.y;
													else
														offsety= m_pt.y+((m_size.cy-m_bmInfo.bmHeight)/2);
													m_hbar.MoveWindow(offsetx,offsety+m_bmInfo.bmHeight,m_size.cx,18);
													m_vbar.ShowWindow(false);
												 }
												 else
												  m_vbar.ShowWindow(true);
												m_vbar.SetScrollInfo(&vert);


												InvalidateRect(&rectStaticClient);
												}

								////////////////////////////////////////////////
											//清除动态生成的控件

												duowenzi[0]->ShowWindow (false);
												duowenzi[1]->ShowWindow (false);
												duowenzi[2]->ShowWindow (false);
												duowenzi[3]->ShowWindow (false);
												m_Cedit1="";
												m_Cedit2="";
												m_Cedit4="";
												UpdateData(false);
												break;


													}



		break;


	case 2:
								switch(vigenerecount){

							case 1:
								vigenere[0]->SetWindowText (m_Cedit1);



									break;
							case 2:

								vigenere[1]->SetWindowText (m_Cedit2);


								break;
							case 3:
								m_Cedit4=CString(cipher);
								UpdateData(false);




								break;
							case 4:
				/////////////////////////////////一下不能动zh一直到break是显示另一张图片
								MessageBox("演示完毕");
						

								GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);//就可以隐藏，为SW_SHOW可以是显示。IDC_BUTTON4
								GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);
								m_hBmpNew =	 (HBITMAP) LoadImage(NULL, "Picture\\z.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
									if( m_hBmpNew == NULL )
									{
									 AfxMessageBox("Load Image Failed");
									}
									else
									{
									  m_pic1.GetClientRect( &rectStaticClient );//得到控件的客户区
									  rectStaticClient.NormalizeRect();
									  m_size.cx=rectStaticClient.Size().cx;
									  m_size.cy=rectStaticClient.Size().cy;
									  m_size.cx = rectStaticClient.Width();    // zero based
									  m_size.cy = rectStaticClient.Height();    // zero based
									  m_pic1.ClientToScreen( &rectStaticClient );//转换到屏幕坐标
             						  ScreenToClient( &rectStaticClient);//控件屏幕坐标转换到相对于对话框的客户坐标
									  m_pt.x = rectStaticClient.left;
									  m_pt.y = rectStaticClient.top;
									  GetObject( m_hBmpNew , sizeof(BITMAP), &m_bmInfo );
									  VERIFY(m_hBmpOld = (HBITMAP)SelectObject(m_dcMem, m_hBmpNew )  );
									  offsetx= m_pt.x;
									  offsety=m_pt.y;

									  m_vbar.MoveWindow(offsetx+m_size.cx,offsety,18,m_size.cy);
									  m_hbar.MoveWindow(offsetx,offsety+m_size.cy,m_size.cx,18);
									  horz.cbSize = sizeof(SCROLLINFO);
									  horz.fMask = SIF_ALL;
									  horz.nMin = 0;
									  horz.nMax = m_bmInfo.bmWidth-m_size.cx;
									  horz.nPage =0;
									  horz.nPos = 0;
									  horz.nTrackPos=0;
									  if(m_bmInfo.bmWidth<=m_size.cx)
									  {
										if((m_size.cx-m_bmInfo.bmWidth)==0)
											offsetx= m_pt.x;
										else
											offsetx= m_pt.x+((m_size.cx-m_bmInfo.bmWidth)/2);
										m_vbar.MoveWindow(offsetx+m_bmInfo.bmWidth,offsety,18,m_size.cy);
										m_hbar.ShowWindow(false);
									  }
									 else
									  m_hbar.ShowWindow(true);
									 m_hbar.SetScrollInfo(&horz);


									 vert.cbSize = sizeof(SCROLLINFO);
									 vert.fMask = SIF_ALL;
									 vert.nMin = 0;
									 vert.nMax = m_bmInfo.bmHeight-(m_size.cy);
									 vert.nPage = 0;
									 vert.nTrackPos=0;
									 if(m_bmInfo.bmHeight<=m_size.cy)
									 {
										if((m_size.cy-m_bmInfo.bmHeight)==0)
											offsety= m_pt.y;
										else
											offsety= m_pt.y+((m_size.cy-m_bmInfo.bmHeight)/2);
										m_hbar.MoveWindow(offsetx,offsety+m_bmInfo.bmHeight,m_size.cx,18);
										m_vbar.ShowWindow(false);
									 }
									 else
									  m_vbar.ShowWindow(true);
									m_vbar.SetScrollInfo(&vert);


									InvalidateRect(&rectStaticClient);
									}

					////////////////////////////////////////////////
								//清除动态生成的控件

									vigenere[0]->ShowWindow (false);
									vigenere[1]->ShowWindow (false);
									
									m_Cedit1="";
									m_Cedit2="";
									m_Cedit4="";
									UpdateData(false);
									break;
										}


							
							
							
							
							
							
		
		
		
		break;
	case 3:


		switch(playfaircountnext){
					

						case 1:

						editplayfair[0]->SetWindowText(m_Cedit1);



								break;
						case 2:

							editplayfair[1]->SetWindowText(m_Cedit2);




							break;


						case 3://显示密钥矩阵

							for( i=0; i<strlen(key26) ; i++)//把所输入的密钥转化为大写字母
							{
								if(key26[i]>='a')
									key26[i]=key26[i]-('a'-'A');
								if(key26[i]=='J')
									key26[i]='I';
							}

							p=0;
							for(k=0;k<strlen(key26);k++)//把密钥中的字母填入到矩阵中，并把该字母标记为已用
							{
								for(t=0;t<25;t++)
								{
									i=0;
									j=0;
									if(key26[k]==letters[t] && flag[t]==0)
									{
										keymatrix[p]=letters[t];
										flag[t]=1;
										p++;
									}
								}
							}

							for( k=0;k<25;k++)//按字母表顺序把未用字母依次填入到矩阵中
							{
								if(flag[k]==0)
								{
									keymatrix[p]=letters[k];
									p++;
								}
							}

							j=0;
							for(i=0;i<26;i++)
							{
								
								if(i==4 ||i==9 || i==14|| i==19|| i==24)
								{
									keymatrixmo[j]=keymatrix[i];
									keymatrixmo[j+1]='\r';
									keymatrixmo[j+2]='\n';
									j=j+3;
								}
								else
								{
									keymatrixmo[j]=keymatrix[i];
									keymatrixmo[j+1]=' ';
									j=j+2;
								}
								
							}

					
							editplayfair[2]->SetWindowText(CString(keymatrixmo));

							break;




						case 4:
	
                            //用于想静态编辑框显示密文

							m_Cedit4=CString(cipher);
							UpdateData(false);




							break;

						case 5:

								

			/////////////////////////////////一下不能动zh一直到break是显示另一张图片
						MessageBox("演示完毕");
		
						GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);//就可以隐藏，为SW_SHOW可以是显示。IDC_BUTTON4
						GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);
	
						m_hBmpNew =	 (HBITMAP) LoadImage(NULL, "Picture\\z.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
						if( m_hBmpNew == NULL )
						{
						 AfxMessageBox("Load Image Failed");
						}
						else
						{
						  m_pic1.GetClientRect( &rectStaticClient );//得到控件的客户区
						  rectStaticClient.NormalizeRect();
						  m_size.cx=rectStaticClient.Size().cx;
						  m_size.cy=rectStaticClient.Size().cy;
						  m_size.cx = rectStaticClient.Width();    // zero based
						  m_size.cy = rectStaticClient.Height();    // zero based
						  m_pic1.ClientToScreen( &rectStaticClient );//转换到屏幕坐标
             			  ScreenToClient( &rectStaticClient);//控件屏幕坐标转换到相对于对话框的客户坐标
						  m_pt.x = rectStaticClient.left;
						  m_pt.y = rectStaticClient.top;
						  GetObject( m_hBmpNew , sizeof(BITMAP), &m_bmInfo );
						  VERIFY(m_hBmpOld = (HBITMAP)SelectObject(m_dcMem, m_hBmpNew )  );
						  offsetx= m_pt.x;
						  offsety=m_pt.y;

						  m_vbar.MoveWindow(offsetx+m_size.cx,offsety,18,m_size.cy);
						  m_hbar.MoveWindow(offsetx,offsety+m_size.cy,m_size.cx,18);
						  horz.cbSize = sizeof(SCROLLINFO);
						  horz.fMask = SIF_ALL;
						  horz.nMin = 0;
						  horz.nMax = m_bmInfo.bmWidth-m_size.cx;
						  horz.nPage =0;
						  horz.nPos = 0;
						  horz.nTrackPos=0;
						  if(m_bmInfo.bmWidth<=m_size.cx)
						  {
							if((m_size.cx-m_bmInfo.bmWidth)==0)
								offsetx= m_pt.x;
							else
								offsetx= m_pt.x+((m_size.cx-m_bmInfo.bmWidth)/2);
							m_vbar.MoveWindow(offsetx+m_bmInfo.bmWidth,offsety,18,m_size.cy);
							m_hbar.ShowWindow(false);
						  }
						 else
						  m_hbar.ShowWindow(true);
						 m_hbar.SetScrollInfo(&horz);


						 vert.cbSize = sizeof(SCROLLINFO);
						 vert.fMask = SIF_ALL;
						 vert.nMin = 0;
						 vert.nMax = m_bmInfo.bmHeight-(m_size.cy);
						 vert.nPage = 0;
						 vert.nTrackPos=0;
						 if(m_bmInfo.bmHeight<=m_size.cy)
						 {
							if((m_size.cy-m_bmInfo.bmHeight)==0)
								offsety= m_pt.y;
							else
								offsety= m_pt.y+((m_size.cy-m_bmInfo.bmHeight)/2);
							m_hbar.MoveWindow(offsetx,offsety+m_bmInfo.bmHeight,m_size.cx,18);
							m_vbar.ShowWindow(false);
						 }
						 else
						  m_vbar.ShowWindow(true);
						m_vbar.SetScrollInfo(&vert);


						InvalidateRect(&rectStaticClient);
						}

////////////////////////////////////////////////
			//清除动态生成的控件

						editplayfair[0]->ShowWindow (false);
						editplayfair[1]->ShowWindow (false);
						editplayfair[2]->ShowWindow (false);
						m_Cedit4="";
						m_Cedit1="";
						m_Cedit2="";


						UpdateData(false);








							break;
								
							}


		break;
		case 4:






			break;

		case 5:
							switch(affinecount){
							case 1:
								affine[0]->SetWindowText(m_Cedit1);


								break;

							case 2:
									affine[1]->SetWindowText(CString(key1_temp));

								break;
							case 3:
									affine[2]->SetWindowText(CString(key2));




								break;
							case 4:
									affine[3]->SetWindowText(CString(affine_tmp));

								break;
							case 5:
									m_Cedit4=CString(cipher);
									UpdateData(false);





								break;
							case 6:
												MessageBox("演示完毕");
						
						GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);//就可以隐藏，为SW_SHOW可以是显示。IDC_BUTTON4
						GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);
					
						m_hBmpNew =	 (HBITMAP) LoadImage(NULL, "Picture\\z.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
										if( m_hBmpNew == NULL )
										{
										 AfxMessageBox("Load Image Failed");
										}
										else
										{
										  m_pic1.GetClientRect( &rectStaticClient );//得到控件的客户区
										  rectStaticClient.NormalizeRect();
										  m_size.cx=rectStaticClient.Size().cx;
										  m_size.cy=rectStaticClient.Size().cy;
										  m_size.cx = rectStaticClient.Width();    // zero based
										  m_size.cy = rectStaticClient.Height();    // zero based
										  m_pic1.ClientToScreen( &rectStaticClient );//转换到屏幕坐标
             							  ScreenToClient( &rectStaticClient);//控件屏幕坐标转换到相对于对话框的客户坐标
										  m_pt.x = rectStaticClient.left;
										  m_pt.y = rectStaticClient.top;
										  GetObject( m_hBmpNew , sizeof(BITMAP), &m_bmInfo );
										  VERIFY(m_hBmpOld = (HBITMAP)SelectObject(m_dcMem, m_hBmpNew )  );
										  offsetx= m_pt.x;
										  offsety=m_pt.y;

										  m_vbar.MoveWindow(offsetx+m_size.cx,offsety,18,m_size.cy);
										  m_hbar.MoveWindow(offsetx,offsety+m_size.cy,m_size.cx,18);
										  horz.cbSize = sizeof(SCROLLINFO);
										  horz.fMask = SIF_ALL;
										  horz.nMin = 0;
										  horz.nMax = m_bmInfo.bmWidth-m_size.cx;
										  horz.nPage =0;
										  horz.nPos = 0;
										  horz.nTrackPos=0;
										  if(m_bmInfo.bmWidth<=m_size.cx)
										  {
											if((m_size.cx-m_bmInfo.bmWidth)==0)
												offsetx= m_pt.x;
											else
												offsetx= m_pt.x+((m_size.cx-m_bmInfo.bmWidth)/2);
											m_vbar.MoveWindow(offsetx+m_bmInfo.bmWidth,offsety,18,m_size.cy);
											m_hbar.ShowWindow(false);
										  }
										 else
										  m_hbar.ShowWindow(true);
										 m_hbar.SetScrollInfo(&horz);


										 vert.cbSize = sizeof(SCROLLINFO);
										 vert.fMask = SIF_ALL;
										 vert.nMin = 0;
										 vert.nMax = m_bmInfo.bmHeight-(m_size.cy);
										 vert.nPage = 0;
										 vert.nTrackPos=0;
										 if(m_bmInfo.bmHeight<=m_size.cy)
										 {
											if((m_size.cy-m_bmInfo.bmHeight)==0)
												offsety= m_pt.y;
											else
												offsety= m_pt.y+((m_size.cy-m_bmInfo.bmHeight)/2);
											m_hbar.MoveWindow(offsetx,offsety+m_bmInfo.bmHeight,m_size.cx,18);
											m_vbar.ShowWindow(false);
										 }
										 else
										  m_vbar.ShowWindow(true);
										m_vbar.SetScrollInfo(&vert);


										InvalidateRect(&rectStaticClient);
										}

				////////////////////////////////////////////////
							//清除动态生成的控件

										affine[0]->ShowWindow (false);
										affine[1]->ShowWindow (false);
										affine[2]->ShowWindow (false);
										affine[3]->ShowWindow (false);
										m_Cedit4="";
										m_Cedit1="";
										m_Cedit2="";


										UpdateData(false);

								break;

							}
				break;
			case 6:
									switch(rc4count){

									case 1:
										rc4[0]->SetWindowText(m_Cedit1);

										break;
									case 2:
										rc4[1]->SetWindowText(m_Cedit2);


										break;
									case 3:
										rc4[2]->SetWindowText(CString(keystream));

										break;
									case 4:
										m_Cedit4=CString(cipher);
									UpdateData(false);







										break;
									case 5:
						MessageBox("演示完毕");
						
						GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);//就可以隐藏，为SW_SHOW可以是显示。IDC_BUTTON4
						GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);
					
						m_hBmpNew =	 (HBITMAP) LoadImage(NULL, "Picture\\z.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
										if( m_hBmpNew == NULL )
										{
										 AfxMessageBox("Load Image Failed");
										}
										else
										{
										  m_pic1.GetClientRect( &rectStaticClient );//得到控件的客户区
										  rectStaticClient.NormalizeRect();
										  m_size.cx=rectStaticClient.Size().cx;
										  m_size.cy=rectStaticClient.Size().cy;
										  m_size.cx = rectStaticClient.Width();    // zero based
										  m_size.cy = rectStaticClient.Height();    // zero based
										  m_pic1.ClientToScreen( &rectStaticClient );//转换到屏幕坐标
             							  ScreenToClient( &rectStaticClient);//控件屏幕坐标转换到相对于对话框的客户坐标
										  m_pt.x = rectStaticClient.left;
										  m_pt.y = rectStaticClient.top;
										  GetObject( m_hBmpNew , sizeof(BITMAP), &m_bmInfo );
										  VERIFY(m_hBmpOld = (HBITMAP)SelectObject(m_dcMem, m_hBmpNew )  );
										  offsetx= m_pt.x;
										  offsety=m_pt.y;

										  m_vbar.MoveWindow(offsetx+m_size.cx,offsety,18,m_size.cy);
										  m_hbar.MoveWindow(offsetx,offsety+m_size.cy,m_size.cx,18);
										  horz.cbSize = sizeof(SCROLLINFO);
										  horz.fMask = SIF_ALL;
										  horz.nMin = 0;
										  horz.nMax = m_bmInfo.bmWidth-m_size.cx;
										  horz.nPage =0;
										  horz.nPos = 0;
										  horz.nTrackPos=0;
										  if(m_bmInfo.bmWidth<=m_size.cx)
										  {
											if((m_size.cx-m_bmInfo.bmWidth)==0)
												offsetx= m_pt.x;
											else
												offsetx= m_pt.x+((m_size.cx-m_bmInfo.bmWidth)/2);
											m_vbar.MoveWindow(offsetx+m_bmInfo.bmWidth,offsety,18,m_size.cy);
											m_hbar.ShowWindow(false);
										  }
										 else
										  m_hbar.ShowWindow(true);
										 m_hbar.SetScrollInfo(&horz);


										 vert.cbSize = sizeof(SCROLLINFO);
										 vert.fMask = SIF_ALL;
										 vert.nMin = 0;
										 vert.nMax = m_bmInfo.bmHeight-(m_size.cy);
										 vert.nPage = 0;
										 vert.nTrackPos=0;
										 if(m_bmInfo.bmHeight<=m_size.cy)
										 {
											if((m_size.cy-m_bmInfo.bmHeight)==0)
												offsety= m_pt.y;
											else
												offsety= m_pt.y+((m_size.cy-m_bmInfo.bmHeight)/2);
											m_hbar.MoveWindow(offsetx,offsety+m_bmInfo.bmHeight,m_size.cx,18);
											m_vbar.ShowWindow(false);
										 }
										 else
										  m_vbar.ShowWindow(true);
										m_vbar.SetScrollInfo(&vert);


										InvalidateRect(&rectStaticClient);
										}

				////////////////////////////////////////////////
							//清除动态生成的控件

										rc4[0]->ShowWindow (false);
										rc4[1]->ShowWindow (false);
										rc4[2]->ShowWindow (false);
										//affine[3]->ShowWindow (false);
										m_Cedit4="";
										m_Cedit1="";
										m_Cedit2="";


										UpdateData(false);





										break;




									}














				break;

			case 7:


							
								//
								switch(descount){


								case 1:

									des[0]->SetWindowText (m_Cedit2);
									desnext=false;

										break;
								case 2:
									MessageBox("请点击: 交换选择表1 ");
									//descount=descount+1;
									desnext=false;

									break;
								case 3:
									//memcpy(tempt,kl_tmp,28);
									for (i=0;i<28;i++)
									{
										tempt[i]= kl_tmp[i]?'1':'0';
									}
									//MessageBox(tempt);
									des[1]->SetWindowText (CString(tempt));
									for (i=0;i<28;i++)
									{
										tempt[i]= kr_tmp[i]?'1':'0';
									}
									
									des[2]->SetWindowText (CString(tempt));
									descount=descount+1;
									desnext=false;


									break;
								case 4://显示左28位右28位
									//memcpy(tempt,kl_tmp,28);
								
									desnext=false;

									break;
								case 5://移位后显示
									for (i=0;i<28;i++)
									{
										tempt[i]= kl[i]?'1':'0';
									}	
									des[3]->SetWindowText (CString(tempt));
									for (i=0;i<28;i++)
									{
										tempt[i]= kr[i]?'1':'0';
									}
									des[4]->SetWindowText (CString(tempt));
									descount=descount+1;
									desnext=false;

									break;
								case 6:

										desnext=false;
									
									break;
								case 7:	
									MessageBox("请点击: 交换选择表2 ");
									desnext=false;
									break;
								case 8:	//显示48位子密钥					
									for (i=0;i<48;i++)
									{
										tempt2[i]= subkey[i]?'1':'0';
									}	
									
									
								    des[5]->SetWindowText (CString(tempt2));
									desnext=false;
									break;
								case 9:


										des[0]->ShowWindow (false);
										des[1]->ShowWindow (false);
										des[2]->ShowWindow (false);
										des[3]->ShowWindow (false);
										des[4]->ShowWindow (false);
										des[5]->ShowWindow (false);

									desbutton[0]->ShowWindow(false);
									desbutton[1]->ShowWindow(false);
										desnext=true;




							/////////////////////////////////一下不能动zh一直到break是显示另一张图片
								//	MessageBox("演示完毕");
							


									m_hBmpNew =	 (HBITMAP) LoadImage(NULL, "Picture\\DES_2.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
										if( m_hBmpNew == NULL )
										{
										 AfxMessageBox("Load Image Failed");
										}
										else
										{
										  m_pic1.GetClientRect( &rectStaticClient );//得到控件的客户区
										  rectStaticClient.NormalizeRect();
										  m_size.cx=rectStaticClient.Size().cx;
										  m_size.cy=rectStaticClient.Size().cy;
										  m_size.cx = rectStaticClient.Width();    // zero based
										  m_size.cy = rectStaticClient.Height();    // zero based
										  m_pic1.ClientToScreen( &rectStaticClient );//转换到屏幕坐标
             							  ScreenToClient( &rectStaticClient);//控件屏幕坐标转换到相对于对话框的客户坐标
										  m_pt.x = rectStaticClient.left;
										  m_pt.y = rectStaticClient.top;
										  GetObject( m_hBmpNew , sizeof(BITMAP), &m_bmInfo );
										  VERIFY(m_hBmpOld = (HBITMAP)SelectObject(m_dcMem, m_hBmpNew )  );
										  offsetx= m_pt.x;
										  offsety=m_pt.y;

										  m_vbar.MoveWindow(offsetx+m_size.cx,offsety,18,m_size.cy);
										  m_hbar.MoveWindow(offsetx,offsety+m_size.cy,m_size.cx,18);
										  horz.cbSize = sizeof(SCROLLINFO);
										  horz.fMask = SIF_ALL;
										  horz.nMin = 0;
										  horz.nMax = m_bmInfo.bmWidth-m_size.cx;
										  horz.nPage =0;
										  horz.nPos = 0;
										  horz.nTrackPos=0;
										  if(m_bmInfo.bmWidth<=m_size.cx)
										  {
											if((m_size.cx-m_bmInfo.bmWidth)==0)
												offsetx= m_pt.x;
											else
												offsetx= m_pt.x+((m_size.cx-m_bmInfo.bmWidth)/2);
											m_vbar.MoveWindow(offsetx+m_bmInfo.bmWidth,offsety,18,m_size.cy);
											m_hbar.ShowWindow(false);
										  }
										 else
										  m_hbar.ShowWindow(true);
										 m_hbar.SetScrollInfo(&horz);


										 vert.cbSize = sizeof(SCROLLINFO);
										 vert.fMask = SIF_ALL;
										 vert.nMin = 0;
										 vert.nMax = m_bmInfo.bmHeight-(m_size.cy);
										 vert.nPage = 0;
										 vert.nTrackPos=0;
										 if(m_bmInfo.bmHeight<=m_size.cy)
										 {
											if((m_size.cy-m_bmInfo.bmHeight)==0)
												offsety= m_pt.y;
											else
												offsety= m_pt.y+((m_size.cy-m_bmInfo.bmHeight)/2);
											m_hbar.MoveWindow(offsetx,offsety+m_bmInfo.bmHeight,m_size.cx,18);
											m_vbar.ShowWindow(false);
										 }
										 else
										  m_vbar.ShowWindow(true);
										m_vbar.SetScrollInfo(&vert);


										InvalidateRect(&rectStaticClient);
										}
														
									des[6]=new CEdit() ;
										des[6]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(531,32,718,60) , this , IDC_EDIT2) ;


									des[7]=new CEdit() ;
										des[7]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(758,32,860,58) , this , IDC_EDIT2) ;

									des[8]=new CEdit() ;
										des[8]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(529,139,721,167) , this , IDC_EDIT2) ;

									des[9]=new CEdit() ;
										des[9]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(423,194,578,215) , this , IDC_EDIT2) ;
								des[10]=new CEdit() ;
										des[10]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(669,193,823,215) , this , IDC_EDIT2) ;

									des[11]=new CEdit() ;
										des[11]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(659,276,831,299) , this , IDC_EDIT2) ;

									des[12]=new CEdit() ;
										des[12]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(488,503,640,527) , this , IDC_EDIT2) ;

									des[13]=new CEdit() ;
										des[13]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(669,506,827,526) , this , IDC_EDIT2) ;

									des[14]=new CEdit() ;
										des[14]->Create( ES_MULTILINE |WS_CHILD|WS_VISIBLE |WS_TABSTOP|WS_BORDER, CRect(556,546,747,574) , this , IDC_EDIT2) ;



						
									desbutton[2]->ShowWindow (true);
									desbutton[3]->ShowWindow (true);
									desbutton[4]->ShowWindow (true);


									desnext=true;
				//	desbutton[6]->Create( "交换选择列表 1", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(598,84,657,159), this, IDC_BTNCHANGESELECT1 );

				//	desbutton[7]->Create( "交换选择列表 1", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(598,84,657,159), this, IDC_BTNCHANGESELECT1 );





						////////////////////////////////////////////////
									//清除动态生成的控件
/*
										newedit[0]->ShowWindow (false);
										newedit[1]->ShowWindow (false);
										newedit[2]->ShowWindow (false);
										m_Cedit1="";
										m_Cedit2="";
										m_Cedit4="";
										UpdateData(false);
										*/
										break;
										case 10://显示明文比特流与密钥比特
											for (i=0;i<48;i++)
											{
												tempt2[i]= subkey[i]?'1':'0';
											}

											for (i=0;i<64;i++)
											{
												tempt64[i]=plain64[i]?'1':'0';
											}
											des[6]->SetWindowText (CString(tempt64));
											des[7]->SetWindowText (CString(tempt2) );
											descount=descount+1;
											desnext=true;

											break;
										case 11:

											desnext=true;

											break;
										case 12:	
											//des[7]->SetWindowText (a);
											//要求显示置换表
											MessageBox("请点击 置换表 ");
											desnext=true;
					
											break;
										case 13:	//置换之后的明文块 plain64
											for (i=0;i<64;i++)
											{
												tempt64[i]=plain64_ip[i]?'1':'0';
											}
											des[8]->SetWindowText (CString(tempt64));
											desnext=true;

					
											
											break;
										case 14:	//显示左32位,右32位明文
											for (i=0;i<32;i++)
											{
												tempt32a[i]=plainleft32[i]?'1':'0';
											}

											for(i=0;i<32;i++)
											{
												tempt32b[i]=plainright32[i]?'1':'0';

											}
											
											des[9]->SetWindowText (CString(tempt32a));
											des[10]->SetWindowText (CString(tempt32b));
											descount=descount+1;
											desnext=true;

											
											break;
										case 15:	
											
											desnext=true;
											//descount=descount+1;


											break;
										case 16:	
										//	des[10]->SetWindowText (d);
											MessageBox("请点击 扩充盒 E盒");
											desnext=true;

									
											
											break;
										case 17:	//显示扩充后的明文
											for (i=0;i<48;i++)
											{
												tempt2[i]=plain48[i]?'1':'0';
											}
											des[11]->SetWindowText (CString(tempt2));
											desnext=true;

											break;
				
										case 18:	
											//des[13]->SetWindowText (c);
											MessageBox("请点击 置换盒 P盒");
											desnext=true;
	
											break;
										case 19:	//左32右32位密文
											for (i=0;i<32;i++)
											{
												tempt32a[i]=cipherleft32[i]?'1':'0';
											}
											for(i=0;i<32;i++)
											{
												tempt32b[i]=cipherright32[i]?'1':'0';
											}
											des[12]->SetWindowText (CString(tempt32a));
											des[13]->SetWindowText (CString(tempt32b));
											descount=descount+1;
											desnext=true;
											break;

										case 20:	
											
											desnext=true;
											//descount=descount+1;


											break;
										case 21: //一轮后产生的64位密文
											for (i=0;i<64;i++)
											{
												tempt64[i]=cipher64[i]?'1':'0';
											}
											
											des[14]->SetWindowText (CString(tempt64));
											desnext=true;

											break;
								


										case 22:	
												m_Cedit4=CString(cipher);
												
												UpdateData(false);
												desnext=true;

											
											
											
											
											
											break;
										case 23:	
										MessageBox("演示完毕");
						
										GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);//就可以隐藏，为SW_SHOW可以是显示。IDC_BUTTON4
										GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);
									
										m_hBmpNew =	 (HBITMAP) LoadImage(NULL, "Picture\\z.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
										if( m_hBmpNew == NULL )
										{
										 AfxMessageBox("Load Image Failed");
										}
										else
										{
										  m_pic1.GetClientRect( &rectStaticClient );//得到控件的客户区
										  rectStaticClient.NormalizeRect();
										  m_size.cx=rectStaticClient.Size().cx;
										  m_size.cy=rectStaticClient.Size().cy;
										  m_size.cx = rectStaticClient.Width();    // zero based
										  m_size.cy = rectStaticClient.Height();    // zero based
										  m_pic1.ClientToScreen( &rectStaticClient );//转换到屏幕坐标
             							  ScreenToClient( &rectStaticClient);//控件屏幕坐标转换到相对于对话框的客户坐标
										  m_pt.x = rectStaticClient.left;
										  m_pt.y = rectStaticClient.top;
										  GetObject( m_hBmpNew , sizeof(BITMAP), &m_bmInfo );
										  VERIFY(m_hBmpOld = (HBITMAP)SelectObject(m_dcMem, m_hBmpNew )  );
										  offsetx= m_pt.x;
										  offsety=m_pt.y;

										  m_vbar.MoveWindow(offsetx+m_size.cx,offsety,18,m_size.cy);
										  m_hbar.MoveWindow(offsetx,offsety+m_size.cy,m_size.cx,18);
										  horz.cbSize = sizeof(SCROLLINFO);
										  horz.fMask = SIF_ALL;
										  horz.nMin = 0;
										  horz.nMax = m_bmInfo.bmWidth-m_size.cx;
										  horz.nPage =0;
										  horz.nPos = 0;
										  horz.nTrackPos=0;
										  if(m_bmInfo.bmWidth<=m_size.cx)
										  {
											if((m_size.cx-m_bmInfo.bmWidth)==0)
												offsetx= m_pt.x;
											else
												offsetx= m_pt.x+((m_size.cx-m_bmInfo.bmWidth)/2);
											m_vbar.MoveWindow(offsetx+m_bmInfo.bmWidth,offsety,18,m_size.cy);
											m_hbar.ShowWindow(false);
										  }
										 else
										  m_hbar.ShowWindow(true);
										 m_hbar.SetScrollInfo(&horz);


										 vert.cbSize = sizeof(SCROLLINFO);
										 vert.fMask = SIF_ALL;
										 vert.nMin = 0;
										 vert.nMax = m_bmInfo.bmHeight-(m_size.cy);
										 vert.nPage = 0;
										 vert.nTrackPos=0;
										 if(m_bmInfo.bmHeight<=m_size.cy)
										 {
											if((m_size.cy-m_bmInfo.bmHeight)==0)
												offsety= m_pt.y;
											else
												offsety= m_pt.y+((m_size.cy-m_bmInfo.bmHeight)/2);
											m_hbar.MoveWindow(offsetx,offsety+m_bmInfo.bmHeight,m_size.cx,18);
											m_vbar.ShowWindow(false);
										 }
										 else
										  m_vbar.ShowWindow(true);
										m_vbar.SetScrollInfo(&vert);


										InvalidateRect(&rectStaticClient);
										}

				////////////////////////////////////////////////
							//清除动态生成的控件

										des[6]->ShowWindow (false);
										des[7]->ShowWindow (false);
										des[8]->ShowWindow (false);
										des[9]->ShowWindow (false);
										
										des[10]->ShowWindow (false);
										des[11]->ShowWindow (false);
										des[12]->ShowWindow (false);
										des[13]->ShowWindow (false);
										des[14]->ShowWindow (false);
										desbutton[2]->ShowWindow (false);
										desbutton[3]->ShowWindow (false);
										//desbutton[4]->ShowWindow (false);
										desbutton[4]->ShowWindow (false);

										m_Cedit4="";
										m_Cedit1="";
										m_Cedit2="";
										desnext=false;


										UpdateData(false);							
											break;
											}



				break;//最大的case 后面可以继续接case
	case 8:
									switch(ideacount){
									case 1:
										for(i=0;i<64;i++)
											tempt64[i]=keyblock[i]?'1':'0';
										idea[0]->SetWindowText (CString(tempt64));

										break;
									case 2:
										for(i=0;i<64;i++)
											tempt16[i]=cipher16a[i]?'1':'0';
										idea[1]->SetWindowText (CString(tempt16));
										for(i=0;i<64;i++)
											tempt16[i]=cipher16b[i]?'1':'0';
										idea[2]->SetWindowText (CString(tempt16));
										for(i=0;i<64;i++)
											tempt16[i]=cipher16c[i]?'1':'0';
										idea[3]->SetWindowText (CString(tempt16));
										for(i=0;i<64;i++)
											tempt16[i]=cipher16d[i]?'1':'0';
										idea[4]->SetWindowText (CString(tempt16));

										break;
									case 3:
										m_Cedit4=CString(cipher);
										UpdateData(false);



										break;
									case 4:
										MessageBox("演示完毕");
						
										GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);//就可以隐藏，为SW_SHOW可以是显示。IDC_BUTTON4
										GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);
									
										m_hBmpNew =	 (HBITMAP) LoadImage(NULL, "Picture\\z.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
										if( m_hBmpNew == NULL )
										{
										 AfxMessageBox("Load Image Failed");
										}
										else
										{
										  m_pic1.GetClientRect( &rectStaticClient );//得到控件的客户区
										  rectStaticClient.NormalizeRect();
										  m_size.cx=rectStaticClient.Size().cx;
										  m_size.cy=rectStaticClient.Size().cy;
										  m_size.cx = rectStaticClient.Width();    // zero based
										  m_size.cy = rectStaticClient.Height();    // zero based
										  m_pic1.ClientToScreen( &rectStaticClient );//转换到屏幕坐标
             							  ScreenToClient( &rectStaticClient);//控件屏幕坐标转换到相对于对话框的客户坐标
										  m_pt.x = rectStaticClient.left;
										  m_pt.y = rectStaticClient.top;
										  GetObject( m_hBmpNew , sizeof(BITMAP), &m_bmInfo );
										  VERIFY(m_hBmpOld = (HBITMAP)SelectObject(m_dcMem, m_hBmpNew )  );
										  offsetx= m_pt.x;
										  offsety=m_pt.y;

										  m_vbar.MoveWindow(offsetx+m_size.cx,offsety,18,m_size.cy);
										  m_hbar.MoveWindow(offsetx,offsety+m_size.cy,m_size.cx,18);
										  horz.cbSize = sizeof(SCROLLINFO);
										  horz.fMask = SIF_ALL;
										  horz.nMin = 0;
										  horz.nMax = m_bmInfo.bmWidth-m_size.cx;
										  horz.nPage =0;
										  horz.nPos = 0;
										  horz.nTrackPos=0;
										  if(m_bmInfo.bmWidth<=m_size.cx)
										  {
											if((m_size.cx-m_bmInfo.bmWidth)==0)
												offsetx= m_pt.x;
											else
												offsetx= m_pt.x+((m_size.cx-m_bmInfo.bmWidth)/2);
											m_vbar.MoveWindow(offsetx+m_bmInfo.bmWidth,offsety,18,m_size.cy);
											m_hbar.ShowWindow(false);
										  }
										 else
										  m_hbar.ShowWindow(true);
										 m_hbar.SetScrollInfo(&horz);


										 vert.cbSize = sizeof(SCROLLINFO);
										 vert.fMask = SIF_ALL;
										 vert.nMin = 0;
										 vert.nMax = m_bmInfo.bmHeight-(m_size.cy);
										 vert.nPage = 0;
										 vert.nTrackPos=0;
										 if(m_bmInfo.bmHeight<=m_size.cy)
										 {
											if((m_size.cy-m_bmInfo.bmHeight)==0)
												offsety= m_pt.y;
											else
												offsety= m_pt.y+((m_size.cy-m_bmInfo.bmHeight)/2);
											m_hbar.MoveWindow(offsetx,offsety+m_bmInfo.bmHeight,m_size.cx,18);
											m_vbar.ShowWindow(false);
										 }
										 else
										  m_vbar.ShowWindow(true);
										m_vbar.SetScrollInfo(&vert);


										InvalidateRect(&rectStaticClient);
										}
										idea[0]->ShowWindow (false);
										idea[1]->ShowWindow (false);
										idea[2]->ShowWindow (false);
										idea[3]->ShowWindow (false);
										idea[4]->ShowWindow (false);

										m_Cedit4="";
										m_Cedit1="";
										m_Cedit2="";


										UpdateData(false);	





										break;

									}





					break;
	case 9:
									switch(rsacount){
									case 1:
										rsa[0]->SetWindowText ("FD2655F01F84B4F9911C6762249DB38EAFEA1EFF3C4845803714563C522B876453405EBD75C986D013F211F9C0A9405872C09C93417FE172AD3F0E2116B066D292E362283AF1EDED6D53C63DBCB762591C1147E5B8A802AADCC5D2B53A47DA6699F29352411BD831802D9820F8C828809FECFEE66EC3C709E2D4A2079F");



										break;
									case 2:
										rsa[1]->SetWindowText ("BFCB93A3EC3F78B04597E63DD6A49D6D013C7FC94A69B31C89A8D346CC9B7DCA520786EFD03742821F671EA21C5AC67337D52F9C15118EA96F6D4FBA507910122B2CE338728F0FE91010CF140060E22DA456497B8F1A3DDA8BFA264AA4B8A40E3A09CAADD338BFD44791DBA3A3C7F05B46BFEE67C772ED80DD6F77D6AD");




										break;
									case 3:
										rsa[2]->SetWindowText ("1F185829C54B78CB8398852CCC540713326E165F07C6978952CC9F7DE5C88B2983B4DFFE0F657B034FCFD93BBF81711075ABA7618B0D7B62CA3BA1BF4F1B72C6F697C7A538F0FD7A2B7077FBA0B33A63F19444E6924F8101C4663E4BB5F98EE5D7D8A64E786E5B8C70B30CAB6D4AD88081C4C305C819EE732DF588AC7D7761406E1521E559DBCCE2014AD54934CE4D042635D2C0F795");




										break;
									case 4:
										rsa[3]->SetWindowText ("3DF594ADB6FF7ABDF4795F682FF63EC616AF099356FE03FB763980BD6D4B26D6FA9D6ACF81E1C5C0CD78B1A75F2A47CA8C030197DB703D613E5B93726F0CFF81B6FA2198A7F27C58A93804083766BE046F0BDEDF626923CE4C8FEE52B45615F305180E7274E0A76640945662A4436576FAB1DB7132BCA76779E2CD166F423C7958C257C021BA76D33866CFA8F292429F03CFDE0069A3");




										break;
									case 5:
										rsa[4]->SetWindowText ("B548758E15EAFE878D3F447970E5BB95C2FEA97FBD920A009E2AAE350966FA6EE147632061F6A744D6FBD4D5E2E72E367ABB1DF9A9AE7CD9DB2B4CF1A3D1BFA205C15E720D13E33706227F00B4DB261DFBE29E21E5BD83E7EF97E67BAD4E092CE2B56581E913C4610FD227D9D6B2C13A53933B0881BE2E2CDC7DACA3F7AEE7DDA714883E351529B1D0FDEB60588AF27D74BFD49D7EA1");




										break;
									case 6:




										rsa[0]->ShowWindow (false);
										rsa[1]->ShowWindow (false);
										rsa[2]->ShowWindow (false);
										rsa[3]->ShowWindow (false);
										rsa[4]->ShowWindow (false);
									//des[5]->ShowWindow (false);




							/////////////////////////////////一下不能动zh一直到break是显示另一张图片
								//	MessageBox("演示完毕");
							


									m_hBmpNew =	 (HBITMAP) LoadImage(NULL, "Picture\\RSA_2.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
										if( m_hBmpNew == NULL )
										{
										 AfxMessageBox("Load Image Failed");
										}
										else
										{
										  m_pic1.GetClientRect( &rectStaticClient );//得到控件的客户区
										  rectStaticClient.NormalizeRect();
										  m_size.cx=rectStaticClient.Size().cx;
										  m_size.cy=rectStaticClient.Size().cy;
										  m_size.cx = rectStaticClient.Width();    // zero based
										  m_size.cy = rectStaticClient.Height();    // zero based
										  m_pic1.ClientToScreen( &rectStaticClient );//转换到屏幕坐标
             							  ScreenToClient( &rectStaticClient);//控件屏幕坐标转换到相对于对话框的客户坐标
										  m_pt.x = rectStaticClient.left;
										  m_pt.y = rectStaticClient.top;
										  GetObject( m_hBmpNew , sizeof(BITMAP), &m_bmInfo );
										  VERIFY(m_hBmpOld = (HBITMAP)SelectObject(m_dcMem, m_hBmpNew )  );
										  offsetx= m_pt.x;
										  offsety=m_pt.y;

										  m_vbar.MoveWindow(offsetx+m_size.cx,offsety,18,m_size.cy);
										  m_hbar.MoveWindow(offsetx,offsety+m_size.cy,m_size.cx,18);
										  horz.cbSize = sizeof(SCROLLINFO);
										  horz.fMask = SIF_ALL;
										  horz.nMin = 0;
										  horz.nMax = m_bmInfo.bmWidth-m_size.cx;
										  horz.nPage =0;
										  horz.nPos = 0;
										  horz.nTrackPos=0;
										  if(m_bmInfo.bmWidth<=m_size.cx)
										  {
											if((m_size.cx-m_bmInfo.bmWidth)==0)
												offsetx= m_pt.x;
											else
												offsetx= m_pt.x+((m_size.cx-m_bmInfo.bmWidth)/2);
											m_vbar.MoveWindow(offsetx+m_bmInfo.bmWidth,offsety,18,m_size.cy);
											m_hbar.ShowWindow(false);
										  }
										 else
										  m_hbar.ShowWindow(true);
										 m_hbar.SetScrollInfo(&horz);


										 vert.cbSize = sizeof(SCROLLINFO);
										 vert.fMask = SIF_ALL;
										 vert.nMin = 0;
										 vert.nMax = m_bmInfo.bmHeight-(m_size.cy);
										 vert.nPage = 0;
										 vert.nTrackPos=0;
										 if(m_bmInfo.bmHeight<=m_size.cy)
										 {
											if((m_size.cy-m_bmInfo.bmHeight)==0)
												offsety= m_pt.y;
											else
												offsety= m_pt.y+((m_size.cy-m_bmInfo.bmHeight)/2);
											m_hbar.MoveWindow(offsetx,offsety+m_bmInfo.bmHeight,m_size.cx,18);
											m_vbar.ShowWindow(false);
										 }
										 else
										  m_vbar.ShowWindow(true);
										m_vbar.SetScrollInfo(&vert);


										InvalidateRect(&rectStaticClient);
										}
														
								rsa[5]->ShowWindow (true);
								rsa[6]->ShowWindow (true);
								rsa[7]->ShowWindow (true);
								rsa[8]->ShowWindow (true);
								rsa[9]->ShowWindow (true);
								rsa[10]->ShowWindow (true);
									rsa[5]->SetWindowText ("");
									rsa[6]->SetWindowText ("");
									rsa[7]->SetWindowText ("");
									rsa[8]->SetWindowText ("");
									rsa[9]->SetWindowText ("");
									rsa[10]->SetWindowText ("");


					





										break;
									case 7:
										rsa[5]->SetWindowText ("B548758E15EAFE878D3F447970E5BB95C2FEA97FBD920A009E2AAE350966FA6EE147632061F6A744D6FBD4D5E2E72E367ABB1DF9A9AE7CD9DB2B4CF1A3D1BFA205C15E720D13E33706227F00B4DB261DFBE29E21E5BD83E7EF97E67BAD4E092CE2B56581E913C4610FD227D9D6B2C13A53933B0881BE2E2CDC7DACA3F7AEE7DDA714883E351529B1D0FDEB60588AF27D74BFD49D7EA1");



										break;
									case 8:
										rsa[6]->SetWindowText ("1F185829C54B78CB8398852CCC540713326E165F07C6978952CC9F7DE5C88B2983B4DFFE0F657B034FCFD93BBF81711075ABA7618B0D7B62CA3BA1BF4F1B72C6F697C7A538F0FD7A2B7077FBA0B33A63F19444E6924F8101C4663E4BB5F98EE5D7D8A64E786E5B8C70B30CAB6D4AD88081C4C305C819EE732DF588AC7D7761406E1521E559DBCCE2014AD54934CE4D042635D2C0F795");



										break;
									case 9:
										rsa[7]->SetWindowText (CString(cipher));
										m_Cedit4=CString(cipher);
										UpdateData(false);


										break;
									case 10:
										rsa[8]->SetWindowText (CString(cipher));



										break;
									case 11:
										rsa[9]->SetWindowText ("3DF594ADB6FF7ABDF4795F682FF63EC616AF099356FE03FB763980BD6D4B26D6FA9D6ACF81E1C5C0CD78B1A75F2A47CA8C030197DB703D613E5B93726F0CFF81B6FA2198A7F27C58A93804083766BE046F0BDEDF626923CE4C8FEE52B45615F305180E7274E0A76640945662A4436576FAB1DB7132BCA76779E2CD166F423C7958C257C021BA76D33866CFA8F292429F03CFDE0069A3");



										break;
									case 12:
										rsa[10]->SetWindowText (CString(plain));



										break;
									case 13:
										//	m_Cedit4="min wen wan cheng   !";
										//	UpdateData(false);




										break;
									case 14:
											MessageBox("演示完毕");
						
										GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);//就可以隐藏，为SW_SHOW可以是显示。IDC_BUTTON4
										GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);
									
										m_hBmpNew =	 (HBITMAP) LoadImage(NULL, "Picture\\z.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
										if( m_hBmpNew == NULL )
										{
										 AfxMessageBox("Load Image Failed");
										}
										else
										{
										  m_pic1.GetClientRect( &rectStaticClient );//得到控件的客户区
										  rectStaticClient.NormalizeRect();
										  m_size.cx=rectStaticClient.Size().cx;
										  m_size.cy=rectStaticClient.Size().cy;
										  m_size.cx = rectStaticClient.Width();    // zero based
										  m_size.cy = rectStaticClient.Height();    // zero based
										  m_pic1.ClientToScreen( &rectStaticClient );//转换到屏幕坐标
             							  ScreenToClient( &rectStaticClient);//控件屏幕坐标转换到相对于对话框的客户坐标
										  m_pt.x = rectStaticClient.left;
										  m_pt.y = rectStaticClient.top;
										  GetObject( m_hBmpNew , sizeof(BITMAP), &m_bmInfo );
										  VERIFY(m_hBmpOld = (HBITMAP)SelectObject(m_dcMem, m_hBmpNew )  );
										  offsetx= m_pt.x;
										  offsety=m_pt.y;

										  m_vbar.MoveWindow(offsetx+m_size.cx,offsety,18,m_size.cy);
										  m_hbar.MoveWindow(offsetx,offsety+m_size.cy,m_size.cx,18);
										  horz.cbSize = sizeof(SCROLLINFO);
										  horz.fMask = SIF_ALL;
										  horz.nMin = 0;
										  horz.nMax = m_bmInfo.bmWidth-m_size.cx;
										  horz.nPage =0;
										  horz.nPos = 0;
										  horz.nTrackPos=0;
										  if(m_bmInfo.bmWidth<=m_size.cx)
										  {
											if((m_size.cx-m_bmInfo.bmWidth)==0)
												offsetx= m_pt.x;
											else
												offsetx= m_pt.x+((m_size.cx-m_bmInfo.bmWidth)/2);
											m_vbar.MoveWindow(offsetx+m_bmInfo.bmWidth,offsety,18,m_size.cy);
											m_hbar.ShowWindow(false);
										  }
										 else
										  m_hbar.ShowWindow(true);
										 m_hbar.SetScrollInfo(&horz);


										 vert.cbSize = sizeof(SCROLLINFO);
										 vert.fMask = SIF_ALL;
										 vert.nMin = 0;
										 vert.nMax = m_bmInfo.bmHeight-(m_size.cy);
										 vert.nPage = 0;
										 vert.nTrackPos=0;
										 if(m_bmInfo.bmHeight<=m_size.cy)
										 {
											if((m_size.cy-m_bmInfo.bmHeight)==0)
												offsety= m_pt.y;
											else
												offsety= m_pt.y+((m_size.cy-m_bmInfo.bmHeight)/2);
											m_hbar.MoveWindow(offsetx,offsety+m_bmInfo.bmHeight,m_size.cx,18);
											m_vbar.ShowWindow(false);
										 }
										 else
										  m_vbar.ShowWindow(true);
										m_vbar.SetScrollInfo(&vert);


										InvalidateRect(&rectStaticClient);
										}
										rsa[5]->ShowWindow (false);
										rsa[6]->ShowWindow (false);
										rsa[7]->ShowWindow (false);
										rsa[8]->ShowWindow (false);
										rsa[9]->ShowWindow (false);
										rsa[10]->ShowWindow (false);

										m_Cedit4="";
										m_Cedit1="";
										m_Cedit2="";


										UpdateData(false);	








										break;





									}



		break;


	}

}

void CDialog4::OnButton3() 
{
	// TODO: Add your control notification handler code here

	CFileDialog dlg(true,"txt",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"Word Files (*.doc)|*.doc|Txt Files (*.txt)|*.txt|Html Files (*.html)|*.html|Data Files (*.xlc;*.xls)|*.xlc; *.xls|All Files (*.*)|*.*||") ;    //动态创建保存文件对话框
	dlg.m_ofn .lpstrTitle ="打开明文文件";
	dlg.m_ofn .lpstrDefExt ="txt";
	dlg.m_ofn .lpstrFilter ="Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0";

	if(dlg.DoModal()==IDOK){
		CFile file(dlg.GetFileName(), CFile::modeRead);
		int len=(int)file.GetLength();
		char *pbuf=new char[len];

        file.Read (pbuf, file.GetLength());
		// MessageBox(pbuf);
//	m_Cedit2.Format ("");
		m_Cedit1=(CString)pbuf;//m_Cedit2为 某一EditBox的变量，属性为CString
    	UpdateData(false);
		delete[] pbuf;
        file.Close();

	}
	
}

void CDialog4::OnButton4() 
{
/////////////////////////////////////c此处添加各算法计数器的代码////////////////////////////////////////////////
		
			if(playfaircountnext!=1)	
				playfaircountnext=playfaircountnext-1;
			if(caesercount!=1){
			caesercount=caesercount-1;

			}
			if(affinecount!=1){
				affinecount=affinecount-1;

			}
			if(vigenerecount!=1){
				vigenerecount=vigenerecount-1;
			}
			if(duowenzicount!=1){
				duowenzicount=duowenzicount-1;

			}
			if(descount!=1){
				descount=descount-1;
			}
			if(ideacount!=1){
				ideacount=ideacount-1;
			}
			if(rsacount!=1){
				rsacount=rsacount-1;

			}
			if(rc4count!=1){
				rc4count=rc4count-1;
			}
		
		



//////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////上一步/////////////////////////////////
			char tempt[28];
			char tempt2[48];
			//char tempt32a[32];
			//char tempt32b[32];
			//char tempt64[64];


		//////////////////////////////////////////////////////////////////////////////
	// TODO: Add your control notification handler code here
	switch(selecttree){
	
		case 0:

								switch (caesercount){
								case 1:
										newedit[1]->SetWindowText ("");
									





									break;
								case 2:

									
										newedit[2]->SetWindowText ("");
										



									break;
								case 3:
										

										m_Cedit4=""; 
										UpdateData(false);

									break;
							
								
								}



								break;


		case 1:
					switch (duowenzicount){
						case 1:
						
								duowenzi[1]->SetWindowText ("");

							break;
						case 2:
								duowenzi[2]->SetWindowText ("");
							break;
						case 3:
								duowenzi[3]->SetWindowText ("");
							break;
							case 4:
								m_Cedit4=""; 
								UpdateData(false);
							break;
					
						
						}





			break;



		case 2:

									switch (vigenerecount){
								case 1:
									
										vigenere[1]->SetWindowText ("");
									
										m_Cedit4="";
										UpdateData(false);





									break;
								case 2:

								
										m_Cedit4="";
										UpdateData(false);



									break;
								
								
								}







			break;
		case 3:
										
								switch(playfaircountnext){
									
												case 1:

											//	playfaircountnext=1;
												editplayfair[0]->SetWindowText(m_Cedit1);
												editplayfair[1]->SetWindowText("");
												editplayfair[2]->SetWindowText("");
												m_Cedit4="";
												UpdateData(false);





														break;
												case 2:
												editplayfair[0]->SetWindowText(m_Cedit1);
												editplayfair[1]->SetWindowText(m_Cedit2);
												editplayfair[2]->SetWindowText("");

												m_Cedit4="";
												UpdateData(false);





													break;


												case 3:
												editplayfair[0]->SetWindowText(m_Cedit1);
												editplayfair[1]->SetWindowText(m_Cedit2);
												editplayfair[2]->SetWindowText(c);
												m_Cedit4="";
												UpdateData(false);




													break;


														
													}






			break;
		case 4:




			break;
		case 5:
												switch (affinecount){
											case 1:
													affine[0]->SetWindowText (m_Cedit1);
													affine[1]->SetWindowText ("");
													affine[2]->SetWindowText ("");
													affine[3]->SetWindowText ("");
													m_Cedit4="";
													UpdateData(false);





												break;
											case 2:

													affine[0]->SetWindowText (m_Cedit1);
													affine[1]->SetWindowText (m_Cedit2);
													affine[2]->SetWindowText ("");
													affine[3]->SetWindowText ("");
													m_Cedit4="";
													UpdateData(false);



												break;
											case 3:
													affine[0]->SetWindowText (m_Cedit1);
													affine[1]->SetWindowText (m_Cedit2);
													affine[2]->SetWindowText (m_Cedit2);
													affine[3]->SetWindowText ("");

													m_Cedit4=""; 
													UpdateData(false);

												break;
											case 4:
													affine[0]->SetWindowText (m_Cedit1);
													affine[1]->SetWindowText (m_Cedit2);
													affine[2]->SetWindowText (m_Cedit2);
													affine[3]->SetWindowText (a);

													m_Cedit4=""; 
													UpdateData(false);

												break;
										
										
											
											}
												

			break;
		case 6:
											switch(rc4count){
											case 1:
												rc4[1]->SetWindowText ("");



												break;
											case 2:
												rc4[2]->SetWindowText ("");



												break;

											case 3:
												m_Cedit4=""; 
													UpdateData(false);
												



												break;

											
											}



			break;
		case 7:


			switch(descount){
												case 0:

													des[0]->SetWindowText (m_Cedit2);

													break;
									
												case 1:

											//	playfaircountnext=1;
														MessageBox("请点击 交换选择表1 ");

														break;
												case 2:
					
													break;


												case 3:
												
													//MessageBox(tempt);
													des[1]->SetWindowText ("");
													
												des[2]->SetWindowText ("");
												descount=descount-1;

													break;
												case 4:
										
												
													break;
												case 5:
											


												des[3]->SetWindowText("");
												des[4]->SetWindowText("");
											
												descount=descount-1;




													break;
												case 6:
									

													MessageBox("请点击 交换选择表2 ");



													break;
												case 7:
												
													
													des[5]->SetWindowText ("");
								
													break;
												case 8:
													/*

											
												des[6]->SetWindowText("");
												des[7]->SetWindowText("");
												des[8]->SetWindowText("");
												des[9]->SetWindowText("");
												des[10]->SetWindowText("");
												des[11]->SetWindowText("");
												des[12]->SetWindowText("");
												des[13]->SetWindowText("");
												des[14]->SetWindowText("");

												m_Cedit4="";
												UpdateData(false);
												//descount=descount-1;

												*/


																	
												desbutton[2]->ShowWindow (false);
												desbutton[3]->ShowWindow (false);
												desbutton[4]->ShowWindow (false);


											
												des[6]->ShowWindow (false);
												des[7]->ShowWindow (false);
												des[8]->ShowWindow (false);
												des[9]->ShowWindow (false);
												des[10]->ShowWindow (false);
												des[11]->ShowWindow (false);
												des[12]->ShowWindow (false);
												des[13]->ShowWindow (false);
												des[14]->ShowWindow (false);
												desnext=false;






												m_hBmpNew =	 (HBITMAP) LoadImage(NULL, "Picture\\DES_1.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
												if( m_hBmpNew == NULL )
												{
												 AfxMessageBox("Load Image Failed");
												}
												else
												{
												  m_pic1.GetClientRect( &rectStaticClient );//得到控件的客户区
												  rectStaticClient.NormalizeRect();
												  m_size.cx=rectStaticClient.Size().cx;
												  m_size.cy=rectStaticClient.Size().cy;
												  m_size.cx = rectStaticClient.Width();    // zero based
												  m_size.cy = rectStaticClient.Height();    // zero based
												  m_pic1.ClientToScreen( &rectStaticClient );//转换到屏幕坐标
             									  ScreenToClient( &rectStaticClient);//控件屏幕坐标转换到相对于对话框的客户坐标
												  m_pt.x = rectStaticClient.left;
												  m_pt.y = rectStaticClient.top;
												  GetObject( m_hBmpNew , sizeof(BITMAP), &m_bmInfo );
												  VERIFY(m_hBmpOld = (HBITMAP)SelectObject(m_dcMem, m_hBmpNew )  );
												  offsetx= m_pt.x;
												  offsety=m_pt.y;

												  m_vbar.MoveWindow(offsetx+m_size.cx,offsety,18,m_size.cy);
												  m_hbar.MoveWindow(offsetx,offsety+m_size.cy,m_size.cx,18);
												  horz.cbSize = sizeof(SCROLLINFO);
												  horz.fMask = SIF_ALL;
												  horz.nMin = 0;
												  horz.nMax = m_bmInfo.bmWidth-m_size.cx;
												  horz.nPage =0;
												  horz.nPos = 0;
												  horz.nTrackPos=0;
												  if(m_bmInfo.bmWidth<=m_size.cx)
												  {
													if((m_size.cx-m_bmInfo.bmWidth)==0)
														offsetx= m_pt.x;
													else
														offsetx= m_pt.x+((m_size.cx-m_bmInfo.bmWidth)/2);
													m_vbar.MoveWindow(offsetx+m_bmInfo.bmWidth,offsety,18,m_size.cy);
													m_hbar.ShowWindow(false);
												  }
												 else
												  m_hbar.ShowWindow(true);
												 m_hbar.SetScrollInfo(&horz);
												 vert.cbSize = sizeof(SCROLLINFO);
												 vert.fMask = SIF_ALL;
												 vert.nMin = 0;
												 vert.nMax = m_bmInfo.bmHeight-(m_size.cy);
												 vert.nPage = 0;
												 vert.nTrackPos=0;
												 if(m_bmInfo.bmHeight<=m_size.cy)
												 {
													if((m_size.cy-m_bmInfo.bmHeight)==0)
														offsety= m_pt.y;
													else
														offsety= m_pt.y+((m_size.cy-m_bmInfo.bmHeight)/2);
													m_hbar.MoveWindow(offsetx,offsety+m_bmInfo.bmHeight,m_size.cx,18);
													m_vbar.ShowWindow(false);
												 }
												 else
												  m_vbar.ShowWindow(true);
												m_vbar.SetScrollInfo(&vert);


												InvalidateRect(&rectStaticClient);
												}

											


												desbutton[0]->ShowWindow (true);
												desbutton[1]->ShowWindow (true);
										
									


													
													des[0]->ShowWindow (true);
													
													//des[1]=new CEdit() ;
													des[1]->ShowWindow (true);
													//des[2]=new CEdit() ;
													des[2]->ShowWindow (true);

													//des[3]=new CEdit() ;
													des[3]->ShowWindow (true);

													//des[4]=new CEdit() ;
													des[4]->ShowWindow (true);


													//des[5]=new CEdit() ;
													des[5]->ShowWindow (true);

												des[0]->SetWindowText(m_Cedit2);



												for (i=0;i<28;i++)
												{
													tempt[i]= kl_tmp[i]?'1':'0';
												}
												//MessageBox(tempt);
												des[1]->SetWindowText (CString(tempt));
												for (i=0;i<28;i++)
												{
													tempt[i]= kr_tmp[i]?'1':'0';
												}
												
									des[2]->SetWindowText (CString(tempt));


											//	des[1]->SetWindowText(a);
											//	des[2]->SetWindowText(a);


									for (i=0;i<28;i++)
									{
										tempt[i]= kl[i]?'1':'0';
									}	
									des[3]->SetWindowText (CString(tempt));
									for (i=0;i<28;i++)
									{
										tempt[i]= kr[i]?'1':'0';
									}
									des[4]->SetWindowText (CString(tempt));

												//des[3]->SetWindowText(b);
												//des[4]->SetWindowText(b);
											//des[5]->SetWindowText(m_Cedit2);
									for (i=0;i<48;i++)
									{
										tempt2[i]= subkey[i]?'1':'0';
									}	
									
									
								    des[5]->SetWindowText (CString(tempt2));


											






													break;
												case 9:

										/*
												des[8]->SetWindowText("");
												des[9]->SetWindowText("");
												des[10]->SetWindowText("");
												des[11]->SetWindowText("");
												des[12]->SetWindowText("");
												des[13]->SetWindowText("");
												des[14]->SetWindowText("");

												m_Cedit4="";
												UpdateData(false);
												*/
													



													break;
												case 10:
													
													des[6]->SetWindowText ("");
													des[7]->SetWindowText ("");
													descount=descount-1;

												

									


													break;
												case 11:
													/*

												des[9]->SetWindowText("");
												des[10]->SetWindowText("");
												des[11]->SetWindowText("");
												des[12]->SetWindowText("");
												des[13]->SetWindowText("");
												des[14]->SetWindowText("");

												m_Cedit4="";
												UpdateData(false);
												descount=descount-1;
												*/
														MessageBox("请点击 置换表 ");
												





													break;

													//向上开始弄
												case 12:
													des[8]->SetWindowText("");

					
												
												
												



													break;
												case 13:
												

											

													break;
												case 14:
													des[10]->SetWindowText("");
												des[9]->SetWindowText("");
												descount=descount-1;


											

												



													break;
												case 15:
														MessageBox("请点击 扩充盒 E盒");
												
										
												
											




													break;
												case 16:
														des[11]->SetWindowText("");





													break;
												case 17:
														MessageBox("请点击 置换盒 P盒");




													break;

												case 18:




													break;

												case 19:
							
												des[12]->SetWindowText("");
												des[13]->SetWindowText("");
												descount=descount-1;



														break;
												case 20:
													des[14]->SetWindowText("");




													break;
												case 21:
												m_Cedit4="";
												UpdateData(false);




													break;
											


														
													}

		break;
		case 8:

									switch(ideacount){
									case 1:
										idea[1]->SetWindowText("");
										idea[2]->SetWindowText("");
										idea[3]->SetWindowText("");
										idea[4]->SetWindowText("");




										break;
									case 2:
										m_Cedit4="";
										UpdateData(false);
										



										break;
						
		
									}


			break;
		case 9:
									switch(rsacount){
									case 1:
										rsa[1]->SetWindowText("");


										break;
									case 2:
										rsa[2]->SetWindowText("");


										break;
									case 3:
											rsa[3]->SetWindowText("");

	
										break;
									case 4:
											rsa[4]->SetWindowText("");


										break;
									case 5:

												rsa[5]->ShowWindow (false);
												rsa[6]->ShowWindow (false);
												rsa[7]->ShowWindow (false);
												rsa[8]->ShowWindow (false);
												rsa[9]->ShowWindow (false);
												rsa[10]->ShowWindow (false);
												
												





												m_hBmpNew =	 (HBITMAP) LoadImage(NULL, "Picture\\RSA_1.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
												if( m_hBmpNew == NULL )
												{
												 AfxMessageBox("Load Image Failed");
												}
												else
												{
												  m_pic1.GetClientRect( &rectStaticClient );//得到控件的客户区
												  rectStaticClient.NormalizeRect();
												  m_size.cx=rectStaticClient.Size().cx;
												  m_size.cy=rectStaticClient.Size().cy;
												  m_size.cx = rectStaticClient.Width();    // zero based
												  m_size.cy = rectStaticClient.Height();    // zero based
												  m_pic1.ClientToScreen( &rectStaticClient );//转换到屏幕坐标
             									  ScreenToClient( &rectStaticClient);//控件屏幕坐标转换到相对于对话框的客户坐标
												  m_pt.x = rectStaticClient.left;
												  m_pt.y = rectStaticClient.top;
												  GetObject( m_hBmpNew , sizeof(BITMAP), &m_bmInfo );
												  VERIFY(m_hBmpOld = (HBITMAP)SelectObject(m_dcMem, m_hBmpNew )  );
												  offsetx= m_pt.x;
												  offsety=m_pt.y;

												  m_vbar.MoveWindow(offsetx+m_size.cx,offsety,18,m_size.cy);
												  m_hbar.MoveWindow(offsetx,offsety+m_size.cy,m_size.cx,18);
												  horz.cbSize = sizeof(SCROLLINFO);
												  horz.fMask = SIF_ALL;
												  horz.nMin = 0;
												  horz.nMax = m_bmInfo.bmWidth-m_size.cx;
												  horz.nPage =0;
												  horz.nPos = 0;
												  horz.nTrackPos=0;
												  if(m_bmInfo.bmWidth<=m_size.cx)
												  {
													if((m_size.cx-m_bmInfo.bmWidth)==0)
														offsetx= m_pt.x;
													else
														offsetx= m_pt.x+((m_size.cx-m_bmInfo.bmWidth)/2);
													m_vbar.MoveWindow(offsetx+m_bmInfo.bmWidth,offsety,18,m_size.cy);
													m_hbar.ShowWindow(false);
												  }
												 else
												  m_hbar.ShowWindow(true);
												 m_hbar.SetScrollInfo(&horz);
												 vert.cbSize = sizeof(SCROLLINFO);
												 vert.fMask = SIF_ALL;
												 vert.nMin = 0;
												 vert.nMax = m_bmInfo.bmHeight-(m_size.cy);
												 vert.nPage = 0;
												 vert.nTrackPos=0;
												 if(m_bmInfo.bmHeight<=m_size.cy)
												 {
													if((m_size.cy-m_bmInfo.bmHeight)==0)
														offsety= m_pt.y;
													else
														offsety= m_pt.y+((m_size.cy-m_bmInfo.bmHeight)/2);
													m_hbar.MoveWindow(offsetx,offsety+m_bmInfo.bmHeight,m_size.cx,18);
													m_vbar.ShowWindow(false);
												 }
												 else
												  m_vbar.ShowWindow(true);
												m_vbar.SetScrollInfo(&vert);


												InvalidateRect(&rectStaticClient);
												}

											


									
										
									


													
													rsa[0]->ShowWindow (true);
													
													//des[1]=new CEdit() ;
													rsa[1]->ShowWindow (true);
													//des[2]=new CEdit() ;
													rsa[2]->ShowWindow (true);

													//des[3]=new CEdit() ;
													rsa[3]->ShowWindow (true);

													//des[4]=new CEdit() ;
													rsa[4]->ShowWindow (true);


												

												//rsa[0]->SetWindowText(m_Cedit2);
												rsa[0]->SetWindowText ("FD2655F01F84B4F9911C6762249DB38EAFEA1EFF3C4845803714563C522B876453405EBD75C986D013F211F9C0A9405872C09C93417FE172AD3F0E2116B066D292E362283AF1EDED6D53C63DBCB762591C1147E5B8A802AADCC5D2B53A47DA6699F29352411BD831802D9820F8C828809FECFEE66EC3C709E2D4A2079F");
												rsa[1]->SetWindowText ("BFCB93A3EC3F78B04597E63DD6A49D6D013C7FC94A69B31C89A8D346CC9B7DCA520786EFD03742821F671EA21C5AC67337D52F9C15118EA96F6D4FBA507910122B2CE338728F0FE91010CF140060E22DA456497B8F1A3DDA8BFA264AA4B8A40E3A09CAADD338BFD44791DBA3A3C7F05B46BFEE67C772ED80DD6F77D6AD");

												rsa[2]->SetWindowText ("1F185829C54B78CB8398852CCC540713326E165F07C6978952CC9F7DE5C88B2983B4DFFE0F657B034FCFD93BBF81711075ABA7618B0D7B62CA3BA1BF4F1B72C6F697C7A538F0FD7A2B7077FBA0B33A63F19444E6924F8101C4663E4BB5F98EE5D7D8A64E786E5B8C70B30CAB6D4AD88081C4C305C819EE732DF588AC7D7761406E1521E559DBCCE2014AD54934CE4D042635D2C0F795");
												rsa[3]->SetWindowText ("3DF594ADB6FF7ABDF4795F682FF63EC616AF099356FE03FB763980BD6D4B26D6FA9D6ACF81E1C5C0CD78B1A75F2A47CA8C030197DB703D613E5B93726F0CFF81B6FA2198A7F27C58A93804083766BE046F0BDEDF626923CE4C8FEE52B45615F305180E7274E0A76640945662A4436576FAB1DB7132BCA76779E2CD166F423C7958C257C021BA76D33866CFA8F292429F03CFDE0069A3");
												rsa[4]->SetWindowText ("B548758E15EAFE878D3F447970E5BB95C2FEA97FBD920A009E2AAE350966FA6EE147632061F6A744D6FBD4D5E2E72E367ABB1DF9A9AE7CD9DB2B4CF1A3D1BFA205C15E720D13E33706227F00B4DB261DFBE29E21E5BD83E7EF97E67BAD4E092CE2B56581E913C4610FD227D9D6B2C13A53933B0881BE2E2CDC7DACA3F7AEE7DDA714883E351529B1D0FDEB60588AF27D74BFD49D7EA1");
												//des[5]->SetWindowText(m_Cedit2);


											




										


										break;
								
									case 6:
											rsa[5]->SetWindowText("");


										break;
									case 7:
											rsa[6]->SetWindowText("");


										break;
									case 8:
											rsa[7]->SetWindowText("");


										break;
									case 9:
											rsa[8]->SetWindowText("");


										break;
									case 10:
											rsa[9]->SetWindowText("");


										break;
									case 11:
											rsa[10]->SetWindowText("");


										break;


									case 12:
										m_Cedit4="";
										UpdateData(false);


										break;


									}








			break;

	}

			
	

	
}

void CDialog4::OnChangeEdit4() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here


	
}

////////////






void CDialog4::Onjiaohuanxuanzebiao1()
{

	dialog8.DoModal();

}


void CDialog4::Onjiaohuanxuanzebiao2()
{


dialog9.DoModal();
}






//置换表
void CDialog4::Onzhihuanbiao ()
{


	dialog10.DoModal();
}




//扩充表
void CDialog4::Onkuochonghe ()
{


	dialog11.DoModal();
}



//置换盒
void CDialog4::Onzhihuanhe ()
{


	dialog12.DoModal();
}



//替换盒
void CDialog4::Ontihuanhe ()
{


	//dialog13.DoModal();
}

