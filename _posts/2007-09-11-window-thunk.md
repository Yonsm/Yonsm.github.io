---
date: 2007-09-11 07:41:23+00:00
layout: post
title: Thunk  Window Class Demo
thread: 366
categories: 代码
tags: WM Win 编程
---

Generates __thiscall thunk to convert static funtion to member function.  
  
<!-- more -->  
  
  
  
  
#include   
  
#if defined(_M_IX86)  
template  class CThunk  
{  
private:  
#pragma pack(push, 1)  
   BYTE m_bPopEcx; // POP EAX  
   BYTE m_bPush;   // PUSH pThis  
   PVOID m_pThis;  //   
   BYTE m_bPushEcx;// PUSH EAX  
  
   //BYTE m_bJmp;  // JMP pProc  
   //INT m_iOffset;  
  
   BYTE m_bMovEax; // MOV EAX, tProc  
   T m_tProc;  
   WORD m_wJmpEax; // JMP EAX  
#pragma pack(pop)  
  
public:  
   PROC Init(PVOID pThis, T tProc)  
   {  
       m_bPopEcx = 0x58;  
       m_bPush = 0x68;  
       m_pThis = pThis;  
       m_bPushEcx = 0x50;  
  
       //m_bJmp = 0xE9;  
       //m_iOffset = (INT) ((INT_PTR) pProc - ((INT_PTR) &m;_iOffset + sizeof(m_iOffset)));  
         
       m_bMovEax = 0xB8;  
       m_tProc = tProc;  
       m_wJmpEax = 0xE0FF;  
  
       return (PROC) this;  
   }  
};  
#else  
#error CThunk does not support this platform!  
#endif  
  
class CMyWnd  
{  
public:  
   HWND m_hWnd;  
  
   typedef LRESULT (CALLBACK CMyWnd::*PWNDPROC)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);  
   CThunk m_tProc;  
  
public:  
   CMyWnd()  
   {  
       WNDCLASSEX wceClass = {0};  
  
       // Generate thunk data/code  
       wceClass.lpfnWndProc = (WNDPROC) m_tProc.Init(this, &CMyWnd;::WindowProc);  
  
       wceClass.cbSize = sizeof(WNDCLASSEX);  
       wceClass.style = CS_VREDRAW | CS_HREDRAW;  
       wceClass.hInstance = GetModuleHandle(NULL);  
       wceClass.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));  
       wceClass.hCursor = LoadCursor(NULL, IDC_ARROW);  
       wceClass.hbrBackground = (HBRUSH) COLOR_BTNSHADOW;  
       wceClass.lpszClassName = TEXT("ThThunk");  
       wceClass.hIconSm = NULL;  
       RegisterClassEx(&wceClass;);  
  
       CreateWindowEx(WS_EX_ACCEPTFILES | WS_EX_APPWINDOW, TEXT("ThThunk"), TEXT("ThThunk"), WS_OVERLAPPEDWINDOW,  
           CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, GetModuleHandle(NULL), 0);  
  
       ShowWindow(m_hWnd, SW_SHOW);  
       UpdateWindow(m_hWnd);  
   }  
  
   LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)  
   {  
       switch (uMsg)  
       {  
       case WM_NCCREATE:  
           m_hWnd = hWnd;  
           break;  
  
       case WM_LBUTTONDOWN:  
           {  
               TCHAR tzText[MAX_PATH];  
               GetWindowText(m_hWnd, tzText, MAX_PATH);  
               MessageBox(hWnd, tzText, tzText, MB_ICONINFORMATION);  
           }  
           break;  
  
       case WM_DESTROY:  
           PostQuitMessage(0);  
           break;  
  
       default:  
           break;  
       }  
       return DefWindowProc(hWnd, uMsg, wParam, lParam);  
   }  
};  
  
  
  
INT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)  
{  
   CMyWnd w;  
  
   MSG msg;  
   while (GetMessage(&msg;, NULL, 0, 0))  
   {  
       TranslateMessage(&msg;);  
       DispatchMessage(&msg;);  
   }  
  
   return 0;  
}  

