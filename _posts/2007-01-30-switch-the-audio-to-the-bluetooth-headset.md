---
date: 2007-01-30 22:07:41+00:00
layout: post
title: 切换音频到蓝牙耳机
thread: 290
categories: 代码
tags: 编程 WM
---

买了个蓝牙耳机，竟然不能把除了电话之外的普通音频切换到蓝牙而机上。分析了一个 BTAudoToggle.exe 的代码，很快搞定。代码如下：  
  
   HANDLE hFile;  
   hFile = CreateFile(TEXT("BAG0:"), 0, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);  
   if (hFile != INVALID_HANDLE_VALUE)  
   {  
     g_pMain->m_uFlag ^= VF_BTAudio;  
     DeviceIoControl(hFile, (g_pMain->m_uFlag & VF_BTAudio) ? 1 : 2, NULL, 0, NULL, 0, NULL, NULL);  
     CloseHandle(hFile);  
   }  
   else  
   {  
     g_pMain->ErrorBox(IDM_Utility_BTAudio);  
   }  
  
  
已整合到最新的 [CeleTask 2.2 RAR](/assets/CeleTask.2.2.rar) 版本内，命令 ID 是 1055。要的话可以到 CeleTask 的日志中下载。  
  
:)
