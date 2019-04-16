//
//  AppDelegate.h
//  Test1
//
//  Created by quku on 2019/3/15.
//  Copyright © 2019 quku. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <UIKit/UIApplication.h> // UIApplicationDelegate

#import <QuartzCore/CAMetalLayer.h>
#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>

#include "ViewController.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;
@property (strong, nonatomic) ViewController *vc;
@property (strong, nonatomic) CAMetalLayer *metalLayer;
@property (strong, nonatomic) id<MTLDevice> device;
@end
