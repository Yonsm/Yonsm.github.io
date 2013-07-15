---
date: 2004-11-10 03:53:53+00:00
layout: post
title: CShortcut 类 - 简单方便地操纵创建快捷方式
thread: 118
categories: 代码
---

下载: [CShortcut](/assets/1100001180.rar) (13 KB，包含示例代码)

  


使用方法  
1. 指定文件夹位置 (CSIDL_*) 和快捷方式文件名称即可。  
2. 特别地，如果文件夹位置为 CSIDL_APPDATA 将会转换成快速启动栏的文件夹位置。  
3. 使用之前需要初始化 COM 库 (如 CoInitialize(NULL))。

  

