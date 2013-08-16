#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h >
#define MAXSIZE 100000
#define BUF_SIZE 10240
#define PATH_SIZE 256


void encrypt(char *plain,char *key,char *cipher)
{
    int i=0;
    int j=0;
    int m,n;
    while( (plain[i] !='\0') && (plain[i]!='\n'))
    {
        if(plain[i]==' ')//���������еĿո�
        {
            cipher[j]=' ';
            i++;
            j=j+2;
            continue;
        }
        
        if(plain[i]=='j') //������ĸ"j"
        { 
            m=2;
            n=4;
        }

        if(plain[i]<'j' && plain[i]>='a')
        {
            m=(plain[i]-'a')/5;//������ĸλ��������е���
            n=(plain[i]-'a')-m*5;//����
        }

        if(plain[i]>'j' && plain[i]<='z')
        {
            m=(plain[i]-'a'-1)/5;//������ĸλ��������е���
            n=(plain[i]-'a'-1)-m*5;//����
        }
        cipher[j]=key[m];//���ܺ������
        cipher[j+1]=key[n];
        i++;
        j=j+2;
    }
}




void decrypt(char *plain ,char *cipher,char *key)
{
    int i=0;
    int j=0;
    int k=0;
    int pos,m,n;
    while( (cipher[i]!='\0') && (cipher[i]!='\n') )
    {
        if(cipher[i]==' ')//���������еĿո�
        {
            plain[k]=' ';
            i++;
            k++;
            continue;
        }

        for(j=0;j<5;j++)
        {
            if (cipher[i]==key[j])
                m=j;
            if (cipher[i+1]==key[j])
                n=j;
        }
        pos=m*5+n;
        plain[k]='a'+pos;
        if(plain[k]>'j')
            plain[k]++;
        i=i+2;
        k++;
    }
}

