//
//  SendAnywhere.h
//  SendAnywhereSDK
//
//  Created by SAob_imac27 on 2015. 6. 29..
//  Copyright (c) 2015년 SAob. All rights reserved.
//

#ifndef SendAnywhereSDK_SendAnywhere_h
#define SendAnywhereSDK_SendAnywhere_h



typedef NS_ENUM(NSInteger, SAPreparingDetailState) {
    SAPreparingDetailUndefined,
    SAPreparingDetailUpdatedKey,
    SAPreparingDetailUpdatedFileList,
    
};

typedef NS_ENUM(NSInteger, SATransferDetailState) {
    SATransferDetailTransferring,
};


typedef NS_ENUM(NSInteger, SAFinishedDetailState){
    SAFinishedDetailUndefined,
    SAFinishedDetailSuccess,
    SAFinishedDetailCancel,
    SAFinishedDetailError
};

typedef NS_ENUM(NSUInteger, SAErrorDetailState) {
    SAErrorDetailUndefined,
    SAErrorDetailWrongAPIKey,
    SAErrorDetailServer,
    SAErrorDetailNoRequest,
    SAErrorDetailNoExistFile,
    SAErrorDetailFileNoDownloadPath,
    SAErrorDetailFileNoDiskSpace,
    SAErrorDetailNoExistKey,
};

@protocol SAFileInfo <NSObject>
@property (nonatomic, readonly) NSURL *url;
@property (nonatomic, readonly) NSString *pathName;
@property (nonatomic, readonly) long long transferSize;
@property (nonatomic, readonly) long long totalSize;
@end
#endif
