//
// Copyright 2012 BiasedBit
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

//
//  Created by Bruno de Carvalho -- @biasedbit / http://biasedbit.com
//  Copyright (c) 2012 BiasedBit. All rights reserved.
//

#pragma mark - Enums

typedef enum
{
	// User must provide pre-transition and transition blocks
	BBCyclingLabelTransitionEffectCustom = 0,

    BBCyclingLabelTransitionEffectFadeIn    = 1 << 0,
	BBCyclingLabelTransitionEffectFadeOut   = 1 << 1,
	BBCyclingLabelTransitionEffectCrossFade = BBCyclingLabelTransitionEffectFadeIn |
                                              BBCyclingLabelTransitionEffectFadeOut,

	BBCyclingLabelTransitionEffectZoomIn  = 1 << 2,
	BBCyclingLabelTransitionEffectZoomOut = 1 << 3,

    BBCyclingLabelTransitionEffectScaleFadeOut = BBCyclingLabelTransitionEffectFadeIn |
                                                 BBCyclingLabelTransitionEffectFadeOut |
                                                 BBCyclingLabelTransitionEffectZoomOut,
    BBCyclingLabelTransitionEffectScaleFadeIn  = BBCyclingLabelTransitionEffectFadeIn |
                                                 BBCyclingLabelTransitionEffectFadeOut |
                                                 BBCyclingLabelTransitionEffectZoomIn,

    // These two move the entering label from above/below to center and exiting label up/down without cross-fade
    // It's a good idea to set the clipsToBounds property of the BBCyclingLabel to true and use this in a confined space
    BBCyclingLabelTransitionEffectScrollUp   = 1 << 4,
    BBCyclingLabelTransitionEffectScrollDown = 1 << 5,

    BBCyclingLabelTransitionEffectDefault = BBCyclingLabelTransitionEffectCrossFade
} BBCyclingLabelTransitionEffect;



#pragma mark - Custom types

typedef void(^BBCyclingLabelPreTransitionBlock)(UILabel* labelToEnter);
typedef void(^BBCyclingLabelTransitionBlock)(UILabel* labelToExit, UILabel* labelToEnter);



#pragma mark -

@interface BBCyclingLabel : UIView


#pragma mark Public properties

@property(assign, nonatomic) BBCyclingLabelTransitionEffect   transitionEffect;
@property(copy,   nonatomic) BBCyclingLabelPreTransitionBlock preTransitionBlock;
@property(copy,   nonatomic) BBCyclingLabelTransitionBlock    transitionBlock;
@property(assign, nonatomic) NSTimeInterval                   transitionDuration;
// Same properties as UILabel, these will be propagated to the underlying labels
@property(copy,   nonatomic) NSString*            text;
@property(strong, nonatomic) UIFont*              font;
@property(strong, nonatomic) UIColor*             textColor;
@property(strong, nonatomic) UIColor*             shadowColor;
@property(assign, nonatomic) CGSize               shadowOffset;
@property(assign, nonatomic) UITextAlignment      textAlignment;
@property(assign, nonatomic) UILineBreakMode      lineBreakMode;
@property(assign, nonatomic) NSInteger            numberOfLines;
@property(assign, nonatomic) BOOL                 adjustsFontSizeToFitWidth;
@property(assign, nonatomic) CGFloat              minimumFontSize;
@property(assign, nonatomic) UIBaselineAdjustment baselineAdjustment;


#pragma mark Creation

- (id)initWithFrame:(CGRect)frame andTransitionType:(BBCyclingLabelTransitionEffect)transitionEffect;


#pragma mark Public methods

/*! Sets the text for the next label and performs a transition between current and next label (if animated is YES) */
- (void)setText:(NSString*)text animated:(BOOL)animated;

@end


/*
 
 #pragma mark Property synthesizers
 
 @synthesize defaultLabel  = _defaultLabel;
 @synthesize scaleOutLabel = _scaleOutLabel;
 @synthesize scrollUpLabel = _scrollUpLabel;
 @synthesize customLabel   = _customLabel;
 @synthesize textField     = _textField;
 
 
 #pragma mark UIViewController
 
 - (void)viewDidLoad
 {
 [super viewDidLoad];
 
 _defaultLabel.font = [UIFont systemFontOfSize:15];
 _scaleOutLabel.font = [UIFont systemFontOfSize:15];
 _scrollUpLabel.font = [UIFont systemFontOfSize:15];
 _customLabel.font = [UIFont systemFontOfSize:15];
 
 _defaultLabel.textColor = [UIColor colorWithWhite:0.2 alpha:1];
 _scaleOutLabel.textColor = [UIColor colorWithWhite:0.2 alpha:1];
 _scrollUpLabel.textColor = [UIColor colorWithWhite:0.2 alpha:1];
 _customLabel.textColor = [UIColor colorWithWhite:0.2 alpha:1];
 
 _defaultLabel.shadowColor = [UIColor colorWithWhite:1 alpha:0.75];
 _scaleOutLabel.shadowColor = [UIColor colorWithWhite:1 alpha:0.75];
 _scrollUpLabel.shadowColor = [UIColor colorWithWhite:1 alpha:0.75];
 _customLabel.shadowColor = [UIColor colorWithWhite:1 alpha:0.75];
 
 _defaultLabel.shadowOffset = CGSizeMake(0, 1);
 _scaleOutLabel.shadowOffset = CGSizeMake(0, 1);
 _scrollUpLabel.shadowOffset = CGSizeMake(0, 1);
 _customLabel.shadowOffset = CGSizeMake(0, 1);
 
 _defaultLabel.numberOfLines = 1;
 _scaleOutLabel.numberOfLines = 1;
 _scrollUpLabel.numberOfLines = 1;
 _customLabel.numberOfLines = 1;
 
 _defaultLabel.textAlignment = UITextAlignmentCenter;
 _scaleOutLabel.textAlignment = UITextAlignmentCenter;
 _scrollUpLabel.textAlignment = UITextAlignmentCenter;
 _customLabel.textAlignment = UITextAlignmentCenter;
 
 // Slow so you can get a good look...
 _defaultLabel.transitionDuration = 0.75;
 _scaleOutLabel.transitionDuration = 10.75;
 _scrollUpLabel.transitionDuration = 0.75;
 _customLabel.transitionDuration = 0.75;
 
 [_defaultLabel setText:@"default label text" animated:NO];
 [_scaleOutLabel setText:@"scale out label text" animated:NO];
 [_scrollUpLabel setText:@"scroll up label text" animated:NO];
 [_customLabel setText:@"scroll up label text" animated:NO];
 
 _scaleOutLabel.transitionEffect = BBCyclingLabelTransitionEffectScaleFadeOut;
 
 _scrollUpLabel.transitionEffect = BBCyclingLabelTransitionEffectScrollUp;
 // Since scrolling involves moving the frame of the underlying labels, we need to enable bound clipping
 _scrollUpLabel.clipsToBounds = YES;
 
 // Create a custom transition animation that rotates 180º, reduces size to 0.2 and fades out the exiting label
 _customLabel.transitionEffect = BBCyclingLabelTransitionEffectCustom;
 _customLabel.preTransitionBlock = ^(UILabel* labelToEnter) {
 labelToEnter.transform = CGAffineTransformIdentity;
 labelToEnter.alpha = 0;
 };
 _customLabel.transitionBlock = ^(UILabel* labelToExit, UILabel* labelToEnter) {
 labelToExit.alpha = 0;
 CGAffineTransform transform = CGAffineTransformMakeRotation(M_PI);
 labelToExit.transform = CGAffineTransformScale(transform, 0.2, 0.2);
 
 labelToEnter.alpha = 1;
 };
 _customLabel.clipsToBounds = YES;
 
 _textField.delegate = self;
 
 self.view.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"Background"]];
 }
 
 - (void)viewDidAppear:(BOOL)animated
 {
 [super viewDidAppear:animated];
 }
 
 - (void)viewDidUnload
 {
 [super viewDidUnload];
 }
 
 - (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
 {
 return (interfaceOrientation == UIInterfaceOrientationPortrait);
 }
 
 
 #pragma mark UITextFieldDelegate
 
 - (BOOL)textFieldShouldReturn:(UITextField*)textField
 {
 NSString* text = textField.text;
 
 [_defaultLabel setText:text animated:YES];
 [_scaleOutLabel setText:text animated:YES];
 [_scrollUpLabel setText:text animated:YES];
 [_customLabel setText:text animated:YES];
 
 _textField.text = @"";
 
 return YES;
 }
 */
