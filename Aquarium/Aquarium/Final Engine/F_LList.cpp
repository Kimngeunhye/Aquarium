/*
 *  F_LList.cpp
 *  링크 리스트 클래스
 *
 *  Created by forthen on 11. 4. 18..
 *  Copyright 2011 forthen. All rights reserved.
 *
 */

#include "F_LList.h"


F_LList::F_LList(void)
{
}
F_LList::~F_LList(void)
{
}

//	∏ÆΩ∫∆Æ ª˝º∫
FS_LList	*F_LList::New()
{
	//	∏ÆΩ∫∆Æ 1∞≥ ∏ﬁ∏∏Æ ª˝º∫ π›»Ø.
	FS_LList	*t_List = new FS_LList;
	return t_List;
}
FS_LList	*F_LList::New(LPVOID p_Data,DWORD p_ID,DELETE_LIST	del_Fuc)
{
	//	¿¸¥ﬁ ∞™ »Æ¿Œ
	if(p_Data == NULL)
		return NULL;
	//	∏ÆΩ∫∆Æ ª˝º∫
	FS_LList	*t_List = new FS_LList;
	//	≥ª∫Œ ∞™ º≥¡§
	t_List->m_ID.m_DWORD = p_ID;
	t_List->m_Data = p_Data;
	t_List->m_Del = del_Fuc;
	return t_List;
}

FS_LList	*F_LList::New(LPVOID p_Data,__int64 p_ID,DELETE_LIST	del_Fuc)
{
	//	¿¸¥ﬁ ∞™ »Æ¿Œ
	if(p_Data == NULL)
		return NULL;
	//	∏ÆΩ∫∆Æ ª˝º∫
	FS_LList	*t_List = new FS_LList;
	//	≥ª∫Œ ∞™ º≥¡§
	t_List->m_ID.m_INT64 = p_ID;
	t_List->m_Data = p_Data;
	t_List->m_Del = del_Fuc;
	return t_List;
}

FS_LList	*F_LList::New(LPVOID p_Data,FGS_Code p_ID,DELETE_LIST	del_Fuc)
{
	//	¿¸¥ﬁ ∞™ »Æ¿Œ
	if(p_Data == NULL)
		return NULL;
	//	∏ÆΩ∫∆Æ ª˝º∫
	FS_LList	*t_List = new FS_LList;
	//	≥ª∫Œ ∞™ º≥¡§
	t_List->m_ID.m_Code = p_ID;
	t_List->m_Data = p_Data;
	t_List->m_Del = del_Fuc;
	return t_List;
}

//	∏ÆΩ∫∆Æ ªË¡¶
BOOL	F_LList::Delete(FS_LList *p_List)
{
	if(p_List == NULL)
		return false;
	//	æ’ ∫Œ∫–∞˙ µﬁ ∫Œ∫– πÈæ˜.
	FS_LList	*t_Pre = p_List->m_Pre;
	FS_LList	*t_Next = p_List->m_Next;
	//	æ’ µ⁄ ∫Œ∫– ø¨∞·.
	if((t_Pre != NULL)||(t_Next != NULL))
	{
		if(t_Pre == NULL)
			t_Next->m_Pre = NULL;
		else if(t_Next == NULL)
			t_Pre->m_Next = NULL;
		else
		{
			t_Pre->m_Next = t_Next;
			t_Next->m_Pre = t_Pre;
		}
	}
	//	¥ÎªÛ ªË¡¶
	delete p_List;
	return true;
}

//	∏µÁ ∏ÆΩ∫∆Æ ªË¡¶
BOOL	F_LList::Delete_All(FS_LList *p_List)
{
	// ¿¸¥ﬁ∞™ »Æ¿Œ
	if(p_List == NULL)
		return false;
	//	∏∂¡ˆ∏∑ ∫Œ∫– ±Ó¡ˆ ªË¡¶
	FS_LList	*t_List = p_List;
	while(t_List)
	{
		//	¥Ÿ¿Ω ∏ÆΩ∫∆Æ πÈæ˜
		p_List = t_List->m_Next;
		//	«ÿ¥Á ∏ÆΩ∫∆Æ ªË¡¶
		F_LList::Delete(t_List);
		//	¥Ÿ¿Ω ∏ÆΩ∫∆Æ ¡ˆ¡§
		t_List = p_List;
	}
	return true;
}

//	∏µÁ ∏ÆΩ∫∆Æø° ∆˜«‘µ» µ•¿Ã≈Õ∏∏ ªË¡¶
BOOL	F_LList::Delete_All_Data(FS_LList *p_List)
{
	// ¿¸¥ﬁ∞™ »Æ¿Œ
	if(p_List == NULL)
		return false;
	//	∏∂¡ˆ∏∑ ∫Œ∫– ±Ó¡ˆ ªË¡¶
	FS_LList	*t_List = p_List;
	while(t_List)
	{
		//	¥Ÿ¿Ω ∏ÆΩ∫∆Æ πÈæ˜
		p_List = t_List->m_Next;
		//	t_List µ•¿Ã≈Õ∏∏ ªË¡¶«—¥Ÿ.
		if(t_List->m_Data != NULL)
		{
			if(t_List->m_Del != NULL)
			{
				t_List->m_Del(t_List->m_Data);
			}
			else
			{
				free(t_List->m_Data);
			}
			t_List->m_Data = NULL;
		}
		//	¥Ÿ¿Ω ∏ÆΩ∫∆Æ ¡ˆ¡§
		t_List = p_List;
	}
	return true;
}

//	∏µÁ ∏ÆΩ∫∆Æ ªË¡¶ µ•¿Ã≈Õ¥¬ ªË¡¶æ»«‘
BOOL	F_LList::Delete_All_NoData(FS_LList *p_List)
{
	// ¿¸¥ﬁ∞™ »Æ¿Œ
	if(p_List == NULL)
		return false;
	//	∏∂¡ˆ∏∑ ∫Œ∫– ±Ó¡ˆ ªË¡¶
	FS_LList	*t_List = p_List;
	while(t_List)
	{
		//	¥Ÿ¿Ω ∏ÆΩ∫∆Æ πÈæ˜
		p_List = t_List->m_Next;
		//	∞¸∏Æ µ•¿Ã≈Õ¥¬ ªË¡¶ æ»«—¥Ÿ.
		t_List->m_Data = NULL;
		t_List->m_Del = NULL;
		//	«ÿ¥Á ∏ÆΩ∫∆Æ ªË¡¶
		F_LList::Delete(t_List);
		//	¥Ÿ¿Ω ∏ÆΩ∫∆Æ ¡ˆ¡§
		t_List = p_List;
	}
	return true;
}

//	∏ÆΩ∫∆Æ √ﬂ∞°. (¥ÎªÛ∏ÆΩ∫∆Æ p_Listø°  p_Insert ∏ÆΩ∫∆Æ √ﬂ∞°)
BOOL	F_LList::Insert(FS_LList *p_List,FS_LList *p_Insert)
{
	//	¿¸¥ﬁ¿Œ¿⁄ »Æ¿Œ.
	if(p_List == NULL)
		return false;
	if(p_Insert == NULL)
		return false;
	//	∏∂¡ˆ∏∑ ∫Œ∫–ø° ≥÷±‚. (≥°∫Œ∫– ∏ÆΩ∫∆Æ √£±‚)
	FS_LList	*t_List = p_List;
	while(t_List)
	{
		if(t_List->m_Next == NULL)
		{
			// «ÿ¥Á ∏ÆΩ∫∆Æ∞° ∏∂¡ˆ∏∑ ¿Œ∞ÊøÏ ¥ÎªÛ √ﬂ∞°.
			t_List->m_Next = p_Insert;
			p_Insert->m_Pre = t_List;
			p_Insert->m_Next = NULL;
			return true;
		}
		else
		{
			//	∏∂¡ˆ∏∑ ∫Œ∫–¿Ã æ∆¥— ∞ÊøÏ ¥Ÿ¿Ω ∏ÆΩ∫∆Æ ∞ÀªÁ.
			t_List = t_List->m_Next;
		}
	}
	return true;
}

//	∏ÆΩ∫∆Æ √£±‚ (¥ÎªÛ∏ÆΩ∫∆Æ p_Listø°º≠ ¡ˆ¡§ p_Data µ•¿Ã≈Õ ∏ÆΩ∫∆Æ √£±‚)
FS_LList	*F_LList::Find(FS_LList *p_List,LPVOID	p_Data)
{
	//	¿¸¥ﬁ ∞™ »Æ¿Œ
	if(p_List == NULL)
		return NULL;
	if(p_Data == NULL)
		return NULL;
	//	√£±‚.
	FS_LList	*t_List = p_List;
	while(t_List)
	{
		// µ•¿Ã≈Õ ∆˜¿Œ∆Æ ∫Ò±≥
		if(t_List->m_Data == p_Data)
			return t_List;
		//	∏∂¡ˆ∏∑ ∫Œ∫–¿Ã æ∆¥— ∞ÊøÏ ¥Ÿ¿Ω ∏ÆΩ∫∆Æ ∞ÀªÁ.
		t_List = t_List->m_Next;
	}
	return NULL;
}

//	∏ÆΩ∫∆Æ √£±‚ (¥ÎªÛ∏ÆΩ∫∆Æ p_Listø°º≠ ¡ˆ¡§ ID ∏ÆΩ∫∆Æ √£±‚)
FS_LList	*F_LList::Find(FS_LList *p_List,DWORD p_ID)
{
	//	¿¸¥ﬁ ∞™ »Æ¿Œ
	if(p_List == NULL)
		return NULL;
	//	√£±‚.
	FS_LList	*t_List = p_List;
	while(t_List)
	{
		// µ•¿Ã≈Õ ∆˜¿Œ∆Æ ∫Ò±≥
		if(t_List->m_ID.m_DWORD == p_ID)
			return t_List;
		//	∏∂¡ˆ∏∑ ∫Œ∫–¿Ã æ∆¥— ∞ÊøÏ ¥Ÿ¿Ω ∏ÆΩ∫∆Æ ∞ÀªÁ.
		t_List = t_List->m_Next;
	}
	return NULL;
}
FS_LList	*F_LList::Find(FS_LList *p_List,__int64 p_ID)
{
	//	¿¸¥ﬁ ∞™ »Æ¿Œ
	if(p_List == NULL)
		return NULL;
	//	√£±‚.
	FS_LList	*t_List = p_List;
	while(t_List)
	{
		// µ•¿Ã≈Õ ∆˜¿Œ∆Æ ∫Ò±≥
		if(t_List->m_ID.m_INT64 == p_ID)
			return t_List;
		//	∏∂¡ˆ∏∑ ∫Œ∫–¿Ã æ∆¥— ∞ÊøÏ ¥Ÿ¿Ω ∏ÆΩ∫∆Æ ∞ÀªÁ.
		t_List = t_List->m_Next;
	}
	return NULL;
}
FS_LList	*F_LList::Find(FS_LList *p_List,FGS_Code p_ID)
{
	//	¿¸¥ﬁ ∞™ »Æ¿Œ
	if(p_List == NULL)
		return NULL;
	//	√£±‚.
	FS_LList	*t_List = p_List;
	while(t_List)
	{
		// µ•¿Ã≈Õ ∆˜¿Œ∆Æ ∫Ò±≥
		if(t_List->m_ID.m_Code.m_Hi == p_ID.m_Hi)
		{
			if(t_List->m_ID.m_Code.m_Lo == p_ID.m_Lo)
			{
				return t_List;
			}
		}
		//	∏∂¡ˆ∏∑ ∫Œ∫–¿Ã æ∆¥— ∞ÊøÏ ¥Ÿ¿Ω ∏ÆΩ∫∆Æ ∞ÀªÁ.
		t_List = t_List->m_Next;
	}
	return NULL;
}

//	¥ÎªÛ ∏ÆΩ∫∆Æ¿« ≥°∫Œ∫– √£±‚
FS_LList	*F_LList::Find_Last(FS_LList *p_List)
{
	//	¿¸¥ﬁ ∞™ »Æ¿Œ
	if(p_List == NULL)
		return NULL;
	//	√£±‚.
	FS_LList	*t_List = p_List;
	while(t_List)
	{
		//	∏∂¡ˆ∏∑ ∫Œ∫– »Æ¿Œ.
		if(t_List->m_Next == NULL)
		{
			return t_List;
		}
		//	∏∂¡ˆ∏∑ ∫Œ∫–¿Ã æ∆¥— ∞ÊøÏ ¥Ÿ¿Ω ∏ÆΩ∫∆Æ ∞ÀªÁ.
		t_List = t_List->m_Next;
	}
	return NULL;
}

//	µ•¿Ã≈Õ √£±‚ (¥ÎªÛ∏ÆΩ∫∆Æ p_Listø°º≠ µ•¿Ã≈Õ √£±‚)
LPVOID		F_LList::Find_Data(FS_LList *p_List,DWORD p_ID)
{
	//	¿¸¥ﬁ ∞™ »Æ¿Œ
	if(p_List == NULL)
		return NULL;
	//	√£±‚.
	FS_LList	*t_List = p_List;
	while(t_List)
	{
		// µ•¿Ã≈Õ ∆˜¿Œ∆Æ ∫Ò±≥
		if(t_List->m_ID.m_DWORD == p_ID)
			return t_List->m_Data;
		//	∏∂¡ˆ∏∑ ∫Œ∫–¿Ã æ∆¥— ∞ÊøÏ ¥Ÿ¿Ω ∏ÆΩ∫∆Æ ∞ÀªÁ.
		t_List = t_List->m_Next;
	}
	return NULL;
}
LPVOID		F_LList::Find_Data(FS_LList *p_List,__int64 p_ID)
{
	//	¿¸¥ﬁ ∞™ »Æ¿Œ
	if(p_List == NULL)
		return NULL;
	//	√£±‚.
	FS_LList	*t_List = p_List;
	while(t_List)
	{
		// µ•¿Ã≈Õ ∆˜¿Œ∆Æ ∫Ò±≥
		if(t_List->m_ID.m_INT64 == p_ID)
			return t_List->m_Data;
		//	∏∂¡ˆ∏∑ ∫Œ∫–¿Ã æ∆¥— ∞ÊøÏ ¥Ÿ¿Ω ∏ÆΩ∫∆Æ ∞ÀªÁ.
		t_List = t_List->m_Next;
	}
	return NULL;
}
LPVOID		F_LList::Find_Data(FS_LList *p_List,FGS_Code p_ID)
{
	//	¿¸¥ﬁ ∞™ »Æ¿Œ
	if(p_List == NULL)
		return NULL;
	//	√£±‚.
	FS_LList	*t_List = p_List;
	while(t_List)
	{
		// µ•¿Ã≈Õ ∆˜¿Œ∆Æ ∫Ò±≥
		if(t_List->m_ID.m_Code.m_Hi == p_ID.m_Hi)
		{
			if(t_List->m_ID.m_Code.m_Lo == p_ID.m_Lo)
			{
				return t_List->m_Data;
			}
		}
		//	∏∂¡ˆ∏∑ ∫Œ∫–¿Ã æ∆¥— ∞ÊøÏ ¥Ÿ¿Ω ∏ÆΩ∫∆Æ ∞ÀªÁ.
		t_List = t_List->m_Next;
	}
	return NULL;
}

//	∏ÆΩ∫∆Æ ¿ßƒ° ∞™¿« µ•¿Ã≈Õ æÚ±‚
LPVOID		F_LList::Find_Data_Count(FS_LList *p_List,DWORD p_Count)
{
	//	¿¸¥ﬁ ∞™ »Æ¿Œ
	if(p_List == NULL)
		return NULL;
	
	//	√£±‚.
	FS_LList	*t_List = p_List;
	DWORD	t_Count = 0;
	while(t_List)
	{
		// ¿ßƒ° π¯»£ »Æ¿Œ
		if(t_Count == p_Count)
			return t_List->m_Data;
		//	∏∂¡ˆ∏∑ ∫Œ∫–¿Ã æ∆¥— ∞ÊøÏ ¥Ÿ¿Ω ∏ÆΩ∫∆Æ ∞ÀªÁ.
		t_List = t_List->m_Next;
		t_Count++;
	}
	return NULL;
}

//	¡ˆ¡§∏ÆΩ∫∆Æ¿« ∞≥ºˆ æÚ±‚
DWORD		F_LList::Get_List_Count(FS_LList *p_List)
{
	//	¿¸¥ﬁ ∞™ »Æ¿Œ
	if(p_List == NULL)
		return 0;
	
	//	√£±‚.
	FS_LList	*t_List = p_List;
	DWORD	t_Count = 0;
	while(t_List)
	{
		//	∏∂¡ˆ∏∑ ∫Œ∫–¿Ã æ∆¥— ∞ÊøÏ ¥Ÿ¿Ω ∏ÆΩ∫∆Æ ∞ÀªÁ.
		t_List = t_List->m_Next;
		t_Count++;
	}
	return t_Count;
}

//	¡ˆ¡§∏ÆΩ∫∆Æ æÚ±‚
FS_LList	*F_LList::Get_List(FS_LList *p_List,DWORD p_Num)
{
	//	¿¸¥ﬁ ∞™ »Æ¿Œ
	if(p_List == NULL)
		return NULL;
	
	//	√£±‚.
	FS_LList	*t_List = p_List;
	DWORD	t_Count = 0;
	while(t_List)
	{
		// ¿ßƒ° π¯»£ »Æ¿Œ
		if(t_Count == p_Num)
			return t_List;
		//	∏∂¡ˆ∏∑ ∫Œ∫–¿Ã æ∆¥— ∞ÊøÏ ¥Ÿ¿Ω ∏ÆΩ∫∆Æ ∞ÀªÁ.
		t_List = t_List->m_Next;
		t_Count++;
	}
	return NULL;
}

//	µ•¿Ã≈Õ∏∏ º≥¡§ æ»µ» ∏µ≈© ∏ÆΩ∫∆Æ æÚ±‚
FS_LList	*F_LList::Find_NULL(FS_LList *p_List)
{
	//	¿¸¥ﬁ ∞™ »Æ¿Œ
	if(p_List == NULL)
		return NULL;
	//	√£±‚.
	FS_LList	*t_List = p_List;
	while(t_List)
	{
		// µ•¿Ã≈Õ ∆˜¿Œ∆Æ ∫Ò±≥
		if((t_List->m_ID.m_INT64 != 0)&&(t_List->m_Data == NULL))
		{
			//	µ•¿Ã≈Õ º≥¡§ æ»µ» ∏ÆΩ∫∆Æ
			return t_List;
		}
		//	∏∂¡ˆ∏∑ ∫Œ∫–¿Ã æ∆¥— ∞ÊøÏ ¥Ÿ¿Ω ∏ÆΩ∫∆Æ ∞ÀªÁ.
		t_List = t_List->m_Next;
	}
	return NULL;
}

/////FDC_RYU_100127	Key : ID.DWORD Sort ¡§∑ƒ ±∏«ˆ
// ∏Ò¿˚ : ID.DWORD ±‚¡ÿ¿∏∑Œ Sort (¿¸¡¶ ID ¡ﬂ∫π «„øÎ æ»«‘)
// ¿‘∑¬ : ¡§∑ƒ«“ ∏ÆΩ∫∆Æ¿« ∑Á∆Æ ≥ÎµÂ
FS_LList    *F_LList::Sort_List_Id(FS_LList *p_Root)
{
	if(p_Root == NULL)
		return NULL;
	
	// ªı∑ŒøÓ ∏ÆΩ∫∆Æ Root ∞™ ª˝º∫
	FS_LList *t_Return = New(p_Root->m_Data,p_Root->m_ID.m_DWORD,p_Root->m_Del);
	
	// ªË¡¶«“ ≥ÎµÂ ∫Øºˆ
	FS_LList *t_Del = NULL;
	
	// ¿Ã¿¸ ∏ÆΩ∫∆Æ ø°º≠ ≥ÎµÂ √ﬂ√‚ ±‚¡ÿ º≥¡§
	FS_LList *t_Roof = p_Root->m_Next;
	
	// ªı∑ŒøÓ ∏ÆΩ∫∆Æø° ª¿‘ ¿ßƒ° º≥¡§ ∫Øºˆ
	FS_LList *t_p  = NULL;
	
	// ª¿‘«“ ≥ÎµÂ ∫Øºˆ
	FS_LList *t_New = NULL;
	
	// ¡§∑ƒ Ω√¿€
	while(t_Roof != NULL)
	{
		// ª¿‘ ¿ßƒ° ∫Øºˆ ªı∑ŒøÓ ∏ÆΩ∫∆Æ Root ∑Œ ¿Áº≥¡§
		t_p		 = t_Return;
		
		// ¿Ã¿¸ ≥ÎµÂ √ﬂ√‚ µ•¿Ã≈Õ∞° ªı∑ŒøÓ ∏ÆΩ∫∆Æ √π ≥ÎµÂ ID.Dword ∫∏¥Ÿ ¿€¿∏∏È
		if(t_Roof->m_ID.m_DWORD < t_Return->m_ID.m_DWORD)
		{
			// ª¿‘ ¿ßƒ° √£±‚
			while(t_p != NULL)
			{
				
				// «ˆ¿Á ¿ßƒ°∞° √π ≥ÎµÂ¿Ã∏È
				if(t_p->m_Pre == NULL)
				{
					// ªı∑ŒøÓ ∏ÆΩ∫∆Æ √π ∫Œ∫–ø° ª¿‘
					t_New = New(t_Roof->m_Data,t_Roof->m_ID.m_DWORD,t_Roof->m_Del);
					t_New->m_Next = t_p;
					t_New->m_Pre  = NULL;
					
					t_p->m_Pre  = t_New;
					
					// ªı∑ŒøÓ ∏ÆΩ∫∆Æ Root ∫Ø∞Ê
					t_Return = t_New;
					
					t_New	 = NULL;
					break;
				}
				
				// ª¿‘«“ ≥ÎµÂ∞° ¥Ÿ¿Ω ¿ßƒ° ∞™ ∫∏¥Ÿ ≈´∞ÊøÏ ª¿‘ ¡¯«‡
				if(t_Roof->m_ID.m_DWORD > t_p->m_Pre->m_ID.m_DWORD)
				{
					// ªı∑ŒøÓ ≥ÎµÂ ª˝º∫ π◊ ø¨∞·
					t_New = New(t_Roof->m_Data,t_Roof->m_ID.m_DWORD,t_Roof->m_Del);
					
					t_p->m_Pre->m_Next = t_New;
					
					t_New->m_Pre	   = t_p->m_Pre;
					t_New->m_Next	   = t_p;
					
					t_p->m_Pre		   = t_New;
					
					t_New	 = NULL;
					break;
				}
				t_p = t_p->m_Pre;
			}
		}
		
		// ¿Ã¿¸ ≥ÎµÂ √ﬂ√‚ µ•¿Ã≈Õ∞° ªı∑ŒøÓ ∏ÆΩ∫∆Æ √π ≥ÎµÂ ID.Dword ∫∏¥Ÿ ≈©∏È
		if(t_Roof->m_ID.m_DWORD > t_Return->m_ID.m_DWORD)
		{
			// ª¿‘ ¿ßƒ° √£±‚
			while(t_p != NULL)
			{
				// «ˆ¿Á ¿ßƒ°∞° ≥°≥ÎµÂ¿Ã∏È
				if(t_p->m_Next == NULL)
				{
					// ªı∑ŒøÓ ∏ÆΩ∫∆Æ √π ∫Œ∫–ø° ª¿‘
					t_New = New(t_Roof->m_Data,t_Roof->m_ID.m_DWORD,t_Roof->m_Del);
					t_New->m_Next = NULL;
					t_New->m_Pre  = t_p;
					
					t_p->m_Next  = t_New;
					
					t_New	 = NULL;
					break;
				}
				
				// ª¿‘«“ ≥ÎµÂ∞° ¥Ÿ¿Ω ¿ßƒ° ∞™ ∫∏¥Ÿ ¿€¿∫∞ÊøÏ ª¿‘ ¡¯«‡
				if(t_Roof->m_ID.m_DWORD < t_p->m_Next->m_ID.m_DWORD)
				{
					// ªı∑ŒøÓ ≥ÎµÂ ª˝º∫ π◊ ø¨∞·
					t_New = New(t_Roof->m_Data,t_Roof->m_ID.m_DWORD,t_Roof->m_Del);
					
					t_p->m_Next->m_Pre = t_New;
					
					t_New->m_Pre	   = t_p;
					t_New->m_Next	   = t_p->m_Next;
					
					t_p->m_Next		   = t_New;
					break;
				}
				t_p = t_p->m_Next;
			}
		}
		
		// √ﬂ√‚«— ≥ÎµÂ ªË¡¶ √≥∏Æ(≥ª∫Œµ•¿Ã≈Õ¥¬ ªË¡¶«œ¡ˆ æ ¿Ω)
		t_Del  = t_Roof;
		t_Roof = t_Roof->m_Next;
		t_Del->m_Data = NULL;
		t_Del->m_Del  = NULL;
		F_LList::Delete(t_Del);
		t_Del = NULL;
	}
	
	// ¿Ã¿¸ ∏ÆΩ∫∆Æ ∆˜¿Œ∆Æ NULL √≥∏Æ
	if(p_Root != NULL)
	{
		p_Root->m_Data = NULL;
		p_Root->m_Del  = NULL;
		F_LList::Delete(p_Root);
	}
	
	// ¡§∑ƒµ» ªı∑ŒøÓ ∏ÆΩ∫∆Æ π›»Ø
	return t_Return;
}