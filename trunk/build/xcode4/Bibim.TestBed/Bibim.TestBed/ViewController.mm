#import "ViewController.h"
#include <Bibim/GameFramework.h>
#include <Bibim/GameWindow.h>
#include <Bibim/Point2.h>
#include <Bibim/Environment.h>
using namespace Bibim;

@interface ViewController () {
    GameFramework* game;
}
@property (strong, nonatomic) EAGLContext *context;
@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    
    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyBundleURL(mainBundle);
    CFStringRef str = CFURLCopyFileSystemPath(resourcesURL, kCFURLPOSIXPathStyle);
    char path[PATH_MAX];
    CFStringGetCString(str, path, PATH_MAX, kCFStringEncodingASCII);
    CFRelease(str);
    
    int len = strlen(path);
    path[len] = '/';
    path[len + 1] = '\0';
    
    Bibim::Environment::Setup("ko-KR", path, "");
    
    game = GameFramework::Create();
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormatNone;
    
    [self setupGL];
}

- (void)dealloc
{
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    
    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        
        [self tearDownGL];
        
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    
    GLKView* glkView = (GLKView*)self.view;
    CGRect glkViewFrame = [glkView frame];
    game->GetWindow()->SetSize(Point2(glkViewFrame.size.width, glkViewFrame.size.height));
    game->init();
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
    game->update();
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    game->draw();
}


@end
