---
date: 2004-11-20 04:33:52+00:00
layout: post
title: 完全使用 GDI 绘制的 Office XP 启动画面风格信息框
thread: 106
categories: 代码
---

下载: [CAboutDlg 静态类](/assets/1100867377.rar) (17.5 KB)

  


说明:

  


1.所有信息在 Define.h 中定义。

  


2.如果要添加文字、区域或超链接，请在 AboutDlg.cpp 中的相关数组添加一个成员即可，非常简单方便。

  


3.启动闪屏画面调用方式: CAboutDlg::Splash(); （也可以指定延时关闭时间；默认一秒关闭；-1 表示由用户点击关闭）

  


4.常规显示调用方式: CAboutDlg::Show(hParent); 

没别的意思，仅仅是表现一下我是多么耐心细致地写代码而已：）
