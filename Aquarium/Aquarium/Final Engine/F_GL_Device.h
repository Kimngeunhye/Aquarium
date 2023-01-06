/*
 *  F_GL_Device.h
 *  
 *
 *  Created by forthen on 11. 4. 14..
 *  Copyright 2011 forthen. All rights reserved.
 *
 */
#pragma once
#include "FD_2DData.h"
#include "F_3D_MATH.h"

// OpenGl 장치 관리 클래스
class F_GL_Device
{
	//	생성 함수 및 삭제 함수
public:
	F_GL_Device();
	~F_GL_Device();
	
	//	내부 변수
public:
	//	프레임 버퍼
	GLuint m_Frame_Buffer;
	//	렌더링 버퍼
	GLuint m_Render_Buffer;
	GLuint m_Depth_Buffer;
	
	//	뷰포트 크기
	FS_Rect	m_ViewPort_Rect;
	//	투시 방식 (0 정방투영, 1 원근투영)
	int		m_Projection_Type;
	FS_XYZ	m_Projection;
	
	
	//	3D 직각좌표 영역
	float	m_Range;
	
	//	스크린 회전 상태 값
	float	m_Screen_Rot;
	int		m_Screen_Dir;	// 0(0) ,1(180),2(270 왼쪽 가로),3(90 오른쪽 가로)
	
	//	내부 함수
public:
	//	프레임 버퍼 생성
	bool Create_FB();
	//	프레임 버퍼 삭제
	bool Release_FB();
	//	렌더링 버퍼 생성
	bool Create_RB();
	//	렌더링 버퍼 삭제
	bool Release_RB();
	
	//	뷰포트 사각형 설정
	bool Set_ViewPort_Rect(int x,int y, int w, int h);
	//	뷰포트 설정
	bool Set_ViewPort();
	
	//	3D 직각 좌표 영역 설정
	bool Set_Range(float p_Range);
	//	3D 직각 좌표 모델 뷰 설정
	bool Set_Ortho();
	
	//	화면 스크린 회전 상태에 따라 (모니터 및 디스플레이 회전 방향과 좌표계 방향은 역방향이다)
	bool Set_Screen_Rot(float p_Angle,int p_Dir);
	//	화면 스크린 회전 적용 시작
	bool Start_Screen_Rot();
	//	화면 스크린 회전 적용 끝
	bool End_Screen_Rot();
	
	//	입력된 좌표를 뷰포트 절대 크기로 계산
	bool Calcul_ViewPort(FS_XYZ *p_Out,FS_XYZ *p_Out_Dir,int p_X,int p_Y);
	
	//	전역 함수
public:
	//	프레임 버퍼를 특정 색으로 칠한다.
	static	bool Clear_Color(float p_R,float p_G,float p_B,float p_A);
	//	프레임 버퍼의 특정 영역만 갱신 시작
	static	bool Start_FrameBuffer_Rect(int x,int y, int w,int h);
	//	프레임 버퍼의 특정 영역만 갱신 끝
	static	bool End_FrameBuffer_Rect();
	
};