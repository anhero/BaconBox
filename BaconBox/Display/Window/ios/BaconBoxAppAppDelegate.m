#import "BaconBoxAppAppDelegate.h"

#import "EAGLView.h"

#import "BaconBoxAppViewController.h"
#include <BaconBox/Display/Driver/GraphicDriver.h>
#include "MainWindow.h"


#import "DDLog.h"
#import "DDTTYLogger.h"
#import "HTTPServer.h"
#import "DAVConnection.h"


static const int ddLogLevel = LOG_LEVEL_VERBOSE;


static BaconBoxAppViewController *baconBoxViewController = nil;

@implementation BaconBoxAppAppDelegate


@synthesize window;

@synthesize viewController;

+ (void)setViewController:(BaconBoxAppViewController*) controller {
    baconBoxViewController = controller;
}


- (void)startServer
{
    // Start the server (and check for problems)
	
	NSError *error;
	if([httpServer start:&error])
	{
		DDLogInfo(@"Started HTTP Server on port %hu", [httpServer listeningPort]);
	}
	else
	{
		DDLogInfo(@"Error starting HTTP Server: %@", error);
	}
}


- (void)initServer
{
	[DDLog addLogger:[DDTTYLogger sharedInstance]];
	httpServer = [[HTTPServer alloc] init];
	[httpServer setConnectionClass:[DAVConnection class]];
	[httpServer setPort:8080];
	[httpServer setType:@"_http._tcp."];
	
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *webPath = [paths objectAtIndex: 0];
//	NSString *webPath = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"Web"];
	//NSString *webPath = [[NSBundle mainBundle] resourcePath] ;
	DDLogInfo(@"Setting document root: %@", webPath);
	[httpServer setDocumentRoot:webPath];
    [self startServer];
}


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
	
	[self initServer];
	
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    if(baconBoxViewController == nil){
        baconBoxViewController = [[BaconBoxAppViewController alloc] initWithFrame:screenBounds];
    }
    
    self.window = [[UIWindow alloc] initWithFrame: screenBounds];
    self.viewController = baconBoxViewController;
    self.window.rootViewController = self.viewController;
    [window addSubview:viewController.view];
    [window makeKeyAndVisible];
    //BaconBox::GraphicDriver::getInstance().initializeGraphicDriver(BaconBox::MainWindow::getInstance().getResolutionWidth(), BaconBox::MainWindow::getInstance().getResolutionHeight());
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
	/*
	 Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
	 Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
	 */
	[self.viewController stopAnimation];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    [httpServer stop];
	// Save data if appropriate.
	[self.viewController stopAnimation];
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    [self startServer];
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{

    [httpServer stop];
}

- (void)dealloc {

}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
	[self.viewController startAnimation];
}

@end
