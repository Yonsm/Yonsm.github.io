---
date: 2006-02-11 08:27:20+00:00
layout: post
title: '#pragma 指示符应用举例'
thread: 173
categories: 文档
tags: Win 编程
---

_[Bo-Blog 1.x 到 2.0 的升级程序竟然出现数据丢失现象，导致丢失了好几篇文档，故手动贴上] _  


  
尽管 C 和 C++ 都已经有标准，但是几乎每个编译器 (广义，包含连接器等) 扩展一些 C/C++ 关键字。合理地应用这些关键字，有时候能使我们的工作非常方便。下面随便说说 Visual C++ 中 #pragma 指示符的使用。

<!-- more -->  


**一、用#pragma导出DLL函数**

  


传统的到出 DLL 函数的方法是使用模块定义文件 (.def)，Visual C++ 提供了更简洁方便的方法，那就是"__declspec()"关键字后面跟"dllexport"，告诉连接去要导出这个函数，例如：

  
  

    
    __declspec(dllexport) int __stdcall MyExportFunction(int iTest);

  


把"__declspec(dllexport)"放在函数声明的最前面，连接生成的 DLL 就会导出函数"_MyExportFunction@4"。

  


上面的导出函数的名称也许不是我的希望的，我们希望导出的是原版的"MyExportFunction"。还好，VC 提供了一个预处理指示符"#pragma"来指定连接选项 (不仅仅是这一个功能，还有很多指示功能) ，如下：

  
  

    
    #pragma comment(linker,"/EXPORT:MyExportFunction=_MyExportFunction@4")

  


这下就天如人愿了：）。如果你想指定导出的顺序，或者只将函数导出为序号，没有 Entryname，这个预处理指示符 (确切地说是连接器) 都能够实现，看看 MSDN 的语法说明：

  
  

    
    /EXPORT:entryname[,@ordinal[,NONAME]][,DATA]

  


@ordinal 指定顺序；NONAME 指定只将函数导出为序号；DATA 关键字指定导出项为数据项。

  


**二、指示文件只包含一次**

  


在头文件中，一般在整个工程中我们只要包含一次就够了，但是如果我在多个 .c/.cpp 文件中都要包含着个头文件，比如 Windows.h，那很多声明等等岂不是有两次了？解决这个问题的传统的方法是在头文件开始出用 #define 定义一个宏，比如 Windows.h 中:  


  

    
    <div style="color: #2222aa; background-color: #f5f5f0"> 
    
    #ifndef _WINDOWS_<br></br> #define _WINDOWS_

  
  
  


  然后在文件结为加上 #endif，这样就可以避免被包含多次。但是这样的后果是代码的可读性较差 (个人观点)，VC 给我们提供了另外一个途径，那就是在文件的前面加上:

  
  
  
  
  
  

    
    #pragma once

  
  
  
  
  


   是不是很方便？

  
  
  
  
  


**三、使警告无效**

  


**  


**  
  


   有时候我们不得不对变量进行强制转换，由此引来编译器的一番警告，特别是 C++ 中，类型检查相对于 C 更为严格。这虽然不影响什么，但是看起来多不爽----我是故意要这样的，你警告什么！：）这时候你看到警告类型，比如"warning C4311: "类型转换" : 从"HHOOK"到"BOOL"的指针截断"，在前面加上:

  
  
  
  
  
  

    
    #pragma warning(disable: 4311)

  
  
  


  编译器就没话说了：）。

  
  
  
  
  


**四、指定连接要使用的库**

  


**  


**  


**  
  


   比如我们连接的时候用到了 WSock32.lib，你当然可以不辞辛苦地把它加入到你的工程中。但是我觉得更方便的方法是使用 #pragma 指示符，指定要连接的库:

  
  
  
  
  

    
    #pragma comment(lib, "WSock32.lib")

  
  
  


**  


**  


**五、显示编译消息**

  


**  
    没多少用处，举个例子吧:  
  
  
  
  
  

    
    #ifdef _DEBUG<br></br> #pragma message("编译连接为调试模式...")<br></br> #endif // _DEBUG

  
  
  


  其实"#pragma"的功能远远不止于此，以上只是冰山一角而已。具体的使用方法，详细情况清参看 MSDN，这里仅仅是说说有这些功能而已：） 

  
  
**    没多少用处，举个例子吧:

**

**

**

**

**

**

**
