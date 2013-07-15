---
date: 2009-04-25 19:15:22+00:00
layout: post
title: Windows Mobile SP/PPC 中 Menu Bar 使用完美方案
thread: 456
categories: 文档
tags: WM 编程
---

在SP/PPC写过MenuBar代码的人可能都知道，AygShell 中 Menu Bar 的设计真是无话说，各种系统（SP、PPC、2003、5.0）功能差异不一致，导致编程特别不方便。比如 SP2003 中不能使用 SHCMBF_HMENU 标记，PPC 5.0/6.0 终不能使用 SHCMBM_GETMENU，SP/PPC 2003中不能使用 TBIF_BYINDEX 来操作按钮，等等。  
  
在别扭与愤懑中，用着MenuBar都过了4年了。终于整理出了一套相对比较完美的方案。先做一些假定：<!-- more -->  
  
1.  如果我们的代码用 SP2003 SDK 编译，则必须支持 SP/PPC 2003/5 (这里5.0的意思包含5.0和之后的版本，因为5以后都比较完美统一)。  
2.  用 PPC2003 SDK 编译的话，必须要支持 PPC 2003/5.0。  
3.  用 SP5 SDK编译的话，支持SP5/PPC5。  
4.  用 PPC 5 编译的话，只支持 PPC5。  
  
基于以下假定，我整理了一个小的CeleMenuBar类，在使用的时候，只要：  
  
1.  在资源中定义 IDC_LSK 和 IDC_RSK （=IDC_LSK+1），用于定义左右按钮的命令ID。  
2.  在资源中添加一个菜单，如果不是Popup按钮，则用 IDC_LSK 或 IDC_RSK作为命令。  
3.  如果你的代码需要支持 2003，则请在资源中定义 MenuBar 的 RCDATA；如果只需要支持5.0，则不需要。  
  
4. 在代码中，使用 CeleMenuBar，操作所有的MenuBar按钮都不用管命令ID，只需要指明是左按钮还是右按钮。  
5. 在代码中，如果需要响应按钮命令，请使用 IDC_LSK 和 IDC_RSK；如果是弹出菜单，无视 。  
  
基于以上几个规则，代码写起来就简单多了。  
  
// CeleMenuBar  
#ifndef IDC_LSK  
#ifndef TBIF_BYINDEX  
#pragma message("CeleMenuBar: IDC_LSK is not defined. You should use IDOK & IDCANCEL as soft key command.")  
#endif  
#define IDC_LSK         IDOK  
#define IDC_RSK         IDCANCEL  
#endif  
#if TBIF_BYINDEX  
#define _MBIF(x)        ((x) | TBIF_BYINDEX)  
#define _MBID(x)        (x)  
#else  
#define _MBIF(x)        (x)  
#define _MBID(x)        (IDC_LSK + (x))  
#endif  
class CeleMenuBar  
{  
protected:  
   HWND m_hMenuBar;  
  
public:  
   CeleMenuBar(HWND hMenuBar = NULL)  
   {  
       m_hMenuBar = hMenuBar;  
   }  
  
   operator HWND()  
   {  
       return m_hMenuBar;  
   }  
  
   HWND operator =(HWND hMenuBar)  
   {  
       return m_hMenuBar = hMenuBar;  
   }  
  
   // 创建菜单条  
   HWND Create(HWND hParent, UINT uBarRes = 0, DWORD dwFlags = 0)  
   {  
       SHMENUBARINFO mb = {0};  
       mb.cbSize = sizeof(SHMENUBARINFO);  
       mb.hwndParent = hParent;  
       mb.hInstRes = g_hInst;  
       mb.nToolBarId = uBarRes;  
       if (uBarRes)  
       {  
#ifdef TBIF_BYINDEX  
           mb.dwFlags = dwFlags | SHCMBF_HMENU;  
#else  
           mb.dwFlags = dwFlags;  
#endif  
       }  
       else  
       {  
           mb.dwFlags = SHCMBF_EMPTYBAR;  
       }  
       SHCreateMenuBar(&mb;);  
       _Assert(mb.hwndMB);  
       return m_hMenuBar = mb.hwndMB;  
   }  
  
   // 获取弹出菜单  
   HMENU GetMenu(BOOL bRight = TRUE)  
   {  
#ifdef TBIF_BYINDEX  
       TBBUTTON tb;  
       tb.dwData = NULL;  
       SendMessage(m_hMenuBar, TB_GETBUTTON, _MBID(bRight), (LPARAM) &tb;);  
       return (HMENU) tb.dwData;  
#else  
       return (HMENU) SendMessage(m_hMenuBar, SHCMBM_GETSUBMENU, 0, _MBID(bRight));  
#endif  
   }  
  
   // 重载按键  
   DWORD OverrideKey(WPARAM wParam = VK_TBACK)  
   {  
       return SendMessage(m_hMenuBar, SHCMBM_OVERRIDEKEY, wParam, MAKELPARAM(SHMBOF_NODEFAULT | SHMBOF_NOTIFY, SHMBOF_NODEFAULT | SHMBOF_NOTIFY));  
   }  
  
   // 获取按钮文字  
   BOOL GetButtonText(PTSTR ptzStr, BOOL bRight = TRUE)  
   {  
       TBBUTTONINFO tb;  
       tb.cbSize = sizeof(TBBUTTONINFO);  
       tb.dwMask = _MBIF(TBIF_TEXT);  
       tb.pszText = ptzStr;  
       tb.cchText = MAX_PATH;  
       return SendMessage(m_hMenuBar, TB_GETBUTTONINFO, _MBID(bRight), (LPARAM) &tb;);  
   }  
  
   // 设置按钮文字  
   BOOL SetButtonText(PCTSTR ptzStr, BOOL bRight = TRUE)  
   {  
       TBBUTTONINFO tb;  
       tb.cbSize = sizeof(TBBUTTONINFO);  
       tb.dwMask = _MBIF(TBIF_TEXT);  
       tb.pszText = (PTSTR) ptzStr;  
       return SendMessage(m_hMenuBar, TB_SETBUTTONINFO, _MBID(bRight), (LPARAM) &tb;);  
   }  
  
   // 获取按钮状态  
   BYTE GetButtonState(BOOL bRight = TRUE)  
   {  
       TBBUTTONINFO tb;  
       tb.cbSize = sizeof(TBBUTTONINFO);  
       tb.dwMask = _MBIF(TBIF_STATE);  
       SendMessage(m_hMenuBar, TB_GETBUTTONINFO, _MBID(bRight), (LPARAM) &tb;);  
       return tb.fsState;  
   }  
  
   // 设置按钮状态  
   BOOL SetButtonState(BYTE bState = TBSTATE_ENABLED, BOOL bRight = TRUE)  
   {  
       TBBUTTONINFO tb;  
       tb.cbSize = sizeof(TBBUTTONINFO);  
       tb.dwMask = _MBIF(TBIF_STATE);  
       tb.fsState = bState;  
       return SendMessage(m_hMenuBar, TB_SETBUTTONINFO, _MBID(bRight), (LPARAM) &tb;);  
   }  
  
   // 启用或禁用按钮  
   BOOL EnableButton(BOOL bEnable = TRUE, BOOL bRight = TRUE)  
   {  
       return SetButtonState(bEnable ? TBSTATE_ENABLED : 0, bRight);  
   }  
  
   // 显示或隐藏按钮  
   BOOL HideButton(BOOL bHide = TRUE, BOOL bRight = TRUE)  
   {  
       return SetButtonState(bHide ? TBSTATE_HIDDEN : 0, bRight);  
   }  
  
   // 弹出菜单，用于需要动态切换弹出菜单的情况  
   BOOL PopupMenu(HMENU hMenu, BOOL bRight = TRUE)  
   {  
       BYTE bState = GetButtonState(bRight);  
       if (bState & TBSTATE_PRESSED)  
       {  
           keybd_event(VK_ESCAPE, 0, KEYEVENTF_SILENT, 0);  
           keybd_event(VK_ESCAPE, 0, KEYEVENTF_SILENT | KEYEVENTF_KEYUP, 0);  
       }  
       else  
       {  
           RECT rt;  
           GetWindowRect(m_hMenuBar, &rt;);  
           SetButtonState(bState | TBSTATE_PRESSED, bRight);  
           TrackPopupMenuEx(hMenu, bRight ? (TPM_RIGHTALIGN | TPM_BOTTOMALIGN) : (TPM_LEFTALIGN | TPM_BOTTOMALIGN),   
               bRight ? rt.right : rt.left, rt.top, GetParent(m_hMenuBar), NULL);  
       }  
       return SetButtonState(bState & ~TBSTATE_PRESSED, bRight);  
   }  
};
