//
//  TouchAbleLabel.m
//  testTags
//
//  Created by Alex on 6/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "TouchAbleLabel.h"
@implementation TouchAbleLabel

@synthesize delegate;

#define COLOR(R,G,B,A) [UIColor colorWithRed:R/255.0 green:G/255.0 blue:B/255.0 alpha:A]
- (id)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame])
    {
        [self setLineBreakMode:UILineBreakModeWordWrap|UILineBreakModeTailTruncation];
        [self setBackgroundColor:[UIColor clearColor]];
        [self setUserInteractionEnabled:YES];
        [self setNumberOfLines:0];
    }
    return self;
}


- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    [self setTextColor:[UIColor whiteColor]];
}


// 还原label颜色,获取手指离开屏幕时的坐标点, 在label范围内的话就可以触发自定义的操作
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    [self setTextColor:COLOR(59,136,195,1.0)];
    UITouch *touch = [touches anyObject];
    CGPoint points = [touch locationInView:self];
    
    
    float x_origin = self.frame.origin.x;
    float y_origin = self.frame.origin.y;
    
    float x_range = self.frame.origin.x+self.frame.size.width;
    float y_range = self.frame.origin.y+self.frame.size.height;
    
    
    //if (points.x >= x_origin && points.y >= y_origin && points.x <= x_range && points.y <= y_range)
    {
        [delegate myLabel:self touchesWtihTag:self.tag];
    }
}
- (void)dealloc {
    [super dealloc];
}

@end