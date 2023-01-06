//
//  GLView.h
//
//  Created by zendiya on 11. 4. 29..
//  Copyright 2011 forthen. All rights reserved.
//
#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

#include "F_IOS_Interface.h"
#import "F_IOS_View.h"


@interface GLView : UIView  {
	EAGLContext *m_Context;
	CAEAGLLayer* m_EAGL_Layer;
	int			m_Ver_OpenGL;
	float		m_Time_Main;
	int			m_Screen_W;
	int			m_Screen_H;
	F_IOS_Interface *m_Interface;
	
	IBOutlet	F_IOS_View *m_Text_View;
	
	NSTimer *m_AnimationTimer;
    NSTimeInterval m_AnimationInterval;
}

- (void) drawView;//: (CADisplayLink*) displayLink;
- (void)didRotate: (NSNotification*) notification;
- (UIImage *) Create_Image_Text:(int)p_X :(int)p_Y:(char *)p_String;

-(bool)Init_Interface;
-(bool)Delete_Interface;

@property NSTimeInterval m_AnimationInterval;
@property (nonatomic, assign) NSTimer *m_AnimationTimer;

- (void)startAnimation;
- (void)stopAnimation;
@end
