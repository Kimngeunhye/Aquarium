/*
 *  F_GLES_Define.h
 *  GL ES 기반 헤더 정의
 *
 *  Created by zendiya on 10. 12. 11..
 *  Copyright 2010 forthen. All rights reserved.
 *
 */
#pragma once
#include <stdio.h>
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

// 사용 OpenGL 버전 얻기
int		F_Get_OpenGL_Ver();

// 사용 OpenGL 버전 설정 (한번만 설정 가능)
bool	F_Set_OpenGL_Ver(int p_Ver);