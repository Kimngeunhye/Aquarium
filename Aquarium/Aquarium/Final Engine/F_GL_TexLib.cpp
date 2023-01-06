/*
 *  F_GL_TexLib.cpp
 *  
 *
 *  Created by forthen on 11. 4. 18..
 *  Copyright 2011 forthen. All rights reserved.
 *
 */

#include "F_GL_TexLib.h"

F_GL_TexLib::F_GL_TexLib()
{
	m_List = NULL;
	m_Type = 0;
}

F_GL_TexLib::~F_GL_TexLib()
{
	if(m_List != NULL)
	{
		F_LList::Delete_All(m_List);
		m_List == NULL;
	}
}

//	초기 설정
bool	F_GL_TexLib::Init(int p_Type)
{
	if(m_List != NULL)
		return false;
	m_Type = p_Type;
	return true;
}

//	이미지 리스트 추가
bool	F_GL_TexLib::Insert_Tex(int p_Index,const string& p_Name)
{
	//	기존 인덱스 사용 확인
	if(Find_List(p_Index) != NULL)
		return false;
	//	텍스처 클래스 생성
	F_GL_Texture *t_Tex = new F_GL_Texture;
	if (t_Tex == NULL)
	{
		return false;
	}
	//	초기화
	t_Tex->Init(p_Name,m_Type);
	//	이미지 로딩
	if(!t_Tex->Create_Texture(1))
	{
		F_GL_Texture::Delete((LPVOID)t_Tex);
		return	false;
	}
	
	//	리스트 생성
	FS_LList *t_List = F_LList::New((LPVOID)t_Tex,(DWORD)p_Index,F_GL_Texture::Delete);
	if(t_List == NULL)
	{
		F_GL_Texture::Delete((LPVOID)t_Tex);
		return	false;
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
	return true;
}

//	이미지 리스트 추가
bool	F_GL_TexLib::Insert_Tex_String(int p_Index,char *p_String,int p_R,int p_G,int p_B,int p_A)
{	//	기존 인덱스 사용 확인
	if(Find_List(p_Index) != NULL)
		return false;
	//	텍스처 클래스 생성
	F_GL_Texture *t_Tex = new F_GL_Texture;
	if (t_Tex == NULL)
	{
		return false;
	}
	//	이미지 로딩
	if(!t_Tex->Update_String(p_String,p_R, p_G, p_B, p_A))
	{
		F_GL_Texture::Delete((LPVOID)t_Tex);
		return	false;
	}
	
	//	리스트 생성
	FS_LList *t_List = F_LList::New((LPVOID)t_Tex,(DWORD)p_Index,F_GL_Texture::Delete);
	if(t_List == NULL)
	{
		F_GL_Texture::Delete((LPVOID)t_Tex);
		return	false;
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
	return true;
}

// 문자열 이미지의 상태 설정
bool	F_GL_TexLib::Update_Tex_String(int p_Index,char *p_String,int p_R,int p_G,int p_B,int p_A)
{
	if(p_String == NULL)
		return false;
	F_GL_Texture *t_Tex = Find_Tex(p_Index);
	if(t_Tex == NULL)
		return false;
	// 문자열 변경
	return t_Tex->Update_String(p_String,p_R, p_G, p_B, p_A);
}

//	이미지 리스트 삭제
bool	F_GL_TexLib::Delete_Tex(int p_Index)
{	
	if(m_List == NULL)
		return false;
	FS_LList	*t_Del = Find_List(p_Index);
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

//	이미지 리스트 찾기
FS_LList	*F_GL_TexLib::Find_List(int p_Index)
{
	if(m_List == NULL)
		return NULL;
	return F_LList::Find(m_List,(DWORD)p_Index);
}

//	이미지 클래스 찾기
F_GL_Texture *F_GL_TexLib::Find_Tex(int p_Index)
{
	if(m_List == NULL)
		return NULL;
	return (F_GL_Texture *)F_LList::Find_Data(m_List,(DWORD)p_Index);
}
