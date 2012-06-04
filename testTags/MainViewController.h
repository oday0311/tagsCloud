//
//  MainViewController.h
//  testTags
//
//  Created by Alex on 6/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "FlipsideViewController.h"
#import "TouchAbleLabel.h"

@interface MainViewController : UIViewController <MyLabelDelegate,FlipsideViewControllerDelegate,UITableViewDataSource,UITableViewDelegate>
{
    NSTimer *timer;
    NSMutableArray* TagLabels;
    
    NSMutableArray* LabelContent;
}


@property (strong, nonatomic) UIPopoverController *flipsidePopoverController;

- (IBAction)showInfo:(id)sender;
@property (retain, nonatomic) IBOutlet UITableView *tableref;

@end
