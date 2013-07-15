---
date: 2007-04-21 06:00:45+00:00
layout: post
title: 'Aeon Variable/永生变量 - 保存程序设置到EXE本身'
thread: 317
categories: 文档
tags: Win WM 编程
---

全宇宙人中的编程人员都知道代码中有 局部变量/Local Variable、Global Variable/全局变量（还有Heap/Const，全局变量可细分 .data .bss等），各司其职，各有用处。  
  
这里我提出一个自己胡诌出来的全新变量类型：Aeon Variable，永生变量——比全局变量更拓展一层，变量在程序退出后再次运行，这些变量还保存在上次运行的值——可千万别说从注册表啊什么的重新读取一遍就行了，我这是透明的全新的方法。我已经用两种方法实现了 Aeon Variable：  
  
1. 把数据保存在 EXE 文件最后：这个和保存在注册表之类其实差不多，没新意了。  
2. 代码中定义一个新的 Data Segment，比如叫 .AEON 吧，只要是想永生的变量，都放在这里面：  
  
HWND g_hWnd = NULL; // Global Variable, NOT AEON!  
  
#pragma data_seg(AEON_SEG) // AEON Variable  
INT g_iStartPage = 0;  
TCHAR tzName[MAX_PATH] = TEXT("Yonsm");  
#pragma data_seg() // End of AEON Variable  
<!-- more -->  
OK，然后在 WinMain 开始调用一下我的 AeonInit(hInstance)，WinMain 结束前调用 AeonExit(hInstance)。哈哈，这些变量就永生了，千秋万载一统江湖，仙福永享寿与天齐，万税万税万万税。  
  
实现的思路是这样的，先从 AeonExit 说起：  
  1). 复制当前运行的 *.EXE （DLL 也即将支持）为 *.EXE.AEON  
  2). 搜索当前模块中的 PE Section，找到 .AEON Data Segment 后，把这个段写入到到 *.EXE.AEON 中，这样永生变量就更新到了 *.EXE.AEON 中。  
 3). 运行 *.EXE.AEON。  
 4). 立即、马上以及赶快退出！  
  
再说 AeonInit：  
 1). 判断当前运行的可执行文件名是否是 .AEON，如果是，嘿嘿，自己运行的啰（而不是用户运行的）；如果不是则正常启动程序。  
 2). 把 *.EXE 删除掉，把 *.EXE.AEON 重命名为 *.EXE。  
 3). 重复步骤 2，直到成功。  
  
哈哈，真佩服自己的奇思妙想，而且实现得天衣无缝。  
  
  
测试了一下，WinALL 都能用。但 WinCE 中不能用方法2，因为无法查找正在运行的 PE 的内存中的 Image Base（压根就没有完整的 MZ 开始），所以无法找到 .AEON Segment （或许根本就没有 Section Header 在内存中）。当方法一在 WinCE 中可用。  
  
这样，如此这般，就能做出真正真正的“绿色”软件了！哈哈……妙！  
  
  
代码下载（普通函数实现，但特地把文件扩展名特地使用 .h 而不是 .cpp，期望强制使用者在 WinMain 或 DllMain 之类的 .cpp 中 #include "Aeon.h" ，且只 #include 一次）：  
  
  
  
[下载](/assets/Aeon.h)  
  

