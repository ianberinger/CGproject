
#import "ViewController.h"
#include "Game.hpp"


@interface ViewController () {
@private
    Game g;
}

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    // initialize user application
    g.init();
    
    // There are two ways to display the view of the renderer in your project:
//    [self.view addSubview:p.getProjectRenderer().getView()->getUIView()];    // method 1
    g.getProjectRenderer().getView()->attachToUIView(self.view);   // method 2
}


-(BOOL) shouldAutorotate
{
    // app doesn't adjust view correctly if this function doesn't return "yes"
    return YES;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation
{
    g.deviceRotated();
}

- (void)appWillResignActive
{
    // pass event to c++ application
    g.appWillResignActive();
}

- (void)appDidBecomeActive
{
    // pass event to c++ application
    g.appDidBecomeActive();
}

- (void)appWillTerminate
{
    // pass event to c++ application
    g.appWillTerminate();
}

@end
