---
date: 2008-12-01 02:13:30+00:00
layout: post
title: 主动打开目标计算机的远程协助
thread: 441
categories: 文档
tags: Win
---

Windows XP/Vista 提供的“远程协助”是通过共享桌面提供远程协助的好方法。但是“远程桌面”必须在目标机器的用户配合的情况下才能做到。实际上，Microsoft Windows 语焉不详的帮助说可以输入目标计算机名称或IP地址来主动访问目标机器。但实际上这是空话——根本就不可以（据说在同一个Domain中才行，但我测试好像也不行）。<!-- more -->  
  
另外，用远程桌面客户端 mstsc 登录目标机器，无法做到共享桌面（即使加上/console参数也只能登录到控制台，而不能共享）。  
  
一般来说，如果目标机器有问题（用户想同时了解如何解决的情况下），叫目标机器上的用户打开远程协助是一个很费劲的事情（菜鸟太多啦！）。经过捉摸，终于找到了方便的方法，主动打开目标机器上的远程协助——用PSEXEC在远程机器的指定用户桌面上执行一个带命令行参数的MSRA程序。  
  
PSEXEC \\SH6 -u Jane -p ****** -i msra.exe /saveasfile D:\Yonsm 123456  
MSRA /openfile \\SH6\D$\Yonsm  
  
询问密码输入后即可自动开启  
  
详细情况如下：  
  
  
E:\Tools\SYSINT>psexec  
  
PsExec v1.94 - Execute processes remotely  
Copyright (C) 2001-2008 Mark Russinovich  
Sysinternals - www.sysinternals.com  
  
PsExec executes a program on a remote system, where remotely executed console  
applications execute interactively.  
  
Usage: psexec [\\computer[,computer2[,...] | @file][-u user [-p psswd]][-n s][-l  
][-s|-e][-x][-i [session]][-c [-f|-v]][-w directory][-d][-][-a n,n,...  
] cmd [arguments]  
    -a         Separate processors on which the application can run with  
               commas where 1 is the lowest numbered CPU. For example,  
               to run the application on CPU 2 and CPU 4, enter:  
               "-a 2,4"  
    -c         Copy the specified program to the remote system for  
               execution. If you omit this option the application  
               must be in the system path on the remote system.  
    -d         Don't wait for process to terminate (non-interactive).  
    -e         Does not load the specified account's profile.  
    -f         Copy the specified program even if the file already  
               exists on the remote system.  
    -i         Run the program so that it interacts with the desktop of the  
               specified session on the remote system. If no session is  
               specified the process runs in the console session.  
    -l         Run process as limited user (strips the Administrators group  
               and allows only privileges assigned to the Users group).  
               On Windows Vista the process runs with Low Integrity.  
    -n         Specifies timeout in seconds connecting to remote computers.  
    -p         Specifies optional password for user name. If you omit this  
               you will be prompted to enter a hidden password.  
    -s         Run the remote process in the System account.  
    -u         Specifies optional user name for login to remote  
               computer.  
    -v         Copy the specified file only if it has a higher version number  
               or is newer on than the one on the remote system.  
    -w         Set the working directory of the process (relative to  
               remote computer).  
    -x         Display the UI on the Winlogon secure desktop (local system  
               only).  
    -priority  Specifies -low, -belownormal, -abovenormal, -high or  
               -realtime to run the process at a different priority. Use  
               -background to run at low memory and I/O priority on Vista.  
    computer   Direct PsExec to run the application on the remote  
               computer or computers specified. If you omit the computer  
               name PsExec runs the application on the local system,  
               and if you specify a wildcard (\\*), PsExec runs the  
               command on all computers in the current domain.  
    @file      PsExec will execute the command on each of the computers listed  
               in the file.  
    program    Name of application to execute.  
    arguments  Arguments to pass (note that file paths must be  
               absolute paths on the target system).  
  
You can enclose applications that have spaces in their name with  
quotation marks e.g. psexec \\marklap "c:\long name app.exe".  
Input is only passed to the remote system when you press the enter  
key, and typing Ctrl-C terminates the remote process.  
  
If you omit a user name the process will run in the context of your  
account on the remote system, but will not have access to network  
resources (because it is impersonating). Specify a valid user name  
in the Domain\User syntax if the remote process requires access  
to network resources or to run in a different account. Note that  
the password is transmitted in clear text to the remote system.  
  
Error codes returned by PsExec are specific to the applications you  
execute, not PsExec.  
  
  
E:\Tools\SYSINT>psexec \\SH -u Jane -p ****** -i msra.exe /saveasfile D:\Y  
onsm 123456  
  
PsExec v1.94 - Execute processes remotely  
Copyright (C) 2001-2008 Mark Russinovich  
Sysinternals - www.sysinternals.com  
……
