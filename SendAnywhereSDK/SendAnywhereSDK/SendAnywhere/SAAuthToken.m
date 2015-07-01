//
//  SAAuthToken.m
//  SendAnywhereSDK
//
//  Created by estmob_imac27 on 2015. 6. 30..
//  Copyright (c) 2015년 estmob. All rights reserved.
//

#import "SAAuthToken.h"
#import "SAKeychain.h"

@interface SAAuthToken ()
@property (nonatomic,strong) SAKeychain *keyChain;
@end

@implementation SAAuthToken
@synthesize authToken = __authToken;

+ (instancetype)sharedInstance {
    static SAAuthToken *sharedInstance;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[SAAuthToken alloc] init];
    });
    return sharedInstance;
}


- (instancetype)init {
    self = [super init];
    if (self) {
        SAKeychain *keyChain = [[SAKeychain alloc] initWithService:kSAKeychainServiceName];
        self.keyChain = keyChain;
        NSString *deviceID = [self.keyChain find:kSAKeychainKeyDeviceID];
        NSString *devicePWD = [self.keyChain find:kSAKeychainKeyDevicePWD];
        if (deviceID && devicePWD) {
            __authToken = paprika_auth_create_with_deviceid([deviceID UTF8String], [devicePWD UTF8String]);
        }else {
            __authToken = paprika_auth_create();
        }
    }
    return self;
}

- (void)update {
    const char * deviceID = paprika_auth_get_device_id(__authToken);
    const char * devicePWD = paprika_auth_get_device_password(__authToken);
    [self.keyChain insertOrUpdate:kSAKeychainKeyDeviceID
                             data:[NSData dataWithBytes:deviceID length:strlen(deviceID)]];
    [self.keyChain insertOrUpdate:kSAKeychainKeyDevicePWD
                             data:[NSData dataWithBytes:devicePWD length:strlen(devicePWD)]];
}

- (void)dealloc {
    paprika_auth_close(self.authToken);
}

@end