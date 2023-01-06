/*
 *  F_GL_Sprite.h
 * 
 *
 *  Created by forthen on 11. 4. 18..
 *  Copyright 2011 forthen. All rights reserved.
 *
 */
#pragma once
#include "F_GL_TexLib.h"
#include "F_3D_Vertex.h"

// 스프라이트 구조체
struct FS_Sprite
{
	int m_Index;		// 일렬 번호
	int m_Tex_Index;	// 이미지 인덱스
	int	m_Width;		//	가로
	int m_Height;		//	세로
	float	m_Grid_U;	// 텍스처 U 크기
	float	m_Grid_V;	// 텍스처 V 크기
	int		m_X_Num;	//	X 개수
	int		m_Y_Num;	//	Y 개수
	int		m_All_Num;	//	전체 개수
	float	m_DTime;	//	이미지 지연시간
	// 충돌 박스 및 버튼 영역으로 사용
	FS_XYZW m_Rect;		// 유효 영역 (X,Y) 중앙에서 사각형 좌측 상단 좌표, (Z,W) 가로 세로
	F_GL_Texture *m_Tex;	// 사용텍스처 (참조 포인터)
	F_3D_Vertex	 *m_Vertex;	// 정점 버퍼  (내부 버퍼)
};

//	스프라이트 데이터 클래스
class F_GL_Sprite
{
	//	생성 삭제 함수
public:
	F_GL_Sprite();
	~F_GL_Sprite();
	
	//	클래스 내부 변수
public:
	//	데이터 리스트
	FS_LList *m_List;
	//	텍스처 라이브러리(외부 참조 포인터)
	F_GL_TexLib *m_Lib;
	
	//	클래스 내부 함수
public:
	//	초기 설정
	bool	Init(F_GL_TexLib *p_Lib);
	//	스프라이트 데이터 추가
	FS_Sprite	*Insert(int p_Index,int p_Tex_Index);
	//	스프라이트 데이터 삭제
	bool	Delete(int p_Index);
	//	스프라이트 데이터 얻기
	FS_LList	*Find(int p_Index);
	FS_Sprite	*Find_Data(int p_Index);
	
	//	지정 스프라이트의 가로 세로 설정
	bool	Set_WH(FS_Sprite *p_Sprite,int p_W,int p_H);
	//	지정 스프라이트의 UV 크기 및 그리드 XY 개수 설정
	bool	Set_UV_GridXY(FS_Sprite *p_Sprite,float p_U,float p_V,int p_Nx,int p_Ny,int p_All_Num);
	//	지정 스프라이트의 시간 타입 설정
	bool	Set_DTime(FS_Sprite *p_Sprite,float p_DTime);
	
	//	지정 스프라이트의 정보 설정
	bool	Set_Vertex(FS_Sprite *p_Sprite);
	
	//	지정 스프라이트의 가로 세로 설정
	bool	Set_Rect(FS_Sprite *p_Sprite,float p_Sx,float p_Sy,float p_W,float p_H);
	
	//	클래스 전역 변수
public:
	//	생성 함수
	static	FS_Sprite *New_Sprite();
	//	삭제 함수
	static	BOOL	Delete(LPVOID p_Sprite);
};

