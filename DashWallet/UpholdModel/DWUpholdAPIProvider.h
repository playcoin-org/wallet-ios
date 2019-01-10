//
//  Created by Andrew Podkovyrin
//  Copyright © 2018 Dash Core Group. All rights reserved.
//
//  Licensed under the MIT License (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  https://opensource.org/licenses/MIT
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class DWUpholdCardObject;
@class DWUpholdTransactionObject;

typedef NS_ENUM(NSUInteger, DWUpholdAPIProviderResponseStatusCode) {
    DWUpholdAPIProviderResponseStatusCodeOK,
    DWUpholdAPIProviderResponseStatusCodeUnauthorized,
};

@interface DWUpholdAPIProvider : NSObject

+ (NSOperation *)authOperationWithCode:(NSString *)code
                            completion:(void (^)(NSString *_Nullable accessToken))completion;
+ (NSOperation *)getDashCardAccessToken:(NSString *)accessToken
                             completion:(void (^)(BOOL success, DWUpholdAPIProviderResponseStatusCode statusCode, DWUpholdCardObject *_Nullable card))completion;
+ (NSOperation *)createDashCardAccessToken:(NSString *)accessToken
                                completion:(void (^)(BOOL success, DWUpholdAPIProviderResponseStatusCode statusCode, DWUpholdCardObject *_Nullable card))completion;
+ (NSOperation *)createAddressForDashCard:(DWUpholdCardObject *)inputCard
                              accessToken:(NSString *)accessToken
                               completion:(void (^)(BOOL success, DWUpholdAPIProviderResponseStatusCode statusCode, DWUpholdCardObject *_Nullable card))completion;
+ (NSOperation *)createTransactionForDashCard:(DWUpholdCardObject *)card
                                       amount:(NSString *)amount
                                      address:(NSString *)address
                                  accessToken:(NSString *)accessToken
                                     otpToken:(nullable NSString *)otpToken
                                   completion:(void (^)(BOOL success, DWUpholdAPIProviderResponseStatusCode statusCode, DWUpholdTransactionObject *_Nullable transaction, BOOL otpRequired))completion;
+ (NSOperation *)commitTransaction:(DWUpholdTransactionObject *)transaction
                              card:(DWUpholdCardObject *)card
                       accessToken:(NSString *)accessToken
                          otpToken:(nullable NSString *)otpToken
                        completion:(void (^)(BOOL success, DWUpholdAPIProviderResponseStatusCode statusCode, BOOL otpRequired))completion;
+ (NSOperation *)cancelTransaction:(DWUpholdTransactionObject *)transaction
                              card:(DWUpholdCardObject *)card
                       accessToken:(NSString *)accessToken
                          otpToken:(nullable NSString *)otpToken;

@end

NS_ASSUME_NONNULL_END
