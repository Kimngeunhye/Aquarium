//
//  F_IOS_View.h
//  Aquarium
//
//  Created by zendiya on 11. 5. 1..
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

@interface F_IOS_View : UIView {

	IBOutlet	UILabel	*m_Text;
	NSString	*m_Back;
	//UILabel	*t_Text;
}

-(bool) Set_Text:(char *)p_String;
- (UIImage *) CreateImageWith:(int)p_X :(int)p_Y;
@end
