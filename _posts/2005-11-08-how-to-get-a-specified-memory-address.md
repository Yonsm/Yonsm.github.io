---
date: 2005-11-08 06:28:57+00:00
layout: post
title: 如何获取指定内存所在的模块、当前模块、当前函数的返回模块
thread: 15
categories: 文档
tags: Win 编程
---

利用一个函数VirtualQuery可以获取指定内存所在的模块：

inline HMODULE GetModuleFromAddr(PVOID p)  
{  
    MEMORY_BASIC_INFORMATION m = {0};  
    VirtualQuery(p, &m, sizeof(MEMORY_BASIC_INFORMATION));  
    return (HMODULE) m.AllocationBase;  
}

<!-- more -->有了上面的函数，就非常容易获取当前模块的句柄（比如在静态LIB链接到DLL的项目中，需要知道模块句柄的情况）：

HMODULE hThisModule = GetModuleFromAddr(当前模块中的任意函数或变量地址);

更进一步的应用，假如我们需要知道那个模块在调用自己，可以结合_ReturnAddress() intrinsic来实现：

全局声明：EXTERN_C PVOID _ReturnAddress();

调用：HMODULE hCallerModule = GetModuleFromAddr(_ReturnAddress());
