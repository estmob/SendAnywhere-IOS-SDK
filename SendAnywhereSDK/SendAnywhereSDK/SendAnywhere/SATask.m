//
//  SATask.m
//  SendAnywhereSDK
//
//  Created by estmob_imac27 on 2015. 6. 29..
//  Copyright (c) 2015년 estmob. All rights reserved.
//

#import "SATask.h"
#import "paprika/paprika.h"
#import "NSString+SAAddtions.h"
#import "SAAuthToken.h"
#import "SAOption.h"

@interface SATransferFileInfo : NSObject<SAFileInfo>
- (instancetype)initWithURL:(NSURL*)url pathName:(NSString*)pathName totalSize:(long long) totalSize;
- (void)setTransferSize:(long long)transferSize;
@end


@implementation SATransferFileInfo
@synthesize url = __url;
@synthesize pathName = __pathName;
@synthesize totalSize = __totalSize;
@synthesize transferSize = __transferSize;

- (instancetype)initWithURL:(NSURL *)url pathName:(NSString *)pathName totalSize:(long long)totalSize {
    self = [super init];
    if(self) {
        __url = [url copy];
        __pathName = [pathName copy];
        __totalSize = totalSize;
    }
    return self;
}

- (void)setTransferSize:(long long)transferSize {
    __transferSize = transferSize;
}

- (NSString *)description {
    return [NSString stringWithFormat:@"{ url: %@, pathName: %@, totalSize: %lld}",self.url,self.pathName,self.totalSize];
}

- (NSString *)debugDescription {
    return [self description];
}

@end


@interface SATask ()
@property (nonatomic, readonly) PaprikaTask task;
- (void)setTask:(PaprikaTask)task;
- (void)setTransferKey:(NSString*)key;
@end

@implementation SATask

@synthesize task = __task;
@synthesize key = __key;
@synthesize fileInfoList = __fileInfoList;

- (instancetype)init {
    self = [super init];
    if (self) {
        NSString *apiKey = [[NSBundle mainBundle] infoDictionary][@"SAAPIKey"];
        assert(apiKey);
        paprika_set_apikey([apiKey UTF8String]);

        [self initOptionValue];
    }
    return self;
}


- (void)initOptionValue{

}

- (void)start {
    paprika_set_auth(self.task, [[SAAuthToken sharedInstance] authToken]);
    paprika_set_option(self.task, [[SAOption sharedInstance] option]);
    paprika_set_listner(self.task, transferCallback, (__bridge void *)self);
    paprika_start(self.task);
}

- (void)setTask:(PaprikaTask)task {
    __task = task;

}

- (void)setTransferKey:(NSString *)key {
    __key = key;
}


- (void)setFileInfoList:(NSArray *)fileInfoList {
    __fileInfoList = [fileInfoList copy];
}

- (void)await {
    paprika_wait(self.task);
}

- (void)cancel {
    paprika_cancel(self.task);
}

- (void)close {
    paprika_close(self.task);


}

- (void)dealloc {
    [self close];
}



SAFinishedDetailState convertSAfinishedStateFromPaprikaState(PaprikaDetailedState detailState){
    if (detailState == PAPRIKA_DETAILED_STATE_FINISHED_SUCCESS) {
        return SAFinishedDetailSuccess;
    }
    if (detailState == PAPRIKA_DETAILED_STATE_FINISHED_CANCEL) {
        return SAFinishedDetailCancel;
    }
    
    if (detailState == PAPRIKA_DETAILED_STATE_FINISHED_ERROR) {
        return SAFinishedDetailError;
    }
    
    return SAFinishedDetailUndefined;
    
}

SAErrorDetailState convertSAErrorStateFromPaprikaState(PaprikaDetailedState detailState){
    
    switch (detailState) {
        case PAPRIKA_DETAILED_STATE_ERROR_WRONG_API_KEY:
            return SAErrorDetailWrongAPIKey;
            
        case PAPRIKA_DETAILED_STATE_ERROR_NO_REQUEST:
            return SAErrorDetailNoRequest;
            
        case PAPRIKA_DETAILED_STATE_ERROR_NO_EXIST_FILE:
            return SAErrorDetailNoExistFile;
            
        case PAPRIKA_DETAILED_STATE_ERROR_NO_EXIST_KEY:
            return SAErrorDetailNoExistKey;
            
        case PAPRIKA_DETAILED_STATE_ERROR_FILE_NO_DOWNLOAD_PATH:
            return SAErrorDetailFileNoDownloadPath;
            
        case PAPRIKA_DETAILED_STATE_ERROR_FILE_NO_DISK_SPACE:
            return SAErrorDetailFileNoDiskSpace;
        case PAPRIKA_DETAILED_STATE_ERROR_SERVER_WRONG_PROTOCOL:
        case PAPRIKA_DETAILED_STATE_ERROR_SERVER_NETWORK:
        case PAPRIKA_DETAILED_STATE_ERROR_REQUIRED_LOGIN:
        case PAPRIKA_DETAILED_STATE_ERROR_SERVER_AUTHENTICATAION:
            return SAErrorDetailServer;

    }
    
    return SAErrorDetailUndefined;
    
}


void transferCallback(PaprikaState state, PaprikaDetailedState detailedState, const void* param, void* userptr) {
    SATask* task = (__bridge SATask*)userptr;
    if(state == PAPRIKA_STATE_PREPARING) {
        if(detailedState == PAPRIKA_DETAILED_STATE_PREPARING_UPDATED_KEY) {
            const wchar_t* key = (const wchar_t*)param;
            [task setTransferKey:[NSString stringWithWchart:key]];
            dispatch_async(dispatch_get_main_queue(), ^{
                [task.delegate task:task transferPreparing:SAPreparingDetailUpdatedKey];
            });
        } else if(detailedState == PAPRIKA_DETAILED_STATE_PREPARING_UPDATED_FILE_LIST) {
            PaprikaAllTransferFileState* allFileStates = (PaprikaAllTransferFileState*)param;
            NSMutableArray *array = [NSMutableArray array];
            for( NSInteger i = 0; i < allFileStates->number ; i++ ) {
                PaprikaTransferFileState* fileState = &allFileStates->fileState[i];
                NSString *fileName = [NSString stringWithWchart:fileState->name];
                NSString *fullPath = [NSString stringWithWchart:fileState->fullPath];
                NSURL *url = [NSURL fileURLWithPath:fullPath];
                SATransferFileInfo *fileInfo = [[SATransferFileInfo alloc] initWithURL:url pathName:fileName totalSize:fileState->size];
                [array addObject:fileInfo];
            }
            [task setFileInfoList:array];
            dispatch_async(dispatch_get_main_queue(), ^{
                [task.delegate task:task transferPreparing:SAPreparingDetailUpdatedFileList];
            });
        }else if(detailedState == PAPRIKA_DETAILED_STATE_PREPARING_UPDATED_DEVICE_ID){
            [[SAAuthToken sharedInstance] update];
        }
    } else if(state == PAPRIKA_STATE_TRANSFERRING) {
        PaprikaTransferFileState* fileState = (PaprikaTransferFileState*)param;
        SATransferFileInfo *fileInfo = [[task.fileInfoList filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"url.relativePath = %@", [NSString stringWithWchart:fileState->fullPath]]] lastObject];
        if (detailedState == PAPRIKA_DETAILED_STATE_TRANSFERRING_ACTIVE || detailedState == PAPRIKA_DETAILED_STATE_TRANSFERRING_SERVER || detailedState == PAPRIKA_DETAILED_STATE_TRANSFERRING_PASSIVE) {
            [fileInfo setTransferSize:fileState->sent];
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            [task.delegate task:task fileInfo:fileInfo transferring:SATransferDetailTransferring];
        });

    } else if(state == PAPRIKA_STATE_FINISHED) {
        SAFinishedDetailState finishedState = convertSAfinishedStateFromPaprikaState(detailedState);
        dispatch_async(dispatch_get_main_queue(), ^{
            [task.delegate task:task transferFinished:finishedState];
        });

    } else if(state == PAPRIKA_STATE_ERROR){
        SAErrorDetailState errorState = convertSAErrorStateFromPaprikaState(detailedState);
        dispatch_async(dispatch_get_main_queue(), ^{
            [task.delegate task:task error:errorState];
        });
    }
}

@end


@interface SASendTask ()

@end

@implementation SASendTask


- (instancetype)initWithFileUrls:(NSArray *)urls {
    self = [super init];
    if (self) {
        const wchar_t **files = malloc(sizeof(PaprikaUploadFileInfo)* urls.count);
        [self getFilePathList:files fileItems:urls];
        PaprikaTask task = paprika_create_upload_stream(
                                              files,      // file array pointer
                                              (unsigned int)urls.count,          // file number
                                              NULL,     // stream array pointer
                                              0,          // stream number
                                              NULL,       // wish key
                                              NO,       // save24 mode?
                                              NO // mix number/alphabet key?
                                              );
        [self setTask:task];

    }
    return self;
}

- (void)getFilePathList:(const wchar_t**)files fileItems:(NSArray*)items {
    for (NSInteger i = 0; i < items.count; i++) {
        NSURL *item = items[i];
        files[i] = [[item relativePath] wchart];
    }
}

@end


@implementation SAReceiveTask

- (instancetype)initWithKey:(NSString *)key destDirPath:(NSString *)destDirPath {
    self = [super init];
    if (self) {
        PaprikaTask task = paprika_create_download(
                                         [key wchart],        // key
                                         [destDirPath wchart]    // download path
                                         );
        [self setTask:task];
    }
    return self;
}

@end



