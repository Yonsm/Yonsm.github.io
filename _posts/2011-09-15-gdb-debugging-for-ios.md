---
date: 2011-09-15 17:20:59+00:00
layout: post
title: 终于学会 gdb 调试 iPhone 程序了
thread: 548
categories: 文档
tags: iOS 逆向工程
---

乱摸索尝试，终于搞定了如何查看变量，分析函数调用，哈哈，分析了一下“第一个能安装IPA的IPA”，我也大概知道MobileInstallationInstall的参数了。<!-- more -->  
  
R0: （NSPathStore2）  
(gdb) p (char*)[[NSString stringWithFormat:@"%@",(void*)0x29bca0] UTF8String]  
$21 = 0x88836a0 "/var/mobile/Applications/CEE25E1D-9E40-4DC2-B539-3FE1F87A46FD/Documents/PublicStaging/Youni(有你).ipa"  
  
R1:（__NSCFDictionary）  
(gdb) p (char*)[[NSString stringWithFormat:@"%@",(void*)[0x88cf8c0 allValues]] UTF8String]  
$22 = 0x2e1430 "(\n    User\n)"  
(gdb) p (char*)[[NSString stringWithFormat:@"%@",(void*)[0x88cf8c0 allKeys]] UTF8String]  
$23 = 0x229900 "(\n    ApplicationType\n)"  
  
R2=0  
  
R3=R0
