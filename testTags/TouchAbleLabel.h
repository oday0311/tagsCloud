//
//  TouchAbleLabel.h
//  testTags
//
//  Created by Alex on 6/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BBCyclingLabel.h"
@class  TouchAbleLabel;

@protocol MyLabelDelegate <NSObject>
@required
- (void)myLabel:(TouchAbleLabel *)myLabel touchesWtihTag:(NSInteger)tag;
@end

@interface TouchAbleLabel : BBCyclingLabel 
{
    id <MyLabelDelegate> delegate;
}


@property (nonatomic, assign) id <MyLabelDelegate> delegate;
- (id)initWithFrame:(CGRect)frame;




@end