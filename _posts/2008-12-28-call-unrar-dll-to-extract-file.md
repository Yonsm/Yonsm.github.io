---
date: 2008-12-28 08:35:39+00:00
layout: post
title: 调用 UnRAR.dll 解压缩RAR文件
thread: 448
categories: 代码
tags: WM 编程
---

CeleCmd 中把 TGZ 的解压缩功能用 RAR 解压缩替换了，发现RAR解压缩的代码非常简单。<!-- more -->  
  
  
#include "UnRAR.h"  
#ifdef _UNICODE  
#define _ArcName ArcNameW  
#define STR_RARProcessFile TEXT("RARProcessFileW")  
#else  
#define _ArcName ArcName  
#define STR_RARProcessFile TEXT("RARProcessFile")  
#endif  
typedef HANDLE (PASCAL *PRAROpenArchiveEx)(struct RAROpenArchiveDataEx *ArchiveData);  
typedef INT (PASCAL *PRARReadHeader)(HANDLE hArc, struct RARHeaderData *HeaderData);  
typedef INT (PASCAL *PRARProcessFile)(HANDLE hArc, INT iOperation, PTSTR pwzDestPath, PTSTR pwzDestName);  
typedef INT (PASCAL *PRARCloseArchive)(HANDLE hArc);  
HRESULT RARX(PTSTR ptzSrcFile, PTSTR ptzDstDir)  
{  
   HMODULE hLib = LoadLibrary(TEXT("UnRAR"));  
   if (hLib == NULL)  
   {  
       return ERROR_DLL_NOT_FOUND;  
   }  
  
   PRAROpenArchiveEx pRAROpenArchiveEx = (PRAROpenArchiveEx) GetProcAddress(hLib, TEXT("RAROpenArchiveEx"));  
   PRARReadHeader pRARReadHeader = (PRARReadHeader) GetProcAddress(hLib, TEXT("RARReadHeader"));  
   PRARProcessFile pRARProcessFile = (PRARProcessFile) GetProcAddress(hLib, STR_RARProcessFile);  
   PRARCloseArchive pRARCloseArchive = (PRARCloseArchive) GetProcAddress(hLib, TEXT("RARCloseArchive"));  
   if (!pRAROpenArchiveEx || !pRARReadHeader || !pRARProcessFile || !pRARCloseArchive)  
   {  
       FreeLibrary(hLib);  
       return E_NOINTERFACE;  
   }  
  
   struct RAROpenArchiveDataEx od = {0};  
   od._ArcName = ptzSrcFile;  
   od.CmtBufSize = 16384;  
   od.CmtBuf = (PSTR) UMemAlloc(od.CmtBufSize);  
   if (od.CmtBuf == NULL)  
   {  
     FreeLibrary(hLib);  
     return E_OUTOFMEMORY;  
   }  
     
   od.OpenMode = RAR_OM_EXTRACT;  
   HANDLE hArc = pRAROpenArchiveEx(&od;);  
   if (od.OpenResult == S_OK)  
   {  
       struct RARHeaderData hd = {0};  
       while ((od.OpenResult = pRARReadHeader(hArc, &hd;)) == S_OK)  
       {  
           od.OpenResult = pRARProcessFile(hArc, RAR_EXTRACT, ptzDstDir, NULL);  
           if (od.OpenResult != S_OK)  
           {  
               break;  
           }  
       }  
   }  
  
   pRARCloseArchive(hArc);  
   UMemFree(od.CmtBuf);  
   FreeLibrary(hLib);  
   return od.OpenResult;  
}  
  
  
以上代码 WM、PC 中通用，应该是通用。  
  
要注意的一点是 16384 的 CmtBuf，在官方的Example中是局部变量，如果在 PPC 调用，且你已经用了不少的话，很可能溢出（VS2008建立的工程，默认STACK才64K，调大一点也OK）。我找了好久才找到原因。改成 Heap 内存就OK了。
