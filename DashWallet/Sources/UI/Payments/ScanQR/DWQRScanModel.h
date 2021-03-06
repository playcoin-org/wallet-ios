//
//  DWQRScanViewModel.h
//  dashwallet
//
//  Created by Andrew Podkovyrin on 21/12/2017.
//  Copyright © 2017 Aaron Voisine. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#import <Foundation/Foundation.h>

#import "DWCaptureSessionFrameDelegate.h"

NS_ASSUME_NONNULL_BEGIN

@class AVCaptureSession;
@class AVMetadataMachineReadableCodeObject;
@class DWPaymentInput;

typedef NS_ENUM(NSUInteger, QRCodeObjectType) {
    QRCodeObjectTypeProcessing,
    QRCodeObjectTypeValid,
    QRCodeObjectTypeValidPaymentRequest,
    QRCodeObjectTypePaymentRequestFailed,
    QRCodeObjectTypeInvalid,
};

@interface QRCodeObject : NSObject

@property (readonly, strong, nonatomic) AVMetadataMachineReadableCodeObject *metadataObject;
@property (readonly, assign, nonatomic) QRCodeObjectType type;
@property (nullable, readonly, copy, nonatomic) NSString *errorMessage;

- (instancetype)init NS_UNAVAILABLE;

@end

//

@protocol DWQRScanModelDelegate;

@interface DWQRScanModel : NSObject

@property (readonly, class, getter=isTorchAvailable) BOOL torchAvailable;

@property (nullable, weak, nonatomic) id<DWQRScanModelDelegate> delegate;
@property (nullable, nonatomic, weak) id<DWCaptureSessionFrameDelegate> frameDelegate;

@property (readonly, strong, nonatomic) AVCaptureSession *captureSession;
@property (readonly, assign, nonatomic, getter=isCameraDeniedOrRestricted) BOOL cameraDeniedOrRestricted;
@property (nullable, readonly, strong, nonatomic) QRCodeObject *qrCodeObject;

- (void)startPreviewCompletion:(void (^)(void))completion;
- (void)stopPreview;

- (void)switchTorch;

- (void)cancel;

@end

@protocol DWQRScanModelDelegate <NSObject>

- (void)qrScanModel:(DWQRScanModel *)viewModel didScanPaymentInput:(DWPaymentInput *)paymentInput;
- (void)qrScanModelDidCancel:(DWQRScanModel *)viewModel;

@end

NS_ASSUME_NONNULL_END
