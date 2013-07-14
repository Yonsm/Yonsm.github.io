---
author: Yonsm
comments: true
date: 2007-03-14 05:43:31+00:00
layout: post
slug: reprint-cross-process-memory-into-windwos-ce-pocketpc
title: 【转载】Windwos CE 跨进程内存注入（PocketPC）
wordpress_id: 296
categories:
- 文档
---

　　近日，由于程序设计需要，我对WincowsCE 的[内存](YJWX/ShowClass.asp?ClassID=182)布局进行了研究，由于发现国内在这方面的文档资料较少，于是在研究告一段落之际，形成这篇示例文档，以望抛砖引玉，得到别的高手的指正。  
  
　　**一、程序实现的先决条件**  
  
　　由于windows系统的窗体消息总是投递至一个特定进程的指定窗体消息函数中。于是在本地进程（自己的应用程序）中取得属于其它进程的窗体的消息必须实现以下两个部分：  
  
　　1、将需要挂接窗体的代码放到目标进程的地址空间中去。  
  
　　2、执行这一段代码，并获得目标进程窗体的消息。  
  
　　这两步看起来很简单，但在实现过程中就比较困难。由于Windows CE作为嵌入式移动设备[操作系统](CZXT/Index.asp)，与windows 98/2000/XP等桌面[操作系统](CZXT/Index.asp)在内核的设计理念以及API的支持上有极大的区别。这就直接导致了常规的桌面系统利用全局鼠标钩子注入/远程线程注入等方法在CE中完全得不通。不过可喜的是，微软在开发工具中提供的remotexxx等远程调试程序使我清楚这个目标并不是不可能的任务，微软既然可以做到，那就是说在CE的内部一定有一套完整的跨进程[内存](YJWX/ShowClass.asp?ClassID=182)访问/代码注入的机制。  
  
　　**二、程序实现的基本原理**  
  
　　经过两天的google 搜索，在网上我发现了一个没有在微软文档中声明的有趣的API函数：PerformCallBack4，传说中这个函数可以在自己的应用程序中执行指定的进程中的一个函数，So Cool!这好象正是我所需要的东西。虽然网上也传闻这个函数在wm5不受支持，其实经过实践这个传闻只是谣传而已！  
  
　　PerformCallBack4函数的定义：<!-- more -->  
  
[DllImport("coredll.dll")]  
public static extern uint PerformCallBack4(ref CallBackInfo CallBackInfo,  
IntPtr ni_pVoid1,IntPtr ni_pVoid2,IntPtr ni_pVoid3);  
  
　　其中函数的参数CallBackInfo结构定义:  
  
[StructLayout(LayoutKind.Sequential)]  
public struct CallBackInfo  
{  
public IntPtr hProc; //远程的目标进程  
public IntPtr pfn; //指向远程目标进程的函数地址的指针  
public IntPtr pvArg0; //函数的需要的第一个参数  
}//end struct  
  
　　而PerformCallback4的 ni_pVoid1、ni_pVoid2、ni_pVoid3为传递到远程目标进程执行函数的其它三个参数。  
  
　　至于将代码放到目标进程的[内存](YJWX/ShowClass.asp?ClassID=182)空间，我们可以利用CE设计上的一个特性：  
  
　　1、为了节约[内存](YJWX/ShowClass.asp?ClassID=182)使用，CE将所有程序调用的动态链接库（DLL）都映射到同一个[内存](YJWX/ShowClass.asp?ClassID=182)地址中。  
  
　　2、CE的[内存](YJWX/ShowClass.asp?ClassID=182)布局中划分有一个slot0的[内存](YJWX/ShowClass.asp?ClassID=182)位置，这个[内存](YJWX/ShowClass.asp?ClassID=182)位置是由正在执行的进程所占有的，每一个特定的时间片，只能有一个进程可以占有这个[内存](YJWX/ShowClass.asp?ClassID=182)空间。在进程要求执行时，系统并不直接执行进程所处内存位置的代码，而是将该进程的执行代码复制到slot0的内存位置中产生一个副本执行。也就是说进程在执行时内存将会有进程执行代码的两个完全一样的版本：存在于slot0中正在执行的进程代码和进程本身所处的内存中的代码。  
  
　　在这个特性下，可以得到结论：如果进程A通过LoadLibrary函数装载Test.dll，而进程B也通过LoadLibrary函数装载同一个Test.dll，这个Test.dll的所有函数在进程A和进程B中执行时，相对于slot0中的进程执行代码都会得到同一地址。  
  
　　3、在CE中，系统在内存中划分出33个slot，slot0保留给正在执行的进程，然后在进程启动时将所有的代码放到除slot0以外的一个slot中（这就是臭名昭著的CE系统中内存最多只能有不多于32个程序执行的限制的来由）。在进程执行时，每个应用程序的内存访问默认只能访问slot0内存空间中的地址以及进程所处的slot内存空间的地址。 但为使设备驱动程序可以访问到它们所需的其它应用程序数据，CE提供了两个函数以打破这个限制，SetKmode和SetProcPermission，SetKmode函数告诉系统，当前运行的进程是否需要在内核模式中执行；SetProcPermission函数可以接受一个位掩码，每一位代码一个slot的访问控制，1代表可以访问该slot的内存内容。0表示不能访问该slot的内存内容。这两个函数在msdn中有帮助文档，可参阅msdn的文档说明。  
  
　　本文我们对实现的原理进行了剖析，在下一篇文章中我们将以一个小示例程序演示实现的全过程。   
  


* * *

  
在文章《浅析Windows CE跨进程内存注入实现窗体消息挂接（上）》中，我们已经得到了这个七巧板游戏所需要的所有小板块，剩下的事就是等待我们按一定顺序将合适的板块放到合适的位置，本章我们开始进行真刀真枪的实战演练。

程序目标：捕获explore窗体（也就是程序窗体的消息并输出到WinProcInfo.txt中）

程序的执行步骤设计如下：

1、编写一个窗体消息挂接DLL，这个DLL提供一个，函数中利用setwindowlong函数将窗体的默认消息处理过程改为这个挂接DLL中定义的一个窗体过程。

2、在C#程序中利用findwindow等API函数获得exlore类窗体的句柄及窗体所属的进程，并使用performcallback4在目标进程空间中执行coredll.dll的loadLibrary函数将我们写的挂接dll放到目标进程中。

3、在C#程序中使用performcallback4在目标进程空间中执行挂接DLL提供的导出接口函数实现跨进程窗体消息截获.

**一、程序的实现如下：**

在VS2005中建立一个智能设备的MFC DLL，命名为HookWindowsProcMFCDLL。

在HookWindowsProcMFCDLL.cpp中进行挂接DLL的核心编码： 

LRESULT CALLBACK fnHookWindowProc(HWND hwnd,UINT msg,WPARAM wparam, LPARAM lparam);

int __declspec(dllexport) WINAPI fnAttachWinProc(HWND ni_hAttatchWin,PVOID ,PVOID,PVOID);

int __declspec(dllexport) WINAPI fnDetachWinMsgProc(HWND ni_hDetachWin);

WNDPROC tpOldWindowProc; 

FILE *m_pDebugOutputFile;

//将一个窗体消息处理挂接到net精简版MessageWindow对象上的代码  
typedef struct  
{   
　WNDPROC OldWinProc;//保留窗体原始消息处理过程的函数指针  
　HWND WindowHandle;//保存net精简版中对应的窗口挂接的MessageWindow对象的句柄  
} DEFUDT_AttachWinInfo; //end struct

CMap<HWND,HWND,DEFUDT_AttachWinInfo,DEFUDT_AttachWinInfo> m_aAttachWinInfoMap;

//对指定的窗口进程进行挂接  
int __declspec(dllexport) WINAPI fnAttachWinProc(HWND ni_hAttatchWin,  
PVOID ni_0,  
PVOID ni_1,  
PVOID ni_2 )  
{  
　DEFUDT_AttachWinInfo tudtAttachWinInfo;  
　m_pDebugOutputFile = fopen("\\Storag
e Card\\WinProcInfo.txt", "w");  
　WNDPROC tpOldWindowProc=(WNDPROC)::SetWindowLong(ni_hAttatchWin, GWL_WNDPROC,(LONG) fnHookWindowProc );  
　fprintf(m_pDebugOutputFile,"Attatch successfully! OldWindowProc: %08X\n",tpOldWindowProc);  
　tudtAttachWinInfo.OldWinProc=tpOldWindowProc ;  
　tudtAttachWinInfo.WindowHandle=ni_hAttatchWin;  
　m_aAttachWinInfoMap.SetAt(ni_hAttatchWin,tudtAttachWinInfo);  
　fclose(m_pDebugOutputFile);  
　return 77;// (int)tpOldWindowProc ;  
}//end function

int __declspec(dllexport) WINAPI fnDetachWinMsgProc(HWND ni_hDetachWin)  
{  
　DEFUDT_AttachWinInfo tudtAttachWinInfo;  
　WNDPROC tpOldWindowProc;

　//取得在ncf中消息接收窗口对应的原始消息处理函数的函数指针  
　m_aAttachWinInfoMap.Lookup(ni_hDetachWin,tudtAttachWinInfo) ;

　//将窗体的消息处理函数设为默认的处理过程  
　tpOldWindowProc =(WNDPROC) SetWindowLong(ni_hDetachWin,GWL_WNDPROC , (LONG)tudtAttachWinInfo.OldWinProc);

　//将挂接信息消息处理映谢类中删除  
　m_aAttachWinInfoMap.RemoveKey(ni_hDetachWin);

　return (int)tpOldWindowProc ;

}//end function

  
LRESULT CALLBACK fnHookWindowProc(HWND hwnd,UINT msg,WPARAM wparam, LPARAM lparam)  
{  
　DEFUDT_AttachWinInfo tudtAttachWinInfo;  
　m_aAttachWinInfoMap.Lookup(hwnd,tudtAttachWinInfo) ;  
　m_pDebugOutputFile = fopen("\\Storage Card\\WinProcInfo.txt", "a");  
　if (m_pDebugOutputFile!=NULL)  
　{  
　　fprintf(m_pDebugOutputFile,"HWND: %08X Msg: %08X Wparam %08X Lparam %08X \n",  
hwnd,msg,wparam,lparam);

　}//EHD IF

　fclose(m_pDebugOutputFile);  
　//tudtAttachWin=maatt  
　LRESULT tobjResult= ::CallWindowProc(tudtAttachWinInfo.OldWinProc ,hwnd,msg,wparam,lparam);  
　return tobjResult;  
}//end function   


而在C#的主程序中，我们使用这个DLL挂接explore类的程序窗体，以下给出挂接部分的代码：

int m_hTargetWindow;//要挂接的目标窗体句柄  
IntPtr m_hTargetProcess;//目标窗体所属的进程  
IntPtr m_hModule; //挂接DLL的句柄

private void Form1_Load(object sender, EventArgs e)  
{  
　IntPtr tpTemp = IntPtr.Zero, tpTempa = IntPtr.Zero;  
　uint tuntApiRet;

　m_hTargetWindow = (int)clsCECoreAPI.FindWindow("Explore", null );//资源管理器 0x0013e800;

　//挂接指定的进程窗体消息  
　IntPtr thCurrentProcess = clsCECoreAPI.GetCurrentProcess();  
　m_hTargetProcess=IntPtr.Zero ;// (IntPtr) (unchecked((int)0xedd84e4a));  
　tuntApiRet= clsCECoreAPI.GetWindowThreadProcessId(new IntPtr(unchecked((int) m_hTargetWindow)),  
ref m_hTargetProcess);

　string tstrArgument;  
　tstrArgument = "\\Program Files\\processinject\\HookWindowsProcMFCDLL.dll";// HookWindowsProcMFCDLL.dll";  
　IntPtr tpArg0;

　int tintOriginalKMode = clsCECoreAPI.SetKMode(1);  
　int tintOriginalProcPermission = (int)clsCECoreAPI.SetProcPermissions(0xffffffff);

　IntPtr tpFuncProc = clsCECoreAPI.GetProcAddress(clsCECoreAPI.GetModuleHandle("coredll.dll"), "LoadLibraryW");

　CallBackInfo tudtCALLBACKINFO;

　tpArg0 = clsCECoreAPI.MapPtrToProcess(tstrArgument, thCurrentProcess);

　tudtCALLBACKINFO.hProc = m_hTargetProcess;// Proc;  
　tudtCALLBACKINFO.pfn = clsCECoreAPI.MapPtrToProcess(tpFuncProc, m_hTargetProcess);  
　tudtCALLBACKINFO.pvArg0 = tpArg0;  
　m_hModule =new IntPtr(unchecked(  
(int) clsCECoreAPI.PerformCallBack4(ref tudtCALLBACKINFO,IntPtr.Zero,IntPtr.Zero,IntPtr.Zero )));  
　//clsCECoreAPI.Sleep(1000);

　IntPtr thModule = clsCECoreAPI.LoadLibrary("HookWindowsProcMFCDLL.dll");  
　tpFuncProc = clsCECoreAPI.GetProcAddress(thModule, "fnAttachWinProc");

　tpArg0 = (IntPtr) m_hTargetWindow;// clsCECoreAPI.MapPtrToProcess(ref thTargetWindow, thCurrentProcess);

　tudtCALLBACKINFO.hProc = m_hTargetProcess;  
　tudtCALLBACKINFO.pfn = clsCECoreAPI.MapPtrToProcess(tpFuncProc, m_hTargetProcess);  
　tudtCALLBACKINFO.pvArg0 = tpArg0 ;  
　tuntApiRet = clsCECoreAPI.PerformCallBack4(ref tudtCALLBACKINFO,IntPtr.Zero,IntPtr.Zero,IntPtr.Zero );  
　//clsCECoreAPI.Sleep(5000);  
}

[DllImport("HookWindowsProcMFCDLL.dll")]  
public static extern int fnAttachWinProc(IntPtr ni_hAttatchWin);

[DllImport("HookWindowsProcMFCDLL.dll")]  
public static extern int fnDetachWinMsgProc(IntPtr ni_hDetachWin); 

取消挂接的代码根据上述代码很容易就可以建立，不再细叙。

注：clsCECoreAPI的函数全是封装的标准CE API，由于这些API在msdn 中都有详细的文档注释，因篇幅所限，不再将代码一一列举.

在执行这个程序时，将模拟器的共享路径设为PC机的桌面，这样模拟器的storage card目录就等同桌面了，点模拟器的开始菜单，选程序，你就可以看到explore窗体的消息都输出到桌面的WinProcInfo.txt文件中了，运行结果如下：  
  
　![](http://www.uml.org.cn/embeded/images/42c0m7vf8195s.jpg)　   
  
　目前本程序只在PPC2003/wm5 for PPC测试通过,由于smartphone系统在编译时使用了和ppc系统不同的机制，内存运作不明，本程序在smartphone上无法正确运行，有好的建议的话请指教一二,谢谢. 

  
作者：莫艺潜  
转自：[http://cqreview.yesky.com/dev/185/2590685.shtml](http://cqreview.yesky.com/dev/185/2590685.shtml)  
点评：好！一条路
