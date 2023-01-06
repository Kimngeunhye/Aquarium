/*
 *  F_GLES_Define.cpp
 *  
 *
 *  Created by forten on 11. 4. 14..
 *  Copyright 2011 forthen. All rights reserved.
 *
 */

#include "F_GLES_Define.h"

//	OpenGl 버전 정보 변수
int	G_Gl_Ver = 0;

// 사용 OpenGL 버전 얻기
int		F_Get_OpenGL_Ver()
{
	return G_Gl_Ver;
}

// 사용 OpenGL 버전 설정
bool	F_Set_OpenGL_Ver(int p_Ver)
{
	if(G_Gl_Ver == 0)
	{
		G_Gl_Ver = p_Ver;
		return true;
	}
	return false;
}