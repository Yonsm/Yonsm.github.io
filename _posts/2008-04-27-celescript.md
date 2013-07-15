---
date: 2008-04-27 06:24:44+00:00
layout: post
title: CeleScript - 方便实用、居家旅行、莫名其妙的批处理脚本解释引擎
thread: 413
categories: 软件
tags: Win 分享
---

CeleScript 是一个从 PE 的 XCMD 和为 Windows Mobile 上的 CeleCmd 演变而来的一个东西，我自己用了很久了，语法比较莫名其妙，但用起来比较方便实用。主要用来做一些安装软件、系统设置等自动化操作。基本上的代码都是以前为 Windows Mobile 写的 CeleCmd 转换而来，没有花太多精力，基本上属副产品：）  
  
<!-- more -->  
  
下载：[CeleScript 3.0.820](/assets/CeleScript.3.0.820.zip)   
  
2009.1.11 更新  
PC 上的一键安装工具包：  
工具包（常用工具）：http://yonsm.net/up/CeleTools.exe   
扩展工具包（调试分析工具）：http://yonsm.net/up/CeleTools+.exe  
软件包（普通用户通用工具）：http://yonsm.net/up/CeleUtilities.exe   
  
  


* * *

  
  
CeleScript 使用说明  
注意：此帮助文件未经仔细校对，可能有部分命令解释有误。若有谬错之处，敬请指正。  
  
[简介] [特点] [安装] [使用] [菜单] [命令] [问答] [许可] [致谢]  
  
一、简介  
欢迎使用功能强大、灵活方便的 CeleScript 命令解释引擎。您只要编写简单的 CeleScript 命令文件，就能在 Windows 中实现灵活强大的批处理功能。  
[目录]  
  
二、特点  
性能高效：命令解释引擎精巧构思，短小精干，运行迅速。  
　   
功能强大：内置支持多种命令，使用这些命令可以编写出功能强大的批处理脚本。  
　   
扩展支持：支持调用外部 EXE 和 DLL 函数。  
　   
使用灵活：支持格式统一的命令行参数和命令文件，可以在命令行、命令文件和程序界面中，调用 CeleScript 的各种功能。  
　   
其它功能：支持导入标准的和扩展的 Windows 注册表脚本脚本。  
　   
方便调试：在程序界面中执行命令或命令文件，可以在日志窗口中跟踪脚本执行的流程和结果，方面发现命令脚本的问题。  
　   
广泛支持：一个可执行文件，同时支持 Windows 2000/XP/2003/Vista，并且适用于 Windows XPE 中作为登录解释脚本引擎。  
　   
源码公开：源代码公开，方便更改定制和功能增强，且在源代码中增加扩展命令支持非常容易。   
[目录]  
  
三、安装  
安装：绿色软件，直接运行 CeleScript.exe 即可使用。如果要关联 .csc 命令文件，可以在在程序中双击 CeleScript 的图标。  
　   
卸载：CeleScript 是“绿色”软件，删除 CeleScript.exe 即可卸载。如果选择了关联 .csc 命令文件，请在程序中再次双击 CeleScript 的图标取消文件关联。   
[目录]  
  
四、使用  
使用方式  
　  
直接执行本程序，将显示允许输入命令和现实执行结果的对话框，您可以直接在程序界面上执行各种操作。  
　   
在命令行参数中使用，例如，要创建快捷方式，执行“CeleScript.exe LINK %M\程序\测试程序.lnk,%W\Test.exe”即可。  
　   
在命令文件中使用，例如，“CeleScript.exe LOAD C:\Test\*.csc”。  
　   
如果省略命令关键字，将自动判断参数，且支持通配符和子目录递归查找匹配文件（前导“!”）。如 CeleScript.exe %C\*.csc。CeleScript 将按以下规则解析执行：  
  
  
.inf：安装 INF 文件。   
.csc、.reg：执行 CeleScript 的 LOAD 命令。   
.dll、.ocx、.ax：执行 CeleScript 的 CDLL 命令。   
.exe、.com、bat、cmd：运行可执行文件和批处理文件。   
  
  
命令格式  
  
  
CeleScript 的命令是一行字符串，以大写的四字符关键字开始，紧跟着的是空格或制表符，后面是命令的参数。  
　   
参数之间用逗号“,”分隔，如果在参数中要使用逗号本身，则需要使用“%,”的转义字符。  
　   
不同的命令的参数格式不一致，详细请参考 命令。  
　   
变量与宏  
  
CeleScript 读取一条个命令文件后，首先展开其中用“%”号前导的宏：  
　  
E    当前脚本的完整路径   
C    当前脚本的目录   
T    当前时间   
D    当前日期   
X    最后一条命令的返回值，十六进制格式，如 0XFFFFFFFF   
x    最后一条命令的返回值，十进制格式，如 -1   
0-9  用户变量值，用户可以通过 EVAL 命令设置变量 0 到 9 的内容   
A    可能是 \Application Data   
Y    可能是 \My Documents   
S    可能是 \Windows\Startup   
W    可能是 \Windows   
P    可能是 \Windows\“开始”菜单\程序   
M    可能是 \Windows\“开始”菜单   
F    可能是 \Program Files   
O    可能是 [User Name]\SendTo   
R    回车字符   
N    换行字符   
#    十六进制字符，后面紧跟这四个十六进制字符，如“%#FEFF”   
%    由于“%”用于宏转义，如果需要在参数中确实需要使用“%”本身，则需要用两个“%”代替，如“%1”要写成“%%1”。   
,    CeleScript 把“,”作为参数分隔符，与“%”类似，如果在参数中需要使用“,”本身，则需要使用“%,”的形式。  
　   
命令文件  
  
CeleScript 的命令文件是由 CeleScript 命令组成的命令集合。  
　  
每条命令单独一行。   
命令文件中可以使用注释，注释必须单独一行，以“;”作为注释行开始。   
命令文件支持 UNICODE 格式和 ASCII 格式，为了更高的执行效率，推荐使用 UNICODE 格式。   
命令文件中可以杂合 Windows Registry Script 内容，CeleScript 会把 Registry Script 导入到注册表。但是使用这种方式必须十分小心，因为执行过程中，Registry Script 部分会被修改（仅在内存中），可能导致 CALL 和 GOTO 无法正常使用（使用原则：最新会被执行到的 Registry Script 放在文件最后的子过程中，这样就能避免问题）。   
[目录]  
  
五、界面  
执行：执行命令。  
　   
关于：显示程序版本、版权和作者信息。  
　   
退出：退出 CeleScript 程序。  
　   
清除日志：单击 CeleScript 图标。  
　   
文件关联：双击 CeleScript 图标。   
[目录]  
  
六、命令  
[LOAD] [BATC] [IFEX] [ELSE] [CALL] [GOTO] [PROC] [ENDP] [PLAY] [BEEP] [MSGX] [DLGX] [LINK] [FILE] [REGX] [ENVI] [SEND] [WAIT] [KILL] [SHUT] [EXEC] [CDLL] [EVAL] [ASOC] [CCUI]  
  
具体使用方法请参看附件中的 Resource\CeleScript.htm，或者在 CeleScript 中点击标题栏右上角的问号按钮  
  
七、问答  
在 XPE 中，如何使用 CeleScript 作为登录解释引擎？  
  
我也不知道。   
[目录]  
  
八、许可  
本程序及其源代码是可以免费获取的。  
　   
如果您使用或修改了其中任何的源代码，则必须把使用这些源代码的项目以及项目内的所有源代码和文档公开。否则禁止使用本程序源代码的任何部分。  
　   
您可以复制、分发和传播无限制数量的软件产品，但您必须保证每一份复制、分发和传播都必须是完整和真实的，包括所有有关本软件产品的软件、电子文档，版权和商标宣言。  
　   
作者特此申明对本软件产品之使用不提供任何保证，不对任何用户保证本软件产品的适用性，不保证无故障产生；亦不对任何用户使用此软件所遭遇到的任何理论上的或
