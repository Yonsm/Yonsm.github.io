---
date: 2012-09-27 12:11:00+00:00
layout: post
title: '[转载]iPhone模拟触屏实现事件教程'
thread: 767
categories: 文档
tags: iOS 编程
---

iPhone模拟触屏实现事件教程是本文呀介绍的内容，不多说，我们先来看内容。目前又有了一个想在iPhone上做协助调试的设想，当然控制权什么的是别说了，就是做一些协助方在自己屏幕上点点划划，被协助方也要有同样的操作，因为被调试程序的不确定性，那只能做成发送各种针对屏幕的模拟事件了。

因为apple没有放出直接发送触屏事件等的API，所以用的都是越狱的iPhone加上PrivateFramework，根本没指望上市，反正就是为了内部调试。

首先在kennytm的网站拔下私有framework的头文件，就本应用而言，只需要GrapicsServices文件夹以及Availability2.h即可。然后导入Xcode目录下Platforms下对应的GraphicsService.framework，准备工作就OK了。

发送事件消息，主要是构造GSEventRecord，简单的事件可能只需要填充GSEventRecord里面的type类型参数，再复杂一些的就需要在结构的后面继续填充，填充大小必须在infoSize参数里指定

C代码

			typedef struct GSEventRecord {     
			    GSEventType type; // 0x8     
			    GSEventSubType subtype; // 0xC     
			    CGPoint location;   // 0x10     
			    CGPoint windowLocation; // 0x18     
			    int windowContextId;    // 0x20     
			    uint64_t timestamp; // 0x24, from mach_absolute_time     
			    GSWindowRef window; // 0x2C     
			    GSEventFlags flags; // 0x30     
			    unsigned senderPID; // 0x34     
			    CFIndex infoSize; // 0x38     
			} GSEventRecord;    
			 
			typedef struct GSEventRecord {  
			 GSEventType type; // 0x8  
			 GSEventSubType subtype; // 0xC  
			 CGPoint location;  // 0x10  
			 CGPoint windowLocation; // 0x18  
			 int windowContextId; // 0x20  
			 uint64_t timestamp; // 0x24, from mach_absolute_time  
			 GSWindowRef window; // 0x2C  
			 GSEventFlags flags; // 0x30  
			 unsigned senderPID; // 0x34  
			 CFIndex infoSize; // 0x38  
			} GSEventRecord;
头文件里没有提供一些便捷方法构造复杂的信息结构，这和public API真是云泥之别。不过一些非常简单的消息还是可以直接调用的，如void GSEventLockDevice();就相当与构造了一个type为kGSEventLockDevice的GSEventRecord结构再将其发送出去。

用一个稍微复杂的例子，我们向屏幕的{50，50}坐标处发送一个“按下”的指令

C代码

			#import "GSEvent.h"     
			#include <mach/mach_time.h>     
			void sendclickevent(){     
			    mach_port_t thePortOfApp = GSCopyPurpleNamedPort("com.fuckyou.fuck");     
			         
			    GSEventRecord header;     
			    GSHandInfo click;     
			    GSPathInfo pathInfo = {2,2,2,1,1,{50,50}, NULL};     
			         
			    bzero(&header, sizeof(header));     
			    bzero(&click, sizeof(click));     
			    
			    header.type = kGSEventHand;     
			    header.subtype = kGSEventSubTypeUnknown;     
			    header.location.x = 50;     
			    header.location.y = 50;     
			    header.windowLocation.x = 50;     
			    header.windowLocation.y = 50;     
			    header.infoSize = sizeof(GSHandInfo)+sizeof(GSPathInfo);     
			    header.timestamp = mach_absolute_time();     
			    
			    click.type = kGSHandInfoTypeTouchDown;     
			    click.deltaX = 1;     
			    click.deltaY = 1;     
			    click.pathInfosCount = 1;     
			         
			    struct    
			    {     
			        GSEventRecord record;     
			        GSHandInfo hand;     
			        GSPathInfo path;     
			    } record = {header, click, pathInfo};     
			         
			    GSSendEvent(&record, thePortOfApp);     
			}    
			 
			#import "GSEvent.h"  
			#include <mach/mach_time.h> 
			void sendclickevent(){  
			    mach_port_t thePortOfApp = GSCopyPurpleNamedPort("com.fuckyou.fuck");  
			      
			    GSEventRecord header;  
			    GSHandInfo click;  
			    GSPathInfo pathInfo = {2,2,2,1,1,{50,50}, NULL};  
			      
			    bzero(&header, sizeof(header));  
			    bzero(&click, sizeof(click));  
			 
			    header.type = kGSEventHand;  
			    header.subtype = kGSEventSubTypeUnknown;  
			    header.location.x = 50;  
			    header.location.y = 50;  
			    header.windowLocation.x = 50;  
			    header.windowLocation.y = 50;  
			    header.infoSize = sizeof(GSHandInfo)+sizeof(GSPathInfo);  
			    header.timestamp = mach_absolute_time();  
			 
			    click.type = kGSHandInfoTypeTouchDown;  
			    click.deltaX = 1;  
			    click.deltaY = 1;  
			    click.pathInfosCount = 1;  
			      
			    struct  
			    {  
			        GSEventRecord record;  
			        GSHandInfo hand;  
			        GSPathInfo path;  
			    } record = {header, click, pathInfo};  
			      
			    GSSendEvent(&record, thePortOfApp);  
			}
里面需要注意的是向某应用发送事件，必须获得该应用的端口，也就是第一行代码。而发送复杂的信息必须要将若干信息体拼接到一起，自己定义一写需要的结构体比较合适，并正确填写信息体的大小，这些技巧仿佛回到了蛮荒时代。我本身看到0长数组，顺手就在堆上构造结构了，但这些消息的处理是异步的，我也不清楚何时可以安全地回收内存，所以建议还是使用结构体拼凑的方法。

除了触屏之外，另一个非常重要的就是键盘输入了，但是iPhone的输入的特殊性，不太好说是键盘输入，反正就是那个意思。

具体编码过程其实和触屏事件没什么两样，不过如果把GSHardwareKeyInfo或者GSKeyInfo这种似乎是键盘事件的结构名放google上搜索，一个结果都没有，一开始我还想凑，花了两三天实在凑不出来了发现其实可以逆向来嘛，用GSEventCreateKeyEvent创造一个键盘事件，然后解析它就是，于是这样才搞定，而且可悲的发现其实我想得太多了，里面绝大多数成员填0就行了，没必要为编码区这些东西烦恼。

Objective-c代码

			GSEventRecord header;     
			GSHardwareKeyInfo key = {0,0,0,0,1,{'a'},1,{'a'},0,0,0,0};     
			memset(&header, 0, sizeof(header));     
			    
			header.type = kGSEventKeyDown;     
			header.infoSize = sizeof(GSHardwareKeyInfo);     
			header.timestamp = mach_absolute_time();     
			    
			struct     
			{     
			    GSEventRecord header1;     
			    GSHardwareKeyInfo key1;     
			}fuck = {header, key};     
			GSSendEvent(&fuck, GSGetPurpleApplicationPort());    
			 
			    GSEventRecord header;  
			    GSHardwareKeyInfo key = {0,0,0,0,1,{'a'},1,{'a'},0,0,0,0};  
			    memset(&header, 0, sizeof(header));  
			      
			    header.type = kGSEventKeyDown;  
			    header.infoSize = sizeof(GSHardwareKeyInfo);  
			    header.timestamp = mach_absolute_time();  
			      
			    struct  
			    {  
			        GSEventRecord header1;  
			        GSHardwareKeyInfo key1;  
			    }fuck = {header, key};  
			    GSSendEvent(&fuck, GSGetPurpleApplicationPort());
这样就可以输入一个a了，前提是光标必须在输入框内。

当然后续问题还有很多，这实际上不过是自己的程序向自己的发送事件而已，后面需要做的是程序运行到后台时向前台程序甚至是主界面发事件，能否做到，我也不敢肯定。

小结：iPhone模拟触屏实现事件教程的内容介绍完了，希望本文对你有所帮助！更多相关内容请参考编辑推荐。
