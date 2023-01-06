#pragma once
#include <math.h>
#include "F_IDCode.h"

#define FD_PI    ((float)  3.141592654f)
#define FD_Radian( Degree ) (((Degree) * FD_PI) / 180.0f)
#define FD_Degree( Radian ) (((Radian) * 180.0f) / FD_PI)

//	색상 구조체
struct	FS_RGBA
{
	float	m_R;
	float	m_G;
	float	m_B;
	float	m_A;
};

//	2차원 좌표
struct	FS_XY
{
	float	m_X;
	float	m_Y;
	
	//	내부 변수
	static	float	Degree_X(float p_X,float p_Y);
};

//	3차원 좌표
struct	FS_XYZ
{
	float	m_X;
	float	m_Y;
	float	m_Z;
	
	FS_XYZ operator + (const FS_XYZ & Tg);
	FS_XYZ operator - (const FS_XYZ & Tg);
	FS_XYZ operator * (const float & Tg);
	FS_XYZ operator / (const float & Tg);

	//	외적
	static FS_XYZ	Cross(FS_XYZ &V1,FS_XYZ &V2);
	//	내적
	static float	Dot(FS_XYZ &V1,FS_XYZ &V2);
	//	길이 구하기
	static float	Len(FS_XYZ &V);
	//	노말 백터 구하기
	static FS_XYZ	Normal(FS_XYZ &V);
};

//	4차원 좌표
struct	FS_XYZW
{
	float	m_X;
	float	m_Y;
	float	m_Z;
	float	m_W;
	
	//	회전각 사원수 설정
	static bool Axis_Angle(FS_XYZW *p_Quaternion,float p_Axis_X,float p_Axis_Y,float p_Axis_Z,float p_Degree);
	//	회전 사원수에서 회전각 얻기
	static float Get_Quaternion_Degree(FS_XYZW *p_Quat_In);
	//	회전 사원수에서 회전축 얻기(회전각이 0에 가까운경우 알수 없다)
	static bool Get_Quaternion_Axis(FS_XYZW *p_Quat_In,FS_XYZ *p_Axis_Out);
};

//	정점 블렝딩 구조체
struct	FS_XYZB3
{
	FS_XYZ	m_XYZ;
	float	m_W1;
	float	m_W2;
	DWORD	m_Index;
};


//	4*4 행렬
struct	FS_MATRIX
{
    union 
	{
        struct 
		{
            float        _11, _12, _13, _14;
            float        _21, _22, _23, _24;
            float        _31, _32, _33, _34;
            float        _41, _42, _43, _44;

        };

        float m[4][4];
    };
	//	행렬 초기화
	FS_MATRIX();
	
	//	단위 행렬 설정
	static bool Identity(FS_MATRIX *p_Mat);
	//	이동 행렬 설정
	static bool	Translate(FS_MATRIX *p_Mat,float p_x,float p_y,float p_z);
	//	크기행렬
	static bool	Scale(FS_MATRIX *p_Mat,float p_x,float p_y,float p_z);
	//	회전 행렬 설정
	static bool	Rot(FS_MATRIX *p_Mat,float p_x,float p_y,float p_z,float p_Degree);
	static bool	Rot(FS_MATRIX *p_Mat,FS_XYZW *p_Quat);
	
	//	두행렬 곱
	static bool Mult(FS_MATRIX *p_Out,FS_MATRIX *A,FS_MATRIX *B);
};
