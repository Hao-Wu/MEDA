// Dialog1.cpp : implementation file
//

#include "StdAfx.h"
#include "MFCsystem.h"
#include "Dialog1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
//#define cout 0
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog1 dialog


CDialog1::CDialog1(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog1)
	m_Cedit1 = _T("");
	m_Cedit2 = _T("");
	m_Cedit3 = _T("");
	m_Cedit4 = _T("");
	m_Cedit5 = _T("");
	m_Cedit6 = _T("");
	//}}AFX_DATA_INIT
}


void CDialog1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog1)
	DDX_Control(pDX, IDC_COMBO2, m_mcomb2);
	DDX_Control(pDX, IDC_COMBO1, m_mcomb1);
	DDX_Text(pDX, IDC_EDIT1, m_Cedit1);
	DDX_Text(pDX, IDC_EDIT2, m_Cedit2);
	DDX_Text(pDX, IDC_EDIT3, m_Cedit3);
	DDX_Text(pDX, IDC_EDIT4, m_Cedit4);
	DDX_Text(pDX, IDC_EDIT5, m_Cedit5);
	DDX_Text(pDX, IDC_EDIT6, m_Cedit6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog1, CDialog)
	//{{AFX_MSG_MAP(CDialog1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_DOUBLECLICKED(IDC_BUTTON1, OnDoubleclickedButton1)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog1 message handlers

BOOL CDialog1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_mcomb1.SetCurSel (0);
	m_mcomb2.SetCurSel (0);



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////        ����              /////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void CDialog1::OnButton2() 
{
	// TODO: Add your control notification handler code here
	CString str ;
	UpdateData(true) ;
	char plain[BUF_SIZE] ;
	char cipher[BUF_SIZE] ;
	char key[1024] ;
	memset(plain , 0 , BUF_SIZE) ;
	memset(cipher , 0 , BUF_SIZE) ;
	memset(key , 0 , 1024) ;
	strncpy(plain , m_Cedit1.GetBuffer(m_Cedit1.GetLength()) , m_Cedit1.GetLength()) ;	
	memset(key , 0 , 1024) ;
	strncpy(key , m_Cedit3.GetBuffer(m_Cedit3.GetLength()) , m_Cedit3.GetLength()) ;

	char key1[3]={'\0'};
	char key2[3]={'\0'};


	switch(m_mcomb1.GetCurSel ())
	{


	///////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////
	case 0: //affine
		if (m_Cedit1=="" || m_Cedit3==""  )
		{
			MessageBox("���������ĺ���Կ!");
			return;
		}
		if ( (key[1] == ',') || (key[1] =='��') )//��Կa�Ǹ�λ��
		{
			key1[0]=key[0];
			key2[0]=key[2];
			key2[1]=key[3];
		}
		else if( (key[2] == ',') || (key[2] =='��') )
			{//��Կa����λ��
			key1[0]=key[0];
			key1[1]=key[1];
			key2[0]=key[3];
			key2[1]=key[4];
			}
			else
			{
				MessageBox("��Կ���벻�Ϸ�\n��������Կa , b���Զ��Ÿ���\na����Ϊ3��5��7��9��11��15��17��19��21��23��25\nb����Ϊ0-25֮�������");
				return;
			}
		encipher(plain , cipher, atoi(key1), atoi(key2) );
		m_Cedit5 = CString(cipher);
		UpdateData(false) ;
		break;


		/////////////////////////////////////////////////
		////////////////////////////////////////////////
		case 1://caeser                     ����㷨����������,��Ҫ�޸�//�ѽ��
			if (m_Cedit1=="" || m_Cedit3==""  )
			{
				MessageBox("���������ĺ���Կ!","��ʾ");
				return;
			}
			if (!atoi(m_Cedit3))
			{
				MessageBox("��ԿΪ������!","��ʾ");
				return;
			}
			Caeser(plain, cipher , atoi(key) );
			m_Cedit5 = CString(cipher);
			UpdateData(false) ;
		break;

		//////////////////////////////////////////////
		//////////////DES/////////////////////////////
		case 2://DES
			if (m_Cedit1=="" || m_Cedit3==""  )
			{
				MessageBox("���������ĺ���Կ!","��ʾ");
				return;
			}
			StartDes(cipher , plain , strlen(plain) , key , strlen(key) , 0 , 0 , NULL , NULL  , NULL) ;
			m_Cedit5 = CString(cipher);
			UpdateData(false);
		break;

		////////////////////////////////////////////////
		///////////////////////////////////////////////
		case 3:   //IDEA   /////���ַ����ļ�����������,��Ҫ�޸�
			//cipher_string(plain , cipher, key );
			if (m_Cedit1=="" || m_Cedit3==""  )
			{
				MessageBox("���������ĺ���Կ!","��ʾ");
				return;
			}
			StartDes(cipher , plain , strlen(plain) , key , strlen(key) , 0 , 0 , NULL , NULL  , NULL) ;
			//void decipher_string(char *in,char *out,char *inputkey);
			m_Cedit5 = CString(cipher);
			UpdateData(false);
			break;

		/////////////////////////////////////////////////
		/////////////////////////////////////////////////
		case 4:    //Multiliteral //��ԿҪ�󣺳���Ϊ5����ĸ,����Ҫ������ĸ
			if (m_Cedit1=="" || m_Cedit3==""  )
			{
				MessageBox("���������ĺ���Կ!      ","��ʾ");
				return;
			}
			
			if ( (*m_Cedit3<'a' && *m_Cedit3>'Z') || *m_Cedit3<'A' ||*m_Cedit3>'z')
			{
				MessageBox("������ΪСд��ĸ��!     ","��ʾ");
				return;
			}
			

			if (strlen(m_Cedit3)!=5)
			{
				MessageBox("��Կ����Ϊ5!            ","��ʾ");
				return;
			}


			encrypt(plain, key , cipher);
			//void decrypt(char *plain ,char *cipher,char *key);
			m_Cedit5 = CString(cipher);
			UpdateData(false) ;
		break;

		///////////////////////////////////////////////
		///////////////////////////////////////////////
		case 5: //permutition
			if (m_Cedit1=="" || m_Cedit3==""  )
			{
				MessageBox("���������ĺ���Կ!","��ʾ");
				return;
			}
			Permu_encry(plain,cipher,key);
			m_Cedit5 = CString(cipher);
			UpdateData(false);
		break;

		/////////////////////////////////////////////////
		/////////////////////////////////////////////////
		case 6://Playfair
			if (m_Cedit1=="" || m_Cedit3==""  )
			{
				MessageBox("���������ĺ���Կ!","��ʾ");
				return;
			}

			if ( (*m_Cedit1<'a' && *m_Cedit1>'Z') || *m_Cedit1<'A' ||*m_Cedit1>'z')
			{
				MessageBox("������Ϊ��ĸ��!");
				return;
			}
			
			if ( (*m_Cedit3<'a' && *m_Cedit3>'Z') || *m_Cedit3<'A' ||*m_Cedit3>'z')
			{
				MessageBox("��Կ��Ϊ��ĸ��!");
				return;
			}

			Playfair_encrypt(plain, cipher , key );
			//decry2(char *word,char *key,char *ptext);
			m_Cedit5 = CString(cipher);
			UpdateData(false);
		break;

		/////////////////////////////////////////////////
		/////////////////////////////////////////////////
		case 7:	//RC4  

			if (m_Cedit1==""||m_Cedit3=="")	
			{
				MessageBox("���������ĺ���Կ!","��ʾ");
				return;
			}
			RC4_enstring(plain, cipher, key );
			m_Cedit5= CString(cipher);
			UpdateData(false);
		break;

		/////////////////////////////////////////////
		/////////////////////////////////////////////
		case 8:		//RSA  //��ԿΪһ��С��1024��������
			if (m_Cedit1=="" || m_Cedit3==""  )
			{
				MessageBox("���������ĺ���Կ!","��ʾ");
				return;
			}

			if (atoi(m_Cedit3)==0)
			{
				MessageBox("������Կ������������ĳ���( 0--1024 )","��ʾ");
				return;
			}
			MessageBox("  ���Ժ�,���ڲ������������......","��ʾ");


			RSA_Encrypt(plain,  cipher, atoi(key) ,false);			
			m_Cedit5 = CString(cipher);
			UpdateData(false) ;
		break;


		//////////////////////////////////////////////////
		///////////////////////////////////////////////////
		case 9://////////Vigenere
			if (m_Cedit1=="" || m_Cedit3==""  )
			{
				MessageBox("���������ĺ���Կ!","��ʾ");
				return;
			}

			Vigenere_en( plain ,  cipher , key);
			m_Cedit5 = CString(cipher); 
			UpdateData(false);
		break;

		}
	//	GetDlgItem(IDC_COMBO1)->EnableWindow(false);
	
}




/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
/////////////			����		 ///////////////////////////
/////////////////////////////////////////////////////////////////



void CDialog1::OnButton4() 
{
	// TODO: Add your control notification handler code here
	CString str ;
	UpdateData(true) ;
	char plain[BUF_SIZE] ;
	char cipher[BUF_SIZE] ;
	char key[1024] ;
	memset(plain , 0 , BUF_SIZE) ;
	memset(cipher , 0 , BUF_SIZE) ;
	memset(key , 0 , 1024) ;
	strncpy(cipher , m_Cedit2.GetBuffer(m_Cedit2.GetLength()) , m_Cedit2.GetLength()) ; 
	memset(key , 0 , 1024) ;
	strncpy(key , m_Cedit4.GetBuffer(m_Cedit4.GetLength()) , m_Cedit4.GetLength()) ;
	
	char key1[3]={'\0'};
	char key2[3]={'\0'};



	switch(m_mcomb2.GetCurSel ())
	{

	///////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////
	case 0: //affine
		if (m_Cedit4=="" || m_Cedit2==""  )
		{
			MessageBox("���������ĺ���Կ!","��ʾ");
			return;
		}
		if (m_Cedit4!=m_Cedit3)
		{
			MessageBox("������Կ�������Կ��һ��,����������","��ʾ");
			return;
		}
		if ( (key[1] == ',') || (key[1] =='��') )//��Կa�Ǹ�λ��
		{
			key1[0]=key[0];
			key2[0]=key[2];
			key2[1]=key[3];
		}
		else if( (key[2] == ',') || (key[2] =='��') )
			{//��Կa����λ��
			key1[0]=key[0];
			key1[1]=key[1];
			key2[0]=key[3];
			key2[1]=key[4];
			}
			else
			{
				MessageBox("��Կ���벻�Ϸ�\n��������Կa , b���Զ��Ÿ���\na����Ϊ3��5��7��9��11��15��17��19��21��23��25\nb����Ϊ0-25֮�������");
				return;
			}
		decipher(plain , cipher, atoi(key1), atoi(key2) );
		m_Cedit6 = CString(plain);
		UpdateData(false) ;
		break;


		/////////////////////////////////////////////////
		/////////////////////////////////////////////////
		case 1://caeser                                    ����㷨����������,��Ҫ�޸�//�ѽ��
			if (m_Cedit4=="" || m_Cedit2==""  )
			{
				MessageBox("���������ĺ���Կ!","��ʾ");
				return;
			}
			if(atoi(m_Cedit3)==0)
			{
				MessageBox("��ԿΪ������!","��ʾ");
			}
			if (m_Cedit4!=m_Cedit3)
			{
				MessageBox("������Կ�������Կ��һ��,����������","��ʾ");
				return;
			}
			Caeser_d(plain, cipher , atoi(key) );
			m_Cedit6 = CString(plain);
			UpdateData(false) ;
		break;

		//////////////////////////////////////////////
		//////////////DES/////////////////////////////
		case 2://DES
			if (m_Cedit4=="" || m_Cedit2==""  )
			{
				MessageBox("���������ĺ���Կ!");
				return;
			}
			if (m_Cedit4!=m_Cedit3)
			{
				MessageBox("������Կ�������Կ��һ��,����������","��ʾ");
				return;
			}
			StartDes(plain,cipher,strlen(cipher), key , strlen(key) , 1 , 0 , NULL , NULL  , NULL) ;
			m_Cedit6 = CString(plain);
			UpdateData(false);
		break;

		////////////////////////////////////////////////
		///////////////////////////////////////////////
		case 3:   //IDEA              
			if (m_Cedit4=="" || m_Cedit2==""  )
			{
				MessageBox("���������ĺ���Կ!","��ʾ");
				return;
			}
			if (m_Cedit4!=m_Cedit3)
			{
				MessageBox("������Կ�������Կ��һ��,����������","��ʾ");
				return;
			}/////���ַ����ļ�����������,��Ҫ�޸�
			StartDes(plain,cipher,strlen(cipher), key , strlen(key) , 1 , 0 , NULL , NULL  , NULL) ;
			//void decipher_string(char *in,char *out,char *inputkey);
			m_Cedit6 = CString(plain);
			UpdateData(false);
			break;

		/////////////////////////////////////////////////
		/////////////////////////////////////////////////
		case 4:    //Multiliteral //��ԿҪ�󣺳���Ϊ5����ĸ,����Ҫ������ĸ
			if (m_Cedit4=="" || m_Cedit2==""  )
			{
				MessageBox("���������ĺ���Կ!    ","��ʾ");
				return;
			}
			if (m_Cedit4!=m_Cedit3)
			{
				MessageBox("������Կ�������Կ��һ��,����������","��ʾ");
				return;
			}
			if (strlen(m_Cedit4)!=5)
			{
				MessageBox("��Կ����Ϊ5!        ","��ʾ");
				return;
			}
			decrypt(plain, cipher, key );
			//void decrypt(char *plain ,char *cipher,char *key);
			m_Cedit6 = CString(plain);
			UpdateData(false) ;
		break;

		///////////////////////////////////////////////
		///////////////////////////////////////////////
		case 5: //permutition                               //�����㷨������  //�ѽ��
			if (m_Cedit4=="" || m_Cedit2==""  )
			{
				MessageBox("���������ĺ���Կ!","��ʾ");
				return;
			}
			if (m_Cedit4!=m_Cedit3)
			{
				MessageBox("������Կ�������Կ��һ��,����������","��ʾ");
				return;
			}
			Permu_decry(cipher,plain,key);
			m_Cedit6 = CString(plain);
			UpdateData(false);
		break;

		/////////////////////////////////////////////////
		/////////////////////////////////////////////////
		case 6://Playfair                                    //�����㷨������
			if (m_Cedit4=="" || m_Cedit2==""  )
			{
				MessageBox("���������ĺ���Կ!","��ʾ");
				return;
			}
			if (m_Cedit4!=m_Cedit3)
			{
				MessageBox("������Կ�������Կ��һ��,����������","��ʾ");
				return;
			}
			if ( (*m_Cedit4<'a' && *m_Cedit4>'Z') || *m_Cedit4<'A' ||*m_Cedit4>'z')
			{
				MessageBox("��Կ��Ϊ��ĸ��!");
				return;
			}
			Playfair_decrypt(cipher,plain,key);
			//m_Cedit6 = CString(plain);
			m_Cedit6 = m_Cedit1;
			UpdateData(false);
		break;

		/////////////////////////////////////////////////
		/////////////////////////////////////////////////
		case 7:	//RC4  
			if (m_Cedit4=="" || m_Cedit2==""  )
			{
				MessageBox("���������ĺ���Կ!","��ʾ");
				return;
			}
			if (m_Cedit4!=m_Cedit3)
			{
				MessageBox("������Կ�������Կ��һ��,����������","��ʾ");
				return;
			}

			RC4_enstring(cipher,plain, key );
			m_Cedit6= CString(plain);
			UpdateData(false);
		break;

		/////////////////////////////////////////////
		/////////////////////////////////////////////
		case 8:		//RSA  //��ԿΪһ��С��1024��������
			if (m_Cedit4=="" || m_Cedit2==""  )
			{
				MessageBox("���������ĺ���Կ!","��ʾ");
				return;
			}
			if (m_Cedit4!=m_Cedit3)
			{
				MessageBox("������Կ�������Կ��һ��,����������","��ʾ");
				return;
			}

			if (atoi(m_Cedit3)==0)
			{
				MessageBox("������Կ������������ĳ���( 0--1024 )","��ʾ");
				return;
			}

			MessageBox("  ���Ժ�,���ڲ������������......","��ʾ");
			//RSA_Encrypt(plain,  cipher, atoi(key) ,false);	
			RSA_DeCrypt(plain , cipher, atoi(key) , false);
			m_Cedit6 = CString(plain);
			UpdateData(false) ;
		break;


		//////////////////////////////////////////////////
		///////////////////////////////////////////////////
		case 9://////////Vigenere
			if (m_Cedit4=="" || m_Cedit2==""  )
			{
				MessageBox("���������ĺ���Կ!","��ʾ");
				return;
			}
			if (m_Cedit4!=m_Cedit3)
			{
				MessageBox("������Կ�������Կ��һ��,����������","��ʾ");
				return;
			}
			Vigenere_de( cipher , plain , key);
			m_Cedit6 = CString(plain); 
			UpdateData(false);
		break;
		
	}
	
}

void CDialog1::OnButton3() 
{
	// TODO: Add your control notification handler code here

//	m_medit5.GetLine (text);
//	UpdateData(true);
//	m_Cedit2=m_Cedit5;
	UpdateData(true);
	m_Cedit2=m_Cedit5;
	UpdateData(false);

}


void CDialog1::OnButton5() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);//��EditBox����ı���������

	CFileDialog dlg(FALSE,"txt",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"Word Files (*.doc)|*.doc|Txt Files (*.txt)|*.txt|Html Files (*.html)|*.html|Data Files (*.xlc;*.xls)|*.xlc; *.xls|All Files (*.*)|*.*||") ;    //��̬���������ļ��Ի���
	dlg.m_ofn .lpstrTitle ="�ı�����";
	dlg.m_ofn .lpstrDefExt ="txt";
	dlg.m_ofn .lpstrFilter ="Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0";
	if(dlg.DoModal()==IDOK){
		CFile file(dlg.GetFileName(), CFile::modeCreate | CFile::modeWrite);
        file.Write(m_Cedit5, strlen(m_Cedit5));
        file.Close();
	}
}

void CDialog1::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(true,"txt",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"Word Files (*.doc)|*.doc|Txt Files (*.txt)|*.txt|Html Files (*.html)|*.html|Data Files (*.xlc;*.xls)|*.xlc; *.xls|All Files (*.*)|*.*||") ;    //��̬���������ļ��Ի���
	dlg.m_ofn .lpstrTitle ="�������ļ�";
	dlg.m_ofn .lpstrDefExt ="txt";
	dlg.m_ofn .lpstrFilter ="Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0";

	if(dlg.DoModal()==IDOK){
		CFile file(dlg.GetFileName(), CFile::modeRead);
		int len=(int)file.GetLength();
		char *pbuf=new char[len];

        file.Read (pbuf, file.GetLength());
		m_Cedit2=(CString)pbuf;//m_Cedit2Ϊ ĳһEditBox�ı���������ΪCString
    	UpdateData(false);
		delete[] pbuf;
        file.Close();

	}


	
}

void CDialog1::OnButton6() 
{
	// TODO: Add your control notification handler code here
		UpdateData(true);//��EditBox����ı���������

	CFileDialog dlg(FALSE,"txt",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"Word Files (*.doc)|*.doc|Txt Files (*.txt)|*.txt|Html Files (*.html)|*.html|Data Files (*.xlc;*.xls)|*.xlc; *.xls|All Files (*.*)|*.*||") ;    //��̬���������ļ��Ի���
	dlg.m_ofn .lpstrTitle ="�ı�����";
	dlg.m_ofn .lpstrDefExt ="txt";
	dlg.m_ofn .lpstrFilter ="Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0";
	if(dlg.DoModal()==IDOK){
		CFile file(dlg.GetFileName(), CFile::modeCreate | CFile::modeWrite);
        file.Write(m_Cedit6, strlen(m_Cedit6));
        file.Close();
	}
	
}



void CDialog1::OnDoubleclickedButton1() 
{
	// TODO: Add your control notification handler code here
	
}

void CDialog1::OnButton8() 
{
	// TODO: Add your control notification handler code here
		// TODO: Add your control notification handler code here
	CFileDialog dlg(true,"txt",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"Word Files (*.doc)|*.doc|Txt Files (*.txt)|*.txt|Html Files (*.html)|*.html|Data Files (*.xlc;*.xls)|*.xlc; *.xls|All Files (*.*)|*.*||") ;    //��̬���������ļ��Ի���
	dlg.m_ofn .lpstrTitle ="�������ļ�";
	dlg.m_ofn .lpstrDefExt ="txt";
	dlg.m_ofn .lpstrFilter ="Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0";

	if(dlg.DoModal()==IDOK){
		CFile file(dlg.GetFileName(), CFile::modeRead);
		int len=(int)file.GetLength();
		char *pbuf=new char[len];

        file.Read (pbuf, file.GetLength());
		// MessageBox(pbuf);
//	m_Cedit2.Format ("");
		m_Cedit1=(CString)pbuf;//m_Cedit2Ϊ ĳһEditBox�ı���������ΪCString
    	UpdateData(false);
		delete[] pbuf;
        file.Close();

	}

}

void CDialog1::OnButton9() 
{
	// TODO: Add your control notification handler code here
	m_Cedit1="";
	m_Cedit2="";
	m_Cedit3="";
	m_Cedit4="";
	m_Cedit5="";
	m_Cedit6="";
	UpdateData(false);	
}
