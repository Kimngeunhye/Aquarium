/*
 *  F_GL_Texture.cpp
 *  
 *
 *  Created by forthen on 11. 4. 18..
 *  Copyright 2011 forthen. All rights reserved.
 *
 */

#include "F_GL_Texture.h"
#include "F_Memory.h"


F_GL_Texture::F_GL_Texture()
{
	// 클래스 생성 함수
	m_File_Name = "";
	memset(m_String,0, 256);
	m_Texture = 0;
	m_Type = 0;
	m_Number = 1;
	m_Img = NULL;
}

F_GL_Texture::~F_GL_Texture()
{
	//	클래스 삭제 함수
	if(m_Texture != 0)
	{
		glDeleteTextures(m_Number, &m_Texture);
		m_Texture = 0;
	}
	if(m_Img != NULL)
	{
		//	삭제
		F_Img::Release(m_Img);
		m_Img = NULL;
	}
}

//	초기화 (이미지 파일 이름 지정, 원본 보관 설정(0 보관, 1미보관))
bool	F_GL_Texture::Init(const string& name,int p_Type)
{
	m_Type = p_Type;
	m_File_Name = name;
	if(m_Img != NULL)
	{
		//	삭제
		F_Img::Release(m_Img);
		m_Img = NULL;
	}
	//	내부 데이터 보존 확인
	if(m_Type == 0)
	{
		m_Img = F_Img::Alloc();
		if(m_Img == NULL)
			return false;
		if(!F_IOS_File::Load_PNG(m_Img,m_File_Name))
		{
			F_Img::Release(m_Img);
			m_Img = NULL;
			return false;
		}
	}
	return true;
}

//	문자열 이미지 (내부 버퍼 보관 안함)
bool	F_GL_Texture::Init(char *p_String)
{
	if(p_String == NULL)
		return false;
	// 문자열 텍스쳐
	m_Type = 2;
	memset(m_String,0,256);
	memcpy(m_String,p_String,strlen(p_String));
	if(m_Img != NULL)
	{
		//	삭제
		F_Img::Release(m_Img);
		m_Img = NULL;
	}
	return true;
}

//	문자열 내용 변경
bool	F_GL_Texture::Update_String(char *p_String,int p_R,int p_G,int p_B,int p_A)
{
	if(p_String == NULL)
		return false;
	m_Type = 2;
	memset(m_String,0,256);
	memcpy(m_String,p_String,strlen(p_String));
	if(m_Img != NULL)
	{
		//	삭제
		F_Img::Release(m_Img);
		m_Img = NULL;
	}
	//	이미지 읽어옴
	m_Img = F_Img::Alloc();
	if(m_Img == NULL)
		return false;
	//	GLView 에서 이미지 로딩 처리
	if(!F_IOS_File::Create_Text_Img(m_Img,m_String,p_R,p_G,p_B,p_A))
	{
		F_Img::Release(m_Img);
		m_Img = NULL;
		return false;
	}
	
	//	텍스처 생성
	if(!Create_Texture(m_Img,1))
	{
		F_Img::Release(m_Img);
		m_Img = NULL;
		return false;
	}
	//	내부 원본 테이터 보존 확인
	if(m_Type != 0)
	{
		F_Img::Release(m_Img);
		m_Img = NULL;
	}
	return true;
}

//	텍스처 생성 (내부 설정 이미지 파일로 설정)
bool	F_GL_Texture::Create_Texture(GLsizei p_Num)
{
	if(m_Img == NULL)
	{
		m_Img = F_Img::Alloc();
		if(m_Img == NULL)
			return false;
		if(m_Type == 2)
		{
			//	GLView 에서 이미지 로딩 처리
			if(!F_IOS_File::Create_Text_Img(m_Img,m_String))
			{
				F_Img::Release(m_Img);
				m_Img = NULL;
				return false;
			}
		}
		else 
		{
			if(!F_IOS_File::Load_PNG(m_Img,m_File_Name))
			{
				F_Img::Release(m_Img);
				m_Img = NULL;
				return false;
			}
		}

	}
	//	텍스처 생성
	if(!Create_Texture(m_Img,p_Num))
	{
		F_Img::Release(m_Img);
		m_Img = NULL;
		return false;
	}
	//	내부 원본 테이터 보존 확인
	if(m_Type != 0)
	{
		F_Img::Release(m_Img);
		m_Img = NULL;
	}
	return	true;
}

//	텍스처 생성
bool	F_GL_Texture::Create_Texture(F_Img_Data *p_Png,GLsizei p_Num)
{
	if(m_Texture != 0)
	{
		glDeleteTextures(m_Number, &m_Texture);
		m_Texture = 0;
	}
	if(p_Png == NULL)
		return false;
	m_Number = p_Num;
	glGenTextures(m_Number,&m_Texture);		
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	if(m_Type == 2)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
	}
	//	텍스처 이미지 데이터 설정
	glTexImage2D(GL_TEXTURE_2D, 0, p_Png->m_Format,p_Png->m_Width,p_Png->m_Height,
				 0,p_Png->m_Format,GL_UNSIGNED_BYTE,p_Png->m_Data);
	return true;
}

//	텍스처 포인터 얻기
GLuint	F_GL_Texture::Get_Texture()
{
	return m_Texture;
}

//	텍스처 클래스 삭제 함수
BOOL F_GL_Texture::Delete(LPVOID p_Texture)
{
	if(p_Texture == NULL)
		return true;
	F_GL_Texture *t_Del = (F_GL_Texture *)p_Texture;
	delete t_Del;
	return true;
}

//	텍스처 렌더링 적용 시작
bool	F_GL_Texture::Set_Tex_RenderSet(F_GL_Texture *p_Texture)
{
	if(p_Texture == NULL)
		return false;
	glBindTexture(GL_TEXTURE_2D,p_Texture->Get_Texture());
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	if(p_Texture->m_Type == 2)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
	}

	return true;
}

//	텍스처 렌더링 적용 종료
bool	F_GL_Texture::End_Tex_RenderSet()
{	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	return true;
}
