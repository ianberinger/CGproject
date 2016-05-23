#import "Game.hpp"
#import "MenuViewController.h"

Game g;
UIView *v;

@interface MenuViewController () {
}
@property(weak, nonatomic) IBOutlet UISwitch *Debug;
@property(weak, nonatomic) IBOutlet UISwitch *Compete;

@end

@implementation MenuViewController

- (void)viewDidLoad {
  [super viewDidLoad];
  // initialize user application
  g.runCompleteCallback(removeSubview);
  g.init();
  v = g.getProjectRenderer().getView()->getUIView();
}

- (void)didReceiveMemoryWarning {
  [super didReceiveMemoryWarning];
  // Dispose of any resources that can be recreated.
}
- (BOOL)shouldAutorotate {
  // app doesn't adjust view correctly if this function doesn't return "yes"
  return YES;
}

- (void)didRotateFromInterfaceOrientation:
    (UIInterfaceOrientation)fromInterfaceOrientation {
  g.deviceRotated();
}

- (void)appWillResignActive {
  // pass event to c++ application
  g.appWillResignActive();
}

- (void)appDidBecomeActive {
  // pass event to c++ application
  g.appDidBecomeActive();
}

- (void)appWillTerminate {
  // pass event to c++ application
  g.appWillTerminate();
}

- (IBAction)startGame:(UIButton *)sender {
  g.DEBUG = [_Debug isOn];
  g.COMPETE = [_Compete isOn];
  g.startRun();
  g.appDidBecomeActive();
  [self.view addSubview:v];
}

void removeSubview() {
  printf("We are back!!!\n");
  [v removeFromSuperview];
}
/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little
preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
