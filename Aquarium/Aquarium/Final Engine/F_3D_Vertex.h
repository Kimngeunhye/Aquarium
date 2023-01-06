#pragma once
#include "F_LList.h"
#include "F_3D_Data.h"
/*
	3D 정점 클래스
*/

//	¡§¡° πˆ∆€ ≈¨∑°Ω∫
class F_3D_Vertex
{
	////	≈¨∑°Ω∫ ª˝º∫ ªË¡¶ «‘ºˆ
public:
	F_3D_Vertex(void);
	~F_3D_Vertex(void);

	////	≈¨∑°Ω∫ ≥ª∫Œ ∫Øºˆ
public:
	//	¡§∫∏ ≈¨∑°Ω∫
	FS_LList	*m_List;
	//	¡° ¡§∫∏ ∞≥ºˆ
	DWORD		m_List_N;
	//	¡° «¸Ωƒ º≥¡§
	DWORD		m_FVF;
	//	¡§¡° ≈©±‚
	DWORD		m_VSize;

	////	≈¨∑°Ω∫ ≥ª∫Œ «‘ºˆ
public:
	//	πˆ∆€ √ﬂ∞°
	bool	Insert(F_3D_Data *p_Data);
	//	ª˝º∫ »ƒ √ﬂ∞°.
	F_3D_Data *Insert(F_3D_Data::F_FVF p_FvF,DWORD p_Number);

	//	¡ˆ¡§ µ•¿Ã≈Õ ¡§∫∏  æÚ±‚
	F_3D_Data *Get_Data(DWORD p_List_N);

	//	¡° «¸Ωƒ ¡¶º≥¡§
	DWORD	Reset_FVF();
	
	////	≈¨∑°Ω∫ ø‹∫Œ «‘ºˆ
public:
	//	≈¨∑°Ω∫ ª˝º∫
	static	F_3D_Vertex	*New();
	//	≈¨∑°Ω∫ ªË¡¶
	static	BOOL	Delete(F_3D_Vertex *p_Vertex);
};
