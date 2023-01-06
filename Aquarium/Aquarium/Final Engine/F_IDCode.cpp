/*
 *  F_IDCode.cpp
 *  64 비트 코드 
 *
 *  Created by forthen on 11. 4. 18..
 *  Copyright 2011 forthen. All rights reserved.
 *
 */

#include "F_IDCode.h"


__int64	Int64_FGS_Code(FGS_Code p_Code)
{
	__int64 t_Return = (__int64)p_Code.m_Lo;
	t_Return = t_Return<<32;
	t_Return = t_Return + p_Code.m_Hi;
	return t_Return;
}

__int64	Int64_FGS_Code(DWORD p_Hi,DWORD p_Lo)
{
	__int64 t_Return = (__int64)p_Lo;
	t_Return = t_Return<<32;
	t_Return = t_Return + p_Hi;
	return t_Return;
}

FGS_Code FGS_Code_Int64(__int64 p_Int64)
{
	FGS_Code t_Return;
	__int64	t_64 = p_Int64>>32;
	t_Return.m_Lo = (DWORD)t_64;
	t_64 = p_Int64&0x00000000ffffffff;
	t_Return.m_Hi = (DWORD)t_64;
	return t_Return;
}

FGS_Code FGS_Code_Int64(DWORD p_Hi,DWORD p_Lo)
{
	FGS_Code t_Return;
	t_Return.m_Lo = p_Lo;
	t_Return.m_Hi = p_Hi;
	return t_Return;
}
