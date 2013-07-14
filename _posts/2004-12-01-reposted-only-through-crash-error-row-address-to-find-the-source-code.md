---
author: Yonsm
comments: true
date: 2004-12-01 03:13:04+00:00
layout: post
slug: reposted-only-through-crash-error-row-address-to-find-the-source-code
title: '[转载]仅通过崩溃地址找出源代码的出错行'
wordpress_id: 97
categories:
- 文档
---

_好友_[_老罗_](http://www.luocong.com/)_文章，有时候特别有用，转载于此:_

作为程序员，我们平时最担心见到的事情是什么？是内存泄漏？是界面不好看？……错啦！我相信我的看法是不会有人反对的——那就是，程序发生了崩溃！  
  
“该程序执行了非法操作，即将关闭。请与你的软件供应商联系。”，呵呵，这句 M$ 的“名言”，恐怕就是程序员最担心见到的东西了。有的时候，自己的程序在自己的机器上运行得好好的，但是到了别人的机器上就崩溃了；有时自己在编写和测试的过程中就莫名其妙地遇到了非法操作，但是却无法确定到底是源代码中的哪行引起的……是不是很痛苦呢？不要紧，本文可以帮助你走出这种困境，甚至你从此之后可以自豪地要求用户把崩溃地址告诉你，然后你就可以精确地定位到源代码中出错的那行了。（很神奇吧？呵呵。）<!-- more -->  
  
首先我必须强调的是，本方法可以在目前市面上任意一款编译器上面使用。但是我只熟悉 M$ 的 VC 和 MASM ，因此后面的部分只介绍如何在这两个编译器中实现，请读者自行融会贯通，掌握在别的编译器上使用的方法。  
  
Well，废话说完了，让我们开始！ ：）  
  
首先必须生成程序的 MAP 文件。什么是 MAP 文件？简单地讲， MAP 文件是程序的全局符号、源文件和代码行号信息的唯一的文本表示方法，它可以在任何地方、任何时候使用，不需要有额外的程序进行支持。而且，这是唯一能找出程序崩溃的地方的救星。  
  
好吧，既然 MAP 文件如此神奇，那么我们应该如何生成它呢？在 VC 中，我们可以按下 Alt+F7 ，打开“Project Settings”选项页，选择 C/C++ 选项卡，并在最下面的 Project Options 里面输入：/Zd ，然后要选择 Link 选项卡，在最下面的 Project Options 里面输入： /mapinfo:lines 和 /map:PROJECT_NAME.map 。最后按下 F7 来编译生成 EXE 可执行文件和 MAP 文件。  
  
在 MASM 中，我们要设置编译和连接参数，我通常是这样做的：  
  


rc %1.rc  
ml /c /coff /Zd %1.asm  
link /subsystem:windows /mapinfo:exports /mapinfo:lines /map:%1.map %1.obj %1.res
  
把它保存成 makem.bat ，就可以在命令行输入 makem filename 来编译生成 EXE 可执行文件和 MAP 文件了。  
  
在此我先解释一下加入的参数的含义：  
  


/Zd              表示在编译的时候生成行信息  
/map[:filename]  表示生成 MAP 文件的路径和文件名  
/mapinfo:lines   表示生成 MAP 文件时，加入行信息  
/mapinfo:exports 表示生成 MAP 文件时，加入 exported functions （如果生成的是 DLL 文件，这个选项就要加上）
  
OK，通过上面的步骤，我们已经得到了 MAP 文件，那么我们该如何利用它呢？  
  
让我们从简单的实例入手，请打开你的 VC ，新建这样一个文件：  
  


01  //****************************************************************  
02  //程序名称：演示如何通过崩溃地址找出源代码的出错行  
03  //作者：罗聪  
04  //日期：2003-2-7  
05  //出处：http://www.luocong.com（老罗的缤纷天地）  
06  //本程序会产生“除0错误”，以至于会弹出“非法操作”对话框。  
07  //“除0错误”只会在 Debug 版本下产生，本程序为了演示而尽量简化。  
08  //注意事项：如欲转载，请保持本程序的完整，并注明：  
09  //转载自“老罗的缤纷天地”（http://www.luocong.com）  
10  //****************************************************************  
11    
12  void Crash(void)  
13  {  
14      int i = 1;  
15      int j = 0;  
16      i /= j;  
17  }  
18    
19  void main(void)  
20  {  
21      Crash();  
22  }
  
很显然本程序有“除0错误”，在 Debug 方式下编译的话，运行时肯定会产生“非法操作”。好，让我们运行它，果然，“非法操作”对话框出现了，这时我们点击“详细信息”按钮，记录下产生崩溃的地址——在我的机器上是 0x0040104a 。  
  
再看看它的 MAP 文件：（由于文件内容太长，中间没用的部分我进行了省略）  
  


CrashDemo  
  
Timestamp is 3e430a76 (Fri Feb 07 09:23:02 2003)  
  
Preferred load address is 00400000  
  
Start         Length     Name                   Class  
0001:00000000 0000de04H .text                   CODE  
0001:0000de04 0001000cH .textbss                CODE  
0002:00000000 00001346H .rdata                  DATA  
0002:00001346 00000000H .edata                  DATA  
0003:00000000 00000104H .CRT$XCA                DATA  
0003:00000104 00000104H .CRT$XCZ                DATA  
0003:00000208 00000104H .CRT$XIA                DATA  
0003:0000030c 00000109H .CRT$XIC                DATA  
0003:00000418 00000104H .CRT$XIZ                DATA  
0003:0000051c 00000104H .CRT$XPA                DATA  
0003:00000620 00000104H .CRT$XPX                DATA  
0003:00000724 00000104H .CRT$XPZ                DATA  
0003:00000828 00000104H .CRT$XTA                DATA  
0003:0000092c 00000104H .CRT$XTZ                DATA  
0003:00000a30 00000b93H .data                   DATA  
0003:000015c4 00001974H .bss                    DATA  
0004:00000000 00000014H .idata$2                DATA  
0004:00000014 00000014H .idata$3                DATA  
0004:00000028 00000110H .idata$4                DATA  
0004:00000138 00000110H .idata$5                DATA  
0004:00000248 000004afH .idata$6                DATA  
  
  Address         Publics by Value              Rva+Base     Lib:Object<
br />  
0001:00000020       ?Crash@@YAXXZ              00401020 f   CrashDemo.obj  
0001:00000070       _main                      00401070 f   CrashDemo.obj  
0004:00000000       __IMPORT_DESCRIPTOR_KERNEL32 00424000     kernel32:KERNEL32.dll  
0004:00000014       __NULL_IMPORT_DESCRIPTOR   00424014     kernel32:KERNEL32.dll  
0004:00000138       __imp__GetCommandLineA@0   00424138     kernel32:KERNEL32.dll  
0004:0000013c       __imp__GetVersion@0        0042413c     kernel32:KERNEL32.dll  
0004:00000140       __imp__ExitProcess@4       00424140     kernel32:KERNEL32.dll  
0004:00000144       __imp__DebugBreak@0        00424144     kernel32:KERNEL32.dll  
0004:00000148       __imp__GetStdHandle@4      00424148     kernel32:KERNEL32.dll  
0004:0000014c       __imp__WriteFile@20        0042414c     kernel32:KERNEL32.dll  
0004:00000150       __imp__InterlockedDecrement@4 00424150     kernel32:KERNEL32.dll  
0004:00000154       __imp__OutputDebugStringA@4 00424154     kernel32:KERNEL32.dll  
0004:00000158       __imp__GetProcAddress@8    00424158     kernel32:KERNEL32.dll  
0004:0000015c       __imp__LoadLibraryA@4      0042415c     kernel32:KERNEL32.dll  
0004:00000160       __imp__InterlockedIncrement@4 00424160     kernel32:KERNEL32.dll  
0004:00000164       __imp__GetModuleFileNameA@12 00424164     kernel32:KERNEL32.dll  
0004:00000168       __imp__TerminateProcess@8  00424168     kernel32:KERNEL32.dll  
0004:0000016c       __imp__GetCurrentProcess@0 0042416c     kernel32:KERNEL32.dll  
0004:00000170       __imp__UnhandledExceptionFilter@4 00424170     kernel32:KERNEL32.dll  
0004:00000174       __imp__FreeEnvironmentStringsA@4 00424174     kernel32:KERNEL32.dll  
0004:00000178       __imp__FreeEnvironmentStringsW@4 00424178     kernel32:KERNEL32.dll  
0004:0000017c       __imp__WideCharToMultiByte@32 0042417c     kernel32:KERNEL32.dll  
0004:00000180       __imp__GetEnvironmentStrings@0 00424180     kernel32:KERNEL32.dll  
0004:00000184       __imp__GetEnvironmentStringsW@0 00424184     kernel32:KERNEL32.dll  
0004:00000188       __imp__SetHandleCount@4    00424188     kernel32:KERNEL32.dll  
0004:0000018c       __imp__GetFileType@4       0042418c     kernel32:KERNEL32.dll  
0004:00000190       __imp__GetStartupInfoA@4   00424190     kernel32:KERNEL32.dll  
0004:00000194       __imp__HeapDestroy@4       00424194     kernel32:KERNEL32.dll  
0004:00000198       __imp__HeapCreate@12       00424198     kernel32:KERNEL32.dll  
0004:0000019c       __imp__HeapFree@12         0042419c     kernel32:KERNEL32.dll  
0004:000001a0       __imp__VirtualFree@12      004241a0     kernel32:KERNEL32.dll  
0004:000001a4       __imp__RtlUnwind@16        004241a4     kernel32:KERNEL32.dll  
0004:000001a8       __imp__GetLastError@0      004241a8     kernel32:KERNEL32.dll  
0004:000001ac       __imp__SetConsoleCtrlHandler@8 004241ac     kernel32:KERNEL32.dll  
0004:000001b0       __imp__IsBadWritePtr@8     004241b0     kernel32:KERNEL32.dll  
0004:000001b4       __imp__IsBadReadPtr@8      004241b4     kernel32:KERNEL32.dll  
0004:000001b8       __imp__HeapValidate@12     004241b8     kernel32:KERNEL32.dll  
0004:000001bc       __imp__GetCPInfo@8         004241bc     kernel32:KERNEL32.dll  
0004:000001c0       __imp__GetACP@0            004241c0     kernel32:KERNEL32.dll  
0004:000001c4       __imp__GetOEMCP@0          004241c4     kernel32:KERNEL32.dll  
0004:000001c8       __imp__HeapAlloc@12        004241c8     kernel32:KERNEL32.dll  
0004:000001cc       __imp__VirtualAlloc@16     004241cc     kernel32:KERNEL32.dll  
0004:000001d0       __imp__HeapReAlloc@16      004241d0     kernel32:KERNEL32.dll  
0004:000001d4       __imp__MultiByteToWideChar@24 004241d4     kernel32:KERNEL32.dll  
0004:000001d8       __imp__LCMapStringA@24     004241d8     kernel32:KERNEL32.dll  
0004:000001dc       __imp__LCMapStringW@24     004241dc     kernel32:KERNEL32.dll  
0004:000001e0       __imp__GetStringTypeA@20   004241e0     kernel32:KERNEL32.dll  
0004:000001e4       __imp__GetStringTypeW@16   004241e4     kernel32:KERNEL32.dll  
0004:000001e8       __imp__SetFilePointer@16   004241e8     kernel32:KERNEL32.dll  
0004:000001ec       __imp__SetStdHandle@8      004241ec     kernel32:KERNEL32.dll  
0004:000001f0       __imp__FlushFileBuffers@4  004241f0     kernel32:KERNEL32.dll  
0004:000001f4       __imp__CloseHandle@4       004241f4     kernel32:KERNEL32.dll  
0004:000001f8       177KERNEL32_NULL_THUNK_DATA 004241f8     kernel32:KERNEL32.dll  
  
entry point at        0001:000000f0  
  
  
Line numbers for .DebugCrashDemo.obj(d:msdevmyprojectscrashdemocrashdemo.cpp) segment .text  
  
    13 0001:00000020    14 0001:00000038    15 0001:0000003f    16 0001:00000046  
    17 0001:00000050    20 0001:00000070    21 0001:00000088    22 0001:0000008d
  
如果仔细浏览 Rva+Base 这栏，你会发现第一个比崩溃地址 0x0040104a 大的函数地址是 0x00401070 ，所以在 0x00401070 这个地址之前的那个入口就是产生崩溃的函数，也就是这行：  
  


0001:00000020       ?Crash@@YAXXZ              00401020 f   CrashDemo.obj
  
因此，发生崩溃的函数就是 ?Crash@@YAXXZ ，所有以问号开头的函数名称都是 C++ 修饰的名称。在我们的源程序中，也就是 Crash() 这个子函数。  
  
OK，现在我们轻而易举地便知道了发生崩溃的函数名称，你是不是很兴奋呢？呵呵，先别忙，接下来，更厉害的招数要出场了。  
  
请注意 MAP 文件的最后部分——代码行信息（Line numbers information），它是以这样的形式显示的：  
  


13 0001:00000020
  
第一个数字代表在源代码中的代码行号，第二个数是该代码行在所属的代码段中的偏移量。  
  
如果要查找代码行号，需要使用下面的公式做一些十六进制的减法运算：  
  


崩溃行偏移 = 崩溃地址（Crash Address） - 基地址（ImageBase Address） - 0x1000
  
为什么要这样做呢？细心的朋友可能会留意到 Rva+Base 这栏了，我们得到的崩溃地址都是由 偏移地址（Rva）+ 基地址（Base） 得来的，所以在计算行号的时候要把基地址减去，一般情况下，基地址的值是 0x00400000 。另外，由于一般的 PE 文件的代码段都是从 0x1000 偏移开始的，所以也必须减去 0x1000 。  
  
好了，明白了这点，我们就可以来进行小学减法计算了：  
  


崩溃行偏移 = 0x0040104a - 0x00400000 - 0x1000 = 0x4a
  
如果浏览 MAP 文件的代码行信息，会看到不超过计
