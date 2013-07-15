---
date: 2006-04-08 00:17:28+00:00
layout: post
title: ARM平台上可能Crash的“正常代码”
thread: 201
categories: 文档
tags: WM 编程
---

  
PBYTE p = new BYTE[i + 4];  
PDWORD q = (PDWORD) (p + i);  
*q = 0;  
  
  
上面几行代码在PC上是再正常不过的了（比如希望在某块Buffer后面几个字节置零），但是这几行“正常代码”却导致CeleTask运行起来Crash。<!-- more -->开始一头雾水，分析一下原因，印象中（因为我没有ARM上的开发经验，所以ARM细节不清楚。这好像是和Team同事hj聊天时听到的，所以是印象中）ARM平台上32位数的Load/Store必须到4字节对齐的地址上（类推，16位数必须对齐到2字节地址）。  
  
改成下面的代码就没问题了：  
  
  
PBYTE p = new BYTE[i + 4];  
p_ = p[i+1] = p[i+2] = p[i+3] = 0;  

