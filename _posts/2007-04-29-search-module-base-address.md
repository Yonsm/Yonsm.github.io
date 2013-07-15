---
date: 2007-04-29 05:08:06+00:00
layout: post
title: Search module base  & function address
thread: 322
categories: 代码
tags: Win 编程
---

Search module base (e.g.KERNEL32) & function address (e.g. GetProcAddress) (C++, NOT ASM).<!-- more -->  
  
  
PVOID GetKernelBase()  
{  
 PBYTE pbBase = (PBYTE) 0x70000000;  
__Retry:  
 __try  
 {  
   while (pbBase < (PBYTE) 0x80000000)  
   {  
     if (((PIMAGE_DOS_HEADER) pbBase)->e_magic == IMAGE_DOS_SIGNATURE)  
     {  
       PIMAGE_NT_HEADERS pNTHdr = (PIMAGE_NT_HEADERS) (pbBase + ((PIMAGE_DOS_HEADER) pbBase)->e_lfanew);  
       if (pNTHdr->Signature == IMAGE_NT_SIGNATURE)  
       {  
         PIMAGE_EXPORT_DIRECTORY pExpDir = (PIMAGE_EXPORT_DIRECTORY) (pbBase + pNTHdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);  
         PDWORD p = (PDWORD) (pbBase + pExpDir->Name);  
         if ((p[0] == 'NREK') && (p[1] == '23LE'))  
         {  
           return pbBase;  
         }  
       }  
     }  
     pbBase += 0x1000;  
   }      
 }  
 __except (EXCEPTION_EXECUTE_HANDLER)  
 {  
   pbBase += 0x1000;  
   goto __Retry;  
 }  
 return NULL;  
}  
  
  
typedef FARPROC (WINAPI *PGBA)(HMODULE hModule, PCTSTR pszName);  
  
 // Lookup GetProcAddress funtion  
 PGBA pGetProcAddress = NULL;  
 PBYTE pbBase = (PBYTE) hKernel32;  
 if (((PIMAGE_DOS_HEADER) pbBase)->e_magic == IMAGE_DOS_SIGNATURE)  
 {  
   PIMAGE_NT_HEADERS pNTHdr = (PIMAGE_NT_HEADERS) (pbBase + ((PIMAGE_DOS_HEADER) pbBase)->e_lfanew);  
   if (pNTHdr->Signature == IMAGE_NT_SIGNATURE)  
   {  
     PIMAGE_EXPORT_DIRECTORY pExpDir = (PIMAGE_EXPORT_DIRECTORY) (pbBase + pNTHdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);  
     PDWORD pdwNames = (PDWORD) (pbBase + pExpDir->AddressOfNames);  
     for (UINT i = 0; i < pExpDir->NumberOfNames; i++)  
     {  
       // GetProcAddress  
       PDWORD p = (PDWORD) (pbBase + pdwNames[i]);  
       if (p && (p[0] == 'PteG') && (p[1] == 'Acor') && (p[2] == 'erdd'))  
       {  
         PDWORD pdwFunctions = (PDWORD) (pbBase + pExpDir->AddressOfFunctions);  
         pGetProcAddress = (PGBA) (pbBase + pdwFunctions[i]);  
         break;  
       }  
     }  
   }  
 }  

