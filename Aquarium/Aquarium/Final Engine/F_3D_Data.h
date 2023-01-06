#pragma once
#include "F_3D_MATH.h"
/*
	3D 데이터 구조 
*/

////	데이터 유형 정의
enum F_TYPE
{
	DATA_DWORD		= 0,
	DATA_XY			= 1,
	DATA_XYZ		= 2,
	DATA_XYZW		= 3,
	DATA_MATRIX		= 4,
	DATA_XYZB3		= 5
};
//	크기 얻기
DWORD	Get_Type_Size(F_TYPE p_Type);


//	3D 데이터 구조체
struct	FS_3D_Data
{
	//	유형
	DWORD	m_Type;
	//	FVF 값
	DWORD	m_FVF;
	//	크기
	DWORD	m_Size;
	//	데이터 포인터
	BYTE	*m_Data;
};

////	3D 데이터 클래스
class F_3D_Data
{
public:
	F_3D_Data(void);
	~F_3D_Data(void);

protected:
	FS_3D_Data	m_3DData;

public:
    enum F_FVF
    {
		FD_FVF_RESERVED0        = 0x001,
		FD_FVF_XYZ              = 0x002,
		FD_FVF_XYZRHW           = 0x004,
		FD_FVF_XYZB1            = 0x006,
		FD_FVF_XYZB2            = 0x008,
		FD_FVF_XYZB3            = 0x00a,
		FD_FVF_XYZB4            = 0x00c,
		FD_FVF_XYZB5            = 0x00e,
		FD_FVF_NORMAL           = 0x010,
		FD_FVF_PSIZE            = 0x020,
		FD_FVF_DIFFUSE          = 0x040,
		FD_FVF_SPECULAR         = 0x080,
		FD_FVF_TEX0             = 0x000,
		FD_FVF_TEX1             = 0x100,
		FD_FVF_TEX2             = 0x200,
		FD_FVF_TEX3             = 0x300,
		FD_FVF_TEX4             = 0x400,
		FD_FVF_TEX5             = 0x500,
		FD_FVF_TEX6             = 0x600,
		FD_FVF_TEX7             = 0x700,
		FD_FVF_TEX8             = 0x800,
		FD_FVF_TEXCOUNT_MASK    = 0xf00,
		FD_FVF_LASTBETA_UBYTE4	= 0x1000,
		FD_FVF_XYZW				= 0x4002,
		FD_FVF_POSITION_MASK	= 0x400E,
		FD_FVF_LASTBETA_D3DCOLOR = 0x8000
    };

protected:
	bool	Create(F_FVF p_FvF,DWORD p_Number);
	bool	Create(DWORD p_Type,DWORD p_FVF,DWORD p_Size);
	bool	Delete();

public:
	BYTE	*Get_Data();
	DWORD	Get_FVF();
	DWORD	Sum_FVF(DWORD p_FVF);
	DWORD	Get_Type();
	DWORD	Get_Size();
	DWORD	Get_One_Size();
	DWORD	Get_Data_Number();
	
	//	전역 함수
public:
	static	F_3D_Data *NEW(F_FVF p_FvF,DWORD p_Number);
	static	F_3D_Data *NEW(DWORD p_Type,DWORD p_FVF,DWORD p_Size);
	
	static	BOOL	Delete_List(LPVOID p_F_3D_Data);
	static	DWORD	Size_FVF(DWORD p_FVF);
};
