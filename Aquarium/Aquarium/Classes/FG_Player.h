/*
 *  FG_Player.h
 *  
 *
 *  Created by zendiya on 11. 4. 25..
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once
#include "F_GL_RSprite.h"

//	점수 정보
struct FS_Stage_Info 
{
	int		m_Type;			// 난이도
	int		m_Score;		// 점수
	int		m_Yes_Count;	// 정답 개수
	int		m_No_Count;		// 오답 개수
};

//	플레이 정보
struct FS_Playing_Set 
{
	FS_Stage_Info	m_Info;
	//	출력 정보
	int		m_Max_Count;		// 100개
	int		m_Current_Count;	// 현재 진행 번호
	int		m_Out_Count;		// 출력 문항 번호
	char	m_Out_List[100];	// 0이면 미출력, 1이면 출력됨.
	int		m_Out_Fish[4];		// 문항 선택 번호
	float	m_Size_f;			// 물고기 크기
};

//	게임 정보
struct FS_Play_Info
{
	int m_Level;		// 본인 레렙
	
	//	게임 히스토리
	FS_Stage_Info	m_My_Point[5];
	
	//	게임 진행 
	FS_Playing_Set	m_Play;
	//	이어서 하기 
	int	m_Continue;
	
	//	출력 물고기 변수
	int	m_Out_Fish;
	int	m_Out_Dir;
	int m_Out_Y;
	float m_Out_Speed;
	float m_Out_Time;
	float m_Time;
	
	//	렌덤 변수
	int	m_Line[6];
};

//	게임 문제 데이터 설정
struct FS_QZ_Data
{
	char m_Quz[100][30];
	char m_Ans[100][4][30];
};

//	전체 퀴즈 데이터 설정
struct FS_QZ_All_Data
{
	FS_QZ_Data *m_Level1;
	FS_QZ_Data *m_Level2;
	FS_QZ_Data *m_Level3;
	FS_QZ_Data *m_Level4;
	FS_QZ_Data *m_Level5;
};


class FG_Player
{
public:
	FG_Player();
	~FG_Player();
	
	//	 클래스 내부 변수
public:
	//	유저 캐릭터
	F_GL_RSprite	*m_My_Fish;
	FS_RSprite		*m_Sprite;
	
	//	물고기들
	F_GL_2DEffect	*m_Fishs;
	
	//	메인 이펙트 (참조 포인터)
	F_GL_2DEffect	*m_Main_Effect;
	//	문자출력 라이브러리 (참조 포인터)
	F_GL_Sprite *m_Text_Out;
	F_GL_TexLib *m_TexLib_Text;
	//	UI 렌더링 참조 포인트
	F_GL_RSprite *m_UI;
	
	
	float			m_Play_Size;
	float			m_play_Speed;
	int		m_Combo_Count;
	
	//	게임 플레이 정보
	FS_Play_Info	m_Info;
	
	//	문제 데이터
	FS_QZ_All_Data	*m_Qz;
	
	//	문제 출제 대기 시간
	float	m_Wait_Time;	// 대기 카운트
	int		m_Out_Proccess;	// 대기 0,문제 출력 요청 1 ,항목 출력 2, 정답 선택 및 대기 3, 다음 문제 대기 4, 결과 화면 5
	bool	m_Game_Out;
	
	//	클래스 내부 함수
public:
	//	전역 이펙트 지정
	bool	Set_Effect(F_GL_2DEffect *p_Effect);
	bool	Set_Text_Out(F_GL_Sprite *p_Text_Out,F_GL_TexLib *p_TexLib_Text,F_GL_RSprite *p_UI);
	//	메인 케릭 설정
	bool	Init_Fish(int p_Index,FS_Sprite *p_Sprite);
	//	먹이 물고기 설정
	bool	Set_Fishs(FS_Sprite *p_Sprite);
	//	렌더링 케릭 삭제
	bool	Release_Model();
	
	//	게임 진행 정보 설정
	bool	Set_Play_Type(int p_Type);
	//	이어서 하기 설정
	bool	Continue_Play_Type();
	
	//	렌더링 전처리
	bool	Pre_Render(float p_Time);
	//	렌더링 처리
	bool	Render(float p_Time);
	
	//	물고기 출력
	bool	Out_Fish_Set(float p_Time);
	
	//	마우스 선택
	bool	Mouse_Down(FS_XYZ *p_Pos,FS_XYZ *p_Dir);
	bool	Mouse_Up(FS_XYZ *p_Pos,FS_XYZ *p_Dir);
	bool	Mouse_Move(FS_XYZ *p_Pos,FS_XYZ *p_Dir);
	
	//	충돌 확인
	bool	Conflict_Fish();
	
	//	퀴즈 데이터 삭제
	bool	Release_Qz();
	//	퀴즈 데이터 읽기
	bool	Load_Qz();
	//	퀴즈 파일 읽기
	bool	Load_File(FS_QZ_Data *p_Qz,const char *p_Name);
	
	//	퀴즈 프로세스 설정
	bool	Set_Quiz_Process(int p_Process,float p_DTime);
	//	퀴즈 프로세스 체크
	bool	Quiz_Process(float p_DTime);
	
	//	퀴즈 문장 출력
	bool	Out_Qz_String(bool p_NULL);
	
	//	본인 데이터 업데이트
	bool	My_Data_Update();
	
	//	유저 데이터 저장
	bool	Save_User_Data();
	
	//	유저 데이터 읽기
	bool	Load_User_Data();
	
	//	유저의 데이터 정보 얻기
	int		Get_User_Level();
	int		Get_User_Score(int p_Level);
	int		Get_User_Yes_Count(int p_Level);
	int		Get_User_No_Count(int p_Level);
	
	//	콤보 이펙트 출력
	bool	Out_Put_Combo();
	//	숫자 이팩트
	bool	Out_Put_Number_Effect(int p_Type,int p_Number,float p_X,float p_Y);
	
	//	클래스 외부 함수
public:
	//	플레이 정보 설정
	static bool Init_Playing_Set(FS_Playing_Set *p_Data,int p_Level);
	//	문제 출력 정보 처리
	static int	Out_Put_Qz(FS_Playing_Set *p_Data);
	//	문항 체크
	static int	Check_Put_Qz_An(FS_Playing_Set *p_Data,int p_Number);
};