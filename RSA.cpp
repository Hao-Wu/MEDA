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
//	���ƣ�Encrypt
//	���ܣ�����
//  ������lenΪ�������ݵĳ��ȣ�KeyStr,ModStrΪ0��β����Կ������������RSA��Կ��ģn
//	���أ�����(����)�������(����)����

/******************************************************************************/
int  CRsa::Encrypt(char *Out,char *In,UINT len,char *KeyStr,char *ModStr)
{
	static BigInt  a,c;

	CHECK( Out && In && len && SetKey(KeyStr,ModStr) )
    // �����빹��һ������a
	CHECK_MSG( BI.BuildBIFromByte(a,In,len) && a.len <= n.len, "����RSA����(����)�����ݹ���!" )
	// ����(����)
	CHECK( BI.PowMod(c,a,key,n) )

    CGfL::HalfByteToByte(Out,c.bit,c.len);

	return	(c.len+1)>>1;
}
/******************************************************************************/
//	���ƣ�SetKey
//	���ܣ���������Կ�ַ�������RSA��Կ��ģn
//  ������KeyStr,ModStrΪ0��β����Կ�ַ�������Ӧ�Ĵ�����Կ��ģn
//	���أ����óɹ�����true�����򷵻�false
/******************************************************************************/
bool CRsa::SetKey(char *KeyStr,char *ModStr)
{
	int		klen,nlen;

	key = n = Zero;
	CHECK_MSG( KeyStr && ModStr && KeyStr && (klen=strlen(KeyStr)) && (nlen=strlen(ModStr)) &&
		       klen<=nlen && BI.BuildBIFromStr(key,KeyStr,klen) && BI.BuildBIFromStr(n,ModStr,nlen), 
			   "����RSA��Կ��������Կ������Կ̫��!" )

	return true;
}
/******************************************************************************/
//	���ƣ�GetKey
//	���ܣ���ȡRSA��Կ��
//  ������
//	���أ���ȡ�ɹ�����true�����򷵻�false
//  ��ע�����p,q�ǿգ��뱣֤��Ϊ�����������Ҫ��������p,q�����ڵ���ǰ��p,q��0

/******************************************************************************/
bool CRsa::GetKey(BigInt &p,BigInt &q,BigInt &e,BigInt &d,BigInt &n,
		          UINT plen,UINT qlen,UINT elen)

{
	BigInt  p_1,q_1,n_1,tmp;

    // ���p,q=0�����������
	if( !p.len )
		CHECK( BI.GetPrime(p,plen) )
	if( !q.len )
		CHECK( BI.GetPrime(q,qlen) )
    
	CHECK_MSG( p.len>4 && p.len<=BI_MAXLEN/4 && q.len>4 && q.len<=BI_MAXLEN/4 &&
	           elen>=max(p.len,q.len) && elen<=p.len+q.len, "���Ȳ��ںϷ���Χ֮��! " )
	CHECK_MSG( BI.Cmp(p,q), "��������p,q��ͬ!  " )
    // ����n
	CHECK( BI.Mul(n,p,q) )
	// ��ֹ��Կ���ȳ���N�����������ѭ��
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
