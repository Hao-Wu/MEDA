#include "StdAfx.h"
#include "iostream.h"


////////////////////////////////////////
//�����㷨
void Playfair_encrypt(char *plaintxt,char *ciphertxt,char *key)
{
	char plain[MAXSIZE]={'\0'};
	strcpy(plain,plaintxt);
 //const int N=100;
 int i,j,k,t;
 char letters[26]="ABCDEFGHIKLMNOPQRSTUVWXYZ";//����������
 int flag[25]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//�����ĸ�Ƿ����ھ����У���letters�����Ӧ
 char ch[5][5];//5X5����

 int len='a'-'A';

 for( i=0; i<strlen(key) ; i++)//�����������Կת��Ϊ��д��ĸ
 {
  if(key[i]>='a')
   key[i]=key[i]-len;
 }

 for(i=0;i<strlen(key);i++)//����Կ�е�J����ΪI����Ϊ���㷨��I��J�ǵȼ۵�
 {
  if(key[i]=='J')
	  key[i]='I';
 }
 for(k=0;k<strlen(key);k++)//����Կ�е���ĸ���뵽�����У����Ѹ���ĸ���Ϊ����
 {
	  for(t=0;t<25;t++)
	  {
			i=0;
			j=0;
		   if(key[k]==letters[t] && flag[t]==0)
		   {
			ch[i][j]=letters[t];
			flag[t]=1;
			if(j<4)j++;
			else {i++;j=0;}
		   }
	  }
 }
 for( k=0;k<25;k++)//����ĸ��˳���δ����ĸ�������뵽������
 {
	  if(flag[k]==0)
	  {
	   ch[i][j]=letters[k];
	   flag[k]=1;
	   if(j<4)	
		   j++;
		   else	
		   {	i++;
				j=0;
		   }
	  }
 }

 for(k=0;k<strlen(plain);k++)//�������������ת��Ϊ��д��ĸ
 {
	  if(plain[k]>='a')
		plain[k]=plain[k]-len;
	  if(plain[k]=='J')
		  plain[k]='I';
 }

 for( k=0;k<strlen(plain);k+=2)//Ϊ������ӱ�Ҫ���޹��ַ��Է�ֹͬһ��������ַ���ͬ
 {
	  if(plain[k]==plain[k+1])
	  {
		   for( t=strlen(plain); t>k ; t--)
			plain[t+1]=plain[t];
		   plain[k+1]='X';
	  }
 }

 if(strlen(plain)%2!=0)//���������������ַ��������һ���޹��ַ��Դչ�ż����
 {
	 plain[strlen(plain)+1]=plain[strlen(plain)];
	 plain[strlen(plain)]='X';
 }
 
 for( k=0;k<strlen(plain);k+=2)
 {
  int m1,m2,n1,n2;
  for(m1=0;m1<=4;m1++)
  {
	   for(n1=0;n1<=4;n1++)
	   {
		if(plain[k]==ch[m1][n1])
			break;
	   }
	   if(plain[k]==ch[m1][n1])
		   break;
  }
  for(m2=0;m2<=4;m2++)
  {
	   for(n2=0;n2<=4;n2++)
	   {
		if(plain[k+1]==ch[m2][n2])
			break;
	   }
		if(plain[k+1]==ch[m2][n2])
			break;
  }
  m1=m1%5;
  m2=m2%5;
  if(n1>4){n1=n1%5;m1=m1+1;}
  if(n2>4){n2=n2%5;m2=m2+1;}
  if(m1==m2)
  {
   plain[k]=ch[m1][(n1+1)%5];
   plain[k+1]=ch[m2][(n2+1)%5];
  }
  else 
  {
   if(n1==n2)
   {
    plain[k]=ch[(m1+1)%5][n1];
    plain[k+1]=ch[(m2+1)%5][n2];
   }
   else
   {
    plain[k]=ch[m1][n2];
    plain[k+1]=ch[m2][n1];
   }
  }
 }
 strcpy(ciphertxt,plain);
}
 







///////////////////////////////////////////////////////////////////////////////

//�����㷨
void Playfair_decrypt(char *ciphertxt, char *plaintxt, char*key)
{
	char cipher[MAXSIZE]={'\0'};
 //const int N=100;
 int i,j,k,t;
 char letters[26]="ABCDEFGHIKLMNOPQRSTUVWXYZ";//����������
 int flag[25]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//�����ĸ�Ƿ����ھ����У���letters�����Ӧ
 char ch[5][5];//5X5����
 //char key[N];//��Կ
 //char ch2[N];//����
 int len='a'-'A';
 //cout<<"������Կ��";
 //cin>>key;
 for(i=0;i<strlen(key);i++)//�����������Կת��Ϊ��д��ĸ
 {
  if(key[i]>='a')
   key[i]=key[i]-len;
  if(key[i]=='J')
	  key[i]='I';
 }

 for(k=0;k<strlen(key);k++)//����Կ�е���ĸ���뵽�����У����Ѹ���ĸ���Ϊ����
 {
	  for(t=0;t<25;t++)
	  {
		   if(key[k]==letters[t]&&flag[t]==0)
		   {
			i=0;  j=0;
			ch[i][j]=letters[t];
			flag[t]=1;
			if(j<4)j++;
			else {i++;j=0;}
		   }
	  }
 }
 for(k=0;k<25;k++)//����ĸ��˳���δ����ĸ�������뵽������
 {
	 i=0;
	 j=0;
	  if(flag[k]==0)
	  {
	   ch[i][j]=letters[k];
	   flag[k]=1;
	   if(j<4)j++;
	   else{i++;j=0;}
	  }
 }
 ////////////////�����������///////////////////////////////
 int f=0;
 do{
	 //cout<<"���������ģ�";
	 //cin>>ch2;
	 for( k=0;k<strlen(cipher);k++)//�������������ת��Ϊ��д��ĸ
	 {
		if(cipher[k]>='a')
			cipher[k]=cipher[k]-len;
		if(cipher[k]=='J')cipher[k]='I';
	 }
	 /*
	 for(int k=0;k<strlen(ch2);k+=2)
	 {
	  if(ch2[k]==ch2[k+1])
	  {
	   cout<<"���ַ���������ʹ��Playfair�㷨���ܺ���Եõ�����ʽ��"<<endl;
	   f=1;
	   break;
	  }else f=2;
	 }*/
	 if(f==1) continue;
	 if(strlen(cipher)%2!=0)
	 {
		 cout<<"���ַ���������ʹ��Playfair�㷨���ܺ���Ե�	������ʽ��"<<endl;
		 f=1;
	 }
	 else f=2;
 }while(f==1);

 /////////////���ܿ�ʼ////////
	 for( k=0; k<strlen(cipher);k+=2)
	 {
		  int m1,m2,n1,n2;
		  for(m1=0;m1<=4;m1++)
		  {
			   for(n1=0;n1<=4;n1++)
			   {
				if(cipher[k]==ch[m1][n1])break;
			   }
			   if(cipher[k]==ch[m1][n1])break;
		  }
		  for(m2=0;m2<=4;m2++)
		  {
			   for(n2=0;n2<=4;n2++)
			   {
				if(cipher[k+1]==ch[m2][n2])break;
			   }
			   if(cipher[k+1]==ch[m2][n2])break;
		  }
		  m1=m1%5;
		  m2=m2%5;
		  if(n1>4)	{	n1=n1%5; m1=m1+1; }
		  if(n2>4)	{	n2=n2%5; m2=m2+1; }

		  if(m1==m2)
		  {
			   cipher[k]=ch[m1][(n1+4)%5];
			   cipher[k+1]=ch[m2][(n2+4)%5];
		  }
		  else 
		  {
			   if(n1==n2)
			   {
				cipher[k]=ch[(m1+4)%5][n1];
				cipher[k+1]=ch[(m2+4)%5][n2];
			   }
			   else
			   {
				cipher[k]=ch[m1][n2];
				cipher[k+1]=ch[m2][n1];
		   }
		  }

	 }
	strcpy(plaintxt,cipher);
 }
