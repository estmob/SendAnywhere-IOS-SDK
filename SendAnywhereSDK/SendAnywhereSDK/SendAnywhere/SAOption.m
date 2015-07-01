//
//  SAOption.m
//  SendAnywhereSDK
//
//  Created by estmob_imac27 on 2015. 6. 30..
//  Copyright (c) 2015년 estmob. All rights reserved.
//

#import "SAOption.h"

static const char *kSAServerURL = "https://api.send-anywhere.com/api/v1/";

@implementation SAOption
@synthesize option = __option;

+ (instancetype)sharedInstance {
    static SAOption *sharedInstance;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[SAOption alloc] init];
    });
    return sharedInstance;
}


- (instancetype)init {
    self = [super init];
    if (self) {
        __option = paprika_option_create();
        paprika_option_set_value(self.option, PAPRIKA_OPTION_API_SERVER, kSAServerURL);
    }
    return self;
    
}

- (void)dealloc {
    paprika_option_close(self.option);
}

@end
