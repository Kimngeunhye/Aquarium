/*
 *  F_IOS_Interface.h
 *  IOS 레더링과 연결 클래스
 *
 *  Created by forthen on 11. 4. 13..
 *  Copyright 2011 forthen. All rights reserved.
 *
 */
#pragma once

class	F_IOS_Interface
{
	//	클래스 생성 함수
public:
	F_IOS_Interface();
	~F_IOS_Interface();
	
	//	클래스 가상함수
public:
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
	
	//	클래스 전역 함수
public:
	//	인터페이스 생성 함수
	static F_IOS_Interface *Create_GL_Interface(int p_Gl_Ver);
	//	인터페이스 삭제 함수
	static void Release_Interface(F_IOS_Interface *p_Interface);
};