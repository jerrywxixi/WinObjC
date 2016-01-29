//******************************************************************************
//
// Copyright (c) 2016 Microsoft Corporation. All rights reserved.
//
// This code is licensed under the MIT License (MIT).
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
//******************************************************************************

#pragma once

#import <WebKit/WebKitExport.h>
#import <Foundation/NSCopying.h>
#import <Foundation/NSObject.h>

@class NSURLRequest;
@class WKSecurityOrigin;

WEBKIT_EXPORT_CLASS
@interface WKFrameInfo : NSObject <NSCopying>
@property (nonatomic, readonly, getter=isMainFrame) BOOL mainFrame;
@property (nonatomic, readonly, copy) NSURLRequest* request;
@property (nonatomic, readonly) WKSecurityOrigin* securityOrigin;
@end
