/*
 *  F_IOS_Audio.h
 *  Raising Fish
 *
 *  Created by zendiya on 11. 4. 27..
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

// 음악 출력 구조체
struct FS_IO_Wave
{
	int		m_Play_TF;
	void	*m_Audio;			// 배경음
	unsigned long	m_Sound;	// 효과음 id
};

//	오디오 관려 처리 클래스
class	F_IO_Wave
{
public:
	F_IO_Wave();
	~F_IO_Wave();
	//	내부 변수
public:
	//	배경 음악
	FS_IO_Wave	m_Back;
	//	효과 음악
	FS_IO_Wave	m_Sound[10];
	
	//	내부 함수
public:
	//	삭제
	bool	Release();
	//	테스트 로드
	bool	Load_Wave();
	
	//	배경 음악 볼륨 설정
	bool	Set_Back_Sound(bool p_OnOff,float p_Volum);
	//	배경 음악 루프진행 확인
	bool	Back_Sound_Repeat();
	//	효과음 출력
	bool	Sound_Out(int p_Index);
	
	//	전역 함수
public:
	//	전역 사운드 초기화 함수
	static	bool	Init_Sound();
	//	전역 사운드 삭제 함수
	static	bool	Release_Sound();
	//	배경 사운드 진행 체크 함수
	static	bool	Check_Back_Sound();
	
	//	특정 효과음 출력 함수
	static	bool	Play_Sound(int p_Index);
	//	배경 사운드 출력 설정
	static	bool	Back_Sound_OnOff(bool p_OnOff,float p_Volum);
};
