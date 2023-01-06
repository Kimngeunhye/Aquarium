#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	메모리 관리
*/
#define		F_Alloc(a)	F_MAlloc(a)

unsigned char	*F_MAlloc(int p_Size);

bool	F_Free(void *p_Buffer);
