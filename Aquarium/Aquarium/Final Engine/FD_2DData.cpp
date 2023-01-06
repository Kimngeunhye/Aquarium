/*
 *  FD_2DData.cpp
 *  2D 관련 데이터 구조체 정의
 *
 *  Created by forthen on 11. 4. 14..
 *  Copyright 2011 forthen. All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FD_2DData.h"

int	Rand_Int(int p_Max)
{
	if(p_Max < 2)
		return 0;
	return (rand()%p_Max);
}

float	Rand_Float(float p_Min,float p_Max)
{
	float t_Return = ((float)Rand_Int(1000))/1000.0f;
	t_Return = (p_Max - p_Min)*t_Return + p_Min;
	return t_Return;
}

bool F_Rect::SetRect(FS_P_Rect p_Rect,int x,int y,int w,int h)
{
	if(p_Rect == NULL)
		return false;
	p_Rect->m_X = x;
	p_Rect->m_Y = y;
	p_Rect->m_Width = w;
	p_Rect->m_Height = h;
	return true;
}

bool F_Rect::InitRect(FS_P_Rect p_Rect)
{
	if(p_Rect == NULL)
		return false;
	p_Rect->m_X = 0;
	p_Rect->m_Y = 0;
	p_Rect->m_Width = 0;
	p_Rect->m_Height = 0;
	return true;
}

//	이미지 정보 구조체 생성
F_Img_Data *F_Img::Alloc()
{
	F_Img_Data *t_Img = (F_Img_Data *)malloc(sizeof(F_Img_Data));
	memset(t_Img,0,sizeof(F_Img_Data));
	return t_Img;
}

//	이미지 정보 구조체 삭제
void F_Img::Release(F_Img_Data *p_Img)
{
	if(p_Img==NULL)
		return;
	if(p_Img->m_Data != NULL)
	{
		free(p_Img->m_Data);
		p_Img->m_Data = NULL;
	}
	free(p_Img);
	p_Img = NULL;
}

//	지정한 이미지의 픽셀 버퍼 생성 (이미 생성된 경우 실패)
bool F_Img::Alloc_PixelData(F_Img_Data *p_Img)
{
	if(p_Img == NULL)
		return false;
	if(p_Img->m_Data != NULL)
		return false;
	if(p_Img->m_Data_Size < 1)
		return false;
	p_Img->m_Data = malloc(p_Img->m_Data_Size);
	memset(p_Img->m_Data,0,p_Img->m_Data_Size);
	return true;
}

bool F_Img::Alloc_PixelData(F_Img_Data *p_Img,int p_Input_Size,void *p_Input_Data)
{
	if(p_Img == NULL)
		return false;
	if(p_Input_Data == NULL)
		return false;
	if(p_Input_Size < 1)
		return false;
	if(p_Img->m_Data != NULL)
	{
		free(p_Img->m_Data);
		p_Img->m_Data = NULL;
	}
	//	버퍼 생성
	p_Img->m_Data_Size = p_Input_Size;
	p_Img->m_Data = malloc(p_Img->m_Data_Size);
	//	데이터 복사
	memcpy(p_Img->m_Data, p_Input_Data, p_Input_Size);
	return true;
}


bool F_Img::Alloc_PixelData(F_Img_Data *p_Img,int p_Input_Size,void *p_Input_Data,int p_R,int p_G,int p_B,int p_A)
{
	if(p_Img == NULL)
		return false;
	if(p_Input_Data == NULL)
		return false;
	if(p_Input_Size < 1)
		return false;
	if(p_Img->m_Data != NULL)
	{
		free(p_Img->m_Data);
		p_Img->m_Data = NULL;
	}
	//	버퍼 생성
	p_Img->m_Data_Size = p_Input_Size;
	p_Img->m_Data = malloc(p_Img->m_Data_Size);
	//	데이터 복사
	memcpy(p_Img->m_Data, p_Input_Data, p_Input_Size);
	unsigned char *t_Byte = (unsigned char *)p_Img->m_Data;
	// 128,16
	int t_SX = 128;
	int t_EX = 0;
	for(int y = 0; y < 16; y++)
	{
		for(int x = 0; x < 128; x++)
		{
			if((t_Byte[(x + y*128)*4+0] < 250)&&(t_Byte[(x + y*128)*4+1] < 250)&&(t_Byte[(x + y*128)*4+2] < 250))
			{
				// 글자색 시작
				if(x < t_SX)
					t_SX = x;
				if(x > t_EX)
					t_EX = x;
			}
		}
	}
	
	for(int y = 0; y < 16; y++)
	{
		for(int x = 0; x < 128; x++)
		{
			if(t_EX == 0)
			{
				// 모두 투명
				t_Byte[(x + y*128)*4+3] = 0;
			}
			else
			{
				if((x < t_SX)||(x > t_EX))
				{
					if((t_SX > x)&&((t_SX-8) < x))
					{
						if((y == 0)||(y==15))
						{
							if((x - (t_SX-8))*31 < 64)
							{
								t_Byte[(x + y*128)*4+3] = (x - (t_SX-8))*31;
							}
							else
							{
								t_Byte[(x + y*128)*4+3] = 64;	
							}	
						}
						else if((y == 1)||(y==14))
						{
							if((x - (t_SX-8))*31 < 128)
							{
								t_Byte[(x + y*128)*4+3] = (x - (t_SX-8))*31;
							}
							else
							{
								t_Byte[(x + y*128)*4+3] = 128;	
							}
						}
						else if((y == 2)||(y==13))
						{
							if((x - (t_SX-8))*31 < 182)
							{
								t_Byte[(x + y*128)*4+3] = (x - (t_SX-8))*31;
							}
							else 
							{
								
								t_Byte[(x + y*128)*4+3] = 182;
							}	
						}
						else
						{
							t_Byte[(x + y*128)*4+3] = (x - (t_SX-8))*31;
						}
					}
					else if((t_EX < x)&&((t_EX+8) > x))
					{
						if((y == 0)||(y==15))
						{
							if(((t_EX+8) - x)*31 < 64)
							{
								t_Byte[(x + y*128)*4+3] = ((t_EX+8) - x)*31;
							}
							else
							{
								t_Byte[(x + y*128)*4+3] = 64;	
							}	
						}
						else if((y == 1)||(y==14))
						{
							if(((t_EX+8) - x)*31 < 128)
							{
								t_Byte[(x + y*128)*4+3] = ((t_EX+8) - x)*31;
							}
							else
							{
								t_Byte[(x + y*128)*4+3] = 128;	
							}
						}
						else if((y == 2)||(y==13))
						{
							if(((t_EX+8) - x)*31 < 182)
							{
								t_Byte[(x + y*128)*4+3] = ((t_EX+8) - x)*31;
							}
							else 
							{
								
								t_Byte[(x + y*128)*4+3] = 182;
							}	
						}
						else
						{
							t_Byte[(x + y*128)*4+3] = ((t_EX+8) - x)*31;
						}
					}
					else 
					{
						t_Byte[(x + y*128)*4+3] = 0;
					}
				}
				else
				{
					if((y == 0)||(y==15))
					{
						t_Byte[(x + y*128)*4+3] = 64;	
					}
					else if((y == 1)||(y==14))
					{
						t_Byte[(x + y*128)*4+3] = 128;	
					}
					else if((y == 2)||(y==13))
					{
						t_Byte[(x + y*128)*4+3] = 182;	
					}
					else
					{
						t_Byte[(x + y*128)*4+3] = 255;	
					}
				}
			}
		}
	}
	/*
	for(int i = 0; i < p_Input_Size/4; i++)
	{
		//	흰색에 가까우면 알파 처리한다.
		if((t_Byte[i*4+0] > 250)||(t_Byte[i*4+1] > 250)||(t_Byte[i*4+2] > 250))
		{
			t_Byte[i*4+3] = 0;
		}
		else
		{
			if((t_Byte[i*4+0] < 140)||(t_Byte[i*4+1] < 140)||(t_Byte[i*4+2] < 140))
			{
				//t_Byte[i*4+0] = p_R; // 빨강
				//t_Byte[i*4+1] = p_G; // 녹색
				//t_Byte[i*4+2] = p_B; // 파랑
				t_Byte[i*4+3] = p_A;
			}
			else
			{
				t_Byte[i*4+3] = 255;//-(t_Byte[i*4+0] + t_Byte[i*4+1] + t_Byte[i*4+2])/3;
			}
		}
		//t_Byte[i*4+0] = 255; // 빨강
		//t_Byte[i*4+1] = 0;// 녹색
		//t_Byte[i*4+2] = 0; //  파랑
		//t_Byte[i*4+3] = 255;
	}
	*/
	return true;
}
