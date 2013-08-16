#include <stdafx.h>
void Vigenere_en(char *ptext , char*ctext , char*key)
{
	int k = 0 , p = 0 , i = 0 , j = 0;
	char table[26][26] ;
	k=strlen(key);
	p=strlen(ptext);
	for(i=0;i<26;i++)
	{
		for(j=0;j<26;j++)
		{
			table[i][j]=(i+j)%26+'a';
		}
    }
	for(i=0;i<=p;i++)
	{
		if(ptext[i]>='a'&&ptext[i]<='z'||(ptext[i]>='A'&&ptext[i]<='Z'))   //lu qi ta  fu hao  
		{
			ctext[i]=table[ptext[i]-'a'][key[i%k]-'a'];
		}
		else ctext[i]=ptext[i];
	}
	ctext[i] = '\0' ;
}

void Vigenere_de(char *ctext , char *ptext , char *key)
{
	int k , p , i , j;
	char table[26][26] ;
	k=strlen(key);
	p=strlen(ctext);
	for(i=0;i<26;i++)
	{
		for(j=0;j<26;j++)
		{
			table[i][j]=(i+j)%26+'a';
		}
    }
	for(i=0;i<=p;i++)                //jie mi
	{
		if(ctext[i]>='a'&&ctext[i]<='z'||(ctext[i]>='A'&&ctext[i]<='Z'))
		{
			for(j=0;j<=26;j++)
			{
				if(ctext[i]==table[j][key[i%k]-'a'])
					break;
			}
			ptext[i]='a'+j;
		}
		else ptext[i]=ctext[i];
	}
	ptext[i] = '\0' ;
}

