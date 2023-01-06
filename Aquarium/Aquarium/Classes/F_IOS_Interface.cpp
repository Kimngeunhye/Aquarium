/*
 *  F_IOS_Interface.cpp
 *  
 *
 *  Created by forthen on 11. 4. 13..
 *  Copyright 2011 forthen. All rights reserved.
 *
 */
#include "F_IOS_Main.h"

//	클래스 생성 함수
F_IOS_Interface::F_IOS_Interface()
{
}

//	클래스 삭제 함수
F_IOS_Interface::~F_IOS_Interface()
{
}

//	초기 렌더링 영역 설정
bool F_IOS_Interface::Init_Screen(int p_Width,int p_Height)
{
	return true;
}

//	렌더링 전처리
bool F_IOS_Interface::Pre_Render(float t_Time)
{
	return true;
}

//	렌더링 처리
bool F_IOS_Interface::Render(float t_Time)
{
	return true;
}

//	화면 회전
bool F_IOS_Interface::Reset_Rotate(int p_Rotate)
{
	return true;
}

//	터치 스크린
bool F_IOS_Interface::Touch_On(int p_Nx,int p_Ny)
{
	return true;
}

bool F_IOS_Interface::Touch_Off(int p_Nx,int p_Ny)
{
	return true;
}

bool F_IOS_Interface::Touch_Move(int p_Ox,int p_Oy,int p_Nx,int p_Ny)
{
	return true;
}

//	게임 데이터 저장
bool	F_IOS_Interface::Save_Data()
{
	return true;
}

//	클래스 생성 전역 함수
F_IOS_Interface *F_IOS_Interface::Create_GL_Interface(int p_Gl_Ver)
{
	//	p_Gl_Ver 버전에 따라서 설정
	F_IOS_Main *t_Main = new F_IOS_Main;
	if(t_Main == NULL)
		return NULL;
	t_Main->Create_Render(p_Gl_Ver);
	return t_Main;
}

//	인터페이스 삭제 함수
void F_IOS_Interface::Release_Interface(F_IOS_Interface *p_Interface)
{
	if(p_Interface == NULL)
		return;
	//	버전에 따라 삭제 함수 호출
	F_IOS_Main *t_del = (F_IOS_Main *)p_Interface;
	delete t_del;
	return;
}