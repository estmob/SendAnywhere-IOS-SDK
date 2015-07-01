//
//  ViewController.m
//  SendAnywhereSDKTest
//
//  Created by estmob_imac27 on 2015. 6. 29..
//  Copyright (c) 2015년 estmob. All rights reserved.
//

#import "ViewController.h"


@interface ViewController ()
@property (nonatomic, strong) SAReceiveTask *receiveTask;
@property (nonatomic, strong) SASendTask *sendTask;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

}

- (IBAction)onSend:(id)sender {
    NSURL *url = [[NSBundle mainBundle] URLForResource:@"SendAnywhere" withExtension:@"png"];
    self.sendTask = [[SASendTask alloc] initWithFileUrls:@[url]];
    self.sendTask.delegate = self;
    [self.sendTask start];
}

- (IBAction)onReceive:(id)sender {

    NSArray* paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    self.receiveTask = [[SAReceiveTask alloc] initWithKey:self.textField.text destDirPath:[paths firstObject]];
    self.receiveTask.delegate = self;
    self.sendKeyLabel.text = @"Please wait until the key is generated";
    [self.receiveTask start];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)task:(SATask *)task transferPreparing:(SAPreparingDetailState)state {
    if (state == SAPreparingDetailUpdatedKey) {
        if ([task isEqual:self.sendTask]) {
            self.sendKeyLabel.text = task.key;
        }
    }else if(state == SAPreparingDetailUpdatedFileList){
        NSLog(@"SAPreparingDetailUpdatedFileList %@",task.fileInfoList);
    }
}

- (void)task:(SATask *)task fileInfo:(id<SAFileInfo>)fileInfo transferring:(SATransferDetailState)state {
    if ([task isEqual:self.receiveTask]) {
        self.receiveFileNameLabel.text = fileInfo.pathName;
        self.receiveProgressView.progress = ((double)fileInfo.transferSize)/fileInfo.totalSize;
    }else{
        self.sendFileNameLabel.text = fileInfo.pathName;
        self.sendProgressView.progress = ((double)fileInfo.transferSize)/fileInfo.totalSize;
    }
}

- (void)task:(SATask *)task transferFinished:(SAFinishedDetailState)state {

}

- (void)task:(SATask *)task error:(SAErrorDetailState)state {

}

@end
