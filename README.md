SendAnywhere-IOS-SDK
===

Task Constructor
---

```
@interface SASendTask : SATask
- (instancetype)initWithFileUrls:(NSArray *)urls;
@end

@interface SAReceiveTask : SATask
- (instancetype)initWithKey:(NSString *)key destDirPath:(NSString *)destDirPath;
@end
```

### SASendTask
Parameters |                       |
-----------| ----------------------|
urls       | The file list to send |


### ReceiveTask
Parameters  |                                     |
------------| ------------------------------------|
key         | The KEY for sending files           |
destDirPath | The folder path for receiving files |


Public method
---

```
@interface SATask : NSObject
- (void)start;
- (void)await;
- (void)cancel;
@end
```

### static void init(String key)
Set your API key.

Parameters |               |
-----------| --------------|
key        | Your API Key. |

### void start()
Start a task for sending or receiving files.

### void await()
Wait until the task is finished.

### void cancel()
Stop and cancel the running task.


Delegate for task
---
```
@protocol SATaskDelegate <NSObject>
- (void)task:(SATask *)task transferPreparing:(SAPreparingDetailState)state; 
- (void)task:(SATask *)task fileInfo:(id<SAFileInfo>) fileInfo transferring:(SATransferDetailState)state;
- (void)task:(SATask *)task transferFinished:(SAFinishedDetailState)state;
- (void)task:(SATask *)task error:(SAErrorDetailState)state;
@end
```

### Delegate for prepared transfering
```
- (void)task:(SATask *)task transferPreparing:(SAPreparingDetailState)state;
typedef NS_ENUM(NSInteger, SAPreparingDetailState) {
    SAPreparingDetailUndefined, 
    SAPreparingDetailUpdatedKey,
    SAPreparingDetailUpdatedFileList,
    
};
```
### Delegate for transfering
```
- (void)task:(SATask *)task fileInfo:(id<SAFileInfo>) fileInfo transferring:(SATransferDetailState)state;
typedef NS_ENUM(NSInteger, SATransferDetailState) {
    SATransferDetailTransferring,
};

```

### Delegate for finished transfering
```
- (void)task:(SATask *)task transferFinished:(SAFinishedDetailState)state;
typedef NS_ENUM(NSInteger, SAFinishedDetailState){
    SAFinishedDetailUndefined,
    SAFinishedDetailSuccess,
    SAFinishedDetailCancel,
    SAFinishedDetailError
};
```

### Delegate for error
```
- (void)task:(SATask *)task error:(SAErrorDetailState)state;
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
```

### Flow Step
  * SAPreparingDetailUpdatedKey
    * SAPreparingDetailUpdatedFileList
      * SATransferDetailTransferring
      * SATransferDetailTransferring
      * ...
      * SATransferDetailTransferring
      * SATransferDetailTransferring
        * SAFinishedDetailSuccess 
        * SAFinishedDetailCancel
        * SAFinishedDetailError


File Information
---
```
@protocol SAFileInfo <NSObject>
    @property (nonatomic, readonly) NSURL *url; // File URL
    @property (nonatomic, readonly) NSString *pathName; // Relative file path
    @property (nonatomic, readonly) long long transferSize; // transfered file size in bytes
    @property (nonatomic, readonly) long long totalSize; // file size in bytes
@end
```
