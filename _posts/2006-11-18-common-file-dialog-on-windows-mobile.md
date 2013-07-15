---
date: 2006-11-18 11:23:29+00:00
layout: post
title: Windows Mobile 下面最通用的浏览文件对话框
thread: 276
categories: 文档
tags: 编程
---

M$ Windows Mobile 一大不爽的东西就是 GetOpenFileName 和 GetSaveFileName 函数非常的乱：WM5 上提供了一个 GetOpenFileNameEx 来浏览图片；PPC2003/WM5 下极其简单，只能使用非常浅的文件夹（虽然设计上的考虑，但也太滥了）；SP2003 下压根就没有这些函数。于是只好自己写可以个函数非常通用的函数，Windows Mobile 2003/5.0 SP/PPC 下均可正常运行并获得最佳体验。  
  
补充一下标题，还是最懒的方法，真正的东西一点都不写：）  
  
支持一下功能：  

* 简单的参数
  

* 保存最后文件夹位置（似乎 RFileShell 不响应咱的请求）
  

* 根据不同的运行环境，自动使用最佳的浏览对话框函数
  
  
策略：  

* 如果找到 Resco 的 RFileShell.dll （安装过 Resco Explorer、PhotoViewer 等软件），则使用RFileShell.dll 的浏览文件函数。它的是最棒的，精神奖励一下！
  

* 其次，使用 Windows Mobile 5.0 的 GetOpenFileNameEx，只有打开，没有保存的
  

* 再次，使用 tGetFile 的函数，我都做好了完美本地化了
  

* 最后，使用 CoreDll 的 GetOpenFileName 和 GetSaveFileName 
  

* 实在不行了，又在 Smartphone 2003 下，提示一下用户去下载 RFileShell 或 tGetFile 吧，简单地返回 \\My Documents\AppName.Ext 的文件名吧，顺便问问用户是否接受：）
  
  
真是不费一枪一弹啊……<!-- more -->  
  
以下代码，版权所有 (C) Yonsm.NET，保留所有权利。  
如需在程序中使用，请留言或发送 Mail 告知。  
  
[codes=cpp]  
// 资源  
IDS_Open "打开"  
IDS_Save "保存"  
IDS_GetFileName "没有找到浏览文件名功能的函数库，要使用“%s”作为文件名吗?。\n\n提示: 您可以从下列网站中获得相关的函数库:\n\nRFileShell: http://www.resco.net/downloads/byplatforms.asp\n\ntGetFile:\thttp://www.tillanosoft.com/ce/tgetfile.html"  
  
// CReg  
// STR_AppName  
.....  
[/codes]  
  
  
[codes=cpp]  
// Declaration  
#if (_WIN32_WCE < 0x500)  
typedef struct tagOPENFILENAMEEX  
{  
   // Fields which map to OPENFILENAME  
   DWORD        lStructSize;  
   HWND         hwndOwner;  
   HINSTANCE    hInstance;  
   LPCTSTR      lpstrFilter;  
   LPTSTR       lpstrCustomFilter;  
   DWORD        nMaxCustFilter;  
   DWORD        nFilterIndex;  
   LPTSTR       lpstrFile;  
   DWORD        nMaxFile;  
   LPTSTR       lpstrFileTitle;  
   DWORD        nMaxFileTitle;  
   LPCTSTR      lpstrInitialDir;  
   LPCTSTR      lpstrTitle;  
   DWORD        Flags;  
   WORD         nFileOffset;  
   WORD         nFileExtension;  
   LPCTSTR      lpstrDefExt;  
   LPARAM       lCustData;  
   LPOFNHOOKPROC lpfnHook;  
   LPCTSTR      lpTemplateName;  
  
   // Extended fields  
   DWORD       dwSortOrder;  
   DWORD       ExFlags;  
}  
OPENFILENAMEEX, *LPOPENFILENAMEEX;  
  
// Sort order  
typedef enum tagOFN_SORTORDER  
{  
   OFN_SORTORDER_AUTO,  
   OFN_SORTORDER_DATE,  
   OFN_SORTORDER_NAME,  
   OFN_SORTORDER_SIZE,  
   OFN_SORTORDER_ASCENDING = 0x00008000  
  
}  
OFN_SORTORDER;  
  
// Extended Flags  
typedef enum tagOFN_EXFLAG  
{  
   OFN_EXFLAG_DETAILSVIEW          = 0x00000001,  
   OFN_EXFLAG_THUMBNAILVIEW        = 0x00000002,  
   OFN_EXFLAG_LOCKDIRECTORY        = 0x00000100,  
   OFN_EXFLAG_NOFILECREATE         = 0x00000200,  
   OFN_EXFLAG_HIDEDRMPROTECTED     = 0x00010000,  
   OFN_EXFLAG_HIDEDRMFORWARDLOCKED = 0x00020000  
}  
OFN_EXFLAG;  
#endif  
  
typedef BOOL (*PGETFILENAME)(LPOPENFILENAMEEX pOfn);  
typedef BOOL (*TGETFILENAME)(BOOL bSave, LPOPENFILENAMEEX pOfn);  
  
// Module name and procedure table  
enum {MP_RFileShell, MP_AygShell, MP_tGetFile, MP_CoreDll};  
const struct {PCTSTR ptzModName; PCTSTR ptzOpenProc; PCTSTR ptzSaveProc;} c_sModProc[] =  
{  
   {TEXT("RFileShell"), TEXT("RShellGetOpenFileName"), TEXT("RShellGetSaveFileName")},  
   {TEXT("AygShell"), TEXT("GetOpenFileNameEx"), TEXT("GetSaveFileNameEx")},  
   {TEXT("tGetFile"), TEXT("tGetFile"), TEXT("tGetFile")},  
   {TEXT("CoreDll"), TEXT("GetOpenFileNameW"), TEXT("GetSaveFileNameW")},  
};  
  
[/codes]  
  
  
[codes=cpp]  
  
// Browse for file name  
#define OFN_COMMON (0x11000000 | OFN_HIDEREADONLY)  
BOOL CHelper::GetFileName(HWND hParent, PTSTR ptzPath, UINT uFilterRes, BOOL bSave)  
{  
   // Fill structure  
   OPENFILENAMEEX ofn = {0};  
   ofn.hwndOwner = hParent;  
   ofn.hInstance = g_hInst;  
   ofn.lpstrFile = ptzPath;  
   ofn.nMaxFile = MAX_PATH;  
   ofn.Flags = bSave ? (OFN_COMMON | OFN_OVERWRITEPROMPT) : (OFN_COMMON | OFN_PATHMUSTEXIST);  
  
   ofn.ExFlags = OFN_EXFLAG_THUMBNAILVIEW;  
   ofn.dwSortOrder = OFN_SORTORDER_NAME | OFN_SORTORDER_ASCENDING;  
  
   // Get initialize folder from control  
   TCHAR tzPath[MAX_PATH];  
   if (_IsIntRes(ptzPath))  
   {  
       ofn.lpstrFile = tzPath;  
       GetDlgItemText(hParent, (UINT) ptzPath, tzPath, MAX_PATH);  
   }  
  
   // Load extension filter  
   TCHAR tzFilter[MAX_PATH];  
   _LoadStr(uFilterRes, tzFilter);  
   ofn.lpstrFilter = UStrRep(tzFilter, '|', 0);  
  
   // Parse default extension  
   TCHAR tzDefExt[MAX_NAME];  
   PTSTR p = UStrChr(tzFilter, 0) + 1;  
   if (p = UStrChr(p, '.'))  
   {  
       UStrCopy(tzDefExt, p);  
       if (p = UStrChr(tzDefExt, ';')) *p = 0;  
       ofn.lpstrDefExt = tzDefExt;  
   }  
  
   // Read initialize folder  
   CReg reg;  
   TCHAR tzInitDir[MAX_PATH];  
   if (reg.GetStr(TEXT("InitDir"), tzInitDir))  
   {  
       ofn.lpstrInitialDir = tzInitDir;  
   }  
   else  
   {  
       ofn.lpstrInitialDir = TEXT("\\");  
   }  
  
   // Get title  
   TCHAR tzTitle[MAX_NAME];  
   ofn.lpstrTitle = _LoadStr(bSave ? IDS_Save : IDS_Open, tzTitle);  
  
   // Try all library  
   UINT i = 0;  
   BOOL bResult = FALSE;  
   for (; i < _NumOf(c_sModProc); i++)  
   {  
       HMODULE hModule = LoadLibrary(c_sModProc_.ptzModName);  
       if ((hModule == NULL) && (i == MP_RFileShell))  
       {  
           // Lookup Resco Explorer install folder  
      &nbs;
p;    TCHAR tzModule[MAX_PATH];  
           CReg rfs(TEXT("SOFTWARE\\Apps\\Resco Explorer"), HKEY_LOCAL_MACHINE);  
           if (rfs.GetStr(TEXT("InstallDir"), tzModule))  
           {  
               UDirMakePath(tzModule, c_sModProc_.ptzModName);  
               hModule = LoadLibrary(tzModule);  
           }  
       }  
       if (hModule)  
       {  
           PGETFILENAME pGetFileName = (PGETFILENAME) GetProcAddress(hModule, bSave ? c_sModProc_.ptzSaveProc : c_sModProc_.ptzOpenProc);  
           if (pGetFileName)  
           {  
               ofn.lStructSize = (i == MP_AygShell) ? sizeof(OPENFILENAMEEX) : sizeof(OPENFILENAME);  
               bResult = (i == MP_tGetFile) ? ((TGETFILENAME) pGetFileName)(bSave, &ofn;) : pGetFileName(&ofn;);  
               FreeLibrary(hModule);  
               break;  
           }  
           FreeLibrary(hModule);  
       }  
   }  
  
   // Prompt for library  
   if ((i == MP_CoreDll) && !IsPPC() && !IsWM5() && !bResult)  
   {  
       TCHAR tzStr[MAX_PATH];  
       TCHAR tzInfo[MAX_STR];  
       UStrPrint(ofn.lpstrFile, TEXT("\\My Documentss\\%s.%s"), STR_AppName, ofn.lpstrDefExt);  
       UStrPrint(tzInfo, _GetStr(IDS_GetFileName), ofn.lpstrFile);  
       bResult = (MessageBox(hParent, tzInfo, tzTitle, MB_ICONQUESTION | MB_YESNO) == IDYES);  
   }  
  
   if (bResult)  
   {  
       // Set control text  
       if (_IsIntRes(ptzPath))  
       {  
           SetFocus(GetDlgItem(hParent, (UINT) ptzPath));  
           SetDlgItemText(hParent, (UINT) ptzPath, tzPath);  
       }  
  
       // Save initialize folder  
       p = UStrRChr(ofn.lpstrFile, '\\');  
       if (p)  
       {  
           *p = 0;  
           reg.SetStr(TEXT("InitDir"), ofn.lpstrFile);  
           *p = '\\';  
       }  
   }  
  
   return bResult;  
[/codes] 
