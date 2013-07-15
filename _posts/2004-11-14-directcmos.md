---
date: 2004-11-14 06:39:56+00:00
layout: post
title: DirectCMOS
thread: 113
categories: 代码
---

下载: [DirectCMOS](/assets/1100356483.rar) (895 字节)

一百年前用 Debug 写的 DOS 小工具，保存 CMOS Data 到可执行文件中,或从可执行文件中把数据写入到 CMOS。当初写的目的是用于机房（或网吧）批量更改 CMOS：）

老古董了，不小心看见了，回味一下，权当保存纪念……

<!-- more -->

A  
MOV     SI,0082  
CMP     BY [SI],52    ;'R'  
JZ        0120            ;_Read  
CMP     BY [SI],72         ;'r'  
JZ        0120            ;_Read  
CMP     BY [SI],57         ;'W'  
JZ        0154            ;_Write  
CMP     BY [SI],77         ;'w'  
JZ        0154            ;_Write  
MOV     AH,09  
MOV     DX,017B  
INT      21  
INT      20  
MOV     SI,01D0         ;_Read:  
MOV     CX,0040  
XOR      AL,AL  
OUT     70,AL            ;_LoopRead:  
MOV     AH,AL  
IN        AL,71  
MOV     [SI],AL  
MOV     AL,AH  
INC      AL  
INC      SI  
LOOP   0128            ;_LoopRead  
MOV     AX,3D01  
MOV     DX,0174         ;'DC.COM'  
INT      21  
MOV     BX,AX  
MOV     AH,40  
MOV     CX,0110  
MOV     DX,0100  
INT       21  
MOV     AH,09  
MOV     DX,0194  
INT       21  
INT       20  
MOV     SI,01D0         ;_Write:  
MOV     CX,0040  
XOR     AL,AL  
OUT     70,AL           ;_LoopWrite:  
MOV     AH,AL  
MOV     AL,[SI]  
OUT     71,AL  
MOV     AL,AH  
INC      AL  
INC      SI  
LOOP    015C            ;_LoopWrite  
MOV     AH,09  
MOV     DX,01AB  
INT      21  
INT     20  
DB      'DC.COM',0  
DB      'Message:Unknow argument!$'  
DB      'Message:Read Complete!$'  
DB      'Message:Write Complete!$'  
DB      0,0,0,0,0,0,0,0,0,0,0,0,0  
DB      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0  
DB      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0  
DB      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0  
DB      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

RCX  
110  
N DC.COM  
W  
Q  
 
