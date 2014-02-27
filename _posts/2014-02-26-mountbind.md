---
date: 2014-02-26 19:50:17+00:00
layout: post
title: '另类思维实现 Mac OS X 下的 mount bind'
categories: 文档
tags: 分享 Mac
---

*nix 下的 mount 基本上都支持 -o bind 来绑定另外一个目录到特定目录中。但 Mac OS X 的 mount 确不支持此功能，有时候这个“特性”非常让人郁闷——比如，百度网盘的脑残设计，强制设定只能同步到一个叫“百度云同步盘”的目录中，ln -s 创建的外部链接目录都不支持（需求场景，SSD小硬盘，某个存放大姐姐们的目录在NAS或移动硬盘上，但是想跟百通网盘同步）。

几经尝试，终于找到一个曲线实现的方法：用 mount_afp 来模拟 mount -o 的功能：

如果是本地移动硬盘，先确保该目录已共享，然后执行 

	mount_afp afp://user:pass@localhost/Movies ~/百度云同步盘/Movies

搞定了。

后话：我扯淡了，半夜才想起来，以前创建 RAMDISK 的时候用的 mount -t hfs -o union *** *** 就可以实现这种功能……