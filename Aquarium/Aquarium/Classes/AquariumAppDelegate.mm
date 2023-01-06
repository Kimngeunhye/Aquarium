//
//  AquariumAppDelegate.m
//  Aquarium
//
//  Created by zendiya on 11. 4. 29..
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "AquariumAppDelegate.h"
#include "F_IOS_File.h"

@implementation AquariumAppDelegate

@synthesize window;
@synthesize m_View;


#pragma mark -
#pragma mark Application lifecycle

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    
    
    // Override point for customization after application launch.
	m_Reset_TF = 0;
	if(m_View != nil)
	{
		[self.window addSubview: m_View];
	}
	
    [self.window makeKeyAndVisible];
    
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {

	m_View.m_AnimationInterval = 1.0 / 5.0;

}


- (void)applicationDidEnterBackground:(UIApplication *)application {

	if(m_View != nil)
	{
		[m_View Delete_Interface];
		m_Reset_TF = 1;
	}
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
  
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    
	if(m_View != nil)
	{
		if(m_Reset_TF == 1)
		{
			[m_View Init_Interface];
			m_Reset_TF = 0;
		}
	}
	m_View.m_AnimationInterval = 1.0 / 60.0;
}


- (void)applicationWillTerminate:(UIApplication *)application {
    
	if(m_View != nil)
	{
		[m_View Delete_Interface];
		m_Reset_TF = 1;
	}
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {

	
}


- (void)dealloc {
    [window release];
	[m_View release];
    [super dealloc];
}


@end
