
typedef bool    (*PSubKey)[16][48];
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
