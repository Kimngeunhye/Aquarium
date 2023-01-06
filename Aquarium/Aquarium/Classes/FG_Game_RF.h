/*
 *  FG_Game_RF.h
 *  Raising Fish 게임 메인 처리 및 데이터 
 *
 *  Created by forthen on 11. 4. 19..
 *  Copyright 2011 forthen. All rights reserved.
 *
 */

#pragma once
#include "F_IOS_File.h"
#include "F_GLES_Define.h"
#include "F_GL_Device.h"

#include "F_GL_RSprite.h"
#include "FG_Player.h"

#include "F_IOS_Audio.h"

//	메인 게임 데이터 루틴
class FG_Game_RF
{
public:
	FG_Game_RF();
	~FG_Game_RF();
	
	//	내부 변수
public:
	//	장면 처리 변수
	int	m_Scene_Type;
	int m_Next_Scene_Type;
	
	//	메인 플레이어
	FG_Player	*m_player;
	
	//	메인 타이머
	float	m_Time;
	//	서브 타이머
	float	m_Sub_Time;
	
	//	설정 초기화 변수
	float	m_Load_TF;
	
	//	화면 사라짐
	bool	m_Screen_TF;
	float	m_Screen_Alpha;
	
	//	텍스처 라이브러리
	F_GL_TexLib	*m_TexLib;
	//	문자열 출력 텍스처 라이브러리
	F_GL_TexLib *m_TexLib_Text;
	
	//	스프라이트 데이터
	F_GL_Sprite *m_Sprite;
	//	문자열 출력 스프라이트
	F_GL_Sprite *m_Text_Out;
	
	
	//	렌더링 스프라이트
	F_GL_RSprite *m_Screen;
	//	렌더링 이펙트
	F_GL_2DEffect *m_Effect;
	//	UI 렌더링
	F_GL_RSprite *m_UI;

	
	//	마우스 입력 변수
	int			m_Mouse_Type;
	FS_XYZ		m_Mouse_Pos;
	FS_XYZ		m_Mouse_Dir;
	int			m_Mouse_Event;
	
	int			m_Help_Page;
	
	//	내부 함수
public:
	//	초기화 함수
	bool	Init();
	
	/*
		데이터 초기화 함수
	 */
	//	문자열 텍스트 출력 설정
	bool	Init_Text_Sprite();
	//	텍스처 라이브러리 설정
	bool	Load_TexLib();
	//	텍스처 라이브러리 삭제
	bool	Delete_TexLib();
	
	//	스프라이트 데이터 설정
	bool	Load_Sprite();
	//	스프라이트 데이터 삭제
	bool	Delete_Sprite();
	
	//	렌더링 스프라이트 설정
	bool	Set_Screen_Date(int p_Type);
	//	렌더링 스트라이트 삭제
	bool	Delete_RSprite();
	//	렌더링 스프라이트 초과화
	bool	Init_RSprite();
	
	//	렌더링 이펙트 삭제
	bool	Delete_Effect();
	//	렌더링 이펙트 로딩
	bool	Load_Effect();
	
	
	/*
	  렌더링 관련 함수
	 */
	//	렌더링 전처리 함수
	bool	Pre_Render(float p_Time);
	//	렌더링 함수
	bool	Render(float p_Time);
	//	장면 전환 설정
	bool	Set_Scene(int p_Scene_Type);
	
	//	비활성 버튼 자유 이동
	bool	Move_Button_Set(int p_S_Index, int p_Count);
	
	/* 
		입력 장치 함수
	 */
	bool	Input_Mouse_Down(FS_XYZ *p_Pos,FS_XYZ *p_Dir);
	bool	Input_Mouse_Up(FS_XYZ *p_Pos,FS_XYZ *p_Dir);
	bool	Input_Mouse_Move(FS_XYZ *OPos,FS_XYZ *ODir,FS_XYZ *NPos,FS_XYZ *NDir);
	
	//	게임 데이터 저장
	bool	Save_Data();
	//	게임 데이터 읽기
	bool	Load_Data();
};