
typedef bool    (*PSubKey)[16][48];
void StartDes(char *Out, char *In, long datalen, const char *Key, int keylen, bool Typem, bool option,
              char *name_plainfile, char *name_cipherfile, char *name_plainfile2);
bool DesBegin(char *Out, char *In, long datalen, const char *Key, int keylen, bool Type);
void DES(char Out[8], char In[8], const PSubKey pSubKey, bool Type);//��׼DES��/����
void SetKey(const char* Key, int len);// ������Կ
void GetSubKey(PSubKey pSubKey, const char Key[8]) ;
void SetSubKey(PSubKey pSubKey, const char Key[8]);// ��������Կ
void F_func(bool In[32], const bool Ki[48]);// f ����
void S_func(bool Out[32], const bool In[48]);// S ����
void Transform(bool *Out, bool *In, const char *Table, int len);// �任
void Xor(bool *InA, const bool *InB, int len);// ���
void RotateL(bool *In, int len, int loop);// ѭ������
void ByteToBit(bool *Out, const char *In, int bits);// �ֽ���ת����λ��
void BitToByte(char *Out, const bool *In, int bits);// λ��ת�����ֽ���