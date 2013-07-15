---
date: 2005-10-15 21:28:10+00:00
layout: post
title: 使用 WMF SDK 实现视频网络广播
thread: 18
categories: 文档
tags: Win 编程
---

大致步骤：

  1. 创建并配置  Reader。
  2. 创建并添加 NetWork Sink （WMCreateWriterNetworkSink）。
  3. 配置 Stream 格式 (WMF SDK 里的格式和 DirectShow 的格式有很多相通之处，有的和直接强制转换使用) 。
  4. pWriter->BeginWriting()。
  5. pWriter->WriteSample()。
  6. ……

暂无心情写文章，具体代码请参看： [Nedekko - Fly2000TV 电视广播插件](/nedekko)
