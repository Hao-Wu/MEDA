// Des.h: interface for the CDes class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DES_H__E0A91F40_DF86_11D6_B0C1_00E04C391A51__INCLUDED_)
#define AFX_DES_H__E0A91F40_DF86_11D6_B0C1_00E04C391A51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//////////////////////////////////////////////////////////////////////
#include "FileInOut.h"

//////////////////////////////////////////////////////////////////////
#define BUFSIZE (1024*50)

//////////////////////////////////////////////////////////////////////
struct deshead
{
	UCHAR	Ver; //�汾
	DWORD	TLen;//�ļ�����
	char    DesKey[16];//DES��Կ����
};
typedef struct	deshead DesHead;
typedef bool	(*PSubKey)[16][48];
enum	{ENCRYPT,DECRYPT};
//////////////////////////////////////////////////////////////////////
//DES(class CDes)
class CDes: public CFileInOut
{
public:

	bool	Des2Encrypt(const char *OutFile,const char *InFile,const char *KeyStr);//����
	bool	Des2Decrypt(const char *OutFile,const char *InFile,const char *KeyStr);//����

	bool	Des2Encrypt(HFILE &fh_out,HFILE &fh_in,const char *KeyStr);//����
	bool	Des2Decrypt(HFILE &fh_out,HFILE &fh_in,const char *KeyStr);//����

	bool	Des2Encrypt(char *Out,char *In,UINT len,const char *KeyStr=0);//����
	bool	Des2Decrypt(char *Out,char *In,UINT len,const char *KeyStr=0);//����
	bool	Des2SetSubKey(const char *KeyStr);//��������Կ����������Կ
	static	char* Des2RandKeyStr(char KeyStr[9]);//���������Կ��
private:

	void	Des2DES(char Out[8],char In[8],const PSubKey pSubKey,bool Type=ENCRYPT);//��/����

	void	Des2SetSubKey(PSubKey pSubKey,const char Key[8]);//��������Կ����16Ȧ����Կ
	void	Des2F_func(bool In[32],const bool Ki[48]);//f ����
	void	Des2S_func(bool Out[32],const bool In[48]);//S �д���

private:
	bool	SubKey[2][16][48];//16Ȧ����Կ
	bool    Is3DES;//3��DES��־
	char    deskey[17];//��Կ��������
	char    databuf[BUFSIZE];//���ݻ�����
	DesHead deshead;//��Ϣͷ
};

#endif // !defined(AFX_DES_H__E0A91F40_DF86_11D6_B0C1_00E04C391A51__INCLUDED_)
