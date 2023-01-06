/*

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "F_Memory.h"

//	메모리 생성
unsigned char	*F_MAlloc(int p_Size)
{
	if(p_Size < 1)
		return NULL;

	unsigned char *t_Buffer = (unsigned char *)malloc(p_Size);
	if(t_Buffer == NULL)
	{
		return NULL;
	}
	memset(t_Buffer,0,p_Size);
	return t_Buffer;
}

//	메모리 삭제
bool	F_Free(void *p_Buffer)
{
	if(p_Buffer == NULL)
		return true;
	free(p_Buffer);
	return true;
}
