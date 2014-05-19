---
date: 2012-08-27 11:13:17+00:00
layout: post
title: TransText 2.2 - 字符串提取、回写以及搜索替换工具
thread: 316
categories: 软件
tags: 汉化 分享 Win
---

更新了TransText，加入了最新  Android 4.0 风格的 UTF-8 前导个数的字符串格式支持，修改了程序UI，更直观的地设置字符串格式。

功能：

1. 提取英文字符串，保存为 PASSOLO 支持的 INI 格式，以便工程化翻译（供汉化工作者使用）。
2. 回写英文字符串。
3. 查找和替换字符串。
4. 所有操作均支持文件或文件夹批量处理，支持通配符搜索文件。
5. 全面支持 BSTR (带长度的字符串模式)提取、回写和搜索。2.0 新增
<!-- more -->
6. 支持 Visual Studio 2005/2008 项目文件转换（小功能）：拖动.sln文件到“搜索”页面时，自动检测 Visual Studio 2005/2008 方案文件，并询问是否转换方案和工程文件的格式（2005/2008互转）。

最新版本，2.2.264：[TransText.2.2.264](https://raw.githubusercontent.com/Yonsm/TransText/master/Release/TransText.exe)（[源代码](http://github.com/yonsm/TransText)）

[![](https://raw.githubusercontent.com/Yonsm/TransText/master/Release/TransText.gif)](https://raw.githubusercontent.com/Yonsm/TransText/master/Release/TransText.gif)

<!-- more -->

终于可以大规模工业化汉化 Android 程序了TransText 提取，配合 Passolo，完美实现……
从此可以不用小打小闹了。汉化最怕的就是不能重用资源，利用Passolo的强大功能可以解决这个问题。但Passolo并不支持 Android 的资源文件，配合TransText就行了，步骤大概是：

1. 用 TransText 提取 .arsrc的字符串（勾选UNICODE字符串模式，勾选带长度的字符串模式，只提取英文字符串也可以勾选，避免其他字符串）

2. 用 Passolo 添加 .ttt 文件看工程中（建议创建 .ttt 文件的规则，复制INI规则既可，或者不会的话，直接把 .ttt改名为.ini），汉化ttt文件并输出汉化后的文件。（同时把汉化后的字典导出保存一下，下次升级后再用）

3.用 TransText 回写Passolo的输出ini（ttt）到.arsrc中，重新打包apk即可。


感谢 汉化新世纪 乾（qian.hanzify.org）在此工具制作过程中的意见和建议。

汉化新世纪讨论帖：[http://bbs.hanzify.org/read-htm-tid-52828.html](http://bbs.hanzify.org/read-htm-tid-52828.html) （含 VS2012 编译的支持 XP 的版本）
