// BigInt.h: interface for the CBigInt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BIGINT_H__E0A91F42_DF86_11D6_B0C1_00E04C391A51__INCLUDED_)
#define AFX_BIGINT_H__E0A91F42_DF86_11D6_B0C1_00E04C391A51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

//////////////////////////////////////////////////////////////////////
#define BI_MAXLEN   1200
#define BI_BASE     16


//////////////////////////////////////////////////////////////////////
struct bigint
{
    char	bit[BI_MAXLEN];//��λ��Ӧ��λ����λ��Ӧ��λ
    UINT	len; //��������
};
typedef struct bigint BigInt; 

//////////////////////////////////////////////////////////////////////
//�����㷨��(class CBigInt)
class CBigInt
{
public:
	CBigInt();
	bool    IsPrime(BigInt &P);//���P�Ƿ�Ϊ������
	bool    GetPrime(BigInt &P,UINT len);//��ȡ���������
	bool    PowMod(BigInt &C,BigInt &A,BigInt &B,BigInt &N);//�����˷�ȡģ
	bool	Inverse(BigInt &A,BigInt &X,BigInt &N,BigInt &Y);//��˷���Ԫ
	bool    Mul(BigInt &C,BigInt &A,BigInt &B);//�����˷�
	bool	Div(BigInt &M,BigInt &Spls,BigInt &A,BigInt &B);//��������
	bool    Add(BigInt &C,BigInt &A,BigInt &B);//�����ӷ�
	bool    Sub(BigInt &C,BigInt &A,const BigInt &B);//��������

	bool    ShR(BigInt &Out,BigInt &In,UINT len);//�����߼�����
	int     Cmp(const BigInt &A,const BigInt &B);//�����Ƚ�
	BigInt  New(long n);//����һ������
	long    GetVal(const BigInt &BI);//��ȡ������ֵ
	void	SetVal(BigInt &BI,long n);//���ô�����ֵ
	bool    BuildBIFromByte(BigInt &Out,const char *In,UINT len);//�������ֽ��鹹��һ������
	bool    BuildBIFromHalfByte(BigInt &Out,const char *In,UINT len);//��������ֽ��鹹��һ������
	bool    BuildBIFromStr(BigInt &Out,char *In,UINT len);//�������ַ�������һ������
	bool    RandVal(BigInt &Out,UINT len);//�����������

private:

	bool	GetDivNext(BigInt &Spls,const BigInt &A,const BigInt &B,int &i);

	bool    InitMulCache(BigInt &In);//��ʼ���˷�����
	void    SetLen(BigInt &BI,UINT start);//���ô����ĳ���

private:
   BigInt	MulCache[ BI_BASE ];//�˷�������
   BigInt   Zero,One,Two;
};

#endif // !defined(AFX_BIGINT_H__E0A91F42_DF86_11D6_B0C1_00E04C391A51__INCLUDED_)
