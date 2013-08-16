// Des.cpp: implementation of the CDes class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
//#include "MixedCS.h"
#include "Des2.h"
#include "Window.h"
#include "GfL.h"
//#include "Progress.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////////////
// DES Tables Define
///////////////////////////////////////////////////////////////////////////////

// initial permutation IP
const static char IP_Table[64] = 
{
	58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17,  9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
};
// final permutation IP^-1 
const static char IPR_Table[64] = 
{
	40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41,  9, 49, 17, 57, 25
};
// expansion operation matrix
static const char E_Table[48] = 
{
	32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
	 8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1
};
// 32-bit permutation function P used on the output of the S-boxes 
const static char P_Table[32] = 
{
	16, 7, 20, 21, 29, 12, 28, 17, 1,  15, 23, 26, 5,  18, 31, 10,
	2,  8, 24, 14, 32, 27, 3,  9,  19, 13, 30, 6,  22, 11, 4,  25
};
// permuted choice table (key) 
const static char PC1_Table[56] = 
{
	57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
	10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
	14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4
};
// permuted choice key (table) 
const static char PC2_Table[48] = 
{
	14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
	23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
	41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};
// number left rotations of pc1 
const static char LOOP_Table[16] = 
{
	1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};
// The (in)famous S-boxes 
const static char S_Box[8][4][16] = 
{
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

///////////////////////////////////////////////////////////////////////////////
// CDes Functions
///////////////////////////////////////////////////////////////////////////////
#define CHECK(x)			{if( !(x) ) return false;}
#define CHECK_MSG(x,msg)	{if( !(x) ){CWindow::ShowMessage(msg);return false;}}
#define FILE_CHECK(x,file)	{if( !(x) ) {RunError(file);return false;}}

/******************************************************************************/

/******************************************************************************/
bool CDes::Des2Encrypt(const char *OutFile,const char *InFile,const char *KeyStr)
{
	CHECK( KeyStr && OpenFile(OutFile,InFile) )

	FILE_CHECK( Des2Encrypt(fh_out,fh_in,KeyStr),OutFile )

	CloseFile();
	return true;
}
/******************************************************************************/

/******************************************************************************/
bool CDes::Des2Decrypt(const char *OutFile,const char *InFile,const char *KeyStr)
{
	CHECK( KeyStr && OpenFile(OutFile,InFile) )

	FILE_CHECK( Des2Decrypt(fh_out,fh_in,KeyStr),OutFile )

	CloseFile();
	return true;
}

bool CDes::Des2Encrypt(HFILE &fh_out,HFILE &fh_in,const char *KeyStr)
{
	CWindow  wnd;
	long     len,k=0,TBlock;

    // 设置子密钥
    CHECK( Des2SetSubKey(KeyStr) )
	// 版本信息
	deshead.Ver = 1;
    // 文件长度信息
	deshead.TLen = GetFileSize((HANDLE)fh_in,0);
	// 计算总块数
    TBlock=(deshead.TLen+BUFSIZE-1)/BUFSIZE;
	// 加密密钥串(用于解密时验证密钥的正确性)
	memset(deskey,0,16);
	strcpy(deskey,KeyStr);
	Des2Encrypt(deshead.DesKey,deskey,16);
	// 写入信息头
	_lwrite(fh_out,(char*)&deshead,sizeof(deshead));
    // 显示等待光标
	wnd.ShowWaitCursor();

	// 读取明文到缓冲区
//wnd.SetWindowCaption("共计%d块数据，......",TBlock);
	while( (len=_lread(fh_in,databuf,BUFSIZE)) >0 )
	{   // 显示加密进度
      wnd.SetWindowCaption("共计%d块数据，DES正在加密第%d块......",TBlock,++k);
        // 将缓冲区长度变为8的倍数
		len = ((len+7)>>3)<<3;
		// 在缓冲区中加密
		Des2Encrypt(databuf,databuf,len);
		// 将密文写入输出文件
		_lwrite(fh_out,databuf,len);

		//	CProgress m_progress1;
		 
	//	for(long Lenth=0;Lenth<TBlock;Lenth++) 
	//	m_progress1.SetPos(Lenth); 
	}

    // 结束等待光标
	wnd.EndWaitCursor();
	return true;
}
/******************************************************************************/
//	名称：Decrypt
//	功能：解密
//  参数：fh_out,fh_in为输入输出句柄；KeyStr为0结尾的密钥串，长度<=16，可为任意字符
//	返回：解密成功返回true，否则返回false
//  备注：当密钥长度>8时，系统自动使用3次DES解密
/******************************************************************************/
bool CDes::Des2Decrypt(HFILE &fh_out,HFILE &fh_in,const char *KeyStr)
{
	CWindow  wnd;
	long     len,k=0,TBlock;

    // 设置子密钥
    CHECK( Des2SetSubKey(KeyStr) )
	// 读取信息头并检查长度
	CHECK_MSG( _lread(fh_in,&deshead,sizeof(deshead)) == sizeof(deshead),
	           "错误：该文件不是有效的DES加密文件!" )
    // 版本控制
	CHECK_MSG( deshead.Ver ==1,"该版程序无法解密此文件。\n请使用该程序的最新版。")
	// 解密密钥串
    Des2Decrypt(deshead.DesKey,deshead.DesKey,16);
	// 验证密钥的正确性
	memset(deskey,0,16);
	strcpy(deskey,KeyStr);//密钥串长度一定<=16
    CHECK_MSG( !memcmp(deshead.DesKey,deskey,16), "错误：DES密钥不正确! ");
	// 计算总块数
	TBlock=(deshead.TLen+BUFSIZE-1)/BUFSIZE;
	// 显示等待光标
	wnd.ShowWaitCursor();

	// 读取密文到缓冲区
	while( (len=_lread(fh_in,databuf,BUFSIZE)) >0 )
	{   // 显示解密进度
    	wnd.SetWindowCaption("共计%d块数据，DES正在解密第%d块......",TBlock,++k);
		// 将缓冲区长度变为8的倍数
		len = ((len+7)>>3)<<3;
		// 在缓冲区中解密
		Des2Decrypt(databuf,databuf,len);
		// 将明文写入输出文件
		_lwrite(fh_out,databuf,len);
	}
	// 设置解密文件长度
	_llseek(fh_out,deshead.TLen,SEEK_SET);
	SetEndOfFile((HANDLE)fh_out);

	// 结束等待光标
	wnd.EndWaitCursor();
	return true;
}
/******************************************************************************/
//	名称：Encrypt
//	功能：加密
//  参数：len—数据长度，必须是8的倍数；KeyStr为0结尾的密钥串，长度<=16，可为任意字符
//        KeyStr默认值为0，如果你在调用前设置过子密钥，则可省略该参数。例:
//        SetSubKey(KeyStr);Encrypt(data,data,len);或:Encrypt(data,data,len,KeyStr);
//	返回：加密成功返回true，否则返回false
//  备注：当密钥长度>8时，系统自动使用3次DES加密
/******************************************************************************/
bool CDes::Des2Encrypt(char *Out,char *In,UINT len,const char *KeyStr)
{
    CHECK( Out && In && !(len&0x7) )

	if( KeyStr )
		CHECK( Des2SetSubKey(KeyStr) )

	if( !Is3DES )
	{   // 1次DES
		for(int i=0,j=len>>3; i<j; ++i)
		{
			Des2DES(Out,In,&SubKey[0],ENCRYPT);
			Out += 8; In += 8;
		}
	}
	else
	{   // 3次DES E-D-E
		for(int i=0,j=len>>3; i<j; ++i)
		{
			Des2DES(Out,In, &SubKey[0],ENCRYPT);
			Des2DES(Out,Out,&SubKey[1],DECRYPT);
			Des2DES(Out,Out,&SubKey[0],ENCRYPT);
			Out += 8; In += 8;
		}
	}

	return true;
}
/******************************************************************************/
//	名称：Decrypt
//	功能：解密
//  参数：len—数据长度，必须是8的倍数；KeyStr为0结尾的密钥串，长度<=16，可为任意字符
//        KeyStr默认值为0，如果你在调用前设置过子密钥，则可省略该参数。例:
//        SetSubKey(KeyStr);Decrypt(data,data,len);或:Decrypt(data,data,len,KeyStr);
//	返回：解密成功返回true，否则返回false
//  备注：当密钥长度>8时，系统自动使用3次DES解密
/******************************************************************************/
bool CDes::Des2Decrypt(char *Out,char *In,UINT len,const char *KeyStr)
{
    CHECK( Out && In && !(len&0x7) )

	if( KeyStr )
		CHECK( Des2SetSubKey(KeyStr) )
    if( !Is3DES )
	{   // 1次DES
		for(int i=0,j=len>>3; i<j; ++i)
		{
			Des2DES(Out,In,&SubKey[0],DECRYPT);
			Out += 8; In += 8;
		}
	}
	else
	{   // 3次DES D-E-D
		for(int i=0,j=len>>3; i<j; ++i)
		{
			Des2DES(Out,In, &SubKey[0],DECRYPT);
			Des2DES(Out,Out,&SubKey[1],ENCRYPT);
			Des2DES(Out,Out,&SubKey[0],DECRYPT);
			Out += 8; In += 8;
		}
	}

	return true;
}
/******************************************************************************/
//	名称：SetSubKey
//	功能：由输入密钥串设置子密钥
//  参数：KeyStr为0结尾的密钥串，长度<=16，可为任意字符
//	返回：设置成功返回true，否则返回false
//  备注：当密钥长度>8时，将设置第2密钥，且置3次DES标志
/******************************************************************************/
bool CDes::Des2SetSubKey(const char *KeyStr)
{
    int		len;

	CHECK_MSG( KeyStr && (len=strlen(KeyStr))<=16 && len>0, 
		       "设置DES密钥出错：空密钥，或密钥太长!" )
	memset(deskey,0,16);
	memcpy(deskey,KeyStr,len);
	// 设置第1密钥
	Des2SetSubKey(&SubKey[0],deskey);
	Is3DES = false;
	if( len>8 )
	{   // 置3次DES标志
		Is3DES = true;
		// 设置第2密钥
		Des2SetSubKey(&SubKey[1],&deskey[8]);
	}
	return true;
}
/******************************************************************************/
//	名称：RandKeyStr
//	功能：产生随机密钥串
//  参数：
//	返回：KeyStr地址
//  备注：
/******************************************************************************/
char* CDes::Des2RandKeyStr(char KeyStr[9])
{
    CHECK( KeyStr )

	srand(GetTickCount());
    for(int i=0; i<8; ++i)
	{
        KeyStr[i] = rand()%256;
	}
	while( !( KeyStr[7] && 0xf0 ) )
        KeyStr[7] = rand()%256;
	KeyStr[8] = '\0';
    // 这样可以进行连接操作
	return KeyStr;
}
/******************************************************************************/
//	名称：DES
//	功能：加/解密
//  参数：Type—ENCRYPT:加密,DECRYPT:解密
//	返回：
//  备注：私有函数，不用检查指针是否为空
/******************************************************************************/
void CDes::Des2DES(char Out[8],char In[8],const PSubKey pSubKey,bool Type)
{
    static bool M[64],Tmp[32],*Li,*Ri;

    // 将输入字节组分解成位组
   	CGfL::ByteToBit(M,In,8);
    // 初始变换
    CGfL::Transform(M,M,IP_Table,64);

	if( Type == ENCRYPT )
		Li=&M[0],Ri=&M[32];
	else
		Li=&M[32],Ri=&M[0];

    for(int i=0; i<16; ++i)
    {
        memcpy(Tmp,Ri,32);
		if( Type == ENCRYPT )
			F_func(Ri,(*pSubKey)[i]);
		else
			F_func(Ri,(*pSubKey)[15-i]);
        CGfL::Xor(Ri,Li,32);
        memcpy(Li,Tmp,32);
    }
    // 逆初始变换
    CGfL::Transform(M,M,IPR_Table,64);
	// 将位组合并成输出字节组
	CGfL::BitToByte(Out,M,64);
}
/******************************************************************************/
//	名称：SetSubKey
//	功能：由输入密钥设置16圈子密钥
//  参数：
//	返回：
//  备注：私有函数，不用检查指针是否为空
/******************************************************************************/
void CDes::Des2SetSubKey(PSubKey pSubKey,const char Key[8])
{
    static  bool K[64],*KL=&K[0],*KR=&K[28];

    // 将密钥字节组分解成密钥位组
	CGfL::ByteToBit(K,Key,8);
	// 密钥变换
    CGfL::Transform(K,K,PC1_Table,56);
    for(int i=0; i<16; ++i)
    {	// 循环左移
        CGfL::RotateL((char*)KL,28,LOOP_Table[i]);
        CGfL::RotateL((char*)KR,28,LOOP_Table[i]);
		// 压缩变换
        CGfL::Transform((*pSubKey)[i],K,PC2_Table,48);
    }
}
/******************************************************************************/
//	名称：F_func
//	功能：f 函数
//  参数：
//	返回：
//  备注：私有函数，不用检查指针是否为空
/******************************************************************************/
void CDes::Des2F_func(bool In[32],const bool Ki[48])
{
    static bool MR[48];

	// 扩展变换
    CGfL::Transform(MR,In,E_Table,48);
    CGfL::Xor(MR,Ki,48);
    S_func(In,MR);
	// P 变换
    CGfL::Transform(In,In,P_Table,32);
}
/******************************************************************************/
//	名称：S_func
//	功能：S 盒代替
//  参数：
//	返回：
//  备注：私有函数，不用检查指针是否为空
/******************************************************************************/
void CDes::Des2S_func(bool Out[32],const bool In[48])
{
    for(char i=0,j,k; i<8; ++i)
    {
        j = (In[0]<<1) + In[5];
        k = (In[1]<<3) + (In[2]<<2) + (In[3]<<1) + In[4];
		CGfL::ByteToBit(Out,&S_Box[i][j][k],1,4);
		Out +=4; In += 6;
    }
}

///////////////////////////////////////////////////////////////////////////////
// End of Files
///////////////////////////////////////////////////////////////////////////////
