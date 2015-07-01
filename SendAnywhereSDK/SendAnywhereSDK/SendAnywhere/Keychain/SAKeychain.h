//
//  ESTMKeychain.h
//  PaprikaV2
//
//  Created by So Jeong lim on 2014. 8. 12..
//  Copyright (c) 2014년 estmob. All rights reserved.
//

#import <Foundation/Foundation.h>

FOUNDATION_EXPORT NSString *const kSAKeychainKeyDeviceID;
FOUNDATION_EXPORT NSString *const kSAKeychainKeyDevicePWD;
FOUNDATION_EXPORT NSString *const kSAKeychainServiceName;


@interface SAKeychain : NSObject
{
    NSString * __service;
}
-(id) initWithService:(NSString *) service_ ;

-(BOOL) insert:(NSString *)key : (NSData *)data;
-(BOOL) update:(NSString*)key :(NSData*) data;
-(BOOL) remove: (NSString*)key;
-(NSString*) find:(NSString*)key;

- (BOOL)insertOrUpdate:(NSString*)key data:(NSData*)data;
@end
