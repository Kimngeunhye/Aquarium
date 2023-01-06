/*
 *  F_IOS_Main.cpp
 *  
 *
 *  Created by forthen on 11. 4. 13..
 *  Copyright 2011 forthen. All rights reserved.
 *
 */

#include "F_IOS_Main.h"

F_IOS_Main::F_IOS_Main()
{
	m_Device = NULL;
	m_Game = NULL;
	
	m_TexLib = NULL;
}

F_IOS_Main::~F_IOS_Main()
{
	if(m_Device != NULL)
	{
		delete m_Device;
		m_Device = NULL;
	}
	if(m_Game != NULL)
	{
		delete m_Game;
		m_Game = NULL;
	}
	
	if(m_TexLib != NULL)
	{
		delete m_TexLib;
		m_TexLib = NULL;
	}
}

//	렌더링 버퍼 초기화
bool F_IOS_Main::Create_Render(int p_Device_Ver)
{
	//	사용할 오픈지엘 버전 설정
	F_Set_OpenGL_Ver(p_Device_Ver);
	if(m_Device != NULL)
	{
		delete m_Device;
		m_Device = NULL;
	}
	//	장치 생성
	m_Device = new F_GL_Device;
	//	렌더링 버퍼 생성
	m_Device->Create_RB();
	
	// 게임 데이터 클래스 생성
	if(m_Game == NULL)
	{
		m_Game = new FG_Game_RF;
	}
	return true;
}

//	초기 렌더링 영역 설정
bool F_IOS_Main::Init_Screen(int p_Width,int p_Height)
{
	if(m_Device == NULL)
		return false;
	//	뷰포트 영역 설정
	m_Device->Set_ViewPort_Rect(0, 0, p_Width,p_Height);
	//	프레임 버퍼 생성
	m_Device->Create_FB();
	//	뷰 좌표 영역 설정
	m_Device->Set_Range(160.0f);
	
	// 뷰포트 설정
	m_Device->Set_ViewPort();
	// 직교좌표 뷰 설정
	m_Device->Set_Ortho();
	
	//	게임 데이터 설정
	if(m_Game != NULL)
	{
		//	데이터 초기화
		m_Game->Init();
		
		////	정면 데이터 설정
		//m_Game->Set_Screen_Date(1);
		
		
		//	장면 변환 : 시작 화면
		m_Game->Set_Scene(1);
	}
	
	//glEnable(GL_TEXTURE_2D);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//string t_Dir = F_IOS_File::Get_Resource_Path();
	
	return true;
}

//	화면 회전
bool F_IOS_Main::Reset_Rotate(int p_Rotate)
{
	float	t_Angle = 0.0f;
	switch(p_Rotate)
	{
		case 2:
		{
			//	거꾸로 된 상태
			t_Angle = 180.0f;
			break;
		}
		case 3:
		{
			//	왼쪽으로 기울인 상태
			t_Angle = 270.0f;
			break;
		}
		case 4:
		{
			//	오른쪽으로 기울인 상태
			t_Angle = 90.0f;
			break;
		}
		default:
		{
			t_Angle = 0.0f;
			p_Rotate = 0;
			break;
		}
	}
	if(m_Device != NULL)
	{
		m_Device->Set_Screen_Rot(t_Angle,p_Rotate);
	}
	return true;
}

//	렌더링 전처리
bool F_IOS_Main::Pre_Render(float t_Time)
{
	if(m_Game == NULL)
		return false;
	m_Game->Pre_Render(t_Time);
	return true;
}

//	렌더링 처리
bool F_IOS_Main::Render(float t_Time)
{
	if(m_Device == NULL)
		return false;
	if(m_Game == NULL)
		return false;
	
	F_GL_Device::Clear_Color(0.1f,0.1f,0.1f,1.0f);
	m_Device->Start_Screen_Rot();
	m_Game->Render(t_Time);
	m_Device->End_Screen_Rot();
	
	
	
	/*
	int backgroundRectangle[] = { 0, 0, 256, 256 };
    glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_CROP_RECT_OES, backgroundRectangle);
    glBindTexture(GL_TEXTURE_2D, m_Test_Texture);
	//glColor4f(0.0, 0.0, 0.0, 1);
    glDrawTexfOES(10, 10, 0, 256, 256);
	*/

	
	/*
	float	t_Pos[12];
	float	t_Color[24];
	float	t_UV[12];
	t_Pos[0] = -1.0f; t_Pos[1] = -1.0f;
	t_Pos[2] = 1.0f; t_Pos[3] = -1.0f;
	t_Pos[4] = 1.0f; t_Pos[5] = 1.0f;
	t_Pos[6] = -1.0f; t_Pos[7] = -1.0f;
	t_Pos[8] = 1.0f; t_Pos[9] = 1.0f;
	t_Pos[10] = -1.0f; t_Pos[11] = 1.0f;
	t_Color[0] = 1.0f; t_Color[1] = 1.0f; t_Color[2] = 1.0f; t_Color[3]= 1.0f;
	t_Color[4] = 1.0f; t_Color[5] = 1.0f; t_Color[6] = 1.0f; t_Color[7]= 1.0f;
	t_Color[8] = 1.0f; t_Color[9] = 1.0f; t_Color[10] = 1.0f; t_Color[11]= 1.0f;
	t_Color[12] = 1.0f; t_Color[13] = 1.0f; t_Color[14] = 1.0f; t_Color[15]= 1.0f;
	t_Color[16] = 1.0f; t_Color[17] = 1.0f; t_Color[18] = 1.0f; t_Color[19]= 1.0f;
	t_Color[20] = 1.0f; t_Color[21] = 1.0f; t_Color[22] = 1.0f; t_Color[23]= 1.0f;
	
	t_UV[0] = 0.0f;	t_UV[1] = 1.0f;
	t_UV[2] = 1.0f;	t_UV[3] = 1.0f;	
	t_UV[4] = 1.0f;	t_UV[5] = 0.0f;	
	t_UV[6] = 0.0f;	t_UV[7] = 1.0f;	
	t_UV[8] = 1.0f;	t_UV[9] = 0.0f;	
	t_UV[10] = 0.0f;	t_UV[11] = 0.0f;
	*/
	
	/*
	float t_Vertex[3][6];
	t_Vertex[0][0] = -1.0f; t_Vertex[0][1] = -1.0f;
	t_Vertex[0][2] = 1.0f; t_Vertex[0][3] = 1.0f; t_Vertex[0][4] = 0.5f; t_Vertex[0][5] = 1.0f;
	t_Vertex[1][0] = 1.0f; t_Vertex[1][1] = -1.0f;
	t_Vertex[1][2] = 1.0f; t_Vertex[1][3] = 1.0f; t_Vertex[1][4] = 0.5f; t_Vertex[1][5] = 1.0f;
	t_Vertex[2][0] = 0.0f; t_Vertex[2][1] = 1.0f;
	t_Vertex[2][2] = 1.0f; t_Vertex[2][3] = 1.0f; t_Vertex[2][4] = 0.5f; t_Vertex[2][5] = 1.0f;
	*/
	
	/*
	F_GL_Texture::Set_Tex_RenderSet(m_TexLib->Find_Tex(1));//m_Texture);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	glVertexPointer(2,GL_FLOAT,8,t_Pos);
	glColorPointer(4,GL_FLOAT,16,t_Color);
	glTexCoordPointer(2,GL_FLOAT,8,t_UV);
	
	glDrawArrays(GL_TRIANGLES,0,6);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	F_GL_Texture::End_Tex_RenderSet();
	
	
	t_Pos[0] = t_Pos[0] - 2.5f;
	t_Pos[2] = t_Pos[2] - 2.5f;
	t_Pos[4] = t_Pos[4] - 2.5f;
	t_Pos[6] = t_Pos[6] - 2.5f;
	t_Pos[8] = t_Pos[8] - 2.5f;
	t_Pos[10] = t_Pos[10] - 2.5f;
	F_GL_Texture::Set_Tex_RenderSet(m_TexLib->Find_Tex(2));//m_Texture);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	glVertexPointer(2,GL_FLOAT,8,t_Pos);
	glColorPointer(4,GL_FLOAT,16,t_Color);
	glTexCoordPointer(2,GL_FLOAT,8,t_UV);
	
	glDrawArrays(GL_TRIANGLES,0,6);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	F_GL_Texture::End_Tex_RenderSet();
	
	t_Pos[0] = t_Pos[0] + 5.0f;
	t_Pos[2] = t_Pos[2] + 5.0f;
	t_Pos[4] = t_Pos[4] + 5.0f;
	t_Pos[6] = t_Pos[6] + 5.0f;
	t_Pos[8] = t_Pos[8] + 5.0f;
	t_Pos[10] = t_Pos[10] + 5.0f;
	F_GL_Texture::Set_Tex_RenderSet(m_TexLib->Find_Tex(3));//m_Texture);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	glVertexPointer(2,GL_FLOAT,8,t_Pos);
	glColorPointer(4,GL_FLOAT,16,t_Color);
	glTexCoordPointer(2,GL_FLOAT,8,t_UV);
	
	glDrawArrays(GL_TRIANGLES,0,6);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	F_GL_Texture::End_Tex_RenderSet();
	*/
	
	//m_Device->End_Screen_Rot();
	
	/*
	// 특정 영역 버퍼만 업데이트 진행
	if(F_GL_Device::Start_FrameBuffer_Rect(10,10,200,300))
	{
		//	버퍼 색상 초기화
		F_GL_Device::Clear_Color(0.0f,0.0f,1.0f,1.0f);
		
		//	특정 영역 버퍼 업데이트 끝
		F_GL_Device::End_FrameBuffer_Rect();
	}
	*/
	/*
	glClearColor(1.0f,0.0f,0.0f,1);
	glClear(GL_COLOR_BUFFER_BIT);
	//glPushMatrix();
	//glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	
	glClearColor(0.0f,1.0f,0.0f,1);
	glScissor(10,10,300,400);
	glEnable(GL_SCISSOR_TEST);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glDisable(GL_SCISSOR_TEST);
	
	//glPopMatrix();
	 */
	return true;
}

//	터치 스크린
bool F_IOS_Main::Touch_On(int p_Nx,int p_Ny)
{
	if(m_Game == NULL)
		return false;
	if(m_Device == NULL)
		return false;
	FS_XYZ t_XYZ;
	FS_XYZ t_Dir;
	if(m_Device->Calcul_ViewPort(&t_XYZ,&t_Dir,p_Nx,p_Ny))
	{
		//	공간 뷰에 따라서 마우스 피킹 위치와 방향을 계산 한다.
		m_Game->Input_Mouse_Down(&t_XYZ,&t_Dir);
	}
	return true;
}

bool F_IOS_Main::Touch_Off(int p_Nx,int p_Ny)
{
	if(m_Game == NULL)
		return false;
	if(m_Device == NULL)
		return false;
	FS_XYZ t_XYZ;
	FS_XYZ t_Dir;
	if(m_Device->Calcul_ViewPort(&t_XYZ,&t_Dir,p_Nx,p_Ny))
	{
		m_Game->Input_Mouse_Up(&t_XYZ,&t_Dir);
	}
	return true;
}

bool F_IOS_Main::Touch_Move(int p_Ox,int p_Oy,int p_Nx,int p_Ny)
{
	if(m_Game == NULL)
		return false;
	if(m_Device == NULL)
		return false;
	FS_XYZ t_XYZ;
	FS_XYZ t_Dir;
	if(m_Device->Calcul_ViewPort(&t_XYZ,&t_Dir,p_Nx,p_Ny))
	{
		m_Game->Input_Mouse_Move(NULL,NULL,&t_XYZ,&t_Dir);
	}
	return true;
}

//	게임 데이터 저장
bool	F_IOS_Main::Save_Data()
{
	if(m_Game != NULL)
	{
		m_Game->Save_Data();
	}
	return true;
}