#include  "Bigint.h"

class CRsa
{
public:
	CRsa();
	int 	Encrypt(char *Out,char *In,UINT len,char *KeyStr,char *ModStr);//����
	int 	Decrypt(char *Out,char *In,UINT len,char *KeyStr,char *ModStr)//����
			{return Encrypt(Out,In,len,KeyStr,ModStr);}
	bool    GetKey(BigInt &p,BigInt &q,BigInt &e,BigInt &d,BigInt &n,
		           UINT plen,UINT qlen,UINT elen);//��ȡRSA��Կ��
	bool    SetKey(char *KeyStr,char *ModStr);//��������Կ������RSA��Կ��ģn

private:
    BigInt  key,n,Zero;//��Կ��ģn������0
	CBigInt BI;
};

void RSA_Encrypt(char *plaintext,char *chiphertext,int key ,bool flag);
void RSA_DeCrypt(char *plaintext,char *chiphertext,int key ,bool flag);