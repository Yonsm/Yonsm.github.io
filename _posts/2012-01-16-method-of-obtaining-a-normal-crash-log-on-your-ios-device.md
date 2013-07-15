---
date: 2012-01-16 05:49:52+00:00
layout: post
title: 获取普通用户 iOS 设备上的 Crash Log 的方法
thread: 552
categories: 文档
tags: iOS 编程
---

方法1：用工具直接获取 iPhone 设备上 /var/mobile/Library/Logs/CrashReporter  中的 Crash 报告文件。（Mac 下用 PhoneView/iTools/iExplorer，Windows下用、iFunBox、iTools、91助手等）。  
  
方法2：如果 iTunes 同步，则同步后Crash日志会同步到电脑上，把以下目录中的Crash提取打包即可：  
Mac OS X：~/Library/Logs/CrashReporter/MobileDevice  
Windows XP：C:\Documents and Settings\Application Data\Apple computer\Logs\CrashReporter  
Windows 7/Vista: C:\Users\AppData\Roaming\Apple computer\Logs\CrashReporter/MobileDevice/  

