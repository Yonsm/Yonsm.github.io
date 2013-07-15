---
date: 2009-05-03 11:48:31+00:00
layout: post
title: 把 Opera 做成完全绿色免安装版
thread: 460
categories: 文档
tags: 逆向工程
---

发现 Opera 在网页浏览方面还是很有优势的，一直以来都因为这个鸟软件不能绿色安装（特指放在任意目录那种）一直没用。趁着前两天改 Google Maps 的精神，今天又操刀了一下：  
<!-- more -->  
  
零、首先提剪切 Application Data 下面的 Opera （可能是 Opera 9.51 Beta 之类的名称）目录到 Opera 程序文件所在目录，我们的目的是使它能绿色正常运行。  
  
  
一、查找 SHGetSpecialFolderPath(...0x1A...) 这个地方是获取 Application Data路径的。找到后改为：  
  
IDA ARM Code:  
  
  
.text:00569FB4 sub_569FB4                              ; CODE XREF: sub_71B08+24 p  
.text:00569FB4                 STR     LR, [SP,#-4]!  
.text:00569FB8                 LDR     R1, =unk_6448A0  
.text:00569FBC                 MOV     R2, #0x104  
.text:00569FC0                 MOV     R0, #0  
.text:00569FC4                 BL      GetModuleFileNameW  
.text:00569FC8                 MOV     R2, #0  
.text:00569FCC                 LDR     R3, =unk_6448A0  
.text:00569FD0                 ADD     R3, R3, R0,LSL#1  
.text:00569FD4                 STRH    R2, [R3,#-0x16]  
.text:00569FD8                 MOV     R0, #1  
.text:00569FDC                 LDR     R1, =unk_63A32C  
.text:00569FE0                 LDR     R0, =unk_6448A0  
.text:00569FE4                 LDR     LR, [SP],#4  
.text:00569FE8                 B       loc_569F6C  
.text:00569FE8 ; End of function sub_569FB4  
  
下面的VC ARM Code可作参考:  
  
  
; 6    :   TCHAR tzPath[MAX_PATH];  
; 7    :   UINT nLen = GetModuleFileName(NULL, tzPath, MAX_PATH);  
  
 00008  e3a02f41   mov         r2, #0x41, 30  
 0000c  e28d1000   add         r1, sp, #0  
 00010  e3a00000   mov         r0, #0  
 00014  eb000000   bl          GetModuleFileNameW  
  
; 8    :   tzPath[nLen - 11] = 0;  
  
 00018  e28d3000   add         r3, sp, #0  
 0001c  e0833080   add         r3, r3, r0, lsl #1  
 00020  e3a02000   mov         r2, #0  
 00024  e14321b6   strh        r2, [r3, #-0x16]  
  
; 9    :   return 1;  
  
 00028  e3a00001   mov         r0, #1  
  
二、另外，该死的Opera团队，乱七八糟的版本多不说，程序中我竟然还有很多硬编码，Opera的老大还有脸说UCWeb技术没有他们好，靠！Win95 时期菜鸟程序员的垃圾风格。我们还需要把一处 rdata.xxxxxxx 中的 \Application Data 硬编码字符串的引用指向上面的 unk_6448A0。  
  
  
三、经过上面两步，Opera 已经能够运行了，继续完美它。opera.ini 中帮助文件路径改成你所希望的路径。  
  
[User Prefs]  
Default URL=http://www.google.com/  
Home URL=http://www.google.com/  
Help URL=\Application Data\Opera 9.5 Beta\help\en\->\Application Data  改成你的Opera目录  
  
  
四、注册表项目需要导入到注册表中  
  
  
[HKEY_LOCAL_MACHINE\Software\Opera\Info]  
"SplashscreenWgtManPortrait Generic"="\\Storage Card\\Tools\\Opera\\splash_wgtman_225x150.bmp\\"  
"SplashProgressFPS Generic"=dword:0000000a  
"SplashWgtProgressImage Generic"="\\Storage Card\\Tools\\Opera\\line.png"  
"SplashProgressHeight Generic"=dword:00000008  
"SplashscreenPortrait Generic"="\\Storage Card\\Tools\\Opera\\splash_225x150.bmp"  
"SplashProgressImage Generic"="\\Storage Card\\Tools\\Opera\\line.png"  
"SplashscreenWgtManLandscape Generic"="\\Storage Card\\Tools\\Opera\\splash_wgtman_225x150.bmp\\"  
"SplashscreenLandscape Generic"="\\Storage Card\\Tools\\Opera\\splash_225x150.bmp"  
  
五、设置的地址也是硬编码的，需要改过来，否则无法进入设置了：用十六进制编辑器查找：  
  
  
file://localhost/Application Data/Opera 9.5 Beta/Settings/settings.htm  
  
替换成你的实际路径（如果长度不够了，改成文件系统的路径，比如我改成：  
  
  
\Storage Card\Tools\Opera\Opera 9.5 Beta\Settings\settings.htm  
  
六、最后，皮肤选择，如果是QVGA，默认则可。如果是VGA，建议使用 standard_skin_VGA.zip，改名成 standard_skin.zip  
  
还有，opera.ini 中看一下，还需要把缩放参数变一下，具体自己看。VGA和QVGA的缩放参数不一样。  
  
[Adaptive Zoom]  
  
;For VGA  
;Maximum Zoom=190  
;Minimum Zoom=190  
  
Maximum Zoom=100  
Minimum Zoom=70  
  
也可以输入 opera:config 可以进入详细设置（在User Pref下面），自己慢慢体会，可以开启 Turbo 方式，似乎可以翻墙了。  
  
  
好麻烦啊，还不如安装版？以后再弄个CeleSetup的自动脚本就方便了。  
  
OK，完成收工，好麻烦。上面只是给出一个可行的方法。顺便放上 Opera 9.51 Beta IOICN 清凉汉化版的修改版作为成果，支持 PPC5/6 VGA/QVGA，需要的请下载。其中第三、四、五步如果和我不一样的目录，请自己替换。（以后我会整合和 一键安装软件包 中）  
  
  
By Yonsm 2009.05.03 4:29 AM, My LP is sleeping soundly:)  
  
  
[下载](/assets/Opera.zip)  
  
  

