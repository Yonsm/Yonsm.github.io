---
date: 2007-09-03 05:51:29+00:00
layout: post
title: '修改 CorePlayer 配置保存路径'
thread: 362
categories: 文档
tags: WM 逆向工程
---

1. 首先 UPX Unpack Coplayer 的主程序。  
  
2. 用 IDA 反汇编。  
  
3. 首先 Application Data 是 CLSID_APPDATA 目录 ID，一般是 ShGetSpecialLocationPath 获取的。首先看有没有导入这个函数，看 Import View，没有，失望。  
  
4. 还是按上一步的思路，查 SDK 知道 CLSID_APPDATA 这个值是 0x10。在 IDA 中查找这个立即数。定位到：<!-- more -->  
  
  
.text:00053750                 MOV     R2, #0x1A  
  
  
  可以知道 CorePlayer 配置文件目录就是在这附近得到和创建的。另外，可以通过 CreateDirectory 来定位关键代码的位置，根据 Import 找到这里：  
  
  
.text:00053748                 MOV     R4, R3  
.text:0005374C                 MOV     R3, #1  
.text:00053750                 MOV     R2, #0x1A 》》看这里，立即数  
  
……  
  
.text:00053768 loc_53768                               ; CODE XREF: sub_536F8+4C j  
.text:00053768                 CMP     R2, #0  》》比较是有 Application Data 目录  
.text:0005376C                 BNE     loc_537B4  》》根据后面的分析，这里是关键转跳！！  
.text:0005376C  
.text:00053770 ; ---------------------------------------------------------------------------  
  
……  
  
.text:00053780  
.text:00053784                 MOV     R1, #0          ; lpSecurityAttributes  
.text:00053788                 ADD     R0, SP, #4      ; lpPathName  
.text:0005378C                 BL      CreateDirectoryW  》》有 Application Data 目录则创建它下面的 CorePlayer 子目录  
  
……  
  
.text:000537B0                 LDMFD   SP!, {R4-R8,PC}  
.text:000537B0  
.text:000537B4 ; ---------------------------------------------------------------------------  
.text:000537B4  
.text:000537B4 loc_537B4                               ; CODE XREF: sub_536F8+74 j  》》没有 Application Data 目录则转跳到这里  
.text:000537B4                 MOV     R0, #0  
.text:000537B8                 BL      sub_140C0  
.text:000537B8  
.text:000537BC                 MOV     R2, R6          ; nSize  
.text:000537C0                 MOV     R1, R5          ; lpFilename  
.text:000537C4                 BL      GetModuleFileNameW  》》一看，哈哈，没有 Application Data 则使用 EXE 文件所在的目录，所以，只要把上面的判断强行的转跳强行到这里就 OK 了  
  
……  
  
.text:000537F8                 LDMFD   SP!, {R4-R8,PC}  
.text:000537F8  
.text:000537F8 ; End of function sub_536F8  
  
  
5. 根据上面的分析，只要把 .text:0005376C                 BNE     loc_537B4 改成 B     loc_537B4 就好  
了  
  
6. 转到 HEX View 把 上面指令附近的 Hex 值复制，用 UltraEdit 打开 EXE，查找这 HEX，定位到这里。吧指令改一下就 OK 了。顺便说一句，B 转调的指令操作码是 0xEA，也就是说：  
  
结论：  
  
搜索：04 F0 A0 E1 B4 20 DD E1  00 00 52 E3 10 00 00 0A  
改成：04 F0 A0 E1 B4 20 DD E1  00 00 52 E3 10 00 00 EA  
  
改一个字节即可。  

