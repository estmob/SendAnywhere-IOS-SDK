//
//  ViewController.h
//  SendAnywhereSDKTest
//
//  Created by estmob_imac27 on 2015. 6. 29..
//  Copyright (c) 2015년 estmob. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <SendAnywhereSDK/SendAnywhereSDK.h>

@interface ViewController : UIViewController <SATaskDelegate>

@property (nonatomic, weak) IBOutlet UITextField *textField;
@property (nonatomic, weak) IBOutlet UIProgressView *sendProgressView;
@property (nonatomic, weak) IBOutlet UIProgressView *receiveProgressView;
@property (nonatomic, weak) IBOutlet UILabel *sendKeyLabel;
@property (nonatomic, weak) IBOutlet UILabel *sendFileNameLabel;
@property (nonatomic, weak) IBOutlet UILabel *receiveFileNameLabel;

@end

