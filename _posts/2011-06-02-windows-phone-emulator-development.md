---
date: 2011-06-02 09:46:46+00:00
layout: post
title: Windows Phone Emulator Unlocked ROM 完整版用于开发调试的方法
thread: 542
categories: 文档
tags: WP 编程
---

Windows Phone Emulator 提供的是一个阉割版的 ROM Image（MS 就是不想 Developer好？），网上很多地方说有 unlocked 的完整版 ROM 下载。Google 一下，果然能找到<!-- more -->”http://forum.xda-developers.com/showthread.php?t=784523“（需翻墙下载）。  
  
刚高兴没多久，发现这个ROM几乎没法用于开发调试，因为每次启动都会非常完全Reboot，”Windows Mobile Emulator is doing a complete OS boot“，将近3分钟或者更久才能完成启动，严重影响调试的心情。  
  
几经琢磨，歪打正着，终于找到了预先Boot这个ROM的方法：  
  
1. 删除C:\ProgramData\Microsoft\XDE文件夹（老的Boot状态）  
2. 执行msiexec /update WindowsPhoneDeveloperResources_en-US_Patch1.msp（这是个WPDT的更新包，你懂的），执行后会等很久才能完成（用任务管理器看XDE进程不在了，则完成了）  
  
之后重新Boot就万事大吉了——终于可以在完整版的ROM里面调试程序了。  
  
另外，刚刚发现 VS2011可以直接打开 WP 的工程文件，但VS2011里面不能创建WP工程（看readme，似乎同样语言的版本似乎可以？）。
