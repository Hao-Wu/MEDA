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
    char	bit[BI_MAXLEN];//低位对应低位，高位对应高位
    UINT	len; //大数长度
};
typedef struct bigint BigInt; 

//////////////////////////////////////////////////////////////////////
//大数算法库(class CBigInt)
class CBigInt
{
public:
	CBigInt();
	bool    IsPrime(BigInt &P);//检查P是否为大素数
	bool    GetPrime(BigInt &P,UINT len);//获取随机大素数
	bool    PowMod(BigInt &C,BigInt &A,BigInt &B,BigInt &N);//大数乘方取模
	bool	Inverse(BigInt &A,BigInt &X,BigInt &N,BigInt &Y);//求乘法逆元
	bool    Mul(BigInt &C,BigInt &A,BigInt &B);//大数乘法
	bool	Div(BigInt &M,BigInt &Spls,BigInt &A,BigInt &B);//大数除法
	bool    Add(BigInt &C,BigInt &A,BigInt &B);//大数加法
	bool    Sub(BigInt &C,BigInt &A,const BigInt &B);//大数减法

	bool    ShR(BigInt &Out,BigInt &In,UINT len);//大数逻辑右移
	int     Cmp(const BigInt &A,const BigInt &B);//大数比较
	BigInt  New(long n);//产生一个大数
	long    GetVal(const BigInt &BI);//获取大数的值
	void	SetVal(BigInt &BI,long n);//设置大数的值
	bool    BuildBIFromByte(BigInt &Out,const char *In,UINT len);//由输入字节组构造一个大数
	bool    BuildBIFromHalfByte(BigInt &Out,const char *In,UINT len);//由输入半字节组构造一个大数
	bool    BuildBIFromStr(BigInt &Out,char *In,UINT len);//由输入字符串构造一个大数
	bool    RandVal(BigInt &Out,UINT len);//产生随机大数

private:

	bool	GetDivNext(BigInt &Spls,const BigInt &A,const BigInt &B,int &i);

	bool    InitMulCache(BigInt &In);//初始化乘法缓存
	void    SetLen(BigInt &BI,UINT start);//设置大数的长度

private:
   BigInt	MulCache[ BI_BASE ];//乘法缓冲区
   BigInt   Zero,One,Two;
};

#endif // !defined(AFX_BIGINT_H__E0A91F42_DF86_11D6_B0C1_00E04C391A51__INCLUDED_)
