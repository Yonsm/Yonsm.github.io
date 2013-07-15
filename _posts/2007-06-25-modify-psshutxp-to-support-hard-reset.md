---
date: 2007-06-25 11:18:14+00:00
layout: post
title: 修改 psShutXP 使他的硬起功能生效
thread: 342
categories: 代码
tags: 逆向工程 WM
---

经验征得之，SetCleanRebootFlag 对于 HTC 系列的 PPC 无效。但一般的软件硬起，往往就用这个函数，psShutXP 也不例外。  
  
我已经修改 psShutXP，让它的硬起功能真的“硬起”了。下面是分析 HTC ClearStorage 的关键代码（这很容易，但是要把这些代码挪动到 psShutXP 中，那不是一般的难啊——还好我搞定了：）。<!-- more -->  
  
  
// HTC Cold Reboot  
.text:00011000 sub_11000                               ; CODE XREF: sub_11064+11C p  
.text:00011000                                         ; DATA XREF: .pdata:00014000 o  
.text:00011000  
.text:00011000 var_8           = -8  
.text:00011000 var_4           = -4  
.text:00011000 arg_4           =  4  
.text:00011000  
.text:00011000                 STR     LR, [SP,#var_4]!  
.text:00011004                 SUB     SP, SP, #8  
.text:00011008                 LDR     R0, =0x1012594  
.text:0001100C                 MOV     LR, #0  
.text:00011010                 MOV     R3, #0  
.text:00011014                 MOV     R2, #0  
.text:00011018                 MOV     R1, #0  
.text:0001101C                 STR     LR, [SP,#8+var_4]  
.text:00011020                 STR     LR, [SP,#8+var_8]  
.text:00011024                 BL      KernelIoControl  
.text:00011024  
.text:00011028                 ADD     SP, SP, #8  
.text:0001102C                 LDR     PC, [SP],#arg_4  
.text:0001102C  
.text:0001102C ; End of function sub_11000  
.text:0001102C  
.text:0001102C ; ---------------------------------------------------------------------------  
.text:00011030 dword_11030     DCD 0x1012594           ; DATA XREF: sub_11000+8 r  
  
  
  
// REEBOOT  
.text:00011034  
.text:00011034                 STR     LR, [SP,#var_4]!  
.text:00011038                 MOV     R3, #0  
.text:0001103C                 MOV     R2, #0  
.text:00011040                 MOV     R1, #0  
.text:00011044                 MOV     R0, #0xDF  
.text:00011048                 BL      keybd_event  
.text:00011048  
.text:0001104C                 MOV     R3, #0  
.text:00011050                 MOV     R2, #2  
.text:00011054                 MOV     R1, #0  
.text:00011058                 MOV     R0, #0xDF  
.text:0001105C                 LDR     LR, [SP],#arg_4  
.text:00011060                 B       keybd_event  
.text:00011060  
  
  
翻译成 C 代码：  
  
  
#define IOCTL_HAL_COLDBOOT_HTC 0x1012594   
KernelIoControl(IOCTL_HAL_COLDBOOT_HTC, NULL, 0, NULL, 0, NULL);  
keybd_event(VK_OFF, 0, 0, 0);  
keybd_event(VK_OFF, 0, KEYEVENTF_KEYUP, 0);  
  
  
其实后两句改成下面更好些：  
  
#define IOCTL_HAL_REBOOT 0x101003C  
KernelIoControl(IOCTL_HAL_REBOOT, NULL, 0, NULL, 0, NULL);  
  
  
修改过的程序在 Prophet 上验证通过。  
  
乘胜追击，继续分析完全系统电源功能，找来 PowerOffWarning，得出如下：  
  
  
// 关闭 RIL，否则别人打你电话就变成了无信号状态，所谓超级飞行了。  
.text:00011478                 BL      sub_11088   
  
// 完全关闭电源  
.text:0001147C                 MOV     R3, #0x1000000  
.text:00011480                 ORR     R0, R3, #unk_12000  
.text:00011484                 MOV     LR, #0  
.text:00011488                 MOV     R3, #0  
.text:0001148C                 MOV     R2, #0  
.text:00011490                 MOV     R1, #0  
.text:00011494                 STR     LR, [SP,#0x25C+var_258]  
.text:00011498                 STR     LR, [SP,#0x25C+var_25C]  
.text:0001149C                 BL      KernelIoControl  
.text:0001149C  
.text:000114A0                 BL      GwesPowerOffSystem  
  
  
哈哈，今天一大收获，搞定两个问题，“业界”无公开的：）  
  
下载我汉化修改过的仅适合 HTC Prophet（830等） QVGA 的 psShutXP（预计针对其它机型应该没有效果，这些都是私有的代码）：  
  
[下载](/assets/PSShutXP.rar)  
  
修改后的 psShutXP，硬起功能有效。且关机命令不再是关闭屏幕，而是直接关闭电源（但是RIL，即电话模块，没通知运营商正常关闭，也没有通知应用程序保存数据。所以请使用关机命令前保存好数据）  
  
  
顺便体贴个 CeleCommand 中的各式各样的关机、重启、硬起代码：  
  
  
  
#define IOCTL_HAL_REBOOT 0x101003C  
#define IOCTL_HAL_SHUTDOWN 0x1012000  
#define IOCTL_HAL_COLDBOOT 0x1012594  
extern "C" BOOL WINAPI SetCleanRebootFlag();  
extern "C" BOOL WINAPI GwesPowerOffSystem();  
extern "C" BOOL WINAPI ExitWindowsEx(UINT uFlags, DWORD dwReason);  
extern "C" BOOL KernelIoControl(DWORD dwIoControlCode, PVOID pInBuf, DWORD nInBufSize, PVOID pOutBuf, DWORD nOutBufSize, PDWORD pBytesReturned);  
HRESULT SHUT(PCTSTR ptzCmd)  
{  
 BOOL bResult;  
 switch (UChrToUpper(*ptzCmd))  
 {  
 case 'S':  
   // HTC  
   KernelIoControl(IOCTL_HAL_SHUTDOWN, NULL, 0, NULL, 0, NULL);  
  
 case 'G':  
   bResult = GwesPowerOffSystem();  
   break;  
  
 case 'P':  
   bResult = ExitWindowsEx(EWX_POWEROFF, 0);  
   break;  
  
 case 'K':  
   keybd_event(VK_OFF, 0, KEYEVENTF_SILENT, 0);  
   keybd_event(VK_OFF, 0, KEYEVENTF_SILENT | KEYEVENTF_KEYUP, 0);  
   bResult = TRUE;  
   break;  
  
 case 'H':  
   // HTC  
   KernelIoControl(IOCTL_HAL_COLDBOOT, NULL, 0, NULL, 0, NULL);  
  
 case 'C':  
   SetCleanRebootFlag();  
  
 case 'R':  
   bResult = KernelIoControl(IOCTL_HAL_REBOOT, NULL, 0, NULL, 0, NULL);  
   break;  
  
 default:  
   bResult = ExitWindowsEx(EWX_REBOOT, 0);  
   break;  
 }  
  
 return !bResult;  
}  
  
  

