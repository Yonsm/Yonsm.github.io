---
date: 2006-02-12 08:27:24+00:00
layout: post
title: 从 TWAIN 设备中扫描图像
thread: 174
categories: 文档
tags: Win 编程
---

### 一、简介

TWAIN 数据源管理程序 (DSM) 工业标准的软件库，用于从静态图像设备提取图像。绝大部分的扫描仪和数码相机都提供了 TWAIN 驱动程序，利用统一的 TWAIN 接口，应用程序可以非常方便地从这些设备中获取图像。

<!-- more -->  


###   
二、使用步骤

互联网上关于 TWAIN 编程的中文资料很少，代码更是难找到，因为我不得不仔细阅读了 [http://www.twain.org/](http://www.twain.org/) 提供的 TWAIN Specification。下面说说使用 TWAIN 接口获取图像的简要步骤。

  


Windows 系统中存在一个 TWAIN_32.dll，所有的 TWAIN 操作都是通过这个 DLL 导出的 DSM_Entry 函数来实现的 (说实在话，我个人觉得 TWAIN 接口设计得太差了，看看 MS 的WIA，逻辑上非常清晰)。这个函数的声明如下:

  


TW_UINT16 FAR PASCAL DSM_Entry(  
pTW_IDENTITY pOrigin, // Source of message  
pTW_IDENTITY pDest, // Destination of message  
TW_UINT32 DG, // Data group ID: DG_xxxx  
TW_UINT16 DAT, // Data argument type: DAT_xxxx  
TW_UINT16 MSG, // Message ID: MSG_xxxx  
TW_MEMREF pData // Pointer to data  
);

  


1. 打开 DSM (Data Source Manager: 数据源管理器)

  


TWAIN 是一个数据源管理程序，应用程序首先要使用 MSG_OPENDSM 消息，打开数据源管理器。这里需要指定一个窗口句柄，应用程序应该在此窗口的消息循环中处理 TWAIN 消息 (MSG_PROCESSEVENT)。

  


2. 选择 DS (Data Source: 数据源)

  


因为一个系统中可能存在多个 TWAIN 设备，因此必须选择一个数据源。选择数据源通常有两种方式: 选择默认数据源 (MSG_GETDEFAULT) 和显示选择数据源对话框，由用户来选择数据源 (MSG_USERSELECT)。

  


3. 打开 DS

  


使用 MSG_OPENDS 消息打开数据源。

  


4. 设置参数

  


消息为 MSG_SET，设置各种参数，如获取方式、图像数量等。有些参数由设备驱动支持才有效。

  


5. 显示扫描界面

  


使用 MSG_ENABLEDS 消息，显示设备驱动提供的用户界面 (UI)。

  


6. 获取图像

  


如果用户选择扫描什么的，可以在窗口的消息循环中获取到这个事件 (MSG_XFERREADY)。此时，应用程序可以通过 DAT_SETUPFILEXFER 设置文件名，然后用 DAT_IMAGEFILEXFER 获取图像到文件中。

  


7. 关闭扫描界面

  


在窗口的消息循环中获取到 MSG_CLOSEDSREQ 或 MSG_CLOSEDSOK 消息，可以关闭扫描界面 (MSG_DISABLEDS)。

  


8. 关闭 DS

  


消息为 MSG_CLOSEDS。

  


9. 关闭数据源  
  
消息为 MSG_CLOSEDSM。

  


###   
三、CTwainHelper 助手类

为了使用方便，我写了一个静态 TWAIN 助手类 CTwainHelper。使用 CTwainHelper 的五个函数，就可以简单地从 TWAIN 设备获取图像到文件中。使用方法如下:

  


  1. 调用 CTwainHelper::Initialize() 确定是否有可用的设备。 
  2. 在窗口消息循环中，调用 CTwainHelper::ProcessMessage() 处理 TWAIN 消息。 
  3. 要获取图像时，调用 CTwainHelper::GetImage()。 
  4. 如果图像已准备好 (如用户确定扫描图像)，窗口会收到 WM_COMMAND 消息，wParam 为 IDC_TwainHelper。此时应用程序可以调用 CTwainHelper::TransferImage() 获取图像到文件中。

具体使用方法请参看示例代码。  
  
CTwainHelper 可以在 Visual C++ 6.x/7.x 工程中使用，支持 UNICODE 编译。因为是静态类，要改写成 C 代码只需要做一点点少量的工作。  


  


### 四、后话

当然，上面只是一种常用的步骤。其实应用程序完全可以自定义所有的步骤，比如不使用 TWAIN 驱动提供扫描对话框而直接扫描，或者扫描图像到内存中等等。详细情况请参考 TWAIN Specification，步骤大同小异，消息和参数千差万别，仔细看看应该很容易的。

  


如果没有 TWAIN 设备又要进行 TWAIN 程序开发，可以到 TWAIN 官方网站下载 TWAIN Developers Toolkit，安装后会有一个虚拟的 TWAIN 设备。不过应用程序在这个虚拟 TWAIN 设备中正常工作，不代表一定能在实际的 TWAIN 设备正常使用，这点需要注意。以前 CTwainHelper 就碰到过这样的情况 在虚拟 TWAIN 设备中明明是好的，在我的扫描仪上却不能扫描图像。检查后发现，原来设置了不支持的参数。  
  
最后，TWAIN 是 Technology Without A Interesting Name 缩写，直译为没有“没有让人感兴趣名字的技术”，真是一个让人摸不着头脑的名字。

  


TWAIN 助手类: [CTwainHelper](/assets/1099925198.rar) (包含示例代码 35K)  
TWAIN 官方网站: [http://www.twain.org](http://www.twain.org/)  
TWAIN 头文件: [http://www.twain.org/devfiles/twain.h](http://www.twain.org/devfiles/twain.h)  
TWAIN Specification: [http://www.twain.org/docs/Spec1_9_197.pdf](http://www.twain.org/docs/Spec1_9_197.pdf)  
TWAIN Developers Toolkit: [http://www.twain.org/devfiles/twainkit.exe](http://www.twain.org/devfiles/twainkit.exe)

  
  
  
  
[2006.2.22] 下面是更简单的版本，其中的 GetImage 函数内部自动具有消息循环，直到TWAIN对话框完全关闭后才会返回，适合任何场合使用：  
[下载](/assets/TwainHelper.rar) 
