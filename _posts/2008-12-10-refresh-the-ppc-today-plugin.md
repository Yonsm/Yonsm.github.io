---
date: 2008-12-10 22:02:51+00:00
layout: post
title: 刷新PPC今日使插件更改生效
thread: 444
categories: 文档
tags: WM 编程
---

更改PPC今日插件项目后，并没有公开的文档说明如何使更改生效，经过分析 cplmain.cpl，找到一个未公开的方法（后来发现网上已经人说过了）：  
  
PostMessage(HWND_BROADCAST, WM_SETTINGCHANGE, 0xF2, 0)。  
  
注意，在Today插件中调用的话，可能造成死锁。  
  
如果要在 CeleCmd 中刷新今日插件的更改，执行如下命令即可：  
  
CDLL %W\CoreDLL.dll,PostMessageW,#0xFFFF,#0x1A,#0xF2,#0
