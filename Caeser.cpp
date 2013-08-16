#include <StdAfx.h>

void Caeser(char *plaintext,char *chiphertext,int key)
{

	
		int len = strlen(plaintext);
		for(int i=0;i<len;i++)
		{
			if( (plaintext[i]>='a') && (plaintext[i]<='z') )
			{
				chiphertext[i]='a'+(plaintext[i]-'a'+key)%26;
			}
			else
			{	chiphertext[i]=plaintext[i];	}	
		}
	
}


void Caeser_d(char *plaintext,char *chiphertext,int key)
{

		int len = strlen(chiphertext);
		for(int i=0;i<len;i++)
		{
			if( chiphertext[i]>=97 && chiphertext[i]<=122)
			{
				if( (chiphertext[i]-key) >= 'a')
					plaintext[i]= chiphertext[i]-key;
				else
					plaintext[i]= chiphertext[i]+26-key;
			}
			else
			{	chiphertext[i]=plaintext[i];	}
		}
	
}