---
date: 2004-10-28 02:41:16+00:00
layout: post
title: TeleControl - 10Moons 电视大师遥控器增强工具
thread: 131
categories: 软件
tags: 折腾 分享
---

  
为自己使用而写的电视遥控器增强工具，有 10Moons TV Master 或 10Moons TV Master FM 的人可以试试看。我自己觉得非常非常方便……

  


下载: [TeleControl 2.6.600 (包含源代码)](/assets/1098873491.rar)

  


一、简介

  


   TeleControl 是基于 10Moons TV Master 的遥控器增强工具。它能帮助你充分利用每个遥控器按键，让你全程遥控计算机。

  


  
二、优点

  


   1. 系统资源占用非常非常少，大概消耗 7M 内存，CPU 占用几乎总是 0%。

  


   2. 兼容 10Moons TV Master，不影响原来的功能和使用习惯，只是在不看电视的时候增加了按键功能，充分利用按键。

  


   3. 支持 DScaler、Fly2000TV 和 Windows Media Player。

  


   4. 纯 Win32SDK/C 源代码开发，方便用户自行修改。

<!-- more -->  


  
三、使用说明

  


   1. 打开 10Moons TV Master 应用程序之后，TeleControl 自动失效，所有的按键归 10Moons TV Master 应用程序所有。10Moons TV Master 应用程序关闭之后，TeleControl 自动生效。

  


   2. 如果 DScaler、Fly2000TV 或 Windows Media Player 应用程序正在运行，且处于最前端，则所有的按键归操作将针对 DScaler、Fly2000TV 或 Windows Media Player 窗口。

  


   3. 其它情况下，按键功能定义如下：

  


       Power:          打开当前目录下的电视程序。  
       Mute:           定时关机。关机前 60 秒将会出现提示对话框，此时可以取消关机。

  


       Video Setting:  模拟 Shift 键。  
       Snapshot:       模拟 Win+D 键。  
       Freeze:         模拟 Alt+F4 键。  
       Video Default:  模拟 Ctrl 键。  
       Hide Panel:     模拟 Alt 键。

  


       CH+:            模拟 ↑ 键。  
       CH-:            模拟 ↓ 键。  
       VOL-:           模拟 <- 键。  
       VOL+:           模拟 -> 键。

  


       REC:            模拟 Enter 键。

  


       Full Screen:    模拟 Alt+Enter 键。  
       AV Source:      模拟 Alt+Tab 键。  
       <:              模拟 F6 键。  
       >:              模拟 Tab 键。

  


       12346789:       分别模拟个方向上的鼠标移动，单位为 10 像素。  
       5:              模拟 Win 键。  
       -/--:           模拟左击。  
       0:              模拟右击。

  


       Recall:         模拟 Escape 键。

  


   4. 在 TeleControl 生效状态下，如果有按键按下，系统托盘图标由蓝色变成黄色。

  


  
四、安装及卸载

  


   1. 请先确认已安装 10Moons TV Master 的驱动程序。

  


   2. 将 TeleControl 安装在 10Moons TV Master 应用程序同一目录下，替换原来的 SystemTray.exe 或 TVTray.exe。

  


   3. 如果是 DScaler 或 Fly2000TV 用户，请安装在 DScaler 或 Fly2000TV 目录下。

  


   4. TeleControl 是"绿色软件"，除了程序文件之外，不会在系统中保存任何信息。如果要卸载，直接删除程序文件即可。

  


  
五、其它信息

  


   1. 写这个程序目的是为了自己方便遥控计算机，所以没有提供配置界面什么的。每个按键的功能都是固定的，所以可能不适合普通用户使用。源代码是开放的，不保留版权，用 Visual Studio .NET 2003 可以编译修改，以符合自己的使用习惯。

  


   2. 使用 TeleControl 纯属你自己的选择，作者不对使用过程中产生的任何问题法律负责，如果你不同意此项，请不要使用 TeleControl。

  


   3. 如果你有意见、建议，或者在使用过程中碰到问题，请描述详细信息并 Email 至 [Yonsm@163.com](mailto:Yonsm@163.com)。

    
Powered by Yonsm  
2004.9.4  


  

