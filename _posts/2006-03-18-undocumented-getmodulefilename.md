---
date: 2006-03-18 08:56:43+00:00
layout: post
title: '发现GetModuleFileName未公开的功能'
thread: 194
categories: 文档
tags: WM 编程
---

PC 版本的 Windows 中提供了一个 GetModuleFileNameEx 来获取其它进程的可执行文件路径。但是在 Smartphone 中，并没有这个函数。翻遍了所有的文档，也没能发现简单或许其它进程完整路径的方法（ToolHelp API 等等，均不行，当然，复杂的方法，我还是能想出来，不过太得不偿失了）。  
  
现在深夜，突然忽发奇想，用Process ID作为参数，调用 GetModuleFileName((HMODULE) dwProcessID, tzPath, MAX_PATH) ，在 Windows Modile 5.0 Smartphone 和 Windows Modile 2003 Smartphone 中，竟然可以成功获取其它进程的 EXE 文件路径！真是——踏破铁鞋无觅处，得来全不费功夫。  
  
经过试验，在 SP2003/WM2005 中均可正常使用，按推测在，PPC中应该也没问题，不知道 普通的 WinCE 系统中是否也有这个功能。但是，在 PC 版 Windows 上，这样调用将导致失败。  
  
分析了以下原因，PC 版的 Windows 中，Process ID （类似0x00001010之类的值）仅仅是一个整数标识（类似索引一类的）；但是在 SP 中，Process ID （类似0x94344567之类的值）却代表了指向 ???? 的句柄一类的东西？……  
  
MSDN、WinCE/PPC/SP SDK以 及网上均未提及，Yonsm 绝对的 Un-documented 发现——一个莫名其妙的发现！  
  
哈哈哈哈……  
  
补充y一下：  
在VS2005的MSDN里，在 Platform Builder for Microsoft Windows CE 5.0 -> Tool Helper 的帮助中，终于不经意地又发现了一小段提示的话，说 Process ID 和 Thread ID 可以 Cast 成 Process Handle （但按 GetModuleFileName 的解释，Process Handle 依然不是它所能接受的参数） 和 Thread Handle。  
  
To use the process and thread identifiers with GetThreadTimes and other functions that take process handles, the identifiers can be cast directly to process and thread handles. However, accessing PROCESSENTRY32 for other processes requires using the SetProcPermissions function to enable access to the other process's slot.
