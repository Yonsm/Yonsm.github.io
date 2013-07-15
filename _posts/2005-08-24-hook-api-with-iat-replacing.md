---
date: 2005-08-24 19:23:39+00:00
layout: post
title: 替换 IAT 中的导入函数地址实现 Hook API
thread: 25
categories: 代码
---

详细说明《Windows 核心编程》中有。贴段代码，我写得比他写得简洁多了。自己会查找 Image Import descriptor 的地址，而不像书中所用的调用 ImageHlp.dll 或者 DbgHelp.dll 中的函数 ImageDirectoryToData 来实现。为了使用一些 PE 结构类型，请 #include （不会导入他的函数）。


<!-- more -->


使用方法：




HookAPI((PBYTE) GetModuleHandle(NULL), "User32.dll", MessageBox, MyMessageBox);




取消Hook：




HookAPI((PBYTE) GetModuleHandle(NULL), "User32.dll", MyMessageBox, MessageBox);




原本以为用这种方法能 Hook User32.dll 中的 SetScrollInfo 实现 ClassXP 自绘 Scroll 的。因为需要 HookAPI((PBYTE) GetModuleHandle("User32.dll"), "User32.dll", SetScrollInfo, MySetScrollInfo) ，后来发现 User32.dll 根本不是导入自己的函数，而是直接调用——早该想到了，晕死！




所以替换 IAT 方法 Hook，还是有限制的，没办法在ClassXP中使用：（只好替换SetScrollInfo的入口点代码了：（






    
    PVOID HookAPI(PBYTE pbModule, PCSTR pszName, PVOID pvOrg, PVOID pvNew)
     {
         PIMAGE_THUNK_DATA r;
         PIMAGE_NT_HEADERS p;
         PIMAGE_IMPORT_DESCRIPTOR q;
         
         p = (PIMAGE_NT_HEADERS) (pbModule + ((PIMAGE_DOS_HEADER) pbModule)->e_lfanew);
         q = (PIMAGE_IMPORT_DESCRIPTOR) (pbModule + p->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
     
         for (; q->Name; q++)
         {
             if (lstrcmpiA(pszName, (PCSTR) (pbModule + q->Name)) == 0)
             {
                 for (r = (PIMAGE_THUNK_DATA) (pbModule + q->FirstThunk); r->u1.Function; r++)
                 {
                     if ((PVOID) r->u1.Function == pvOrg) 
                     {
                         WriteProcessMemory(GetCurrentProcess(), &r->u1.Function, &pvNew, sizeof(PVOID), NULL);
                         return pvOrg;
                     }
                 }
             }
         }
     
         return NULL;
     }
     
        下面是替换函数入口的方法，只能用于X86的平台中，尚不完善。 PVOID HookApi(PVOID pvOrg, PVOID pvNew) {     DWORD dwProtect;      if (VirtualProtect(pvOrg, 16, PAGE_READWRITE, &dwProtect))     {         PBYTE p = (PBYTE) pvOrg;         PDWORD q = (PDWORD) (p + 1);          *p = 0xE9;         *q = (LONG) pvNew - (LONG) (p + 5);          VirtualProtect(pvOrg, 16, dwProtect, &dwProtect);          return pvOrg;     }      return NULL; }






2012.08.27 补充代码：
`
//
#include 
#pragma comment(lib, "Dbghelp.lib")
PROC HookIAT(PCSTR dllName, PCSTR procName, PROC newProc)
{
	DWORD dwSize = 0;
	HANDLE hProcess = GetModuleHandle (NULL);
	PIMAGE_IMPORT_DESCRIPTOR pImageImport = (PIMAGE_IMPORT_DESCRIPTOR)ImageDirectoryEntryToData(hProcess, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &dwSize;);
	if (NULL == pImageImport) return NULL;

	PIMAGE_THUNK_DATA pImageThunkOriginal = NULL;
	PIMAGE_THUNK_DATA pImageThunkReal  = NULL;
	PIMAGE_IMPORT_BY_NAME pImageImportByName = NULL;
	while (pImageImport->Name)
	{
		if (0 == _strcmpi((PSTR)((PBYTE)hProcess+pImageImport->Name), dllName))
		{
			break;
		}
		++pImageImport;
	}
	if (!pImageImport->Name) return NULL;


	PROC oldProc = NULL;
	pImageThunkOriginal = (PIMAGE_THUNK_DATA)((PBYTE)hProcess+pImageImport->OriginalFirstThunk);
	pImageThunkReal = (PIMAGE_THUNK_DATA)((PBYTE)hProcess+pImageImport->FirstThunk);
	while (pImageThunkOriginal->u1.Function)
	{
		if ((pImageThunkOriginal->u1.Ordinal & IMAGE_ORDINAL_FLAG) != IMAGE_ORDINAL_FLAG)
		{
			pImageImportByName = (PIMAGE_IMPORT_BY_NAME)((PBYTE)hProcess+pImageThunkOriginal->u1 .AddressOfData);
			if (0 == _strcmpi(procName, (PSTR)pImageImportByName->Name))
			{
				MEMORY_BASIC_INFORMATION mbi_thunk;
				VirtualQuery(pImageThunkReal, &mbi;_thunk, sizeof(MEMORY_BASIC_INFORMATION)); 
				VirtualProtect(mbi_thunk.BaseAddress, mbi_thunk.RegionSize, PAGE_READWRITE, &mbi;_thunk.Protect); 

				oldProc = (PROC)pImageThunkReal->u1.Function; 
				pImageThunkReal->u1.Function = (DWORD_PTR)newProc;

				DWORD dwOldProtect; 
				VirtualProtect(mbi_thunk.BaseAddress, mbi_thunk.RegionSize, mbi_thunk.Protect, &dwOldProtect;); 
				break;
			}
		}
		++pImageThunkOriginal;
		++pImageThunkReal;
	}

	return oldProc;
}
`

