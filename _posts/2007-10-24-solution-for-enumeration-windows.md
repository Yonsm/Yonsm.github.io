---
date: 2007-10-24 04:05:28+00:00
layout: post
title: 枚举窗口假死和枚举进程失败的解决方案
thread: 379
categories: 文档
tags: WM 编程
---

CeleTask 枚举任务窗口时，如果其他程序停止响应，可能会出现假死状态。枚举进程的部分如果内存过少（或者某些程序开着），会出现无法成功的情况。今天经过仔细分析，终于找到了终极解决方案。  
  
1. 枚举窗口没有问题，问题出在获取窗口标题上，WM_GETTEXT/GetWindowText 均会造成程序等待，如果其他进程窗口假死，则CeleTask也等着。解决方法是使用以下方法获取标题，经试验完美解决：  
  
SendMessageTimeout(hWnd, WM_GETTEXT, MAX_NAME, (LPARAM) &tzStr;, 0, 100, &dwRet;);  
  
2. 进程枚举失败的部分，经过反汇编分析 SKTools 的代码，发现一个 Undocumented 的 Flag: 0x40000000，把这个 标记设置在 CreateToolhelpSnapshot 上，就可以了。经查确认，此标志无文档支持，但经测试以完美解决。  
  
市面上所有的窗口枚举和进程枚举软件均存在此问题（SKTools的进程功能除外），包括QuickMenu等。现已解决，分享在此。<!-- more -->  
  
基于以上结论， CeleTask 将在近期更新版本 2.4 ，除了解决上述问题，还将加入其他功能（导入注册表文件等）。Smartphone 用户可留意本 BLOG 的更新信息。  
  
  
2007.10.27 更新：声明如下未公开的函数，代替GetWindowText使用，效果最佳，无阻赛问题，速度快，P/PPC 2003/5.0/6.0 均适用：  
  
extern "C" INT WINAPI GetWindowTextWDirect(HWND hWnd, PWSTR pwzStr, INT nMaxCount);  

