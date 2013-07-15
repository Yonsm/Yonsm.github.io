---
date: 2006-08-22 07:09:18+00:00
layout: post
title: CeleFusion - 具有数据中继/变换功能的 HTTP 代理
thread: 237
categories: 代码
tags: Win 编程
---

一个短小的 HTTP Proxy，算是比较精妙的实用程序了，附件是源代码，非常简明清晰。

*  支持 HTTP GET Proxy（暂不支持 HTTP CONNECT 模式）
*  支持 Relay 模式，可以在客户端和 Proxy 插入不限个数的 Relay 服务器
*  Relay 模式支持数据加密（变换），在 Relay 和 Proxy 之间的数据不再是明文，可以比较数据被监听（装个Proxy在国外的机器上，自己本机上装个Relay服务器，就能访问所有国外网站了）
*  支持普通模式和 NT 服务模式运行
*  服务支持远程安装、删除

控制台程序，下面是用法：

			D:\Visual Studio 2005\Projects\CeleFusion\Release>CeleFusion /?
			CeleFusion 1.2.8
			Copyright (C) 2006 Yonsm.NET, All Rights Reserved

			Usage: CeleFusion.exe [/Options]
			 INSTALL                Install NT service
			 REMOVE                 Remove NT service
			 SERVE                  Run NT service
			 START                  Start proxy
			 STOP                   Stop proxy

			 MACHINE < \\Machine>    Remote machine name [Local Computer] USERNAME     Remote machine username [Current Username] PASSWORD     Remote machine password [Current Password]
			 PORT             Port to listen [4444] RELAY   Relay server and port [NA:4444]

			D:\Visual Studio 2005\Projects\CeleFusion\Release>
