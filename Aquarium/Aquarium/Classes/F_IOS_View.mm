//
//  F_IOS_View.m
//  Aquarium
//
//  Created by zendiya on 11. 5. 1..
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "F_IOS_View.h"


@implementation F_IOS_View


- (id)initWithFrame:(CGRect)frame {
    
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code.
    }
    return self;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code.
}
*/

-(bool) Set_Text:(char *)p_String
{
	if(p_String == nil)
		return false;
	/*
	if(t_Text != NULL)
	{
		[t_Text release];
		t_Text = NULL;
	}
	t_Text = [[UILabel alloc] initWithFrame:CGRectMake(0,0,128,16)];
	t_Text.text = [[NSString alloc] initWithUTF8String:p_String];
	t_Text.font = [UIFont boldSystemFontOfSize:14];
	t_Text.textColor = [UIColor blackColor];
	t_Text.backgroundColor = [UIColor whiteColor];
	t_Text.adjustsFontSizeToFitWidth = YES;
	*/
	if(m_Text == nil)
		return false;
	if(m_Text.text != nil)
	{
		//[m_Text.text release];
		m_Back = m_Text.text;
		m_Text.text = NULL;
		m_Text.text = [[NSString alloc] initWithUTF8String:p_String];
	}
	return true;
}
- (UIImage *) CreateImageWith:(int)p_X :(int)p_Y
{
	UIGraphicsBeginImageContext(CGSizeMake(p_X,p_Y));
	CGContextRef context = UIGraphicsGetCurrentContext();	
	[self.layer renderInContext:context];
	UIImage *theImage = UIGraphicsGetImageFromCurrentImageContext();
	UIGraphicsEndImageContext();
	[theImage retain];
	if(m_Back !=NULL)
	{
		[m_Text.text release];
		m_Text.text = m_Back;
		m_Back = NULL;
	}
	return theImage;
}

- (void)dealloc {
	[m_Text release];
    [super dealloc];
}


@end
