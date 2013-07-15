---
date: 2004-10-13 03:23:41+00:00
layout: post
title: Pure C++ 实现 Shell Context Menu Extention
thread: 147
categories: 代码
---

纯 C++ 实现的 Shell 上下文菜单扩展，既是一个小例子。也是一个很好的模板。

  


用 Visual C++ 建立一个空的 DLL 工程，加入附件中的两个文件，编译注册即可。

  


有关 Shell 扩展编程，这里有个详细的 CHM 文档: [http://www.vckbase.com/tools/downtools.asp?id=105](http://www.vckbase.com/tools/downtools.asp?id=105)

  
附件下载：[CxtMenu](/assets/1097580159.rar)

  


<!-- more -->  

    
    ////////////////////////////////////////////////////////////////////////////////////////////////////<br></br> // 文件: CxtMenu.h<br></br> // 更新: 2003.7.1<br></br> ////////////////////////////////////////////////////////////////////////////////////////////////////<br></br> <br></br> <br></br> <br></br> ////////////////////////////////////////////////////////////////////////////////////////////////////<br></br> // 编译预处理<br></br> #pragma once<br></br> #include <br></br> #include <br></br> <br></br> // 导出函数<br></br> #pragma comment(linker, "/EXPORT:DllRegisterServer=_DllRegisterServer@0,PRIVATE")<br></br> #pragma comment(linker, "/EXPORT:DllUnregisterServer=_DllUnregisterServer@0,PRIVATE")<br></br> #pragma comment(linker, "/EXPORT:DllGetClassObject=_DllGetClassObject@12,PRIVATE")<br></br> #pragma comment(linker, "/EXPORT:DllCanUnloadNow=_DllCanUnloadNow@0,PRIVATE")<br></br> ////////////////////////////////////////////////////////////////////////////////////////////////////<br></br> <br></br> <br></br> <br></br> ////////////////////////////////////////////////////////////////////////////////////////////////////<br></br> //  CCxtMenuFactory 类声明<br></br> class CCxtMenuFactory : public IClassFactory  <br></br> {<br></br> public:<br></br>   CCxtMenuFactory();<br></br>   ~CCxtMenuFactory();<br></br> <br></br>   // IUnknown<br></br>   ULONG WINAPI AddRef();<br></br>   ULONG WINAPI Release();<br></br>   HRESULT WINAPI QueryInterface(REFIID rIID, void ** ppvObject);<br></br> <br></br>   // IClassFactory<br></br>   HRESULT WINAPI CreateInstance(IUnknown * pUnknown, REFIID rIID, void ** ppvObject);<br></br>   HRESULT WINAPI LockServer(BOOL bLock);<br></br> <br></br> protected:<br></br>   // 引用计数器<br></br>   int m_iRefCount;<br></br> };<br></br> ////////////////////////////////////////////////////////////////////////////////////////////////////<br></br> <br></br> <br></br> <br></br> <br></br> ////////////////////////////////////////////////////////////////////////////////////////////////////<br></br> // <br></br> class CCxtMenu : public IShellExtInit, public IContextMenu<br></br> {<br></br> public:<br></br>   CCxtMenu();<br></br>   ~CCxtMenu();<br></br> <br></br>   // IUnknown 方法<br></br>   ULONG WINAPI AddRef();<br></br>   ULONG WINAPI Release();<br></br>   HRESULT WINAPI QueryInterface(REFIID rIID, void ** ppvObject);<br></br> <br></br>   // IShellExtMenuInit 方法<br></br>   HRESULT WINAPI Initialize(LPCITEMIDLIST pidlFolder, IDataObject * pDataObj, HKEY hProgID);<br></br> <br></br>   // IContextMenu 方法<br></br>   HRESULT WINAPI QueryContextMenu(HMENU hMenu, UINT indexMenu,<br></br>     UINT idCmdFirst, UINT idCmdLast,UINT uFlags);<br></br>   HRESULT WINAPI GetCommandString(UINT_PTR idCmd,UINT uFlags,<br></br>     UINT * pwReserved, LPSTR pszName, UINT cchMax);<br></br>   HRESULT WINAPI InvokeCommand(LPCMINVOKECOMMANDINFO pCmdInfo);<br></br> <br></br> protected:<br></br>   // 引用计数器<br></br>   int m_iRefCount;<br></br>   char m_szFileName[MAX_PATH];<br></br> <br></br> };<br></br> ////////////////////////////////////////////////////////////////////////////////////////////////////<br></br> 
