#include "StdAfx.h"
#include "Gfl.h"
CRsa::CRsa()
{
    Zero = BI.New(0);
	key = n = Zero;
}

///////////////////////////////////////////////////////////////////////////////
// CRsa Functions
///////////////////////////////////////////////////////////////////////////////
#define CHECK(x)			{if( !(x) ) return false;}
//#define CHECK_MSG(x,msg)	{if( !(x) ){CWindow::ShowMessage(msg);return false;}}
#define CHECK_MSG(x,msg)	{if( !(x) ){printf("%s\n",msg);return false;}}



/******************************************************************************/
//	名称：Encrypt
//	功能：加密
//  参数：len为加密内容的长度；KeyStr,ModStr为0结尾的密钥串，用于设置RSA密钥和模n
//	返回：加密(解密)后的密文(明文)长度

/******************************************************************************/
int  CRsa::Encrypt(char *Out,char *In,UINT len,char *KeyStr,char *ModStr)
{
	static BigInt  a,c;

	CHECK( Out && In && len && SetKey(KeyStr,ModStr) )
    // 由输入构造一个大数a
	CHECK_MSG( BI.BuildBIFromByte(a,In,len) && a.len <= n.len, "错误：RSA加密(解密)的内容过长!" )
	// 加密(解密)
	CHECK( BI.PowMod(c,a,key,n) )

    CGfL::HalfByteToByte(Out,c.bit,c.len);

	return	(c.len+1)>>1;
}
/******************************************************************************/
//	名称：SetKey
//	功能：由输入密钥字符串设置RSA密钥和模n
//  参数：KeyStr,ModStr为0结尾的密钥字符串，对应的大数密钥和模n
//	返回：设置成功返回true，否则返回false
/******************************************************************************/
bool CRsa::SetKey(char *KeyStr,char *ModStr)
{
	int		klen,nlen;

	key = n = Zero;
	CHECK_MSG( KeyStr && ModStr && KeyStr && (klen=strlen(KeyStr)) && (nlen=strlen(ModStr)) &&
		       klen<=nlen && BI.BuildBIFromStr(key,KeyStr,klen) && BI.BuildBIFromStr(n,ModStr,nlen), 
			   "设置RSA密钥出错：空密钥，或密钥太长!" )

	return true;
}
/******************************************************************************/
//	名称：GetKey
//	功能：获取RSA密钥对
//  参数：
//	返回：获取成功返回true，否则返回false
//  备注：如果p,q非空，请保证其为素数。如果需要产生素数p,q，请在调用前将p,q置0

/******************************************************************************/
bool CRsa::GetKey(BigInt &p,BigInt &q,BigInt &e,BigInt &d,BigInt &n,
		          UINT plen,UINT qlen,UINT elen)

{
	BigInt  p_1,q_1,n_1,tmp;

    // 如果p,q=0，则产生素数
	if( !p.len )
		CHECK( BI.GetPrime(p,plen) )
	if( !q.len )
		CHECK( BI.GetPrime(q,qlen) )
    
	CHECK_MSG( p.len>4 && p.len<=BI_MAXLEN/4 && q.len>4 && q.len<=BI_MAXLEN/4 &&
	           elen>=max(p.len,q.len) && elen<=p.len+q.len, "长度不在合法范围之内! " )
	CHECK_MSG( BI.Cmp(p,q), "错误：素数p,q相同!  " )
    // 计算n
	CHECK( BI.Mul(n,p,q) )
	// 防止密钥长度超过N，以免造成死循环
	if( elen>n.len )
		elen = n.len;
    p_1 = p; p_1.bit[0] -= 1;
    q_1 = q; q_1.bit[0] -= 1;
	CHECK( BI.Mul(n_1,p_1,q_1) )

	while( true )
	{
		BI.RandVal(e,elen);
		if( BI.Cmp(e,n)<0 && BI.Inverse(e,d,n_1,tmp) )
			return true;
	}
}

///////////////////////////////////////////////////////////////////////////////
// End of Files
///////////////////////////////////////////////////////////////////////////////
