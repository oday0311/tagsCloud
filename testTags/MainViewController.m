//
//  MainViewController.m
//  testTags
//
//  Created by Alex on 6/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "MainViewController.h"
#import "TouchAbleLabel.h"

@interface MainViewController ()

@end

@implementation MainViewController
@synthesize tableref = _tableref;

@synthesize flipsidePopoverController = _flipsidePopoverController;

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    ////////////////////////huangzf========================= 
    self.tableref.backgroundColor = [UIColor clearColor];
    //   MytableView.backgroundColor =
    //  [UIColor colorWithPatternImage:[UIImage imageNamed:@"dotline.png"]];
    self.tableref.superview.backgroundColor = [UIColor colorWithPatternImage: [UIImage imageNamed:@"background.jpg"]];
    [self.tableref setSeparatorStyle:UITableViewCellSeparatorStyleNone];
    self.tableref.opaque = NO;
    //////////////////////////////////////

    TagLabels = [[NSMutableArray alloc] init];
    timer=[NSTimer scheduledTimerWithTimeInterval:2 
                                           target:self 
                                         selector:@selector(resetTagLabel) 
                                         userInfo:nil 
                                          repeats:YES]; 
    LabelContent = [[NSMutableArray alloc] init];
    for (int i = 0; i<50; i++) {
        NSString* content=[@"" stringByAppendingFormat:@"hello%i",i];
        [LabelContent addObject:content];
    }
}

static int labelContentIndex = 0;
-(void)resetTagLabel
{
    for (int i = 0; i<5; i++)
    {
        int LabelIndex = rand()%[TagLabels count];
        TouchAbleLabel* tempLabel = [TagLabels objectAtIndex:LabelIndex];
        NSString* labelcontent = [LabelContent objectAtIndex:labelContentIndex++ % [LabelContent count]];
        [tempLabel setText:labelcontent animated:YES];

    }
}


- (void)viewDidUnload
{
    [LabelContent release];
    [timer release];
    [TagLabels release];
    [self setTableref:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}

#pragma mark - Flipside View Controller

- (void)flipsideViewControllerDidFinish:(FlipsideViewController *)controller
{
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        [self dismissModalViewControllerAnimated:YES];
    } else {
        [self.flipsidePopoverController dismissPopoverAnimated:YES];
    }
}

- (void)dealloc
{
    [_flipsidePopoverController release];
    [_tableref release];
    [super dealloc];
}



- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    int count = 15;
    
    return count;
}

-(NSString*)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    if (section==0) {
        return @"梅州";
    }
    
    else
        return @"";
}
static int global_tags_for_touchAbleLabel= 1000;
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath 
{
    
    UITableViewCell *cell = nil;
    
    static NSString *kDisplayCell_ID = @"DisplayCellID";
    cell = [tableView dequeueReusableCellWithIdentifier:kDisplayCell_ID];
    if (cell == nil)
    {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kDisplayCell_ID] autorelease];
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
        
        for (int i = 0; i<=3;i++) {
            float x_offset = rand()%30 -15;
            float y_offset = rand()%20- 10 ;
            
            TouchAbleLabel* tempLabel = [[[TouchAbleLabel alloc] initWithFrame:CGRectMake(80*i+x_offset,5+y_offset , 80, 40)]  autorelease];
            tempLabel.backgroundColor = [UIColor clearColor];
            tempLabel.textColor = [UIColor yellowColor];
            tempLabel.text = @"test";
            float alpha_random = (rand()%10) *0.1;
            tempLabel.alpha = alpha_random;
            
            float font_size = (rand()%10)+8;
            tempLabel.font = [UIFont systemFontOfSize:font_size];
            
            tempLabel.tag = global_tags_for_touchAbleLabel++;
            [tempLabel setDelegate:self];
            
            tempLabel.transitionEffect = BBCyclingLabelTransitionEffectScaleFadeOut;
            tempLabel.transitionDuration = 3;
            //[tempLabel setText:@"newText" animated:YES];
            [TagLabels addObject:tempLabel];
            [cell addSubview:tempLabel];
        }

        
    }
      
  
    
    return cell;
}


//- (void)myLabel:(TouchAbleLabel *)myLabel touchesWtihTag:(NSInteger)tag;
- (void)myLabel:(TouchAbleLabel *)myLabel touchesWtihTag:(NSInteger)tag {
    //[[UIApplication sharedApplication] openURL:[NSURL URLWithString:webSite.text]];
    NSLog(@"press decected");
    NSLog(@"press tags is %i", tag);
}




#pragma mark UITableViewDelegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    
    
       
}



- (IBAction)showInfo:(id)sender
{
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        FlipsideViewController *controller = [[[FlipsideViewController alloc] initWithNibName:@"FlipsideViewController" bundle:nil] autorelease];
        controller.delegate = self;
        controller.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
        [self presentModalViewController:controller animated:YES];
    } else {
        if (!self.flipsidePopoverController) {
            FlipsideViewController *controller = [[[FlipsideViewController alloc] initWithNibName:@"FlipsideViewController" bundle:nil] autorelease];
            controller.delegate = self;
            
            self.flipsidePopoverController = [[[UIPopoverController alloc] initWithContentViewController:controller] autorelease];
        }
        if ([self.flipsidePopoverController isPopoverVisible]) {
            [self.flipsidePopoverController dismissPopoverAnimated:YES];
        } else {
            [self.flipsidePopoverController presentPopoverFromBarButtonItem:sender permittedArrowDirections:UIPopoverArrowDirectionAny animated:YES];
        }
    }
}

@end
