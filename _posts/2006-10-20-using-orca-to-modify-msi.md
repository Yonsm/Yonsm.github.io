---
date: 2006-10-20 06:11:55+00:00
layout: post
title: Orca - 修改 MSI 文件的好工具 - 终于搞定在 Win2003 上安装 WinCE5 PB
thread: 266
categories: 资源
---

很久以前就辛辛苦苦从电驴上下载来 Microsoft Windows CE 5.0 （开发包，特指 Platform Builder for Microsoft Windows CE 5.0），一安装提示只能在 WinXP SP1 以上或 Win2000 SP4 以上安装，我一直用 Win2003，真郁闷，每次要提取文件，只好用其他方法来找，找到后解除来看。  
  
因为是 MSI 的安装包，一直想分析一下在那里判断版本的，为此不仅调试分析过，还写过一个 FakeVer DLL，专门用来欺骗版本号，竟然都没成功，晕死！  
  
今天突然想到，以前都是针对 MSI 的执行程序 msiexec.exe 分析，干嘛不从 MSI 安装文件入手试试看呢？于是找啊找啊，终于尝试了一个叫 Orca 的工具，打开 MSI 文件后，根据错误提示字符串，找到相关的条件判断，删除掉，顺利安装——终于用上了 Win CE 5 PB！感谢 CCTV，感谢 MTV……  
  
其实真正要感谢的是 MS，Orca 是 MS 的工具。另外要感谢 wanfu，我用的是 wanfu 汉化的 3.1.4000.1830，可从这里下载：http://www.hanzify.org/index.php?Go=Show::List&ID;=11122  

