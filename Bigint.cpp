#include "stdafx.h"
#include "Gfl.h"
#include "BigInt.h"

#include "Window.h"

///////////////////////////////////////////////////////////////////////////////
// Little Primes
///////////////////////////////////////////////////////////////////////////////

#define PTL 550
const static int PrimeTable[PTL] =
{   3,    5,    7,    11,   13,   17,   19,   23,   29,   31,
    37,   41,   43,   47,   53,   59,   61,   67,   71,   73,
	79,   83,   89,   97,   101,  103,  107,  109,  113,  127, 
	131,  137,  139,  149,  151,  157,  163,  167,  173,  179, 
	181,  191,  193,  197,  199,  211,  223,  227,  229,  233, 
	239,  241,  251,  257,  263,  269,  271,  277,  281,  283, 
	293,  307,  311,  313,  317,  331,  337,  347,  349,  353, 
	359,  367,  373,  379,  383,  389,  397,  401,  409,  419, 
	421,  431,  433,  439,  443,  449,  457,  461,  463,  467, 
	479,  487,  491,  499,  503,  509,  521,  523,  541,  547, 
	557,  563,  569,  571,  577,  587,  593,  599,  601,  607, 
	613,  617,  619,  631,  641,  643,  647,  653,  659,  661, 
	673,  677,  683,  691,  701,  709,  719,  727,  733,  739, 
	743,  751,  757,  761,  769,  773,  787,  797,  809,  811, 
	821,  823,  827,  829,  839,  853,  857,  859,  863,  877,
	881,  883,  887,  907,  911,  919,  929,  937,  941,  947, 
	953,  967,  971,  977,  983,  991,  997,  1009, 1013, 1019, 
	1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087,
	1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153, 
	1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223, 1229, 
	1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291, 1297, 
	1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373, 1381,
	1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451, 1453, 
	1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511, 1523,
	1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583, 1597, 
	1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657, 1663, 
	1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733, 1741, 
	1747, 1753, 1759, 1777, 1783, 1787, 1789, 1801, 1811, 1823, 
	1831, 1847, 1861, 1867, 1871, 1873, 1877, 1879, 1889, 1901, 
	1907, 1913, 1931, 1933, 1949, 1951, 1973, 1979, 1987, 1993, 
	1997, 1999, 2003, 2011, 2017, 2027, 2029, 2039, 2053, 2063,
	2069, 2081, 2083, 2087, 2089, 2099, 2111, 2113, 2129, 2131, 
	2137, 2141, 2143, 2153, 2161, 2179, 2203, 2207, 2213, 2221, 
	2237, 2239, 2243, 2251, 2267, 2269, 2273, 2281, 2287, 2293,
	2297, 2309, 2311, 2333, 2339, 2341, 2347, 2351, 2357, 2371,
	2377, 2381, 2383, 2389, 2393, 2399, 2411, 2417, 2423, 2437, 
	2441, 2447, 2459, 2467, 2473, 2477, 2503, 2521, 2531, 2539, 
	2543, 2549, 2551, 2557, 2579, 2591, 2593, 2609, 2617, 2621, 
	2633, 2647, 2657, 2659, 2663, 2671, 2677, 2683, 2687, 2689, 
	2693, 2699, 2707, 2711, 2713, 2719, 2729, 2731, 2741, 2749, 
	2753, 2767, 2777, 2789, 2791, 2797, 2801, 2803, 2819, 2833, 
	2837, 2843, 2851, 2857, 2861, 2879, 2887, 2897, 2903, 2909,
	2917, 2927, 2939, 2953, 2957, 2963, 2969, 2971, 2999, 3001,
	3011, 3019, 3023, 3037, 3041, 3049, 3061, 3067, 3079, 3083,
	3089, 3109, 3119, 3121, 3137, 3163, 3167, 3169, 3181, 3187, 
	3191, 3203, 3209, 3217, 3221, 3229, 3251, 3253, 3257, 3259, 
	3271, 3299, 3301, 3307, 3313, 3319, 3323, 3329, 3331, 3343,
	3347, 3359, 3361, 3371, 3373, 3389, 3391, 3407, 3413, 3433, 
	3449, 3457, 3461, 3463, 3467, 3469, 3491, 3499, 3511, 3517, 
	3527, 3529, 3533, 3539, 3541, 3547, 3557, 3559, 3571, 3581,
    3583, 3593, 3607, 3613, 3617, 3623, 3631, 3637, 3643, 3659, 
	3671, 3673, 3677, 3691, 3697, 3701, 3709, 3719, 3727, 3733, 
	3739, 3761, 3767, 3769, 3779, 3793, 3797, 3803, 3821, 3823, 
	3833, 3847, 3851, 3853, 3863, 3877, 3881, 3889, 3907, 3911, 
	3917, 3919, 3923, 3929, 3931, 3943, 3947, 3967, 3989, 4001
};

////////////////////////////////////////////////////////////////////////////////
// Construction
////////////////////////////////////////////////////////////////////////////////
CBigInt::CBigInt()
{
	Zero= New(0);
    One = New(1);
    Two = New(2);
    MulCache[0] = Zero;
}

////////////////////////////////////////////////////////////////////////////////
// CBigInt Functions
////////////////////////////////////////////////////////////////////////////////
#define CHECK(x)			{if( !(x) ) return false;}
#define CHECK_MSG(x,msg)	{if( !(x) ){CWindow::ShowMessage(msg);return false;}}
#define EQUAL(BI,y)			( BI.len==1 && BI.bit[0]==y )

/******************************************************************************/
//	名称：GetPrime
//	功能：获取随机大素数
//  参数：len—大素数长度>4,<=BI_MAXLEN/4
//	返回：获取成功返回true，否则返回false

/******************************************************************************/
bool CBigInt::GetPrime(BigInt &P,UINT len)
{
	/////////////////////////////////////////////////////////////////
  // CHECK_MSG( len>4 && len<=BI_MAXLEN/4, "素数长度不在合法范围之内!" )
   
	BigInt P_1,P_1Div2,LtP,A,Tmp;

	int			k=0;

 ////////////////////////////////////////////////////////////////////
Next:	++k;
	// 产生一个随机大数(奇数) P
	RandVal(P,len);
    P.bit[len-1] |= BI_BASE>>1;
    // 先用小素数测试
    for(int i=0; i<PTL; ++i)
    {
		SetVal(LtP,PrimeTable[i]);
        CHECK( Div(Tmp,A,P,LtP) )
        if( !A.len )
            goto Next;
    }
    // 再用 Lehmann 方法测试
    P_1=P; P_1.bit[0] -= 1;
    CHECK( Div(P_1Div2,Tmp,P_1,Two) )
    for(i=0; i<5; ++i)
    {   // 产生一个小随机大数 A
		SetVal(A,rand()+2);
        CHECK( PowMod(Tmp,A,P_1Div2,P) )
        if( ! ( EQUAL(Tmp,1)||!Cmp(Tmp,P_1) ) )
		{   
#ifdef _DEBUG_
			printf("正在测试第%d个随机大数......\n",k);
#endif
            goto Next;
		}
    }
    // 结束等待光标
    return true;
}
/******************************************************************************/
//	名称：IsPrime
//	功能：检查P是否为大素数
//  参数：
//	返回：是返回true，否则返回false

/******************************************************************************/
bool CBigInt::IsPrime(BigInt &P)
{
    // 如为素数，最后一位必为奇数
    CHECK( P.bit[0]%2 )

//	CWindow		wnd;
    // 显示等待光标
//    wnd.ShowWaitCursor();
//	wnd.SetWindowCaption("正在测试该数是否是素数......");

	BigInt P_1,P_1Div2,A,Tmp;

    // 用 Lehmann 方法测试
    P_1=P; P_1.bit[0] -= 1;
    CHECK( Div(P_1Div2,Tmp,P_1,Two) )
    for(int i=0; i<3; ++i)
    {   // 产生一个小随机大数 a
		SetVal(A,rand()+2);
        CHECK( PowMod(Tmp,A,P_1Div2,P) )
        CHECK( EQUAL(Tmp,1) || !Cmp(Tmp,P_1) )
    }

    // 结束等待光标
//	wnd.EndWaitCursor();
    return true;
}
/******************************************************************************/
//	名称：PowMod
//	功能：大数乘方取模 ( C = Power(A,B) (Mod N) )
//  参数：
//	返回：成功返回true，否则返回false

/******************************************************************************/
bool CBigInt::PowMod(BigInt &c,BigInt &a,BigInt &b,BigInt &n)
{
	// n != 0
	CHECK( n.len ) 

	static bool		bits[ BI_MAXLEN*4 ];
    static BigInt	Out,Tmp,M,ModCache[ BI_MAXLEN*4 ];

    // ModCache[i] = Power(a, Power(2,i) ) (Mod n)
    CHECK( Div(M,ModCache[0],a,n) )
    for(int i=1,j=b.len<<2; i<j ; ++i)
    {   
        CHECK( Mul(Tmp,ModCache[i-1],ModCache[i-1]) )
        CHECK( Div(M,ModCache[i],Tmp,n) )
    }

    Out = One;
	// 将b分解成位组
	CGfL::ByteToBit(bits,b.bit,b.len,4);
    for(i=0; i<j; ++i)
    {
        if(bits[i])
        {
            CHECK( Mul(Tmp,Out,ModCache[i]) )
            CHECK( Div(M,Out,Tmp,n) )
        }
    }
	c = Out;

    return true;
}
/******************************************************************************/
//	名称：Inverse
//	功能：求乘法逆元 ( 即求X使 AX = 1 (mod N) )
//  参数：X—乘法逆元
//	返回：成功(A,N互素)返回 true; 否则返回 false
//  备注：虽然该算法使用递归，但它的时间效率和空间效率都非常高(我曾将书上的算法改成大数版，
//        但它连10位(16进制)都跑不起来，而我的算法跑500位(16进制)不超过2秒钟，简直没法比)
//        该算法使用动态内存分配存储中间大数，所以根本不会产生栈溢出错误，因为递归时压入
//        栈中的只是几个指针。

/******************************************************************************/
#define IV_CHECK(x) {if( !(x) ){ if(Spls)delete(Spls); if(M)delete(M);return false; }}

bool CBigInt::Inverse(BigInt &a,BigInt &X,BigInt &n,BigInt &Y)
{ 
    BigInt *Spls=new(BigInt),*M=new(BigInt);

	// 检查申请内存是否成功
	IV_CHECK( Spls && M )

	IV_CHECK( Div(*M,*Spls,n,a) )
	// 检查余数是否为0
    IV_CHECK( Spls->len )

    if( EQUAL((*Spls),1) )
    {
        Sub(X,n,*M);
        Sub(Y,a,One);
    }
    else
    {
		// 递归调用
        CHECK( Inverse(*Spls,X,a,Y) )

        static BigInt Tmp;
        IV_CHECK( Mul(Tmp,X,*M) )
        IV_CHECK( Add(Tmp,Tmp,Y) )
        IV_CHECK( Sub(Y,a,X) )
        IV_CHECK( Sub(X,n,Tmp) )
    }

	delete(Spls); 
    delete(M);

	return true;
}
/******************************************************************************/
//	名称：Mul
//	功能：大数乘法 ( C = a * b )
//  参数：
//	返回：成功返回true，否则返回false
//  备注：
/******************************************************************************/
bool CBigInt::Mul(BigInt &C,BigInt &a,BigInt &b)
{
    static BigInt Out,Tmp,*pa,*pb;

    if( a.len > b.len )
		pa=&a,pb=&b;
	else
		pa=&b,pb=&a;

    Out = Zero;
	CHECK( InitMulCache(*pa) )

	for(int i=0,j=b.len; i<j; ++i)
    {
        if( pb->bit[i] )
        {
            CHECK( ShR(Tmp,MulCache[ pb->bit[i] ],i) )
            CHECK( Add(Out,Out,Tmp) )
        }
    }
    C = Out;

    return true;
}
/******************************************************************************/
//	名称：GetDivNext
//	用途：从a中(高位(由i确定)到低位)移入一些位到Spls中，使Spls>=b
//  参数：i—指向a的"当前最高位"
//	返回：成功返回true,否则返回false
//  备注：

/******************************************************************************/
bool CBigInt::GetDivNext(BigInt &Spls,const BigInt &a,const BigInt &b,int &i)
{
	do{
		int k = b.len - Spls.len;
		if( k>0 )
		{
			if( i >= k-1 )
			{   
				i -= k;
				ShR(Spls,Spls,k);
				memcpy(Spls.bit,a.bit+i+1,k);
				// 如果Spls为0,则必须重设长度，因为移入的高位可能是0
				if( !Spls.len )
					SetLen(Spls,b.len-1);
			}
			else
			{
				ShR(Spls,Spls,i+1);
				memcpy(Spls.bit,a.bit ,i+1);
				if( !Spls.len )
					SetLen(Spls,i);
				return false;
			}
		}

		if( Cmp(Spls,b)<0 )
		{
			if( i>=0 )
			{
				ShR(Spls,Spls,1);
				Spls.bit[0] = a.bit[i--];
				if( !Spls.len && Spls.bit[0] )
					Spls.len = 1;
			}
			else
			{
				return false;
			}
		}
	}while( Spls.len < b.len );

	return true;
}
/******************************************************************************/
//	名称：BI_Div
//	功能：大数除法 ( M = a/b; Spls = a (Mod b) )
//  参数：
//	返回：成功返回true，否则返回false 
//  备注：

/******************************************************************************/
bool CBigInt::Div(BigInt &M,BigInt &Spls,BigInt &a,BigInt &b)
{
	// b != 0
	CHECK( b.len )

	if( Cmp(a,b)<0 )
    {
        M = Zero;
        Spls = a;
        return true;
    }

    static BigInt Out,Mod;
 
	Out = Mod = Zero;
    InitMulCache(b);
    for(int i=a.len-1,f,h,t,m; i>=0; )
    {
        if( !GetDivNext(Mod,a,b,i) )
            break;
        //用二分法找商
        h=1; t=BI_BASE-1;
        while( h<=t )
        {
            m = (h+t) >> 1;
            f = Cmp(MulCache[m],Mod);
            if( !f )
                break;
            if( f>0 )
                t = m-1;
            else
                h = m+1;
        }
        Out.bit[i+1] = f ? --h : m;

        if(f)
            Sub(Mod,Mod,MulCache[h]);
        else 
            Mod = Zero;
     }
    
    SetLen( Out,a.len-b.len);
	Spls = Mod;
	M = Out;

    return true;
}
/******************************************************************************/
//  名称：Add
//  功能：大数加法 ( C = a + b )
//  参数：
//	返回：成功返回true，否则返回false
//  备注：

/***************************************************************************/
bool CBigInt::Add(BigInt &C,BigInt &a,BigInt &b)
{
    static BigInt Out,*pa,*pb;

    if( a.len > b.len )
		pa=&a,pb=&b;
	else
		pa=&b,pb=&a;

	Out = *pa;

	for(UINT i=0,carry=0,j=pb->len,tmp; i<j; ++i)
    {
        tmp = pa->bit[i] + pb->bit[i] + carry;
        if( tmp > BI_BASE-1 )
        {
            tmp -= BI_BASE;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        Out.bit[i] = tmp;
    }

	if(carry)
    {
        while( Out.bit[i] == BI_BASE-1 )
        {
            Out.bit[i] = 0;
            CHECK( ++i < BI_MAXLEN );
        }
        CHECK( i < BI_MAXLEN );
        ++Out.bit[i];
        if( i == pa->len )
            ++Out.len;
    }

    C = Out;

	return true;
}
/******************************************************************************/
//	名称：Sub
//	功能：大数减法 ( C = a - b )
//  参数：
//	返回：成功返回true，否则返回false
//  备注：调用前保证a >= b，否则结果不对

/******************************************************************************/
bool CBigInt::Sub(BigInt &C,BigInt &a,const BigInt &b)
{
	if( &C != &a )
		C = a;

    for(int i=0,carry=0,j=b.len,tmp; i<j; ++i)
    {
        tmp = a.bit[i] - b.bit[i] - carry;
        if( tmp<0 )
        {
            tmp += BI_BASE;
            carry = 1;
        }
        else
		{
            carry = 0;
		}
        C.bit[i] = tmp;
    }
    
    if(carry)
    {
        while( !C.bit[i] )
        {
            C.bit[i] = BI_BASE-1;
            CHECK( ++i < BI_MAXLEN );
        }
        CHECK( i < BI_MAXLEN );
        --C.bit[i];
    }

	SetLen(C,C.len-1);

	return true;
}
/******************************************************************************/
//	名称：InitMulCache
//	功能：初始化乘法缓存 ( MulCache[i] = In*i )
//  参数：
//	返回：成功返回true，否则返回false
//  备注：
/******************************************************************************/
bool CBigInt::InitMulCache(BigInt &In)
{
    MulCache[1] = In;

	for(int i=2; i<BI_BASE; ++i)
	{
		CHECK( Add(MulCache[i],MulCache[i-1],In) )
	}

	return true;
}
/******************************************************************************/
//  名称：SetLen
//  功能：设置大数的长度
//  参数：
//	返回：
//  备注：

/***************************************************************************/
void CBigInt::SetLen(BigInt &BI,UINT start)
{
	for( int i=start; i>=0 && !BI.bit[i]; --i );

    BI.len = i+1;
}
/******************************************************************************/
//	名称：ShR
//	功能：大数逻辑右移
//  参数：
//	返回：成功返回true，否则返回false
//  备注：

/******************************************************************************/
bool CBigInt::ShR(BigInt &Out,BigInt &In,UINT len)
{
    CHECK( (In.len+len) <= BI_MAXLEN )
    
    if( !len )
	{
		if( &Out != &In )
			Out = In;
	}
    else if( In.len )
    {
        static BigInt Tmp;
		Tmp = Zero;
        memcpy(Tmp.bit+len,In.bit,In.len);
        Tmp.len = In.len + len;
		Out = Tmp;
    }

	return true;
}
/******************************************************************************/
//	名称：Cmp
//	功能：大数比较
//  参数：
//	返回：a>b 返回 1; a=b 返回 0; a<b 返回 -1
//  备注：
/******************************************************************************/
int CBigInt::Cmp(const BigInt &a,const BigInt &b)
{
    int i=a.len;

	if( (UINT)i > b.len )
	    return 1;
	if( (UINT)i < b.len )
	    return -1;

    for(--i; i>=0; --i)
    {
        if( a.bit[i] > b.bit[i] )
            return 1;
        if( a.bit[i] < b.bit[i] )
            return -1;
    }

    return 0;
}
/******************************************************************************/
//	名称：New
//	功能：产生一个大数
//  参数：
//	返回：
//  备注：

/******************************************************************************/
BigInt CBigInt::New(long n)
{
    int i=0;
    BigInt Out;

    memset(Out.bit,0,BI_MAXLEN);
    while(n)
    {
        Out.bit[i++] = n%BI_BASE;
        n /= BI_BASE;
    }
    Out.len = i;
    
    return Out;
}
/******************************************************************************/
//	名称：GetVal
//	功能：获取大数的值
//  参数：
//	返回：
//  备注：

/******************************************************************************/
long CBigInt::GetVal(const BigInt &In)
{
    CHECK( In.len )
    
    long n=0;

    for(int i=In.len-1; i>=0; --i)
    {
        n *= BI_BASE;
        n += In.bit[i];
    }

    return n;
}
/******************************************************************************/
//	名称：SetVal
//	功能：设置大数的值
//  参数：
//	返回：
//  备注：

/******************************************************************************/
void CBigInt::SetVal(BigInt &BI,long n)
{
    int i=0;

    BI = Zero;
    while(n)
    {
        BI.bit[i++] = n%BI_BASE;
        n /= BI_BASE;
    }
    BI.len = i;
}
/******************************************************************************/
//	名称：BuildBIFromByte
//	功能：由输入字节组构造一个大数
//  参数：
//	返回：构造成功返回true，否则返回false
//  备注：

/******************************************************************************/
bool CBigInt::BuildBIFromByte(BigInt &Out,const char *In,UINT len)
{
	CHECK( In && len<=BI_MAXLEN/4 )

    Out = Zero;
	CGfL::ByteToHalfByte(Out.bit,In,len);
    SetLen(Out,len<<1);

	return true;
}
/******************************************************************************/
//	名称：BuildBIFromHalfByte
//	功能：由输入半字节组构造一个大数
//  参数：
//	返回：构造成功返回true，否则返回false
//  备注：

/******************************************************************************/
bool CBigInt::BuildBIFromHalfByte(BigInt &Out,const char *In,UINT len)
{
	CHECK( In && len<=BI_MAXLEN/2 )

    Out = Zero;
	memcpy(Out.bit,In,len);
    SetLen(Out,len);

	return true;
}
/******************************************************************************/
//	名称：BuildBIFromStr
//	功能：由输入字符串构造一个大数
//  参数：len—字符串长度
//	返回：构造成功返回true，否则返回false
//  备注：

/******************************************************************************/
bool CBigInt::BuildBIFromStr(BigInt &Out,char *In,UINT len)
{
	CHECK( In && len<=BI_MAXLEN/2 )

    Out = Zero;
	CGfL::StrToHalfByte( Out.bit,In,len);
    SetLen(Out,len);

	return true;
}
/******************************************************************************/
//	名称：Rand
//	功能：产生随机大数
//  参数：len—随机大数的长度
//	返回：产生成功返回true，否则返回false

/******************************************************************************/
bool CBigInt::RandVal(BigInt &Out,UINT len)
{
    CHECK( len>0 && len<=BI_MAXLEN )

	Out = Zero;
    srand(GetTickCount());
    for(UINT i=0; i<len; ++i)
	{
        Out.bit[i] = rand()%BI_BASE;
	}

    Out.bit[0] |= 1;  //确保是奇数
    Out.bit[len-1] |= 1; //确保是len长的数
	Out.len = len;

	return true;
}
///////////////////////////////////////////////////////////////////////////////
// End of Files
///////////////////////////////////////////////////////////////////////////////
