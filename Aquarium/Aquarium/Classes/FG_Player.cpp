/*
 *  FG_Player.cpp
 *  
 *
 *  Created by zendiya on 11. 4. 25..
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#include "FG_Player.h"
#include "F_IOS_Audio.h"
#include "F_Memory.h"


FG_Player::FG_Player()
{
	m_My_Fish = NULL;
	m_Sprite = NULL;
	m_Fishs = NULL;
	m_Play_Size = 0.4f;
	m_play_Speed = 120.0f;
	m_Main_Effect = NULL;
	m_Text_Out = NULL;
	m_TexLib_Text = NULL;
	m_UI = NULL;
	m_Qz = NULL;
	m_Game_Out = false;
}

FG_Player::~FG_Player()
{
	Release_Model();
	Release_Qz();
}

//	전역 이펙트 지정
bool	FG_Player::Set_Effect(F_GL_2DEffect *p_Effect)
{
	m_Main_Effect = p_Effect;
	return true;
}

bool	FG_Player::Set_Text_Out(F_GL_Sprite *p_Text_Out,F_GL_TexLib *p_TexLib_Text,F_GL_RSprite *p_UI)
{
	m_Text_Out = p_Text_Out;
	m_TexLib_Text = p_TexLib_Text;
	m_UI = p_UI;
	return true;
}

//	메인 케릭 설정
bool	FG_Player::Init_Fish(int p_Index,FS_Sprite *p_Sprite)
{
	if(p_Sprite == NULL)
		return false;
	if(m_My_Fish != NULL)
	{
		delete m_My_Fish;
		m_My_Fish = NULL;
	}
	//	 렌더링 모델 설정
	m_My_Fish = new F_GL_RSprite;
	m_My_Fish->Init(m_Main_Effect);
	m_Sprite = m_My_Fish->Insert(p_Index,p_Sprite);
	if(m_Sprite != NULL)
	{	
		m_My_Fish->Set_RS_Type(m_Sprite,1);
		m_My_Fish->Set_View_Type(m_Sprite,1);
		m_My_Fish->Set_RS_Pos(m_Sprite,0.0f,0.0f,0.0f);
		m_My_Fish->Set_RS_Scale(m_Sprite,1.0f,0.7f,1.0f);
		
		m_My_Fish->Set_Scale_F(m_Sprite,m_Play_Size);
		
		m_My_Fish->Set_RS_Move1_Param(m_Sprite,0.0f, 0.0f,0.0f,0.0f,0);		// 마우스 클릭 이동 처리.
		m_My_Fish->Set_RS_Move2_Param(m_Sprite,0.0f, 1.0f,0.0f,4.0f,10);	// 물고기 재자리 튼들림
		m_My_Fish->Set_RS_Move3_Param(m_Sprite,0.0f,0.0f,0.0f,0.0f,0);
		m_My_Fish->Set_RS_Z_Rot(m_Sprite,0);
		m_My_Fish->Set_RS_Effect_ID(m_Sprite,1);
	}
	return true;
}

//	먹이 물고기 설정
bool	FG_Player::Set_Fishs(FS_Sprite *p_Sprite)
{
	if(p_Sprite == NULL)
		return false;
	if(m_Fishs != NULL)
	{
		delete m_Fishs;
		m_Fishs = NULL;
	}
	m_Fishs = new F_GL_2DEffect;
	m_Fishs->Set_Sub_Effect((void *)m_Main_Effect);
	//	물고기 15개 추가
	FS_2DEffect *t_Fish = m_Fishs->Insert(1,p_Sprite);
	if(t_Fish != NULL)
	{
		t_Fish->m_Scale = 1.0f;
		m_Fishs->Set_EF_Time_Limit(t_Fish,60.0f);
		m_Fishs->Set_EF_Img_Select_Type(t_Fish,1,0,0);
		m_Fishs->Set_EF_Rect(t_Fish,-18.0f,6.0f,36.0f,12.0f);
		m_Fishs->Set_EF_Sub_Effect(t_Fish,1);
	}
	t_Fish = m_Fishs->Insert(2,p_Sprite);
	if(t_Fish != NULL)
	{
		m_Fishs->Set_EF_Time_Limit(t_Fish,60.0f);
		t_Fish->m_Scale = 1.0f;
		m_Fishs->Set_EF_Img_Select_Type(t_Fish,1,1,0);
		m_Fishs->Set_EF_Rect(t_Fish,-22.0f,6.0f,44.0f,12.0f);
		m_Fishs->Set_EF_Sub_Effect(t_Fish,1);

	}
	t_Fish = m_Fishs->Insert(3,p_Sprite);
	if(t_Fish != NULL)
	{
		m_Fishs->Set_EF_Time_Limit(t_Fish,60.0f);
		t_Fish->m_Scale = 1.0f;
		m_Fishs->Set_EF_Img_Select_Type(t_Fish,1,2,0);
		m_Fishs->Set_EF_Rect(t_Fish,-26.0f,11.0f,52.0f,22.0f);
		m_Fishs->Set_EF_Sub_Effect(t_Fish,1);

	}
	t_Fish = m_Fishs->Insert(4,p_Sprite);
	if(t_Fish != NULL)
	{
		m_Fishs->Set_EF_Time_Limit(t_Fish,60.0f);
		t_Fish->m_Scale = 1.0f;
		m_Fishs->Set_EF_Img_Select_Type(t_Fish,1,0,1);
		m_Fishs->Set_EF_Rect(t_Fish,-28.0f,10.0f,56.0f,20.0f);
		m_Fishs->Set_EF_Sub_Effect(t_Fish,1);

	}
	t_Fish = m_Fishs->Insert(5,p_Sprite);
	if(t_Fish != NULL)
	{
		m_Fishs->Set_EF_Time_Limit(t_Fish,60.0f);
		t_Fish->m_Scale = 1.0f;
		m_Fishs->Set_EF_Img_Select_Type(t_Fish,1,1,1);
		m_Fishs->Set_EF_Rect(t_Fish,-28.0f,10.0f,56.0f,20.0f);
		m_Fishs->Set_EF_Sub_Effect(t_Fish,1);

	}
	t_Fish = m_Fishs->Insert(6,p_Sprite);
	if(t_Fish != NULL)
	{
		m_Fishs->Set_EF_Time_Limit(t_Fish,60.0f);
		t_Fish->m_Scale = 1.0f;
		m_Fishs->Set_EF_Img_Select_Type(t_Fish,1,2,1);
		m_Fishs->Set_EF_Rect(t_Fish,-31.0f,14.0f,62.0f,28.0f);
		m_Fishs->Set_EF_Sub_Effect(t_Fish,1);

	}
	t_Fish = m_Fishs->Insert(7,p_Sprite);
	if(t_Fish != NULL)
	{
		m_Fishs->Set_EF_Time_Limit(t_Fish,60.0f);
		t_Fish->m_Scale = 1.0f;
		m_Fishs->Set_EF_Img_Select_Type(t_Fish,1,0,2);
		m_Fishs->Set_EF_Rect(t_Fish,-36.0f,7.0f,72.0f,14.0f);
		m_Fishs->Set_EF_Sub_Effect(t_Fish,1);

	}
	t_Fish = m_Fishs->Insert(8,p_Sprite);
	if(t_Fish != NULL)
	{
		m_Fishs->Set_EF_Time_Limit(t_Fish,60.0f);
		t_Fish->m_Scale = 1.0f;
		m_Fishs->Set_EF_Img_Select_Type(t_Fish,1,1,2);
		m_Fishs->Set_EF_Rect(t_Fish,-40.0f,13.0f,80.0f,26.0f);
		m_Fishs->Set_EF_Sub_Effect(t_Fish,1);

	}
	t_Fish = m_Fishs->Insert(9,p_Sprite);
	if(t_Fish != NULL)
	{
		m_Fishs->Set_EF_Time_Limit(t_Fish,60.0f);
		t_Fish->m_Scale = 1.0f;
		m_Fishs->Set_EF_Img_Select_Type(t_Fish,1,2,2);
		m_Fishs->Set_EF_Rect(t_Fish,-43.0f,17.0f,86.0f,34.0f);
		m_Fishs->Set_EF_Sub_Effect(t_Fish,1);

	}
	t_Fish = m_Fishs->Insert(10,p_Sprite);
	if(t_Fish != NULL)
	{
		m_Fishs->Set_EF_Time_Limit(t_Fish,60.0f);
		t_Fish->m_Scale = 1.0f;
		m_Fishs->Set_EF_Img_Select_Type(t_Fish,1,0,3);
		m_Fishs->Set_EF_Rect(t_Fish,-47.0f,19.0f,94.0f,38.0f);
		m_Fishs->Set_EF_Sub_Effect(t_Fish,1);

	}
	t_Fish = m_Fishs->Insert(11,p_Sprite);
	if(t_Fish != NULL)
	{
		m_Fishs->Set_EF_Time_Limit(t_Fish,60.0f);
		t_Fish->m_Scale = 1.0f;
		m_Fishs->Set_EF_Img_Select_Type(t_Fish,1,1,3);
		m_Fishs->Set_EF_Rect(t_Fish,-52.0f,13.0f,104.0f,26.0f);
		m_Fishs->Set_EF_Sub_Effect(t_Fish,1);

	}
	t_Fish = m_Fishs->Insert(12,p_Sprite);
	if(t_Fish != NULL)
	{
		m_Fishs->Set_EF_Time_Limit(t_Fish,60.0f);
		t_Fish->m_Scale = 1.0f;
		m_Fishs->Set_EF_Img_Select_Type(t_Fish,1,2,3);
		m_Fishs->Set_EF_Rect(t_Fish,-58.0f,16.0f,116.0f,32.0f);
		m_Fishs->Set_EF_Sub_Effect(t_Fish,1);

	}
	t_Fish = m_Fishs->Insert(13,p_Sprite);
	if(t_Fish != NULL)
	{
		m_Fishs->Set_EF_Time_Limit(t_Fish,60.0f);
		t_Fish->m_Scale = 1.0f;
		m_Fishs->Set_EF_Img_Select_Type(t_Fish,1,0,4);
		m_Fishs->Set_EF_Rect(t_Fish,-63.0f,16.0f,126.0f,32.0f);
		m_Fishs->Set_EF_Sub_Effect(t_Fish,1);

	}
	t_Fish = m_Fishs->Insert(14,p_Sprite);
	if(t_Fish != NULL)
	{
		m_Fishs->Set_EF_Time_Limit(t_Fish,60.0f);
		t_Fish->m_Scale = 1.0f;
		m_Fishs->Set_EF_Img_Select_Type(t_Fish,1,0,4);
		m_Fishs->Set_EF_Rect(t_Fish,-67.0f,19.0f,134.0f,38.0f);
		m_Fishs->Set_EF_Sub_Effect(t_Fish,1);

	}
	t_Fish = m_Fishs->Insert(15,p_Sprite);
	if(t_Fish != NULL)
	{
		m_Fishs->Set_EF_Time_Limit(t_Fish,60.0f);
		t_Fish->m_Scale = 1.0f;
		m_Fishs->Set_EF_Img_Select_Type(t_Fish,1,0,4);
		m_Fishs->Set_EF_Rect(t_Fish,-72.0f,28.0f,144.0f,56.0f);
		m_Fishs->Set_EF_Sub_Effect(t_Fish,1);

	}
	t_Fish = m_Fishs->Insert(16,p_Sprite);
	if(t_Fish != NULL)
	{
		m_Fishs->Set_EF_Time_Limit(t_Fish,60.0f);
		t_Fish->m_Scale = 1.0f;
		m_Fishs->Set_EF_Img_Select_Type(t_Fish,1,0,4);
		m_Fishs->Set_EF_Rect(t_Fish,-83.0f,23.0f,166.0f,46.0f);
		m_Fishs->Set_EF_Sub_Effect(t_Fish,1);

	}
	return true;
}

//	렌더링 케릭 삭제
bool	FG_Player::Release_Model()
{
	if(m_My_Fish != NULL)
	{
		delete m_My_Fish;
		m_My_Fish = NULL;
	}
	m_Sprite = NULL;
	if(m_Fishs != NULL)
	{
		delete m_Fishs;
		m_Fishs = NULL;
	}
	m_Main_Effect = NULL;
	return true;
}

//	렌더링 전처리
bool	FG_Player::Pre_Render(float p_Time)
{
	//	물고기 출력 조절
	Out_Fish_Set(p_Time);
	if(m_My_Fish != NULL)
	{
		m_My_Fish->Pre_Render(p_Time);
	}
	if(m_Fishs != NULL)
	{
		if(m_Fishs->Pre_Render(p_Time))
		{
			if((m_Out_Proccess == 2)||(m_Out_Proccess == 3))
			{
				//	다음 문제로 넘김 2,3 번인 경우에 설정.
				Set_Quiz_Process(4,1.0f);
			}
		}
	}
	//if(m_Main_Effect != NULL)
	//{
	//	m_Main_Effect->Pre_Render(p_Time);
	//}
	//	충돌 확인
	Conflict_Fish();
	return	true;
}

//	렌더링 처리
bool	FG_Player::Render(float p_Time)
{
	if(m_My_Fish != NULL)
	{
		m_My_Fish->Render(p_Time);
	}
	if(m_Fishs != NULL)
	{
		m_Fishs->Render(p_Time,1.0f);
	}
	//if(m_Main_Effect != NULL)
	//{
	//	m_Main_Effect->Render(p_Time);
	//}
	return true;
}

bool	FG_Player::Mouse_Down(FS_XYZ *p_Pos,FS_XYZ *p_Dir)
{
	if(p_Pos == NULL)
		return false;
	//if(m_My_Fish != NULL)
	//{
	//	m_My_Fish->Mouse_Down(p_Pos, p_Dir);
	//}
	
	//	종료 화면이면 무시
	if(m_Out_Proccess >= 5)
		return true;
	
	//	본인 물고기 이동 처리
	if(m_Sprite != NULL)
	{
		//	지정 위치로 이동 처리 (방향 ,속도)
		m_My_Fish->Set_RS_Move1_Param(m_Sprite,p_Pos->m_X,p_Pos->m_Y,0.0f,m_play_Speed,8);
	}
	return true;
}

bool	FG_Player::Mouse_Up(FS_XYZ *p_Pos,FS_XYZ *p_Dir)
{
	if(p_Pos == NULL)
		return false;
	//if(m_My_Fish != NULL)
	//{
	//	m_My_Fish->Mouse_Up(p_Pos, p_Dir);
	//}
	return true;
}

bool	FG_Player::Mouse_Move(FS_XYZ *p_Pos,FS_XYZ *p_Dir)
{
	if(p_Pos == NULL)
		return false;
	//if(m_My_Fish != NULL)
	//{
	//	m_My_Fish->Mouse_Move(p_Pos, p_Dir);
	//}
	
	//	종료 화면이면 무시
	if(m_Out_Proccess >= 5)
		return true;
	
	//	본인 물고기 이동 처리
	if(m_Sprite != NULL)
	{
		//	지정 위치로 이동 처리 (방향 ,속도)
		m_My_Fish->Set_RS_Move1_Param(m_Sprite,p_Pos->m_X,p_Pos->m_Y,0.0f,m_play_Speed,8);
	}
	return true;
}

//	게임 진행 정보 설정
bool	FG_Player::Set_Play_Type(int p_Type)
{
	m_Game_Out = false;
	m_Combo_Count = 0;
	m_Info.m_Continue = 1; // 이어서 하기 가능함
	FG_Player::Init_Playing_Set(&m_Info.m_Play,p_Type);
	m_Play_Size = m_Info.m_Play.m_Size_f;
	switch(m_Info.m_Play.m_Info.m_Type)
	{
		case 1:
		{
			m_Info.m_Out_Fish = Rand_Int(13)+1;
			m_Info.m_Out_Dir = Rand_Int(2);
			m_Info.m_Out_Time = Rand_Float(2.0f,3.0f);
			m_Info.m_Out_Y = Rand_Int(6);
			m_Info.m_Out_Speed = Rand_Float(25.0f,35.0f);
			m_Info.m_Time = 0.0f;
			for(int i = 0 ; i < 6; i++)
			{
				m_Info.m_Line[i] = 0;
			}
			break;
		}
		case 2:
		{
			m_Info.m_Out_Fish = Rand_Int(13)+1;
			m_Info.m_Out_Dir = Rand_Int(2);
			m_Info.m_Out_Time = Rand_Float(2.0f,3.0f);
			m_Info.m_Out_Y = Rand_Int(6);
			m_Info.m_Out_Speed = Rand_Float(25.0f,35.0f);
			m_Info.m_Time = 0.0f;
			for(int i = 0 ; i < 6; i++)
			{
				m_Info.m_Line[i] = 0;
			}
			break;
		}
		case 3:
		{
			m_Info.m_Out_Fish = Rand_Int(13)+1;
			m_Info.m_Out_Dir = Rand_Int(2);
			m_Info.m_Out_Time = Rand_Float(2.0f,3.0f);
			m_Info.m_Out_Y = Rand_Int(6);
			m_Info.m_Out_Speed = Rand_Float(25.0f,35.0f);
			m_Info.m_Time = 0.0f;
			for(int i = 0 ; i < 6; i++)
			{
				m_Info.m_Line[i] = 0;
			}
			break;
		}
		case 4:
		{
			m_Info.m_Out_Fish = Rand_Int(13)+1;
			m_Info.m_Out_Dir = Rand_Int(2);
			m_Info.m_Out_Time = Rand_Float(2.0f,3.0f);
			m_Info.m_Out_Y = Rand_Int(6);
			m_Info.m_Out_Speed = Rand_Float(25.0f,35.0f);
			m_Info.m_Time = 0.0f;
			for(int i = 0 ; i < 6; i++)
			{
				m_Info.m_Line[i] = 0;
			}
			break;
		}
		case 5:
		{
			m_Info.m_Out_Fish = Rand_Int(13)+1;
			m_Info.m_Out_Dir = Rand_Int(2);
			m_Info.m_Out_Time = Rand_Float(2.0f,3.0f);
			m_Info.m_Out_Y = Rand_Int(6);
			m_Info.m_Out_Speed = Rand_Float(25.0f,35.0f);
			m_Info.m_Time = 0.0f;
			for(int i = 0 ; i < 6; i++)
			{
				m_Info.m_Line[i] = 0;
			}
			break;
		}
	}
	if(m_Fishs != NULL)
	{
		//	출력 물고기 삭제
		m_Fishs->Stop_Out_Effect();
	}
	//	퀴즈 프로세스 진행
	Set_Quiz_Process(0,1.0f);
	return	true;
}

//	이어서 하기 설정
bool	FG_Player::Continue_Play_Type()
{
	m_Game_Out = false;
	m_Info.m_Continue = 1; // 이어서 하기 가능함
	m_Combo_Count = 0;
	//	물고기 크기 복원
	m_Play_Size = m_Info.m_Play.m_Size_f;
	
	// 라인 초기화
	m_Info.m_Out_Fish = Rand_Int(13)+1;
	m_Info.m_Out_Dir = Rand_Int(2);
	m_Info.m_Out_Time = Rand_Float(2.0f,3.0f);
	m_Info.m_Out_Y = Rand_Int(6);
	m_Info.m_Out_Speed = Rand_Float(25.0f,35.0f);
	m_Info.m_Time = 0.0f;
	for(int i = 0 ; i < 6; i++)
	{
		m_Info.m_Line[i] = 0;
	}
	if(m_Fishs != NULL)
	{
		//	출력 물고기 삭제
		m_Fishs->Stop_Out_Effect();
	}
	//	퀴즈 프로세스 진행
	Set_Quiz_Process(0,1.0f);
	return	true;
}

//	물고기 출력
bool	FG_Player::Out_Fish_Set(float p_Time)
{
	Quiz_Process(p_Time);
	//	종료 화면이면 무시
	if(m_Out_Proccess >= 5)
		return true;
	
	switch(m_Info.m_Play.m_Info.m_Type)
	{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		{
			m_Info.m_Time = m_Info.m_Time + p_Time;
			if(m_Info.m_Time > m_Info.m_Out_Time)
			{
				//	물고기 출력 설정
				int t_Rand_i =  Rand_Int(100);
				if(t_Rand_i < 20)
					m_Info.m_Out_Fish = 1;
				else if(t_Rand_i < 35)
					m_Info.m_Out_Fish = 2;
				else if(t_Rand_i < 45)
					m_Info.m_Out_Fish = 3;
				else if(t_Rand_i < 53)
					m_Info.m_Out_Fish = 4;
				else if(t_Rand_i < 60)
					m_Info.m_Out_Fish = 5;
				else if(t_Rand_i < 66)
					m_Info.m_Out_Fish = 6;
				else if(t_Rand_i < 71)
					m_Info.m_Out_Fish = 7;
				else if(t_Rand_i < 78)
					m_Info.m_Out_Fish = 8;
				else if(t_Rand_i < 84)
					m_Info.m_Out_Fish = 9;
				else if(t_Rand_i < 89)
					m_Info.m_Out_Fish = 10;
				else if(t_Rand_i < 94)
					m_Info.m_Out_Fish = 11;
				else if(t_Rand_i < 98)
					m_Info.m_Out_Fish = 12;
				else if(t_Rand_i < 100)
				{
					m_Info.m_Out_Fish = 13 + Rand_Int(4);
				}
				
				m_Info.m_Out_Dir = Rand_Int(2);
				m_Info.m_Out_Time = Rand_Float(1.0f,1.5f);
				m_Info.m_Out_Y = Rand_Int(6);
				
				int	t_Roof = 0;
				for(int i = 0 ; i < 6; i++)
				{
					t_Roof = m_Info.m_Line[i] + t_Roof;
				}
				if(t_Roof > 5)
				{
					/*
					 if(m_Out_Proccess == 1)
					{
						// 문제 출력으로 전환
						Set_Quiz_Process(2,0.0f);
					}
					*/
					//	리셋
					for(int i = 0 ; i < 6; i++)
					{
						m_Info.m_Line[i] = 0;
					}
				}
				t_Roof = 0;
				while (m_Info.m_Line[m_Info.m_Out_Y] == 1) 
				{
					//	다시 검사
					m_Info.m_Out_Y = Rand_Int(6);
					t_Roof++;
					if(t_Roof > 10)
					{
						if(m_Info.m_Line[m_Info.m_Out_Y] == 1)
							return false;
					}
				}
				//	출력 정보 설정
				m_Info.m_Line[m_Info.m_Out_Y] = 1;
				
				//	물고기 이동 속도
				m_Info.m_Out_Speed = Rand_Float(60.0f,80.0f);
				m_Info.m_Time = 0.0f;
				
				//	출력 진행
				if(m_Fishs != NULL)
				{
					FS_2DEffect_Info *t_Fish = m_Fishs->Out_Effect(m_Info.m_Out_Fish);
					if(t_Fish != NULL)
					{
						//	방향이동
						if(m_Info.m_Out_Dir == 0)
						{
							m_Fishs->Set_EF_Start_Pos(t_Fish,-280.0f,m_Info.m_Out_Y*45.0f - 120.0f,-10.0f);
							m_Fishs->Set_EF_End_Pos(t_Fish,280.0f,m_Info.m_Out_Y*45.0f - 120.0f,-10.0f);
							m_Fishs->Set_EF_Move1_Param(t_Fish,1.0f,0.0f,0.0f,m_Info.m_Out_Speed,1);
						}
						else
						{
							m_Fishs->Set_EF_Start_Pos(t_Fish,280.0f,m_Info.m_Out_Y*45.0f - 120.0f,-5.0f);
							m_Fishs->Set_EF_End_Pos(t_Fish,-280.0f,m_Info.m_Out_Y*45.0f - 120.0f,-5.0f);
							m_Fishs->Set_EF_Move1_Param(t_Fish,-1.0f,0.0f,0.0f,m_Info.m_Out_Speed,1);
						}
						m_Fishs->Set_EF_Move2_Param(t_Fish,0.0f,1.0f,0.0f,3.0f,10);	// 물고기 재자리 튼들림
						
						//	해당 물고기에 문제 출력하기.
						if(m_Out_Proccess == 2)
						{
							int t_Check = FG_Player::Check_Put_Qz_An(&m_Info.m_Play,m_Info.m_Out_Y);
							if(t_Check == 1)
							{
								// 모두 출력됨
								Set_Quiz_Process(3,0.0f);
								//	감점 처리 (점수)
								m_Fishs->Set_EF_Result(t_Fish,0, m_Info.m_Out_Fish+1);
							}
							else if(t_Check > 1)
							{
								// 지정 이팩트에 출력
								//	물고기에 문자열 이팩트 넣는다.
								// m_Fishs
								m_Fishs->Set_EF_Text_Pos(t_Fish,m_Text_Out->Find_Data(t_Check),0.0f,-16.0f,5.0f,1.0f);
								if(t_Check == 2)
								{
									//	정답
									m_Fishs->Set_EF_Result(t_Fish,1, m_Info.m_Out_Fish+20);
								}
								else
								{
									// 오답
									m_Fishs->Set_EF_Result(t_Fish,2, m_Info.m_Out_Fish+5);
								}
							}
							else
							{
								m_Fishs->Set_EF_Result(t_Fish,0, m_Info.m_Out_Fish+1);
							}

						}
						else
						{
							//	감점 처리 (점수)
							m_Fishs->Set_EF_Result(t_Fish,0, m_Info.m_Out_Fish+1);
						}
					}
				}
			}
			break;
		}
	}
	return true;
}

//	충돌 확인
bool	FG_Player::Conflict_Fish()
{
	if(m_Sprite == NULL)
		return false;
	if(m_Fishs == NULL)
		return false;
	//	종료 화면이면 무시
	if(m_Out_Proccess >= 5)
		return true;
	//	충돌 확인
	FS_2DEffect_Info *t_Target = m_Fishs->Get_Conflict(&m_Sprite->m_Button_Rect);
	if(t_Target != NULL)
	{
		
		if(t_Target->m_Result1 == 1)
		{
			// 크기 조절
			m_Play_Size = m_Play_Size + 0.1f;
			if(m_Play_Size > 1.2f)
			{
				m_Play_Size = 1.2f;
				m_Combo_Count = m_Combo_Count + 1;
				//	테스트 컴보
				Out_Put_Combo();
			}
			m_Info.m_Play.m_Size_f = m_Play_Size;
			m_My_Fish->Set_Scale_F(m_Sprite,m_Play_Size);
			
			// 점수 추가.
			m_Info.m_Play.m_Info.m_Score = m_Info.m_Play.m_Info.m_Score + t_Target->m_Result2 + m_Combo_Count*5;
			m_Info.m_Play.m_Info.m_Yes_Count = m_Info.m_Play.m_Info.m_Yes_Count+1;
			
			//	추가 점수 이팩트 출력
			Out_Put_Number_Effect(0,t_Target->m_Result2 + m_Combo_Count*5,
								  m_Sprite->m_Button_Rect.m_X + m_Sprite->m_Button_Rect.m_Z/2.0f,
								  m_Sprite->m_Button_Rect.m_Y - m_Sprite->m_Button_Rect.m_W/2.0f);
			
			//	점수 렌더링 업데디트
			if(m_UI != NULL)
			{
				FS_RSprite *t_Sprite = m_UI->Find_Data(20);
				if(t_Sprite != NULL)
				{
					m_UI->Set_Out_Number(t_Sprite,m_Info.m_Play.m_Info.m_Score,t_Target->m_Result2 + m_Combo_Count*5);
				}
				t_Sprite = m_UI->Find_Data(21);
				if(t_Sprite != NULL)
				{
					m_UI->Set_Out_Number(t_Sprite,m_Info.m_Play.m_Info.m_Yes_Count,0);
				}
			}
			
			// 타겟 사라지고 이펙트 처리
			t_Target->m_Type = 10;
			//	식사 에니 메이션 시작
			m_Sprite->m_Button_State = 7;
			//	테스트
			if(m_Main_Effect != NULL)
			{
				FS_2DEffect_Info *t_Effect = m_Main_Effect->Out_Effect(2);
				if(t_Effect != NULL)
				{
					m_Main_Effect->Set_EF_Start_Pos(t_Effect,t_Target->m_Pos.m_X,t_Target->m_Pos.m_Y,100.0f);
					m_Main_Effect->Set_EF_End_Pos(t_Effect,t_Target->m_Pos.m_X,t_Target->m_Pos.m_Y,100.0f);
					m_Main_Effect->Set_EF_Move1_Param(t_Effect, 0.0f,0.0f,1.0f,0.0f,2);
				}
			}
			
			//	점수 사운드
			F_IO_Wave::Play_Sound(3);
		}
		else
		{
			//	t_Target->m_Result2 점수 감소
			m_Combo_Count = 0;
			if(t_Target->m_Result1 == 2)
			{
				m_Info.m_Play.m_Info.m_No_Count = m_Info.m_Play.m_Info.m_No_Count+1;
			}
			
			int t_Score = m_Info.m_Play.m_Info.m_Score - t_Target->m_Result2;
			if(t_Score < 0)
			{
				t_Score = m_Info.m_Play.m_Info.m_Score;
				m_Info.m_Play.m_Info.m_Score = 0;
			}
			else
			{
				t_Score = t_Target->m_Result2;
				m_Info.m_Play.m_Info.m_Score = m_Info.m_Play.m_Info.m_Score - t_Target->m_Result2;
			}
			//	감점 이팩트 출력
			Out_Put_Number_Effect(1,t_Target->m_Result2,
								  m_Sprite->m_Button_Rect.m_X + m_Sprite->m_Button_Rect.m_Z/2.0f,
								  m_Sprite->m_Button_Rect.m_Y - m_Sprite->m_Button_Rect.m_W/2.0f);
			
			//	점수 렌더링 업데디트
			if(m_UI != NULL)
			{
				FS_RSprite *t_Sprite = m_UI->Find_Data(20);
				if(t_Sprite != NULL)
				{
					m_UI->Set_Out_Number(t_Sprite,m_Info.m_Play.m_Info.m_Score,-t_Score);
				}
				t_Sprite = m_UI->Find_Data(22);
				if(t_Sprite != NULL)
				{
					m_UI->Set_Out_Number(t_Sprite,m_Info.m_Play.m_Info.m_No_Count,0);
				}
			}
			
			//	타겟 도망치고 이펙트 처리
			t_Target->m_Type = 2;
			// 위치 얻기
			float t_RY = (float)(rand()%320) - 160.0f;
			if(t_Target->m_Y_Rot == 1)
			{
				//	카운트 만큼 이동 후 사라짐
				m_Fishs->Set_EF_Move3_Param(t_Target,(-300.0f - t_Target->m_Pos.m_X)/60.0f,
										 (t_RY - t_Target->m_Pos.m_Y)/60.0f,0.0f,60.0f,31);
			}
			else
			{
				m_Fishs->Set_EF_Move3_Param(t_Target,(300.0f - t_Target->m_Pos.m_X)/60.0f,
											(t_RY - t_Target->m_Pos.m_Y)/60.0f,0.0f,60.0f,31);
			}
			
			//	크기 줄임
			m_Play_Size = m_Play_Size - 0.1f;
			if(m_Play_Size < 0.1f)
			{
				m_Play_Size = 0.1f;
				m_Info.m_Play.m_Size_f = m_Play_Size;
				// 채력 바닥 게임 종료
				Set_Quiz_Process(5,0.0f);
			}
			else
			{
				m_Info.m_Play.m_Size_f = m_Play_Size;
			}

			m_My_Fish->Set_Scale_F(m_Sprite,m_Play_Size);
			//	데이지
			m_Sprite->m_Button_State = 5;
			//	데이지 사운드
			F_IO_Wave::Play_Sound(4);
			
		}

	}
	return true;
}

//	퀴즈 데이터 삭제
bool	FG_Player::Release_Qz()
{
	if(m_Qz == NULL)
		return false;
	if(m_Qz->m_Level1 != NULL)
	{
		F_Free(m_Qz->m_Level1);
		m_Qz->m_Level1 = NULL;
	}
	if(m_Qz->m_Level2 != NULL)
	{
		F_Free(m_Qz->m_Level2);
		m_Qz->m_Level2 = NULL;
	}
	if(m_Qz->m_Level3 != NULL)
	{
		F_Free(m_Qz->m_Level3);
		m_Qz->m_Level3 = NULL;
	}
	if(m_Qz->m_Level4 != NULL)
	{
		F_Free(m_Qz->m_Level4);
		m_Qz->m_Level4 = NULL;
	}
	if(m_Qz->m_Level5 != NULL)
	{
		F_Free(m_Qz->m_Level5);
		m_Qz->m_Level5 = NULL;
	}
	F_Free(m_Qz);
	m_Qz = NULL;
	return true;
}

//	퀴즈 데이터 읽기
bool	FG_Player::Load_Qz()
{
	//	기존 메모리 삭제
	Release_Qz();
	//	매모리 생성
	m_Qz = (FS_QZ_All_Data *)F_Alloc(sizeof(FS_QZ_All_Data));
	if(m_Qz == NULL)
		return false;
	//	메모리 생성
	m_Qz->m_Level1 = (FS_QZ_Data *)F_Alloc(sizeof(FS_QZ_Data));
	m_Qz->m_Level2 = (FS_QZ_Data *)F_Alloc(sizeof(FS_QZ_Data));
	m_Qz->m_Level3 = (FS_QZ_Data *)F_Alloc(sizeof(FS_QZ_Data));
	m_Qz->m_Level4 = (FS_QZ_Data *)F_Alloc(sizeof(FS_QZ_Data));
	m_Qz->m_Level5 = (FS_QZ_Data *)F_Alloc(sizeof(FS_QZ_Data));
	
	Load_File(m_Qz->m_Level1,"ek1.qda");
	Load_File(m_Qz->m_Level2,"ek2.qda");
	Load_File(m_Qz->m_Level3,"ke1.qda");
	Load_File(m_Qz->m_Level4,"ke2.qda");
	Load_File(m_Qz->m_Level5,"ee1.qda");

	return true;
}

//	퀴즈 프로세스 설정
bool	FG_Player::Set_Quiz_Process(int p_Process,float p_DTime)
{
	m_Wait_Time = p_DTime;		// 대기 카운트
	m_Out_Proccess = p_Process;
	return true;
}

//	퀴즈 프로세스 체크
bool	FG_Player::Quiz_Process(float p_DTime)
{
	switch (m_Out_Proccess)
	{
		case 0:
		{
			// 출제 대기
			m_Wait_Time = m_Wait_Time - p_DTime;
			if(m_Wait_Time < 0.0f)
			{
				m_Wait_Time = 0.0f;
				// 문제 출제 진행
				Set_Quiz_Process(1,1.0f);
				// 출제 문제 선택
				int t_Int = FG_Player::Out_Put_Qz(&m_Info.m_Play);
				if(t_Int == 2)
				{
					//	결과 보여주고 3초후 초기화면으로
					Set_Quiz_Process(5,0.0f);
				}
				else if(t_Int == 1)
				{
					//	출제 문제 텍스트 출력.
					Out_Qz_String(false);
				}
			}
			break;
		}
		case 1:
		{
			//	문제 출제 요청
			m_Wait_Time = m_Wait_Time - p_DTime;
			if(m_Wait_Time < 0.0f)
			{
				Set_Quiz_Process(2,0.0f);
			}
			//	물고기 출력 시스템에서 물고기 배정되면 2로 변경
			break;
		}
		case 2:
		{
			//	물고기 출력 시스템에서 모든 물고기 배정되면 3로 변경
			break;
		}
		case 3:
		{
			//	정답 또는 오답 물고기 선택까지 기다림
			//	하나가 체크 되거나, 정답 물고기 사라진경우 4번으로 변경
			break;
		}
		case 4:
		{
			//	정답, 또는 오답에 대한 점수 가감 및 이팩트 출력
			m_Wait_Time = m_Wait_Time - p_DTime;
			if(m_Wait_Time < 0.0f)
			{
				m_Wait_Time = 0.0f;
				//	처음 프로세스로
				Set_Quiz_Process(0,0.5f);
				
				//	출제 문제 텍스트 출력.
				Out_Qz_String(true);
			}
			break;
		}
		case 5:
		{
			//	게임 결과 보여주고 초기 화면으로 변환.
			// 모든 문제 끝남, 결과 저장.
			m_Info.m_Continue = 0; // 이어서 하기 불가
			// 게임 진행 결과 저장
			My_Data_Update();
			
			//	 UI 및 버튼 삭제
			if(m_UI != NULL)
			{
				FS_RSprite *t_Sprite = m_UI->Find_Data(1);
				if(t_Sprite != NULL)
				{
					// 사라짐
					m_UI->Set_View_Type(t_Sprite,0);
				}
				t_Sprite = m_UI->Find_Data(2);
				if(t_Sprite != NULL)
				{
					// 사라짐
					m_UI->Set_View_Type(t_Sprite,0);
				}
				t_Sprite = m_UI->Find_Data(3);
				if(t_Sprite != NULL)
				{
					// 사라짐
					m_UI->Set_View_Type(t_Sprite,0);
				}
				t_Sprite = m_UI->Find_Data(4);
				if(t_Sprite != NULL)
				{
					// 사라짐
					m_UI->Set_View_Type(t_Sprite,0);
				}
				t_Sprite = m_UI->Find_Data(7);
				if(t_Sprite != NULL)
				{
					// 사라짐
					m_UI->Set_View_Type(t_Sprite,0);
				}
				t_Sprite = m_UI->Find_Data(10);
				if(t_Sprite != NULL)
				{
					// 사라짐
					m_UI->Set_View_Type(t_Sprite,0);
				}
				t_Sprite = m_UI->Find_Data(20);
				if(t_Sprite != NULL)
				{
					// 사라짐
					m_UI->Set_View_Type(t_Sprite,0);
				}
				t_Sprite = m_UI->Find_Data(21);
				if(t_Sprite != NULL)
				{
					// 사라짐
					m_UI->Set_View_Type(t_Sprite,0);
				}
				t_Sprite = m_UI->Find_Data(22);
				if(t_Sprite != NULL)
				{
					// 사라짐
					m_UI->Set_View_Type(t_Sprite,0);
				}
				
				//	출력 정보 출력.
				t_Sprite = m_UI->Find_Data(30);
				if(t_Sprite != NULL)
				{
					// 출력
					t_Sprite->m_Time = ((float)t_Sprite->m_Rand_int)/10.0f;
					m_UI->Set_View_Type(t_Sprite,1);
					m_UI->Set_RS_Move1_Param(t_Sprite,0.0f,200.0f,0.0f,300.0f,11);
				}
				//	점수,정답,오답,도전문항 수
				t_Sprite = m_UI->Find_Data(31);
				if(t_Sprite != NULL)
				{
					t_Sprite->m_Time = ((float)t_Sprite->m_Rand_int)/10.0f;
					m_UI->Set_View_Type(t_Sprite,1);
					m_UI->Set_RS_Move1_Param(t_Sprite,0.0f,200.0f,0.0f,300.0f,11);
					m_UI->Set_Out_Number(t_Sprite,m_Info.m_Play.m_Info.m_Score,0);
				}
				t_Sprite = m_UI->Find_Data(32);
				if(t_Sprite != NULL)
				{
					t_Sprite->m_Time = ((float)t_Sprite->m_Rand_int)/10.0f;
					m_UI->Set_View_Type(t_Sprite,1);
					m_UI->Set_RS_Move1_Param(t_Sprite,0.0f,200.0f,0.0f,300.0f,11);
					m_UI->Set_Out_Number(t_Sprite,m_Info.m_Play.m_Info.m_Yes_Count,0);
				}
				t_Sprite = m_UI->Find_Data(33);
				if(t_Sprite != NULL)
				{
					t_Sprite->m_Time = ((float)t_Sprite->m_Rand_int)/10.0f;
					m_UI->Set_View_Type(t_Sprite,1);
					m_UI->Set_RS_Move1_Param(t_Sprite,0.0f,200.0f,0.0f,300.0f,11);
					m_UI->Set_Out_Number(t_Sprite,m_Info.m_Play.m_Info.m_No_Count,0);
				}
				t_Sprite = m_UI->Find_Data(34);
				if(t_Sprite != NULL)
				{
					t_Sprite->m_Time = ((float)t_Sprite->m_Rand_int)/10.0f;
					m_UI->Set_View_Type(t_Sprite,1);
					m_UI->Set_RS_Move1_Param(t_Sprite,0.0f,200.0f,0.0f,300.0f,11);
					m_UI->Set_Out_Number(t_Sprite,m_Info.m_Play.m_Current_Count,0);
				}
				for(int i = 0; i < 7;i++)
				{
					t_Sprite = m_UI->Find_Data(35+i);
					if(t_Sprite != NULL)
					{
						t_Sprite->m_Time = ((float)t_Sprite->m_Rand_int)/10.0f;
						m_UI->Set_View_Type(t_Sprite,1);
						m_UI->Set_RS_Move1_Param(t_Sprite,0.0f,200.0f,0.0f,300.0f,11);
					}
				}
				//	난이도 출력
				t_Sprite = m_UI->Find_Data(42);
				if(t_Sprite != NULL)
				{
					t_Sprite->m_Time = ((float)t_Sprite->m_Rand_int)/10.0f;
					m_UI->Set_View_Type(t_Sprite,1);
					m_UI->Set_RS_Ani(t_Sprite,(m_Info.m_Play.m_Info.m_Type-1)%3,(m_Info.m_Play.m_Info.m_Type-1)/3,0.0f);
					m_UI->Set_RS_Move1_Param(t_Sprite,0.0f,200.0f,0.0f,300.0f,11);
				}
				//	등급 출력
				t_Sprite = m_UI->Find_Data(43);
				if(t_Sprite != NULL)
				{
					t_Sprite->m_Time = ((float)t_Sprite->m_Rand_int)/10.0f;
					m_UI->Set_View_Type(t_Sprite,1);
					if(m_Info.m_Play.m_Info.m_Yes_Count <= 50)
					{
						m_UI->Set_RS_Ani(t_Sprite,0,0,0.0f);
					}
					else if(m_Info.m_Play.m_Info.m_Yes_Count <= 80)
					{
						m_UI->Set_RS_Ani(t_Sprite,1,0,0.0f);
					}
					else
					{
						m_UI->Set_RS_Ani(t_Sprite,2,0,0.0f);
					}
					m_UI->Set_RS_Move1_Param(t_Sprite,0.0f,200.0f,0.0f,300.0f,11);
				}
				
			}
			
			//	프로세스 변경
			Set_Quiz_Process(6,5.0f);
			break;
		}
		case 6:
		{
			//	결과 출력 대기
			m_Wait_Time = m_Wait_Time - p_DTime;
			if(m_Wait_Time < 0.0f)
			{
				m_Wait_Time = 0.0f;
				// 초기 화면으로
				m_Game_Out = true;
			}
			break;
		}
		default:
			break;
	}
	return false;
}

//	퀴즈 파일 읽기
bool	FG_Player::Load_File(FS_QZ_Data *p_Qz,const char *p_Name)
{
	if(p_Name == NULL)
		return false;
	if(p_Qz == NULL)
		return false;	
	//	파일 읽기
	string	t_Path = F_IOS_File::Get_Resource_Path();
	char	t_File_Name[512];
	sprintf(t_File_Name,"%s/%s",t_Path.c_str(),p_Name);
	
	FILE *t_File = fopen(t_File_Name,"r");
	if(t_File == NULL)
		return	false;
	char *t_Buffer = NULL;
	
	//	버퍼 읽는다.
	fseek(t_File,0, SEEK_END);
	int	t_Size_file = ftell(t_File);
	if(t_Size_file > 0)
	{
		fseek(t_File,0, SEEK_SET);
		//	메모리 할당
		t_Buffer = (char *)F_Alloc(t_Size_file);
		if(t_Buffer != NULL)
		{
			fread(t_Buffer,t_Size_file,1,t_File);
		}
		else
		{
			F_Free(t_Buffer);
			t_Buffer = NULL;
		}
	}
	
	//	파일 닫는다.
	fclose(t_File);
	t_File = NULL;
	
	int t_Tab = 0;
	int	t_Line = 0;
	int t_Num = 0;
	//	데이터 처리
	if(t_Buffer != NULL)
	{
		for(int i = 3; i < t_Size_file;i++)
		{
			if(t_Buffer[i] == 0x09)
			{
				// 텝이동
				t_Tab++;
				t_Num = 0;
			}
			else if((t_Buffer[i] == 0x0d)&&(t_Buffer[i+1] == 0x0a))
			{
				// 줄럼김
				t_Line++;
				t_Tab = 0;
				t_Num = 0;
				i++;
			}
			else
			{
				if(t_Line < 100)
				{
					// 데이터 넣기
					if(t_Tab == 0)
					{
						p_Qz->m_Quz[t_Line][t_Num] = t_Buffer[i];
					}	
					else
					{
						p_Qz->m_Ans[t_Line][t_Tab - 1][t_Num] = t_Buffer[i];
					}
					t_Num++;
				}
			}
		}
		F_Free(t_Buffer);
	}
	return true;
}

//	플레이 정보 설정
bool FG_Player::Init_Playing_Set(FS_Playing_Set *p_Data,int p_Level)
{
	if(p_Data == NULL)
		return false;
	memset(p_Data,0,sizeof(FS_Playing_Set));
	p_Data->m_Info.m_Type = p_Level;
	p_Data->m_Max_Count = 100;
	p_Data->m_Size_f = 0.4;
	return true;
}

//	문제 출력 정보 처리
int	FG_Player::Out_Put_Qz(FS_Playing_Set *p_Data)
{
	if(p_Data == NULL)
		return 0;
	if(p_Data->m_Info.m_Type == 0)
		return 0;
	//	현재 문제 풀이 정보
	p_Data->m_Current_Count++;
	if(p_Data->m_Max_Count < p_Data->m_Current_Count)
	{
		p_Data->m_Current_Count = p_Data->m_Max_Count;
		return 2;	// 완료
	}
	p_Data->m_Out_Count = Rand_Int(100);		// 출력 문항 번호
	bool	t_TF = false;
	for(int i = 0; i < 100;i++)
	{
		if(p_Data->m_Out_List[(i+p_Data->m_Out_Count)%100] == 0)
		{
			// 출력 문제 선택됨
			p_Data->m_Out_List[(i+p_Data->m_Out_Count)%100] = 1;
			p_Data->m_Out_Count = (i+p_Data->m_Out_Count)%100;
			//	출력 물고기 번호 설정
			for(int k = 0; k < 4; k++)
			{
				p_Data->m_Out_Fish[k] = Rand_Int(6)+1;
				//	중복 검사
				t_TF = true;
				while (t_TF) 
				{
					t_TF = false;
					for(int kk = 0; kk < k;kk++)
					{
						if(p_Data->m_Out_Fish[kk] == p_Data->m_Out_Fish[k])
						{
							//	다음 번호 선정
							p_Data->m_Out_Fish[k] = (p_Data->m_Out_Fish[k])%6 + 1;
							//	첨부터 다시 검사
							t_TF = true;
							kk = k;
						}
					}
				}
			}
			return 1;
		}
	}
	// 모든 문제 완료
	p_Data->m_Current_Count = p_Data->m_Max_Count;
	return 2;
}

//	문항 체크
int	FG_Player::Check_Put_Qz_An(FS_Playing_Set *p_Data,int p_Number)
{
	if(p_Data == NULL)
		return 0;
	for(int k = 0; k < 4; k++)
	{
		if(p_Data->m_Out_Fish[k] == (p_Number+1))
		{
			p_Data->m_Out_Fish[k] = 0;
			return 2+k;
		}
	}
	//	모두다 출력되었는지 확인
	int	t_count = p_Data->m_Out_Fish[0] + p_Data->m_Out_Fish[1] + p_Data->m_Out_Fish[2] + p_Data->m_Out_Fish[3];
	if(t_count == 0)
	{
		return 1;
	}
	return 0;
}

//	퀴즈 문장 출력
bool	FG_Player::Out_Qz_String(bool p_NULL)
{
	if(m_TexLib_Text == NULL)
		return false;
	if(m_Qz == NULL)
		return false;
	if(m_Info.m_Play.m_Out_Count >= 100)
		return false;
	if(p_NULL)
	{	
		m_TexLib_Text->Update_Tex_String(1,(char *)" ",0,0,0,255);
		return true;
	}
	switch(m_Info.m_Play.m_Info.m_Type)
	{
		case 1:
		{
			if(m_Qz->m_Level1 != NULL)
			{
				m_TexLib_Text->Update_Tex_String(1,m_Qz->m_Level1->m_Quz[m_Info.m_Play.m_Out_Count],0,0,0,255);
				for(int i = 0 ; i < 4; i++)
				{
					m_TexLib_Text->Update_Tex_String(2+i,m_Qz->m_Level1->m_Ans[m_Info.m_Play.m_Out_Count][i],0,0,0,255);
				}
			}
			break;
		}
		case 2:
		{
			if(m_Qz->m_Level2 != NULL)
			{
				m_TexLib_Text->Update_Tex_String(1,m_Qz->m_Level2->m_Quz[m_Info.m_Play.m_Out_Count],0,0,0,255);
				for(int i = 0 ; i < 4; i++)
				{
					m_TexLib_Text->Update_Tex_String(2+i,m_Qz->m_Level2->m_Ans[m_Info.m_Play.m_Out_Count][i],0,0,0,255);
				}
			}
			break;
		}
		case 3:
		{
			if(m_Qz->m_Level3 != NULL)
			{
				m_TexLib_Text->Update_Tex_String(1,m_Qz->m_Level3->m_Quz[m_Info.m_Play.m_Out_Count],0,0,0,255);
				for(int i = 0 ; i < 4; i++)
				{
					m_TexLib_Text->Update_Tex_String(2+i,m_Qz->m_Level3->m_Ans[m_Info.m_Play.m_Out_Count][i],0,0,0,255);
				}
			}
			break;
		}
		case 4:
		{
			if(m_Qz->m_Level4 != NULL)
			{
				m_TexLib_Text->Update_Tex_String(1,m_Qz->m_Level4->m_Quz[m_Info.m_Play.m_Out_Count],0,0,0,255);
				for(int i = 0 ; i < 4; i++)
				{
					m_TexLib_Text->Update_Tex_String(2+i,m_Qz->m_Level4->m_Ans[m_Info.m_Play.m_Out_Count][i],0,0,0,255);
				}
			}
			break;
		}
		case 5:
		{
			if(m_Qz->m_Level5 != NULL)
			{
				m_TexLib_Text->Update_Tex_String(1,m_Qz->m_Level5->m_Quz[m_Info.m_Play.m_Out_Count],0,0,0,255);
				for(int i = 0 ; i < 4; i++)
				{
					m_TexLib_Text->Update_Tex_String(2+i,m_Qz->m_Level5->m_Ans[m_Info.m_Play.m_Out_Count][i],0,0,0,255);
				}
			}
			break;
		}
		default:
		{
			m_TexLib_Text->Update_Tex_String(1,(char *)" ",0,0,0,255);
			break;
		}
	}
	return false;
}

//	본인 데이터 업데이트
bool	FG_Player::My_Data_Update()
{
	int t_Level = m_Info.m_Play.m_Info.m_Type;
	if(t_Level == 0)
		return false;
	if(t_Level > 5)
		return false;
	t_Level = t_Level-1;
	// 업데이트 확인
	if(m_Info.m_My_Point[t_Level].m_Score <  m_Info.m_Play.m_Info.m_Score)
	{
		//	변경
		m_Info.m_My_Point[t_Level].m_Type = m_Info.m_Play.m_Info.m_Type;
		m_Info.m_My_Point[t_Level].m_Score = m_Info.m_Play.m_Info.m_Score;
		m_Info.m_My_Point[t_Level].m_Yes_Count = m_Info.m_Play.m_Info.m_Yes_Count;
		m_Info.m_My_Point[t_Level].m_No_Count = m_Info.m_Play.m_Info.m_No_Count;
		// 정답이 50개 이상이면 다음 레벨 도전 가능
		if(m_Info.m_My_Point[t_Level].m_Yes_Count >= 50)
		{
			if(m_Info.m_Level < (m_Info.m_My_Point[t_Level].m_Type + 1))
			{
				m_Info.m_Level = m_Info.m_My_Point[t_Level].m_Type + 1;
				if(m_Info.m_Level > 5)
					m_Info.m_Level = 5;
			}
		}
		//	파일 저장
		Save_User_Data();
	}
	return true;
}

//	유저 데이터 저장
bool	FG_Player::Save_User_Data()
{
	// 저장 경로 얻기
	string	t_Path = F_IOS_File::Get_Document_Path();
	char	t_File_Name[512];
	sprintf(t_File_Name,"%s/Save.gdt",t_Path.c_str());
	
	FILE *t_File = fopen(t_File_Name,"w");
	if(t_File == NULL)
		return	false;
	int	t_Ver = 1;
	//	버전 저장
	fwrite(&t_Ver,4,1,t_File);
	//	게임 진행 정보 저장
	if(m_Info.m_Level == 0)
	{
		m_Info.m_Level = 1;
	}
	fwrite(&m_Info,sizeof(FS_Play_Info),1,t_File);
	
	fclose(t_File);
	t_File = NULL;
	return true;
}

//	유저 데이터 읽기
bool	FG_Player::Load_User_Data()
{
	//	읽기 경로 얻기
	string	t_Path = F_IOS_File::Get_Document_Path();
	char	t_File_Name[512];
	sprintf(t_File_Name,"%s/Save.gdt",t_Path.c_str());
	FILE *t_File = fopen(t_File_Name,"r");
	if(t_File == NULL)
		return	false;
	int	t_Ver = 0;
	// 버전 읽기
	fread(&t_Ver,4,1,t_File);
	if(t_Ver == 1)
	{
		fread(&m_Info,sizeof(FS_Play_Info),1,t_File);
	}
	fclose(t_File);
	t_File = NULL;
	return true;
}

int		FG_Player::Get_User_Level()
{
	if(m_Info.m_Level == 0)
	{
		m_Info.m_Level = 1;
	}
	/*
	// 치트
	m_Info.m_Level = 5;
	for(int i = 0; i < 5; i++)
	{
		m_Info.m_My_Point[i].m_Type = 1+i;
		m_Info.m_My_Point[i].m_Score = 2000+Rand_Int(500);
		m_Info.m_My_Point[i].m_Yes_Count = 100;
		m_Info.m_My_Point[i].m_No_Count = 6+Rand_Int(10);
	}
	
	*/
	return m_Info.m_Level;
}

int		FG_Player::Get_User_Score(int p_Level)
{
	if(p_Level > 5)
		return 0;
	if(p_Level < 1)
		return 0;
	return m_Info.m_My_Point[p_Level - 1].m_Score;
}

int		FG_Player::Get_User_Yes_Count(int p_Level)
{
	if(p_Level > 5)
		return 0;
	if(p_Level < 1)
		return 0;
	return m_Info.m_My_Point[p_Level - 1].m_Yes_Count;
}

int		FG_Player::Get_User_No_Count(int p_Level)
{
	if(p_Level > 5)
		return 0;
	if(p_Level < 1)
		return 0;
	return m_Info.m_My_Point[p_Level - 1].m_No_Count;
}

//	콤보 이펙트 출력
bool	FG_Player::Out_Put_Combo()
{
	if(m_Main_Effect == NULL)
		return false;
	
	// 찾기
	FS_2DEffect_Info *t_Out = m_Main_Effect->Out_Effect(3);
	if(t_Out != NULL)
	{
		m_Main_Effect->Set_EF_Start_Pos(t_Out,
										0.0f,
										0.0f,
										100.0f);
		//	확대 이팩트
		m_Main_Effect->Set_EF_Move1_Param(t_Out,0.2f,2.0f,0.0f,0.0f,3);
	}
	t_Out = m_Main_Effect->Out_Effect(4);
	if(t_Out != NULL)
	{
		m_Main_Effect->Set_EF_Start_Pos(t_Out,
										0.0f,
										30.0f,
										100.0f);
		m_Main_Effect->Set_EF_Number(t_Out,m_Combo_Count);
		//	확대 이팩트
		m_Main_Effect->Set_EF_Move1_Param(t_Out,0.2f,2.0f,0.0f,0.0f,3);
	}
	
	return true;
}

//	숫자 이팩트
bool	FG_Player::Out_Put_Number_Effect(int p_Type,int p_Number,float p_X,float p_Y)
{
	if(m_Main_Effect == NULL)
		return false;
	FS_2DEffect_Info *t_Out = NULL;
	if(p_Type == 0)
	{
		t_Out = m_Main_Effect->Out_Effect(5);
	}
	else
	{
		t_Out = m_Main_Effect->Out_Effect(6);
	}
	if(t_Out != NULL)
	{
		m_Main_Effect->Set_EF_Start_Pos(t_Out,
										p_X,
										p_Y,
										100.0f);
		m_Main_Effect->Set_EF_Number(t_Out,p_Number);
		//	확대 이팩트
		m_Main_Effect->Set_EF_Move1_Param(t_Out,0.5f,2.0f,0.0f,0.0f,3);
	}
	return true;
}
