---
author: Yonsm
comments: true
date: 2007-03-21 07:30:11+00:00
layout: post
slug: ntfs-partition-after-you-install-vista-delete-method
title: NTFS 分区安装 Vista 后的删除方法
wordpress_id: 297
categories:
- 文档
tags:
- 分享
- 技巧
---

如果要格式化整个分区，一了百了没话说。  
但如果你不想格式化整个 Vista 所在的分区，那么要删除起来可有点费劲，因为Vista把每个系统子目录很文件都设定了指定的权限，默认情况下，在XP或Win2003中删除不了。我琢磨了一下，终于找到方法，比如要删除 D:\Windows：  
  
  
1. 更改所有者  
TAKEOWN.EXE /F D:\Windows /R /A /D Y  
  
2. 获取权限  
CD D:\Windows  
FOR /R %1 IN (*) DO CACLS.EXE "%1" /E /G Administrators:F  
  
这里最好有这个工具：XCALCS.EXE（可以从 Microsoft/Google 网站上找），则命令变成  
XCACLS.EXE D:\Windows  /T /E /G Administrators:F  
  
3. 删除目录  
RD /Q /S D:\Windows  
  
  

