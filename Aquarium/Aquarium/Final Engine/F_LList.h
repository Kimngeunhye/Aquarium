/*
 *  F_LList.h
 *  링크 리스트 클래스
 *
 *  Created by forthen on 11. 4. 18..
 *  Copyright 2011 forthen. All rights reserved.
 *
 */

#pragma once
#include "F_IDCode.h"

//	클래스 삭제 함수 타입 정의
typedef BOOL (*DELETE_LIST)(LPVOID lpThreadParameter);

//	링크 리스트 구조체 설정( 내부 데이터는 클래스 포인터 사용, m_Del가 없는 경우 malloc 할당)
struct	FS_LList
{
	FGU_ID		m_ID;		// 데이터 ID
	VOID		*m_Data;	// 내부 데이터 포인트, 클래스 포인터 또는 메모리 포이터
	DELETE_LIST	m_Del;		// 클래스 포인터인 경우 삭제 함수
	FS_LList	*m_Pre;		// 이전 리스트
	FS_LList	*m_Next;	// 다음 리스트
	
	//	초기화
	FS_LList()
	{
		m_ID.m_INT64 = 0;
		m_Data = NULL;
		m_Del = NULL;
		m_Pre = NULL;
		m_Next = NULL;
	}
	//	삭제
	~FS_LList()
	{
		if(m_Data != NULL)
		{
			if(m_Del != NULL)
			{
				m_Del(m_Data);
			}
			else
			{
				free(m_Data);
			}
			m_Data = NULL;
		}
		m_ID.m_INT64 = 0;
		m_Del = NULL;
		m_Pre = NULL;
		m_Next = NULL;
	}
};

/*
		링크 리스트 관리 클래스, 관리 클래스 목록
*/

class	F_LList
{
public:
	F_LList(void);
	~F_LList(void);
	////	전역 함수 지정
public:
	//	링크 리스트 생성
	static	FS_LList	*New();
	static	FS_LList	*New(LPVOID p_Data,DWORD p_ID = 0,DELETE_LIST	del_Fuc = NULL);
	static	FS_LList	*New(LPVOID p_Data,__int64 p_ID,DELETE_LIST	del_Fuc = NULL);
	static	FS_LList	*New(LPVOID p_Data,FGS_Code p_ID,DELETE_LIST	del_Fuc = NULL);
	
	//	지정 리스트만 삭제
	static	BOOL	Delete(FS_LList *p_List);
	//	모든 리스트 삭제
	static	BOOL	Delete_All(FS_LList *p_List);
	//	모든 데이터 삭제 (리스트는 보존)
	static	BOOL	Delete_All_Data(FS_LList *p_List);
	//	모든 리스트 삭제 (내부 데이터 포인터는 삭제 안한, 리스트의 데이터 포인터 이동에 사용)
	static	BOOL	Delete_All_NoData(FS_LList *p_List);
	
	//	지정리스트에 리스트 추가
	static	BOOL	Insert(FS_LList *p_List,FS_LList *p_Insert);
	
	//	리스트 찾기
	static	FS_LList	*Find(FS_LList *p_List,LPVOID	p_Data);
	static	FS_LList	*Find(FS_LList *p_List,DWORD p_ID);
	static	FS_LList	*Find(FS_LList *p_List,__int64 p_ID);
	static	FS_LList	*Find(FS_LList *p_List,FGS_Code p_ID);
	//	리스트 끝 찾기
	static	FS_LList	*Find_Last(FS_LList *p_List);
	
	//	리스트의 데이터 찾기
	static	LPVOID		Find_Data(FS_LList *p_List,DWORD p_ID);
	static	LPVOID		Find_Data(FS_LList *p_List,__int64 p_ID);
	static	LPVOID		Find_Data(FS_LList *p_List,FGS_Code p_ID);
	//	리스트의 개수 번호의 데이터 얻기
	static	LPVOID		Find_Data_Count(FS_LList *p_List,DWORD p_Count);
	//	리스트 개수 얻기
	static	DWORD		Get_List_Count(FS_LList *p_List);
	//	리스트의 다음 순서 위치의 리스트 얻기
	static	FS_LList	*Get_List(FS_LList *p_List,DWORD p_Num);
	
	//	리스트에서 데이터 설정 안된 리스트 얻기
	static	FS_LList	*Find_NULL(FS_LList *p_List);
	
	//	ID 기반으로 정렬 하기
	static  FS_LList    *Sort_List_Id(FS_LList *p_Root);
};
