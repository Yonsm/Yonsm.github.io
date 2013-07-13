---
author: Yonsm
comments: true
date: 2006-03-03 07:17:01+00:00
layout: post
slug: reposted-wtl-for-beginners
title: '[转贴]WTL初学者'
wordpress_id: 188
categories:
- 文档
tags:
- 编程
---

对于WTL来说，我是个地道的初学者。虽然当年用C++的时候，用过VCL和MFC（那时候的WTL还没有现在这么出名），水平只是限于一般使用者。CSDN的BCB版上七千多的专家分就是明证——这小子水平也很菜。重拾对WTL的关注是因为Visual Studio 2005，微软的官方文档上已经说明，VS.NET 2005已经支持WTL在CE平台上的开发了。不过那个WTL 8.0到现在还没出来，弄得一堆人在微软新闻组里乱叫。  
  
为了提前感受一下，我弄了个WTL 7.1感受一下。其实WTL 7.1已经支持在EVC4下开发CE和Windows Mobile的应用程序了，我们稍后会讲到。既然是初学者，就要从最基本的入手，先用VS.NET 2003写一个WTL的应用程序吧。  
  
从网上下载WTL 7.1的安装包，解压后会生成一个“c:\wtl71”的文件夹。因为我们要在VS.NET 2003里写WTL程序，所以就选择执行“AppWiz70”目录下的setup71.js，如果是VS.NET 2002则选择执行“setup.js”。  
  
安装过程比以前要容易多了，在提示安装成功后，我们直接打开VS.NET 2003，创建新项目，在VC++项目中会多一个ATL/WTL Application Wizard的图标……  
  
更多内容请看：http://www.microsoft.com/china/msdn/developercenter/mobility/blog/WTLstart.mspx  
  
原文引用自：http://blog.csdn.net/aawolf/，作者：马宁
