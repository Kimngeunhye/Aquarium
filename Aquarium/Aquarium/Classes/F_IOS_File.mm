/*
 *  F_IOS_File.cpp
 *  
 *
 *  Created by forthen on 11. 4. 14..
 *  Copyright 2011 forthen. All rights reserved.
 *
 */
#import "GLView.h"
#include "F_GLES_Define.h"
#include "F_IOS_File.h"

GLView	*G_View = NULL;

//	전역 GLView  얻기
bool	F_IOS_File::Set_GLView(void *p_View)
{
	G_View = (GLView *)p_View;
	return true;
}

//	 이미지 데이터 만들기
bool	F_IOS_File::Create_Text_Img(F_Img_Data *p_Out_Png,char *p_String,int p_R,int p_G,int p_B,int p_A)
{
	if(G_View == NULL)
		return false;
	if(p_Out_Png == NULL)
		return false;
	UIImage *t_Img = [G_View Create_Image_Text:128 :16 :p_String];
	if(t_Img == NULL)
		return false;
	//	텍스처 버퍼 생성
	CGImageRef t_RefImage = t_Img.CGImage;
	p_Out_Png->m_Width = CGImageGetWidth(t_RefImage);
	p_Out_Png->m_Height = CGImageGetHeight(t_RefImage);
	p_Out_Png->m_Bit_Component = CGImageGetBitsPerComponent(t_RefImage);
	
	// 데이터 포멧 지정
	F_IOS_File::Set_OpenGL_Format(p_Out_Png,CGImageGetAlphaInfo(t_RefImage),
								  CGColorSpaceGetModel(CGImageGetColorSpace(t_RefImage)));
	//	이미지 데이터 포인터 얻기
	CFDataRef	t_Data = CGDataProviderCopyData(CGImageGetDataProvider(t_RefImage));
	//	데이터 복사.
	F_Img::Alloc_PixelData(p_Out_Png,CFDataGetLength(t_Data),(void*)CFDataGetBytePtr(t_Data), p_R, p_G, p_B, p_A);

	CFRelease(t_Data);
	[t_Img release];
	return	true;
}

//	리소스 경로 파일 얻기
string F_IOS_File::Get_Resource_Path()
{
	//	메인 번들의 리소스 결로 문자열 얻기
	NSString* bundlePath =[[NSBundle mainBundle] resourcePath];
	//	스트링르로 반환
	return [bundlePath UTF8String];
}

//	도큐먼트 폴더 얻기
string F_IOS_File::Get_Document_Path()
{
	NSArray	*paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,NSUserDomainMask,YES); 
	NSString *t_Document_Path = [paths objectAtIndex:0];
	return [t_Document_Path UTF8String];
}

//	리소스에서 PNG 파일 읽기
bool F_IOS_File::Load_PNG(F_Img_Data *p_Out_Png,const string& name)
{
	if(p_Out_Png == NULL)
		return false;
	//	문자열 변화
	NSString* t_Name = [[NSString alloc] initWithUTF8String:name.c_str()];
	//	메인 번들 얻기
	NSBundle* t_Main = [NSBundle mainBundle];
	//	파일의 전체 경로 얻기
	NSString* t_Path = [t_Main pathForResource:t_Name ofType:@"png"];
	//	이미지 읽기
	UIImage* t_Image = [[UIImage alloc] initWithContentsOfFile:t_Path];
	CGImageRef t_RefImage = t_Image.CGImage;
	p_Out_Png->m_Width = CGImageGetWidth(t_RefImage);
	p_Out_Png->m_Height = CGImageGetHeight(t_RefImage);
	p_Out_Png->m_Bit_Component = CGImageGetBitsPerComponent(t_RefImage);

	// 데이터 포멧 지정
	F_IOS_File::Set_OpenGL_Format(p_Out_Png,CGImageGetAlphaInfo(t_RefImage),
		CGColorSpaceGetModel(CGImageGetColorSpace(t_RefImage)));
	
	//	이미지 데이터 포인터 얻기
	CFDataRef	t_Data = CGDataProviderCopyData(CGImageGetDataProvider(t_RefImage));
	//	데이터 복사.
	F_Img::Alloc_PixelData(p_Out_Png,CFDataGetLength(t_Data),(void*)CFDataGetBytePtr(t_Data));
	// 사용 데이터 삭제
	[t_Image release];
	[t_Name release];
	CFRelease(t_Data);
	return true;
}
//	지정 이미지의 OpenGL 포맷 지정
bool F_IOS_File::Set_OpenGL_Format(F_Img_Data *p_Img,int p_Alpha,int p_Color)
{
	if(p_Img == NULL)
		return false;
	// 설정 안된것은 지원 안함
	switch(p_Alpha)
	{
		case 0:
		{
			// 알파 사용안함
			if(p_Color == 1)
			{
				p_Img->m_Format = GL_RGB;
			}
			else if(p_Color == 0)
			{
				p_Img->m_Format = GL_LUMINANCE;
			}	
			break;
		}
		case 1:
		{
			// RGBA
			if(p_Color == 1)
			{
				p_Img->m_Format = GL_RGBA;
			}
			else if(p_Color == 0)
			{
				p_Img->m_Format = GL_LUMINANCE_ALPHA;
			}
			break;
		}
		case 2:
		{
			// ARBG
			if(p_Color == 1)
			{
				p_Img->m_Format = GL_RGBA;
			}
			else if(p_Color == 0)
			{
				p_Img->m_Format = GL_LUMINANCE_ALPHA;
			}
			// 알파 값 변경 필요
			break;
		}
		case 3:
		{
			// RGB-A 불리된 알파
			if(p_Color == 1)
			{
				p_Img->m_Format = GL_RGBA;
			}
			else if(p_Color == 0)
			{
				p_Img->m_Format = GL_LUMINANCE_ALPHA;
			}
			break;
		}
		case 4:
		{
			// A-RGB 불리된 알파
			if(p_Color == 1)
			{
				p_Img->m_Format = GL_RGBA;
			}
			else if(p_Color == 0)
			{
				p_Img->m_Format = GL_LUMINANCE_ALPHA;
			}
			// 알파 값 변경 필요
			break;
		}
		case 5:
		{
			// RGBX
			if(p_Color == 1)
			{
				p_Img->m_Format = GL_RGBA;
			}
			else if(p_Color == 0)
			{
				p_Img->m_Format = GL_LUMINANCE_ALPHA;
			}
			break;
		}
		case 6:
		{
			// XRGB
			break;
		}
		case 7:
		{
			// A 이미지
			p_Img->m_Format = GL_ALPHA;
			break;
		}
	}
	return true;
}

