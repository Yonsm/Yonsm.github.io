---
date: 2012-09-28 11:47:20+00:00
layout: post
title: 支持 iOS 6 的通讯录访问功能
thread: 775
categories: 文档
tags: iOS 编程
---

老的 iOS 的程序在 iOS 6 正式版之前能正常访问通讯录功能的，包括在 iOS 6 Beta 4 中，不用做任何改变，只是多了一个UI确认框而已。但在正式版的 iOS 6 中，是无法读取读取到的，需要程序主动（Beta 4 是系统自动发起）申请用户确认后才能读取。这次被苹果摆了一刀……

不过，稍微改进一下代码，可以在不改变原有代码结构的基础上，尽快实现这个功能，下面是代码，直接替换 ABAddressBookCreate 就行了：

<!-- more -->

			//
			ABAddressBookRef ContactCenter::MyAddressBookCreate()
			{
				if (UIUtil::SystemVersion() < 6)
				{
					return ABAddressBookCreate();
				}
				
				ABAddressBookRef book = ABAddressBookCreateWithOptions(NULL, NULL);
				if (ABAddressBookGetAuthorizationStatus() != kABAuthorizationStatusAuthorized)
				{
					static NSCondition *_waiting;
					_waiting = [[NSCondition alloc] init];

					ABAddressBookRequestAccessWithCompletion(book, ^(bool granted, CFErrorRef error) {
						//[_waiting lock];
						[_waiting signal];
						//[_waiting unlock];
					});
					
					//[_waiting lock];
					[_waiting wait];
					//[_waiting unlock];
					[_waiting release];
					_waiting = nil;
				}
				return book;
			}
