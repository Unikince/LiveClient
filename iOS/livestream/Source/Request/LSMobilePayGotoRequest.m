//
//  LSMobilePayGotoRequest.m
//  dating
//
//  Created by Alex on 19/10/09.
//  Copyright © 2019年 qpidnetwork. All rights reserved.
//

#import "LSMobilePayGotoRequest.h"

@implementation LSMobilePayGotoRequest
- (instancetype)init{
    if (self = [super init]) {
        self.orderType = LSORDERTYPE_FLOWERGIFT;
        self.clickFrom = @"";
        self.number = @"";
        self.orderNo = @"";
    }
    
    return self;
}

- (void)dealloc {
    
}

- (BOOL)sendRequest {
    if( self.manager ) {
        __weak typeof(self) weakSelf = self;
        NSInteger request = [self.manager mobilePayGoto:self.orderType clickFrom:self.clickFrom number:self.number orderNo:self.orderNo finishHandler:^(BOOL success, HTTP_LCC_ERR_TYPE errnum, NSString *errmsg, NSString *redirtctUrl)  {
            BOOL bFlag = NO;
            
            // 没有处理过, 才进入LSSessionRequestManager处理
            if( !weakSelf.isHandleAlready && weakSelf.delegate && [weakSelf.delegate respondsToSelector:@selector(request:handleRespond:errnum:errmsg:)] ) {
                bFlag = [self.delegate request:weakSelf handleRespond:success errnum:errnum errmsg:errmsg];
                weakSelf.isHandleAlready = YES;
            }
            
            if( !bFlag && weakSelf.finishHandler ) {
                weakSelf.finishHandler(success, errnum, errmsg, redirtctUrl);
                [weakSelf finishRequest];
            }
        }];
        return request != 0;
    }
    return NO;
}

- (void)callRespond:(BOOL)success errnum:(HTTP_LCC_ERR_TYPE)errnum errmsg:(NSString* _Nullable)errmsg {
    if( self.finishHandler && !success ) {
        self.finishHandler(NO, errnum, errmsg, @"");
    }
    
    [super callRespond:success errnum:errnum errmsg:errmsg];
}

@end
