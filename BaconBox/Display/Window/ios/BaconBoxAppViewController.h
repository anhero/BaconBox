#import <UIKit/UIKit.h>

#import <OpenGLES/EAGL.h>

#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#include <sigly.h>
#import <CoreMotion/CoreMotion.h>

@interface BaconBoxAppViewController : UIViewController {
@private
    EAGLContext *context;
    GLuint program;
    BOOL animating;
    NSInteger animationFrameInterval;
    __unsafe_unretained CADisplayLink *displayLink;
	CMMotionManager *motionManager;
	sigly::Signal1<CMAcceleration *> *accelData;
}

@property (readonly, nonatomic, getter=isAnimating) BOOL animating;
@property (nonatomic) NSInteger animationFrameInterval;

@property (strong, nonatomic) CMMotionManager *motionManager;
@property sigly::Signal1<CMAcceleration *> *accelData;


- (BOOL)shouldAutorotate;
- (void)startAnimation;
- (void)stopAnimation;
- (id)initWithFrame:(CGRect)frame;
- (void)setFrameInterval: (double) frameInterval;

@end
