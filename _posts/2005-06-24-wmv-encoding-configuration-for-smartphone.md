---
date: 2005-06-24 05:03:52+00:00
layout: post
title: 用于 Smartphone 上播放的 WMV 编码配置文件
thread: 35
categories: 文档
---

用 Windows Media Encoder 编码，速度不错，不过没有 ProCoder 快。

经过测试，我认为下列配置的 WMV 最适合在 Smartphone 上播放：

  * 视频
    * 格式：WMV9 Video，最棒的编码格式。
    * 尺寸：224 x 176，适用于全屏播放。勿用 220x176，因为非 16 整数倍的尺寸会导致 BetaPlay 崩溃。
    * 码率：峰值 VBR （可变码率），平均码率 120 Kbps，最大码率 150 Kbps，保证流畅播放。
    * 帧率：10 fps，够流畅了。
  * 音频
    * 格式：WMV9.1 Audio，Mono，没的说。
    * 码率：CBR （固定码率），16 Kbps。
    * 采样：16 KHz，音质还可以。

这样的配置编出来的视频音频质量不错，压缩率高，一分钟还没有 1M 数据，一部电影也就 120 M 左右，128M 的 SD 卡搞定——量身定制哦：）

[下载配置文件](/assets/1119446244.prx)
