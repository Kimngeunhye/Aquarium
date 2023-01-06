/*
 *  F_GL_Texture.h
 * 
 *
 *  Created by forthen on 11. 4. 18..
 *  Copyright 2011 forthen. All rights reserved.
 *
 */
#pragma once
#include "F_IOS_File.h"
#include "F_LList.h"
#include "F_GLES_Define.h"

// GL 기반 텍스처 클래스 생성
class	F_GL_Texture
{
	//	클래스 생성 ,삭제
public:
	F_GL_Texture();
	~F_GL_Texture();
	
	//	클래스 내부 변수
public:
	//	원본 이미지 이름
	string	m_File_Name;
	char	m_String[256];
	//	데이터 타입 (0:내부 원본 이미지 보관, 1:원본 이미지 보관안함)
	int		m_Type;
	//	원본 이미지 데이터
	F_Img_Data *m_Img;
	
	//	텍스처 포인터
	GLuint	m_Texture;
	//	텍스처 객체 수 (보통 1을 사용)
	GLsizei m_Number;
	//	텍스처 정보 구조체 (추가 필요)
	
	//	클래스 내부 함수
public:
	//	초기화 (이미지 파일 이름 지정, 원본 보관 설정(0 보관, 1미보관))
	bool	Init(const string& name,int p_Type = 0);
	//	문자열 이미지 (내부 버퍼 보관 안함)
	bool	Init(char *p_String);
	//	텍스처 생성 (내부 설정 이미지 파일로 설정)
	bool	Create_Texture(GLsizei p_Num = 1);
	//	텍스처 생성 (전달된 이미지 정보 사용)
	bool	Create_Texture(F_Img_Data *p_Png,GLsizei p_Num = 1);
	//	텍스처 포인터 얻기
	GLuint	Get_Texture();
	
	//	문자열 내용 변경
	bool	Update_String(char *p_String,int p_R,int p_G,int p_B,int p_A);
	
	//	클래스 전역 함수
public:
	//	텍스처 클래스 삭제 함수
	static BOOL Delete(LPVOID p_Texture);
	
	//	텍스처 렌더링 적용 시작
	static bool	Set_Tex_RenderSet(F_GL_Texture *p_Texture);
	//	텍스처 렌더링 적용 종료
	static bool	End_Tex_RenderSet();	
};