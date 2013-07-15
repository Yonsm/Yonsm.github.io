---
date: 2009-03-24 03:43:29+00:00
layout: post
title: PPC 中向其它进程中插入DLL的方法及通用代码
thread: 453
categories: 文档
tags: WM 编程
---

大家都知道 PC 中写破解补丁的其中一个方法是 Loader，通常的做法是CreateProcess后用CreateRemoteThread来Load我们的DLL。但这个方法在WM中显然不可行（压根没这个API）。  
  
WM中要在指定的进程中执行我们的代码，可以用一个未公开的 PerformCallBack4 API。利用这个API，可以在目标进程中执行我们的代码。<!-- more -->  
  
首先声明：这个方法仅对于SP2003及所有PPC有效，对于SP5及其以上系统非常可能失效，因为SP的权限要求比PPC高。为了在SP5/6中具备同样的功能，需要做一系列非常复杂的操作，我也已经琢磨出相关的方案可通用的代码，说起来比较啰嗦，暂且按下不表，以后再叙吧。  
  
  
废话不多说，直接看代码：  
 STATIC HMODULE RemoteLoadLibrary(HANDLE hProcess, PCTSTR ptzPath)  
 {  
   BOOL bMode = SetKMode(TRUE);  
   DWORD dwPerm = SetProcPermissions(0xFFFFFFFF);  
  
   CALLBACKINFO ci;  
   ci.hProc= hProcess;  
   ci.pFunc = (FARPROC) MapPtrToProcess(GetProcAddress(GetModuleHandle(TEXT("COREDLL")), TEXT("LoadLibraryW")), hProcess);;  
   ci.pvArg0 = MapPtrToProcess((PVOID) ptzPath, GetCurrentProcess());  
   HMODULE hModule = (HMODULE) PerformCallBack4(&ci;, 0, 0, 0);  
  
   SetKMode(bMode);  
   SetProcPermissions(dwPerm);  
   return hModule;  
 }  
  
上面的函数中，首先设置权限，然后映射LoadLibraryW的地址到目标进程，然后在目标进程中执行LoadLibraryW装载我们的DLL。OK，既然我们的DLL都被Load到目标进城了，要干什么，请随意（一般来说，DllMain函数中创建一个线程后，立即返回。在线程中做你想做的事）。  
  
使用例子（执行一个目标进程并运行直接运行一个EXE（如果没运行，运行了则直接操作）并运行我们的DLL）：  
  
 HMODULE hModule = CCodeInj::RemoteLoadLibrary(TEXT("cprog.exe"), tzDllPath);  
 if (hModule == NULL)  
 {  
   Sleep(500);  
   PROCESS_INFORMATION pi;  
   if (CreateProcess(TEXT("cprog.exe"),, NULL, NULL, NULL, FALSE, 0, NULL, NULL, NULL, π))  
   {  
     Sleep(2000);  
  
     hModule = CCodeInj::RemoteLoadLibrary(pi.hProcess, tzDllPath);  
  
     CloseHandle(pi.hThread);  
     CloseHandle(pi.hProcess);  
   }  
 }  
  
为了更好地使用，我提供了更多的功能，请参看附件。  
  
下载附件请到：http://bbs.pediy.com/showthread.php?p=595544#post595544  
或者来信至 Yonsm@msn.cm  
  


  
1.你得准备一个 DLL，假设是 MyHook.dll  
2 另有一个代码执行的空间（无论是EXE还是DLL，也可以在 MyHook.dll），然后在这个代码空间执行：RemoteLoadLibrary  
  指定远程进程（比如 cprog.exe，就是你要插入的进程），和DLL路径（就是MyHook.dll的路径）  
3. 那么，RemoteLoadLibrary就会让 crpog.exe 来 LoadLibrary(MyHook.dll)，你在MyHook.dll里面就可以做你想做的事。  


  
  

