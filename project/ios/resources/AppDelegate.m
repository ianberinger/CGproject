
#import "AppDelegate.h"
#import "MenuViewController.h"

@interface AppDelegate () {
 @private
  MenuViewController *menuViewController;
}

@end

@implementation AppDelegate

@synthesize window;

- (BOOL)application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  // create window
  self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
  self.window.backgroundColor = [UIColor blackColor];

  // create view controller
  menuViewController = [[MenuViewController alloc] init];

  [self.window setRootViewController:menuViewController];
  [self.window makeKeyAndVisible];

  return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
  // pass event to view controller holding the c++ application
  [menuViewController appWillResignActive];
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
  // pass event to view controller holding the c++ application
  [menuViewController appDidBecomeActive];
}

- (void)applicationWillTerminate:(UIApplication *)application {
  // pass event to view controller holding the c++ application
  [menuViewController appWillTerminate];
}

@end
