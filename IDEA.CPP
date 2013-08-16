#include "IDEA.h"
#include "StdAfx.h"

int end_of_file,noisy,overwrite;   /*global vars*/

static uint16 inv(uint16 x)
{
   uint16 t0,t1;
   uint16 q,y;
   if (x<=1)
      return x;
   t1=(uint16)(0x10001l/x);
   y=(uint16)(0x10001l%x);
   if (y==1)
  return low16(1-t1);
   t0=1;
   do
   {
      q=x/y;
      x=x%y;
      t0+=q*t1;
      if (x==1)
  return t0;
      q=y/x;
      y=y%x;
      t1+=q*t0;
   } while (y!=1);
   return low16(1-t1);
}

static void en_key_idea(word16 *userkey, word16 *Z)
{
   int i,j;
   /* shifts */
   for (j=0;j<8;j++)
      Z[j]=*userkey++;
   for (i=0;j<KEYLEN;j++)
   {
      i++;
      Z[i+7]=((Z[i&7] << 9) | (Z[i+1 & 7] >> 7));
      Z+=i&8;
      i&=7;
   }
}

static void de_key_idea(IDEAkey Z,IDEAkey DK)
{
   int j;
   uint16 t1,t2,t3;
   IDEAkey T;
   word16 *p=T+KEYLEN;
   t1=inv(*Z++);
   t2=-*Z++;
   t3=-*Z++;
   *--p=inv(*Z++);
   *--p=t3;
   *--p=t2;
   *--p=t1;
   for (j=1;j<ROUNDS;j++)
   {
      t1=*Z++;
      *--p=*Z++;
      *--p=t1;
      t1=inv(*Z++);
      t2=-*Z++;
      t3=-*Z++;
      *--p=inv(*Z++);
      *--p=t2;
      *--p=t3;
      *--p=t1;
   }
   t1=*Z++;
   *--p=*Z++;
   *--p=t1;
   t1=inv(*Z++);
   t2=-*Z++;
   t3=-*Z++;
   *--p=inv(*Z++);
   *--p=t3;
   *--p=t2;
   *--p=t1;
   /*copy and destroy temp copy*/
   for(j=0,p=T;j<KEYLEN;j++)
   {
      *DK++=*p;
      *p++=0;
   }
}


uint16 mul(uint16 a, uint16 b)
{
   word32 p;

   if (a)
   {
      if (b)
      {
   p=(word32)a*b;
   b=(uint16)(low16(p));
   a=(uint16)(p>>16);
   return b-a+(b<a);
      }
      else
      {
   return 1-a;
      }
   }
   else
      return 1-b;
}

#define MUL(x,y) (x=mul(low16(x),y))


#define CONST

static void cipher_idea(word16 in[4],word16 out[4],register CONST IDEAkey Z)
{//加密函数
   register uint16 x1,x2,x3,x4,t1,t2;
   int r=ROUNDS;
   x1=*in++; x2=*in++;
   x3=*in++; x4=*in;
   do
   {
      MUL(x1,*Z++);
      x2+=*Z++;
      x3+=*Z++;
      MUL(x4,*Z++);
      t2=x1^x3;
      MUL(t2,*Z++);
      t1=t2+(x2^x4);
      MUL(t1,*Z++);
      t2=t1+t2;
      x1^=t1;
      x4^=t2;
      t2^=x2;
      x2=x3^t1;
      x3=t2;
   } while (--r);
   MUL(x1,*Z++);
   *out++=x1;
   *out++=(x3+*Z++);
   *out++=(x2+*Z++);
   MUL(x4,*Z);
   *out=x4;
}

char read_char_from_file(FILE *fp)
{
   char temp=0;

   if ((fread(&temp,sizeof(char),1,fp))!=1)
      end_of_file=1;

   return (temp);
}

word16 read_word16_from_file(FILE *fp)
{
   word16 temp=0;

   if ((fread(&temp,sizeof(word16),1,fp))!=1)
      end_of_file=1;

   return temp;
}

void write_char_to_file(char data,FILE *fp)
{
   if ((fwrite(&data,sizeof(char),1,fp))!=1)
   {
      printf("Fatal Error writing output file!!!\n");
      exit(-1);
   }
}

void write_word16_to_file(word16 data,FILE *fp)
{
   if ((fwrite(&data,sizeof(word16),1,fp))!=1)
   {
      printf("Fatal Error writing output file!!!\n");
      exit(-1);
   }
}


void cipher_file(FILE *in,FILE *out,word16 *key)
{
   word16 input[4],output[4];
   IDEAkey Z;
   int x,y;
   int count=0;
   long length;
   int temp;

   en_key_idea(key,Z);
   end_of_file=0;

   length=filelength(fileno(in));
   fwrite(&length,sizeof(long),1,out);

   while (!end_of_file)
   {
      x=0;

      while (x<4)
      {
   input[x]=((word16)(read_char_from_file(in)<<8));
   if (!end_of_file)
   {
      temp=read_char_from_file(in);
      if (temp<0) temp+=256;
      input[x]=input[x]|temp;
      x++;
   }
   if (end_of_file)
   {
      while (x<4) input[x++]=0;
      break;
   }
      }

      cipher_idea(input,output,Z);

      for (y=0;y<x;y++)
      {
	   if (noisy) if (count++%256==0) printf(".");
	   write_word16_to_file(output[y],out);
      }
   }
}

void cipher_string(char *in,char *out,char *inputkey)
{//加密字符串，在加密文件的基础上改写
	word16 key[8];
	getuserkey(key,inputkey);
	FILE *tmp_plain=fopen("tmp_plainfile.txt","w+");
	FILE *tmp_cipher=fopen("tmp_cipherfile.txt","w+");
	fprintf(tmp_plain,"%s\n",in);
	cipher_file(tmp_plain,tmp_cipher,key);
	memset(out,0,MAXSIZE);
	fscanf(tmp_cipher,"%s",out);
	fclose(tmp_plain);
	fclose(tmp_cipher);
}

void decipher_file(FILE *in,FILE *out,	word16 *key)
{

	word16 input[4],output[4];
	int x,y;
	IDEAkey Z,DK;
	int count=0;
	long length=0;
	
	en_key_idea(key,Z);
	de_key_idea(Z,DK);
	
	end_of_file=0;
	
	fread(&length,sizeof(long),1,in);
	
	
	while (!end_of_file)
	{
		x=0;
		while (x<4)
		{
			input[x]=read_word16_from_file(in);
			if (end_of_file)
				break;
			x++;
		}
		cipher_idea(input,output,DK);
		for (y=0;y<x;y++)
		{
			if (noisy) if (count++%256==0) printf(".");
			if (length-->0)
				write_char_to_file(((char)(output[y]>>8)),out);
			if (length-->0)
				write_char_to_file(((char)(output[y]&255)),out);
		}
	}
}


void decipher_string(char *in,char *out,char *inputkey)
{//解密密字符串，在解密文件的基础上改写
	word16 key[8];
	getuserkey(key,inputkey);
	FILE *tmp_cipher=fopen("tmp_cipherfile.txt","w+");
	FILE *tmp_plain=fopen("tmp_plainfile.txt","w+");
	fprintf(tmp_cipher,"%s\n",in);
	decipher_file(tmp_cipher,tmp_plain,key);
	memset(out,0,MAXSIZE);
	fscanf(tmp_plain,"%s",out);
	fclose(tmp_plain);
	fclose(tmp_cipher);
}


void swap_files_and_clean_up(char *file)
{
   long fsize,count;
   FILE *fp;
   char temp[100];

   if (overwrite)
   {
      if ((fp=fopen(file,"r+b"))==NULL)
      {
   printf("\nError overwriting old file, security compromised.\n");
      }
      else
      {
   fseek(fp,0l,SEEK_END);
   fsize=ftell(fp);
   fseek(fp,0l,SEEK_SET);
   for (count=0;count<fsize;count++)
      fputc('0',fp);
   fclose(fp);
      }

      if ((remove(file))!=0)
      {
   printf("\nERROR removing old file <%s>\n",file);
   printf("encoded data remains in temporary file <%s>\n",tempfilename);
   exit(-1);
      }
   }
   else
   {
      strcpy(temp,file);
      file=strtok(temp,".");
      strcat(file,".enc");
   }

   if ((rename(tempfilename,file))!=0)
   {
      printf("\nERROR renaming temporary file <%s>!!\n",tempfilename);
      printf("Data is safely processed and stored in that file.\n");
      exit(-1);
   }
}




#define KBYTES 1024

void getuserkey(word16 *key,char *arg)
{
   int x;

   for (x=0;x<strlen(arg) && x<8;x++)
   {
       if (x==0) key[x]=arg[x]<<8;
       else key[x]=((arg[x]<<8)|(key[x-1]>>8));
   }

   if (strlen(arg)>8) printf ("\nONLY first *8* characters of key used!!!\n");

   if (x<8) while (x<8) key[x++]=0;
}

int main()
{
   char key[MAXSIZE];
   char in[MAXSIZE];
   char out[MAXSIZE];
   char type;
   FILE *fp,*temp;
   int to_or_from;
	
   printf("input string!");
   scanf("%s",in);
   printf("input type:\n");
   getchar();
   scanf("%c",&type);
   printf("input key!");
   scanf("%s",key);
	if (type=='e')
	cipher_string(in,out, key);
	else if(type=='d')
		decipher_string(in,out,key);
	printf("%s\n",out);
    return 0;
} 
