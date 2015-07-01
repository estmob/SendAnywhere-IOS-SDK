//
//  NSString+SAAddtions.h
//  SendAnywhereSDK
//
//  Created by estmob_imac27 on 2015. 6. 30..
//  Copyright (c) 2015년 estmob. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (SAAddtions)

- (wchar_t *)wchart;
+ (NSString*)stringWithWchart:(const wchar_t*)wchart;
@end

@implementation NSString (SAAddtions)

- (wchar_t *)wchart{
    const char* temp = [self cStringUsingEncoding:NSUTF8StringEncoding];
    int buflen = strlen(temp)+1; //including NULL terminating char
    wchar_t* buffer = malloc(buflen * sizeof(wchar_t));
    mbstowcs(buffer, temp, buflen);
    return buffer;
//    return (wchar_t*)[self cStringUsingEncoding:CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingUTF32LE)];
}

- (void)getWchart:(wchar_t**)wchart{
    wchar_t *wc = (wchar_t*)[self cStringUsingEncoding:CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingUTF32LE)];
    NSInteger length = self.length+1;
    wchar_t result[length];
    for (NSInteger i = 0; i < self.length; i++) {
        result[i] = wc[i];
    }
    result[length-1] = '\0';
    const wchar_t *copyItem = result;
    wcscpy(*wchart, copyItem);
}

+ (NSString*)stringWithWchart:(const wchar_t*)wchart {
    if (wchart == NULL) {
        return @"";
    }
    int bufflen = 8*wcslen(wchart)+1;
    char* temp = malloc(bufflen);
    wcstombs(temp, wchart, bufflen);
    NSString* retVal = [self stringWithUTF8String:temp];
    free(temp);
    return retVal;
}

@end