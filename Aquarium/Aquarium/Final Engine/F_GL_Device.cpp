/*
 *  F_GL_Device.cpp
 *  Raising Fish
 *
 *  Created by forthen on 11. 4. 14..
 *  Copyright 2011 forthen. All rights reserved.
 *
 */

#include "F_GLES_Define.h"
#include "F_GL_Device.h"


//	장치 관련 클래스 생성
F_GL_Device::F_GL_Device()
{
	//	프레임 버퍼
	m_Frame_Buffer = 0;
	//	렌더링 버퍼
	m_Render_Buffer = 0;
	m_Depth_Buffer = 0;
	//	뷰포트 크기 설정
	F_Rect::SetRect(&m_ViewPort_Rect,0,0,320,480);
	m_Range = 100.0f;
	m_Screen_Rot = 0.0f;
	m_Screen_Dir = 0;
	m_Projection_Type = 0;
}

//	장치 관련 클래스 삭제
F_GL_Device::~F_GL_Device()
{
	Release_FB();
	Release_RB();
}

//	프레임 버퍼 생성
bool F_GL_Device::Create_FB()
{	
	if(m_Frame_Buffer != 0)
		return false;
	//	깊이 버퍼
    glGenRenderbuffersOES(1, &m_Depth_Buffer);
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, m_Depth_Buffer);
    glRenderbufferStorageOES(GL_RENDERBUFFER_OES,
                             GL_DEPTH_COMPONENT16_OES,
                             m_ViewPort_Rect.m_Width,m_ViewPort_Rect.m_Height);
	
	// 렌더링 영역에 대한 프레임 버퍼 설정
	glGenFramebuffersOES(1,&m_Frame_Buffer);
	glBindFramebufferOES(GL_FRAMEBUFFER_OES,m_Frame_Buffer);
	glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES,GL_COLOR_ATTACHMENT0_OES,
								 GL_RENDERBUFFER_OES,m_Render_Buffer);
    glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES,
                                 GL_RENDERBUFFER_OES, m_Depth_Buffer);
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, m_Render_Buffer);
	return true;
}

//	프레임 버퍼 삭제
bool F_GL_Device::Release_FB()
{
	if(m_Frame_Buffer == 0)
		return true;
	glDeleteFramebuffersOES(1, &m_Frame_Buffer);
	m_Frame_Buffer = 0;
	if (m_Depth_Buffer == 0)
		return true;
	glDeleteRenderbuffersOES(1,&m_Depth_Buffer);
	m_Depth_Buffer = 0;
	return true;
}

//	렌더링 버퍼 생성
bool F_GL_Device::Create_RB()
{
	if(m_Render_Buffer != 0)
		return false;
	//	기본 장치 설정 (렌더링 버퍼 설정)
	glGenRenderbuffersOES(1,&m_Render_Buffer);
	glBindRenderbufferOES(GL_RENDERBUFFER_OES,m_Render_Buffer);
	return true;
}

//	렌더링 버퍼 삭제
bool F_GL_Device::Release_RB()
{
	if (m_Render_Buffer == 0)
		return true;
	glDeleteRenderbuffersOES(1,&m_Render_Buffer);
	m_Render_Buffer = 0;
	return true;
}

//	뷰포트 사각형 설정
bool F_GL_Device::Set_ViewPort_Rect(int x,int y, int w, int h)
{
	F_Rect::SetRect(&m_ViewPort_Rect,x,y,w,h);
	return true;
}

//	뷰포트 설정
bool F_GL_Device::Set_ViewPort()
{
	//	뷰포트 설정
	glViewport(m_ViewPort_Rect.m_X,m_ViewPort_Rect.m_Y,
			   m_ViewPort_Rect.m_Width,m_ViewPort_Rect.m_Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	return true;
}
//	3D 직각 좌표 영역 설정
bool F_GL_Device::Set_Range(float p_Range)
{
	m_Range = p_Range;
	return true;
}

//	3D 직각 좌표 모델 뷰 설정
bool F_GL_Device::Set_Ortho()
{	
	if(m_ViewPort_Rect.m_Width < 1)
		return false;
	//	투시 방식 (0 정방투영, 1 원근투영)
	m_Projection_Type = 0;
	//	직교 영역 뷰 설정
	float	t_WH = ((float)m_ViewPort_Rect.m_Height)/((float)m_ViewPort_Rect.m_Width);
	//	직교 투영 범위 보관
	m_Projection.m_X = m_Range;
	m_Projection.m_Y = m_Range*t_WH;
	m_Projection.m_Z = m_Range;
	//	투영 설정
	glOrthof(-m_Range,m_Range,-m_Range*t_WH,m_Range*t_WH,-m_Range,m_Range);
	
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	return true;
}

//	화면 회전 값 넣기
bool F_GL_Device::Set_Screen_Rot(float p_Angle,int p_Dir)
{
	m_Screen_Rot = p_Angle;
	m_Screen_Dir = p_Dir;
	return true;
}

//	화면 스크린 회전 적용 시작
bool F_GL_Device::Start_Screen_Rot()
{	
	glPushMatrix();
	glRotatef(m_Screen_Rot, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GEQUAL,0.1f);
	return true;
}

//	화면 스크린 회전 적용 끝
bool F_GL_Device::End_Screen_Rot()
{
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_DEPTH_TEST);
	glPopMatrix();
	return true;
}

/*
	전역 함수
 */
//	프레임 버퍼를 특정 색으로 칠한다.
bool F_GL_Device::Clear_Color(float p_R,float p_G,float p_B,float p_A)
{
	glClearColor(p_R,p_G,p_B,p_A);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return true;
}

//	프레임 버퍼의 특정 영역만 갱신 시작
bool F_GL_Device::Start_FrameBuffer_Rect(int x,int y, int w,int h)
{
	glEnable(GL_SCISSOR_TEST);
	if(glGetError() != GL_NO_ERROR)
	{
		return false;
	}
	glScissor(x,y,w,h);
	return	true;
}

//	프레임 버퍼의 특정 영역만 갱신 끝
bool F_GL_Device::End_FrameBuffer_Rect()
{
	glDisable(GL_SCISSOR_TEST);
	return	true;
}

//	입력된 좌표를 뷰포트 절대 크기로 계산
bool F_GL_Device::Calcul_ViewPort(FS_XYZ *p_Out,FS_XYZ *p_Out_Dir,int p_X,int p_Y)
{
	if(p_Out == NULL)
		return false;
	int t_W = m_ViewPort_Rect.m_Width/2;
	int t_H = m_ViewPort_Rect.m_Height/2;
	if(t_W == 0)
		return false;
	if(t_H == 0)
		return false;
	//	-1 ~ 1 범위로 변환
	p_Out->m_X = ((float)(p_X - t_W))/(float)t_W;
	p_Out->m_Y = ((float)(t_H - p_Y))/(float)t_H;
	
	//	투영 방식에 따라서 좌표 변환
	p_Out->m_X = p_Out->m_X*m_Projection.m_X;
	p_Out->m_Y = p_Out->m_Y*m_Projection.m_Y;
	p_Out->m_Z = m_Projection.m_Z;
	p_Out_Dir->m_X = 0.0f;
	p_Out_Dir->m_Y = 0.0f;
	p_Out_Dir->m_Z = -1.0f;
	
	float t_Temp_f = 0.0f;
	//	모니터 회전에 따른 변경, (카메라 뷰에 따른 조작)
	switch(m_Screen_Dir)
	{
		case 2:
		{
			//	90도 회전
			p_Out->m_X = -p_Out->m_X;
			p_Out->m_Y = -p_Out->m_Y;
			break;
		}
		case 3:
		{
			//	270도 회전
			t_Temp_f = p_Out->m_X;
			p_Out->m_X = -p_Out->m_Y;
			p_Out->m_Y = t_Temp_f;
			break;
		}
		case 4:
		{
			//	90도 회전
			t_Temp_f = p_Out->m_X;
			p_Out->m_X = p_Out->m_Y;
			p_Out->m_Y = -t_Temp_f;
			break;
		}
		default:
			break;
	}
	return true;
}

