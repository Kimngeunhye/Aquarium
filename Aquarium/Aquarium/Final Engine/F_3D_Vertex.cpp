
#include "F_3D_Vertex.h"

F_3D_Vertex::F_3D_Vertex(void)
{
	m_List = NULL;
	m_List_N = 0;
	m_FVF = 0;
	m_VSize = 0;
}

F_3D_Vertex::~F_3D_Vertex(void)
{
	if(m_List != NULL)
	{
		F_LList::Delete_All(m_List);
		m_List = NULL;
	}
	m_List_N = 0;
	m_FVF = 0;
	m_VSize = 0;
}

//	데이터 추가
bool	F_3D_Vertex::Insert(F_3D_Data *p_Data)
{
	//	µ•¿Ã≈Õ »Æ¿Œ.
	if(p_Data == NULL)
		return false;
	//	 ∏ÆΩ∫∆Æ √ﬂ∞° ID ªÁøÎ æ»«‘.
	FS_LList	*t_List = F_LList::New(p_Data,m_List_N + 1,F_3D_Data::Delete_List);
	if(t_List == NULL)
		return false;
	//	∞≥ºˆ ¡ı∞°
	m_List_N = m_List_N + 1;
	//	∏ÆΩ∫∆Æø° √ﬂ∞°
	if(m_List == NULL)
		m_List = t_List;
	else
		F_LList::Insert(m_List,t_List);
	//	FVF º≥¡§.
	Reset_FVF();
	return true;
}

//	ª˝º∫ »ƒ √ﬂ∞°.
F_3D_Data *F_3D_Vertex::Insert(F_3D_Data::F_FVF p_FvF,DWORD p_Number)
{
	F_3D_Data	*t_Data = F_3D_Data::NEW(p_FvF, p_Number);
	if(t_Data == NULL)
		return false;
	//	√ﬂ∞°
	Insert(t_Data);
	return t_Data;
}

//	¡ˆ¡§ µ•¿Ã≈Õ ¡§∫∏  æÚ±‚
F_3D_Data *F_3D_Vertex::Get_Data(DWORD p_List_N)
{
	if(p_List_N >= m_List_N)
		return NULL;
	//	√£±‚
	F_3D_Data	*t_Data = (F_3D_Data *)F_LList::Find_Data_Count(m_List,p_List_N);
	return t_Data;
}

//	¡° «¸Ωƒ ¡¶º≥¡§
DWORD	F_3D_Vertex::Reset_FVF()
{
	m_FVF = 0;
	m_VSize = 0;
	if(m_List == NULL)
	{
		return m_FVF;
	}
	//	∞ÀªÁ
	FS_LList	*t_List = m_List;
	F_3D_Data	*t_Data;
	while(t_List != NULL)
	{
		//	µ•¿Ã≈Õ «¸∫Ø»Ø
		if(t_List->m_Data != NULL)
		{
			t_Data = (F_3D_Data *)t_List->m_Data;
			//	FVF ¥©¿˚ √≥∏Æ
			m_FVF = t_Data->Sum_FVF(m_FVF);
			//	¡§¡° ≈©±‚ ∞ËªÍ
			m_VSize = m_VSize + Get_Type_Size((F_TYPE)t_Data->Get_Type());
		}
		//	¥Ÿ¿Ω ∞ÀªÁ
		t_List = t_List->m_Next;
	}
	return m_FVF;
}

//	≈¨∑°Ω∫ ª˝º∫
F_3D_Vertex	*F_3D_Vertex::New()
{
	F_3D_Vertex	*t_Return = new F_3D_Vertex;
	return t_Return;
}

//	≈¨∑°Ω∫ ªË¡¶
BOOL	F_3D_Vertex::Delete(F_3D_Vertex *p_Vertex)
{
	if(p_Vertex == NULL)
		return true;
	delete p_Vertex;
	return true;
}