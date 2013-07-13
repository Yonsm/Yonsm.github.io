---
author: Yonsm
comments: true
date: 2005-12-06 20:23:04+00:00
layout: post
slug: pobind-iat-implement-api-hook-reusable-code
title: PoBind - IAT替换实现API Hook的可重用代码
wordpress_id: 8
categories:
- 代码
---

此代码演示了替换IAT实现API Hook的完整实现。其中 ApiHook.cpp/.h 为可充用的代码，参考了《Windows核心编程》，但应该比他写的看起来更舒服些（但去除了Unhook功能，因为我认为没必要）。

此DLL一旦被任何进程载入，即会替换进程内的相关API的所有地址，包括后面载入的的DLL。详细情况，请参考代码和《Windows核心编程》。<!-- more -->

下载：[PoBind](up/PoBind%201.0.69.271.rar)
