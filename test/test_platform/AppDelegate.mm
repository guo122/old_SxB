//
//  AppDelegate.m
//  Test1
//
//  Created by quku on 2019/3/15.
//  Copyright © 2019 quku. All rights reserved.
//

//#define VERTICAL_SCREEN_HEIGHT MAX([UIScreen mainScreen].bounds.size.width, [UIScreen mainScreen].bounds.size.height)
//
//#define VERTICAL_SCREEN_WIDTH  MIN([UIScreen mainScreen].bounds.size.width, [UIScreen mainScreen].bounds.size.height)
//
//#define IS_IPHONE_5     (IS_IPHONE && (VERTICAL_SCREEN_HEIGHT == 568.f))
//#define IS_IPHONE_6     (IS_IPHONE && (VERTICAL_SCREEN_HEIGHT == 568.f))
//#define IS_IPHONE_7     (IS_IPHONE && (VERTICAL_SCREEN_HEIGHT == 568.f))
//#define IS_IPHONE_8     (IS_IPHONE && (VERTICAL_SCREEN_HEIGHT == 568.f))
//
//#define IS_IPHONE_4     (IS_IPHONE && (VERTICAL_SCREEN_HEIGHT == 480.f))
//

//#include "bgfx/bgfx.h"
//#include "bgfx/platform.h"
//#include "bx/bx.h"

#import "AppDelegate.h"

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
    self.device = MTLCreateSystemDefaultDevice();
    self.metalLayer = [CAMetalLayer new];
    
    self.metalLayer.device = self.device;

//    self.window = [[UIWindow alloc] initWithFrame:
//                   [[UIScreen mainScreen] bounds]];
    self.window = [[UIWindow alloc] initWithFrame:CGRectMake(0, 0, 320, 568)];
    //CGRect tmpR = [[UIScreen mainScreen]bounds];
    self.window.backgroundColor = [UIColor whiteColor];
    self.vc = [[ViewController alloc]init];
    UINavigationController *nav = [[UINavigationController alloc]initWithRootViewController:self.vc];
    [self.window setRootViewController:nav];
    
    [self.window makeKeyAndVisible];
    
    self.metalLayer.frame = self.window.layer.frame;
    
    CGSize drawableSize = self.window.bounds.size;
    

    drawableSize.width *= self.window.contentScaleFactor;
    drawableSize.height *= self.window.contentScaleFactor;
    self.metalLayer.drawableSize = drawableSize;

    
    [self.window.layer addSublayer:self.metalLayer];

//    bgfx::PlatformData pd;
//    pd.nwh = (__bridge void *)self.metalLayer;
//    bgfx::setPlatformData(pd);
//
//    bgfx::Init bgfxInit;
//    bgfxInit.type = bgfx::RendererType::Count; // Automatically choose a renderer.
//    bgfxInit.resolution.width = 1280;
//    bgfxInit.resolution.height = 720;
//    bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
//    bgfx::init(bgfxInit);
//    bgfx::setDebug(BGFX_DEBUG_TEXT);
//
//    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
//    bgfx::setViewRect(0, 0, 0, 1280, 720);
//
//
//    bgfx::touch(0);
//    bgfx::frame();
    NSString * bundlePath = [[ NSBundle mainBundle] pathForResource: @ "Settings" ofType :@ "bundle"];
    if (bundlePath)
    {
        NSLog(bundlePath);
    }
    else
    {
        NSLog("----failed----");
    }
    //NSBundle *resourceBundle = [NSBundle bundleWithPath:bundlePath];
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}


- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}


@end
