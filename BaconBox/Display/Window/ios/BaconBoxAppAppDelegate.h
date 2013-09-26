#import <UIKit/UIKit.h>

@class BaconBoxAppViewController;
@class HTTPServer;
@interface BaconBoxAppAppDelegate : NSObject <UIApplicationDelegate> {
	HTTPServer *httpServer;

@private
	


}

@property (nonatomic, retain) IBOutlet UIWindow *window;

@property (nonatomic, retain) IBOutlet BaconBoxAppViewController *viewController;

+ (BaconBoxAppViewController*)getViewController;

+ (void)setViewController:(BaconBoxAppViewController*) controller;

@end
