/*
 *  F_GL_2DEffect.h
 *  
 *
 *  Created by zendiya on 11. 4. 25..
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "F_GL_Sprite.h"

struct FS_2DEffect_Info
{
	int		m_Type;
	FS_XYZ	m_Pos;	
	float	m_Time;	
	FS_XYZ	m_TPos;	
	FS_MATRIX	m_Mat;
	int			m_Y_Rot;	
	int			m_Select_N;
	FS_XYZW		m_Move_Dir1;
	FS_XYZW		m_Move_Dir2;
	FS_XYZW		m_Move_Dir3;
	int			m_Move_Param1;	
	int			m_Move_Param2;
	int			m_Move_Param3;
	int			m_Alpha_TF;
	float		m_Alpha;
	
	FS_XYZW		m_Rect;
	int	m_Result1;
	int	m_Result2;
	int			m_Out_Number;
	
	FS_Sprite	*m_Text;
	FS_XYZW		m_Text_Pos;
};

struct FS_2DEffect
{
	int			m_Index;	
	int			m_Out_Count;
	FS_Sprite	*m_Sprite;	
	FS_LList	*m_Out_List;	
	int			m_Select_Type;
	int			m_X_Select;
	int			m_Y_Select;
    FS_XYZW		m_Rect;	
	
	float		m_Limit_Time;
	float		m_Scale;		
	int			m_EF_Index;		
};

class	F_GL_2DEffect
{
public:
	F_GL_2DEffect();
	~F_GL_2DEffect();
public:
	FS_LList	*m_List;
	bool	m_Init_Out;
	FS_XY	m_Rot_UV[6];
	void	*m_Effect;
public:
	bool	Set_Sub_Effect(void *p_Effect);
	bool	Release();
	FS_2DEffect	*Insert(int p_Index,FS_Sprite *p_Sprite);
	FS_LList	*Find(int p_Index);
	FS_2DEffect	*Find_Data(int p_Index);
	bool	Delete(int p_Index);
	bool	Set_EF_Time_Limit(FS_2DEffect *p_Effect,float p_Time);
	bool	Set_EF_Img_Select_Type(FS_2DEffect *p_Effect,int p_Type,int p_X_Select,int p_Y_Select);
	bool	Set_EF_Rect(FS_2DEffect *p_Effect,float p_sx,float p_sy,float p_w,float p_h);
	bool	Set_EF_Sub_Effect(FS_2DEffect *p_EF_Info,int p_Effect_ID);
	FS_2DEffect_Info	*Out_Effect(int p_Index);
	bool	Init_Out_Count();
	bool	Stop_Out_Effect();
	
	bool	Pre_Render(float t_DTime);
	bool	Render(float t_DTime,float p_Alpha);
	bool	Pre_Render_Effect(FS_2DEffect *p_Effect,float t_DTime);
	bool	Pre_Render_Effect_Data(FS_2DEffect *p_Effect,FS_2DEffect_Info *p_Info,float t_DTime);
	bool	Render_Effect(FS_2DEffect *p_Effect,float t_DTime,float p_Alpha);
	bool	Render_Effect_Data(FS_2DEffect *p_Effect,FS_2DEffect_Info *p_Info,float t_DTime,float p_Alpha);
	bool	Render_Text_Delete(FS_2DEffect *p_Effect);
	bool	Render_Sub_Text(FS_2DEffect_Info *p_Info,float t_DTime);
	bool	Set_EF_Move1_Param(FS_2DEffect_Info *p_EF_Info,float dx,float dy,float dz,float dMove,int p_Parm);
	bool	Set_EF_Move2_Param(FS_2DEffect_Info *p_EF_Info,float dx,float dy,float dz,float dMove,int p_Parm);
	bool	Set_EF_Move3_Param(FS_2DEffect_Info *p_EF_Info,float dx,float dy,float dz,float dMove,int p_Parm);
	bool	Set_EF_Start_Pos(FS_2DEffect_Info *p_EF_Info,float dx,float dy,float dz);
	bool	Set_EF_End_Pos(FS_2DEffect_Info *p_EF_Info,float dx,float dy,float dz);
	bool	Set_EF_Result(FS_2DEffect_Info *p_EF_Info,int p_Result1,int p_Result2);
	bool	Set_EF_Number(FS_2DEffect_Info *p_EF_Info,int p_Number);
	bool	Set_EF_Text_Pos(FS_2DEffect_Info *p_EF_Info,FS_Sprite *p_Text,float dx,float dy,float dz,float scale);
	
	FS_2DEffect_Info	*Get_Conflict(FS_XYZW *p_Rect);
	
public:
	static BOOL	Delete_Effect(LPVOID p_2DEffect);
	static FS_2DEffect *Alloc_2DEffect();
};
