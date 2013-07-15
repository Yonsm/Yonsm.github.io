---
date: 2006-11-24 03:20:55+00:00
layout: post
title: Menu Bar on Windows Mobile
thread: 280
categories: 文档
tags: WM 编程
---

总结一下 MS WM 上莫名其妙的、非常不爽的 Menu Bar API：  
  
  
**SHCreateMenuBar**：在 SP2003 中不支持SHCMBF_HMENU参数创建，PPC2003 WM5PPC WM5SP 均支持，即不需要 RCDATA 即可创建 MenuBar 非常方便，不仅不需要 RCDATA，String Resource 也省了。  
  
**SHCMBM_GETMENU**：在 WM5PPC 中不支持此消息（除非使用 SHCMBF_HMENU 创建且 Top Level Menu Item 大于 2，但此时 Menu Bar 就成了 PPC2003 的外观了）。其他平台上 PPC2003、SP2003、WM5SP 均支持此消息。代替方案是 SHCMBM_GETSUBMENU，但是这样将无法获取一个 Root Level 的 HMENU，痛苦！  
  
Google 一下，问这类问题的人真多，给通用性程序的API选择带来非常麻烦的问题。再次说声：莫名其妙！  
  
有更好的解决方法的，不妨说一声。
