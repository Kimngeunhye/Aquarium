/*
 *  F_IOS_Main.h
 *  
 *
 *  Created by forthen on 11. 4. 13..
 *  Copyright 2011 forthen. All rights reserved.
 *
 */
#pragma once
#include "FG_Game_RF.h"
#include "F_IOS_Interface.h"

// 메인 클래스 설정
class	F_IOS_Main : public	F_IOS_Interface
{
	//	생성 및 삭제
public:
	F_IOS_Main();
	~F_IOS_Main();
	
	////	클래스 내부 변수
public:
	//	OpenGl 장치 클래스 포인터
	F_GL_Device	*m_Device;
	
	//	게임 데이터 관련 클래스 포인터
	FG_Game_RF	*m_Game;
	F_GL_TexLib	*m_TexLib;
		
	////	클래스 내부 함수
public:
	//	렌더링 버퍼 초기화
	bool	Create_Render(int p_Device_Ver);
	
	//	초기 렌더링 영역 설정
	virtual bool Init_Screen(int p_Width,int p_Height);
	//	렌더링 전처리
	virtual bool Pre_Render(float t_Time);
	//	렌더링 처리
	virtual bool Render(float t_Time);
	
	//	화면 회전
	virtual bool Reset_Rotate(int p_Rotate);
	
	//	터치 스크린
	virtual bool Touch_On(int p_Nx,int p_Ny);
	virtual bool Touch_Off(int p_Nx,int p_Ny);
	virtual bool Touch_Move(int p_Ox,int p_Oy,int p_Nx,int p_Ny);
	
	//	게임 데이터 저장
	virtual bool	Save_Data();
	////	전역 함수
public:
};