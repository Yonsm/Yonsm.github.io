---
date: 2008-04-13 18:31:07+00:00
layout: post
title: 在 ASUS A8Sc 中安装 Mac OSX Leopard 10.5.2
thread: 411
categories: 文档
tags: Mac
---

突发奇想想在我的 A8Sc 笔记本上装个 Mac OSX Leopard 玩玩。本来以为是很简单的事情，在MM面前夸口说没有做不到滴，还叫她一起看安装进度，结果竟然装不上，RP差点崩溃了：)  
  
回来后一番琢磨，终于搞定了。基本上做到了完美的状态，除了无线网卡和读卡器不能工作之外（网卡可以工作，无线网络可用可不用）。  
  
前期绕了很多弯路，现在想想其实不复杂----关键是需要刷特定的 BIOS。如果你也有兴趣，不妨看看我的安装步骤：）<!-- more -->  
**  
一、准备  
**  
**1. 刷 BIOS：  
**  
看帖子，在帖子中找找你的笔记本的BIOS，Kalyl 的修改版，看看有没有，没有的话可以请求他做个最新版本的修改：  
  
[http://forum.insanelymac.com/index.php?showtopic=90505&st=20](http://forum.insanelymac.com/index.php?showtopic=90505&st=20)  
  
对于 ASUS A8Sc，BIOS 下载地址是：  
[http://rapidshare.com/files/96376069/A8SEAS.301_mod.zip.html](http://rapidshare.com/files/96376069/A8SEAS.301_mod.zip.html)  
  
**2. 下载Mac OSX Leopard 10.5.2 安装盘，用Kalyway的版本：**  
  
[http://thepiratebay.org/tor/4122511/Kalyway_Leopard_10.5.2_DVD_Intel_Amd](http://thepiratebay.org/tor/4122511/Kalyway_Leopard_10.5.2_DVD_Intel_Amd)  
  
**3.因为Kalyway精简掉了中文支持，所以还必须修在中文支持包：  
**  
1).简体中文:  
下载地址1:[http://www.mediafire.com/?xkmmkmoer7z](http://www.mediafire.com/?xkmmkmoer7z)  
下载地址2:http://www.fs2you.com/files/051ec987-f5cf-11dc-93ac-0014221b798a/

2).繁体中文:  
下载地址:http://www.fs2you.com/files/1e8f6b8c-081e-11dd-a48a-0014221b798a/   
  
**4.因为在 Vista 或者 XP 共存的，所以建议用 TBOOT 或者 CHAIN0 来引导，你还需要修在 TBOOT 和 CHAIN0：  
**  
TBOOT: [http://www.weiphone.com/thread-1918-1-1.html](http://www.weiphone.com/thread-1918-1-1.html)  
  
**5. nVIDIA 8400 M或者其他 nVIDIA 的显卡，请下载驱动包：  
  
[http://www.horay.cn/download/10.5.2_NV8600GT_kexts.rar](http://www.horay.cn/download/10.5.2_NV8600GT_kexts.rar)  
**  
**6.建议下载Fun Input Toy 输入法：  
  
**[http://fit.coollittlethings.com/?page_id=3](http://fit.coollittlethings.com/?page_id=3)  
  
**7.重要！请准备一张WinPE启动盘，里面要有可以激活分区的工具，比如PM7。或者可以启动并激活分区的引导盘  
均可。否则安装后系统将无法引导。**  
  
**二、安装**  
  
**1.准备 Mac OSX 分区：**  
  
我实在磁盘最后预留了一个 Mac 主分区来安装 OSX 的，不过据说用TBOOT引导的话，逻辑分区也是可以滴。准备分区的过程，请参见：  
  
[http://benyouhui.it168.com/thread-367135-1-2.html](http://benyouhui.it168.com/thread-367135-1-2.html)  
  
**2.安装 Mac OSX：**  
  
用Mac安装盘启动，一路回车，不用任何参数，进入安装环境后，用磁盘工具把刚才的分区"抹除"掉(记得设置卷标名称，假定为OSX)，这样才能安装到那里去。另外自己选择创下组件，然后正常安装即可。  
  
**3.修复 XP/Vista 引导：**  
  
安装后，XP/Vista 主分区被设为非激活状态，不能引导系统了，此时用引导盘启动，把第一个主分区设为激活，重新启动即可。  
  
**4.设置 CHAIN0 或者 TBOOT 引导：**  
  
接上步，重新启动进入 XP 或者 Vista 后，在 XP NT Loader 或者 Vista Boot Manager 中加入引导项（以TBOOT举例，CHAIN0也一样）：  
  
1).XP：在 BOOT.INI 最后加入一行即可：  
  
C:\TBOOT="Mac OSX Leopard"  
  
2)Vista：请看命令（哈哈，这么久了，我终于对BCDEdit很熟悉了）：  
  
BCDEdit /create /d "Mac OSX Leopard" /application bootsector  
BCDEDIT /set {XXXX-XXXX...} device boot  
BCDEDIT /set {XXXX-XXXX...} path \TBOOT  
BCDEDIT /displayorder {XXXX-XXXX...} /addlast  
BCDEDIT /timeout 5  
  
（执行第一条命令后，记下 GUID，假设为：{XXXX-XXXX...}）  
  
**5.完成安装**  
  
启动后选择 Mac OSX，然后进入到 Mac OS X引导提示（默认5秒超时），此时必须按F8，选择OSX分区启动，否则又进入到XP中去了。这点以后每次启动 Mac OSX 都必须这样做，挺不完美的，不知道哪里可以更改Mac OSX Darwin引导的默认启动项。然后即可进入设置向导，完成后即进入到 Mac OSX 桌面。  
  
**6.安装中文支持：**  
  
点击 SimplifiedChinese.pkg 安装中文支持包，完成安装后，自动注销。然后重新进入，在系统设置中，把简体中文拖动到最上面，重新注销在登陆就是完整的中文界面了。  
  
顺便安装个好用的输入法，默认 Alt+Space 激活。  
  
**6.安装显卡驱动和其他驱动**  
  
很简单安装玩重新启动即可。关键是有些驱动比较难找，呵呵：）  
  
A8Sc 验证成功。到此，装好了准备给MM用一下，先行体会一下 Leopard，其实很好用啦，慢慢享用吧……  
  
**三、有用的链接  
  
[http://bbs.pcbeta.com/viewthread.php?tid=257912&page=1&fromuid=449332#pid5448849](http://bbs.pcbeta.com/viewthread.php?tid=257912&page=1&fromuid=449332#pid5448849)  
[http://benyouhui.it168.com/thread-663049-1-1.html](http://benyouhui.it168.com/thread-663049-1-1.html)  
[http://bbs.pcbeta.com/thread-257678-1-2.html](http://bbs.pcbeta.com/thread-257678-1-2.html)  
[http://www.weiphone.com/thread-1918-1-1.html](http://www.weiphone.com/thread-1918-1-1.html)  
[http://bbs.think-different.cn/thread-121-1-1.html?sid=JcV4ny](http://bbs.think-different.cn/thread-121-1-1.html?sid=JcV4ny)  
[http://forum.insanelymac.com/index.php?showtopic=90505&st=20](http://forum.insanelymac.com/index.php?showtopic=90505&st=20)**
