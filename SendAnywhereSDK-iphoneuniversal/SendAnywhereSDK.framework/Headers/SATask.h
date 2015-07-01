//
//  SATask.h
//  SendAnywhereSDK
//
//  Created by estmob_imac27 on 2015. 6. 29..
//  Copyright (c) 2015년 estmob. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SendAnywhere.h"

@protocol SATaskDelegate;
@interface SATask : NSObject

@property (nonatomic, weak) id<SATaskDelegate> delegate;
@property (nonatomic, readonly) NSString *key;
@property (nonatomic, readonly) NSArray *fileInfoList;
- (void)start;
- (void)await;
- (void)cancel;
@end


@protocol SATaskDelegate <NSObject>
- (void)task:(SATask *)task transferPreparing:(SAPreparingDetailState)state;
- (void)task:(SATask *)task fileInfo:(id<SAFileInfo>) fileInfo transferring:(SATransferDetailState)state;
- (void)task:(SATask *)task transferFinished:(SAFinishedDetailState)state;
- (void)task:(SATask *)task error:(SAErrorDetailState)state;
@end


@interface SASendTask : SATask
- (instancetype)initWithFileUrls:(NSArray *)urls; // Array contain NSURL
@end


@interface SAReceiveTask : SATask
- (instancetype)initWithKey:(NSString *)key destDirPath:(NSString *)destDirPath;
@end
