---
date: 2007-03-28 00:39:02+00:00
layout: post
title: 定制 Windows Mobile ROM 中的 Default.hv 注册表文件
thread: 299
categories: 文档
tags: WM 折腾 固件
---

定制ROM相信很多人多做过了，编辑其中的注册表是一件很麻烦的事。经过一番摸索，终于找到了一条比较舒服的捷径，简述如下：  
  
**一、使用 RGUComp 导出 hv 为 rgu**  
  
  
ECHO Windows Registry Editor Version 5.00>default.reg  
RGUComp.exe -o default.hv -nologo>>default.reg  
  
  
用UltraEdit把.reg文件转换成 Uncode DOS 格式，这是必需的 RGU 的 U 就是这个意思吧。  
  
这里 RGUComp.exe 一定要用我修改过的版本，有两个原因：  
  
1.支持中文（这点似乎是wh_cxh修改的）；  
2.将multi_sz字符串导出为“hex(7):”和“hex(15):”这种格式，而不是“multi_sz:”和“mui_sz:”这种格式。这样才能在后面用Registry Workshop等软件来编辑。  
  
  
**二、使用 UltraEdit 宏功能为 .reg 文件按项排序**  
  
要排序是因为Registry Workshop似乎处理未排序且有重复项的.reg文件时有问题，排序仅对[]中项的行进行。<!-- more -->  
  
妙用 UltraEdit 实现 .reg/.rgu 文件排序，类似的方法可以应用到别的地方。下面的Macro代码有点精妙，有心人不妨看看。下面是 UltraEdit 的宏代码，说实话这种宏命令集真不是人看的：）  
  
  
  
InsertMode  
ColumnModeOff  
HexOff  
UnixReOff  
Find "Windows Registry Editor Version 5.00^p"  
Replace All " Windows Registry Editor Version 5.00^p"  
Find "]^p"  
Replace All " YonsmEND^p"  
Find "^p"  
Replace All "^pYonsmBEGIN"  
Find "^pYonsmBEGIN[HK"  
Replace All "^p[HK"  
Find "^pYonsmBEGIN"  
Replace All "YonsmBEGIN"  
SortAsc IgnoreCase 1 -1 0 0 0 0 0 0  
Find "YonsmBEGIN"  
Replace All "^p"  
Find " YonsmEND^p"  
Replace All "]^p"  
Find " Windows Registry Editor Version 5.00^p"  
Replace All "Windows Registry Editor Version 5.00^p"  
Top  
  
附件中已包含这个Macro的文件，SortReg.mac。  
  
注意，如果有的行实在太长（实际发现就两个项，就是又长又臭的 .NET CF 的注册表项），UltraEdit 的 ^p 参数替换就出错。所以，这种情况下，把太长的行现 Ctrl+X 掉，处理好后再手动找到合适的地方 Ctrl+V。  
  
  
**三、使用 RegistryWorkshop 编辑 default.reg 文件**  
  
前面的准备工作都是为了这里能好好的编辑。只要能用上这个软件，.reg的编辑那是非常方便的，比较等等都行。没话说了，看附件中下载。  
  
**四、重构注册表文件 default.hv**  
  
把 .reg 的 Magic 标志（Windows Registry Editor Version 5.00）改成 REGEDIT4（RGUComp才能认识，本来这个地方我想hack的，没找到地方）。  
  
  
  
set _FLATRELEASEDIR=.  
COPY default.reg boot.rgu  
rgucomp.exe -b  
del boot.rgu  
move /Y boot.hv Default.New.hv  
pause  
  
  
附件中的 CoXCo 是解码 InitFlashFiles.dat 的小工具，具体看这里：http://bbs.pdafans.com/viewthread.php?tid=342677&pid;=353144  
  
[下载](/assets/1174991588_0.rar)  

