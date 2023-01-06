/*
 *  FG_Game_RF.cpp
 *  Raising Fish 게임 메인 처리 및 데이터 
 *
 *  Created by forthen on 11. 4. 19..
 *  Copyright 2011 forthen. All rights reserved.
 *
 */

#include "FG_Game_RF.h"

//	생성 함수
FG_Game_RF::FG_Game_RF()
{
	m_Scene_Type = 0;
	m_Next_Scene_Type = 0;
	m_Help_Page = 0;

	m_Time = 0.0f;
	m_Sub_Time = 0.0f;
	m_Load_TF = 0;
	
	m_Screen_TF = false;
	m_Screen_Alpha = 1.0f;
	
	m_TexLib = NULL;
	m_TexLib_Text = NULL;
	m_Sprite = NULL;
	m_Text_Out = NULL;
	m_Screen = NULL;
	m_Effect = NULL;
	m_player = NULL;
	m_UI = NULL;
	
	m_Mouse_Event = 0;
	//	사운드 초기화
	F_IO_Wave::Init_Sound();
}

//	삭제 함수
FG_Game_RF::~FG_Game_RF()
{
	Delete_Sprite();
	Delete_TexLib();
	Delete_RSprite();
	Delete_Effect();
	if(m_player != NULL)
	{
		delete m_player;
		m_player = NULL;
	}
	//	사운드 삭제
	F_IO_Wave::Release_Sound();
}

//	초기화 함수
bool	FG_Game_RF::Init()
{
	Load_TexLib();
	Load_Sprite();
	//	이펙트 생성
	Load_Effect();
	if(m_Screen == NULL)
	{
		m_Screen = new F_GL_RSprite;
		m_Screen->Init(m_Effect);
	}
	//	UI 모듈
	if(m_UI == NULL)
	{
		m_UI = new F_GL_RSprite;
	}
	//	메인 플레이어 생성
	if(m_player == NULL)
	{
		m_player = new FG_Player;
		//	전역 이펙트 지정
		m_player->Set_Effect(m_Effect);
		//	케릭터 모델 설정 (시작 단계예 따라서 물고기 변경
		m_player->Init_Fish(1,m_Sprite->Find_Data(9));
		//	유저 저장 정보 읽기
		m_player->Set_Fishs(m_Sprite->Find_Data(6));
		//	문제 데이터 읽기
		m_player->Load_Qz();
		//	유저 게임 진행 결과 읽기
		m_player->Load_User_Data();
	}
	//	배경 플레 진행
	F_IO_Wave::Back_Sound_OnOff(true,0.05f);
	return true;
}

/*
 데이터 초기화 함수
 */

bool	FG_Game_RF::Init_Text_Sprite()
{
	
	if(m_TexLib_Text == NULL)
	{
		m_TexLib_Text = new F_GL_TexLib;
		if(m_TexLib_Text != NULL)
		{
			//	원본 보관 안함
			m_TexLib_Text->Init(1);
			
			char	t_Temp[10] = "테스트";
			//	문제 출제
			m_TexLib_Text->Insert_Tex_String(1,t_Temp,0,0,0,255);
			//	문항 출력
			m_TexLib_Text->Insert_Tex_String(2,t_Temp,0,0,0,255);
			m_TexLib_Text->Insert_Tex_String(3,t_Temp,0,0,0,255);
			m_TexLib_Text->Insert_Tex_String(4,t_Temp,0,0,0,255);
			m_TexLib_Text->Insert_Tex_String(5,t_Temp,0,0,0,255);
		}
	}
	
	if((m_Text_Out == NULL)&&(m_TexLib_Text != NULL))
	{
		m_Text_Out = new F_GL_Sprite;
		if(m_Text_Out != NULL)
		{
			m_Text_Out->Init(m_TexLib_Text);
			FS_Sprite *t_Sprite =NULL;
			for(int i = 0; i < 5;i++)
			{
				t_Sprite = m_Text_Out->Insert(i+1,i+1);
				if(t_Sprite != NULL)
				{
					m_Text_Out->Set_WH(t_Sprite,128,16);
					m_Text_Out->Set_UV_GridXY(t_Sprite,1.0f,1.0f,1,1,1);
					m_Text_Out->Set_DTime(t_Sprite,0.0f);
					m_Text_Out->Set_Vertex(t_Sprite);
					m_Text_Out->Set_Rect(t_Sprite,-64,8,128,16);
					t_Sprite = NULL;
				}
			}
		}
		//	출력용 문자열 지정
		if(m_player != NULL)
		{
			m_player->Set_Text_Out(m_Text_Out,m_TexLib_Text,m_UI);
		}
	}
	return true;
}

//	텍스처 라이브러리 설정
bool	FG_Game_RF::Load_TexLib()
{
	if(m_TexLib != NULL)
		return false;
	
	//	텍스처 생성
	m_TexLib = new F_GL_TexLib;
	if(m_TexLib != NULL)
	{
		//	원본 보관 안함
		m_TexLib->Init(1);
		//	텍스처 추가
		m_TexLib->Insert_Tex(1,"init_480_320");
		m_TexLib->Insert_Tex(2,"vocacity");
		m_TexLib->Insert_Tex(3,"Player_Fish");
		m_TexLib->Insert_Tex(4,"bubble");
		m_TexLib->Insert_Tex(5,"back512");
		m_TexLib->Insert_Tex(6,"Fishs");
		m_TexLib->Insert_Tex(7,"effect");
		m_TexLib->Insert_Tex(8,"window1");
		m_TexLib->Insert_Tex(9,"Player_Fish_sky");
		m_TexLib->Insert_Tex(10,"Player_Fish_blue");
		m_TexLib->Insert_Tex(11,"Player_Fish_Yellow");
		m_TexLib->Insert_Tex(12,"Player_Fish_2");
		m_TexLib->Insert_Tex(13,"Player_Fish_Rage");
		
		m_TexLib->Insert_Tex(20,"menu_icon");
		m_TexLib->Insert_Tex(21,"menu_icon2");
		m_TexLib->Insert_Tex(22,"Number");
		m_TexLib->Insert_Tex(23,"water_a");
		m_TexLib->Insert_Tex(24,"bord");
		m_TexLib->Insert_Tex(25,"q1");
		m_TexLib->Insert_Tex(26,"q2");
		m_TexLib->Insert_Tex(27,"score");
		m_TexLib->Insert_Tex(28,"exit");
		m_TexLib->Insert_Tex(29,"Rank");
		m_TexLib->Insert_Tex(30,"Help");
		m_TexLib->Insert_Tex(31,"result");
		m_TexLib->Insert_Tex(32,"medal");
		m_TexLib->Insert_Tex(33,"Rank_Menu");
		m_TexLib->Insert_Tex(34,"Rank_name");
		m_TexLib->Insert_Tex(35,"help_all");
		m_TexLib->Insert_Tex(36,"combo");
		m_TexLib->Insert_Tex(37,"combo_num");
	}
	return true;
}
//	텍스처 라이브러리 삭제
bool	FG_Game_RF::Delete_TexLib()
{
	if(m_TexLib != NULL)
	{
		delete m_TexLib;
		m_TexLib = NULL;
	}
	if(m_TexLib_Text != NULL)
	{
		delete m_TexLib_Text;
		m_TexLib_Text = NULL;
	}
	return true;
}

//	스프라이트 데이터 설정
bool	FG_Game_RF::Load_Sprite()
{
	Delete_Sprite();
	//	스프라이트 데이터 생성
	m_Sprite = new F_GL_Sprite;
	if(m_Sprite == NULL)
		return false;
	if(m_TexLib == NULL)
		return false;
	//	사용 라이브러리 지정
	m_Sprite->Init(m_TexLib);
	
	//	스프라이트 추가
	FS_Sprite *t_Sprite = NULL;
	//	1번 이미지 로딩 배경 그림
	t_Sprite = m_Sprite->Insert(1,1);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,480,320);
		m_Sprite->Set_UV_GridXY(t_Sprite,480.0f/512.0f,320.0f/512.0f,1,1,1);
		m_Sprite->Set_DTime(t_Sprite,0.0f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-240,160,480,320);
		
		t_Sprite = NULL;
	}
	//	2번 로고
	t_Sprite = m_Sprite->Insert(2,2);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,256,128);
		m_Sprite->Set_UV_GridXY(t_Sprite,1.0f,1.0f,1,1,1);
		m_Sprite->Set_DTime(t_Sprite,0.0f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-128,64,256,128);
		
		t_Sprite = NULL;
	}
	//	3번 도움말 윈도우
	t_Sprite = m_Sprite->Insert(3,8);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,406,286);
		m_Sprite->Set_UV_GridXY(t_Sprite,406.0f/512.0f,286.0f/512.0f,1,1,1);
		m_Sprite->Set_DTime(t_Sprite,0.0f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-203,143,406,286);
		
		t_Sprite = NULL;
	}
	
	//	4번 스프라이트 설정 물방울
	t_Sprite = m_Sprite->Insert(4,4);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,40,40);
		m_Sprite->Set_UV_GridXY(t_Sprite,40.0f/64.0f,40.0f/64.0f,1,1,1);
		m_Sprite->Set_DTime(t_Sprite,0.0f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-20,20,40,40);
		t_Sprite = NULL;
	}
	
	//	5번 게임 배경 화면
	t_Sprite = m_Sprite->Insert(5,5);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,512,390);
		m_Sprite->Set_UV_GridXY(t_Sprite,1.0f,390.0f/512.0f,1,1,1);
		m_Sprite->Set_DTime(t_Sprite,0.0f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-256,195,512,390);
		t_Sprite = NULL;
	}
	//	6번 게임 물고기 이미지
	t_Sprite = m_Sprite->Insert(6,6);
	if(t_Sprite)
	{
		m_Sprite->Set_WH(t_Sprite,170,80);
		m_Sprite->Set_UV_GridXY(t_Sprite,170.0f/512.0f,80.0f/512.0f,3,6,16);
		m_Sprite->Set_DTime(t_Sprite,0.0f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-85,40,170,80);
		t_Sprite = NULL;
	}
	//	7번 이펙트 이미지
	t_Sprite = m_Sprite->Insert(7,7);
	if(t_Sprite)
	{
		m_Sprite->Set_WH(t_Sprite,64,64);
		m_Sprite->Set_UV_GridXY(t_Sprite,64.0f/256.0f,64.0f/256.0f,4,3,9);
		m_Sprite->Set_DTime(t_Sprite,0.1f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-32,32,64,64);
		t_Sprite = NULL;
	}
	
	//	8번 버튼 물고기
	t_Sprite = m_Sprite->Insert(8,9);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,100,100);
		m_Sprite->Set_UV_GridXY(t_Sprite,100.0f/512.0f,100.0f/512.0f,3,3,9);
		m_Sprite->Set_DTime(t_Sprite,0.3f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-40,40,80,80);
		t_Sprite = NULL;
	}
	
	//	9번 메인 케릭터 1
	t_Sprite = m_Sprite->Insert(9,3);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,100,100);
		m_Sprite->Set_UV_GridXY(t_Sprite,100.0f/512.0f,100.0f/512.0f,3,3,9);
		m_Sprite->Set_DTime(t_Sprite,0.3f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-36,38,48,78);
		t_Sprite = NULL;
	}
	
	//	10번 메인 케릭터 2
	t_Sprite = m_Sprite->Insert(10,10);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,100,100);
		m_Sprite->Set_UV_GridXY(t_Sprite,100.0f/512.0f,100.0f/512.0f,3,3,9);
		m_Sprite->Set_DTime(t_Sprite,0.3f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-36,38,48,78);
		t_Sprite = NULL;
	}
	
	//	11번 메인 케릭터 3
	t_Sprite = m_Sprite->Insert(11,11);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,100,100);
		m_Sprite->Set_UV_GridXY(t_Sprite,100.0f/512.0f,100.0f/512.0f,3,3,9);
		m_Sprite->Set_DTime(t_Sprite,0.3f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-36,38,48,78);
		t_Sprite = NULL;
	}
	//	12번 메인 케릭터 4
	t_Sprite = m_Sprite->Insert(12,12);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,100,100);
		m_Sprite->Set_UV_GridXY(t_Sprite,100.0f/512.0f,100.0f/512.0f,3,3,9);
		m_Sprite->Set_DTime(t_Sprite,0.3f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-36,38,48,78);
		t_Sprite = NULL;
	}
	//	13번 메인 케릭터 5
	t_Sprite = m_Sprite->Insert(13,13);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,100,100);
		m_Sprite->Set_UV_GridXY(t_Sprite,100.0f/512.0f,100.0f/512.0f,3,3,9);
		m_Sprite->Set_DTime(t_Sprite,0.3f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-36,38,48,78);
		t_Sprite = NULL;
	}
	
	//	20번 메뉴
	t_Sprite = m_Sprite->Insert(20,20);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,128,64);
		m_Sprite->Set_UV_GridXY(t_Sprite,128.0f/256.0f,64.0f/256.0f,2,4,8);
		m_Sprite->Set_DTime(t_Sprite,0.0f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-64,32,128,64);
		t_Sprite = NULL;
	}
	//	21번 메뉴2
	t_Sprite = m_Sprite->Insert(21,21);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,128,64);
		m_Sprite->Set_UV_GridXY(t_Sprite,128.0f/256.0f,64.0f/256.0f,2,2,3);
		m_Sprite->Set_DTime(t_Sprite,0.0f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-64,32,128,64);
		t_Sprite = NULL;
	}
	//	22번 번호
	t_Sprite = m_Sprite->Insert(22,22);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,20,20);
		m_Sprite->Set_UV_GridXY(t_Sprite,20.0f/256.0f,20.0f/128.0f,10,4,40);
		m_Sprite->Set_DTime(t_Sprite,0.0f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-10,10,20,20);
		t_Sprite = NULL;
	}
	//	23번 물풀
	t_Sprite = m_Sprite->Insert(23,23);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,64,88);
		m_Sprite->Set_UV_GridXY(t_Sprite,64.0f/128.0f,88.0f/128.0f,1,1,1);
		m_Sprite->Set_DTime(t_Sprite,0.0f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-32,44,64,88);
		t_Sprite = NULL;
	}
	//	24번 출력 창
	t_Sprite = m_Sprite->Insert(24,24);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,242,64);
		m_Sprite->Set_UV_GridXY(t_Sprite,242.0f/256.0f,64.0f/64.0f,1,1,1);
		m_Sprite->Set_DTime(t_Sprite,0.0f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-121,32,242,64);
		t_Sprite = NULL;
	}
	//	25번 문제 조건
	t_Sprite = m_Sprite->Insert(25,25);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,256,64);
		m_Sprite->Set_UV_GridXY(t_Sprite,1.0f,1.0f,1,1,1);
		m_Sprite->Set_DTime(t_Sprite,0.0f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-128,32,256,64);
		t_Sprite = NULL;
	}
	//	26번 문제 조건 (동의어 문제)
	t_Sprite = m_Sprite->Insert(26,26);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,256,64);
		m_Sprite->Set_UV_GridXY(t_Sprite,1.0f,1.0f,1,1,1);
		m_Sprite->Set_DTime(t_Sprite,0.0f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-128,32,256,64);
		t_Sprite = NULL;
	}
	//	27 스코어 이미지
	t_Sprite = m_Sprite->Insert(27,27);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,256,64);
		m_Sprite->Set_UV_GridXY(t_Sprite,1.0f,1.0f,1,1,1);
		m_Sprite->Set_DTime(t_Sprite,0.0f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-128,32,256,64);
		t_Sprite = NULL;
	}
	//	28 게임 종료
	t_Sprite = m_Sprite->Insert(28,28);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,64,32);
		m_Sprite->Set_UV_GridXY(t_Sprite,1.0f,1.0f,1,1,1);
		m_Sprite->Set_DTime(t_Sprite,0.0f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-32,16,64,32);
		t_Sprite = NULL;
	}
	//	29 업적 글자 이미지
	t_Sprite = m_Sprite->Insert(29,29);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,128,64);
		m_Sprite->Set_UV_GridXY(t_Sprite,1.0f,1.0f,1,1,1);
		m_Sprite->Set_DTime(t_Sprite,0.0f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-64,32,128,64);
		t_Sprite = NULL;
	}
	//	30 도움말 글자 이미지
	t_Sprite = m_Sprite->Insert(30,30);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,128,64);
		m_Sprite->Set_UV_GridXY(t_Sprite,1.0f,1.0f,1,1,1);
		m_Sprite->Set_DTime(t_Sprite,0.0f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-64,32,128,64);
		t_Sprite = NULL;
	}
	//	31 결과 글자 이미지
	t_Sprite = m_Sprite->Insert(31,31);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,128,64);
		m_Sprite->Set_UV_GridXY(t_Sprite,1.0f,1.0f,1,1,1);
		m_Sprite->Set_DTime(t_Sprite,0.0f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-64,32,128,64);
		t_Sprite = NULL;
	}
	//	32 메달
	t_Sprite = m_Sprite->Insert(32,32);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,30,32);
		m_Sprite->Set_UV_GridXY(t_Sprite,30.0f/128.0f,1.0f,3,1,3);
		m_Sprite->Set_DTime(t_Sprite,0.0f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-15,16,30,32);
		t_Sprite = NULL;
	}
	//	33 랭크 메뉴
	t_Sprite = m_Sprite->Insert(33,33);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,80,30);
		m_Sprite->Set_UV_GridXY(t_Sprite,80.0f/256.0f,30.0f/64.0f,3,2,6);
		m_Sprite->Set_DTime(t_Sprite,0.0f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-40,15,80,30);
		t_Sprite = NULL;
	}
	//	34 랭크 이름
	t_Sprite = m_Sprite->Insert(34,34);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,80,20);
		m_Sprite->Set_UV_GridXY(t_Sprite,80.0f/256.0f,20.0f/64.0f,3,2,5);
		m_Sprite->Set_DTime(t_Sprite,0.0f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-40,10,80,20);
		t_Sprite = NULL;
	}
	
	//	35 전체 도움말
	t_Sprite = m_Sprite->Insert(35,35);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,500,330);
		m_Sprite->Set_UV_GridXY(t_Sprite,500.0f/1024.0f,330.0f/1024.0f,2,3,6);
		m_Sprite->Set_DTime(t_Sprite,0.0f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-250,165,500,330);
		t_Sprite = NULL;
	}
	
	//	36 콤보 문자
	t_Sprite = m_Sprite->Insert(36,36);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,128,64);
		m_Sprite->Set_UV_GridXY(t_Sprite,1.0f,1.0f,1,1,1);
		m_Sprite->Set_DTime(t_Sprite,0.0f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-64,32,128,64);
		t_Sprite = NULL;
	}
	
	//	37 콤보 숫자
	t_Sprite = m_Sprite->Insert(37,37);
	if(t_Sprite != NULL)
	{
		m_Sprite->Set_WH(t_Sprite,20,32);
		m_Sprite->Set_UV_GridXY(t_Sprite,20.0f/256.0f,1.0f,10,1,10);
		m_Sprite->Set_DTime(t_Sprite,0.0f);
		m_Sprite->Set_Vertex(t_Sprite);
		m_Sprite->Set_Rect(t_Sprite,-10,16,20,32);
		t_Sprite = NULL;
	}
	//m_TexLib->Insert_Tex(36,"combo");
	//m_TexLib->Insert_Tex(37,"combo_num");
	return true;
}
//	스프라이트 데이터 삭제
bool	FG_Game_RF::Delete_Sprite()
{
	if(m_Sprite != NULL)
	{
		delete m_Sprite;
		m_Sprite = NULL;
	}
	if(m_Text_Out != NULL)
	{
		delete m_Text_Out;
		m_Text_Out = NULL;
	}
	return true;
}

//	렌더링 스프라이트 설정
bool	FG_Game_RF::Set_Screen_Date(int p_Type)
{
	if(m_Screen == NULL)
		return false;
	if(m_Sprite == NULL)
		return false;
	if(m_UI == NULL)
		return false;
	//	장면 구성에 필요한 정보 설정
	switch(p_Type)
	{
		case 1:
		{
			m_UI->Release_List();
			//	기존 스크린 정보 초기화
			m_Screen->Release_List();
			//	렌더링 이팩트 삭제.
			m_Effect->Stop_Out_Effect();
			//	뒷배경
			FS_RSprite *t_Sprite = m_Screen->Insert(1,m_Sprite->Find_Data(1));
			if(t_Sprite != NULL)
			{
				m_Screen->Set_RS_Type(t_Sprite,0);
				m_Screen->Set_View_Type(t_Sprite,1);
				m_Screen->Set_RS_Pos(t_Sprite,0.0f,0.0f,-100.0f);
			}
			//	제목
			t_Sprite = m_Screen->Insert(2,m_Sprite->Find_Data(2));
			if(t_Sprite != NULL)
			{
				//	이동 이미지
				m_Screen->Set_RS_Type(t_Sprite,2);
				m_Screen->Set_View_Type(t_Sprite,1);
				m_Screen->Set_RS_Pos(t_Sprite,0.0f,85.0f,-55.0f);
				
				m_Screen->Set_RS_Move1_Param(t_Sprite,0.0f,128.0f,0.0f,100.0f,11);	// 추가 이동 소모형
			}
			//	버튼 (메뉴)
			bool	t_Continue = 0;
			if(m_player != NULL)
			{
				if(m_player->m_Info.m_Continue == 1)
				{
					t_Continue = true;
				}
			}
			for(int i = 0; i < 3;i++)
			{
				if(t_Continue == 0)
				{
					if(i==0)
					{
						//	이어서 하기 건너뜀
						i = 1;
					}
				}
				//	8 번 붕어 사용
				t_Sprite = m_Screen->Insert(i+3,m_Sprite->Find_Data(8));
				if(t_Sprite != NULL)
				{	
					m_Screen->Set_RS_Type(t_Sprite,1);
					m_Screen->Set_Button_OnOff(t_Sprite,1);
					m_Screen->Set_View_Type(t_Sprite,1);
					m_Screen->Set_RS_Pos(t_Sprite,-60.0f + (i+1)*80.0f,-120.0f,-50.0f);
					m_Screen->Set_RS_Scale(t_Sprite,1.0f,0.7f,1.0f);
					
					if(i == 0)
					{
						// 이어서 하기 우선 기능 없음
						m_Screen->Set_Button_Return(t_Sprite,600);
					}
					//	10 업적 ,20 도움말 메뉴 코드
					else
					{
						m_Screen->Set_Button_Return(t_Sprite,10+(i-1)*10);
					}
					m_Screen->Set_Scale_F(t_Sprite,0.8f);
					m_Screen->Set_RS_Move1_Param(t_Sprite,600.0f + (i+1)*80.0f, 0.0f,0.0f,300.0f,11);	// 추가 이동 소모형
					m_Screen->Set_RS_Move2_Param(t_Sprite,0.0f, 1.0f,0.0f, 3.0f,10);	// 물고기 재자리 튼들림
					m_Screen->Set_RS_Move3_Param(t_Sprite,0.0f,0.0f,0.0f,0.0f,0);
					m_Screen->Set_RS_Effect_ID(t_Sprite,1);
					m_Screen->Set_RS_Z_Rot(t_Sprite,0);
					
					//	서브 스프라이트 설정
					m_Screen->Set_Sub_Sprite(i+3,m_Sprite->Find_Data(20));
					m_Screen->Set_Sub_Sprite_Pos(i+3,20.0f,-20.0f,20.0f,0.8f);
				}
			}
			//	서브 스프라이트 유형
			m_Screen->Set_Sub_Sprite_Type(3, 1, 0, 1);
			m_Screen->Set_Sub_Sprite_Type(4, 1, 0, 0);
			m_Screen->Set_Sub_Sprite_Type(5, 1, 1, 0);
			
			//	플레이 버튼
			int	t_User_Level = m_player->Get_User_Level();
			float	t_Scale_f = 1.0f;
			for(int i = 0; i < 5;i++)
			{
				t_Sprite = m_Screen->Insert(i+10,m_Sprite->Find_Data(9 + i));
				//	스프라이트
				if(t_Sprite != NULL)
				{	
					m_Screen->Set_RS_Type(t_Sprite,1);
					m_Screen->Set_View_Type(t_Sprite,1);
					m_Screen->Set_RS_Scale(t_Sprite,1.0f,0.7f,1.0f);
					//	100 게임 진행 화면
					m_Screen->Set_Button_Return(t_Sprite,100 + i*100);
					m_Screen->Set_RS_Pos(t_Sprite,-180.0f,-120.0f + 60.0f*i,-50.0f);
					//	유저의 달성 레벨에 따라서
					if(i < t_User_Level)
					{
						m_Screen->Set_Button_OnOff(t_Sprite,1);
						t_Scale_f = ((float)m_player->Get_User_Yes_Count(i+1))/200.0f;
						m_Screen->Set_Scale_F(t_Sprite,0.6f + t_Scale_f);
						//	서브 스프라이트 설정
						m_Screen->Set_Sub_Sprite(i+10,m_Sprite->Find_Data(20));
						m_Screen->Set_Sub_Sprite_Pos(i+10,20.0f,-20.0f,20.0f,0.8f);
					}
					else
					{
						//	버튼 비활성
						m_Screen->Set_Button_OnOff(t_Sprite,0);
						m_Screen->Set_Scale_F(t_Sprite,0.3f);	
						//	서브 스프라이트 설정
						m_Screen->Set_Sub_Sprite(i+10,NULL);
						m_Screen->Set_Sub_Sprite_Pos(i+10,20.0f,-20.0f,20.0f,0.8f);
					}
					m_Screen->Set_RS_Move1_Param(t_Sprite,600.0f, 0.0f,0.0f,300.0f,11);
					m_Screen->Set_RS_Move2_Param(t_Sprite,0.0f, 1.0f,0.0f, 3.0f,10);	// 물고기 재자리 튼들림
					m_Screen->Set_RS_Move3_Param(t_Sprite,0.0f,0.0f,0.0f,0.0f,0);
					m_Screen->Set_RS_Effect_ID(t_Sprite,1);
					m_Screen->Set_RS_Z_Rot(t_Sprite,0);
				}
			}
			//	서브 스프라이트 유형
			m_Screen->Set_Sub_Sprite_Type(10, 1, 1, 1);
			m_Screen->Set_Sub_Sprite_Type(11, 1, 0, 2);
			m_Screen->Set_Sub_Sprite_Type(12, 1, 1, 2);
			m_Screen->Set_Sub_Sprite_Type(13, 1, 0, 3);
			m_Screen->Set_Sub_Sprite_Type(14, 1, 1, 3);
			
			//  악세사리 물고기
			for(int i = 0; i < 6;i++)
			{
				t_Sprite = m_Screen->Insert(i+15,m_Sprite->Find_Data(8 + i));
				//	스프라이트
				if(t_Sprite != NULL)
				{	
					m_Screen->Set_RS_Type(t_Sprite,1);
					m_Screen->Set_View_Type(t_Sprite,1);
					m_Screen->Set_RS_Scale(t_Sprite,1.0f,0.7f,1.0f);
					m_Screen->Set_Button_Return(t_Sprite,0);
					//	버튼 비활성
					m_Screen->Set_Button_OnOff(t_Sprite,0);
					m_Screen->Set_RS_Pos(t_Sprite,260,0.0f,-50.0f);
					m_Screen->Set_Scale_F(t_Sprite,0.3f);
					m_Screen->Set_RS_Move1_Param(t_Sprite,0.0f,0.0f,0.0f,0.0f,0);
					m_Screen->Set_RS_Move2_Param(t_Sprite,0.0f, 1.0f,0.0f, 3.0f,10);	// 물고기 재자리 튼들림
					m_Screen->Set_RS_Move3_Param(t_Sprite,0.0f,0.0f,0.0f,0.0f,0);
					m_Screen->Set_RS_Effect_ID(t_Sprite,1);
					m_Screen->Set_RS_Z_Rot(t_Sprite,0);
				}
			}
			
			// 물방을 이팩트
			for(int i = 100; i < 108;i++)
			{
				t_Sprite = m_Screen->Insert(i,m_Sprite->Find_Data(4));
				if(t_Sprite != NULL)
				{
					//	이동 이미지
					m_Screen->Set_RS_Type(t_Sprite,3);
					m_Screen->Set_View_Type(t_Sprite,1);
					m_Screen->Set_RS_Pos(t_Sprite,-50.0f+(float)(rand()%100),-20.0f,-60.0f);
				
					m_Screen->Set_RS_Move1_Param(t_Sprite,0.0f,200.0f,0.0f,20.0f,9);	// 물방을 상승
					m_Screen->Set_RS_Move2_Param(t_Sprite,2.0f,0.0f,0.0f,20.0f,14);	// 불규칙 왕복 운동 X축(최대,결정값,진행시간,시간부기)
					m_Screen->Set_RS_Wait_Count(t_Sprite,100 + 150*(i-100),5);
				}
			}
			t_Sprite = m_Screen->Insert(108,m_Sprite->Find_Data(4));
			if(t_Sprite != NULL)
			{
				//	이동 이미지
				m_Screen->Set_RS_Type(t_Sprite,3);
				m_Screen->Set_View_Type(t_Sprite,1);
				m_Screen->Set_RS_Pos(t_Sprite,-200.0f,-70.0f,-60.0f);
				
				m_Screen->Set_RS_Move1_Param(t_Sprite,0.0f,500.0f,0.0f,20.0f,9);	// 물방을 상승
				m_Screen->Set_RS_Move2_Param(t_Sprite,2.0f,0.0f,0.0f,20.0f,14);	// 불규칙 왕복 운동 X축(최대,결정값,진행시간,시간부기)
				m_Screen->Set_RS_Wait_Count(t_Sprite,300,5);
			}
			t_Sprite = m_Screen->Insert(109,m_Sprite->Find_Data(4));
			if(t_Sprite != NULL)
			{
				//	이동 이미지
				m_Screen->Set_RS_Type(t_Sprite,3);
				m_Screen->Set_View_Type(t_Sprite,1);
				m_Screen->Set_RS_Pos(t_Sprite,200.0f,-70.0f,-60.0f);
				
				m_Screen->Set_RS_Move1_Param(t_Sprite,0.0f,500.0f,0.0f,20.0f,9);	// 물방을 상승
				m_Screen->Set_RS_Move2_Param(t_Sprite,2.0f,0.0f,0.0f,20.0f,14);	// 불규칙 왕복 운동 X축(최대,결정값,진행시간,시간부기)
				m_Screen->Set_RS_Wait_Count(t_Sprite,77,5);
			}
			break;
		}
		case 11:
		{
			//	업적 보기 화면 설정
			m_UI->Release_List();
			//	배경 그림 출력
			m_Screen->Release_List();
			//	렌더링 이팩트 삭제.
			m_Effect->Stop_Out_Effect();
			//	뒷배경
			FS_RSprite *t_Sprite = m_Screen->Insert(1,m_Sprite->Find_Data(1));
			if(t_Sprite != NULL)
			{
				m_Screen->Set_RS_Type(t_Sprite,0);
				m_Screen->Set_View_Type(t_Sprite,1);
				m_Screen->Set_RS_Pos(t_Sprite,0.0f,0.0f,-100.0f);
			}
			//	업적윈도우 출력
			t_Sprite = m_Screen->Insert(2,m_Sprite->Find_Data(3));
			if(t_Sprite != NULL)
			{
				//	이동 이미지
				m_Screen->Set_RS_Type(t_Sprite,2);
				m_Screen->Set_View_Type(t_Sprite,1);
				m_Screen->Set_RS_Pos(t_Sprite,0.0f,0.0f,-55.0f);
				
				m_Screen->Set_RS_Move1_Param(t_Sprite,0.0f,300.0f,0.0f,200.0f,11);	// 추가 이동 소모형
			}
			//	업적 타이틀
			t_Sprite = m_Screen->Insert(4,m_Sprite->Find_Data(29));
			if(t_Sprite != NULL)
			{
				//	이동 이미지
				m_Screen->Set_RS_Type(t_Sprite,2);
				m_Screen->Set_View_Type(t_Sprite,1);
				m_Screen->Set_RS_Pos(t_Sprite,0.0f,140.0f,-50.0f);
				
				m_Screen->Set_RS_Move1_Param(t_Sprite,0.0f,300.0f,0.0f,200.0f,11);	// 추가 이동 소모형
			}
			
			//	돌아가기 버튼 설정.
			t_Sprite = m_Screen->Insert(3,m_Sprite->Find_Data(8));
			if(t_Sprite != NULL)
			{	
				m_Screen->Set_RS_Type(t_Sprite,1);
				m_Screen->Set_Button_OnOff(t_Sprite,1);
				m_Screen->Set_View_Type(t_Sprite,1);
				m_Screen->Set_RS_Pos(t_Sprite,180.0f,-120.0f,-50.0f);
				m_Screen->Set_RS_Scale(t_Sprite,1.0f,0.7f,1.0f);
				//	초기 화면으로
				m_Screen->Set_Button_Return(t_Sprite,12);
				
				m_Screen->Set_RS_Move1_Param(t_Sprite,300.0f,0.0f,0.0f,300.0f,11);	// 추가 이동 소모형
				m_Screen->Set_RS_Move2_Param(t_Sprite,0.0f, 1.0f,0.0f, 3.0f,10);	// 물고기 재자리 튼들림
				m_Screen->Set_RS_Move3_Param(t_Sprite,0.0f,0.0f,0.0f,0.0f,0);
				m_Screen->Set_RS_Effect_ID(t_Sprite,1);
				m_Screen->Set_RS_Z_Rot(t_Sprite,0);
				
				//	서브 스프라이트 설정
				m_Screen->Set_Sub_Sprite(3,m_Sprite->Find_Data(21));
				m_Screen->Set_Sub_Sprite_Pos(3,20.0f,-20.0f,20.0f,0.8f);
				m_Screen->Set_Sub_Sprite_Type(3, 1, 0, 1);
			}
			
			//  악세사리 물고기
			for(int i = 0; i < 6;i++)
			{
				t_Sprite = m_Screen->Insert(i+10,m_Sprite->Find_Data(8 + i));
				//	스프라이트
				if(t_Sprite != NULL)
				{	
					m_Screen->Set_RS_Type(t_Sprite,1);
					m_Screen->Set_View_Type(t_Sprite,1);
					m_Screen->Set_RS_Scale(t_Sprite,1.0f,0.7f,1.0f);
					m_Screen->Set_Button_Return(t_Sprite,0);
					//	버튼 비활성
					m_Screen->Set_Button_OnOff(t_Sprite,0);
					m_Screen->Set_RS_Pos(t_Sprite,260,0.0f,-30.0f);
					m_Screen->Set_Scale_F(t_Sprite,0.3f);
					m_Screen->Set_RS_Move1_Param(t_Sprite,0.0f,0.0f,0.0f,0.0f,0);
					m_Screen->Set_RS_Move2_Param(t_Sprite,0.0f, 1.0f,0.0f, 3.0f,10);	// 물고기 재자리 튼들림
					m_Screen->Set_RS_Move3_Param(t_Sprite,0.0f,0.0f,0.0f,0.0f,0);
					m_Screen->Set_RS_Effect_ID(t_Sprite,1);
					m_Screen->Set_RS_Z_Rot(t_Sprite,0);
				}
			}
			//	16 부터 렝크 메뉴 5개
			for(int i = 0; i < 5;i++)
			{
				t_Sprite = m_Screen->Insert(i+16,m_Sprite->Find_Data(33));
				//	스프라이트
				if(t_Sprite != NULL)
				{
					m_Screen->Set_RS_Type(t_Sprite,0);
					m_Screen->Set_View_Type(t_Sprite,1);
					m_Screen->Set_RS_Scale(t_Sprite,1.0f,1.0f,1.0f);
					m_Screen->Set_RS_Pos(t_Sprite,-140.0f + 70.0f*i,90.0f,-45.0f);
					m_Screen->Set_RS_Ani(t_Sprite,i%3,i/3,0.0f);
					m_Screen->Set_RS_Move1_Param(t_Sprite,0.0f,300.0f,0.0f,200.0f,11);	// 추가 이동 소모형
				}
			}
			int	t_User_Level = m_player->Get_User_Level();
			//	21 부터 게임 레벨 5개
			for(int i = 0; i < t_User_Level;i++)
			{
				t_Sprite = m_Screen->Insert(i+21,m_Sprite->Find_Data(34));
				//	스프라이트
				if(t_Sprite != NULL)
				{
					m_Screen->Set_RS_Type(t_Sprite,0);
					m_Screen->Set_View_Type(t_Sprite,1);
					m_Screen->Set_RS_Scale(t_Sprite,1.0f,1.0f,1.0f);
					m_Screen->Set_RS_Pos(t_Sprite,-140.0f,60.0f - 35.0f*i,-45.0f);
					m_Screen->Set_RS_Ani(t_Sprite,i%3,i/3,0.0f);
					m_Screen->Set_RS_Move1_Param(t_Sprite,0.0f,300.0f,0.0f,200.0f,11);	// 추가 이동 소모형
				}
			}
			//	26 부터 게임 단계별 성적 출력
			int	t_Score = 0;
			for(int i = 0; i < t_User_Level;i++)
			{
				// 점수
				t_Sprite = m_Screen->Insert(i*4+26,m_Sprite->Find_Data(22));
				t_Score = m_player->Get_User_Yes_Count(i+1);
				if(t_Sprite != NULL)
				{
					m_Screen->Set_RS_Type(t_Sprite,4);
					m_Screen->Set_View_Type(t_Sprite,1);
					m_Screen->Set_RS_Scale(t_Sprite,1.0f,1.0f,1.0f);
					m_Screen->Set_RS_Pos(t_Sprite,-70.0f,60.0f - 35.0f*i,-45.0f);
					m_Screen->Set_Out_Number(t_Sprite,m_player->Get_User_Score(i+1),0);
					m_Screen->Set_RS_Move1_Param(t_Sprite,0.0f,300.0f,0.0f,200.0f,11);	
				}
				// 정답
				t_Sprite = m_Screen->Insert(i*4+26 + 1,m_Sprite->Find_Data(22));
				if(t_Sprite != NULL)
				{
					m_Screen->Set_RS_Type(t_Sprite,4);
					m_Screen->Set_View_Type(t_Sprite,1);
					m_Screen->Set_RS_Scale(t_Sprite,1.0f,1.0f,1.0f);
					m_Screen->Set_RS_Pos(t_Sprite,0.0f,60.0f - 35.0f*i,-45.0f);
					m_Screen->Set_Out_Number(t_Sprite,m_player->Get_User_Yes_Count(i+1),0);
					m_Screen->Set_RS_Move1_Param(t_Sprite,0.0f,300.0f,0.0f,200.0f,11);	
				}
				// 오답
				t_Sprite = m_Screen->Insert(i*4+26 + 2,m_Sprite->Find_Data(22));
				if(t_Sprite != NULL)
				{
					m_Screen->Set_RS_Type(t_Sprite,4);
					m_Screen->Set_View_Type(t_Sprite,1);
					m_Screen->Set_RS_Scale(t_Sprite,1.0f,1.0f,1.0f);
					m_Screen->Set_RS_Pos(t_Sprite,70.0f,60.0f - 35.0f*i,-45.0f);
					m_Screen->Set_Out_Number(t_Sprite,m_player->Get_User_No_Count(i+1),0);
					m_Screen->Set_RS_Move1_Param(t_Sprite,0.0f,300.0f,0.0f,200.0f,11);	
				}
				// 등급 메달
				t_Sprite = m_Screen->Insert(i*4+26 + 3,m_Sprite->Find_Data(32));
				if(t_Sprite != NULL)
				{
					m_Screen->Set_RS_Type(t_Sprite,0);
					m_Screen->Set_View_Type(t_Sprite,1);
					m_Screen->Set_RS_Scale(t_Sprite,1.0f,1.0f,1.0f);
					m_Screen->Set_RS_Pos(t_Sprite,140.0f,60.0f - 35.0f*i,-45.0f);
					m_Screen->Set_RS_Move1_Param(t_Sprite,0.0f,300.0f,0.0f,200.0f,11);
					if(t_Score <= 50)
					{
						m_Screen->Set_RS_Ani(t_Sprite,0,0,0.0f);
					}
					else if(t_Score <= 80)
					{
						m_Screen->Set_RS_Ani(t_Sprite,1,0,0.0f);
					}
					else
					{
						m_Screen->Set_RS_Ani(t_Sprite,2,0,0.0f);
					}
				}
			}
			break;
		}
		case 21:
		{
			//	도움말 보기 화면 설정
			m_UI->Release_List();
			//	배경 그림 출력
			m_Screen->Release_List();
			//	렌더링 이팩트 삭제.
			m_Effect->Stop_Out_Effect();
			//	뒷배경
			FS_RSprite *t_Sprite = m_Screen->Insert(1,m_Sprite->Find_Data(1));
			if(t_Sprite != NULL)
			{
				m_Screen->Set_RS_Type(t_Sprite,0);
				m_Screen->Set_View_Type(t_Sprite,1);
				m_Screen->Set_RS_Pos(t_Sprite,0.0f,0.0f,-100.0f);
			}
			//	도움말 타이틀
			t_Sprite = m_Screen->Insert(2,m_Sprite->Find_Data(30));
			if(t_Sprite != NULL)
			{
				//	이동 이미지
				m_Screen->Set_RS_Type(t_Sprite,2);
				m_Screen->Set_View_Type(t_Sprite,1);
				m_Screen->Set_RS_Pos(t_Sprite,0.0f,140.0f,-50.0f);
				
				m_Screen->Set_RS_Move1_Param(t_Sprite,0.0f,200.0f,0.0f,100.0f,11);	// 추가 이동 소모형
			}
			
			//	돌아가기 버튼 설정.
			t_Sprite = m_Screen->Insert(3,m_Sprite->Find_Data(8));
			if(t_Sprite != NULL)
			{	
				m_Screen->Set_RS_Type(t_Sprite,1);
				m_Screen->Set_Button_OnOff(t_Sprite,1);
				m_Screen->Set_View_Type(t_Sprite,1);
				m_Screen->Set_RS_Pos(t_Sprite,180.0f,-130.0f,-50.0f);
				m_Screen->Set_RS_Scale(t_Sprite,1.0f,0.7f,1.0f);
				//	초기 화면으로
				m_Screen->Set_Button_Return(t_Sprite,22);
				
				m_Screen->Set_RS_Move1_Param(t_Sprite,300.0f,0.0f,0.0f,300.0f,11);	// 추가 이동 소모형
				m_Screen->Set_RS_Move2_Param(t_Sprite,0.0f, 1.0f,0.0f, 3.0f,10);	// 물고기 재자리 튼들림
				m_Screen->Set_RS_Move3_Param(t_Sprite,0.0f,0.0f,0.0f,0.0f,0);
				m_Screen->Set_RS_Effect_ID(t_Sprite,1);
				m_Screen->Set_RS_Z_Rot(t_Sprite,0);
				
				//	서브 스프라이트 설정
				m_Screen->Set_Sub_Sprite(3,m_Sprite->Find_Data(21));
				m_Screen->Set_Sub_Sprite_Pos(3,20.0f,-20.0f,20.0f,0.8f);
				m_Screen->Set_Sub_Sprite_Type(3, 1, 0, 1);
			}
			//	이전 버튼 처리
			t_Sprite = m_Screen->Insert(4,m_Sprite->Find_Data(8));
			if(t_Sprite != NULL)
			{	
				m_Screen->Set_RS_Type(t_Sprite,1);
				m_Screen->Set_Button_OnOff(t_Sprite,1);
				m_Screen->Set_View_Type(t_Sprite,1);
				m_Screen->Set_RS_Pos(t_Sprite,-190.0f,130.0f,0.0f);
				m_Screen->Set_RS_Scale(t_Sprite,1.0f,0.7f,1.0f);
				//	초기 화면으로
				m_Screen->Set_Button_Return(t_Sprite,1010);
				
				m_Screen->Set_RS_Move1_Param(t_Sprite,600.0f,0.0f,0.0f,300.0f,11);	// 추가 이동 소모형
				m_Screen->Set_RS_Move2_Param(t_Sprite,0.0f, 1.0f,0.0f, 3.0f,10);	// 물고기 재자리 튼들림
				m_Screen->Set_RS_Move3_Param(t_Sprite,0.0f,0.0f,0.0f,0.0f,0);
				m_Screen->Set_RS_Effect_ID(t_Sprite,1);
				m_Screen->Set_RS_Z_Rot(t_Sprite,0);
				
				//	서브 스프라이트 설정
				m_Screen->Set_Sub_Sprite(4,m_Sprite->Find_Data(21));
				m_Screen->Set_Sub_Sprite_Pos(4,20.0f,-20.0f,20.0f,0.8f);
				m_Screen->Set_Sub_Sprite_Type(4, 1, 0, 0);
			}
			//	다음 버튼 처리
			t_Sprite = m_Screen->Insert(5,m_Sprite->Find_Data(8));
			if(t_Sprite != NULL)
			{	
				m_Screen->Set_RS_Type(t_Sprite,1);
				m_Screen->Set_Button_OnOff(t_Sprite,1);
				m_Screen->Set_View_Type(t_Sprite,1);
				m_Screen->Set_RS_Pos(t_Sprite,190.0f,130.0f,0.0f);
				m_Screen->Set_RS_Scale(t_Sprite,1.0f,0.7f,1.0f);
				//	초기 화면으로
				m_Screen->Set_Button_Return(t_Sprite,1011);
				
				m_Screen->Set_RS_Move1_Param(t_Sprite,-600.0f,0.0f,0.0f,300.0f,11);	// 추가 이동 소모형
				m_Screen->Set_RS_Move2_Param(t_Sprite,0.0f, 1.0f,0.0f, 3.0f,10);	// 물고기 재자리 튼들림
				m_Screen->Set_RS_Move3_Param(t_Sprite,0.0f,0.0f,0.0f,0.0f,0);
				m_Screen->Set_RS_Effect_ID(t_Sprite,1);
				m_Screen->Set_RS_Z_Rot(t_Sprite,1);
				
				//	서브 스프라이트 설정
				m_Screen->Set_Sub_Sprite(5,m_Sprite->Find_Data(21));
				m_Screen->Set_Sub_Sprite_Pos(5,-20.0f,-20.0f,20.0f,0.8f);
				m_Screen->Set_Sub_Sprite_Type(5, 1, 1, 0);
			}
			
			//	업적윈도우 출력
			t_Sprite = m_Screen->Insert(6,m_Sprite->Find_Data(3));
			if(t_Sprite != NULL)
			{
				//	이동 이미지
				m_Screen->Set_RS_Type(t_Sprite,2);
				m_Screen->Set_View_Type(t_Sprite,1);
				m_Screen->Set_RS_Pos(t_Sprite,0.0f,0.0f,-60.0f);
				
				m_Screen->Set_RS_Move1_Param(t_Sprite,0.0f,200.0f,0.0f,100.0f,11);	// 추가 이동 소모형
			}
			
			//	도움말 내용 이미지
			t_Sprite = m_Screen->Insert(7,m_Sprite->Find_Data(35));
			if(t_Sprite != NULL)
			{
				m_Screen->Set_RS_Type(t_Sprite,0);
				m_Screen->Set_View_Type(t_Sprite,1);
				m_Screen->Set_RS_Pos(t_Sprite,8.0f,0.0f,-55.0f);
				m_Screen->Set_RS_Scale(t_Sprite,0.8f,0.8f,1.0f);
				m_Screen->Set_RS_Ani(t_Sprite,m_Help_Page%2,m_Help_Page/2,0.0f);
				
				m_Screen->Set_RS_Move1_Param(t_Sprite,0.0f,200.0f,0.0f,100.0f,11);	// 추가 이동 소모형
			}
			
			
			//  악세사리 물고기
			for(int i = 0; i < 6;i++)
			{
				t_Sprite = m_Screen->Insert(i+10,m_Sprite->Find_Data(8 + i));
				//	스프라이트
				if(t_Sprite != NULL)
				{	
					m_Screen->Set_RS_Type(t_Sprite,1);
					m_Screen->Set_View_Type(t_Sprite,1);
					m_Screen->Set_RS_Scale(t_Sprite,1.0f,0.7f,1.0f);
					m_Screen->Set_Button_Return(t_Sprite,0);
					//	버튼 비활성
					m_Screen->Set_Button_OnOff(t_Sprite,0);
					m_Screen->Set_RS_Pos(t_Sprite,260,0.0f,-30.0f);
					m_Screen->Set_Scale_F(t_Sprite,0.3f);
					m_Screen->Set_RS_Move1_Param(t_Sprite,0.0f,0.0f,0.0f,0.0f,0);
					m_Screen->Set_RS_Move2_Param(t_Sprite,0.0f, 1.0f,0.0f, 3.0f,10);	// 물고기 재자리 튼들림
					m_Screen->Set_RS_Move3_Param(t_Sprite,0.0f,0.0f,0.0f,0.0f,0);
					m_Screen->Set_RS_Effect_ID(t_Sprite,1);
					m_Screen->Set_RS_Z_Rot(t_Sprite,0);
				}
			}
			break;
		}
		//	업적에서 초기화면으로
		case 12:
		{
			//	게임 화면으로 진행 처리.
			FS_RSprite *t_Sprite = NULL;
			//	모든 버튼 사라짐
			float t_RY = 0.0f;
			for(int i = 0; i < 1;i++)
			{
				t_Sprite = m_Screen->Find_Data(i+3);
				if(t_Sprite != NULL)
				{
					// 위치 얻기
					t_RY = (float)(rand()%320) - 160.0f;
					//	카운트 만큼 이동 후 사라짐
					m_Screen->Set_RS_Move1_Param(t_Sprite,0.0f,0.0f,0.0f,0.0f,0);
					m_Screen->Set_RS_Move3_Param(t_Sprite,(-300.0f - t_Sprite->m_Pos.m_X)/60.0f,
												 (t_RY - t_Sprite->m_Pos.m_Y)/60.0f,0.0f,60.0f,31);
				}
			}
			//	 악세라리 물고기 사라짐
			for(int i = 0; i < 6;i++)
			{
				t_Sprite = m_Screen->Find_Data(i+10);
				if(t_Sprite != NULL)
				{
					// 위치 얻기
					t_RY = (float)(rand()%320) - 160.0f;
					//	카운트 만큼 이동 후 사라짐
					m_Screen->Set_RS_Move1_Param(t_Sprite,0.0f,0.0f,0.0f,0.0f,0);
					m_Screen->Set_RS_Move3_Param(t_Sprite,(-300.0f - t_Sprite->m_Pos.m_X)/60.0f,
												 (t_RY - t_Sprite->m_Pos.m_Y)/60.0f,0.0f,60.0f,31);
				}
			}
			//	윈도우 사라짐
			t_Sprite = m_Screen->Find_Data(2);
			if(t_Sprite != NULL)
			{
				//	카운트 만큼 이동 후 사라짐
				m_Screen->Set_RS_Move3_Param(t_Sprite,0.0f,300.0f/60.0f,0.0f,60.0f,30);
			}
			// 타이틀 사라짐
			t_Sprite = m_Screen->Find_Data(4);
			if(t_Sprite != NULL)
			{
				//	카운트 만큼 이동 후 사라짐
				m_Screen->Set_RS_Move3_Param(t_Sprite,0.0f,300.0f/60.0f,0.0f,60.0f,30);
			}
			//	나머지 아이콘 사라짐
			for(int i = 0; i < 30;i++)
			{
				t_Sprite = m_Screen->Find_Data(i+16);
				if(t_Sprite != NULL)
				{
					//	카운트 만큼 이동 후 사라짐
					m_Screen->Set_RS_Move3_Param(t_Sprite,0.0f,300.0f/60.0f,0.0f,60.0f,30);
				}
			}
			break;
		}
			//	도움말에서 초기화면으로
		case 22:
		{
			//	게임 화면으로 진행 처리.
			FS_RSprite *t_Sprite = NULL;
			//	모든 버튼 사라짐
			float t_RY = 0.0f;
			for(int i = 0; i < 3;i++)
			{
				t_Sprite = m_Screen->Find_Data(i+3);
				if(t_Sprite != NULL)
				{
					// 위치 얻기
					t_RY = (float)(rand()%320) - 160.0f;
					//	카운트 만큼 이동 후 사라짐
					m_Screen->Set_RS_Move1_Param(t_Sprite,0.0f,0.0f,0.0f,0.0f,0);
					if(i==2)
					{
						m_Screen->Set_RS_Move3_Param(t_Sprite,-(-300.0f - t_Sprite->m_Pos.m_X)/60.0f,
													 (t_RY - t_Sprite->m_Pos.m_Y)/60.0f,0.0f,60.0f,31);
					}
					else 
					{
						m_Screen->Set_RS_Move3_Param(t_Sprite,(-300.0f - t_Sprite->m_Pos.m_X)/60.0f,
													 (t_RY - t_Sprite->m_Pos.m_Y)/60.0f,0.0f,60.0f,31);
					}
				}
			}
			//	 악세라리 물고기 사라짐
			for(int i = 0; i < 6;i++)
			{
				t_Sprite = m_Screen->Find_Data(i+10);
				if(t_Sprite != NULL)
				{
					// 위치 얻기
					t_RY = (float)(rand()%320) - 160.0f;
					//	카운트 만큼 이동 후 사라짐
					m_Screen->Set_RS_Move1_Param(t_Sprite,0.0f,0.0f,0.0f,0.0f,0);
					m_Screen->Set_RS_Move3_Param(t_Sprite,(-300.0f - t_Sprite->m_Pos.m_X)/60.0f,
												 (t_RY - t_Sprite->m_Pos.m_Y)/60.0f,0.0f,60.0f,31);
				}
			}
			//	윈도우 사라짐
			t_Sprite = m_Screen->Find_Data(2);
			if(t_Sprite != NULL)
			{
				//	카운트 만큼 이동 후 사라짐
				m_Screen->Set_RS_Move3_Param(t_Sprite,0.0f,300.0f/60.0f,0.0f,60.0f,30);
			}
			t_Sprite = m_Screen->Find_Data(6);
			if(t_Sprite != NULL)
			{
				//	카운트 만큼 이동 후 사라짐
				m_Screen->Set_RS_Move3_Param(t_Sprite,0.0f,300.0f/60.0f,0.0f,60.0f,30);
			}
			t_Sprite = m_Screen->Find_Data(7);
			if(t_Sprite != NULL)
			{
				//	카운트 만큼 이동 후 사라짐
				m_Screen->Set_RS_Move3_Param(t_Sprite,0.0f,300.0f/60.0f,0.0f,60.0f,30);
			}
			break;
		}
		case 10:
		//	업적 보기 전환
		case 20:
		//	도움말 전환
		case 100:
		case 200:
		case 300:
		case 400:
		case 500:
		case 600:	// 이어서 하기
		{
			//	게임 화면으로 진행 처리.
			FS_RSprite *t_Sprite = NULL;
			float t_RY = 0.0f;
			//	모든 버튼 사라짐
			for(int i = 0; i < 3;i++)
			{
				t_Sprite = m_Screen->Find_Data(i+3);
				if(t_Sprite != NULL)
				{
					// 위치 얻기
					t_RY = (float)(rand()%320) - 160.0f;
					//	카운트 만큼 이동 후 사라짐
					m_Screen->Set_RS_Move1_Param(t_Sprite,0.0f,0.0f,0.0f,0.0f,0);
					m_Screen->Set_RS_Move3_Param(t_Sprite,(-300.0f - t_Sprite->m_Pos.m_X)/60.0f,
												 (t_RY - t_Sprite->m_Pos.m_Y)/60.0f,0.0f,60.0f,31);
				}
			}
			for(int i = 0; i < 11;i++)
			{
				t_Sprite = m_Screen->Find_Data(i+10);
				if(t_Sprite != NULL)
				{
					// 위치 얻기
					t_RY = (float)(rand()%320) - 160.0f;
					//	카운트 만큼 이동 후 사라짐
					m_Screen->Set_RS_Move1_Param(t_Sprite,0.0f,0.0f,0.0f,0.0f,0);
					m_Screen->Set_RS_Move3_Param(t_Sprite,(-300.0f - t_Sprite->m_Pos.m_X)/60.0f,
												 (t_RY - t_Sprite->m_Pos.m_Y)/60.0f,0.0f,60.0f,31);
				}
			}
			//	타이틀 로고 사라짐 처리
			t_Sprite = m_Screen->Find_Data(2);
			if(t_Sprite != NULL)
			{
				//	카운트 만큼 이동 후 사라짐
				m_Screen->Set_RS_Move3_Param(t_Sprite,0.0f,128.0f/60.0f,0.0f,60.0f,30);
			}
			break;
		}
		case 101:
		case 201:
		case 301:
		case 401:
		case 501:
		case 601: // 이어서 하기
		{
			//	기존 화면 렌더링 정보 삭제.
			m_UI->Release_List();
			m_Screen->Release_List();
			//	렌더링 이팩트 삭제.
			m_Effect->Stop_Out_Effect();
			
			//	게임 배경화면
			FS_RSprite *t_Sprite = m_Screen->Insert(1,m_Sprite->Find_Data(5));
			if(t_Sprite != NULL)
			{
				m_Screen->Set_RS_Type(t_Sprite,0);
				m_Screen->Set_View_Type(t_Sprite,1);
				m_Screen->Set_RS_Pos(t_Sprite,0.0f,0.0f,-100.0f);
			}
			//	배경 물풀
			for(int i = 0; i < 5;i++)
			{
				t_Sprite = m_Screen->Insert(2+i,m_Sprite->Find_Data(23));
				if(t_Sprite != NULL)
				{
					m_Screen->Set_RS_Type(t_Sprite,1);
					m_Screen->Set_View_Type(t_Sprite,1);
					m_Screen->Set_RS_Scale(t_Sprite,1.0f,1.0f,1.0f);
					m_Screen->Set_Button_Return(t_Sprite,0);
					//	버튼 비활성
					m_Screen->Set_Button_OnOff(t_Sprite,0);
					m_Screen->Set_RS_Pos(t_Sprite,-120.0f + i*60.0f+Rand_Float(-20.0f,20.0f),-165.0f,-90.0f);
					m_Screen->Set_Scale_F(t_Sprite,1.0f + Rand_Float(-0.3f, 0.3f));
					//	기준축 이동
					m_Screen->Set_RS_Move1_Param(t_Sprite,0.0f,44.0f,0.0f,0.0f,12);	
					m_Screen->Set_RS_Move2_Param(t_Sprite,0.0f, 1.0f,0.0f, 3.0f,11);
				}
			}
			
			//	문제창 UI 설정
			t_Sprite = m_UI->Insert(1,m_Sprite->Find_Data(24));
			if(t_Sprite != NULL)
			{
				m_UI->Set_RS_Type(t_Sprite,2);
				m_UI->Set_View_Type(t_Sprite,1);
				m_UI->Set_RS_Pos(t_Sprite,-120.0f,120.0f,100.0f);
				m_UI->Set_RS_Scale(t_Sprite,0.9f,1.0f,1.0f);
				m_UI->Set_RS_Move1_Param(t_Sprite,0.0f,100.0f,0.0f,50.0f,11);	// 추가 이동 소모형
			}
			//	게임 점수 창
			t_Sprite = m_UI->Insert(2,m_Sprite->Find_Data(24));
			if(t_Sprite != NULL)
			{
				m_UI->Set_RS_Type(t_Sprite,2);
				m_UI->Set_View_Type(t_Sprite,1);
				m_UI->Set_RS_Pos(t_Sprite,120.0f,120.0f,100.0f);
				m_UI->Set_RS_Scale(t_Sprite,0.9f,1.0f,1.0f);
				m_UI->Set_RS_Move1_Param(t_Sprite,0.0f,100.0f,0.0f,50.0f,11);	// 추가 이동 소모형
			}
			
			//	문제 유형 UI
			if((p_Type == 501)||(m_player->m_Info.m_Play.m_Info.m_Type == 5))
			{
				t_Sprite = m_UI->Insert(3,m_Sprite->Find_Data(26));
				if(t_Sprite != NULL)
				{
					m_UI->Set_RS_Type(t_Sprite,2);
					m_UI->Set_View_Type(t_Sprite,1);
					m_UI->Set_RS_Pos(t_Sprite,-115.0f,120.0f,105.0f);
					m_UI->Set_RS_Scale(t_Sprite,0.85f,0.85f,1.0f);
					m_UI->Set_RS_Move1_Param(t_Sprite,0.0f,100.0f,0.0f,50.0f,11);	// 추가 이동 소모형
				}
			}
			else
			{
				t_Sprite = m_UI->Insert(3,m_Sprite->Find_Data(25));
				if(t_Sprite != NULL)
				{
					m_UI->Set_RS_Type(t_Sprite,2);
					m_UI->Set_View_Type(t_Sprite,1);
					m_UI->Set_RS_Pos(t_Sprite,-115.0f,120.0f,105.0f);
					m_UI->Set_RS_Scale(t_Sprite,0.85f,0.85f,1.0f);
					m_UI->Set_RS_Move1_Param(t_Sprite,0.0f,100.0f,0.0f,50.0f,11);	// 추가 이동 소모형
				}
			}
			
			//	점수  UI
			t_Sprite = m_UI->Insert(4,m_Sprite->Find_Data(27));
			if(t_Sprite != NULL)
			{
				m_UI->Set_RS_Type(t_Sprite,2);
				m_UI->Set_View_Type(t_Sprite,1);
				m_UI->Set_RS_Pos(t_Sprite,144.0f,118.0f,105.0f);
				m_UI->Set_RS_Scale(t_Sprite,1.0f,1.0f,1.0f);
				m_UI->Set_RS_Move1_Param(t_Sprite,0.0f,100.0f,0.0f,50.0f,11);	// 추가 이동 소모형
			}
			//	게임 나가기 종료 버튼
			t_Sprite = m_UI->Insert(7,m_Sprite->Find_Data(8));
			if(t_Sprite != NULL)
			{	
				m_UI->Set_RS_Type(t_Sprite,1);
				m_UI->Set_Button_OnOff(t_Sprite,1);
				m_UI->Set_View_Type(t_Sprite,1);
				m_UI->Set_RS_Pos(t_Sprite,210.0f,140.0f,110.0f);
				m_UI->Set_RS_Scale(t_Sprite,1.0f,0.7f,1.0f);
				//	초기 화면으로
				m_UI->Set_Button_Return(t_Sprite,110);
				
				m_UI->Set_RS_Move1_Param(t_Sprite,300.0f,0.0f,0.0f,300.0f,11);	// 추가 이동 소모형
				m_UI->Set_RS_Move2_Param(t_Sprite,0.0f, 1.0f,0.0f, 3.0f,10);	// 물고기 재자리 튼들림
				m_UI->Set_RS_Move3_Param(t_Sprite,0.0f,0.0f,0.0f,0.0f,0);
				m_UI->Set_RS_Effect_ID(t_Sprite,1);
				m_UI->Set_RS_Z_Rot(t_Sprite,0);
				m_UI->Set_Scale_F(t_Sprite,0.8f);
				
				//	서브 스프라이트 설정
				m_UI->Set_Sub_Sprite(7,m_Sprite->Find_Data(28));
				m_UI->Set_Sub_Sprite_Pos(7,-10.0f,-17.0f,2.0f,0.7f);
				m_UI->Set_Sub_Sprite_Type(7,2);// 그냥 이미지
			}

			//	문제 단어 출력
			t_Sprite = m_UI->Insert(10,m_Text_Out->Find_Data(1));
			if(t_Sprite != NULL)
			{
				m_UI->Set_RS_Type(t_Sprite,2);
				m_UI->Set_View_Type(t_Sprite,1);
				m_UI->Set_RS_Pos(t_Sprite,-120.0f,111.0f,110.0f);
				m_UI->Set_RS_Scale(t_Sprite,1.0f,1.0f,1.0f);
				m_UI->Set_RS_Move1_Param(t_Sprite,0.0f,100.0f,0.0f,50.0f,11);	// 추가 이동 소모형
				
				m_TexLib_Text->Update_Tex_String(1,(char *)" ",255,0,0,200);
			}
			
			
			//	점수 출력 설정
			t_Sprite = m_UI->Insert(20,m_Sprite->Find_Data(22));
			if(t_Sprite != NULL)
			{
				m_UI->Set_RS_Type(t_Sprite,4);
				m_UI->Set_View_Type(t_Sprite,1);
				m_UI->Set_RS_Pos(t_Sprite,100.0f,136.0f,112.0f);
				m_UI->Set_RS_Scale(t_Sprite,1.0f,1.0f,1.0f);
				
				m_UI->Set_Scale_F(t_Sprite,1.0f);
				if(p_Type == 601)
				{
					m_UI->Set_Out_Number(t_Sprite,m_player->m_Info.m_Play.m_Info.m_Score,0);
				}
				else
				{
					m_UI->Set_Out_Number(t_Sprite,0,0);
				}
				m_UI->Set_RS_Ani(t_Sprite,0,0,0.0f);	// 숫자 출력에서 Y 값은 색상번호 (파랑색)
				m_UI->Set_RS_Move1_Param(t_Sprite,0.0f,100.0f,0.0f,50.0f,11);	// 추가 이동 소모형
			}
			//	정답 개수
			t_Sprite = m_UI->Insert(21,m_Sprite->Find_Data(22));
			if(t_Sprite != NULL)
			{
				m_UI->Set_RS_Type(t_Sprite,4);
				m_UI->Set_View_Type(t_Sprite,1);
				m_UI->Set_RS_Pos(t_Sprite,76.0f,106.0f,112.0f);
				m_UI->Set_RS_Scale(t_Sprite,1.0f,1.0f,1.0f);
				
				m_UI->Set_Scale_F(t_Sprite,1.0f);
				if(p_Type == 601)
				{
					m_UI->Set_Out_Number(t_Sprite,m_player->m_Info.m_Play.m_Info.m_Yes_Count,0);
				}
				else
				{
					m_UI->Set_Out_Number(t_Sprite,0,0);
				}
				m_UI->Set_RS_Ani(t_Sprite,0,3,0.0f);	// 숫자 출력에서 Y 값은 색상번호 (연두색)
				m_UI->Set_RS_Move1_Param(t_Sprite,0.0f,100.0f,0.0f,50.0f,11);	// 추가 이동 소모형
			}
			//	오답 개수
			t_Sprite = m_UI->Insert(22,m_Sprite->Find_Data(22));
			if(t_Sprite != NULL)
			{
				m_UI->Set_RS_Type(t_Sprite,4);
				m_UI->Set_View_Type(t_Sprite,1);
				m_UI->Set_RS_Pos(t_Sprite,177.0f,106.0f,112.0f);
				m_UI->Set_RS_Scale(t_Sprite,1.0f,1.0f,1.0f);
				
				m_UI->Set_Scale_F(t_Sprite,1.0f);
				if(p_Type == 601)
				{
					m_UI->Set_Out_Number(t_Sprite,m_player->m_Info.m_Play.m_Info.m_No_Count,0);
				}
				else
				{
					m_UI->Set_Out_Number(t_Sprite,0,0);
				}
				m_UI->Set_RS_Ani(t_Sprite,0,1,0.0f);	// 숫자 출력에서 Y 값은 색상번호 (빨강)
				m_UI->Set_RS_Move1_Param(t_Sprite,0.0f,100.0f,0.0f,50.0f,11);	// 추가 이동 소모형
			}
			
			//	결과 정보 인터페이스
			t_Sprite = m_UI->Insert(30,m_Sprite->Find_Data(3));
			if(t_Sprite != NULL)
			{
				m_UI->Set_RS_Type(t_Sprite,2);
				m_UI->Set_View_Type(t_Sprite,0);
				m_UI->Set_RS_Pos(t_Sprite,0.0f,0.0f,100.0f);
			}
			//	점수,정답,오답,도전문항 수
			for(int i = 0 ; i < 4;i++)
			{
				t_Sprite = m_UI->Insert(31+i,m_Sprite->Find_Data(22));
				if(t_Sprite != NULL)
				{
					m_UI->Set_RS_Type(t_Sprite,4);
					m_UI->Set_View_Type(t_Sprite,0);
					m_UI->Set_RS_Scale(t_Sprite,1.3f,1.3f,1.0f);
					m_UI->Set_Scale_F(t_Sprite,1.0f);
					m_UI->Set_RS_Ani(t_Sprite,0,i,0.0f);
					m_UI->Set_Out_Number(t_Sprite,0,0);
					
					if(i == 3)
					{
						m_UI->Set_RS_Pos(t_Sprite,40.0f,45.0f - 35.0f*(i+1),101.0f);
					}
					else 
					{
						m_UI->Set_RS_Pos(t_Sprite,40.0f,45.0f - 35.0f*i,101.0f);
					}

				}
			}
			//	결과 타이틀
			t_Sprite = m_UI->Insert(35,m_Sprite->Find_Data(31));
			if(t_Sprite != NULL)
			{
				m_UI->Set_RS_Type(t_Sprite,0);
				m_UI->Set_View_Type(t_Sprite,0);
				m_UI->Set_RS_Ani(t_Sprite,0,0,0.0f);
				m_UI->Set_RS_Scale(t_Sprite,1.0f,1.0f,1.0f);
				m_UI->Set_RS_Pos(t_Sprite,0.0f,140,101.0f);
			}
			
			// 결과 글씨
			for(int i = 0 ; i < 6;i++)
			{
				t_Sprite = m_UI->Insert(36 + i,m_Sprite->Find_Data(33));
				if(t_Sprite != NULL)
				{
					m_UI->Set_RS_Type(t_Sprite,0);
					m_UI->Set_View_Type(t_Sprite,0);
					m_UI->Set_RS_Ani(t_Sprite,i%3,i/3,0.0f);
					m_UI->Set_RS_Scale(t_Sprite,1.0f,1.0f,1.0f);
					m_UI->Set_RS_Pos(t_Sprite,-60.0f,80.0f - 35.0f*i,101.0f);
				}
			}
			//	난이도
			t_Sprite = m_UI->Insert(42,m_Sprite->Find_Data(34));
			if(t_Sprite != NULL)
			{
				m_UI->Set_RS_Type(t_Sprite,0);
				m_UI->Set_View_Type(t_Sprite,0);
				m_UI->Set_RS_Ani(t_Sprite,0,0,0.0f);
				m_UI->Set_RS_Scale(t_Sprite,1.0f,1.0f,1.0f);
				m_UI->Set_RS_Pos(t_Sprite,40.0f,80.0f,101.0f);
			}
			// 메달
			t_Sprite = m_UI->Insert(43,m_Sprite->Find_Data(32));
			if(t_Sprite != NULL)
			{
				m_UI->Set_RS_Type(t_Sprite,0);
				m_UI->Set_View_Type(t_Sprite,0);
				m_UI->Set_RS_Ani(t_Sprite,0,0,0.0f);
				m_UI->Set_RS_Scale(t_Sprite,1.0f,1.0f,1.0f);
				m_UI->Set_RS_Pos(t_Sprite,40.0f,80.0f - 35.0f*4.0f,101.0f);
			}
			
			//	메인 케릭터 설정
			switch(p_Type)
			{
				case 101:
				{
					if(m_player != NULL)
					{
						//	게임 진행 정보 설정
						m_player->Set_Play_Type(1);
						m_player->Init_Fish(1,m_Sprite->Find_Data(9));
					}
					break;
				}
				case 201:
				{
					if(m_player != NULL)
					{
						//	게임 진행 정보 설정
						m_player->Set_Play_Type(2);
						m_player->Init_Fish(1,m_Sprite->Find_Data(10));
					}
					break;
				}
				case 301:
				{
					if(m_player != NULL)
					{
						//	게임 진행 정보 설정
						m_player->Set_Play_Type(3);
						m_player->Init_Fish(1,m_Sprite->Find_Data(11));
					}
					break;
				}
				case 401:
				{
					if(m_player != NULL)
					{
						//	게임 진행 정보 설정
						m_player->Set_Play_Type(4);
						m_player->Init_Fish(1,m_Sprite->Find_Data(12));
					}
					break;
				}
				case 501:
				{
					if(m_player != NULL)
					{
						//	게임 진행 정보 설정
						m_player->Set_Play_Type(5);
						m_player->Init_Fish(1,m_Sprite->Find_Data(13));
					}
					break;
				}
				case 601:
				{
					//	이어서 하기 
					m_player->Continue_Play_Type();
					//	메인 플레이어 물고기 설정
					if(m_player->m_Info.m_Play.m_Info.m_Type == 0)
					{
						m_player->m_Info.m_Play.m_Info.m_Type = 1;
					}
					m_player->Init_Fish(1,m_Sprite->Find_Data(8 + m_player->m_Info.m_Play.m_Info.m_Type));
					break;
				}
			}
			break;
		}
		default:
		{
			break;
		}
	}
	return true;
}

//	렌더링 스트라이트 삭제
bool	FG_Game_RF::Delete_RSprite()
{
	if(m_Screen != NULL)
	{
		delete m_Screen;
		m_Screen = NULL;
	}
	if(m_UI != NULL)
	{
		delete m_UI;
		m_UI = NULL;
	}
	return true;
}
//	렌더링 스프라이트 초과화
bool	FG_Game_RF::Init_RSprite()
{
	if(m_Screen == NULL)
		return false;
	m_Screen->Release_List();
	return true;
}

//	렌더링 이펙트 삭제
bool	FG_Game_RF::Delete_Effect()
{
	if(m_Effect == NULL)
		return false;
	delete m_Effect;
	m_Effect = NULL;
	return true;
}

//	렌더링 이펙트 로딩
bool	FG_Game_RF::Load_Effect()
{
	if(m_Sprite == NULL)
		return false;
	if(m_Effect != NULL)
	{
		delete m_Effect;
		m_Effect = NULL;
	}
	m_Effect = new F_GL_2DEffect;
	
	//	1 물방울 이펙트 설정
	FS_2DEffect *t_Effect = m_Effect->Insert(1, m_Sprite->Find_Data(4));
	if(t_Effect != NULL)
	{
		//	출력 시간 2초
		m_Effect->Set_EF_Time_Limit(t_Effect,2.0f);
		t_Effect->m_Scale = 0.3f;
	}
	//	이펙트
	t_Effect = m_Effect->Insert(2, m_Sprite->Find_Data(7));
	if(t_Effect != NULL)
	{
		//	출력 시간 1초
		t_Effect->m_Scale = 1.0f;
		m_Effect->Set_EF_Time_Limit(t_Effect,1.0f);
		//	전체 스프라이트 진행
		m_Effect->Set_EF_Img_Select_Type(t_Effect,3,0,0);
	}
	
	//	콤보 이펙트
	t_Effect = m_Effect->Insert(3, m_Sprite->Find_Data(36));
	if(t_Effect != NULL)
	{
		//	출력 시간 1초
		t_Effect->m_Scale = 1.0f;
		m_Effect->Set_EF_Time_Limit(t_Effect,1.0f);
	}
	//	콤보 숫자 이펙트
	t_Effect = m_Effect->Insert(4, m_Sprite->Find_Data(37));
	if(t_Effect != NULL)
	{
		//	출력 시간 1초
		t_Effect->m_Scale = 1.0f;
		m_Effect->Set_EF_Time_Limit(t_Effect,1.0f);
		//	숫자 이팩트
		m_Effect->Set_EF_Img_Select_Type(t_Effect,4,0,0);
	}
	//	파란 숫자
	t_Effect = m_Effect->Insert(5, m_Sprite->Find_Data(22));
	if(t_Effect != NULL)
	{
		//	출력 시간 1초
		t_Effect->m_Scale = 1.0f;
		m_Effect->Set_EF_Time_Limit(t_Effect,1.0f);
		//	숫자 이팩트
		m_Effect->Set_EF_Img_Select_Type(t_Effect,4,0,0);
	}
	//	빨강 숫자
	t_Effect = m_Effect->Insert(6, m_Sprite->Find_Data(22));
	if(t_Effect != NULL)
	{
		//	출력 시간 1초
		t_Effect->m_Scale = 1.0f;
		m_Effect->Set_EF_Time_Limit(t_Effect,1.0f);
		//	숫자 이팩트
		m_Effect->Set_EF_Img_Select_Type(t_Effect,4,0,1);
	}
	return true;
}

/*
 렌더링 관련 함수
 */
//	렌더링 전처리 함수
bool	FG_Game_RF::Pre_Render(float p_Time)
{
	//	문자열 스프라이트 생성 확인
	Init_Text_Sprite();
	//	배경 반복 체크 
	F_IO_Wave::Check_Back_Sound();
	//	장면 번호 변경 확인
	if(m_Scene_Type != m_Next_Scene_Type)
	{
		m_Scene_Type = m_Next_Scene_Type;
		//m_Next_Scene_Type = 0;
		m_Time = 0.0f;
		m_Load_TF = 1;
	}
	else 
	{
		//	타임 진행
		m_Time = m_Time+p_Time;
	}

	
	//	유형에 따라서
	switch (m_Scene_Type)
	{
		case 1:
		{
			// 초기화면
			if(m_Screen != NULL)
			{
				if(m_Load_TF == 1)
				{
					//	장면 데이터 설정
					Set_Screen_Date(m_Scene_Type);
					m_Load_TF = 0;
				}
				//	비활성 버튼 자유 이동
				Move_Button_Set(10,11);
				m_Screen->Pre_Render(p_Time);
				m_Screen_TF = false;	// 화면 보기
			}
			if(m_Effect != NULL)
			{
				m_Effect->Pre_Render(p_Time);
			}
			break;
		}
		case 10:
		{
			//	업적 화면으로 전환 진행
			if(m_Load_TF == 1)
			{
				//	장면 전환 처리
				Set_Screen_Date(m_Scene_Type);
				m_Load_TF = 0;
				m_Sub_Time = 2.0f;
			}
			if(m_Screen != NULL)
			{
				m_Screen->Pre_Render(p_Time);
			}
			if(m_Effect != NULL)
			{
				m_Effect->Pre_Render(p_Time);
			}
			//	화면 전환 확인
			if(m_Sub_Time < m_Time)
			{
				//	게임 화면으로
				Set_Scene(11);
				m_Sub_Time = 0.0f;
			}
			break;
		}
		case 11:
		{
			// 업적 화면으로 전환 진행
			if(m_Load_TF == 1)
			{
				//	장면 전환 처리
				Set_Screen_Date(m_Scene_Type);
				m_Load_TF = 0;
				m_Screen_TF = false;	// 화면 보기
			}
			if(m_Screen != NULL)
			{
				//	비활성 버튼 자유 이동
				Move_Button_Set(10,6);
				m_Screen->Pre_Render(p_Time);
			}
			if(m_Effect != NULL)
			{
				m_Effect->Pre_Render(p_Time);
			}
			break;
		}
		case 12:
		{
			// 초기 화면으로 전환
			if(m_Load_TF == 1)
			{
				//	장면 전환 처리
				Set_Screen_Date(m_Scene_Type);
				m_Load_TF = 0;
				m_Sub_Time = 2.0f;
			}
			if(m_Screen != NULL)
			{
				m_Screen->Pre_Render(p_Time);
			}
			if(m_Effect != NULL)
			{
				m_Effect->Pre_Render(p_Time);
			}
			//	화면 전환 확인
			if(m_Sub_Time < m_Time)
			{
				//	게임 화면으로
				Set_Scene(1);
				m_Sub_Time = 0.0f;
			}
			break;
		}
		case 20:
		{
			//	결과 화면으로 전환 진행
			if(m_Load_TF == 1)
			{
				//	장면 전환 처리
				Set_Screen_Date(m_Scene_Type);
				m_Load_TF = 0;
				m_Sub_Time = 2.0f;
			}
			if(m_Screen != NULL)
			{
				m_Screen->Pre_Render(p_Time);
			}
			if(m_Effect != NULL)
			{
				m_Effect->Pre_Render(p_Time);
			}
			//	화면 전환 확인
			if(m_Sub_Time < m_Time)
			{
				//	게임 화면으로
				Set_Scene(21);
				m_Sub_Time = 0.0f;
			}
			break;
		}
		case 21:
		{
			//	결과 화면 진행
			if(m_Load_TF == 1)
			{
				//	장면 전환 처리
				Set_Screen_Date(m_Scene_Type);
				m_Load_TF = 0;
				m_Screen_TF = false;	// 화면 보기
			}
			if(m_Screen != NULL)
			{
				//	비활성 버튼 자유 이동
				Move_Button_Set(10,6);
				m_Screen->Pre_Render(p_Time);
			}
			if(m_Effect != NULL)
			{
				m_Effect->Pre_Render(p_Time);
			}
			break;
		}
		case 22:
		{
			// 초기 화면으로 전환
			if(m_Load_TF == 1)
			{
				//	장면 전환 처리
				Set_Screen_Date(m_Scene_Type);
				m_Load_TF = 0;
				m_Sub_Time = 2.0f;
			}
			if(m_Screen != NULL)
			{
				m_Screen->Pre_Render(p_Time);
			}
			if(m_Effect != NULL)
			{
				m_Effect->Pre_Render(p_Time);
			}
			//	화면 전환 확인
			if(m_Sub_Time < m_Time)
			{
				//	게임 화면으로
				Set_Scene(1);
				m_Sub_Time = 0.0f;
			}
			break;
		}
		case 100:
		case 200:
		case 300:
		case 400:
		case 500:
		case 600:	// 이어서 하기
		{
			// 게임 진행 화면으로 전환
			if(m_Load_TF == 1)
			{
				//	장면 전환 처리
				Set_Screen_Date(m_Scene_Type);
				m_Load_TF = 0;
				m_Sub_Time = 2.0f;
			}
			if(m_Screen != NULL)
			{
				m_Screen->Pre_Render(p_Time);
			}
			if(m_Effect != NULL)
			{
				m_Effect->Pre_Render(p_Time);
			}
			if(m_Time > 1.0f)
			{
				if(!m_Screen_TF)
					m_Screen_TF = true;	// 화면 숨김
			}
			//	화면 전환 확인
			if(m_Sub_Time < m_Time)
			{
				//	게임 화면으로
				Set_Scene(m_Scene_Type + 1);
				m_Sub_Time = 0.0f;
			}
			break;
		}
		case 101:
		case 201:
		case 301:
		case 401:
		case 501:
		case 601:	// 이어서 하기
		{
			if(m_Load_TF == 1)
			{
				//	장면 전환 처리
				Set_Screen_Date(m_Scene_Type);
				m_Load_TF = 0;
				m_Screen_TF = false;	// 화면 보기
			}
			if(m_Screen != NULL)
			{
				m_Screen->Pre_Render(p_Time);
			}
			if(m_player != NULL)
			{
				m_player->Pre_Render(p_Time);
				if(m_player->m_Game_Out)
				{
					//	초기 화면으로
					Set_Scene(110);
					m_player->m_Game_Out = false;
				}
			}
			if(m_Effect != NULL)
			{
				m_Effect->Pre_Render(p_Time);
			}
			if(m_UI != NULL)
			{
				m_UI->Pre_Render(p_Time);
			}
			break;
		}
		case 110:
		{
			if(m_Load_TF == 1)
			{
				m_Load_TF = 0;
				m_Screen_TF = true; // 숨김
				// 게임 진행 상태 저장
				m_player->Save_User_Data();
			}
			
			m_Screen->Pre_Render(p_Time);
			if(m_Effect != NULL)
			{
				m_Effect->Pre_Render(p_Time);
			}
			//	완전히 숨겨진 경우 화면 변경
			if((m_Screen_TF)&&(m_Screen_Alpha < 0.05f))
			{
				//	초기 메뉴로 
				Set_Scene(1);
			}
			break;
		}
		default:
		{
			break;
		}
	}
	return true;
}
//	렌더링 함수
bool	FG_Game_RF::Render(float p_Time)
{
	if(m_Screen_TF)
	{
		if(m_Screen_Alpha > 0.05f)
		{
			m_Screen_Alpha = m_Screen_Alpha - 0.05f;
		}
		else
		{
			m_Screen_Alpha = 0.0f;
		}

	}
	else
	{
		if(m_Screen_Alpha > 0.95f)
		{
			m_Screen_Alpha = 1.0f;
		}
		else 
		{
			m_Screen_Alpha = m_Screen_Alpha + 0.05f;
		}

	}
	glColor4f(1.0f,1.0f,1.0f,m_Screen_Alpha);
	
	switch (m_Scene_Type)
	{
		case 1:
		{
			// 인트로
			if(m_Screen != NULL)
			{
				m_Screen->Render(p_Time);
			}
			if(m_Effect != NULL)
			{
				m_Effect->Render(p_Time,m_Screen_Alpha);
			}
			break;
		}
		case 10:
		case 11:
		case 12:
		{
			// 업적 화면으로 전환
			if(m_Screen != NULL)
			{
				m_Screen->Render(p_Time);
			}
			if(m_Effect != NULL)
			{
				m_Effect->Render(p_Time,m_Screen_Alpha);
			}
			break;
		}
		case 20:
		case 21:
		case 22:
		{
			//	도움말 화면으로 전환
			if(m_Screen != NULL)
			{
				m_Screen->Render(p_Time);
			}
			if(m_Effect != NULL)
			{
				m_Effect->Render(p_Time,m_Screen_Alpha);
			}
			break;
		}
		case 100:
		case 200:
		case 300:
		case 400:
		case 500:
		case 600:
		{
			//	게임 화면으로 진행 처리
			if(m_Screen != NULL)
			{
				m_Screen->Render(p_Time);
			}
			if(m_Effect != NULL)
			{
				m_Effect->Render(p_Time,m_Screen_Alpha);
			}
			break;
		}
		case 101:
		case 201:
		case 301:
		case 401:
		case 501:
		case 601:
		{
			//	게임 화면
			if(m_Screen != NULL)
			{
				m_Screen->Render(p_Time);
			}
			if(m_player != NULL)
			{
				m_player->Render(p_Time);
			}
			if(m_Effect != NULL)
			{
				m_Effect->Render(p_Time,m_Screen_Alpha);
			}
			if(m_UI != NULL)
			{
				m_UI->Render(p_Time);
			}
			break;
		}
		case 110:
		{
			//	게임 화면에서 메인 화면으로 변경
			if(m_Screen != NULL)
			{
				m_Screen->Render(p_Time);
			}
			if(m_Effect != NULL)
			{
				m_Effect->Render(p_Time,m_Screen_Alpha);
			}
			break;
		}
		default:
		{
			break;
		}
	}
	return true;
}

//	장면 전환 설정
bool	FG_Game_RF::Set_Scene(int p_Scene_Type)
{
	if(m_Scene_Type != p_Scene_Type)
	{
		//	다음 화면 번호 보관.
		m_Next_Scene_Type = p_Scene_Type;
	}
	return true;
}

bool	FG_Game_RF::Input_Mouse_Down(FS_XYZ *p_Pos,FS_XYZ *p_Dir)
{
	m_Mouse_Type = 1;
	m_Mouse_Pos = *p_Pos;
	m_Mouse_Dir = *p_Dir;
	
	//	렌더링 오브젝트에 마우스 타운 설정
	switch (m_Scene_Type)
	{
		case 1:
		case 11:
		case 21:
		{
			if(m_Screen != NULL)
			{
				//	마우스 이벤트 처리
				m_Screen->Mouse_Down(&m_Mouse_Pos,&m_Mouse_Dir);
			}
			break;
		}
		case 101:
		case 201:
		case 301:
		case 401:
		case 501:
		case 601:
		{
			if(m_Screen != NULL)
			{
				//	마우스 이벤트 처리
				m_Screen->Mouse_Down(&m_Mouse_Pos,&m_Mouse_Dir);
			}
			if(m_UI != NULL)
			{
				//	마우스 이벤트 처리
				m_UI->Mouse_Down(&m_Mouse_Pos,&m_Mouse_Dir);
			}
			if(m_player != NULL)
			{
				m_player->Mouse_Down(&m_Mouse_Pos,&m_Mouse_Dir);
			}
			break;
		}
		default:
			break;
	}
	return true;
}

bool	FG_Game_RF::Input_Mouse_Up(FS_XYZ *p_Pos,FS_XYZ *p_Dir)
{
	m_Mouse_Type = 0;
	m_Mouse_Pos = *p_Pos;
	m_Mouse_Dir = *p_Dir;
	//	렌더링 오브젝트에 마우스 업 설정
	switch (m_Scene_Type)
	{
		case 1:
		case 11:
		case 21:
		{
			if(m_Screen != NULL)
			{
				//	마우스 이벤트 처리
				int t_Return = m_Screen->Mouse_Up(&m_Mouse_Pos,&m_Mouse_Dir);
				if((t_Return != 0)&&(m_Mouse_Event == 0))
				{
					//	버튼 이벤트 처리 요청
					m_Mouse_Event = t_Return;
					if(m_Mouse_Event < 1000)
					{
						//	화면 장면 변경
						Set_Scene(m_Mouse_Event);
						m_Mouse_Event = 0;
					}
					else
					{
						FS_RSprite	*t_Sprite = NULL;
						//	일반 버튼 이벤트
						if(m_Mouse_Event == 1010)
						{
							//	1010 도움말 이전
							t_Sprite = m_Screen->Find_Data(7);
							m_Help_Page = m_Help_Page - 1;
							if(m_Help_Page < 0)
								m_Help_Page = 5;
							if(t_Sprite != NULL)
							{
								m_Screen->Set_RS_Ani(t_Sprite,m_Help_Page%2,m_Help_Page/2,0.0f);
							}
						}
						else if(m_Mouse_Event == 1011)
						{
							//	1011 도움말 다음
							m_Help_Page++;
							if(m_Help_Page > 5)
								m_Help_Page = 0;
							t_Sprite = m_Screen->Find_Data(7);
							if(t_Sprite != NULL)
							{
								m_Screen->Set_RS_Ani(t_Sprite,m_Help_Page%2,m_Help_Page/2,0.0f);
							}
						}
						//	1011 도움말 다음
						m_Mouse_Event = 0;
					}
					
				}
			}
			break;
		}
		case 101:
		case 201:
		case 301:
		case 401:
		case 501:
		case 601:
		{
			if(m_Screen != NULL)
			{
				//	마우스 이벤트 처리
				int t_Return = m_Screen->Mouse_Up(&m_Mouse_Pos,&m_Mouse_Dir);
				if((t_Return != 0)&&(m_Mouse_Event == 0))
				{
					//	버튼 이벤트 처리 요청
					m_Mouse_Event = t_Return;
					if(m_Mouse_Event < 1000)
					{
						//	화면 장면 변경
						Set_Scene(m_Mouse_Event);
						m_Mouse_Event = 0;
					}
					else
					{
						//	일반 버튼 이벤트
						m_Mouse_Event = 0;
					}
				}
			}
			if(m_UI != NULL)
			{
				//	마우스 이벤트 처리
				int t_Return = m_UI->Mouse_Up(&m_Mouse_Pos,&m_Mouse_Dir);
				if((t_Return != 0)&&(m_Mouse_Event == 0))
				{
					//	버튼 이벤트 처리 요청
					m_Mouse_Event = t_Return;
					if(m_Mouse_Event < 1000)
					{
						//	화면 장면 변경
						Set_Scene(m_Mouse_Event);
						m_Mouse_Event = 0;
					}
					else
					{
						//	일반 버튼 이벤트
						m_Mouse_Event = 0;
					}
				}
			}
			if(m_player != NULL)
			{
				m_player->Mouse_Up(&m_Mouse_Pos,&m_Mouse_Dir);
			}
			break;
		}
		default:
			break;
	}
	return true;
}

bool	FG_Game_RF::Input_Mouse_Move(FS_XYZ *OPos,FS_XYZ *ODir,FS_XYZ *NPos,FS_XYZ *NDir)
{
	m_Mouse_Type = 1;
	m_Mouse_Pos = *NPos;
	m_Mouse_Dir = *NDir;
	//	렌더링 오브젝트에 마우스 이동 설정
	switch (m_Scene_Type)
	{
		case 1:
		case 11:
		case 21:
		{
			if(m_Screen != NULL)
			{
				//	마우스 이벤트 처리
				m_Screen->Mouse_Move(&m_Mouse_Pos,&m_Mouse_Dir);
			}
			break;
		}
		case 101:
		case 201:
		case 301:
		case 401:
		case 501:
		case 601:
		{
			if(m_Screen != NULL)
			{
				//	마우스 이벤트 처리
				m_Screen->Mouse_Move(&m_Mouse_Pos,&m_Mouse_Dir);
			}
			if(m_UI != NULL)
			{
				//	마우스 이벤트 처리
				m_UI->Mouse_Move(&m_Mouse_Pos,&m_Mouse_Dir);
			}
			if(m_player != NULL)
			{
				m_player->Mouse_Down(&m_Mouse_Pos,&m_Mouse_Dir);
			}
			break;
		}
		default:
			break;
	}
	return true;
}

//	비활성 버튼 자유 이동
bool	FG_Game_RF::Move_Button_Set(int p_S_Index, int p_Count)
{
	if(m_Screen == NULL)
		return false;

	FS_RSprite *t_Sprite = NULL;
	float	t_X = 0.0f;
	float	t_Y = 0.0f;
	FS_XYZ	t_DPos;
	float	t_S = 40.0f;
	for(int i = 0; i < p_Count;i++)
	{
		t_Sprite = m_Screen->Find_Data(i+p_S_Index);
		if(t_Sprite != NULL)
		{
			// 버튼 기능이 없는 경우
			if(t_Sprite->m_Button_TF == 0)
			{
				//	이동이 없는 경우
				if(m_Mouse_Type == 0)
				{
					if(t_Sprite->m_Move_Param1 == 0)
					{
						t_X = Rand_Float(-200.0f,200.0f);
						t_Y = Rand_Float(-50.0f,120.0f);
						t_S = Rand_Float(60.0f,100.0f);
						// 이동 거리 최대 100 넘지 않도록 처리
						t_DPos.m_X = t_X - t_Sprite->m_Pos.m_X;
						t_DPos.m_Y = t_Y - t_Sprite->m_Pos.m_Y;
						t_DPos.m_Z = 0.0f;
						if(FS_XYZ::Len(t_DPos) > 100.0f)
						{
							t_DPos = FS_XYZ::Normal(t_DPos);
							t_DPos = t_DPos*100.0f;
							t_X = t_DPos.m_X+t_Sprite->m_Pos.m_X;
							t_Y = t_DPos.m_Y+t_Sprite->m_Pos.m_Y;
							m_Screen->Set_RS_Move1_Param(t_Sprite,t_X,t_Y,0.0f,t_S,6);
						}
						else 
						{
							m_Screen->Set_RS_Move1_Param(t_Sprite,t_X,t_Y,0.0f,t_S,8);
						}
					}
				}
				else
				{
					if((t_Sprite->m_Move_Param1 == 0)||(t_Sprite->m_Move_Param1 == 7))
					{
						t_X = m_Mouse_Pos.m_X + Rand_Float(-50.0f,50.0f);
						t_Y = m_Mouse_Pos.m_Y + Rand_Float(-50.0f,50.0f);
						t_S = Rand_Float(100.0f,160.0f);
						// 이동 거리 최대 100 넘지 않도록 처리
						t_DPos.m_X = t_X - t_Sprite->m_Pos.m_X;
						t_DPos.m_Y = t_Y - t_Sprite->m_Pos.m_Y;
						t_DPos.m_Z = 0.0f;
						if(FS_XYZ::Len(t_DPos) > 50.0f)
						{
							t_DPos = FS_XYZ::Normal(t_DPos);
							t_DPos = t_DPos*50.0f;
							t_X = t_DPos.m_X+t_Sprite->m_Pos.m_X;
							t_Y = t_DPos.m_Y+t_Sprite->m_Pos.m_Y;
							m_Screen->Set_RS_Move1_Param(t_Sprite,t_X,t_Y,0.0f,t_S,6);
						}
						else
						{		
							m_Screen->Set_RS_Move1_Param(t_Sprite,t_X,t_Y,0.0f,t_S,8);
						}
					}
				}
			}
		}
	}
	return true;
}

//	게임 데이터 저장
bool	FG_Game_RF::Save_Data()
{
	if(m_player != NULL)
	{
		m_player->Save_User_Data();
	}
	return true;
}

//	게임 데이터 읽기
bool	FG_Game_RF::Load_Data()
{
	if(m_player != NULL)
	{
		m_player->Load_User_Data();
	}
	return true;
}
