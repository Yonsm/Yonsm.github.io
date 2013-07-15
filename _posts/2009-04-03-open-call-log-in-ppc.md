---
date: 2009-04-03 05:41:28+00:00
layout: post
title: PPC 中打开通话记录
thread: 454
categories: 文档
tags: WM 编程
---

SP 中有一个exe用来打开通话记录，万恶的WM竟然弄得PPC上不一样。经分析找到一个简洁的方法，可以在PPC中打开通话记录界面，代码如下：  
  
  
if (HWND hWnd = FindWindow(TEXT("MSCProg"), NULL))  
{  
 PostMessage(hWnd, 0x801A, 0, 0);  
}  
  
<!-- more -->  
  
又他妈的是私有的消息，做出这么垃圾的系统垃圾的设计，WM 的设计者真该去S!
