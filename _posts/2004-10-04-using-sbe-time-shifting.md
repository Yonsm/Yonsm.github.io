---
date: 2004-10-04 02:19:09+00:00
layout: post
title: 使用 SBE 实现 Time Shifting
thread: 165
categories: 文档
---

一、概述

  


　　Windows XP Service Pack1 提供的 Stream Buffer Engine （以下简称 SBE）允许应用程序对视频流（包括 Live Source 和 File Source）进行定位、暂停、录制、快进和倒放操作。通过 SBE，应用程序可以简单快速地实现 Time Shifting 功能。

  


　　目前，SBE 仅在 Windows XP Service Pack 1 /2中提供，且仅支持 MPEG2 Stream 和 DV Stream。

  


  
二、实现

  


　　使用 SBE 提供的 Stream Buffer Sink Filter 和 Stream Buffer Source Filter，应用程序可以构建两个 Graph。然后通过 IStreamBufferSource::SetStreamSink() 关联两个 Graph，使 Stream Buffer Source Filter 读取 Stream Buffer Sink Filter 的输出。通过 Stream Buffer Source Filter 上的 IStreamBufferMediaSeeking::SetRate()，可以设置播放速率，实现快进和倒放功能。

  


　　BTW: 两个 Graph 可以处于不同的进程中（此时通过 Stream Buffer Source Filter 的 IFileSourceFilter::Load() 关联两个 Graph）；另外，Sink Filter 和 Source Filter 也可处于同一个Graph 中。

<!-- more -->  


  
三、图解

  


　　先看看 Windows XP Media Center Edition 的 My TV 的 Graph：

  


[![ ](/assets/1096798563.jpg)](/assets/1096798563.jpg)

  


　　最左边的就是 Stream Buffer Source Filter。下面，我们来看看怎样对 Live Source 实现 Time Shifting 功能（File Source 与 Live Source 类似，在此不再详述）。先看看怎么连接 Stream Buffer Sink Filter：

  


[![ ](/assets/1096798652.jpg)](/assets/1096798652.jpg)

  


　　MPEG-2 流通过 MPEG-2 Demultiplexer 分成 Video Stream 和 Audio Stream，其中 Audio Stream 直接连到 Stream Buffer Sink Filter，Video Stream 通过 MPEG-2 Video Stream Analyzer 后再连接到 Stream Buffer Sink Filter。

  


　　再看看 Stream Buffer Source Filter 的连接方法：

  


[![ ](/assets/1096798665.jpg)](/assets/1096798665.jpg)

  


  
四、代码

  


　　为了使 Stream Buffer Source Filter 读取 Stream Buffer Sink Filter 的输出，需要在代码中实现。下面是伪代码：

  


　　IStreamBufferSink::LoadProfile(NULL); // 一定要先 LockProfile。如果要设置相关属性，必须在 LockProfile 之前  
　　IStreamBufferSource::SetStreamSink(IStreamBufferSink);

  


　　好了，运行这两个 Graph，OK！

  


　　通过 Stream Buffer Sink Filter 上的 IStreamBufferInitialize、IStreamBufferConfig 等接口，可以配置相关的参数（如 Buffer 文件大小、路径等等）。如果省略这些步骤，SBE 将会使用省却的参数。

  


　　通过 Stream Buffer Source Filter 上的 IStreamBufferMediaSeeking 接口，可以实现媒体定定位、快进和倒放操作。

  


　　通过 Stream Buffer Source Filter 上的 IStreamBufferSource::CreateRecorder，可以获取 IStreamBufferRecordControl 接口，进而实现录制功能。

  
  


五、其它

  


　　用 IStreamBufferMediaSeeking::SetRate(dRate) 设置播放速率，如果 dRate 为负值表示倒放。当倒放到 Buffer 起始处的时候（无 Stream 可供倒放了），将转入暂停状态。

  


　　如果 dRate 为正值且大于 1 表示快进。当快进到 Buffer 末端的时候（无 Stream 可供快进了），将转入正常播放状态。

  


　　除正常播放状态（dRate = 1）以外，Audio 将不会播放。

  


　　所有的 SBE 事件通知消息（如倒放、快进到头等），可以通过常规的 Direct Show 的方法获得。

  


  


  

