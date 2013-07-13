---
author: Yonsm
comments: true
date: 2006-04-04 08:10:21+00:00
layout: post
slug: windows-mobile-cant-openthread-other-threads
title: Windows Mobile 竟然无法 OpenThread 操作其它线程
wordpress_id: 199
categories:
- 代码
tags:
- 编程
- 郁闷
---

辛辛苦苦写了一个函数，后头一看竟然连 OpenThread 都没有，瞎忙！  
原来 Windows Mobile 下的线程操作函数，只能针对当前线程或者本进程中创建的线程进行操作（挂起/恢复等等）。贴于 Dead Code 于此处，谨示纪念……<!-- more -->  
  
#ifndef UNDER_CE  
BOOL CProcView::SuspendProcess(CProcItem* p)  
{  
   BOOL bResult = p->bSuspend || g_pMain->Confirm(IDM_Proc_Suspend);  
   if (bResult)  
   {  
       HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, p->dwProcessID);  
       if (hSnap != INVALID_HANDLE_VALUE)  
       {  
           THREADENTRY32 te;  
           te.dwSize = sizeof(te);  
           p->bSuspend = !p->bSuspend;  
           for (bResult = Thread32First(hSnap, &te;); bResult; bResult = Thread32Next(hSnap, &te;))   
           {  
               if (te.th32OwnerProcessID == p->dwProcessID)   
               {  
                   HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, te.th32ThreadID);  
                   if (hThread)  
                   {  
                       if (p->bSuspend)  
                       {  
                           SuspendThread(hThread);  
                       }  
                       else  
                       {  
                           ResumeThread(hThread);  
                       }  
                       CloseHandle(hThread);  
                   }                     
               }  
           }  
           bResult = CloseToolhelp32Snapshot(hSnap);  
       }  
   }  
   return bResult;  
}  
#endif  

