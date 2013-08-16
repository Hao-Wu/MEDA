#include "StdAfx.h"

typedef struct rc4_key
{      
	unsigned char state[256];       
	unsigned char x;        
	unsigned char y;
}rc4_key;


class rc4
{
public:
	rc4(unsigned char *key_data_ptr,int nLen);//类初始化时接受字串，初始化key
	void rc4_encode(unsigned char *buffer_ptr, int buffer_len);//明文与暗文使用同一个函数转换
private:
	rc4_key key;//加密与解密用到的key，初始化时就需要赋值
	void prepare_key(unsigned char *key_data_ptr, int key_data_len);//初始化key
	void swap_byte(unsigned char *a, unsigned char *b);//交换
};

rc4::rc4(unsigned char *key_data_ptr,int nLen)
{
	prepare_key(key_data_ptr,nLen);
}

void rc4::prepare_key(unsigned char *key_data_ptr, int key_data_len)
{
	unsigned char index1;
	unsigned char index2;
	unsigned char* state;
	short counter;
	
	state = &key.state[0];
	
	for(counter = 0; counter < 256; counter++)
		state[counter] = (unsigned char)counter;
	
	key.x = 0;
	key.y = 0;
	index1 = 0;
	index2 = 0;
	
	for(counter = 0; counter < 256; counter++)
	{
		index2 = (key_data_ptr[index1] + state[counter] + index2) % 256;
		swap_byte(&state[counter], &state[index2]);
		index1 = (index1 + 1) % key_data_len;
	}
}

void rc4::swap_byte(unsigned char *a, unsigned char *b)
{
	unsigned char x;
	x=*a;*a=*b;*b=x;
}

void rc4::rc4_encode(unsigned char *buffer_ptr, int buffer_len)
{
	unsigned char x;
	unsigned char y;
	unsigned char* state;
	unsigned char xorIndex;
	short counter;
	
	x = key.x;
	y = key.y;
	state = &key.state[0];
	
	for(counter = 0; counter < buffer_len; counter++)
	{
		x = (x + 1) % 256;
		y = (state[x] + y) % 256;
		swap_byte(&state[x], &state[y]);
		xorIndex = (state[x] + state[y]) % 256;
		buffer_ptr[counter] ^= state[xorIndex];
	}
	buffer_ptr[counter] = '\0' ;
	key.x = x;
	key.y = y;
}

void RC4_enstring(char* m_strOpenFile,char* m_strSaveFile,char* m_strKey)
{
	rc4 rc4_cona((unsigned char *)m_strKey,strlen(m_strKey));
	char buf[BUF_SIZE];

	for(int i=0;i<(int)strlen(m_strOpenFile);i++)
	{
		buf[i]=m_strOpenFile[i];
	}
	buf[i] = '\0' ;
	rc4_cona.rc4_encode((unsigned char*)buf,BUF_SIZE);
	for(int j=0;j<(int)strlen(buf);j++)
	{
		m_strSaveFile[j]=buf[j];
	}
	m_strSaveFile[j] = '\0' ;
	
}

void RC4_process(char *key, char *keystream)
{
	int i=0;
	int j=0;
	int length=strlen(key);
	for (i=0; i<(256/length) ; i++)
	{
		for (j=0;j<length;j++)
		{
				keystream[i*length+j]=key[j];
		}
	}

}