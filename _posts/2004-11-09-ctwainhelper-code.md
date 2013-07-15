---
date: 2004-11-09 06:57:32+00:00
layout: post
title: CTwainHelper 助手类
thread: 119
categories: 代码
---

下载: [CTwainHelper](/assets/1099925198.rar) (包含示例代码 35K)

  


使用方法如下:

  


  1. 调用 CTwainHelper::Initialize() 确定是否有可用的设备。 
  2. 在窗口消息循环中，调用 CTwainHelper::ProcessMessage() 处理 TWAIN 消息。 
  3. 要获取图像时，调用 CTwainHelper::GetImage()。 
  4. 如果图像已准备好 (如用户确定扫描图像)，窗口会收到 WM_COMMAND 消息，wParam 为 IDC_TwainHelper。此时应用程序可以调用 CTwainHelper::TransferImage() 获取图像到文件中 。

有关 TWAIN 的介绍和使用请参看: [[从 TWAIN 设备中扫描图像](read.php?174)]

  

