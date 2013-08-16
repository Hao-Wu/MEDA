//仿射加密
#include "StdAfx.h"

int gongyueshu(int &m,int &n)//求公约数
{ 
int temp;
int r;
int p;
if(n<m)
{
temp=n;
n=m;
m=temp;
}

p=m*n;
while(m!=0)
{
r=n%m;
n=m;
m=r;
}
return(n);

}


void encipher(char*p,char*c,int a,int b)//加密
{ 

int i;
int maxnum=0;
int s=26;
int t=a;
maxnum=gongyueshu(t,s);
if(maxnum!=1)
printf("输入的密钥a不符合条件！请重新输");
else
{
for(i=0;*(p+i)!='\0';i++)
{ 
int temp;
temp=p[i]-97;
//printf("%d\n",b);
*(c+i)=char(((a*temp+b)%26)+97);
} 
c[i]='\0';
}

}


void decipher(char *p,char *c,int a, int b)
{ 

	int a0;
	int k=0; 
	while((26*k+1)%a!=0)
	{ 
		k++;
	}
	a0=(26*k+1)/a;
	int i;
	for(i=0;*(c+i)!='\0';i++)
	{ 
		int temp; 
		temp=*(c+i)-97;
		if((temp-b)<0)
		*(p+i)=((a0*(temp-b))%26+26)+97;
		else
		*(p+i)=((a0*(temp-b))%26)+97;
	}

	p[i]='\0';

}


