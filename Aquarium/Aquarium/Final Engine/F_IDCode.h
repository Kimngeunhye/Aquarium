/*
 *  F_IDCode.h
 *  64 비트 코드 정의
 *
 *  Created by forthen on 11. 4. 18..
 *  Copyright 2011 forthen. All rights reserved.
 *
 */

#pragma once
#include <stdio.h>
#include <stdlib.h>


//	MS 컴파일이 아닌 경우 별도 정의 필요
typedef	unsigned int	DWORD;
typedef long long		__int64;
typedef void			VOID;
typedef	void*			LPVOID;
typedef int				BOOL;
typedef unsigned char	BYTE;


//	코드 구조체
struct	FGS_Code
{
	//	상위 코드
	DWORD	m_Hi;
	//	하위 코드
	DWORD	m_Lo;
};

//	64비드 코드 공동체
union	FGU_ID 
{
	DWORD		m_DWORD;
	FGS_Code	m_Code;
	__int64		m_INT64;
};

//	코드 데이터 변경
__int64	Int64_FGS_Code(FGS_Code p_Code);
__int64	Int64_FGS_Code(DWORD p_Hi,DWORD p_Lo);
FGS_Code FGS_Code_Int64(__int64 p_Int64);
FGS_Code FGS_Code_Int64(DWORD p_Hi,DWORD p_Lo);