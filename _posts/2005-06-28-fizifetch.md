---
date: 2005-06-28 21:00:57+00:00
layout: post
title: FiziFetch & DumpROM - 从 Smartphone 中提取任何文件
thread: 33
categories: 文档
tags: WM
---

首先，用我写的 FiziFetch 在 SP 中运行，提取物理内存数据文件（ROM，假设为 Fizi.bin）。  
FiziFetch 是一个用于提取物理内存数据的小工具。填写好物理内存的起始地址、欲提取的大小，即可提取数据到输出文件中。(参看 ROMDump 写的小程序，因为 ROM Dump 无法在 SP 上运行)  
  
此程序必须以特权模式运行。在很多ARM机器上可能无法访问物理内存，为了破解需要，我们只需要CoreDLL.dll AygShell.dll 的导出表，与目标平台没关系，所以我们可以运行在 SP2003 x86 模拟器中，提取 x86 的模拟器中的 CoreDLL.dll 即可。这里是我已经提取好的 CoreDLL.dll、AygShell.dll、Phone.dll等，PJ 的朋友可以直接下载使用。  
  
XDA Developer 是对 Pocket PC 的 ROM 深有研究，上面有提取 ROM 文件和创建 ROM 文件的多个工具。在 PC 上用 XDA Developer 的 DumpROM (http://w201.nl/~itsme/projects/xda/dumprom.html) 解出所有 ROM 文件：   
MD Fizi  
  
DumpROM -4 Fizi.bin -d Fizi  
  
关于特权模式，详细请看一下这篇文章：http://www.microsoft.com/china/MSDN/library/Mobility/pocketpc/2k3smartphonesecurity.mspx  
一句话就是要使用 特权证书 Store 里面的下属的数字签名。现在有的手机厂商采用提示数字签名不信任的方式运行，如果得到确认，好像也是运行在特权模式下。  
  
用 eVC 编程的话可能就知道了，Project -> Setting -> Security -> 里面可以选择是否使用特权证书签名以及是否写入特权证书 Store 。  
  
下载: [FiziFetch](/assets/FiziFetch.rar) ( 包含源代码 eVC4/SP4/SP2003SDK Project，x86/ARM目标文件)  
  
下载: SP2003.CoreDll.X86   
[下载](/assets/SP2003.CoreDLL.X86.rar) 
