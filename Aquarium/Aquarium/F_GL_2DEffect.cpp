/*
 *  F_GL_2DEffect.cpp
 *  
 *
 *  Created by zendiya on 11. 4. 25..
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "F_GL_2DEffect.h"
#include "F_Memory.h"


F_GL_2DEffect::F_GL_2DEffect()
{
	m_List = NULL;
	m_Init_Out = false;
	m_Effect = NULL;
}

F_GL_2DEffect::~F_GL_2DEffect()
{
	Release();
}

bool	F_GL_2DEffect::Set_Sub_Effect(void *p_Effect)
{
	m_Effect = p_Effect;
	return true;
}

bool	F_GL_2DEffect::Release()
{
	if(m_List != NULL)
	{
		F_LList::Delete_All(m_List);
		m_List = NULL;
	}
	m_Effect = NULL;
	return true;
}

BOOL	F_GL_2DEffect::Delete_Effect(LPVOID p_2DEffect)
{
	if(p_2DEffect == NULL)
		return false;
	FS_2DEffect	*t_del = (FS_2DEffect *)p_2DEffect;
	if(t_del->m_Out_List != NULL)
	{
		F_LList::Delete_All(t_del->m_Out_List);
		t_del->m_Out_List = NULL;
	}
	F_Free(t_del);
	return true;
}


FS_2DEffect *F_GL_2DEffect::Alloc_2DEffect()
{
	FS_2DEffect	*t_Alloc = (FS_2DEffect *)F_Alloc(sizeof(FS_2DEffect));
	if(t_Alloc == NULL)
		return NULL;
	return t_Alloc;
}


//	이펙트 추가
FS_2DEffect	*F_GL_2DEffect::Insert(int p_Index,FS_Sprite *p_Sprite)
{
	if(p_Sprite == NULL)
		return	NULL;

	FS_2DEffect *t_Data = Find_Data(p_Index);
	if(t_Data != NULL)
	{
		if(t_Data->m_Sprite == p_Sprite)
			return t_Data;
		return NULL;
	}
	
	t_Data = F_GL_2DEffect::Alloc_2DEffect();
	if(t_Data == NULL)
		return NULL;
	
	t_Data->m_Sprite = p_Sprite;
	t_Data->m_Index = p_Index;
	t_Data->m_Out_Count = 0;
	Set_EF_Img_Select_Type(t_Data,0,0,0);
	
	
	FS_LList	*t_Insert = F_LList::New((void *)t_Data,(DWORD)p_Index,F_GL_2DEffect::Delete_Effect);
	if(t_Insert == NULL)
	{
		F_GL_2DEffect::Delete_Effect(t_Data);
		return NULL;
	}
	if(m_List == NULL)
	{
		m_List = t_Insert;
	}
	else 
	{
		F_LList::Insert(m_List,t_Insert);
	}
	return	t_Data;
}

FS_LList	*F_GL_2DEffect::Find(int p_Index)
{
	if(m_List == NULL)
		return NULL;
	return	F_LList::Find(m_List,(DWORD)p_Index);
}

FS_2DEffect	*F_GL_2DEffect::Find_Data(int p_Index)
{
	if(m_List == NULL)
		return NULL;
	return	(FS_2DEffect *)F_LList::Find_Data(m_List,(DWORD)p_Index);
}

bool	F_GL_2DEffect::Delete(int p_Index)
{
	if(m_List == NULL)
		return false;
	FS_LList	*t_Del = Find(p_Index);
	if(t_Del == NULL)
		return false;

	if(t_Del == m_List)
	{
		m_List = t_Del->m_Next;
	}
	F_LList::Delete(t_Del);
	return true;
}

bool	F_GL_2DEffect::Set_EF_Time_Limit(FS_2DEffect *p_Effect,float p_Time)
{
	if(p_Effect == NULL)
		return false;
	p_Effect->m_Limit_Time = p_Time;
	return true;
}

bool	F_GL_2DEffect::Set_EF_Img_Select_Type(FS_2DEffect *p_Effect,int p_Type,int p_X_Select,int p_Y_Select)
{
	if(p_Effect == NULL)
		return false;
	if(p_Effect->m_Sprite == NULL)
		return false;
	if(p_Type != 0)
	{
		if((p_Effect->m_Sprite->m_X_Num <= p_X_Select)||(p_Effect->m_Sprite->m_Y_Num <= p_Y_Select))
		{
			return false;
		}
	}
	p_Effect->m_Select_Type = p_Type;
	p_Effect->m_X_Select = p_X_Select;
	p_Effect->m_Y_Select = p_Y_Select;
	return true;
}

bool	F_GL_2DEffect::Set_EF_Rect(FS_2DEffect *p_Effect,float p_sx,float p_sy,float p_w,float p_h)
{
	if(p_Effect == NULL)
		return false;
	p_Effect->m_Rect.m_X = p_sx;
	p_Effect->m_Rect.m_Y = p_sy;
	p_Effect->m_Rect.m_Z = p_w;
	p_Effect->m_Rect.m_W = p_h;
	return true;
}

FS_2DEffect_Info	*F_GL_2DEffect::Out_Effect(int p_Index)
{
	if(m_List == NULL)
		return NULL;
	FS_2DEffect *t_Data = Find_Data(p_Index);
	if(t_Data == NULL)
		return NULL;
	t_Data->m_Out_Count++;
	if(t_Data->m_Out_List != NULL)
	{
		while (F_LList::Find(t_Data->m_Out_List,(DWORD)t_Data->m_Out_Count) != NULL) 
		{
			t_Data->m_Out_Count++;
			if(t_Data->m_Out_Count > 100000)
			{
				m_Init_Out = true;
				return NULL;
			}
		}
	}
		
	FS_2DEffect_Info *t_Out = (FS_2DEffect_Info *)F_Alloc(sizeof(FS_2DEffect_Info));
	if(t_Out == NULL)
		return NULL;
	
	FS_LList	*t_Insert = F_LList::New((void *)t_Out,(DWORD)t_Data->m_Out_Count,NULL);
	if(t_Insert == NULL)
	{
		F_Free((void *)t_Out);
		return NULL;
	}
	if(t_Data->m_Out_List == NULL)
	{
		t_Data->m_Out_List = t_Insert;
	}
	else 
	{
		F_LList::Insert(t_Data->m_Out_List,t_Insert);

	}
	return t_Out;
}

bool	F_GL_2DEffect::Init_Out_Count()
{
	if(!m_Init_Out)
		return false;
	m_Init_Out = false;
	
	FS_LList	*t_List = m_List;
	FS_2DEffect *t_Data = NULL;
	while (t_List != NULL)
	{
		t_Data = (FS_2DEffect *)t_List->m_Data;
		if(t_Data != NULL)
		{
			if(t_Data->m_Out_Count > 100000)
			{
				t_Data->m_Out_Count = 0;
				if(t_Data->m_Out_List != NULL)
				{
					F_LList::Delete_All(t_Data->m_Out_List);
					t_Data->m_Out_List = NULL;
				}
			}
		}
		t_List = t_List->m_Next;
	}
	return true;
}

bool	F_GL_2DEffect::Stop_Out_Effect()
{
	FS_LList	*t_List = m_List;
	FS_2DEffect *t_Data = NULL;
	while (t_List != NULL)
	{
		t_Data = (FS_2DEffect *)t_List->m_Data;
		if(t_Data != NULL)
		{
			t_Data->m_Out_Count = 0;
			if(t_Data->m_Out_List != NULL)
			{
				F_LList::Delete_All(t_Data->m_Out_List);
				t_Data->m_Out_List = NULL;
			}
		}
		t_List = t_List->m_Next;
	}
	return true;
}

bool	F_GL_2DEffect::Pre_Render(float t_DTime)
{
	FS_LList	*t_List = m_List;
	FS_2DEffect *t_Data = NULL;
	bool	t_TF = false;
	while (t_List != NULL)
	{
		t_Data = (FS_2DEffect *)t_List->m_Data;
		if(t_Data != NULL)
		{
			if(Pre_Render_Effect(t_Data,t_DTime))
			{
				t_TF = true;
			}
		}
		t_List = t_List->m_Next;
	}
	if(t_TF)
	{
		t_List = m_List;
		while (t_List != NULL)
		{
			t_Data = (FS_2DEffect *)t_List->m_Data;
			if(t_Data != NULL)
			{
				Render_Text_Delete(t_Data);
			}
			t_List = t_List->m_Next;
		}
	}
	return t_TF;
}

bool	F_GL_2DEffect::Render(float t_DTime,float p_Alpha)
{
	FS_LList	*t_List = m_List;
	FS_2DEffect *t_Data = NULL;
	while (t_List != NULL)
	{
		t_Data = (FS_2DEffect *)t_List->m_Data;
		if(t_Data != NULL)
		{
			Render_Effect(t_Data,t_DTime,p_Alpha);
		}
		t_List = t_List->m_Next;
	}
	return true;
}

bool	F_GL_2DEffect::Pre_Render_Effect(FS_2DEffect *p_Effect,float t_DTime)
{
	if(p_Effect == NULL)
		return false;
	if(p_Effect->m_Out_List == NULL)
		return false;
	FS_LList	*t_Del = NULL;
	FS_LList	*t_List = p_Effect->m_Out_List;
	FS_2DEffect_Info *t_Effect = NULL;
	bool	t_Return_TF = false;
	while(t_List != NULL)
	{
		t_Effect = (FS_2DEffect_Info *)t_List->m_Data;
		if(t_Effect != NULL)
		{
			t_Effect->m_Time = t_Effect->m_Time + t_DTime;
			if((t_Effect->m_Time > p_Effect->m_Limit_Time)||(t_Effect->m_Type == 10))
			{
				t_Del = t_List;
				if(t_Effect->m_Result1 == 1)
				{
					t_Return_TF = true;
				}
			}
			else
			{
				Pre_Render_Effect_Data(p_Effect,t_Effect,t_DTime);
				if(t_Effect->m_Type == 10)
				{
					t_Del = t_List;
					if(t_Effect->m_Result1 == 1)
					{
						t_Return_TF = true;
					}
				}
			}

		}
		t_List = t_List->m_Next;
		if(t_Del != NULL)
		{
			if(t_Del == p_Effect->m_Out_List)
			{
				p_Effect->m_Out_List = t_Del->m_Next;
			}
			F_LList::Delete(t_Del);
			t_Del = NULL;
		}
	}
	return t_Return_TF;
}

bool	F_GL_2DEffect::Render_Text_Delete(FS_2DEffect *p_Effect)
{
	if(p_Effect == NULL)
		return false;
	FS_LList	*t_List = p_Effect->m_Out_List;
	FS_2DEffect_Info *t_Effect = NULL;
	while(t_List != NULL)
	{
		t_Effect = (FS_2DEffect_Info *)t_List->m_Data;
		if(t_Effect != NULL)
		{
			if(t_Effect->m_Text != NULL)
			{
				t_Effect->m_Text = NULL;
				t_Effect->m_Result1 = 0;
			}
			if(t_Effect->m_Result1 > 0)
			{
				t_Effect->m_Result1 = 0;
			}
		}
		t_List = t_List->m_Next;
	}	
	return true;
}

bool	F_GL_2DEffect::Pre_Render_Effect_Data(FS_2DEffect *p_Effect,FS_2DEffect_Info *p_Info,float t_DTime)
{
	if(p_Effect == NULL)
		return false;
	if(p_Info == NULL)
		return false;
	if(p_Info->m_Type == 0)
	{
		p_Info->m_Type = 1;
	}
	p_Info->m_Alpha_TF = false;
	p_Info->m_Alpha = 1.0f;
	
	FS_MATRIX	t_Mat1,t_Mat2,t_Mat3,t_Mat4;
	FS_MATRIX::Scale(&t_Mat1,p_Effect->m_Scale,p_Effect->m_Scale,p_Effect->m_Scale);
	FS_MATRIX::Rot(&t_Mat2,0.0f,0.0f,1.0f,0.0f);
    FS_MATRIX::Translate(&t_Mat3,p_Info->m_Pos.m_X,p_Info->m_Pos.m_Y,p_Info->m_Pos.m_Z);
	
	if(p_Info->m_Move_Param1 == 1)
	{
		float t_Move = t_DTime*p_Info->m_Move_Dir1.m_W;
		if(p_Info->m_Move_Dir1.m_X < 0.0f)
			p_Info->m_Y_Rot = 1;
		else
			p_Info->m_Y_Rot = 0;
		p_Info->m_Pos.m_X = p_Info->m_Pos.m_X + p_Info->m_Move_Dir1.m_X*t_Move;
		p_Info->m_Pos.m_Y = p_Info->m_Pos.m_Y + p_Info->m_Move_Dir1.m_Y*t_Move;
		p_Info->m_Pos.m_Z = p_Info->m_Pos.m_Z + p_Info->m_Move_Dir1.m_Z*t_Move;
		FS_MATRIX::Translate(&t_Mat4,
							 p_Info->m_Move_Dir1.m_X*t_Move,
							 p_Info->m_Move_Dir1.m_Y*t_Move,
							 p_Info->m_Move_Dir1.m_Z*t_Move);
		FS_MATRIX::Mult(&t_Mat3,&t_Mat3,&t_Mat4);
        if(((p_Info->m_TPos.m_X - p_Info->m_Pos.m_X)*p_Info->m_Move_Dir1.m_X < 0.0f)
		   ||((p_Info->m_TPos.m_Y - p_Info->m_Pos.m_Y)*p_Info->m_Move_Dir1.m_Y < 0.0f))
		{
			p_Info->m_Time = p_Effect->m_Limit_Time;	
		}
	}
	else if(p_Info->m_Move_Param1 == 2)
	{
		FS_MATRIX::Rot(&t_Mat4,p_Info->m_Move_Dir1.m_X,p_Info->m_Move_Dir1.m_Y,
					   p_Info->m_Move_Dir1.m_Z,p_Info->m_Move_Dir1.m_W*p_Info->m_Time);
		FS_MATRIX::Mult(&t_Mat2,&t_Mat2,&t_Mat4);
		
		FS_MATRIX::Scale(&t_Mat4,4.0f*p_Info->m_Time/p_Effect->m_Limit_Time,4.0f*p_Info->m_Time/p_Effect->m_Limit_Time,1.0f);
		FS_MATRIX::Mult(&t_Mat1,&t_Mat1,&t_Mat4);
		
		p_Info->m_Alpha_TF = true;
		p_Info->m_Alpha = 1.0f- p_Info->m_Time/p_Effect->m_Limit_Time;
		if(p_Info->m_Alpha < 0.0f)
			p_Info->m_Alpha = 0.0f;
		if(p_Effect->m_Select_Type == 3)
		{
			if(p_Effect->m_Sprite != NULL)
			{
				if(p_Effect->m_Sprite->m_DTime > 0.0f)
				{
					float t_Select = p_Info->m_Time/p_Effect->m_Sprite->m_DTime;
					p_Info->m_Select_N = (int)t_Select;
				}
			}
		}
	}
	else if(p_Info->m_Move_Param1 == 3)
	{
		p_Info->m_Alpha_TF = true;
		p_Info->m_Alpha = 1.0f- p_Info->m_Time/p_Effect->m_Limit_Time;
		if(p_Info->m_Alpha < 0.0f)
			p_Info->m_Alpha = 0.0f;
		FS_MATRIX::Scale(&t_Mat4,
							 (p_Info->m_Move_Dir1.m_X+p_Info->m_Move_Dir1.m_Y*(1.0f -p_Info->m_Alpha)),
							 (p_Info->m_Move_Dir1.m_X+p_Info->m_Move_Dir1.m_Y*(1.0f -p_Info->m_Alpha)),1.0f);
		FS_MATRIX::Mult(&t_Mat1,&t_Mat1,&t_Mat4);	
	}
	else if(p_Info->m_Move_Param1 == 9)
	{
		float	t_Sin_F = sinf(p_Info->m_Time*10.0f);
		float	t_Move = p_Info->m_Time;
		float	t_Len = FS_XYZ::Len((FS_XYZ&)p_Info->m_Move_Dir1);
		FS_XYZ	t_Dir = FS_XYZ::Normal((FS_XYZ&)p_Info->m_Move_Dir1);
		
		FS_MATRIX::Translate(&t_Mat4,
							 t_Dir.m_X*t_Move*p_Info->m_Move_Dir1.m_W,
							 t_Dir.m_Y*t_Move*p_Info->m_Move_Dir1.m_W,
							 t_Dir.m_Z*t_Move*p_Info->m_Move_Dir1.m_W);
		FS_MATRIX::Mult(&t_Mat3,&t_Mat3,&t_Mat4);
		FS_MATRIX::Rot(&t_Mat4,0.0f,0.0f,1.0f,5.0f*t_Sin_F);
		FS_MATRIX::Mult(&t_Mat2,&t_Mat2,&t_Mat4);
		
		if(t_Len > 0.0f)
		{
			FS_MATRIX::Scale(&t_Mat4,
							 (1.0f+(2.0f*t_Move*p_Info->m_Move_Dir1.m_W)/t_Len)*(1.0f + 0.05f*t_Sin_F),
							 (1.0f+(2.0f*t_Move*p_Info->m_Move_Dir1.m_W)/t_Len)*(1.0f - 0.05f*t_Sin_F),1.0f);
			FS_MATRIX::Mult(&t_Mat1,&t_Mat1,&t_Mat4);
		}		
		p_Info->m_Alpha_TF = true;
		p_Info->m_Alpha = 1.0f- p_Info->m_Time/p_Effect->m_Limit_Time;
		if(p_Info->m_Alpha < 0.0f)
			p_Info->m_Alpha = 0.0f;
	}
	
	if(p_Info->m_Move_Param2 == 10)
	{
		float	t_Sin_F = sinf(p_Info->m_Time*4.0f);
		FS_MATRIX::Translate(&t_Mat4,
							 p_Info->m_Move_Dir2.m_X*p_Info->m_Move_Dir2.m_W*t_Sin_F,
							 p_Info->m_Move_Dir2.m_Y*p_Info->m_Move_Dir2.m_W*t_Sin_F,
							 p_Info->m_Move_Dir2.m_Z*p_Info->m_Move_Dir2.m_W*t_Sin_F);
		FS_MATRIX::Mult(&t_Mat3,&t_Mat3,&t_Mat4);
		FS_MATRIX::Rot(&t_Mat4,0.0f,1.0f,0.0f,15.0f*t_Sin_F);
		FS_MATRIX::Mult(&t_Mat2,&t_Mat2,&t_Mat4);
		//FS_MATRIX::Rot(&t_Mat4,0.0f,0.0f,1.0f,3.0f*t_Sin_F*t_Sin_F);
		//FS_MATRIX::Mult(&t_Mat2,&t_Mat2,&t_Mat4);
		
		FS_MATRIX::Scale(&t_Mat4,1.0f+0.02f*t_Sin_F,
						 1.0f-0.05f*t_Sin_F,1.0f);
		FS_MATRIX::Mult(&t_Mat1,&t_Mat1,&t_Mat4);
	}
	else if(p_Info->m_Move_Param2 == 14)
	{
		if(p_Info->m_Move_Dir2.m_W >= 20.0f)
		{
			p_Info->m_Move_Dir2.m_Z = (((float)(rand()%100))/100.0f)*p_Info->m_Move_Dir2.m_X;
			if(p_Info->m_Move_Dir2.m_Y > 0.0f)
			{
				p_Info->m_Move_Dir2.m_Z = -p_Info->m_Move_Dir2.m_Z;
			}
			p_Info->m_Move_Dir2.m_Z = (p_Info->m_Move_Dir2.m_Z - p_Info->m_Move_Dir2.m_Y)/20.0f;
			p_Info->m_Move_Dir2.m_W = 0.0f;
		}
		p_Info->m_Move_Dir2.m_W = p_Info->m_Move_Dir2.m_W + 1.0f;
		p_Info->m_Move_Dir2.m_Y = p_Info->m_Move_Dir2.m_Y + p_Info->m_Move_Dir2.m_Z;
		
		FS_MATRIX::Translate(&t_Mat4,p_Info->m_Move_Dir2.m_Y,0.0f,0.0f);
		FS_MATRIX::Mult(&t_Mat3,&t_Mat3,&t_Mat4);
	}
	
	if(p_Info->m_Move_Param3 == 31)
	{
		if(p_Info->m_Move_Dir3.m_W > 0.0f)
		{
			p_Info->m_Move_Dir3.m_W = p_Info->m_Move_Dir3.m_W - 1.0f;
			p_Info->m_Move_Dir3.m_Z = p_Info->m_Move_Dir3.m_Z + 1.0f;
			if(p_Info->m_Move_Dir3.m_W < 1.0f)
			{
				p_Info->m_Type = 10;
			}
			else 
			{
				FS_MATRIX::Translate(&t_Mat4,p_Info->m_Move_Dir3.m_X*p_Info->m_Move_Dir3.m_Z,p_Info->m_Move_Dir3.m_Y*p_Info->m_Move_Dir3.m_Z,0.0f);
				FS_MATRIX::Mult(&t_Mat3,&t_Mat3,&t_Mat4);
                float t_Degree_X = FS_XY::Degree_X(p_Info->m_Move_Dir3.m_X,p_Info->m_Move_Dir3.m_Y);
				if(p_Info->m_Y_Rot != 0)
				{		
					if(t_Degree_X < 0.0f)
					{
						t_Degree_X = t_Degree_X + 180.0f;
					}
					else
					{
						t_Degree_X = t_Degree_X - 180.0f;
					}
				}
				
				FS_MATRIX::Rot(&t_Mat4,0.0f,0.0f,1.0f,t_Degree_X);
				FS_MATRIX::Mult(&t_Mat2,&t_Mat2,&t_Mat4);
				
				float	t_Sin_F = sinf(p_Info->m_Time*6.0f);
				FS_MATRIX::Rot(&t_Mat4,0.0f,1.0f,0.0f,40.0f*t_Sin_F);
				FS_MATRIX::Mult(&t_Mat2,&t_Mat2,&t_Mat4);
				
				if((p_Effect->m_EF_Index != 0)&&(m_Effect != NULL))
				{
					if(p_Info->m_Move_Dir3.m_Z < 10.0f)
					{
						if(Rand_Int(2)==1)
						{
							F_GL_2DEffect *t_Main_Effect = (F_GL_2DEffect *)m_Effect;
							FS_2DEffect_Info *t_Out = t_Main_Effect->Out_Effect(p_Effect->m_EF_Index);
							if(t_Out != NULL)
							{
								t_Main_Effect->Set_EF_Start_Pos(t_Out,
										t_Mat3.m[3][0]+Rand_Float(-30.0f,30.0f),
										t_Mat3.m[3][1]+Rand_Float(-30.0f,30.0f),t_Mat3.m[3][2] + 50.0f);
								t_Main_Effect->Set_EF_Move1_Param(t_Out,0.0f,
										200.0f+Rand_Float(-50.0f,50.0f),0.0f,
										60.0f+Rand_Float(-30.0f,30.0f),9);
								t_Main_Effect->Set_EF_Move2_Param(t_Out,5.0f,0.0f,0.0f,20.0f,14);
							}
						}
					}
				}
				
			}
		}
	}

	p_Info->m_Rect.m_X = p_Effect->m_Rect.m_X*t_Mat1.m[0][0] + t_Mat3.m[3][0];
	p_Info->m_Rect.m_Y = p_Effect->m_Rect.m_Y*t_Mat1.m[1][1] + t_Mat3.m[3][1];
	p_Info->m_Rect.m_Z = p_Effect->m_Rect.m_Z*t_Mat1.m[0][0];
	p_Info->m_Rect.m_W = p_Effect->m_Rect.m_W*t_Mat1.m[1][1];
	
	FS_MATRIX::Mult(&t_Mat1,&t_Mat1,&t_Mat2);
	FS_MATRIX::Mult(&p_Info->m_Mat,&t_Mat1,&t_Mat3);
	return true;
}


bool	F_GL_2DEffect::Render_Effect(FS_2DEffect *p_Effect,float t_DTime,float p_Alpha)
{
	if(p_Effect == NULL)
		return false;
	if(p_Effect->m_Out_List == NULL)
		return false;
	
	FS_LList	*t_List = p_Effect->m_Out_List;
	FS_2DEffect_Info *t_Effect = NULL;
	while(t_List != NULL)
	{
		t_Effect = (FS_2DEffect_Info *)t_List->m_Data;
		if(t_Effect != NULL)
		{
			Render_Effect_Data(p_Effect,t_Effect,t_DTime,p_Alpha);
		}
		t_List = t_List->m_Next;
	}
	return	true;
}

bool	F_GL_2DEffect::Render_Effect_Data(FS_2DEffect *p_Effect,FS_2DEffect_Info *p_Info,float t_DTime,float p_Alpha)
{
	if(p_Effect == NULL)
		return false;
	if(p_Info == NULL)
		return false;
	if(p_Effect->m_Sprite == NULL)
		return false;
	if(p_Info->m_Type == 0)
		return false;
	FS_Sprite *t_Sprite = p_Effect->m_Sprite;
	if(t_Sprite->m_Tex == NULL)
		return false;
	if(t_Sprite->m_Vertex == NULL)
		return false;
	
	F_3D_Data *t_Pos = t_Sprite->m_Vertex->Get_Data(0);
	F_3D_Data *t_Uv = t_Sprite->m_Vertex->Get_Data(1);
	if(t_Pos == NULL)
		return false;
	if(t_Uv == NULL)
		return false;
	
	FS_XYZ	*t_VB = (FS_XYZ *)t_Pos->Get_Data();
	FS_XY	*t_UVB = (FS_XY *)t_Uv->Get_Data();
	if(t_VB == NULL)
		return false;
	if(t_UVB == NULL)
		return false;
	
	glPushMatrix();
	glMultMatrixf((GLfloat *)&p_Info->m_Mat);
	F_GL_Texture::Set_Tex_RenderSet(t_Sprite->m_Tex);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	if(p_Info->m_Alpha_TF)
	{
		glColor4f(1.0f,1.0f,1.0f,p_Info->m_Alpha*p_Alpha);
	}
	
	if(p_Effect->m_Select_Type == 0)
	{
		glVertexPointer(3,GL_FLOAT,12,&t_VB[0]);
		glTexCoordPointer(2,GL_FLOAT,8,&t_UVB[0]);
		glDrawArrays(GL_TRIANGLES,0,6);
	}
	else if(p_Effect->m_Select_Type == 1)
	{
		int t_Max_X = t_Sprite->m_X_Num;
		if(p_Info->m_Y_Rot == 1)
		{
			m_Rot_UV[0] = t_UVB[(p_Effect->m_X_Select + p_Effect->m_Y_Select*t_Max_X)*6+2];
			m_Rot_UV[1] = t_UVB[(p_Effect->m_X_Select + p_Effect->m_Y_Select*t_Max_X)*6+5];
			m_Rot_UV[2] = t_UVB[(p_Effect->m_X_Select + p_Effect->m_Y_Select*t_Max_X)*6+0];
			m_Rot_UV[3] = t_UVB[(p_Effect->m_X_Select + p_Effect->m_Y_Select*t_Max_X)*6+0];
			m_Rot_UV[4] = t_UVB[(p_Effect->m_X_Select + p_Effect->m_Y_Select*t_Max_X)*6+5];
			m_Rot_UV[5] = t_UVB[(p_Effect->m_X_Select + p_Effect->m_Y_Select*t_Max_X)*6+1];
			
			glVertexPointer(3,GL_FLOAT,12,&t_VB[(p_Effect->m_X_Select + p_Effect->m_Y_Select*t_Max_X)*6]);
			glTexCoordPointer(2,GL_FLOAT,8,m_Rot_UV);
		}
		else
		{
			glVertexPointer(3,GL_FLOAT,12,&t_VB[(p_Effect->m_X_Select + p_Effect->m_Y_Select*t_Max_X)*6]);
			glTexCoordPointer(2,GL_FLOAT,8,&t_UVB[(p_Effect->m_X_Select + p_Effect->m_Y_Select*t_Max_X)*6]);	
		}
		glDrawArrays(GL_TRIANGLES,0,6);
	}
	else if(p_Effect->m_Select_Type == 3)
	{
		int t_Select = 0;
		if(p_Info->m_Select_N < t_Sprite->m_All_Num)
		{
			t_Select = p_Info->m_Select_N;
		}
		else
		{
			t_Select = t_Sprite->m_All_Num - 1;
		}
		if(t_Select < 0)
		{
			t_Select = 0;
		}
		if(p_Info->m_Y_Rot == 1)
		{
			m_Rot_UV[0] = t_UVB[t_Select*6+2];
			m_Rot_UV[1] = t_UVB[t_Select*6+5];
			m_Rot_UV[2] = t_UVB[t_Select*6+0];
			m_Rot_UV[3] = t_UVB[t_Select*6+0];
			m_Rot_UV[4] = t_UVB[t_Select*6+5];
			m_Rot_UV[5] = t_UVB[t_Select*6+1];
			
			glVertexPointer(3,GL_FLOAT,12,&t_VB[t_Select*6]);
			glTexCoordPointer(2,GL_FLOAT,8,m_Rot_UV);
		}
		else
		{
			glVertexPointer(3,GL_FLOAT,12,&t_VB[t_Select*6]);
			glTexCoordPointer(2,GL_FLOAT,8,&t_UVB[t_Select*6]);	
		}
		glDrawArrays(GL_TRIANGLES,0,6);
	}
	else if(p_Effect->m_Select_Type == 4)
	{
		int	t_Out_Number = p_Info->m_Out_Number;
		if(t_Out_Number < 0)
			t_Out_Number = 0;
		int	t_Line = 1;
		int t_Number = t_Out_Number;
		while ((t_Number/10) > 0) {
			t_Number = t_Number/10;
			t_Line++;
		}
		t_Number = 0;
		
		int t_Count = 0;
		for (int i = t_Line; i > 0; i--)
		{
			if(i == 1)
			{
				t_Number = t_Out_Number%10;
			}
			else
			{
				t_Number = 10;
				for(int j = 1;j < (i-1);j++)
				{
					t_Number = t_Number*10;
				}
				t_Number = t_Out_Number/t_Number;
				t_Number = t_Number%10;
			}
			glPushMatrix();
			glTranslatef(((float)t_Count - ((float)t_Line)/2)*(t_Sprite->m_Width - 5.0f),0.0f,0.0f);
			glVertexPointer(3,GL_FLOAT,12,&t_VB[(t_Number + p_Effect->m_Y_Select*t_Sprite->m_X_Num)*6]);
			glTexCoordPointer(2,GL_FLOAT,8,&t_UVB[(t_Number + p_Effect->m_Y_Select*t_Sprite->m_X_Num)*6]);	
			glDrawArrays(GL_TRIANGLES,0,6);
			glPopMatrix();
			t_Count++;
		}
	}
	
	if(p_Info->m_Alpha_TF)
	{
		glColor4f(1.0f,1.0f,1.0f,p_Alpha);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glPopMatrix();
	
	Render_Sub_Text(p_Info,t_DTime);
	return true;
}

bool	F_GL_2DEffect::Render_Sub_Text(FS_2DEffect_Info *p_Info,float t_DTime)
{
	if(p_Info->m_Text == NULL)
		return false;

	FS_Sprite *t_Sprite = p_Info->m_Text;
	if(t_Sprite->m_Tex == NULL)
		return false;
	if(t_Sprite->m_Vertex == NULL)
		return false;

	F_3D_Data *t_Pos = t_Sprite->m_Vertex->Get_Data(0);
	F_3D_Data *t_Uv = t_Sprite->m_Vertex->Get_Data(1);
	if(t_Pos == NULL)
		return false;
	if(t_Uv == NULL)
		return false;
	
	FS_XYZ	*t_VB = (FS_XYZ *)t_Pos->Get_Data();
	FS_XY	*t_UVB = (FS_XY *)t_Uv->Get_Data();
	if(t_VB == NULL)
		return false;
	if(t_UVB == NULL)
		return false;		
	glPushMatrix();
	glTranslatef(p_Info->m_Text_Pos.m_X + p_Info->m_Mat.m[3][0],
				 p_Info->m_Text_Pos.m_Y + p_Info->m_Mat.m[3][1],
				 p_Info->m_Text_Pos.m_Z + p_Info->m_Mat.m[3][2]);
	
	F_GL_Texture::Set_Tex_RenderSet(t_Sprite->m_Tex);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	glVertexPointer(3,GL_FLOAT,12,t_VB);
	glTexCoordPointer(2,GL_FLOAT,8,t_UVB);
	glDrawArrays(GL_TRIANGLES,0,6);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glPopMatrix();
	return true;
}

bool	F_GL_2DEffect::Set_EF_Move1_Param(FS_2DEffect_Info *p_EF_Info,float dx,float dy,float dz,float dMove,int p_Parm)
{
	if(p_EF_Info == NULL)
		return false;
	p_EF_Info->m_Move_Dir1.m_X = dx; 
	p_EF_Info->m_Move_Dir1.m_Y = dy; 
	p_EF_Info->m_Move_Dir1.m_Z = dz; 
	p_EF_Info->m_Move_Dir1.m_W = dMove;
	p_EF_Info->m_Move_Param1 = p_Parm;
	return true;
}
bool	F_GL_2DEffect::Set_EF_Move2_Param(FS_2DEffect_Info *p_EF_Info,float dx,float dy,float dz,float dMove,int p_Parm)
{
	if(p_EF_Info == NULL)
		return false;
	p_EF_Info->m_Move_Dir2.m_X = dx; 
	p_EF_Info->m_Move_Dir2.m_Y = dy; 
	p_EF_Info->m_Move_Dir2.m_Z = dz; 
	p_EF_Info->m_Move_Dir2.m_W = dMove;
	p_EF_Info->m_Move_Param2 = p_Parm;
	return true;
}
bool	F_GL_2DEffect::Set_EF_Move3_Param(FS_2DEffect_Info *p_EF_Info,float dx,float dy,float dz,float dMove,int p_Parm)
{
	if(p_EF_Info == NULL)
		return false;
	p_EF_Info->m_Move_Dir3.m_X = dx; 
	p_EF_Info->m_Move_Dir3.m_Y = dy; 
	p_EF_Info->m_Move_Dir3.m_Z = dz; 
	p_EF_Info->m_Move_Dir3.m_W = dMove;
	p_EF_Info->m_Move_Param3 = p_Parm;	
	return true;
}

bool	F_GL_2DEffect::Set_EF_Start_Pos(FS_2DEffect_Info *p_EF_Info,float dx,float dy,float dz)
{
	if(p_EF_Info == NULL)
		return false;
	p_EF_Info->m_Pos.m_X = dx;
	p_EF_Info->m_Pos.m_Y = dy;
	p_EF_Info->m_Pos.m_Z = dz;
	return true;
}

bool	F_GL_2DEffect::Set_EF_End_Pos(FS_2DEffect_Info *p_EF_Info,float dx,float dy,float dz)
{
	if(p_EF_Info == NULL)
		return false;
	p_EF_Info->m_TPos.m_X = dx;
	p_EF_Info->m_TPos.m_Y = dy;
	p_EF_Info->m_TPos.m_Z = dz;
	return	true;
}

bool	F_GL_2DEffect::Set_EF_Result(FS_2DEffect_Info *p_EF_Info,int p_Result1,int p_Result2)
{
	if(p_EF_Info == NULL)
		return false;
	p_EF_Info->m_Result1 = p_Result1;
	p_EF_Info->m_Result2 = p_Result2;
	return	true;
}

bool	F_GL_2DEffect::Set_EF_Number(FS_2DEffect_Info *p_EF_Info,int p_Number)
{
	if(p_EF_Info == NULL)
		return false;
	p_EF_Info->m_Out_Number = p_Number;
	return true;
}

bool	F_GL_2DEffect::Set_EF_Text_Pos(FS_2DEffect_Info *p_EF_Info,FS_Sprite *p_Text,float dx,float dy,float dz,float scale)
{
	if(p_EF_Info == NULL)
	{
		return false;
	}
	p_EF_Info->m_Text = p_Text;
	p_EF_Info->m_Text_Pos.m_X = dx;
	p_EF_Info->m_Text_Pos.m_Y = dy;
	p_EF_Info->m_Text_Pos.m_Z = dz;
	p_EF_Info->m_Text_Pos.m_W = scale;
	return true;
}

FS_2DEffect_Info	*F_GL_2DEffect::Get_Conflict(FS_XYZW *p_Rect)
{
	if(p_Rect == NULL)
		return NULL;
	if(m_List == NULL)
		return NULL;
	
	FS_LList			*t_Root = m_List;
	FS_LList			*t_List = NULL;
	FS_2DEffect			*t_Effect = NULL;
	FS_2DEffect_Info	*t_Out = NULL;
	while(t_Root != NULL)
	{
		t_Effect = (FS_2DEffect *)t_Root->m_Data;
		if(t_Effect != NULL)
		{
			t_List = t_Effect->m_Out_List;
			while(t_List != NULL)
			{
				t_Out = (FS_2DEffect_Info *)t_List->m_Data;
				if(t_Out != NULL)
				{
					if(t_Out->m_Type == 1)
					{
						if(!(((p_Rect->m_X > t_Out->m_Rect.m_X)&&(p_Rect->m_X > (t_Out->m_Rect.m_X + t_Out->m_Rect.m_Z)))
						 ||(((p_Rect->m_X+p_Rect->m_Z) < t_Out->m_Rect.m_X)&&((p_Rect->m_X+p_Rect->m_Z) < (t_Out->m_Rect.m_X + t_Out->m_Rect.m_Z)))))
						{
							if(!(((p_Rect->m_Y < t_Out->m_Rect.m_Y)&&(p_Rect->m_Y < (t_Out->m_Rect.m_Y - t_Out->m_Rect.m_W)))
								||(((p_Rect->m_Y-p_Rect->m_W) > t_Out->m_Rect.m_Y)&&((p_Rect->m_Y-p_Rect->m_W) > (t_Out->m_Rect.m_Y - t_Out->m_Rect.m_W)))))
							{
								return t_Out;
							}
						}
					}
				}
				t_List = t_List->m_Next;
			}
		}
		t_Root = t_Root->m_Next;
	}
	return NULL;
}

bool	F_GL_2DEffect::Set_EF_Sub_Effect(FS_2DEffect *p_EF_Info,int p_Effect_ID)
{
	if(p_EF_Info == NULL)
		return false;
	p_EF_Info->m_EF_Index = p_Effect_ID;
	return NULL;
}
