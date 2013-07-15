---
date: 2011-10-10 01:56:47+00:00
layout: post
title: iOS 程序逆向工程分析方法和工具介绍（GDB、IDA、ARMASM）
thread: 549
categories: 文档
tags: iOS 逆向工程
---

一、简述  
  
先用自己的话给 iOS 做个介绍：iOS 是基于 ARM 处理器的 Mac OS X 的移动设备专用操作系统，可以认为是 Unix-like 的操作系统核心和 Cocoa Touch 应用层构成的一个系统架构。  
  
基于上述描述，要分析 iOS 程序，我们需要有以下基础知识：<!-- more -->  
  
1. ARM 汇编指令  
  
   逆向工程意味着没有源代码可以参考，不得不在很低的一个 Level 去分析程序的意图，然后才能做更进一步的修改的操作。  
  
2. Unix-like 的系统  
  
   了解 Unix-like 系统的基本知识是有必要的，如果有 *nix 上常用的 调试工具 gdb 的知识更佳。  
  
3. Coacoa Touch 的开发语言 Object C  
  
   AppStore 中发布的 iOS 的应用程序都是在 XCode 中使用 Object C 编写出来的，了解开发语言才能更清楚地知道原作者的意图，在一堆堆没有人性的汇编代码面前，做到“目无全牛”绝不是轻而易举能达到的。  
  
0. 逆向工程中常用的思维方式和工具应用  
  
   废话了，这才是本文的重点……  
  
  下面内容中将会介绍到的工具包括：GDB、IDA、CeleASM、ClassDump、WinHex，基于 Mac OS X 下及其蹩脚的和稀有的工具，分析 iOS 程序的主要功能平台听应该选定在 Windows 下进行（Mac OS X下想找到对应的工具，试试看——连个拿得出手的 Hex 编辑工具都没有）。  
  
  
[待续]  
  
二、读懂汇编代码的意图  
  
  
（一）、静态分析  
[待续]  
  
http://www.codethecode.com/projects/class-dump/  
https://github.com/kennytm/iphone-private-frameworks  
http://zhiwei.li/text/2011/09/iphone%E7%A7%81%E6%9C%89api%E8%B7%9F%E7%94%B5%E8%AF%9D%E7%9B%B8%E5%85%B3%E7%9A%84coretelephony/  
http://code.google.com/p/iphone-wireless/source/browse/wiki/CoreTelephonyFunctions.wiki  
  
（二）、动态调试  
[待续]  
  
三、修改汇编代码  
  
[待续]  

