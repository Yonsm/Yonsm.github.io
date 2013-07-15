---
date: 2008-12-17 23:43:14+00:00
layout: post
title: MSVC 中的几个非标准特殊关键字
thread: 445
categories: 文档
tags: Win 编程
---

MSVC 中的有些非标准的关键字，有些时候特别有用。  
  
1. __if_exist() 和 __if_not_exist()  
  
用途：判断一个变量是否存在，（在编译期）以便选择相应的代码。  
举例：以下代码，无论 g_hInst 是否声明，都不会编译出错。  
  
__if_exist (g_hInst)  
{  
   LoadString(g_hInst, ...)  
}  
__if_not_exist (g_hInst)  
{  
  LoadString(NULL ...)  
}  
  
  
2.__declspec(selectany)  
  
用途：指明变量或函数实体在连接是只选择其中一个实体拷贝。<!-- more -->  
举例：在头文件中声明一个变量，即使很多CPP文件包含它，连接期间也只会选择其中一个，从而避免错误。  
  
__declspec(selectany) HINSTANCE g_hInst;  
  
这样就不必在.cpp中定义变量，在.h中声明变量了（直接在.h中定义，多余的副本会被连接器抛弃）。  
  
3.以前介绍过的#pragma、naked等等，参考以前的文档......  

