---
date: 2005-02-24 01:19:53+00:00
layout: post
title: 完美的 NSIS 安装脚本
thread: 58
categories: 文档
---

这几天稍稍深入地使用了一下 NSIS，功能太强大了。回首看看不比学习一门高级语言容易，不过一般也能信手拈来……

制作了一个 CuteFoto 的 NSIS 安装脚本，支持多语言，支持自动判断操作系统并优先选择安装 ASCII/UNICODE或AMD64版本，支持……

感觉应该是非常完美了：）<!-- more -->

附件下载: [请点这里](/assets/1109151259.nsi)

其中几个地方说明一下:

  * 如果以 SectionGroup 而不是 Section 为第一个区段定义，发现 NSIS 无法正常处理默认/自定义安装类型，应该是 NSIS 的一个 BUG。但是在d第一个 SectionGroup 之前加上一个无名的空段 (隐藏)，即可解决此问题。即 Section...SectionEnd。
  * 判断是否是 NT 类操作系统: ReadRegStr $0 HKLM "SOFTWAREMicrosoftWindows NTCurrentVersion" "CurrentVersion"  
${If} $0 != ""
  * 判断是处理器架构: ReadRegStr $0 HKLM "SYSTEMCurrentControlSetControlSession ManagerEnvironment" "PROCESSOR_ARCHITECTURE"  
${If} $0 != "AMD64"
  * 还有单选按钮支持，看代码……
  * NSIS 的中文文档和例子请看这里: [http://foobar.nease.net/nsis/](http://foobar.nease.net/nsis/) (衷心感谢蓝色网际网友的工作，foobarr.cab 内有一个助手函数库，看看也许会很有用)
  * 
