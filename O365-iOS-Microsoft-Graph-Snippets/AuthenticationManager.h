/*
 * Copyright (c) Microsoft. All rights reserved. Licensed under the MIT license. See full license at the bottom of this file.
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <ADAuthenticationContext.h>

/**
 *  AuthenticationManager
 *  This class is used as an interface between a UIViewController and authentication.
 *  If additional authentication mechanisms are used, this class is scalable.
 */

@interface AuthenticationManager : NSObject

+ (AuthenticationManager*)sharedInstance;

- (void)initWithAuthority:(NSString *)authority
                 clientId:(NSString *)clientId
              redirectURI:(NSString *)redirectURI
               resourceID: (NSString *)resourceID
               completion:(void (^)(ADAuthenticationError *error))completion;

@property (nonatomic, strong) NSString *accessToken;
@property (nonatomic, strong) NSString *refreshToken;
@property (nonatomic, strong) NSDate *expiresDate;

@property (nonatomic, strong) NSString *givenName;
@property (nonatomic, strong) NSString *familyName;
@property (nonatomic, strong) NSString *userID;

// Acquire token
- (void)acquireAuthTokenWithResource:(NSString *)resourceID
                            clientID:(NSString *)clientID
                         redirectURI:(NSURL*)redirectURI
                          completion:(void (^)(ADAuthenticationError *error))completion;

- (void) acquireAuthTokenCompletion:(void (^)(ADAuthenticationError *error))completion;

// Clears the ADAL token cache and the cookie cache.
- (void) clearCredentials;

// Check and refresh tokens if needed
- (void) checkAndRefreshTokenWithCompletion:(void (^)(ADAuthenticationError *error))completion;

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