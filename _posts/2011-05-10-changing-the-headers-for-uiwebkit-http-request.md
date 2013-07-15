---
date: 2011-05-10 22:12:03+00:00
layout: post
title: '[转载]Changing the headers for UIWebKit HTTP requests - Method Swizzling'
thread: 539
categories: 文档
tags: iOS 编程
---

I was asked several times, in which way the “User-Agent” header can be modified for the HTTP requests that are initiated from within the UIWebView object. iCabMobile is doing this, and also some other iPhone Apps, but the UIWebView API doesn’t provide anything which allows to modify the “User-Agent” information or any other HTTP header.  
  
When you load a web page from the internet through UIWebView, you can provide a delegate which is called for each web page that is loaded. And in the method “webView:shouldStartLoadWithRequest:navigationType:” of the delegate, you’ll even get an NSURLRequest object you can look at, but unfortunately you can not modify this object. So there’s no way to change the default “User-Agent” information that is sent to the server, nor can you modify any other data.<!-- more -->  
  
When you’re loading data from the internet outside of UIWebView, you would probably use the NSURLConnection class. In this case you would create an NSURLRequest object (or the mutable counterpart NSMutableURLRequest) with all the HTTP headers for the request yourself (using the method “setValue:forHTTPHeaderField:”). You have full control over all of the HTTP headers you want to send to the server, including the “User-Agent” information.  
  
When we assume that the UIWebView object will internally also use NSURLRequest or NSMutableURLRequest to create a HTTP request before this request is passed to the networking classes like NSURLConnection, we need a way to subclass or overwrite the method “setValue:forHTTPHeaderField:” of the NSMutableURLRequest class. Then we would be able to check for each HTTP header that is set for a NSMutableURLRequest, if this is the “User-Agent” header and if it is, we can modify it.  
  
The only problem is that we can’t overwrite or subclass the NSMutableURLRequest class and force UIWebView to use our subclass instead of the original class. But iPhone Apps are written in Objective C and this programming language does allow exchanging and modifying classes, methods, variables etc. at runtime any time. So we can tell the Objective C runtime system that each time the method “setValue:forHTTPHeaderField:” of the “NSMutableURLRequest” class is called, our own method is called instead. This way it doesn’t matter that UIWebView will never call our method directly. Exchanging methods is called “Method Swizzling” and you can learn more about it on the CocoaDev page.  
  
The method swizzling is very powerful, but it can be also very dangerous if you don’t know what you’re doing. So be very careful.  
  
Now to the sources. I’ve implemented the method swizzling as a category of NSObject, so you can use it for all classes very easy (but as I said above, be careful, don’t use it if there are other options).  
  
MethodSwizzling.h:  
  
@interface NSObject (Swizzle)  
  
+ (BOOL)swizzleMethod:(SEL)origSelector withMethod:(SEL)newSelector;  
  
@end  
  
  
MethodSwizzling.m:  
  
  
#import "MethodSwizzling.h"  
  
@implementation NSObject (Swizzle)  
  
+ (BOOL)swizzleMethod:(SEL)origSelector withMethod:(SEL)newSelector  
{  
   Method origMethod = class_getInstanceMethod(self, origSelector);  
   Method newMethod = class_getInstanceMethod(self, newSelector);  
  
   if (origMethod && newMethod) {  
       if (class_addMethod(self, origSelector, method_getImplementation(newMethod), method_getTypeEncoding(newMethod))) {  
           class_replaceMethod(self, newSelector, method_getImplementation(origMethod), method_getTypeEncoding(origMethod));  
       } else {  
           method_exchangeImplementations(origMethod, newMethod);  
       }  
       return YES;  
   }  
   return NO;  
}  
  
@end  
  
  
You can call “swizzleMethod:” for an object, passing in the selectors of the original and the new replacement methods. If the “swizzleMethod:” method returns with the result YES, each call of the original method will then call the replacement method and each call of the replacement method will call the original method. So within your replacement method you can still call the original method.  
  
Here’s the implementation of the new replacement method for the NSMutableURLRequest class:  
  
MyMutableURLRequest.h:  
  
@interface NSMutableURLRequest (MyMutableURLRequest)  
  
+ (void)setupUserAgentOverwrite;  
  
@end  
  
  
MyMutableURLRequest.m:  
  
  
#import "MyMutableURLRequest.h"  
#import "MethodSwizzling.h"  
  
@implementation NSMutableURLRequest (MyMutableURLRequest)  
  
- (void)newSetValue:(NSString *)value forHTTPHeaderField:(NSString *)field;  
{  
   if ([field isEqualToString:@"User-Agent"]) {  
       value = @"The new User-Agent string";  
   }  
   [self newSetValue:value forHTTPHeaderField:field];  
}  
  
+ (void)setupUserAgentOverwrite  
{  
   [self swizzleMethod:@selector(setValue:forHTTPHeaderField:)  
           withMethod:@selector(newSetValue:forHTTPHeaderField:)];  
}  
  
@end  
  
  
This new method is implemented as a category, we don’t need to subclass. The replacement method for “setValue:forHTTPHeaderField:” is called “newSetValue:forHTTPHeaderField:” and it is simply checking if the “field” variable is equal to “User-Agent”. If it is, the value is modified. Afterwards the original method is called.  
Please note: because the method swizzling exchanges the original and replacement methods, we have to call “newSetValue:forHTTPHeaderField:” to call the original method “setValue:forHTTPHeaderField:”. This looks confusing, but this is the way you can give control back to the original method.  
  
The method “setupUserAgentOverwrite” has to be called once after the App is launched (for example in the Application delegate in the “applicationDidFinishLaunching:” method, or even in “main()”).  
  
  [NSMutableURLRequest setupUserAgentOverwrite];  
This should be done before any UIWebView objects are created to make sure that the “User-Agent” is modified for all requests.  
  
You can also use this approach when you need to modify other HTTP headers.  
  
转自：http://www.icab.de/blog/2010/04/07/changing-the-headers-for-uiwebkit-http-requests/  
点评：就是Windows下常说的API Hook类似的东西。可能无法通过AppStore的审核。
