/*
 *  F_GL_TexLib.h
 *  
 *
 *  Created by forthen on 11. 4. 18..
 *  Copyright 2011 forthen. All rights reserved.
 *
 */
#pragma once
#include "F_GL_Texture.h"

//	텍스처 이미지 라이브러리 클래스
class	F_GL_TexLib
{
	//	클래스 생성 삭제
public:
	F_GL_TexLib();
	~F_GL_TexLib();
	
	//	클래스 내부 변수
public:
	//	리스트 관리 클래스
	FS_LList	*m_List;
	//	내부 원본 데이터 보관 옵션(0 보관,1 보관 안함)
	int			m_Type;
	
	//	클래스 내부 함수
public:
	//	초기 설정
	bool	Init(int p_Type);
	//	이미지 리스트 추가
	bool	Insert_Tex(int p_Index,const string& p_Name);
	//	이미지 리스트 추가
	bool	Insert_Tex_String(int p_Index,char *p_String,int p_R = 0,int p_G = 0,int p_B = 0,int p_A = 255);
	//	이미지 리스트 삭제
	bool	Delete_Tex(int p_Index);
	//	이미지 리스트 찾기
	FS_LList	*Find_List(int p_Index);
	//	이미지 클래스 찾기
	F_GL_Texture *Find_Tex(int p_Index);
	
	// 문자열 이미지의 상태 설정
	bool	Update_Tex_String(int p_Index,char *p_String,int p_R = 0,int p_G = 0,int p_B = 0,int p_A = 255);
};