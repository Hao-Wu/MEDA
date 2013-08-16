#include "StdAfx.h"
#include "global.h"

void rc4_process( )
{
	int i=0,j=0;

	for (i=0; i<(256/strlen(origin_keystream)) ;i=i+j)
	{
		for (j=0;j<strlen(origin_keystream);j++)
		{
			keystream[i+j]=origin_keystream[j];
		}

	}
}