/*
 *  F_GL_RSprite.cpp
 *  Raising Fish
 *
 *  Created by zendiya on 11. 4. 20..
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "F_GL_RSprite.h"
#include "F_Memory.h"
#include "F_IOS_Audio.h"


F_GL_RSprite::F_GL_RSprite()
{
	m_List = NULL;
	m_Select = NULL;
	m_Effect = NULL;
}

F_GL_RSprite::~F_GL_RSprite()
{
	Release_List();
	m_Effect = NULL;
	m_Select = NULL;
}

bool	F_GL_RSprite::Init(F_GL_2DEffect *p_Effect)
{
	m_Effect = p_Effect;
	return true;
}
bool	F_GL_RSprite::Release_List()
{
	if(m_List != NULL)
	{
		F_LList::Delete_All(m_List);
		m_List = NULL;
	}
	return true;
}

FS_RSprite	*F_GL_RSprite::Insert(int p_Index,FS_Sprite *p_Sprite)
{
	if(p_Sprite == NULL)
		return NULL;
	FS_RSprite	*t_Find = Find_Data(p_Index);
	if(t_Find != NULL)
	{
		if(t_Find->m_Sprite == p_Sprite)
		{
			return t_Find;
		}
		return NULL;
	}
	FS_RSprite *t_Data = F_GL_RSprite::Alloc();
	if(t_Data == NULL)
		return NULL;
	t_Data->m_Index = p_Index;
	t_Data->m_Sprite = p_Sprite;
	Set_RS_Pos(t_Data,0.0f,0.0f,0.0f);
	Set_RS_Scale(t_Data,1.0f,1.0f,1.0f);
	Set_RS_Rot(t_Data,0.0f,0.0f,1.0f,0.0f);
	Set_Update(t_Data,1);
	Set_View_Type(t_Data,0);
	Set_RS_Ani(t_Data,0,0,0.0f);
	Set_Scale_F(t_Data,1.0f);
	Set_Button_Return(t_Data,0);
    
    FS_LList *t_Insert = F_LList::New((void *)t_Data,(DWORD)p_Index,F_GL_RSprite::Delete);
	if(t_Insert == NULL)
	{
		F_GL_RSprite::Delete(t_Data);
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
	return t_Data;
}

bool	F_GL_RSprite::Delete(int p_Index)
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

FS_LList	*F_GL_RSprite::Find(int p_Index)
{
	if(m_List == NULL)
		return NULL;
	return F_LList::Find(m_List,(DWORD)p_Index);
}

FS_RSprite	*F_GL_RSprite::Find_Data(int p_Index)
{
	if(m_List == NULL)
		return NULL;
	return (FS_RSprite *)F_LList::Find_Data(m_List,(DWORD)p_Index);
}

bool	F_GL_RSprite::Set_Sub_Sprite(int p_Index,FS_Sprite *p_Sprite)
{
	FS_RSprite *t_Find = Find_Data(p_Index);
	if(t_Find == NULL)
	{
		return false;
	}
	t_Find->m_SubSprite = p_Sprite;
	return true;
}

bool	F_GL_RSprite::Set_Sub_Sprite_Type(int p_Index,int p_Type,int p_X,int p_Y)
{
	FS_RSprite *t_Find = Find_Data(p_Index);
	if(t_Find == NULL)
	{
		return false;
	}
	t_Find->m_Sub_Sprite_Type = p_Type;
	t_Find->m_Sub_Sprite_X = p_X;
	t_Find->m_Sub_Sprite_Y = p_Y;
	return true;
}

bool	F_GL_RSprite::Set_Sub_Sprite_Pos(int p_Index,float p_X,float p_Y,float p_Z,float p_Scale)
{
	FS_RSprite *t_Find = Find_Data(p_Index);
	if(t_Find == NULL)
	{
		return false;
	}
	t_Find->m_Sub_Sprite_Pos.m_X = p_X;
	t_Find->m_Sub_Sprite_Pos.m_Y = p_Y;
	t_Find->m_Sub_Sprite_Pos.m_Z = p_Z;
	t_Find->m_Sub_Sprite_Pos.m_W = p_Scale;
	FS_MATRIX	t_Mat1,t_Mat2;
	FS_MATRIX::Scale(&t_Mat1,p_Scale/t_Find->m_Scale.m_X,p_Scale/t_Find->m_Scale.m_Y,p_Scale/t_Find->m_Scale.m_Z);
	FS_MATRIX::Translate(&t_Mat2,p_X,p_Y,p_Z);
	FS_MATRIX::Mult(&t_Find->m_SubMat,&t_Mat1,&t_Mat2);
	return true;
}

FS_RSprite *F_GL_RSprite::Alloc()
{
	FS_RSprite *t_Return = (FS_RSprite*)F_Alloc(sizeof(FS_RSprite));
	return t_Return;
}

BOOL	F_GL_RSprite::Delete(LPVOID p_RSprite)
{
	if(p_RSprite ==NULL)
		return false;
	FS_RSprite	*t_del = (FS_RSprite *)p_RSprite;
	F_Free(t_del);
	return	true;
}

bool	F_GL_RSprite::Set_View_Type(FS_RSprite *p_Sprite,int p_Type)
{
	if(p_Sprite == NULL)
		return false;
	p_Sprite->m_View_Type = p_Type;
	return true;
}

bool	F_GL_RSprite::Set_RS_Ani(FS_RSprite *p_Sprite,int p_X,int p_Y,float p_Time)
{
	if(p_Sprite == NULL)
		return false;
	p_Sprite->m_Ani_X = p_X;
	p_Sprite->m_Ani_Y = p_Y;
	p_Sprite->m_Ani_Time = p_Time;
	if(p_Sprite->m_Sprite != NULL)
	{
		if(p_Sprite->m_Sprite->m_X_Num <= p_Sprite->m_Ani_X)
		{
			p_Sprite->m_Ani_X = 0;
		}
		if(p_Sprite->m_Sprite->m_Y_Num <= p_Sprite->m_Ani_Y)
		{
			p_Sprite->m_Ani_Y = 0;
		}
	}
	return true;
}

bool	F_GL_RSprite::Set_Update(FS_RSprite *p_Sprite,int p_Type)
{
	if(p_Sprite == NULL)
		return false;
	p_Sprite->m_Update = p_Type;
	return true;
}

bool	F_GL_RSprite::Render_Sprite(FS_RSprite *p_Sprite,float p_DTime)
{
	if(p_Sprite == NULL)
		return false;
	if(p_Sprite->m_View_Type == 0)
		return false;
	if(p_Sprite->m_Sprite == NULL)
		return false;
	FS_Sprite *t_Sprite = p_Sprite->m_Sprite;
	if(t_Sprite->m_Tex == NULL)
		return false;
	if(t_Sprite->m_Vertex == NULL)
		return false;
	if(p_Sprite->m_Wait_Count > 0)
	{
		if(p_Sprite->m_Wait_Count > p_Sprite->m_Wait_Current)
		{
			return false;
		}
	}
	
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
	
	if(p_Sprite->m_Type == 4)
	{
		int	t_Out_Number = p_Sprite->m_Out_Number;
		if(p_Sprite->m_Add_Number > 0)
		{
			p_Sprite->m_Add_Number= p_Sprite->m_Add_Number - 1;
			t_Out_Number = t_Out_Number - p_Sprite->m_Add_Number;
		}
		else if(p_Sprite->m_Add_Number < 0)
		{
			p_Sprite->m_Add_Number= p_Sprite->m_Add_Number + 1;
			t_Out_Number = t_Out_Number + p_Sprite->m_Add_Number;
		}
		
		if(t_Out_Number < 0)
			t_Out_Number = 0;
        int	t_Line = 1;
		int t_Number = t_Out_Number;
		while ((t_Number/10) > 0) {
			t_Number = t_Number/10;
			t_Line++;
		}
		t_Number = 0;
		glPushMatrix();
		glMultMatrixf((GLfloat *)&p_Sprite->m_Mat);
		F_GL_Texture::Set_Tex_RenderSet(t_Sprite->m_Tex);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		
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
			glTranslatef(((float)t_Count)*(t_Sprite->m_Width - 6.0f),0.0f,0.0f);
			glVertexPointer(3,GL_FLOAT,12,&t_VB[(t_Number + p_Sprite->m_Ani_Y*t_Sprite->m_X_Num)*6]);
			glTexCoordPointer(2,GL_FLOAT,8,&t_UVB[(t_Number + p_Sprite->m_Ani_Y*t_Sprite->m_X_Num)*6]);	
			glDrawArrays(GL_TRIANGLES,0,6);
			glPopMatrix();
			t_Count++;
		}
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	else
	{
		glPushMatrix();
		glMultMatrixf((GLfloat *)&p_Sprite->m_Mat);
		F_GL_Texture::Set_Tex_RenderSet(t_Sprite->m_Tex);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		
		glVertexPointer(3,GL_FLOAT,12,&t_VB[(p_Sprite->m_Ani_X + p_Sprite->m_Ani_Y*t_Sprite->m_X_Num)*6]);
		if(p_Sprite->m_Y_Rot == 0)
		{
			glTexCoordPointer(2,GL_FLOAT,8,&t_UVB[(p_Sprite->m_Ani_X + p_Sprite->m_Ani_Y*t_Sprite->m_X_Num)*6]);
		}
		else
		{
			m_Rot_UV[0] = t_UVB[(p_Sprite->m_Ani_X + p_Sprite->m_Ani_Y*t_Sprite->m_X_Num)*6+2];
			m_Rot_UV[1] = t_UVB[(p_Sprite->m_Ani_X + p_Sprite->m_Ani_Y*t_Sprite->m_X_Num)*6+5];
			m_Rot_UV[2] = t_UVB[(p_Sprite->m_Ani_X + p_Sprite->m_Ani_Y*t_Sprite->m_X_Num)*6+0];
			m_Rot_UV[3] = t_UVB[(p_Sprite->m_Ani_X + p_Sprite->m_Ani_Y*t_Sprite->m_X_Num)*6+0];
			m_Rot_UV[4] = t_UVB[(p_Sprite->m_Ani_X + p_Sprite->m_Ani_Y*t_Sprite->m_X_Num)*6+5];
			m_Rot_UV[5] = t_UVB[(p_Sprite->m_Ani_X + p_Sprite->m_Ani_Y*t_Sprite->m_X_Num)*6+1];
			glTexCoordPointer(2,GL_FLOAT,8,m_Rot_UV);
		}	
		glDrawArrays(GL_TRIANGLES,0,6);
	
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	if(p_Sprite->m_SubSprite != NULL)
	{
		switch(p_Sprite->m_Sub_Sprite_Type)
		{
			case 1:
			{
				t_Sprite = p_Sprite->m_SubSprite;
				
				t_Pos = t_Sprite->m_Vertex->Get_Data(0);
				t_Uv = t_Sprite->m_Vertex->Get_Data(1);
				if(t_Pos == NULL)
					break;
				if(t_Uv == NULL)
					break;
				
				t_VB = (FS_XYZ *)t_Pos->Get_Data();
				t_UVB = (FS_XY *)t_Uv->Get_Data();
				if(t_VB == NULL)
					break;
				if(t_UVB == NULL)
					break;

				glPushMatrix();
				glMultMatrixf((GLfloat *)&p_Sprite->m_SubMat);
				F_GL_Texture::Set_Tex_RenderSet(t_Sprite->m_Tex);
				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
				
				glVertexPointer(3,GL_FLOAT,12,&t_VB[(p_Sprite->m_Sub_Sprite_X + p_Sprite->m_Sub_Sprite_Y*t_Sprite->m_X_Num)*6]);
				glTexCoordPointer(2,GL_FLOAT,8,&t_UVB[(p_Sprite->m_Sub_Sprite_X + p_Sprite->m_Sub_Sprite_Y*t_Sprite->m_X_Num)*6]);
				glDrawArrays(GL_TRIANGLES,0,6);
				
				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				glPopMatrix();
				break;
			}
			case 2:
			{
				t_Sprite = p_Sprite->m_SubSprite;
                t_Pos = t_Sprite->m_Vertex->Get_Data(0);
				t_Uv = t_Sprite->m_Vertex->Get_Data(1);
				if(t_Pos == NULL)
					break;
				if(t_Uv == NULL)
					break;
				
				t_VB = (FS_XYZ *)t_Pos->Get_Data();
				t_UVB = (FS_XY *)t_Uv->Get_Data();
				if(t_VB == NULL)
					break;
				if(t_UVB == NULL)
					break;
				glPushMatrix();
				glMultMatrixf((GLfloat *)&p_Sprite->m_SubMat);
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
				break;
			}
		}
	}
	
	glPopMatrix();
    return true;
}

bool	F_GL_RSprite::Update_RS_Time(FS_RSprite *p_Sprite,float p_Time)
{
	if(p_Sprite == NULL)
		return false;
	if(p_Sprite->m_Type==0)
		return true;
	if(p_Sprite->m_Sprite == NULL)
		return false;
	if(p_Sprite->m_Type == 1)
	{
		if(p_Sprite->m_Button_State == 1)
		{
			p_Sprite->m_Ani_Time = 0;
			p_Sprite->m_Ani_Y = 1;
			p_Sprite->m_Ani_X = 0;
			p_Sprite->m_Button_State = 2;
		}
		else if(p_Sprite->m_Button_State == 3)
		{
			p_Sprite->m_Ani_Time = 0;
			p_Sprite->m_Ani_Y = 2;
			p_Sprite->m_Ani_X = 0;
			p_Sprite->m_Button_State = 4;
		}
		else if(p_Sprite->m_Button_State == 5)
		{
			p_Sprite->m_Ani_Time = 0;
			p_Sprite->m_Ani_Y = 1;
			p_Sprite->m_Ani_X = 0;
			p_Sprite->m_Button_State = 6;
		}
		else if(p_Sprite->m_Button_State == 7)
		{
			p_Sprite->m_Ani_Time = 0;
			p_Sprite->m_Ani_Y = 2;
			p_Sprite->m_Ani_X = 0;
			p_Sprite->m_Button_State = 8;
		}
	}
	
	p_Sprite->m_Ani_Time = p_Sprite->m_Ani_Time + p_Time;
	if(p_Sprite->m_Sprite->m_DTime < p_Sprite->m_Ani_Time)
	{
		p_Sprite->m_Ani_Time = 0;
		if(p_Sprite->m_Sprite->m_X_Num > 1)
		{
			p_Sprite->m_Ani_X++;
			if(p_Sprite->m_Sprite->m_X_Num <= p_Sprite->m_Ani_X)
			{
				if(p_Sprite->m_Type == 1)
				{
					if(p_Sprite->m_Button_State == 2)
					{	
						p_Sprite->m_Ani_X = p_Sprite->m_Sprite->m_X_Num - 1;
					}
					else if(p_Sprite->m_Button_State == 4)
					{
						p_Sprite->m_Ani_Y = 0;
						p_Sprite->m_Button_State = 0;
						p_Sprite->m_Ani_X = 0;
					}
					else if(p_Sprite->m_Button_State == 6)
					{	
						p_Sprite->m_Ani_Y = 0;
						p_Sprite->m_Button_State = 0;
						p_Sprite->m_Ani_X = 0;
					}
					else if(p_Sprite->m_Button_State == 8)
					{
						p_Sprite->m_Ani_Y = 0;
						p_Sprite->m_Button_State = 0;
						p_Sprite->m_Ani_X = 0;
					}
					else
					{
						p_Sprite->m_Ani_X = 0;
					}

				}
				else 
				{
					p_Sprite->m_Ani_X = 0;
				}

			}
		}
	}
	return true;
}

bool	F_GL_RSprite::Pre_Render_Sprite(FS_RSprite *p_Sprite,float p_DTime)
{
	if(p_Sprite == NULL)
		return false;
	if(p_Sprite->m_Update == 0)
		return false;
	if(p_Sprite->m_Wait_Count > 0)
	{
		if(p_Sprite->m_Wait_Count > p_Sprite->m_Wait_Current)
		{
			p_Sprite->m_Wait_Current++;
			if(p_Sprite->m_Wait_Count > p_Sprite->m_Wait_Current)
				return false;
		}
	}
	p_Sprite->m_Time = p_Sprite->m_Time + p_DTime;
	switch(p_Sprite->m_Type)
	{
		case 0:
		{
			Calcul_Mat(p_Sprite,2,p_DTime);
			Set_Update(p_Sprite,1);
			break;
		}
		case 1:
		{
			Update_RS_Time(p_Sprite,p_DTime);
			Calcul_Mat(p_Sprite,2,p_DTime);
			Set_Update(p_Sprite,1);
			break;
		}
		case 2:
		{
			Update_RS_Time(p_Sprite,p_DTime);
			Calcul_Mat(p_Sprite,2,p_DTime);
			Set_Update(p_Sprite,1);
			break;
		}
		case 3:
		{
			Update_RS_Time(p_Sprite,p_DTime);
			Calcul_Mat(p_Sprite,2,p_DTime);
			Set_Update(p_Sprite,1);
			break;
		}
		case 4:
		{
			Update_RS_Time(p_Sprite,p_DTime);
			Calcul_Mat(p_Sprite,2,p_DTime);
			Set_Update(p_Sprite,1);
			break;
		}
		default:
		{
			Calcul_Mat(p_Sprite);
			Set_Update(p_Sprite,0);
			break;
		}
	}
	return true;
}

bool	F_GL_RSprite::Render(float p_DTime)
{
	if(m_List == NULL)
		return false;
	FS_LList *t_List = m_List;
	while(t_List != NULL)
	{
		if(t_List->m_Data != NULL)
		{
			Render_Sprite((FS_RSprite *)t_List->m_Data,p_DTime);
		}
		t_List = t_List->m_Next;
	}
	return true;
}

bool	F_GL_RSprite::Pre_Render(float p_DTime)
{
	if(m_List == NULL)
		return false;
	FS_LList *t_List = m_List;
	while(t_List != NULL)
	{
		if(t_List->m_Data != NULL)
		{
			Pre_Render_Sprite((FS_RSprite *)t_List->m_Data,p_DTime);
		}
		t_List = t_List->m_Next;
	}
	return true;
}

bool	F_GL_RSprite::Set_RS_Type(FS_RSprite *p_Sprite,int p_Type)
{
	if(p_Sprite == NULL)
		return false;
	p_Sprite->m_Type = p_Type;
	p_Sprite->m_Rand_int = rand()%100;
	p_Sprite->m_Time = ((float)p_Sprite->m_Rand_int)/10.0f;
	return true;
}
bool	F_GL_RSprite::Set_RS_Pos(FS_RSprite *p_Sprite,float x, float y, float z)
{
	if(p_Sprite == NULL)
		return false;
	p_Sprite->m_Pos.m_X = x;
	p_Sprite->m_Pos.m_Y = y;
	p_Sprite->m_Pos.m_Z = z;
	return true;
}

bool	F_GL_RSprite::Set_RS_Scale(FS_RSprite *p_Sprite,float sx,float sy, float sz)
{
	if(p_Sprite == NULL)
		return false;
	p_Sprite->m_Scale.m_X = sx;
	p_Sprite->m_Scale.m_Y = sy;
	p_Sprite->m_Scale.m_Z = sz;
	return true;
}

bool	F_GL_RSprite::Set_RS_Rot(FS_RSprite *p_Sprite,float dx,float dy,float dz,float degree)
{
	if(p_Sprite == NULL)
		return false;
	p_Sprite->m_Rote.m_X = dx;
	p_Sprite->m_Rote.m_Y = dy;
	p_Sprite->m_Rote.m_Z = dz;
	p_Sprite->m_Rote.m_W = degree;
	return true;
}

bool	F_GL_RSprite::Calcul_Mat(FS_RSprite *p_Sprite,int p_Sub_Type,float p_Time)
{
	if(p_Sprite == NULL)
		return false;
	FS_MATRIX	t_Mat1,t_Mat2,t_Mat3,t_Mat4;
	FS_MATRIX::Scale(&t_Mat1,p_Sprite->m_Scale.m_X*p_Sprite->m_Scale_f,p_Sprite->m_Scale.m_Y*p_Sprite->m_Scale_f,p_Sprite->m_Scale.m_Z*p_Sprite->m_Scale_f);
	FS_MATRIX::Rot(&t_Mat2,p_Sprite->m_Rote.m_X,p_Sprite->m_Rote.m_Y,p_Sprite->m_Rote.m_Z,p_Sprite->m_Rote.m_W);
	FS_MATRIX::Translate(&t_Mat3,p_Sprite->m_Pos.m_X,p_Sprite->m_Pos.m_Y,p_Sprite->m_Pos.m_Z);
	
	switch (p_Sub_Type) 
	{
		case 1:
		{
			break;
		}
		case 2:
		{
			if(p_Sprite->m_Move_Param1 == 7)
			{
				if((p_Sprite->m_Move_Dir1.m_Z > -90.0f)&&(p_Sprite->m_Move_Dir1.m_Z < 90.0f))
				{
					p_Sprite->m_Move_Dir1.m_Z = p_Sprite->m_Move_Dir1.m_Z*0.98f;
					if((p_Sprite->m_Move_Dir1.m_Z > -2.0f)&&(p_Sprite->m_Move_Dir1.m_Z < 2.0f))
					{
						Set_RS_Move1_Param(p_Sprite,0.0f,0.0f,0.0f,0.0f,0);
						if(p_Sprite->m_EF_Index != 0)
						{
							if(m_Effect != NULL)
							{
								FS_2DEffect_Info *t_Out = m_Effect->Out_Effect(p_Sprite->m_EF_Index);
								if(t_Out != NULL)
								{
									m_Effect->Set_EF_Start_Pos(t_Out,
										t_Mat3.m[3][0]+Rand_Float(-30.0f,30.0f),
										t_Mat3.m[3][1]+Rand_Float(-30.0f,30.0f),t_Mat3.m[3][2] + 50.0f);
									m_Effect->Set_EF_Move1_Param(t_Out,0.0f,
										200.0f+Rand_Float(-50.0f,50.0f),0.0f,
										60.0f+Rand_Float(-30.0f,30.0f),9);	
									m_Effect->Set_EF_Move2_Param(t_Out,5.0f,0.0f,0.0f,20.0f,14);
								}
							}
						}
						
					}
				}
				FS_MATRIX::Rot(&t_Mat4,0.0f,0.0f,1.0f,p_Sprite->m_Move_Dir1.m_Z);
				FS_MATRIX::Mult(&t_Mat2,&t_Mat2,&t_Mat4);

			}
			else if((p_Sprite->m_Move_Param1 == 8)||(p_Sprite->m_Move_Param1 == 6))
			{
				FS_XYZ	t_Dir;
				t_Dir.m_X = p_Sprite->m_Move_Dir1.m_X - p_Sprite->m_Pos.m_X;
				t_Dir.m_Y = p_Sprite->m_Move_Dir1.m_Y - p_Sprite->m_Pos.m_Y;
				t_Dir.m_Z = 0.0f;
				float	t_Len = FS_XYZ::Len(t_Dir);
				if(t_Len < 0.001f)
				{
					p_Sprite->m_Pos.m_X = p_Sprite->m_Move_Dir1.m_X;
					p_Sprite->m_Pos.m_Y = p_Sprite->m_Move_Dir1.m_Y;
					if(p_Sprite->m_Move_Param1 == 6)
					{
						p_Sprite->m_Move_Param1 = 0;
					}
					else
					{
						p_Sprite->m_Move_Param1 = 7;
					}
				}
				else
				{
					t_Dir = FS_XYZ::Normal(t_Dir);
                    if(t_Len < (p_Sprite->m_Move_Dir1.m_W*p_Time))
					{
						p_Sprite->m_Pos.m_X = p_Sprite->m_Pos.m_X + t_Dir.m_X*t_Len;
						p_Sprite->m_Pos.m_Y = p_Sprite->m_Pos.m_Y + t_Dir.m_Y*t_Len;
						p_Sprite->m_Move_Param1 = 7;
					}
					else
					{
						p_Sprite->m_Pos.m_X = p_Sprite->m_Pos.m_X + t_Dir.m_X*p_Sprite->m_Move_Dir1.m_W*p_Time;
						p_Sprite->m_Pos.m_Y = p_Sprite->m_Pos.m_Y + t_Dir.m_Y*p_Sprite->m_Move_Dir1.m_W*p_Time;
					}
					
					float t_Degree_X = FS_XY::Degree_X(t_Dir.m_X,t_Dir.m_Y);
					if(t_Degree_X < 0.0f)
					{
						t_Degree_X = t_Degree_X + 180.0f;
					}
					else
					{
						t_Degree_X = t_Degree_X - 180.0f;
					}
					if((t_Degree_X < -90.0f)||(t_Degree_X > 90.0f))
					{
						p_Sprite->m_Y_Rot = 1;
						if(t_Degree_X < -90)
						{
							t_Degree_X = 180 + t_Degree_X;
						}
						else
						{
							t_Degree_X = t_Degree_X - 180;
						}
					}
					else 
					{
						p_Sprite->m_Y_Rot = 0;
					}
					p_Sprite->m_Move_Dir1.m_Z = t_Degree_X;
					FS_MATRIX::Rot(&t_Mat4,0.0f,0.0f,1.0f,p_Sprite->m_Move_Dir1.m_Z);
					FS_MATRIX::Mult(&t_Mat2,&t_Mat2,&t_Mat4);
				}
			}
			else if(p_Sprite->m_Move_Param1 == 9)
			{
				float	t_Move = (p_Sprite->m_Time - ((float)p_Sprite->m_Rand_int)/10.0f);
				float	t_Len = FS_XYZ::Len((FS_XYZ&)p_Sprite->m_Move_Dir1);
				FS_XYZ	t_Dir = FS_XYZ::Normal((FS_XYZ&)p_Sprite->m_Move_Dir1);

				if(t_Len <= t_Move*p_Sprite->m_Move_Dir1.m_W)
				{
					p_Sprite->m_Time = ((float)p_Sprite->m_Rand_int)/10.0f;
					t_Move = 0.0f;
					Set_RS_Wait_Count(p_Sprite,p_Sprite->m_Wait_Count,0);
				}
				
				FS_MATRIX::Translate(&t_Mat4,
							t_Dir.m_X*t_Move*p_Sprite->m_Move_Dir1.m_W,
							t_Dir.m_Y*t_Move*p_Sprite->m_Move_Dir1.m_W,
							t_Dir.m_Z*t_Move*p_Sprite->m_Move_Dir1.m_W);
				FS_MATRIX::Mult(&t_Mat3,&t_Mat3,&t_Mat4);
					
				FS_MATRIX::Rot(&t_Mat4,0.0f,0.0f,1.0f,5.0f*sinf(p_Sprite->m_Time*10.0f));
				FS_MATRIX::Mult(&t_Mat2,&t_Mat2,&t_Mat4);
					
				if(t_Len > 0.0f)
				{
					FS_MATRIX::Scale(&t_Mat4,
							((t_Move*p_Sprite->m_Move_Dir1.m_W)/t_Len)*(1.0f + 0.05f*sinf(p_Sprite->m_Time*10.0f)),
							((t_Move*p_Sprite->m_Move_Dir1.m_W)/t_Len)*(1.0f - 0.05f*sinf(p_Sprite->m_Time*10.0f)),1.0f);
					FS_MATRIX::Mult(&t_Mat1,&t_Mat1,&t_Mat4);
				}
			}
			else if(p_Sprite->m_Move_Param1 == 11)
			{
				float	t_Time = (p_Sprite->m_Time - ((float)p_Sprite->m_Rand_int)/10.0f);
				float	t_Len = FS_XYZ::Len((FS_XYZ&)p_Sprite->m_Move_Dir1);
				float	t_MaxTime = t_Len/p_Sprite->m_Move_Dir1.m_W;
				if(t_Time < t_MaxTime)
				{
					float	t_Move = t_Len*(1.0f - (t_Time - t_MaxTime)*(t_Time - t_MaxTime)/(t_MaxTime*t_MaxTime));
					
					FS_XYZ	t_Dir = FS_XYZ::Normal((FS_XYZ&)p_Sprite->m_Move_Dir1);
					FS_MATRIX::Translate(&t_Mat4,
										 p_Sprite->m_Move_Dir1.m_X - t_Dir.m_X*t_Move,
										 p_Sprite->m_Move_Dir1.m_Y - t_Dir.m_Y*t_Move,
										 p_Sprite->m_Move_Dir1.m_Z - t_Dir.m_Z*t_Move);
					FS_MATRIX::Mult(&t_Mat3,&t_Mat3,&t_Mat4);
				}
				else
				{
					Set_RS_Move1_Param(p_Sprite,0.0f,0.0f,0.0f,0.0f,0);
				}
			}
			else if(p_Sprite->m_Move_Param1 == 12)
			{
				FS_MATRIX::Translate(&t_Mat4,
									 p_Sprite->m_Move_Dir1.m_X,
									 p_Sprite->m_Move_Dir1.m_Y,
									 p_Sprite->m_Move_Dir1.m_Z);
				FS_MATRIX::Mult(&t_Mat1,&t_Mat4,&t_Mat1);
			}
			
			
			if(p_Sprite->m_Move_Param2 == 10)
			{
				FS_MATRIX::Translate(&t_Mat4,
				  p_Sprite->m_Move_Dir2.m_X*p_Sprite->m_Move_Dir2.m_W*sinf(p_Sprite->m_Time + ((float)p_Sprite->m_Rand_int)/50.0f),
				  p_Sprite->m_Move_Dir2.m_Y*p_Sprite->m_Move_Dir2.m_W*sinf(p_Sprite->m_Time + ((float)p_Sprite->m_Rand_int)/50.0f),
				  p_Sprite->m_Move_Dir2.m_Z*p_Sprite->m_Move_Dir2.m_W*sinf(p_Sprite->m_Time + ((float)p_Sprite->m_Rand_int)/50.0f));
				FS_MATRIX::Mult(&t_Mat3,&t_Mat3,&t_Mat4);

				FS_MATRIX::Rot(&t_Mat4,0.0f,0.0f,1.0f,5.0f*sinf(p_Sprite->m_Time + (float)p_Sprite->m_Rand_int));
				FS_MATRIX::Mult(&t_Mat2,&t_Mat2,&t_Mat4);
				
				FS_MATRIX::Scale(&t_Mat4,1.0f+0.05f*sinf(p_Sprite->m_Time + (float)p_Sprite->m_Rand_int),
								 1.0f-0.05f*sinf(p_Sprite->m_Time + (float)p_Sprite->m_Rand_int),1.0f);
				FS_MATRIX::Mult(&t_Mat1,&t_Mat1,&t_Mat4);
			}
			else if(p_Sprite->m_Move_Param2 == 11)
			{
				FS_MATRIX::Rot(&t_Mat4,0.0f,0.0f,1.0f,5.0f*sinf(p_Sprite->m_Time + (float)p_Sprite->m_Rand_int));
				FS_MATRIX::Mult(&t_Mat2,&t_Mat2,&t_Mat4);
				
				FS_MATRIX::Scale(&t_Mat4,1.0f+0.05f*sinf(p_Sprite->m_Time + (float)p_Sprite->m_Rand_int),
								 1.0f-0.05f*sinf(p_Sprite->m_Time + (float)p_Sprite->m_Rand_int),1.0f);
				FS_MATRIX::Mult(&t_Mat1,&t_Mat1,&t_Mat4);
			}
			else if(p_Sprite->m_Move_Param2 == 14)
			{
				if(p_Sprite->m_Move_Dir2.m_W >= 20.0f)
				{
					p_Sprite->m_Move_Dir2.m_Z = (((float)(rand()%100))/100.0f)*p_Sprite->m_Move_Dir2.m_X;
					if(p_Sprite->m_Move_Dir2.m_Y > 0.0f)
					{
						p_Sprite->m_Move_Dir2.m_Z = -p_Sprite->m_Move_Dir2.m_Z;
					}
					p_Sprite->m_Move_Dir2.m_Z = (p_Sprite->m_Move_Dir2.m_Z - p_Sprite->m_Move_Dir2.m_Y)/20.0f;
					p_Sprite->m_Move_Dir2.m_W = 0.0f;
				}
				p_Sprite->m_Move_Dir2.m_W = p_Sprite->m_Move_Dir2.m_W + 1.0f;
				p_Sprite->m_Move_Dir2.m_Y = p_Sprite->m_Move_Dir2.m_Y + p_Sprite->m_Move_Dir2.m_Z;
				
				FS_MATRIX::Translate(&t_Mat4,p_Sprite->m_Move_Dir2.m_Y,0.0f,0.0f);
				FS_MATRIX::Mult(&t_Mat3,&t_Mat3,&t_Mat4);
			}
			
			if(p_Sprite->m_Move_Param3 == 30)
			{
				if(p_Sprite->m_Move_Dir3.m_W > 0.0f)
				{
					p_Sprite->m_Move_Dir3.m_W = p_Sprite->m_Move_Dir3.m_W - 1.0f;
					p_Sprite->m_Move_Dir3.m_Z = p_Sprite->m_Move_Dir3.m_Z + 1.0f;
					if(p_Sprite->m_Move_Dir3.m_W < 1.0f)
					{
						p_Sprite->m_View_Type = 0;
					}
					FS_MATRIX::Translate(&t_Mat4,p_Sprite->m_Move_Dir3.m_X*p_Sprite->m_Move_Dir3.m_Z,p_Sprite->m_Move_Dir3.m_Y*p_Sprite->m_Move_Dir3.m_Z,0.0f);
					FS_MATRIX::Mult(&t_Mat3,&t_Mat3,&t_Mat4);
				}
			}
			else if(p_Sprite->m_Move_Param3 == 31)
			{
				if(p_Sprite->m_Move_Dir3.m_W > 0.0f)
				{
					p_Sprite->m_Move_Dir3.m_W = p_Sprite->m_Move_Dir3.m_W - 1.0f;
					p_Sprite->m_Move_Dir3.m_Z = p_Sprite->m_Move_Dir3.m_Z + 1.0f;
					if(p_Sprite->m_Move_Dir3.m_W < 1.0f)
					{
						p_Sprite->m_View_Type = 0;
					}
					else 
					{
						FS_MATRIX::Translate(&t_Mat4,p_Sprite->m_Move_Dir3.m_X*p_Sprite->m_Move_Dir3.m_Z,p_Sprite->m_Move_Dir3.m_Y*p_Sprite->m_Move_Dir3.m_Z,0.0f);
						FS_MATRIX::Mult(&t_Mat3,&t_Mat3,&t_Mat4);
						
						float t_Degree_X = FS_XY::Degree_X(p_Sprite->m_Move_Dir3.m_X,p_Sprite->m_Move_Dir3.m_Y);
						if(t_Degree_X < 0.0f)
						{
							t_Degree_X = t_Degree_X + 180.0f;
						}
						else
						{
							t_Degree_X = t_Degree_X - 180.0f;
						}
						if((t_Degree_X < -90.0f)||(t_Degree_X > 90.0f))
						{
							p_Sprite->m_Y_Rot = 1;
							if(t_Degree_X < -90)
							{
								t_Degree_X = 180 + t_Degree_X;
							}
							else
							{
								t_Degree_X = t_Degree_X - 180;
							}
						}
						else 
						{
							p_Sprite->m_Y_Rot = 0;
						}

						FS_MATRIX::Rot(&t_Mat4,0.0f,0.0f,1.0f,t_Degree_X);
						FS_MATRIX::Mult(&t_Mat2,&t_Mat2,&t_Mat4);
						
						if(p_Sprite->m_EF_Index != 0)
						{
							if(p_Sprite->m_Move_Dir3.m_Z < 10.0f)
							{
								if(Rand_Int(2)==1)
								{	
									if(m_Effect != NULL)
									{
										FS_2DEffect_Info *t_Out = m_Effect->Out_Effect(p_Sprite->m_EF_Index);
										if(t_Out != NULL)
										{
											m_Effect->Set_EF_Start_Pos(t_Out,
														t_Mat3.m[3][0]+Rand_Float(-30.0f,30.0f),
														t_Mat3.m[3][1]+Rand_Float(-30.0f,30.0f),t_Mat3.m[3][2] + 50.0f);
											m_Effect->Set_EF_Move1_Param(t_Out,0.0f,
														200.0f+Rand_Float(-50.0f,50.0f),0.0f,
														60.0f+Rand_Float(-30.0f,30.0f),9);	
											m_Effect->Set_EF_Move2_Param(t_Out,5.0f,0.0f,0.0f,20.0f,14);
										}
									}
								}
							}
						}
					}
				}
			}
			break;
		}
		default:
			break;
	}
	if(p_Sprite->m_Type == 1)
	{
		if(p_Sprite->m_Sprite != NULL)
		{
			p_Sprite->m_Button_Rect.m_X = p_Sprite->m_Sprite->m_Rect.m_X*t_Mat1.m[0][0] + t_Mat3.m[3][0];
			p_Sprite->m_Button_Rect.m_Y = p_Sprite->m_Sprite->m_Rect.m_Y*t_Mat1.m[1][1] + t_Mat3.m[3][1];
			p_Sprite->m_Button_Rect.m_Z = p_Sprite->m_Sprite->m_Rect.m_Z*t_Mat1.m[0][0];
			p_Sprite->m_Button_Rect.m_W = p_Sprite->m_Sprite->m_Rect.m_W*t_Mat1.m[1][1];
		}
	}
	
	if(p_Sprite->m_SubSprite != NULL)
	{
		if(p_Sprite->m_Sub_Sprite_Type == 1)
		{
			FS_MATRIX	t_Mat11,t_Mat22;
			FS_MATRIX::Scale(&t_Mat11,p_Sprite->m_Sub_Sprite_Pos.m_W/t_Mat1.m[0][0],
							 p_Sprite->m_Sub_Sprite_Pos.m_W/t_Mat1.m[1][1],
							 p_Sprite->m_Sub_Sprite_Pos.m_W);
			FS_MATRIX::Translate(&t_Mat22,p_Sprite->m_Sub_Sprite_Pos.m_X/t_Mat1.m[0][0],p_Sprite->m_Sub_Sprite_Pos.m_Y/t_Mat1.m[1][1],p_Sprite->m_Sub_Sprite_Pos.m_Z);
			FS_MATRIX::Mult(&p_Sprite->m_SubMat,&t_Mat11,&t_Mat22);
		}
	}
	
	FS_MATRIX::Mult(&t_Mat1,&t_Mat1,&t_Mat2);
	FS_MATRIX::Mult(&p_Sprite->m_Mat,&t_Mat1,&t_Mat3);
	return true;
}

bool	F_GL_RSprite::Set_RS_Move1_Param(FS_RSprite *p_Sprite,float dx,float dy,float dz,float dMove,int p_Parm)
{
	if(p_Sprite == NULL)
		return false;
	p_Sprite->m_Move_Dir1.m_X = dx; 
	p_Sprite->m_Move_Dir1.m_Y = dy; 
	p_Sprite->m_Move_Dir1.m_Z = dz; 
	p_Sprite->m_Move_Dir1.m_W = dMove;
	p_Sprite->m_Move_Param1 = p_Parm;
	return true;
}

bool	F_GL_RSprite::Set_RS_Move2_Param(FS_RSprite *p_Sprite,float dx,float dy,float dz,float dMove,int p_Parm)
{
	if(p_Sprite == NULL)
		return false;
	p_Sprite->m_Move_Dir2.m_X = dx; 
	p_Sprite->m_Move_Dir2.m_Y = dy; 
	p_Sprite->m_Move_Dir2.m_Z = dz; 
	p_Sprite->m_Move_Dir2.m_W = dMove;
	p_Sprite->m_Move_Param2 = p_Parm;
	return true;
}

bool	F_GL_RSprite::Set_RS_Move3_Param(FS_RSprite *p_Sprite,float dx,float dy,float dz,float dMove,int p_Parm)
{
	if(p_Sprite == NULL)
		return false;
	p_Sprite->m_Move_Dir3.m_X = dx; 
	p_Sprite->m_Move_Dir3.m_Y = dy; 
	p_Sprite->m_Move_Dir3.m_Z = dz; 
	p_Sprite->m_Move_Dir3.m_W = dMove;
	p_Sprite->m_Move_Param3 = p_Parm;
	return true;
}

bool	F_GL_RSprite::Set_RS_Effect_ID(FS_RSprite *p_Sprite,int p_Effect_ID)
{
	if(p_Sprite == NULL)
		return false;
	p_Sprite->m_EF_Index = p_Effect_ID;
	return true;
}

bool	F_GL_RSprite::Set_RS_Wait_Count(FS_RSprite *p_Sprite,int p_Wait_C,int p_Rand_Max)
{
	if(p_Sprite == NULL)
		return false;
	if(p_Rand_Max > 1)
	{
		p_Sprite->m_Wait_Count = p_Wait_C+rand()%p_Rand_Max;
	}
	else 
	{
		p_Sprite->m_Wait_Count = p_Wait_C;
	}

	p_Sprite->m_Wait_Current = 0;
	return true;
}

bool	F_GL_RSprite::Mouse_Down(FS_XYZ *p_Pos,FS_XYZ *p_Dir)
{
	m_Select = NULL;
	if(m_List == NULL)
		return false;
	FS_LList *t_List = m_List;
	FS_RSprite *t_Sprite = NULL;
	FS_RSprite *t_Select = NULL;
	while(t_List != NULL)
	{
		t_Sprite = (FS_RSprite *)t_List->m_Data;
		if(t_Sprite != NULL)
		{
			if(t_Sprite->m_View_Type != 0)
			{
				if((t_Sprite->m_Type == 1)&&(t_Sprite->m_Button_TF == 1))
				{
					if((t_Sprite->m_Button_Rect.m_X < p_Pos->m_X)&&((t_Sprite->m_Button_Rect.m_X + t_Sprite->m_Button_Rect.m_Z) > p_Pos->m_X))
					{
						if((t_Sprite->m_Button_Rect.m_Y > p_Pos->m_Y)&&((t_Sprite->m_Button_Rect.m_Y - t_Sprite->m_Button_Rect.m_W) < p_Pos->m_Y))
						{
							if(t_Select == NULL)
							{
								t_Select = t_Sprite;
							}
							else 
							{
								if(t_Sprite->m_Pos.m_Z > t_Select->m_Pos.m_Z)
								{
									t_Select = t_Sprite;
								}
							}
						}
					}
				}
			}
		}
		t_List = t_List->m_Next;
	}
	if(t_Select != NULL)
	{
		m_Select = t_Select;
		m_Select->m_Button_State = 1;
		return true;
	}
	return false;
}

int	F_GL_RSprite::Mouse_Up(FS_XYZ *p_Pos,FS_XYZ *p_Dir)
{
	if(m_Select == NULL)
		return 0;
	if((m_Select->m_Button_Rect.m_X < p_Pos->m_X)&&((m_Select->m_Button_Rect.m_X + m_Select->m_Button_Rect.m_Z) > p_Pos->m_X))
	{
		if((m_Select->m_Button_Rect.m_Y > p_Pos->m_Y)&&((m_Select->m_Button_Rect.m_Y - m_Select->m_Button_Rect.m_W) < p_Pos->m_Y))
		{
			m_Select->m_Button_State = 3;
			int Return_I = m_Select->m_Button_Return;
			m_Select = NULL;
			F_IO_Wave::Play_Sound(1);
			return Return_I;
		}
	}
	m_Select->m_Button_State = 3;
	m_Select = NULL;
	return 0;
}

bool	F_GL_RSprite::Mouse_Move(FS_XYZ *p_Pos,FS_XYZ *p_Dir)
{
	if(m_Select == NULL)
		return false;
	if((m_Select->m_Button_Rect.m_X < p_Pos->m_X)&&((m_Select->m_Button_Rect.m_X + m_Select->m_Button_Rect.m_Z) > p_Pos->m_X))
	{
		if((m_Select->m_Button_Rect.m_Y > p_Pos->m_Y)&&((m_Select->m_Button_Rect.m_Y - m_Select->m_Button_Rect.m_W) < p_Pos->m_Y))
		{
			return true;
		}
	}
	m_Select->m_Button_State = 3;
	m_Select = NULL;
	return true;
}

bool	F_GL_RSprite::Set_Scale_F(FS_RSprite *p_Sprite,float p_ScaleF)
{
	if(p_Sprite == NULL)
		return false;
	p_Sprite->m_Scale_f = p_ScaleF;
	return true;
}

bool	F_GL_RSprite::Set_Button_Return(FS_RSprite *p_Sprite,int p_Return)
{
	if(p_Sprite == NULL)
		return false;
	p_Sprite->m_Button_Return = p_Return;
	return true;
}

bool	F_GL_RSprite::Set_Button_OnOff(FS_RSprite *p_Sprite,int p_OnOff)
{
	if(p_Sprite == NULL)
		return false;
	p_Sprite->m_Button_TF = p_OnOff;
	return true;
}

bool	F_GL_RSprite::Set_RS_Z_Rot(FS_RSprite *p_Sprite,int p_ZRot)
{
	if(p_Sprite == NULL)
		return false;
	p_Sprite->m_Y_Rot = p_ZRot;
	return	true;
}

bool	F_GL_RSprite::Set_Out_Number(FS_RSprite *p_Sprite,int p_Number,int p_Add_Number)
{
	if(p_Sprite == NULL)
		return false;
	p_Sprite->m_Out_Number = p_Number;
	p_Sprite->m_Add_Number = p_Add_Number;
	return true;
}