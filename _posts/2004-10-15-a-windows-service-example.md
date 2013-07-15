---
date: 2004-10-15 03:07:04+00:00
layout: post
title: 一个 Windows 服务例子
thread: 144
categories: 代码
---

一个 Windows 服务小例子，也是一个很好的模板。支持远程安装和删除，支持自动选择线程语言（中文或英文）。

  


下载附件：[BeepSrv](/assets/1097751870.rar)

<!-- more -->  
  

    
    Microsoft Windows [版本 5.2.3790]<br></br> (C) 版权所有 1985-2003 Microsoft Corp.<br></br> <br></br> F:>BeepSrv<br></br> BeepService 版本 1.0.0<br></br> CopyLeft(L) 2003 Yonsm，不保留任何权利。<br></br> <br></br> 用法: BeepSrv <命令> [机器] [用户] [密码]<br></br> <br></br> 命令: 指定操作命令，可以接受 Install 或者 Remove 命令。<br></br> 机器: 指定要操作的计算机名，默认操作本地计算机。<br></br> 用户: 指定访问目标机器所使用的用户名，默认使用当前用户。<br></br> 密码: 指定要使用的密码，默认使用当前密码。<br></br> <br></br> F:>BeepSrv Install 192.168.0.1<br></br> BeepService 版本 1.0.0<br></br> CopyLeft(L) 2003 Yonsm，不保留任何权利。<br></br> <br></br> 连接到 192.168.0.1IPC$: 操作成功完成。<br></br> 打开服务管理器: 操作成功完成。<br></br> 打开 BeepSrv 服务: 指定的服务未安装。<br></br> 复制文件到 192.168.0.1ADMIN$System32BeepSrv.exe: 操作成功完成。<br></br> 创建 BeepSrv 服务: 操作成功完成。<br></br> 启动 BeepSrv 服务: 操作成功完成。<br></br> 断开 192.168.0.1IPC$ 连接: 操作成功完成。<br></br> <br></br> F:>BeepSrv Remove Yonsm<br></br> BeepService 版本 1.0.0<br></br> CopyLeft(L) 2003 Yonsm，不保留任何权利。<br></br> <br></br> 连接到 YonsmIPC$: 操作成功完成。<br></br> 打开服务管理器: 操作成功完成。<br></br> 打开 BeepSrv 服务: 操作成功完成。<br></br> 查询 BeepSrv 服务状态: 正在运行。<br></br> 停止 BeepSrv 服务: 操作成功完成。<br></br> 删除 BeepSrv 服务: 操作成功完成。<br></br> 删除文件 YonsmADMIN$System32BeepSrv.exe: 操作成功完成。<br></br> 断开 YonsmIPC$ 连接: 操作成功完成。<br></br> <br></br> F:>_<br></br> <br></br> 

  
yi
