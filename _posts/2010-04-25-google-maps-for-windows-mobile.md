---
date: 2010-04-25 02:13:33+00:00
layout: post
title: Google Maps 4.1 绿色版 - 非常实用的地图软件
thread: 459
categories: 资源
tags: 逆向工程 分享
---

Google Maps Mobile 是目前为止我发现的最实用的手机软件，在手机上查看 Google 地图、卫星图、生活信息（餐馆等）、交通状况（仅北京上海等城市）、GPS定位、公交驾车导航、纵横（好友定位）、Buzz（墙外开花墙内没香，暂时不能用）、语音搜索等……  
  
关键一点是，如果没有GPS，一样可以非常方便地使用这个软件，它会读取你的移动电话所使用的基站（就是移动电话发射塔）的位置信息，做到一个粗略的定位——城市精确度800-1500米左右，乡村可能更差点，依赖于基站的密集程度——这个精确度水然比较低，但已经非常有用了：一打开软件就会帮你找到你所在的位置的周边地图，非常的实用。另外“谷歌纵横”功能可以帮助我们随时得知好友的位置信息。感谢 Google 提供这么棒的软件！  
  
Google Maps 支持多种手机（智能手机都支持，非智能手机也支持部分），具体可以到此 http://mobile.google.com 查询下载。  
  
对于 Windows Mobile，目前最新版本是 4.1，SP 和 PPC 是通用的。但郁闷的一点是，程序的缓存数据一定会保存在 Applicaion Data 中（且程序字符串也必须在这个目录下）。为了解决这个问题，我耐心分析后修改了一个“当前目录”的版本，所有的数据都保存在当前EXE所在的GoogleMaps目录下，做成绿色版本了（高难度动作：）。<!-- more -->  
  
有需要可以从一键安装GPS软件包中获取此软件修改版（如果只需要谷歌地图，只提取其中的GMAP目录即可）  
  
[![](/assets/1241094363_6214a0c3.gif)](/assets/1241094363_6214a0c3.gif)  
  
[下载](/assets/PPCGPS.zip)  
  
  
另外，下面是修改方法：  
  
1. 找到 SHGetSpecialFolderPath 函数，参数是...0x1A... 的就是 Application Data 的目录。  
  
2. 我们要修改为以下代码：  
  
UINT nLen = GetModuleFileName(NULL, tzPath, MAX_PATH);  
tzPath[nLen - 15] = 0;  
  
3. 换成汇编代码为：  
.text::00019E8C                 MOV     R2, #0x104  
.text:00019E90                 ADD     R1, SP, #0x458+var_42C  
.text:00019E94                 MOV     R0, #0  
.text:00019E98                 BL      GetModuleFileNameW  
.text:00019E9C                 ADD     R3, SP, #0x458+var_42C  
.text:00019EA0                 ADD     R3, R3, R0,LSL#1  
.text:00019EA4                 MOV     R2, #0  
.text:00019EA8                 STRH    R2, [R3,#-0x1E]  
.text:00019EAC                 B       loc_19ED4  
  
  
查找（可能不准确）：  
  
02 00 A0 E1  
1A 20 A0 E3 00 30 A0 E3 2C 10 8D E2 F1 E3 05 EB  
BC 32 DD E1 5C 00 53 E3 09 00 00 0A BC 01 9F E5  
  
改成（其中7E E3 05 EB必须更改为GetModuleFIileW的调用）：  
41 2F A0 E3  
2C 10 8D E2 00 00 A0 E3 7E E3 05 EB 2C 30 8D E2  
80 30 83 E0 00 20 A0 E3 BE 21 43 E1 08 00 00 EA  
  
  
  
4. 因为还会加上 \Storage Card，所以必须去掉此功能。往下看，转到本来就有的GetModuleFileNameW下面：  
.text:00019F70                 MOV     R6, #0  
.text:00019F74                 CMP     R7, #0  
.text:00019F78                 BLE       loc_1A01C  
改为：  
.text:00019F70                 MOV     R6, #0  
.text:00019F74                 CMP     R7, #0  
.text:00019F78                 B       loc_1A01C  
  
  
查找（可能不准确）：  
0B 0C 00 EB 00 60 A0 E3  00 00 57 E3 27 00 00 DA  
把 DA 改成 EA 即可  
  
  


  
2009.8.15  更新到3.2  
2009.9.15  更新到3.2.1.12  
2009.11.13  更新到3.2.1.35  
2009.12.09  更新到3.3.1  
2010.2.18  更新到4.0.0  
2010.4.24  更新到4.1.0  
  

