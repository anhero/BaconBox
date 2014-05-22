#import <QuartzCore/QuartzCore.h>

#import "BaconBoxAppViewController.h"
#import "EAGLView.h"

#include <BaconBox/Core/Engine.h>
#include "BaconBox/Platform.h"
@interface BaconBoxAppViewController ()
@property (nonatomic, retain) EAGLContext *context;
@property (nonatomic, assign) CADisplayLink *displayLink;
@end

@implementation BaconBoxAppViewController

@synthesize animating, context, displayLink, motionManager, accelData;


- (BOOL)shouldAutorotate{
	return false;
}
- (id)initWithFrame:(CGRect)frame
{
    self.view = [[EAGLView alloc] initWithFrame:frame];
	bool retina = [[UIScreen mainScreen] scale] == 2;
//	BaconBox::Platform::getInstance().isRetina = retina;
//	BaconBox::Platform::getInstance().isIphone = (frame.size.width == 320);
//	BaconBox::Platform::getInstance().isIOSWide = (frame.size.height == 568);
//	BaconBox::Platform::getInstance().isIpad = (frame.size.width == 768);
    if ([[UIScreen mainScreen] respondsToSelector:@selector(scale)] && retina){
        [self.view setContentScaleFactor:2.0f];
    }
//    self.view.clipsToBounds = YES;
    
    EAGLContext *aContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    
   
    if (!aContext)
        NSLog(@"Failed to create ES context");
    else if (![EAGLContext setCurrentContext:aContext])
        NSLog(@"Failed to set ES context current");
    
	self.context = aContext;
	
    [(EAGLView *)self.view setContext:context];
    [(EAGLView *)self.view setFramebuffer];
 
    animating = FALSE;
    animationFrameInterval = 1;
    self.displayLink = nil;
	
	if ([self respondsToSelector:@selector(setNeedsStatusBarAppearanceUpdate)]) {
        // iOS 7
        [self prefersStatusBarHidden];
        [self performSelector:@selector(setNeedsStatusBarAppearanceUpdate)];
    } else {
        // iOS 6
        [[UIApplication sharedApplication] setStatusBarHidden:YES withAnimation:UIStatusBarAnimationSlide];
    }
//	CMMotionManager *test;

	
	//init accelerometer and gyrometer
	self.motionManager = [[CMMotionManager alloc] init];
	self.motionManager.accelerometerUpdateInterval = .2;
	self.motionManager.gyroUpdateInterval = .2;
	
	[self.motionManager startAccelerometerUpdatesToQueue:[NSOperationQueue currentQueue]
											 withHandler:^(CMAccelerometerData  *accelerometerData, NSError *error) {
												 [self outputAccelertionData:accelerometerData.acceleration];
												 if(error){
													 
													 NSLog(@"%@", error);
												 }
											 }];
	
	
	[self.motionManager startGyroUpdatesToQueue:[NSOperationQueue currentQueue]
									withHandler:^(CMGyroData *gyroData, NSError *error) {
										[self outputRotationData:gyroData.rotationRate];
									}];
	
	self.accelData = new sigly::Signal1<CMAcceleration *>();
	
	
    return self;
}


-(sigly::Signal1<CMAcceleration *>*)getAccelSignal{
	return accelData;
}

-(void)outputAccelertionData:(CMAcceleration)acceleration
{
	accelData->shoot(&acceleration);
}
-(void)outputRotationData:(CMRotationRate)rotation
{
	
}


- (void)dealloc
{
	// Tear down context.
    if ([EAGLContext currentContext] == context)
        [EAGLContext setCurrentContext:nil];
    
    
}


- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}

- (void)viewWillAppear:(BOOL)animated
{
    [self startAnimation];
    
    [super viewWillAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [self stopAnimation];
    
    [super viewWillDisappear:animated];
}

- (void)viewDidUnload
{
	[super viewDidUnload];
	
    // Tear down context.
    if ([EAGLContext currentContext] == context)
        [EAGLContext setCurrentContext:nil];
	self.context = nil;	
}

- (NSInteger)animationFrameInterval
{
    return animationFrameInterval;
}

- (void)setAnimationFrameInterval:(NSInteger)frameInterval
{
    /*
	 Frame interval defines how many display frames must pass between each time the display link fires.
	 The display link will only fire 30 times a second when the frame internal is two on a display that refreshes 60 times a second. The default frame interval setting of one will fire 60 times a second when the display refreshes at 60 times a second. A frame interval setting of less than one results in undefined behavior.
	 */
    if (frameInterval >= 1) {
        animationFrameInterval = frameInterval;
        
        if (animating) {
            [self stopAnimation];
            [self startAnimation];
        }
    }
}

- (void)setFrameInterval: (double) frameInterval {
	animationFrameInterval = frameInterval;
	[self.displayLink setFrameInterval:animationFrameInterval];

}


- (void)startAnimation
{
    if (!animating) {
        CADisplayLink *aDisplayLink = [[UIScreen mainScreen] displayLinkWithTarget:self selector:@selector(drawFrame)];
		[aDisplayLink setFrameInterval:animationFrameInterval];
        [aDisplayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];

        self.displayLink = aDisplayLink;
        
        animating = TRUE;
    }
}

- (void)stopAnimation
{
    if (animating) {
        [self.displayLink invalidate];
        self.displayLink = nil;
        animating = FALSE;
    }
}

- (void)drawFrame
{
    [(EAGLView *)self.view setFramebuffer];
	BaconBox::Engine::pulse();
    [(EAGLView *)self.view presentFramebuffer];
}

@end
