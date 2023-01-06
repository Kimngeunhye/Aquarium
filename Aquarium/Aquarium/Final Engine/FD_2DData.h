/*
 *  FD_2DData.h
 *  2D 관련 데이터 구조체 정의
 *
 *  Created by forthen on 11. 4. 14..
 *  Copyright 2011 forthen. All rights reserved.
 *
 */
#pragma once
#include <math.h>

int		Rand_Int(int p_Max);
float	Rand_Float(float p_Min,float p_Max);

//	실수형 위치 좌표
struct FS_PointF 
{
	FS_PointF()
	{
		m_X = 0.0f;
		m_Y = 0.0f;
	}
	float m_X;
	float m_Y;
};
typedef struct FS_PointF  FS_PointF;
typedef FS_PointF*	FS_P_PointF;

// 정수형 위치 좌표
struct FS_Point
{
	FS_Point()
	{
		m_X = 0;
		m_Y = 0;
	}
	int	m_X;
	int m_Y;
};
typedef struct FS_Point FS_Point;
typedef FS_Point*	FS_P_Point;


//	사각형 구조체
struct FS_Rect {
	int m_X;
	int m_Y;
	int m_Width;
	int	m_Height;
};
typedef struct FS_Rect FS_Rect;
typedef FS_Rect*	FS_P_Rect;

//	사각형 구조체 관리 함수
class F_Rect
{
public:
	//	관리 함수
	static bool SetRect(FS_P_Rect p_Rect,int x,int y,int w,int h);
	static bool	InitRect(FS_P_Rect p_Rect);
};


//	2D 이미지 정보
struct F_Img_Data{
	//	이미지 폭
	int m_Width;
	//	이미지 높이
	int	m_Height;
	//	포맷
	int	m_Format;
	//	컴포넌트 당 비트
	int	m_Bit_Component;
	//	이미지 픽셀 데이터 크기
	int	m_Data_Size;
	//	이미지 픽셀데이터 버퍼
	void *m_Data;
};
typedef struct F_Img_Data F_Img_Data;

//	이미지 관리 클래스
class F_Img
{
public:
	//	이미지 정보 구조체 생성
	static F_Img_Data *Alloc();
	//	이미지 정보 구조체 삭제
	static void Release(F_Img_Data *p_Img);
	
	//	지정한 이미지의 픽셀 버퍼 생성 (이미 생성된 경우 실패)
	static bool Alloc_PixelData(F_Img_Data *p_Img);
	static bool Alloc_PixelData(F_Img_Data *p_Img,int p_Input_Size,void *p_Input_Data);
	static bool Alloc_PixelData(F_Img_Data *p_Img,int p_Input_Size,void *p_Input_Data,int p_R,int p_G,int p_B,int p_A);
	
};
