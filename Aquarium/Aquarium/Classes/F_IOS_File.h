/*
 *  F_IOS_File.h
 *  파일 관리 클래스
 *
 *  Created by forthen on 11. 4. 14..
 *  Copyright 2011 forthen. All rights reserved.
 *
 */
#pragma once
#import <string>
#import <iostream>
#include "FD_2DData.h"

using std::string;

//	파일 관리 전역 함수 클래스
class F_IOS_File
{
public:
	//	리소스 경로 파일 얻기
	static string Get_Resource_Path();
	//	리소스에서 PNG 파일 읽기
	static bool Load_PNG(F_Img_Data *p_Out_Png,const string& name);
	
	//	지정 이미지의 OpenGL 포맷 지정
	static bool Set_OpenGL_Format(F_Img_Data *p_Img,int p_Alpha,int p_Color);
	
	//	도큐먼트 폴더 얻기
	static string Get_Document_Path();
	
	//	 이미지 데이터 만들기
	static bool		Create_Text_Img(F_Img_Data *p_Out_Png,char *p_String,int p_R = 0,int p_G = 0,int p_B = 0,int p_A = 255);
	/*
	//	이미지 텍스처 요청 함수
	static	bool	Send_Text_Change();
	static	char	*Get_Text_Change();
	static	bool	Insert_Text(void *p_Img);
	*/
	//	전역 GLView  얻기
	static	bool	Set_GLView(void *p_View);
	
};
