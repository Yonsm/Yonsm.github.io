---
date: 2006-12-30 07:46:24+00:00
layout: post
title: Another way to hook/modify API
thread: 284
categories: 代码
tags: Win 逆向工程
---

<!-- more -->[codes=cpp]  
// Hook ExitWindows to execute a command  
VOID Hook(HANDLE hProcess)  
{  
   __asm  
   {  
       // BOOL WINAPI WriteProcessMemory(HANDLE hProcess, PVOID pvBaseAddress, PVOID pvBuffer, DWORD dwSize, PDWORD pdwNumberOfBytesWritten);  
       // Write code to target  
       PUSH    NULL  
       MOV     EAX, OFFSET _End  
       SUB     EAX, OFFSET _Code  
       PUSH    EAX  
       PUSH    OFFSET _Code  
       PUSH    ExitWindowsEx  
       PUSH    hProcess  
       CALL    DWORD PTR [WriteProcessMemory];  
  
       // Write True WinExec address to target  
       PUSH    NULL  
       PUSH    4  
       LEA     EAX, WinExec  
       PUSH    EAX  
       MOV     EAX, OFFSET _WinExec  
       SUB     EAX, OFFSET _Code  
       ADD     EAX, ExitWindowsEx  
       PUSH    EAX  
       PUSH    hProcess  
       CALL    DWORD PTR [WriteProcessMemory];  
  
       // Return  
       RET     4  
  
       // Target code (Call WinExec to execute a command), address independent  
_Code:  
       MOV     EAX, [ESP + 4]  
       PUSH    EAX  
       CALL    _GetWinExec  
_WinExec:  
       _EMIT   0  
       _EMIT   0  
       _EMIT   0  
       _EMIT   0  
_GetWinExec:  
       POP     EAX  
       CALL    _Call  
       _EMIT   'R'  
       _EMIT   'X'  
       _EMIT   'P'  
       _EMIT   'E'  
       _EMIT   '.'  
       _EMIT   'E'  
       _EMIT   'X'  
       _EMIT   'E'  
       _EMIT   ' '  
       _EMIT   'H'  
       _EMIT   'E'  
       _EMIT   'L'  
       _EMIT   'P'  
       _EMIT   0  
_Call:  
       CALL    [EAX]  
       RET     8  
_End:  
   }  
}  
  
[/codes] 
