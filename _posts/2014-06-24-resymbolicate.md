---
date: 2014-06-24 17:31:42+00:00
layout: post
title: 'Re-Symbolicate iOS Crash Report'
categories: 文档
tags: iOS 编程
---

Xcode Organizer 连接手机看 Device Logs 的时候，有个 Re-Symbolicate 功能可以根据地址反查 Call Stack 中系统模块（如UIKit、CoreFoundation等）的符号信息。

如果收到的是第三者设备提供过来的Crash Log，则无法使用该功能。使用以下命令可以实现同样的目的：

      export DEVELOPER_DIR=/Applications/Xcode.app/Contents/Developer
      /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/Library/PrivateFrameworks/DTDeviceKitBase.framework/Versions/A/Resources/symbolicatecrash -v ~/CrashLog.crash


上面提到的是反查系统模块的符号，下面这个则是根据崩溃地址和dSYM来反查自己程序模块中的符号：

    dwarfdump --lookup 0x00002712 -arch armv7 CrashTesting.app.dSYM/
    
一旦从地址中反查到了符号，将非常有助于分析Crash的原因。
