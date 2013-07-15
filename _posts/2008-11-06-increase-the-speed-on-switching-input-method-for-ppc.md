---
date: 2008-11-06 05:17:36+00:00
layout: post
title: 提高PPC输入法切换速度
thread: 436
categories: 文档
tags: WM 编程
---

关于 PPC 输入法切换速度慢的问题分析，很久以前我写过一篇日志（http://www.yonsm.net/read.php?265），从CE源代码中找出了原因，但一直没有解决方案。  
  
今天从论坛中一不小心看到一帖子（http://bbs.pdafans.com/thread-306707-1-1.html），说把 HKEY_CLASSS_ROOT\CLSID 导出然后重新导入，即可大大提高输入法切换速度。咋一看以为不太可能，试了一下之后发现，确实如此。  
  
初步猜测，可能的原因是，注册表的hive保存在ROM的原因导致了速度慢，重新导入后则把更改的部分导入到了内置存储中（可写Storage部分）。  
  
感谢 wwx1987 的发现。  
  

