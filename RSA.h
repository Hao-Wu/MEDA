#include  "Bigint.h"

class CRsa
{
public:
	CRsa();
	int 	Encrypt(char *Out,char *In,UINT len,char *KeyStr,char *ModStr);//加密
	int 	Decrypt(char *Out,char *In,UINT len,char *KeyStr,char *ModStr)//解密
			{return Encrypt(Out,In,len,KeyStr,ModStr);}
	bool    GetKey(BigInt &p,BigInt &q,BigInt &e,BigInt &d,BigInt &n,
		           UINT plen,UINT qlen,UINT elen);//获取RSA密钥对
	bool    SetKey(char *KeyStr,char *ModStr);//由输入密钥串设置RSA密钥和模n

private:
    BigInt  key,n,Zero;//密钥，模n，常量0
	CBigInt BI;
};

void RSA_Encrypt(char *plaintext,char *chiphertext,int key ,bool flag);
void RSA_DeCrypt(char *plaintext,char *chiphertext,int key ,bool flag);