//
//  SAOption.h
//  SendAnywhereSDK
//
//  Created by estmob_imac27 on 2015. 6. 30..
//  Copyright (c) 2015년 estmob. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <paprika/paprika.h>
@interface SAOption : NSObject
@property (readonly)PaprikaOption option;
+ (instancetype)sharedInstance;
@end