
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "F_3D_MATH.h"

//	내부 변수
float FS_XY::Degree_X(float p_X,float p_Y)
{
	float t_Len = sqrtf(p_X*p_X + p_Y*p_Y);
	if(t_Len < 0.00001f)
		return 0.0f;
	if(p_Y < 0.0f)
	{
		return FD_Degree(-acosf(p_X/t_Len));
	}
	return FD_Degree(acosf(p_X/t_Len));
}

FS_XYZ FS_XYZ::operator + (const FS_XYZ & Tg)
{
	FS_XYZ		Rt;
	Rt.m_X = m_X + Tg.m_X;
	Rt.m_Y = m_Y + Tg.m_Y;
	Rt.m_Z = m_Z + Tg.m_Z;
	return Rt;
}

FS_XYZ FS_XYZ::operator - (const FS_XYZ & Tg)
{
	FS_XYZ		Rt;
	Rt.m_X = m_X - Tg.m_X;
	Rt.m_Y = m_Y - Tg.m_Y;
	Rt.m_Z = m_Z - Tg.m_Z;
	return Rt;
}

FS_XYZ FS_XYZ::operator * (const float & Tg)
{
	FS_XYZ		Rt;
	Rt.m_X = m_X * Tg;
	Rt.m_Y = m_Y * Tg;
	Rt.m_Z = m_Z * Tg;
	return Rt;
}

FS_XYZ FS_XYZ::operator / (const float & Tg)
{
	FS_XYZ		Rt;
	Rt.m_X = m_X / Tg;
	Rt.m_Y = m_Y / Tg;
	Rt.m_Z = m_Z / Tg;
	return Rt;
}

//	외적
FS_XYZ	FS_XYZ::Cross(FS_XYZ &V1,FS_XYZ &V2)
{
	FS_XYZ		Rt;
	Rt.m_X = V1.m_Y * V2.m_Z - V1.m_Z * V2.m_Y;
	Rt.m_Y = V1.m_Z * V2.m_X - V1.m_X * V2.m_Z;
	Rt.m_Z = V1.m_X * V2.m_Y - V1.m_Y * V2.m_X;
	return Rt;
}
//	내적
float	FS_XYZ::Dot(FS_XYZ &V1,FS_XYZ &V2)
{
	float		Rt;
	Rt = V1.m_X * V2.m_X + V1.m_Y * V2.m_Y + V1.m_Z * V2.m_Z;
	return Rt;
}
//	길이
float	FS_XYZ::Len(FS_XYZ &V)
{
	float	len = V.m_X*V.m_X + V.m_Y*V.m_Y + V.m_Z*V.m_Z;
	len = sqrtf(len);
	return len;
}

//	노말
FS_XYZ	FS_XYZ::Normal(FS_XYZ &V)
{
	//	±Ê¿Ã∞° 1¿Œ ∫§≈Õ
	FS_XYZ		Rt;
	Rt = V/Len(V);
	return Rt;
}

//	회전각 사원수 설정
bool FS_XYZW::Axis_Angle(FS_XYZW *p_Quaternion,float p_Axis_X,float p_Axis_Y,float p_Axis_Z,float p_Degree)
{
	if(p_Quaternion == NULL)
		return false;
	//	라디안 값 얻기
	float t_Radian = FD_Radian(p_Degree);
	float t_Sin = (float)sinf( t_Radian / 2.0f ); //theta값을 위한 식
	
	p_Quaternion->m_W = (float)cosf( t_Radian / 2.0f );
	p_Quaternion->m_X = p_Axis_X * t_Sin;
	p_Quaternion->m_Y = p_Axis_Y * t_Sin;
	p_Quaternion->m_Z = p_Axis_Z * t_Sin;  
	return true;
}

//	회전 사원수에서 회전각 얻기
float FS_XYZW::Get_Quaternion_Degree(FS_XYZW *p_Quat_In)
{
	if(p_Quat_In == NULL)
		return 0.0f;
	float t_Degree = FD_Degree(2.0f*acosf(p_Quat_In->m_W));
	return t_Degree;
}

//	회전 사원수에서 회전축 얻기
bool FS_XYZW::Get_Quaternion_Axis(FS_XYZW *p_Quat_In,FS_XYZ *p_Axis_Out)
{
	if(p_Quat_In == NULL)
		return false;
	if(p_Axis_Out == NULL)
		return false;
	float t_Sin = sinf(acosf(p_Quat_In->m_W));
	if((t_Sin > -0.00001f)&&(t_Sin < 0.00001f))
	{
		return false;
	}
	else 
	{
		p_Axis_Out->m_X = p_Quat_In->m_X/t_Sin;
		p_Axis_Out->m_Y = p_Quat_In->m_Y/t_Sin;
		p_Axis_Out->m_Z = p_Quat_In->m_Z/t_Sin;
	}
	return	true;
}

/*
	행렬
 */
FS_MATRIX::FS_MATRIX()
{
	m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
	m[0][1] = m[0][2] = m[0][3] = 0.0f;
	m[1][0] = m[1][2] = m[1][3] = 0.0f;
	m[2][0] = m[2][1] = m[2][3] = 0.0f;
	m[3][0] = m[3][1] = m[3][2] = 0.0f;
}

//	단위 행렬 설정
bool FS_MATRIX::Identity(FS_MATRIX *p_Mat)
{
	if(p_Mat == NULL)
		return false;
	p_Mat->m[0][0] = p_Mat->m[1][1] = p_Mat->m[2][2] = p_Mat->m[3][3] = 1.0f;
	p_Mat->m[0][1] = p_Mat->m[0][2] = p_Mat->m[0][3] = 0.0f;
	p_Mat->m[1][0] = p_Mat->m[1][2] = p_Mat->m[1][3] = 0.0f;
	p_Mat->m[2][0] = p_Mat->m[2][1] = p_Mat->m[2][3] = 0.0f;
	p_Mat->m[3][0] = p_Mat->m[3][1] = p_Mat->m[3][2] = 0.0f;
	return true;
}

//	이동 행렬 설정
bool	FS_MATRIX::Translate(FS_MATRIX *p_Mat,float p_x,float p_y,float p_z)
{
	if(p_Mat == NULL)
		return false;
	FS_MATRIX::Identity(p_Mat);
	p_Mat->m[3][0] = p_x;
	p_Mat->m[3][1] = p_y;
	p_Mat->m[3][2] = p_z;
	return true;
}

//	크기행렬
bool	FS_MATRIX::Scale(FS_MATRIX *p_Mat,float p_x,float p_y,float p_z)
{
	if(p_Mat == NULL)
		return false;
	p_Mat->m[0][0] = p_x;
	p_Mat->m[1][1] = p_y;
	p_Mat->m[2][2] = p_z;
	p_Mat->m[3][3] = 1.0f;
	p_Mat->m[0][1] = p_Mat->m[0][2] = p_Mat->m[0][3] = 0.0f;
	p_Mat->m[1][0] = p_Mat->m[1][2] = p_Mat->m[1][3] = 0.0f;
	p_Mat->m[2][0] = p_Mat->m[2][1] = p_Mat->m[2][3] = 0.0f;
	p_Mat->m[3][0] = p_Mat->m[3][1] = p_Mat->m[3][2] = 0.0f;
	return true;
}

//	회전 행렬 설정
bool	FS_MATRIX::Rot(FS_MATRIX *p_Mat,float p_x,float p_y,float p_z,float p_Degree)
{
	if(p_Mat == NULL)
		return false;
	FS_XYZW	t_Quat;
	FS_XYZW::Axis_Angle(&t_Quat,p_x,p_y,p_z,p_Degree);
	return FS_MATRIX::Rot(p_Mat,&t_Quat);
}

bool	FS_MATRIX::Rot(FS_MATRIX *p_Mat,FS_XYZW *p_Quat)
{
	if(p_Mat == NULL)
		return false;
	/*
	[ 1-(2yy+2zz)       2xy+2zw      2xz-2yw        0 ]
	[ 2xy-2zw        1-(2xx+2zz)     2zy+2xw        0 ]
	[ 2xz+2yw         2yz-2xw     1-(2xx+2yy)       0 ]
	[    0             0            0             1 ]
	 */
	p_Mat->m[0][0] = 1.0f - 2.0f*(p_Quat->m_Y*p_Quat->m_Y + p_Quat->m_Z*p_Quat->m_Z);
	p_Mat->m[0][1] = 2.0f*(p_Quat->m_X*p_Quat->m_Y + p_Quat->m_Z*p_Quat->m_W);
	p_Mat->m[0][2] = 2.0f*(p_Quat->m_X*p_Quat->m_Z - p_Quat->m_Y*p_Quat->m_W);
	p_Mat->m[0][3] = 0.0f;
	
	p_Mat->m[1][0] = 2.0f*(p_Quat->m_X*p_Quat->m_Y - p_Quat->m_Z*p_Quat->m_W);
	p_Mat->m[1][1] = 1.0f - 2.0f*(p_Quat->m_X*p_Quat->m_X + p_Quat->m_Z*p_Quat->m_Z);
	p_Mat->m[1][2] = 2.0f*(p_Quat->m_Z*p_Quat->m_Y + p_Quat->m_X*p_Quat->m_W);
	p_Mat->m[1][3] = 0.0f;
	
	p_Mat->m[2][0] = 2.0f*(p_Quat->m_X*p_Quat->m_Z + p_Quat->m_Y*p_Quat->m_W);
	p_Mat->m[2][1] = 2.0f*(p_Quat->m_Y*p_Quat->m_Z - p_Quat->m_X*p_Quat->m_W);
	p_Mat->m[2][2] = 1.0f - 2.0f*(p_Quat->m_X*p_Quat->m_X + p_Quat->m_Y*p_Quat->m_Y);
	p_Mat->m[2][3] = 0.0f;
	
	p_Mat->m[3][0] = 0.0f;
	p_Mat->m[3][1] = 0.0f;
	p_Mat->m[3][2] = 0.0f;
	p_Mat->m[3][3] = 1.0f;
	return true;
}

//	두행렬 곱
bool FS_MATRIX::Mult(FS_MATRIX *p_Out,FS_MATRIX *A,FS_MATRIX *B)
{
	if(p_Out == NULL)
		return false;
	if(A == NULL)
		return false;
	if(B == NULL)
		return false;
	if(B == A)
		return false;
	FS_MATRIX m;
	m.m[0][0] = A->m[0][0] * B->m[0][0] + A->m[0][1] * B->m[1][0] + A->m[0][2] * B->m[2][0] + A->m[0][3] * B->m[3][0];
	m.m[0][1] = A->m[0][0] * B->m[0][1] + A->m[0][1] * B->m[1][1] + A->m[0][2] * B->m[2][1] + A->m[0][3] * B->m[3][1];
	m.m[0][2] = A->m[0][0] * B->m[0][2] + A->m[0][1] * B->m[1][2] + A->m[0][2] * B->m[2][2] + A->m[0][3] * B->m[3][2];
	m.m[0][3] = A->m[0][0] * B->m[0][3] + A->m[0][1] * B->m[1][3] + A->m[0][2] * B->m[2][3] + A->m[0][3] * B->m[3][3];
	m.m[1][0] = A->m[1][0] * B->m[0][0] + A->m[1][1] * B->m[1][0] + A->m[1][2] * B->m[2][0] + A->m[1][3] * B->m[3][0];
	m.m[1][1] = A->m[1][0] * B->m[0][1] + A->m[1][1] * B->m[1][1] + A->m[1][2] * B->m[2][1] + A->m[1][3] * B->m[3][1];
	m.m[1][2] = A->m[1][0] * B->m[0][2] + A->m[1][1] * B->m[1][2] + A->m[1][2] * B->m[2][2] + A->m[1][3] * B->m[3][2];
	m.m[1][3] = A->m[1][0] * B->m[0][3] + A->m[1][1] * B->m[1][3] + A->m[1][2] * B->m[2][3] + A->m[1][3] * B->m[3][3];
	m.m[2][0] = A->m[2][0] * B->m[0][0] + A->m[2][1] * B->m[1][0] + A->m[2][2] * B->m[2][0] + A->m[2][3] * B->m[3][0];
	m.m[2][1] = A->m[2][0] * B->m[0][1] + A->m[2][1] * B->m[1][1] + A->m[2][2] * B->m[2][1] + A->m[2][3] * B->m[3][1];
	m.m[2][2] = A->m[2][0] * B->m[0][2] + A->m[2][1] * B->m[1][2] + A->m[2][2] * B->m[2][2] + A->m[2][3] * B->m[3][2];
	m.m[2][3] = A->m[2][0] * B->m[0][3] + A->m[2][1] * B->m[1][3] + A->m[2][2] * B->m[2][3] + A->m[2][3] * B->m[3][3];
	m.m[3][0] = A->m[3][0] * B->m[0][0] + A->m[3][1] * B->m[1][0] + A->m[3][2] * B->m[2][0] + A->m[3][3] * B->m[3][0];
	m.m[3][1] = A->m[3][0] * B->m[0][1] + A->m[3][1] * B->m[1][1] + A->m[3][2] * B->m[2][1] + A->m[3][3] * B->m[3][1];
	m.m[3][2] = A->m[3][0] * B->m[0][2] + A->m[3][1] * B->m[1][2] + A->m[3][2] * B->m[2][2] + A->m[3][3] * B->m[3][2];
	m.m[3][3] = A->m[3][0] * B->m[0][3] + A->m[3][1] * B->m[1][3] + A->m[3][2] * B->m[2][3] + A->m[3][3] * B->m[3][3];
	memcpy(p_Out,&m,sizeof(FS_MATRIX));
	return true;
}