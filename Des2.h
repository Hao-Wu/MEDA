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
	UCHAR	Ver; //版本
	DWORD	TLen;//文件长度
	char    DesKey[16];//DES密钥密文
};
typedef struct	deshead DesHead;
typedef bool	(*PSubKey)[16][48];
enum	{ENCRYPT,DECRYPT};
//////////////////////////////////////////////////////////////////////
//DES(class CDes)
class CDes: public CFileInOut
{
public:

	bool	Des2Encrypt(const char *OutFile,const char *InFile,const char *KeyStr);//加密
	bool	Des2Decrypt(const char *OutFile,const char *InFile,const char *KeyStr);//解密

	bool	Des2Encrypt(HFILE &fh_out,HFILE &fh_in,const char *KeyStr);//加密
	bool	Des2Decrypt(HFILE &fh_out,HFILE &fh_in,const char *KeyStr);//解密

	bool	Des2Encrypt(char *Out,char *In,UINT len,const char *KeyStr=0);//加密
	bool	Des2Decrypt(char *Out,char *In,UINT len,const char *KeyStr=0);//解密
	bool	Des2SetSubKey(const char *KeyStr);//由输入密钥串设置子密钥
	static	char* Des2RandKeyStr(char KeyStr[9]);//产生随机密钥串
private:

	void	Des2DES(char Out[8],char In[8],const PSubKey pSubKey,bool Type=ENCRYPT);//加/解密

	void	Des2SetSubKey(PSubKey pSubKey,const char Key[8]);//由输入密钥设置16圈子密钥
	void	Des2F_func(bool In[32],const bool Ki[48]);//f 函数
	void	Des2S_func(bool Out[32],const bool In[48]);//S 盒代替

private:
	bool	SubKey[2][16][48];//16圈子密钥
	bool    Is3DES;//3次DES标志
	char    deskey[17];//密钥串缓冲区
	char    databuf[BUFSIZE];//数据缓冲区
	DesHead deshead;//信息头
};

#endif // !defined(AFX_DES_H__E0A91F40_DF86_11D6_B0C1_00E04C391A51__INCLUDED_)
