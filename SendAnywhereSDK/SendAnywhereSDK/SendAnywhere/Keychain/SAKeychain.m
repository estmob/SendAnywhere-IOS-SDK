//
//  ESTMKeychain.m
//  PaprikaV2
//
//  Created by So Jeong lim on 2014. 8. 12..
//  Copyright (c) 2014년 estmob. All rights reserved.
//

#import "SAKeychain.h"
#import <Security/Security.h>

NSString *const kSAKeychainKeyDeviceID = @"SEND_ANYWHERE_KEY_DEVICE_ID";
NSString *const kSAKeychainKeyDevicePWD = @"SEND_ANYWHERE_KEY_DEVICE_PWD";
NSString *const kSAKeychainServiceName = @"SendAnyWhere";

@implementation SAKeychain

- (id) initWithService:(NSString *)service
{
    self =[super init];
    if(self)
    {
        __service = [service copy];
        
    }
    
    return  self;
}

- (NSMutableDictionary *) prepareDict:(NSString *) key
{
    
    NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
    [dict setObject:(__bridge id)kSecClassGenericPassword forKey:(__bridge id)kSecClass];
    
    NSData *encodedKey = [key dataUsingEncoding:NSUTF8StringEncoding];
    [dict setObject:encodedKey forKey:(__bridge id)kSecAttrGeneric];
    [dict setObject:encodedKey forKey:(__bridge id)kSecAttrAccount];
    [dict setObject:__service forKey:(__bridge id)kSecAttrService];
    [dict setObject:(__bridge id)kSecAttrAccessibleAlwaysThisDeviceOnly forKey:(__bridge id)kSecAttrAccessible];
    return  dict;
    
}

-(BOOL) insert:(NSString *)key : (NSData *)data
{
    NSMutableDictionary * dict =[self prepareDict:key];
    [dict setObject:data forKey:(__bridge id)kSecValueData];
    
    OSStatus status = SecItemAdd((__bridge CFDictionaryRef)dict, NULL);
    if(errSecSuccess != status) {

    }
    return (errSecSuccess == status);
}

-(NSString*) find:(NSString*)key
{
    NSMutableDictionary *dict = [self prepareDict:key];
    [dict setObject:(__bridge id)kSecMatchLimitOne forKey:(__bridge id)kSecMatchLimit];
    [dict setObject:(id)kCFBooleanTrue forKey:(__bridge id)kSecReturnData];
    CFTypeRef result = NULL;
    OSStatus status = SecItemCopyMatching((__bridge CFDictionaryRef)dict,&result);
    
    if( status != errSecSuccess) {

        return nil;
    }
    
    NSString *resultStr = [[NSString alloc] initWithData:(__bridge NSData *)result encoding:NSUTF8StringEncoding];
    return resultStr;
}

-(BOOL) update:(NSString*)key :(NSData*) data
{
    NSMutableDictionary * dictKey =[self prepareDict:key];
    
    NSMutableDictionary * dictUpdate =[[NSMutableDictionary alloc] init];
    [dictUpdate setObject:data forKey:(__bridge id)kSecValueData];
    
    OSStatus status = SecItemUpdate((__bridge CFDictionaryRef)dictKey, (__bridge CFDictionaryRef)dictUpdate);
    if(errSecSuccess != status) {

    }
    return (errSecSuccess == status);
}


- (BOOL)insertOrUpdate:(NSString*)key data:(NSData*)data {
    if([self find:key]){
        return [self update:key :data];
    }
    return [self insert:key :data];
}

-(BOOL) remove: (NSString*)key
{
    NSMutableDictionary *dict = [self prepareDict:key];
    OSStatus status = SecItemDelete((__bridge CFDictionaryRef)dict);
    if( status != errSecSuccess) {

        return NO;
    }
    return  YES;
}
@end
