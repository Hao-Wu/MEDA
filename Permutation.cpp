#include "stdafx.h"

void Permu_encry(char *ptext,char *ctext,char *key)
{
	char b[N1];
	char a[N1];
	char jz[N2/20][N1/20];                        
	int i,j,k,l,m=0,n=0;
	int T;  
		k = strlen(key);
		j = strlen(ptext);
		if(j%k!=0)
		{
			for(i=j;i<=j+k-j%k;i++)             //添q
				ptext[i]='q';
			T= j/k + 1;
		}
		else T = j/k ;
		for(i=0;i<T;i++)
		{
			for(l=0;l<k;l++)
			{
				jz[i][l] = ptext[m];
				++m;
			}
		}
		for(i=0;i<k;i++)
			b[i]=key[i];                     //保存key
		m=0;
		for(l=0;l<k;l++)
		{
			for(i=l+1;i<k-l;i++)
			{
				if(key[l] > key[i] )
					break; 
			}	
			for(i=0;i<T;i++)                
			{
				ctext[m]=jz[i][l];                //得密文
				++m;
			}
			for(i=0;i<l;i++)
				a[i]=key[i];
			for(i=l;i<k-l-1;i++)
				a[i]=key[i+1];
			for(i=0;i<k-l-1;i++)
				key[i]=a[i];
		}
		ctext[m] = '\0' ;
	
}

void Permu_decry(char *ctext,char *ptext,char *key)
{
	char b[N1];
	char a[N1];
	char jz[N2/20][N1/20];  
	int i,k,l,m=0,n=0;
	int T,j;
		k = strlen(key);
		j = strlen(ctext);
		m=0;
		if(j%k!=0)
		{
			for(i=j;i<=j+k-j%k;i++)             //添q
				ptext[i]='q';
			T= j/k + 1;                       
		}
		else T = j/k ;
		for(l=0;l<k;l++)
		{
			for(i=l+1;i<k-l;i++)
			{if(b[l] > b[i] )  break; }
			for(i=0;i<T;i++)                  //求列位置
			{
				jz[i][l] = ctext[m];                //恢复
				++m;
			}
			for(i=0;i<l;i++)                     
				a[i]=key[i];
			for(i=l;i<k-l-1;i++)
				a[i]=key[i+1];
			for(i=0;i<k-l-1;i++)
				key[i]=a[i];
		}
		for(i=0;i<T;i++)
			for(l=0;l<k;l++)
			{
				ptext[n]=jz[i][l];       //得出明文
				n++;
			}
}
