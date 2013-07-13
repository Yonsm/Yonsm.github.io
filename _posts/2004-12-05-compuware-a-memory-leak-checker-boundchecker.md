---
author: Yonsm
comments: true
date: 2004-12-05 03:56:53+00:00
layout: post
slug: compuware-a-memory-leak-checker-boundchecker
title: Compuware 内存泄露检查工具 BoundChecker
wordpress_id: 93
categories:
- 资源
---

BoundChecker 6.51 版本，如果要集成到 VC，只支持 Visual C++ 6.0，不支持 VS.NET。

  


临时下载(可能失效): [http://free2.e-168.cn/gcygcy/BoundsChecker%206.51.rar](http://free2.e-168.cn/gcygcy/BoundsChecker%206.51.rar)

<!-- more -->  
  


_下列文字摘自: _[_http://www.51testing.com/cgi-bin/viewthread.php?tid=11&sid=zSDHjNCu_](http://www.51testing.com/cgi-bin/viewthread.php?tid=11&sid=zSDHjNCu)

  


程序员在开发过程中可能会经常遇到这样的问题：调试时语法没有问题，代码也没有错误，但应用程序运行就是不正常甚至死机，其实这有可能是由于逻辑错误引起的内存溢出或资源泄露等问题，这些错误一般是不容易被检测出来的。而这类错误就是BoundsChecker错误检测范围之一。  
   通过对被测应用程序的操作，BoundsChecker提供清晰的、详细的程序错误分析，自动查明静态的堆栈错误及内存/资源泄露，并能够迅速的定位出错的源代码，即使在没有源代码的情况下也可检查第三方组件的错误。  
   BoundsChecker错误检测范围主要包括：  
    1)．指针和泄露错误  
        接口泄露  
        内存泄露  
        资源泄露  
        未分配的指针错误  
  
       2)．内存错误  
        动态存储溢出  
        无效的句柄被锁定  
        句柄没有被锁定  
        内存分配冲突  
        栈空间溢出  
        静态存储溢出  
  
3)．API和OLE错误  
        API函数返回失败  
        API函数未执行  
        无效的变量（包括指针变量、字符串变量等）  
        OLE接口方法的变量无效  
        OLE接口方法失败  
        线程调用库函数错误  
  
   BoundsChecker支持的语言和主机平台:  
        C++, Delphi  
        Windows NT, Windows95/98  
  
以上是一个比较早的介绍文字，现在已经支持了c++ builder和windows xp。

  

