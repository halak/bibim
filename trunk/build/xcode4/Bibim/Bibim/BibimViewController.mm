#import "BibimViewController.h"
#include <Bibim/GameFramework.h>
#include <Bibim/GameWindow.h>
#include <Bibim/IME.h>
#include <Bibim/Environment.h>
#include <Bibim/Point2.h>
using namespace Bibim;

@interface BibimViewController () {
    GameFramework* game;
}
@property (strong, nonatomic) EAGLContext *context;
@end

@implementation BibimViewController

- (Bibim::Point2)screenSizeInPixels
{
    const UIScreen* screen = [UIScreen mainScreen];
    const CGRect screenBounds = [screen bounds];
    const float screenScale = [screen scale];
    
    return Bibim::Point2((int)(screenBounds.size.width * screenScale),
                         (int)(screenBounds.size.height * screenScale));
}

- (Bibim::Point2)touchPoint:(UITouch*)touch
{
    CGPoint point = [touch locationInView:self.view];
    const float scale = [[UIScreen mainScreen] scale];
    return Bibim::Point2((int)(point.x * scale),
                         (int)(point.y * scale));
}

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
    
    [EAGLContext setCurrentContext:self.context];
    
    game->GetWindow()->SetSize([self screenSizeInPixels]);
    game->init();
}

- (void)dealloc
{
    [EAGLContext setCurrentContext:self.context];
    
    // finalize
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    
    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        
        [EAGLContext setCurrentContext:self.context];
        
        // finalize
        
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }
}



#pragma mark - update & draw

- (void)update
{
    game->update();
    
    static int counter = 0;
    if (counter++ % 30 == 0) {
        IME* ime = game->GetIME();
        if (ime && ime->HasMobileRequest()) {
            IME::Request request = ime->PopMobileRequest();
            NSString* title = [NSString stringWithUTF8String:request.GetTitle().CStr()];
            NSString* description = [NSString stringWithUTF8String:request.GetDescription().CStr()];
            NSString* text = [NSString stringWithUTF8String:request.GetText().CStr()];
            
            UIAlertView* alert = [[UIAlertView alloc] initWithTitle:title
                                                            message:description
                                                           delegate:self
                                                  cancelButtonTitle:@"Ok"
                                                  otherButtonTitles:@"Cancel", nil];
            [alert setTag:request.GetID()];
            
            if (request.GetFormat() == IME::Password) {
                [alert setAlertViewStyle:UIAlertViewStyleSecureTextInput];
            } else {
                [alert setAlertViewStyle:UIAlertViewStylePlainTextInput];
            }
            
            [alert show];
            
            UITextField* textField = [alert textFieldAtIndex:0];
            [textField setText:text];
            UIKeyboardType keyboardType = UIKeyboardTypeDefault;
            switch (request.GetFormat()) {
                case IME::Number:
                    keyboardType = UIKeyboardTypeNumberPad;
                    break;
                case IME::Email:
                    keyboardType = UIKeyboardTypeEmailAddress;
                    break;
            }
            
            [textField setKeyboardType:keyboardType];
        }
    }
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    game->draw();
}


#pragma mark - Input

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    Point2 xy = [self touchPoint:[touches anyObject]];
    game->GetWindow()->RaiseMouseLeftButtonDownEvent(xy.X, xy.Y);
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    Point2 xy = [self touchPoint:[touches anyObject]];
    game->GetWindow()->RaiseMouseLeftButtonUpEvent(xy.X, xy.Y);
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    Point2 xy = [self touchPoint:[touches anyObject]];
    game->GetWindow()->RaiseMouseMoveEvent(xy.X, xy.Y);
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    Point2 xy = [self touchPoint:[touches anyObject]];
    game->GetWindow()->RaiseMouseLeftButtonUpEvent(xy.X, xy.Y);
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation
{
    Point2 size = [self screenSizeInPixels];
    int w = 0;
    int h = 0;
    if (UIDeviceOrientationIsPortrait([[UIDevice currentDevice] orientation]))
    {
        w = size.X;
        h = size.Y;
    }
    else
    {
        w = size.Y;
        h = size.X;
    }
    
    game->GetWindow()->SetSize(Point2(w, h));
}

#pragma mark - UIAlertViewDelegate
- (void)alertViewCancel:(UIAlertView *)alertView
{
    if (IME* ime = game->GetIME()) {
        ime->CancelMobileEdit(alertView.tag);
    }
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (IME* ime = game->GetIME()) {
        if (buttonIndex == alertView.cancelButtonIndex) {
            UITextField* textField = [alertView textFieldAtIndex:0];
            ime->SubmitMobileEdit(alertView.tag, [textField.text UTF8String]);
        } else {
            ime->CancelMobileEdit(alertView.tag);
        }
    }
}

@end
