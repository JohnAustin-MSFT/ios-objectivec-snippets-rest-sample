/*
 * Copyright (c) Microsoft. All rights reserved. Licensed under the MIT license. See full license at the bottom of this file.
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "AuthHelperDelegate.h"

@class ADAuthenticationResult;

/**
 *  Authentication Delegates
 *  This delegate is used for callbacks on authentication
 */
@protocol AuthManagerDelegates <NSObject>

- (void) authSuccess;
- (void) authFailure:(NSError*)error;
- (void) authDisconnect:(NSError*)error;

@end


/**
 *  AuthenticationManager
 *  This class is used as an interface between a UIViewController and authentication.
 *  If additional authentication mechanisms are used, this class is scalable.
 */
@interface AuthenticationManager : NSObject <AuthHelperDelegate>

@property (nonatomic, assign) BOOL isO365Connected;

@property (nonatomic, strong) NSString *userId;
@property (nonatomic, strong) NSString *emailAddress;

@property (nonatomic, weak) id<AuthManagerDelegates> authDelegate;

@property (nonatomic, strong) NSString *accessToken;
@property (nonatomic, strong) NSString *refreshToken;
@property (nonatomic, strong) NSDate *expiresDate;

+ (AuthenticationManager *)sharedInstance;

// Connect O365 account
- (void) connectO365;

// Clear everything on disconnect
- (void) disconnect;

// Check and refresh tokens if needed
- (void)checkAndRefreshToken;

@end

// *********************************************************
//
// O365-iOS-Unified-API-Snippets, https://github.com/OfficeDev/O365-iOS-Unified-API-Snippets
//
// Copyright (c) Microsoft Corporation
// All rights reserved.
//
// MIT License:
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// *********************************************************