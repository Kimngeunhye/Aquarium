/*
 *  F_IOS_Audio.cpp
 *  Raising Fish
 *
 *  Created by zendiya on 11. 4. 27..
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#import <UIKit/UIKit.h>
#import <AudioToolBox/AudioServices.h>
#import <AVFoundation/AVAudioPlayer.h>
#include "F_IOS_Audio.h"

//	게임 사운드 관리  클래스
F_IO_Wave	*G_Sound = NULL;

F_IO_Wave::F_IO_Wave()
{
	memset(&m_Back,0,sizeof(FS_IO_Wave));
	memset(m_Sound,0,10*sizeof(FS_IO_Wave));
}

F_IO_Wave::~F_IO_Wave()
{
	if (m_Back.m_Audio != NULL)
	{
		AVAudioPlayer *t_Audio = (AVAudioPlayer *)m_Back.m_Audio;
		[t_Audio release];
		m_Back.m_Audio = NULL;
	}
	for(int i = 0 ; i < 10; i++)
	{
		if(m_Sound[i].m_Sound != 0)
		{
			AudioServicesDisposeSystemSoundID((SystemSoundID)m_Sound[i].m_Sound);
			m_Sound[i].m_Sound = 0;
		}
	}
}

//	삭제
bool	F_IO_Wave::Release()
{
	return true;
}

//	테스트 로드
bool	F_IO_Wave::Load_Wave()
{
	//	배경음 로딩
	NSString *soundFilePath = [[NSBundle mainBundle] pathForResource: @"back_m" ofType: @"mp3"]; 
	NSURL *fileURL = [[NSURL alloc] initFileURLWithPath: soundFilePath]; 
	
	AVAudioPlayer *t_Audio = [[AVAudioPlayer alloc] initWithContentsOfURL: fileURL error: nil]; 
	m_Back.m_Audio = (void *)t_Audio;
	[fileURL release];
	fileURL = NULL;
	t_Audio.volume = 0.1f;
	[t_Audio prepareToPlay];
	
	//	효과음 설정.
	soundFilePath = [[NSBundle mainBundle] pathForResource: @"click" ofType: @"wav" inDirectory:@"/"]; 
	fileURL = [[NSURL alloc] initFileURLWithPath: soundFilePath];
	CFURLRef baseURL = (CFURLRef)fileURL;
	AudioServicesCreateSystemSoundID(baseURL,(SystemSoundID *)&m_Sound[0].m_Sound);
	m_Sound[0].m_Play_TF = 1;
	[fileURL release]; 
	fileURL = NULL;
	baseURL = NULL;
	
	soundFilePath = [[NSBundle mainBundle] pathForResource: @"yes" ofType: @"wav" inDirectory:@"/"]; 
	fileURL = [[NSURL alloc] initFileURLWithPath: soundFilePath];
	baseURL = (CFURLRef)fileURL; 
	AudioServicesCreateSystemSoundID(baseURL,(SystemSoundID *)&m_Sound[1].m_Sound);
	m_Sound[1].m_Play_TF = 2;
	[fileURL release]; 
	fileURL = NULL;
	baseURL = NULL;
	
	soundFilePath = [[NSBundle mainBundle] pathForResource: @"yes2" ofType: @"wav" inDirectory:@"/"]; 
	fileURL = [[NSURL alloc] initFileURLWithPath: soundFilePath];
	baseURL = (CFURLRef)fileURL;  
	AudioServicesCreateSystemSoundID(baseURL,(SystemSoundID *)&m_Sound[2].m_Sound);
	m_Sound[2].m_Play_TF = 3;
	[fileURL release]; 
	fileURL = NULL;
	baseURL = NULL;
	
	soundFilePath = [[NSBundle mainBundle] pathForResource: @"damg" ofType: @"wav" inDirectory:@"/"]; 
	fileURL = [[NSURL alloc] initFileURLWithPath: soundFilePath];
	baseURL = (CFURLRef)fileURL; 
	AudioServicesCreateSystemSoundID(baseURL,(SystemSoundID *)&m_Sound[3].m_Sound);
	m_Sound[3].m_Play_TF = 4;
	[fileURL release]; 
	fileURL = NULL;
	baseURL = NULL;
		
	soundFilePath = [[NSBundle mainBundle] pathForResource: @"end" ofType: @"wav" inDirectory:@"/"]; 
	fileURL = [[NSURL alloc] initFileURLWithPath: soundFilePath];
	baseURL = (CFURLRef)fileURL; 
	AudioServicesCreateSystemSoundID(baseURL,(SystemSoundID *)&m_Sound[4].m_Sound);
	m_Sound[4].m_Play_TF = 5;
	[fileURL release]; 
	fileURL = NULL;
	baseURL = NULL;
	return true;
}

//	배경 음악 볼륨 설정
bool	F_IO_Wave::Set_Back_Sound(bool p_OnOff,float p_Volum)
{
	AVAudioPlayer *t_Audio = (AVAudioPlayer *)m_Back.m_Audio;
	if(t_Audio == NULL)
		return false;
	m_Back.m_Play_TF = p_OnOff;
	t_Audio.volume = p_Volum;
	if(m_Back.m_Play_TF)
	{
		[t_Audio play];
	}
	else 
	{
		[t_Audio stop];
	}
	return true;
}

//	배경 음악 루프진행 확인
bool	F_IO_Wave::Back_Sound_Repeat()
{
	AVAudioPlayer *t_Audio = (AVAudioPlayer *)m_Back.m_Audio;
	if(t_Audio == NULL)
		return false;
	if(!m_Back.m_Play_TF)
		return false;
	// 플레이 종료 확인
	if(![t_Audio isPlaying])
	{
		[t_Audio play];
	}
	return true;
}

//	효과음 출력
bool	F_IO_Wave::Sound_Out(int p_Index)
{
	if(p_Index == 0)
		return false;
	if(p_Index > 10)
		return false;
	if(m_Sound[p_Index - 1].m_Play_TF == p_Index)
	{
		//	 사운드 출력
		AudioServicesPlaySystemSound((SystemSoundID)m_Sound[p_Index - 1].m_Sound);
	}
	return true;
}

//	전역 사운드 초기화 함수
bool	F_IO_Wave::Init_Sound()
{
	F_IO_Wave::Release_Sound();
	G_Sound = new F_IO_Wave;
	if(G_Sound == NULL)
		return false;
	//	음악 파일 로딩
	G_Sound->Load_Wave();
	return true;
}

//	전역 사운드 삭제 함수
bool	F_IO_Wave::Release_Sound()
{
	if(G_Sound != NULL)
	{
		delete G_Sound;
		G_Sound = NULL;
	}
	return true;
}

//	배경 사운드 진행 체크 함수
bool	F_IO_Wave::Check_Back_Sound()
{
	if(G_Sound == NULL)
		return false;
	G_Sound->Back_Sound_Repeat();
	return true;
}

//	특정 효과음 출력 함수
bool	F_IO_Wave::Play_Sound(int p_Index)
{
	if(G_Sound == NULL)
		return false;
	if(p_Index == 0)
		return false;
	return G_Sound->Sound_Out(p_Index);
}

//	배경 사운드 출력 설정
bool	F_IO_Wave::Back_Sound_OnOff(bool p_OnOff,float p_Volum)
{
	if(G_Sound == NULL)
		return false;
	G_Sound->Set_Back_Sound(p_OnOff,p_Volum);
	return true;
}
