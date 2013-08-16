#include "StdAfx.h"

static bool SubKey[16][48] ;
static char Tmp[256], deskey[16];

void StartDes(char *Out, char *In, long datalen, const char *Key, int keylen, bool Typem, bool option,
              char *name_plainfile, char *name_cipherfile, char *name_plainfile2);
bool DesBegin(char *Out, char *In, long datalen, const char *Key, int keylen, bool Type);
void DES(char Out[8], char In[8], const PSubKey pSubKey, bool Type);//标准DES加/解密
void SetKey(const char* Key, int len);// 设置密钥
void GetSubKey(PSubKey pSubKey, const char Key[8]) ;
void SetSubKey(PSubKey pSubKey, const char Key[8]);// 设置子密钥
void F_func(bool In[32], const bool Ki[48]);// f 函数
void S_func(bool Out[32], const bool In[48]);// S 函数
void Transform(bool *Out, bool *In, const char *Table, int len);// 变换
void Xor(bool *InA, const bool *InB, int len);// 异或
void RotateL(bool *In, int len, int loop);// 循环左移
void ByteToBit(bool *Out, const char *In, int bits);// 字节组转换成位组
void BitToByte(char *Out, const bool *In, int bits);// 位组转换成字节组


// Construction/Destruction
const static char IP_Table[64] = {
	58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17,  9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
};


// final permutation IP^-1 
const static char IPR_Table[64] = {
	40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41,  9, 49, 17, 57, 25
};

// 扩充盒:E盒
static const char E_Table[48] = {
	32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
	 8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1
};

// 置换盒:P盒 
const static char P_Table[32] = {
	16, 7, 20, 21, 29, 12, 28, 17, 1,  15, 23, 26, 5,  18, 31, 10,
	2,  8, 24, 14, 32, 27, 3,  9,  19, 13, 30, 6,  22, 11, 4,  25
};

//pc1 ,64位密钥压缩变换为56位密钥
const static char PC1_Table[56] = {	
    4, 12, 20, 28, 5, 13, 21, 29, 37, 45, 53, 61, 6, 14,
	57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
	10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
};

//pc2,56位密钥压缩变换为48为密钥Ki
const static char PC2_Table[48] = {
	
	23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
	41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32,
	14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10
};

// pc1在各轮次左移的位数
static const char LOOP_Table[16] = 
{
	1 , 1 , 2 , 2 , 2 , 2 , 2 , 2 ,
	1 , 2 , 2 , 2 , 2 , 2 , 2 , 1
} ;


// 替换盒:S盒(共8个) 
const static char S_Box[8][4][16] = {
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



void ByteToBit(bool *Out, const char *In, int bits)//字节到位
{
    for(int i=0; i<bits; ++i)
        Out[i] = (In[i>>3]>>(i&7)) & 1; //i>>3相当于i/8
}
void BitToByte(char *Out, const bool *In, int bits)//位到字节
{
    memset(Out, 0, bits>>3);
    for(int i=0; i<bits; ++i)
        Out[i>>3] |= In[i]<<(i&7);
}

void Xor(bool *InA, const bool *InB, int len)//异或
{
    for(int i=0; i<len; ++i)
        InA[i] ^= InB[i];
}

void RotateL(bool *In, int len, int loop)//循环左移
{
    memcpy(Tmp, In, loop);
    memcpy(In, In+loop, len-loop);
    memcpy(In+len-loop, Tmp, loop);
}

void SetSubKey(PSubKey pSubKey, const char Key[8])//设置子密钥
{
    static bool K[64], *KL=&K[0], *KR=&K[28];
    ByteToBit(K, Key, 64);
    Transform(K, K, PC1_Table, 56);//经过PC1变换压缩为56位
    for(int i=0; i<16; ++i) 
	{
       RotateL(KL, 28, LOOP_Table[i]);
        RotateL(KR, 28, LOOP_Table[i]);
		memcpy(K,KL,28);
		memcpy(K+28,KR,28);
		Transform((*pSubKey)[i], K, PC2_Table, 48);       
    }//经过16轮左移 交换 压缩 得到16个48位子密钥 
}

void S_func(bool Out[32], const bool In[48])//S函数,48位->32位
{
    for(char i=0,j,k; i<8; ++i,In+=6,Out+=4) 
    {
        j = (In[0]<<1) + In[5];
        k = (In[1]<<3) + (In[2]<<2) + (In[3]<<1) + In[4];
		ByteToBit(Out, &S_Box[i][j][k], 4);
    }
}



void F_func(bool In[32], const bool Ki[48])//F函数
{
    static bool MR[48];
    Transform(MR, In, E_Table, 48);
    Xor(MR, Ki, 48);

    S_func(In, MR);
    Transform(In, In, P_Table, 32);
}

void Transform(bool *Out, bool *In, const char *Table, int len)
{
    for(int i=0; i<len; ++i)
        Tmp[i] = In[ Table[i]-1 ];
    memcpy(Out, Tmp, len);
}


void GetSubKey(PSubKey pSubKey, const char Key[8])
{
	
	static bool K[64], *KL=&K[0], *KR=&K[28];
    ByteToBit(K, Key, 64);
    Transform(K, K, PC1_Table, 56);
    for(int i=0; i<16; ++i) 
	{
		RotateL(KL, 28, LOOP_Table[i]);
        RotateL(KR, 28, LOOP_Table[i]);
		memcpy(K,KL,28);
		memcpy(K+28,KR,28);
		Transform((*pSubKey)[i], K, PC2_Table, 48);
    }
} 


void StartDes(char *Out, char *In, long datalen, const char *Key, int keylen, bool Type, bool option,
              char *name_plainfile, char *name_cipherfile, char *name_plainfile2)
{
    
    if(option==0)//对字符串操作
    {
        DesBegin(Out, In, strlen(In), Key, strlen(Key), Type);
    }
    else
    {
        
        
        char buf[1024]={'\0'};
        char out[1024]={'\0'};
        int nr;
        if (Type==0)
        {
			FILE *plainfile=fopen(name_plainfile,"rb");
		    FILE *cipherfile=fopen(name_cipherfile,"wb");
            nr = read(fileno(plainfile) , buf , sizeof(buf)) ;
	        while(nr>0)
	        {
		        DesBegin( out , buf , strlen(buf) , Key , strlen(Key) ,0) ;
		        write(fileno(cipherfile) , out , nr) ;
		        nr = read(fileno(plainfile) , buf , sizeof(buf)) ;
	        }
	        fclose(plainfile) ;
	        fclose(cipherfile) ;
        }
        else
        {
			FILE *cipherfile=fopen(name_cipherfile,"rb");
			FILE *plainfile2=fopen(name_plainfile2,"wb");
            nr = read(fileno(cipherfile), buf, sizeof(buf)) ;
            while(nr>0)
            {
                DesBegin( out , buf , nr , Key , strlen(Key) ,1) ;
		        write(fileno(plainfile2) , out , nr) ;
		        nr = read(fileno(cipherfile) , buf , sizeof(buf)) ;
            }
            fclose(plainfile2) ;
	        fclose(cipherfile) ;
        }
    }
}

//开始DES
bool DesBegin(char *Out, char *In, long datalen, const char *Key, int keylen, bool Type)
              
{
    if( !( Out && In && Key && (datalen=(datalen+7)&0xfffffff8))) 
		return false;
    if(datalen%8)
		datalen+=8-datalen%8;
	char deskey[8] ;
	memset(deskey, 0, 8);
	memcpy(deskey, Key, keylen>8?8:keylen);
	GetSubKey(&SubKey , deskey) ;
	{   // 1次DES
		for(long i=0,j=datalen>>3; i<j; ++i,Out+=8,In+=8)
			DES(Out, In, &SubKey, Type);
	} 
	return true;
}



void DES(char Out[8], char In[8], const PSubKey pSubKey, bool Type)
{
    static bool M[64], tmp[32], *Li=&M[0], *Ri=&M[32];
    ByteToBit(M, In, 64);
    Transform(M, M, IP_Table, 64);
    if( Type == 0 ) //加密
	{
        for(int i=0; i<16; ++i)
		{
            memcpy(tmp, Ri, 32);
            F_func(Ri, (*pSubKey)[i]);
            Xor(Ri, Li, 32);
            memcpy(Li, tmp, 32);
        }
    }
	else //解密
	{
        for(int i=15; i>=0; --i) 
		{
            memcpy(tmp, Li, 32);
            F_func(Li, (*pSubKey)[i]);
            Xor(Li, Ri, 32);
            memcpy(Ri, tmp, 32);
        }
	}
   Transform(M, M, IPR_Table, 64);
   BitToByte(Out, M, 64);
}