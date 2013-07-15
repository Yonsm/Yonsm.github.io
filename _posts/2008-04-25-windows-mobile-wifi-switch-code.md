---
date: 2008-04-25 06:39:23+00:00
layout: post
title: Windows Mobile 中开关 WIFI 的“通用”代码
thread: 412
categories: 文档
tags: WM 编程
---

从网上看到用SetDevicePower可以开关WIFI，但郁闷的是不同的OEM厂商，甚至不同型号的手机，WIFI设备名称都可能不一样。  
  
不过我想了想，还是搞定了 Windows Mobile 中开关 WIFI 的"通用"代码，基本上在各种WM手机中都能正常工作。  
  
看下面的代码，主要是枚举所有的通讯设备，如果设备显示名称中包含特定字符串（如Wi-Fi，802.11等）就认为是WIFI设备，接下来的问题迎刃而解，OK，"完美"收工：）<!-- more -->  
  
#pragma once  
#include "UniBase.h"  
#include "Reg.h"  
#include <PM.h>  
  
class CWiFiHelper  
{  
private:  
   TCHAR m_tzDevice[MAX_NAME];

public:  
   CWiFiHelper()  
   {  
       TCHAR tzKey[MAX_PATH];  
       CReg reg(HKEY_LOCAL_MACHINE, TEXT("Comm"));  
       for (UINT i = 0; reg.EnumKey(i, tzKey) == S_OK; i++)  
       {  
           if (tzKey[UStrLen(tzKey) - 1] == '1')  
           {  
               CReg dev(reg, tzKey);  
               TCHAR tzDisplayName[MAX_PATH];  
               if (dev.GetStr(TEXT("DisplayName"), tzDisplayName))  
               {  
                   if (UStrStrI(tzDisplayName, TEXT("WiFi")) ||   
                       UStrStrI(tzDisplayName, TEXT("Wi-Fi")) ||   
                       UStrStrI(tzDisplayName, TEXT("Wireless")) ||   
                       UStrStr(tzDisplayName, TEXT("802.11")))  
                   {  
                       UStrPrint(m_tzDevice, PMCLASS_NDIS_MINIPORT TEXT("[\\%s](file://%25s/)"), tzKey);  
                       //MessageBox(NULL, m_tzDevice, STR_AppName, MB_ICONINFORMATION);  
                       return;  
                   }  
               }  
           }  
       }  
       m_tzDevice[0] = 0;  
   }

   BOOL IsEnabled()  
   {  
       CEDEVICE_POWER_STATE s = D4;  
       if (m_tzDevice [0])  
       {  
           GetDevicePower(m_tzDevice, POWER_NAME, &s);  
       }  
       return s == D0;  
   }

   HRESULT Enable(BOOL bEnable = TRUE)  
   {  
       if (m_tzDevice [0])  
       {  
           return SetDevicePower(m_tzDevice, POWER_NAME, bEnable ? D0 : D4);  
       }  
       else  
       {  
           return ERROR_DEVICE_NOT_AVAILABLE;  
       }  
   }  
};

  
  
  
附件是一个小程序，无参数执行自动切换 WIFI 开关SP/PPC通用。  
  
[]()  
  
  

