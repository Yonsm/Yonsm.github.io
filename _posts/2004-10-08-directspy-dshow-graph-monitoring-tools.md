---
date: 2004-10-08 19:46:08+00:00
layout: post
title: DirectSpy - DShow Graph 监视工具
thread: 157
categories: 资源
---

注册后，可以在 MS GraphEdit 中查看所有 DirectShow 程序的 Filter Graph，即使该 Graph未加入到 Running Table----除非该程序作了特殊保护处理。  
  
这样就可以看看别人的 Graph 是怎样构建的了，写 DShow 程序的话，这是好咚咚。  
  
网上只能下载 Trail 版本，只能看到 Windows Media Player 打开 AVI/MPG 文件的 Graph，附件是我Crack过的。已解除这个限制，和 Full Version 功能一样：）  
  
作者主页： [http://www.asvzzz.com/directspy.htm](http://www.asvzzz.com/directspy.htm)

  


使用举例：  
  
1.注册：Regsvr32.exe DirectSpy.ax。  
2.双击一个 .mpg 文件，用 Windows Media Player 打开播放它。  
3.打开 GraphEdit，File->Connect to remote graph，这时候可以看到。  
  
有一个问题，那就是如果用 Windows Media Player 重新打开另一个文件，Graph 好像不会更新。

  


附件下载：请点击[这里](/assets/1097207028.rar)

  

