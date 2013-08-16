#include "StdAfx.h"
#include "Gfl.h"
#include <string>
using namespace std ;

BigInt	p,q,n,e,d;
string	m_p;
string	m_q;
string	m_d;
string	m_e;
string	m_n;
void OnGetKey() 
{
	CBigInt BI;
	CRsa	rsa;

	int		m_plen=60;
	int		m_qlen=60;
	int		m_elen=120;

	char	buf[BI_MAXLEN+1];
	
	BI.GetPrime(p,m_plen);
	BI.GetPrime(q,m_qlen);
	rsa.GetKey(p,q,e,d,n,0,0,m_elen);

	CGfL::HalfByteToStr(buf,p.bit,p.len);
	m_p = buf;
	
	CGfL::HalfByteToStr(buf,q.bit,q.len);
	m_q = buf;
		
	CGfL::HalfByteToStr(buf,e.bit,e.len);
	m_e = buf;
		
	CGfL::HalfByteToStr(buf,n.bit,n.len);
	m_n = buf;
	
	CGfL::HalfByteToStr(buf,d.bit,d.len);
	m_d = buf;
}



void OnCrypt(char *plaintext,char *ciphertext) 
{
	CRsa	rsa;

	rsa.Encrypt(ciphertext,plaintext,strlen(plaintext),
		(char *)m_e.c_str(),(char *)m_n.c_str());
}


void OnDeCrypt(char *plaintext,char *ciphertext) 
{
	CRsa	rsa;

	rsa.Decrypt(plaintext,ciphertext,strlen(ciphertext),
		(char *)m_d.c_str(),(char *)m_n.c_str());
}




void RSA_Encrypt(char *plaintext,char *chiphertext,int key ,bool flag)
{
	OnGetKey();
	if(flag==true)
	{

	}
	else 
	{
		OnCrypt(plaintext,chiphertext);
	}
}


void RSA_DeCrypt(char *plaintext,char *chiphertext,int key ,bool flag)
{
	if(flag==true)
	{

	}
	else 
	{
		OnDeCrypt(plaintext,chiphertext);
	}
}