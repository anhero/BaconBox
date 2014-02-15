#import "BaconBoxAppAppDelegate.h"

#import "EAGLView.h"

#import "BaconBoxAppViewController.h"
#include <BaconBox/Display/Driver/GraphicDriver.h>
#include "MainWindow.h"


#import "DDLog.h"
#import "DDTTYLogger.h"
#import "HTTPServer.h"
#import "DAVConnection.h"
#import <ifaddrs.h>
#import <arpa/inet.h>
#include "BaconBox/Display/Window/MainWindow.h"
static const int ddLogLevel = LOG_LEVEL_VERBOSE;


static BaconBoxAppViewController *baconBoxViewController = nil;

@implementation BaconBoxAppAppDelegate


@synthesize window;

@synthesize viewController;

+ (BaconBoxAppViewController*)getViewController{
	return baconBoxViewController;
}

+ (void)setViewController:(BaconBoxAppViewController*) controller {
    baconBoxViewController = controller;
}


- (void)startServer
{
#ifdef BB_WEBDAV_SERVER

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
#endif

}


- (void)initServer
{
#ifdef BB_WEBDAV_SERVER
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
	NSString * ip = [self getIPAddress];
	std::cout << "HTTP SERVER IP ADDRESS:  " << [ip cStringUsingEncoding:NSUTF8StringEncoding] << std::endl;
#endif
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


// Get IP Address
- (NSString *)getIPAddress {
    NSString *address = @"error";
    struct ifaddrs *interfaces = NULL;
    struct ifaddrs *temp_addr = NULL;
    int success = 0;
    // retrieve the current interfaces - returns 0 on success
    success = getifaddrs(&interfaces);
    if (success == 0) {
        // Loop through linked list of interfaces
        temp_addr = interfaces;
        while(temp_addr != NULL) {
            if(temp_addr->ifa_addr->sa_family == AF_INET) {
                // Check if interface is en0 which is the wifi connection on the iPhone
                if([[NSString stringWithUTF8String:temp_addr->ifa_name] isEqualToString:@"en0"]) {
                    // Get NSString from C String
                    address = [NSString stringWithUTF8String:inet_ntoa(((struct sockaddr_in *)temp_addr->ifa_addr)->sin_addr)];
                }
            }
            temp_addr = temp_addr->ifa_next;
        }
    }
    // Free memory
    freeifaddrs(interfaces);
    return address;
	
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

- (void)applicationDidBecomeActive:(UIApplication *)application {
	BaconBox::MainWindow::getInstance().gotFocus.shoot();
	[self.viewController startAnimation];
}

@end
