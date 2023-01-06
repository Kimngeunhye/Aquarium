
#include "F_Memory.h"
#include "F_3D_Data.h"

//	데이터의 크기 계산
DWORD	Get_Type_Size(F_TYPE p_Type)
{
	switch(p_Type)
	{
	case DATA_DWORD:
		return 4;
	case DATA_XY:
		return 8;
	case DATA_XYZ:
		return 12;
	case DATA_XYZW:
		return 16;
	case DATA_MATRIX:
		return 64;
	case DATA_XYZB3:
		return 24;
	default:
		break;
	}
	return 0;
}

F_3D_Data::F_3D_Data(void)
{
	memset(&m_3DData,0,sizeof(FS_3D_Data));
}

F_3D_Data::~F_3D_Data(void)
{
	Delete();
}

//	ªË¡¶ «‘ºˆ
BOOL	F_3D_Data::Delete_List(LPVOID p_F_3D_Data)
{
	if(p_F_3D_Data == NULL)
		return false;
	//	µ•¿Ã≈Õ «¸∫Ø»Ø
	F_3D_Data	*t_Data = (F_3D_Data *)p_F_3D_Data;
	//	≈¨∑°Ω∫ ªË¡¶
	delete t_Data;
	return true;
}

//	FVF «¸Ωƒ æÚ±‚
DWORD	F_3D_Data::Get_FVF()
{
	return m_3DData.m_FVF;
}

//	FVF «¸Ωƒ «’ƒ°±‚
DWORD	F_3D_Data::Sum_FVF(DWORD p_FVF)
{
	//	≈ÿΩ∫√≥ ªÛ≈¬∞™ »Æ¿Œ
	DWORD	t_FVF1 = (m_3DData.m_FVF & F_3D_Data::FD_FVF_TEXCOUNT_MASK);
	DWORD	t_FVF2 = (p_FVF & F_3D_Data::FD_FVF_TEXCOUNT_MASK);
	if(t_FVF1 == 0)
	{
		//	¿œπ› »•«’
		if(m_3DData.m_FVF == FD_FVF_XYZB3)
		{
			p_FVF = p_FVF | m_3DData.m_FVF | FD_FVF_LASTBETA_UBYTE4;
		}
		else
			p_FVF = p_FVF | m_3DData.m_FVF;
	}
	else if(t_FVF1 > t_FVF2)
	{
		//	≈ÿΩ∫√≥ ¡§∫∏ ªÛ≈¬ ∞™∏∏ ¡ı∞°.
		p_FVF = t_FVF1 | (p_FVF & 0xfffff0ff);
	}
	return p_FVF;
}

//	≈∏¿‘ æÚ±‚
DWORD	F_3D_Data::Get_Type()
{
	return m_3DData.m_Type;
}

//	≈©±‚ æÚ±‚
DWORD	F_3D_Data::Get_Size()
{
	return m_3DData.m_Size;
}

//	1∞≥ µ•¿Ã≈Õ ≈©±‚ æÚ±‚
DWORD	F_3D_Data::Get_One_Size()
{
	return Get_Type_Size((F_TYPE)m_3DData.m_Type);
}
//	µ•¿Ã≈Õ ∞≥ºˆ æÚ±‚
DWORD	F_3D_Data::Get_Data_Number()
{
	DWORD	t_Gap = Get_One_Size();
	if(t_Gap == 0)
		return 0;
	return (m_3DData.m_Size/t_Gap);
}

//	µ•¿Ã≈Õ ≈¨∑°Ω∫ ª˝º∫ «‘ºˆ
F_3D_Data *F_3D_Data::NEW(F_FVF p_FvF,DWORD p_Number)
{
	F_3D_Data	*t_Return = new F_3D_Data;
	if(t_Return== NULL)
		return NULL;
	t_Return->Create(p_FvF,p_Number);
	return t_Return;
}

//	µ•¿Ã≈Õ ≈¨∑°Ω∫ ª˝º∫ «‘ºˆ
F_3D_Data *F_3D_Data::NEW(DWORD p_Type,DWORD p_FVF,DWORD p_Size)
{
	F_3D_Data	*t_Return = new F_3D_Data;
	if(t_Return== NULL)
		return NULL;
	t_Return->Create(p_Type,p_FVF,p_Size);
	return t_Return;
}

//	πˆ∆€ ª˝º∫
bool	F_3D_Data::Create(F_FVF p_FvF,DWORD p_Number)
{
	if(p_Number == 0) return false;
	//	±‚¡∏ µ•¿Ã≈Õ ªË¡¶.
	Delete();
	//	¡°¡§ ¡§∫∏ ∫∏∞¸
	m_3DData.m_FVF = p_FvF;
	switch(p_FvF)
	{
	case FD_FVF_DIFFUSE:
	case FD_FVF_SPECULAR:
	case FD_FVF_PSIZE:
		{
			m_3DData.m_Type = DATA_DWORD;
			break;
		}
	case FD_FVF_TEX1:
	case FD_FVF_TEX2:
	case FD_FVF_TEX3:
	case FD_FVF_TEX4:
	case FD_FVF_TEX5:
	case FD_FVF_TEX6:
	case FD_FVF_TEX7:
	case FD_FVF_TEX8:
		{
			m_3DData.m_Type = DATA_XY;
			break;
		}
	case FD_FVF_XYZ:
	case FD_FVF_NORMAL:
		{
			m_3DData.m_Type = DATA_XYZ;
			break;
		}
	case FD_FVF_XYZW:
	case FD_FVF_XYZRHW:
		{
			m_3DData.m_Type = DATA_XYZW;
			break;
		}
	case FD_FVF_XYZB3:
		{
			m_3DData.m_Type = DATA_XYZB3;
			break;
		}
		//	πˆ∆€ « ø‰ æ¯¿Ω.
	case FD_FVF_XYZB1:
	case FD_FVF_XYZB2:
	case FD_FVF_XYZB4:
	case FD_FVF_XYZB5:
	case FD_FVF_LASTBETA_UBYTE4:
	case FD_FVF_LASTBETA_D3DCOLOR:
	case FD_FVF_TEX0:
	default:
		return false;
	}
	//	πˆ∆€ ≈©±‚ ±∏«œ±‚
	m_3DData.m_Size = Get_Type_Size((F_TYPE)m_3DData.m_Type)*p_Number;
	//	πˆ∆€ ª˝º∫
	m_3DData.m_Data = (BYTE *)F_Alloc(m_3DData.m_Size);
	if(m_3DData.m_Data == NULL)
		return false;
	return true;
}

//	πˆ∆€ ª˝º∫
bool	F_3D_Data::Create(DWORD p_Type,DWORD p_FVF,DWORD p_Size)
{
	//	±‚¡∏ µ•¿Ã≈Õ ªË¡¶.
	Delete();
	//	¡°¡§ ¡§∫∏ ∫∏∞¸
	m_3DData.m_FVF = p_FVF;
	m_3DData.m_Type = p_Type;
	m_3DData.m_Size = p_Size;
	//	πˆ∆€ ª˝º∫
	m_3DData.m_Data = (BYTE *)F_Alloc(m_3DData.m_Size);
	if(m_3DData.m_Data == NULL)
		return false;
	return true;
}

//	πˆ∆€ ªË¡¶
bool	F_3D_Data::Delete()
{
	if(m_3DData.m_Data != NULL)
	{
		//	∏ﬁ∏∏Æ ªË¡¶
		F_Free(m_3DData.m_Data);
		m_3DData.m_Data = NULL;
	}
	m_3DData.m_FVF = 0;
	m_3DData.m_Type = 0;
	m_3DData.m_Size = 0;
	return true;
}

//	≥ª∫Œ µ•¿Ã≈Õ ∆˜¿Œ≈Õ æÚ±‚
BYTE	*F_3D_Data::Get_Data()
{
	return m_3DData.m_Data;
}

//	¡§¡° «¸Ωƒø° ¿««— ¡§∞À ≈©±‚ ∞ËªÍ
DWORD	F_3D_Data::Size_FVF(DWORD p_FVF)
{
	DWORD t_Size = 0;
	//	¡§¡°
	if((p_FVF&FD_FVF_XYZ) == FD_FVF_XYZ)
	{
		t_Size = t_Size + 12;
	}
	if((p_FVF&FD_FVF_XYZRHW) == FD_FVF_XYZRHW)
	{
		t_Size = t_Size + 16;
	}
	if((p_FVF&FD_FVF_XYZW) == FD_FVF_XYZW)
	{
		t_Size = t_Size + 16;
	}
	if((p_FVF&FD_FVF_XYZB3) == FD_FVF_XYZB3)
	{
		t_Size = t_Size + 24;
	}
	//	≥Î∏ª
	if((p_FVF&FD_FVF_NORMAL) == FD_FVF_NORMAL)
	{
		t_Size = t_Size + 12;
	}
	//	ªˆªÛ ±‚≈∏
	if((p_FVF&FD_FVF_PSIZE) == FD_FVF_PSIZE)
	{
		t_Size = t_Size + 4;
	}
	if((p_FVF&FD_FVF_DIFFUSE) == FD_FVF_DIFFUSE)
	{
		t_Size = t_Size + 4;
	}
	if((p_FVF&FD_FVF_SPECULAR) == FD_FVF_SPECULAR)
	{
		t_Size = t_Size + 4;
	}
	//	UV
	if((p_FVF&FD_FVF_TEX1) == FD_FVF_TEX1)
	{
		t_Size = t_Size + 8;
	}
	if((p_FVF&FD_FVF_TEX2) == FD_FVF_TEX2)
	{
		t_Size = t_Size + 8*2;
	}
	if((p_FVF&FD_FVF_TEX3) == FD_FVF_TEX3)
	{
		t_Size = t_Size + 8*3;
	}
	if((p_FVF&FD_FVF_TEX4) == FD_FVF_TEX4)
	{
		t_Size = t_Size + 8*4;
	}
	if((p_FVF&FD_FVF_TEX5) == FD_FVF_TEX5)
	{
		t_Size = t_Size + 8*5;
	}
	if((p_FVF&FD_FVF_TEX6) == FD_FVF_TEX6)
	{
		t_Size = t_Size + 8*6;
	}
	if((p_FVF&FD_FVF_TEX7) == FD_FVF_TEX7)
	{
		t_Size = t_Size + 8*7;
	}
	if((p_FVF&FD_FVF_TEX8) == FD_FVF_TEX8)
	{
		t_Size = t_Size + 8*8;
	}
	return t_Size;
}