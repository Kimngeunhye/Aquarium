//
//  GLView.m
//
//  Created by zendiya on 11. 4. 29..
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "GLView.h"
#include "F_IOS_File.h"

#define GL_RENDERBUFFER 0x8d41

@implementation GLView

@synthesize m_AnimationTimer;
@synthesize m_AnimationInterval;

+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

//- (id)initWithFrame:(CGRect)frame {
- (id)initWithCoder:(NSCoder*)coder {
	
    //self = [super initWithFrame:frame];
    self = [super initWithCoder:coder];
	F_IOS_File::Set_GLView((void *)self);
    if (self) 
	{
		CGRect screenBounds = [[UIScreen mainScreen] bounds];

		m_Screen_W =CGRectGetWidth(screenBounds);
		m_Screen_H =CGRectGetHeight(screenBounds);
        m_EAGL_Layer = (CAEAGLLayer*) self.layer;
		if(m_EAGL_Layer != nil)
		{
			m_EAGL_Layer.opaque = YES;
		}
		
		m_Ver_OpenGL = 0;
		m_Context = nil;//[[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
		if (m_Context == nil) 
		{
			m_Context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
			if(m_Context == nil)
			{
				[self release];
				return nil;
			}
			else 
			{
				m_Ver_OpenGL = 1;
			}
			
		}
		else 
		{
			m_Ver_OpenGL = 2;
		}
		
		if(![EAGLContext setCurrentContext:m_Context])
		{
			[m_Context release];
			[self release];
			return nil;
		}
		
		[self Init_Interface];
		
		m_Time_Main = CACurrentMediaTime();
		m_AnimationInterval = 1.0 / 60.0;
		[self startAnimation];
    }
    return self;
}

-(bool)Init_Interface
{
	m_Interface = F_IOS_Interface::Create_GL_Interface(m_Ver_OpenGL);
	if (m_Interface == nil)
	{
		[m_Context release];
		[self release];
		return false;
	}
	[m_Context renderbufferStorage:GL_RENDERBUFFER fromDrawable:m_EAGL_Layer];
	
	m_Interface->Reset_Rotate(3);	
	if(!m_Interface->Init_Screen(m_Screen_W,m_Screen_H))
	{
		F_IOS_Interface::Release_Interface(m_Interface);
		m_Interface = nil;
		[m_Context release];
		[self release];
		return false;
	}
	return true;
}

-(bool)Delete_Interface
{	
	if(m_Interface != nil)
	{
		m_Interface->Save_Data();
		
		F_IOS_Interface::Release_Interface(m_Interface);
		m_Interface = nil;
	}
	return true;
}

/*
 // Only override drawRect: if you perform custom drawing.
 // An empty implementation adversely affects performance during animation.
 - (void)drawRect:(CGRect)rect {
 // Drawing code.
 }
 */
- (void)didRotate: (NSNotification*) notification
{
	 
}

- (void) drawView//: (CADisplayLink*) displayLink
{
	if(m_Interface != nil)
	{
		[EAGLContext setCurrentContext:m_Context];

		float t_Current_Time = CACurrentMediaTime();
		float t_Time_Move = t_Current_Time - m_Time_Main;
		m_Time_Main = t_Current_Time;
		m_Interface->Pre_Render(t_Time_Move);
		m_Interface->Render(t_Time_Move);
		[m_Context presentRenderbuffer:GL_RENDERBUFFER_OES];//GL_RENDERBUFFER];
	}
}

-(void)layoutSubviews
{
	[self drawView];
}
//	터치 스크린 입력 이벤트
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	UITouch *t_Touch = [touches anyObject];
	CGPoint t_Point = [t_Touch locationInView:self];
	if(m_Interface != nil)
	{
		m_Interface->Touch_On(t_Point.x,t_Point.y);
	}
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	UITouch *t_Touch = [touches anyObject];
	CGPoint t_Point = [t_Touch locationInView:self];
	if(m_Interface != nil)
	{
		m_Interface->Touch_Off(t_Point.x,t_Point.y);
	}
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{	
	UITouch *t_Touch = [touches anyObject];
	CGPoint t_OldPoint = [t_Touch previousLocationInView:self];
	CGPoint t_Point = [t_Touch locationInView:self];
	if(m_Interface != NULL)
	{
		m_Interface->Touch_Move(t_OldPoint.x,t_OldPoint.y,t_Point.x,t_Point.y);
	}
}

- (void)startAnimation {
    self.m_AnimationTimer = [NSTimer scheduledTimerWithTimeInterval:m_AnimationInterval target:self selector:@selector(drawView) userInfo:nil repeats:YES];
}


- (void)stopAnimation {
    self.m_AnimationTimer = nil;
}


- (void)setAnimationTimer:(NSTimer *)newTimer {
    [m_AnimationTimer invalidate];
    m_AnimationTimer = newTimer;
}


- (void)setAnimationInterval:(NSTimeInterval)interval {
    
    m_AnimationInterval = interval;
    if (m_AnimationTimer) {
        [self stopAnimation];
        [self startAnimation];
    }
}

- (UIImage *) Create_Image_Text:(int)p_X :(int)p_Y:(char *)p_String
{
	UIImage	*t_Return = nil;
	if(p_String == nil)
		return nil;
	if(m_Text_View == nil)
		return nil;
	m_Text_View.hidden = NO;
	[m_Text_View Set_Text:p_String];
	[m_Text_View setNeedsDisplay];
	t_Return = [m_Text_View CreateImageWith:p_X :p_Y];
	m_Text_View.hidden = YES;
	return t_Return;
}

- (void)dealloc {
	F_IOS_File::Set_GLView(NULL);
	
    [self stopAnimation];
	
	if(m_Interface != nil)
	{
		F_IOS_Interface::Release_Interface(m_Interface);
		m_Interface = nil;
	}
	[m_Context release];
	[m_Text_View release];
	
    [super dealloc];
}
@end

