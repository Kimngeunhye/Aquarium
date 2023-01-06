/*
 *  F_GL_Sprite.cpp
 *  
 *
 *  Created by forthen on 11. 4. 18..
 *  Copyright 2011 forthen. All rights reserved.
 *
 */

#include "F_GL_Sprite.h"
#include "F_Memory.h"

F_GL_Sprite::F_GL_Sprite()
{
	m_List = NULL;
	m_Lib = NULL;
}

F_GL_Sprite::~F_GL_Sprite()
{
	if(m_List != NULL)
	{
		F_LList::Delete_All(m_List);
		m_List = NULL;
	}
	m_Lib = NULL;
}

//	스프라이트 정점 생성 함수
FS_Sprite *F_GL_Sprite::New_Sprite()
{
	FS_Sprite *t_Sprite = (FS_Sprite *)F_Alloc(sizeof(FS_Sprite));
	return t_Sprite;
}

//	스프라이트  삭제 함수
BOOL	F_GL_Sprite::Delete(LPVOID p_Sprite)
{
	if(p_Sprite == NULL)
		return true;
	FS_Sprite *t_Del = (FS_Sprite *)p_Sprite;
	if(t_Del->m_Vertex != NULL)
	{
		F_3D_Vertex::Delete(t_Del->m_Vertex);
		t_Del->m_Vertex = NULL;
	}
	F_Free(p_Sprite);
	return true;
}

//	초기 설정
bool	F_GL_Sprite::Init(F_GL_TexLib *p_Lib)
{
	m_Lib = p_Lib;
	return true;
}

//	스프라이트 데이터 추가
FS_Sprite	*F_GL_Sprite::Insert(int p_Index,int p_Tex_Index)
{
	if(m_Lib == NULL)
		return NULL;
	//	기존 인덱스 사용 확인
	if(Find(p_Index) != NULL)
		return NULL;
	//	텍스처 클래스 생성
	F_GL_Texture *t_Tex = m_Lib->Find_Tex(p_Tex_Index);
	if (t_Tex == NULL)
	{
		return NULL;
	}
	//	스프라이트 데이터 생성
	FS_Sprite	*t_Sprite = (FS_Sprite *)F_Alloc(sizeof(FS_Sprite));
	if(t_Sprite == NULL)
		return NULL;
	//	기본 데이터 설정
	t_Sprite->m_Index = p_Index;
	t_Sprite->m_Tex_Index = p_Tex_Index;
	t_Sprite->m_Tex = t_Tex;
	t_Sprite->m_Vertex = NULL;
	
	//	리스트 생성
	FS_LList *t_List = F_LList::New((LPVOID)t_Sprite,(DWORD)p_Index,F_GL_Sprite::Delete);
	if(t_List == NULL)
	{
		F_Free(t_Sprite);
		t_Sprite = NULL;
		return	NULL;
	}
	//	리스트 추가
	if(m_List == NULL)
	{
		m_List = t_List;
	}
	else 
	{
		F_LList::Insert(m_List,t_List);
	}
	return t_Sprite;
}

//	스프라이트 데이터 삭제
bool	F_GL_Sprite::Delete(int p_Index)
{
	if(m_Lib == NULL)
		return false;
	if(m_List == NULL)
		return false;
	FS_LList	*t_Del = Find(p_Index);
	if(t_Del == NULL)
		return false;
	//	선두 노드인 경우만 예외 처리
	if(t_Del == m_List)
	{
		m_List = t_Del->m_Next;
	}
	F_LList::Delete(t_Del);
	return true;
}

//	스프라이트 데이터 얻기
FS_LList	*F_GL_Sprite::Find(int p_Index)
{
	if(m_Lib == NULL)
		return NULL;
	if(m_List == NULL)
		return NULL;
	return F_LList::Find(m_List,(DWORD)p_Index);
}

FS_Sprite	*F_GL_Sprite::Find_Data(int p_Index)
{
	if(m_Lib == NULL)
		return NULL;
	if(m_List == NULL)
		return NULL;
	return (FS_Sprite *)F_LList::Find_Data(m_List,(DWORD)p_Index);
}
//	지정 스프라이트의 가로 세로 설정
bool	F_GL_Sprite::Set_WH(FS_Sprite *p_Sprite,int p_W,int p_H)
{
	if(p_Sprite == NULL)
		return false;
	p_Sprite->m_Width = p_W;
	p_Sprite->m_Height = p_H;
	return	true;
}

//	지정 스프라이트의 UV 크기 및 그리드 XY 개수 설정
bool	F_GL_Sprite::Set_UV_GridXY(FS_Sprite *p_Sprite,float p_U,float p_V,int p_Nx,int p_Ny,int p_All_Num)
{
	if(p_Sprite == NULL)
		return false;
	p_Sprite->m_Grid_U = p_U;	// 텍스처 U 크기
	p_Sprite->m_Grid_V = p_V;	// 텍스처 V 크기
	p_Sprite->m_X_Num = p_Nx;	//	X 개수
	p_Sprite->m_Y_Num = p_Ny;	//	Y 개수
	p_Sprite->m_All_Num = p_All_Num;
	return true;
}

//	지정 스프라이트의 시간 타입 설정
bool	F_GL_Sprite::Set_DTime(FS_Sprite *p_Sprite,float p_DTime)
{
	if(p_Sprite == NULL)
		return false;
	p_Sprite->m_DTime = p_DTime;
	return true;
}

//	지정 스프라이트의 정보 설정
bool	F_GL_Sprite::Set_Vertex(FS_Sprite *p_Sprite)
{
	if(p_Sprite == NULL)
		return false;
	if(p_Sprite->m_Vertex != NULL)
	{
		F_3D_Vertex::Delete(p_Sprite->m_Vertex);
		p_Sprite->m_Vertex = NULL;
	}
	//	생성
	p_Sprite->m_Vertex = F_3D_Vertex::New();
	if(p_Sprite->m_Vertex == NULL)
		return false;
	//	사각형 개수 만큼 정점 생성 6*사각형 개수
	F_3D_Data *t_Pos = p_Sprite->m_Vertex->Insert(F_3D_Data::FD_FVF_XYZ,6*p_Sprite->m_X_Num*p_Sprite->m_Y_Num);
	if(t_Pos == NULL)
	{
		F_3D_Vertex::Delete(p_Sprite->m_Vertex);
		p_Sprite->m_Vertex = NULL;
		return false;
	}
	//	UV 6*사각형 개수
	F_3D_Data *t_UV = p_Sprite->m_Vertex->Insert(F_3D_Data::FD_FVF_TEX1,6*p_Sprite->m_X_Num*p_Sprite->m_Y_Num);
	if(t_UV == NULL)
	{
		F_3D_Vertex::Delete(p_Sprite->m_Vertex);
		p_Sprite->m_Vertex = NULL;
		return false;
	}
	// 정점 설정
	FS_XYZ *t_XYZ = (FS_XYZ *)t_Pos->Get_Data();
	if(t_XYZ != NULL)
	{
		for(int i = 0; i < (p_Sprite->m_X_Num*p_Sprite->m_Y_Num); i++)
		{
			t_XYZ[i*6+0].m_X =-((float)p_Sprite->m_Width)/2.0f;	t_XYZ[i*6+0].m_Y = ((float)p_Sprite->m_Height)/2.0f;	t_XYZ[i*6+0].m_Z = 0.0f;
			t_XYZ[i*6+1].m_X =-((float)p_Sprite->m_Width)/2.0f;	t_XYZ[i*6+1].m_Y =-((float)p_Sprite->m_Height)/2.0f;	t_XYZ[i*6+1].m_Z = 0.0f;
			t_XYZ[i*6+2].m_X = ((float)p_Sprite->m_Width)/2.0f;	t_XYZ[i*6+2].m_Y = ((float)p_Sprite->m_Height)/2.0f;	t_XYZ[i*6+2].m_Z = 0.0f;
			t_XYZ[i*6+3].m_X = ((float)p_Sprite->m_Width)/2.0f;	t_XYZ[i*6+3].m_Y = ((float)p_Sprite->m_Height)/2.0f;	t_XYZ[i*6+3].m_Z = 0.0f;
			t_XYZ[i*6+4].m_X =-((float)p_Sprite->m_Width)/2.0f;	t_XYZ[i*6+4].m_Y =-((float)p_Sprite->m_Height)/2.0f;	t_XYZ[i*6+4].m_Z = 0.0f;
			t_XYZ[i*6+5].m_X = ((float)p_Sprite->m_Width)/2.0f;	t_XYZ[i*6+5].m_Y =-((float)p_Sprite->m_Height)/2.0f;	t_XYZ[i*6+5].m_Z = 0.0f;
		}
	}
	//	UV 설정
	FS_XY *t_XY = (FS_XY *)t_UV->Get_Data();
	if(t_XY != NULL)
	{
		for(int y = 0; y < p_Sprite->m_Y_Num; y++)
		{
			for(int x = 0; x < p_Sprite->m_X_Num; x++)
			{
				t_XY[(x+y*p_Sprite->m_X_Num)*6+0].m_X = x*p_Sprite->m_Grid_U;
				t_XY[(x+y*p_Sprite->m_X_Num)*6+0].m_Y = y*p_Sprite->m_Grid_V;
				
				t_XY[(x+y*p_Sprite->m_X_Num)*6+1].m_X = x*p_Sprite->m_Grid_U; 
				t_XY[(x+y*p_Sprite->m_X_Num)*6+1].m_Y = (1+y)*p_Sprite->m_Grid_V;
				
				t_XY[(x+y*p_Sprite->m_X_Num)*6+2].m_X = (1+x)*p_Sprite->m_Grid_U; 
				t_XY[(x+y*p_Sprite->m_X_Num)*6+2].m_Y = y*p_Sprite->m_Grid_V;
				
				t_XY[(x+y*p_Sprite->m_X_Num)*6+3].m_X = (1+x)*p_Sprite->m_Grid_U; 
				t_XY[(x+y*p_Sprite->m_X_Num)*6+3].m_Y = y*p_Sprite->m_Grid_V;
				
				t_XY[(x+y*p_Sprite->m_X_Num)*6+4].m_X = x*p_Sprite->m_Grid_U; 
				t_XY[(x+y*p_Sprite->m_X_Num)*6+4].m_Y = (1+y)*p_Sprite->m_Grid_V;
				
				t_XY[(x+y*p_Sprite->m_X_Num)*6+5].m_X = (1+x)*p_Sprite->m_Grid_U; 
				t_XY[(x+y*p_Sprite->m_X_Num)*6+5].m_Y = (1+y)*p_Sprite->m_Grid_V;
			}
		}
	}
	return true;
}

//	지정 스프라이트의 가로 세로 설정
bool	F_GL_Sprite::Set_Rect(FS_Sprite *p_Sprite,float p_Sx,float p_Sy,float p_W,float p_H)
{
	if(p_Sprite == NULL)
		return false;
	p_Sprite->m_Rect.m_X = p_Sx;
	p_Sprite->m_Rect.m_Y = p_Sy;
	p_Sprite->m_Rect.m_Z = p_W;
	p_Sprite->m_Rect.m_W = p_H;
	return true;
}
