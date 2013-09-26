#import <UIKit/UIKit.h>

#import <OpenGLES/EAGL.h>

#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

@interface BaconBoxAppViewController : UIViewController {
@private
    EAGLContext *context;
    GLuint program;
    BOOL animating;
    NSInteger animationFrameInterval;
    __unsafe_unretained CADisplayLink *displayLink;
}

@property (readonly, nonatomic, getter=isAnimating) BOOL animating;
@property (nonatomic) NSInteger animationFrameInterval;

- (void)startAnimation;
- (void)stopAnimation;
- (id)initWithFrame:(CGRect)frame;
- (void)setFrameInterval: (double) frameInterval;

@end
