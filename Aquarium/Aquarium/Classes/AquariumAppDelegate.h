//
//  AquariumAppDelegate.h
//  Aquarium
//
//  Created by zendiya on 11. 4. 29..
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "GLView.h"

@interface AquariumAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
	GLView	*m_View;
	int	m_Reset_TF;

}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet GLView	*m_View;

@end

