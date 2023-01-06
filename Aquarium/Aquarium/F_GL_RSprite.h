/*
 *  F_GL_RSprite.h
 *  Raising Fish
 *
 *  Created by zendiya on 11. 4. 20..
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "F_GL_2DEffect.h"

struct FS_RSprite
{
	int			m_Index;
	int			m_Type;		
	float		m_Time;		
	FS_Sprite	*m_Sprite;
	FS_Sprite	*m_SubSprite;	
	int			m_View_Type;	
	int			m_Y_Rot;		
	
	FS_XYZ		m_Pos;		
	FS_XYZ		m_Scale;
	FS_XYZW		m_Rote;			
	FS_MATRIX	m_Mat;			
	FS_MATRIX	m_SubMat;
	float		m_Scale_f;		
	
	int			m_Update;			
	int			m_Button_TF;		
	int			m_Button_State;		
	FS_XYZW		m_Button_Rect;		
	int			m_Button_Return;	
	
	int			m_Out_Number;	
	int			m_Add_Number;		
	
	int			m_Ani_X;
	int			m_Ani_Y;
	float		m_Ani_Time;	
	
	int			m_Rand_int;	
	int			m_Wait_Count;	
	int			m_Wait_Current;	
	
	FS_XYZW		m_Move_Dir1;	
	FS_XYZW		m_Move_Dir2;	
	FS_XYZW		m_Move_Dir3;	
	int			m_Move_Param1;	
	int			m_Move_Param2;
	int			m_Move_Param3;
	
	int			m_EF_Index;		
	int			m_Sub_Sprite_Type;
	int			m_Sub_Sprite_X;
	int			m_Sub_Sprite_Y;
	FS_XYZW		m_Sub_Sprite_Pos;
};

class F_GL_RSprite
{
public:
	F_GL_RSprite();
	~F_GL_RSprite();
	
public:
	FS_LList	*m_List;
	FS_XY	m_Rot_UV[6];
	
	F_GL_2DEffect	*m_Effect;
    FS_RSprite *m_Select;
	
public:
	bool	Init(F_GL_2DEffect *p_Effect);
	bool	Release_List();
	FS_RSprite	*Insert(int p_Index,FS_Sprite *p_Sprite);
	bool	Delete(int p_Index);
	FS_LList	*Find(int p_Index);
	FS_RSprite	*Find_Data(int p_Index);
    bool	Set_Sub_Sprite(int p_Index,FS_Sprite *p_Sprite);
	bool	Set_Sub_Sprite_Type(int p_Index,int p_Type,int p_X = 0,int p_Y = 0);
	bool	Set_Sub_Sprite_Pos(int p_Index,float p_X,float p_Y,float p_Z,float p_Scale);

	bool	Render_Sprite(FS_RSprite *p_Sprite,float p_DTime);
	bool	Pre_Render_Sprite(FS_RSprite *p_Sprite,float p_DTime);
	
	bool	Render(float p_DTime);
	bool	Pre_Render(float p_DTime);
	
	bool	Set_RS_Type(FS_RSprite *p_Sprite,int p_Type);
	bool	Set_RS_Pos(FS_RSprite *p_Sprite,float x, float y, float z);
	bool	Set_RS_Scale(FS_RSprite *p_Sprite,float sx,float sy, float sz);
	bool	Set_RS_Rot(FS_RSprite *p_Sprite,float dx,float dy,float dz,float degree);
	
	bool	Set_RS_Ani(FS_RSprite *p_Sprite,int p_X,int p_Y,float p_Time);
	bool	Update_RS_Time(FS_RSprite *p_Sprite,float p_Time);
	
	bool	Calcul_Mat(FS_RSprite *p_Sprite,int p_Sub_Type = 0,float p_Time = 0.0f);
	bool	Set_Update(FS_RSprite *p_Sprite,int p_Type);
	bool	Set_View_Type(FS_RSprite *p_Sprite,int p_Type);
	
	bool	Set_RS_Move1_Param(FS_RSprite *p_Sprite,float dx,float dy,float dz,float dMove,int p_Parm);
	bool	Set_RS_Move2_Param(FS_RSprite *p_Sprite,float dx,float dy,float dz,float dMove,int p_Parm);
	bool	Set_RS_Move3_Param(FS_RSprite *p_Sprite,float dx,float dy,float dz,float dMove,int p_Parm);
	
	bool	Set_RS_Wait_Count(FS_RSprite *p_Sprite,int p_Wait_C,int p_Rand_Max);
    bool	Set_Scale_F(FS_RSprite *p_Sprite,float p_ScaleF);
    bool	Set_Button_Return(FS_RSprite *p_Sprite,int p_Return);
	bool	Set_Button_OnOff(FS_RSprite *p_Sprite,int p_OnOff);
	
	bool	Set_RS_Effect_ID(FS_RSprite *p_Sprite,int p_Effect_ID);
    bool	Set_RS_Z_Rot(FS_RSprite *p_Sprite,int p_ZRot);
    bool	Set_Out_Number(FS_RSprite *p_Sprite,int p_Number,int p_Add_Number = 0);
	

	bool	Mouse_Down(FS_XYZ *p_Pos,FS_XYZ *p_Dir);
	int		Mouse_Up(FS_XYZ *p_Pos,FS_XYZ *p_Dir);
	bool	Mouse_Move(FS_XYZ *p_Pos,FS_XYZ *p_Dir);
	
public:
	static FS_RSprite *Alloc();
	static BOOL	Delete(LPVOID p_RSprite);
};

