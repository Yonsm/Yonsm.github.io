---
date: 2009-05-04 17:57:31+00:00
layout: post
title: 解决 Windows 7 开始菜单和任务栏图标错误地方法
thread: 461
categories: 文档
tags: Win
---

如果安装或运行一个第三方软件（如飞信之类的，系统默认会自动刷新桌面图标），这时我们新建的开始菜单和任务栏快捷方式的图标很容易变成错误的了。Windows 7 Build 7000 到 7100 似乎一直存在这样的问题。  
  
解决办法是用一些系统维护软件重建图标缓存，或者手动操作：<!-- more -->  
  
先把这个文件删除，然后手工：新建文本文件，改名成iconcache.db，属性改为：只读。或者执行如下命令：  
  
  
CD /D %USERPROFILE%\AppData\Local\  
ATTRIB -s -r -h IconCache.db  
COPY /Y NUL IconCache.db  
ATTRIB +r IconCache.db  
  
  
重启电脑，进入桌面后，再把这个文件只读属性去掉！（如果不去掉只读属性，无法缓存图标）  
  

