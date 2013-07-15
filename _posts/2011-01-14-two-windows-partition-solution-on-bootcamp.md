---
date: 2011-01-14 09:27:07+00:00
layout: post
title: BootCamp 分两个 Windows 分区的完美方案
thread: 529
categories: 文档
tags: Mac 折腾
---

一个 Windows 分区的文件管理方式非常别扭，主要是长久以来习惯了数据和程序分开的使用方式。这也要怪 Windows 这种不稳定的系统──在Windows下用不了多久就感觉系统程序和数据放在一起有点心虚，在 Mac 下一个分区使用到现在从没想过要重装系统之类的……  
  
Boot Camp 助理仅支持一个 Windows 分区。网上找着方案，说得神乎奇乎，貌似都要删除那个200M的或者其他超复杂、超难度的不完美方案。我试着搞了一下，嘿，竟然很简单就搞定了一个很完美的方案：<!-- more -->  
  
1. Mac 下用 Boot Camp 助理分出一个 Windows 分区（容量为之后期待的两个 Windows 分区的总大小）。  
  
2. 用 Mac OS X 光盘启动，使用磁盘工具，把刚才的 Windows 分区抹掉，搞成 Mac OS X 扩展日志分区格式（为了能进行步骤3）。  
  
3. 在磁盘工具中选定磁盘（而不是分区），点击右侧的“分区”页面，然后点击刚才抹掉的 Windows 分区，点击 + 号，变成两个分区。注意调整好你需要的大小。（比如第一个分区 40G，第二个分区200G） 经过步骤三，会有两个Mac OS X扩展日志分区。  
  
4.在磁盘工具中，把上面所说ode两个分区抹掉，成为 exFAT 格式。  
  
5. 重新启动，按住 Option 键，出现系统启动选择界面的时候，按F12或者弹出光盘键推出 Mac OSX 光盘，再放入 Windows 7 光盘（注意 GUID 文件系统，XP可能不能认，现在还想在 Mac 上安装 XP + IE6 的人，下回还投胎到中国吧）。  
  
6. Windows 7 安装的过程中，记得把刚才的两个 exFAT 分区格式化成 NTFS 分区（当然，你也可以用多个NTFS分区+FAT分区）。（同6，现在还不用NTFS来装 Windows 的人，也……那个吧）  
  
(实际上不建议用光盘安装系统，超级慢，妈的。建议用小型 PE （如我的 REBOOT 光盘）启动，然后用 GIMAGEX 之类的，把移动硬盘上的 Win7光盘中的 sources\install.wim 直接释放到C:\上去安装，速度快非常多。（这点技巧不仅适用与iMac上安装Windows，所有PC均如此）。  
  
7. 顺利安装完成。赶紧放入 OS X 光盘到 Windows 中安装 Boot Camp 吧（然后到Apple升级到 Boot Camp 3.2）  
  
(iMac 如果是 ATI 的显卡，安装 Windows 7的时候，第一次重新启动后会黑屏。解决方法是用 PE 光盘或者  Windows 7 光盘启动进入命令行提示符模式，把 ATI 的垃圾驱动删除掉（C:\Windows\System32\Drivers\ati***.sys），重启继续即可。  
)  
  
  
我打字真厉害啊，瞬间一片文章跃然屏上……
