


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header
#include <Windows.h>

//#define AEON_OVR
#ifndef _WIN32_WCE
//#define AEON_SEG ".AEON"
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Init AEON variable
#ifndef AEON_SEG
VOID AeonInit(PVOID pvAeon, DWORD dwSize = sizeof(DWORD), HMODULE hModule = NULL)
#else
VOID AeonInit(HMODULE hModule = NULL)
#endif
{
	TCHAR tzPath[MAX_PATH];
	PTSTR ptzExt = tzPath + GetModuleFileName(hModule, tzPath, MAX_PATH) - 5;
	if (lstrcmpi(ptzExt, TEXT(".AEON")) == 0)
	{
		TCHAR tzOld[MAX_PATH];
		lstrcpy(tzOld, tzPath);
		*ptzExt = 0;
		for (UINT i = 0; i < 1000; i++, Sleep(20))
		{
			DeleteFile(tzPath);
			if (MoveFile(tzOld, tzPath))
			{
				break;
			}
		}
		ExitProcess(0);
	}

#ifndef AEON_SEG
	HANDLE hFile = CreateFile(tzPath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
#ifdef AEON_OVR
		SetFilePointer(hFile, -((LONG) dwSize), 0, FILE_END);
		ReadFile(hFile, pvAeon, dwSize, &dwSize, NULL);
#else
		DWORD dwTemp;
		DWORD dwAeon[2];
		SetFilePointer(hFile, -8, 0, FILE_END);
		ReadFile(hFile, &dwAeon, 8, &dwTemp, NULL);
		if (dwAeon[1] == 'AEON')
		{
			SetFilePointer(hFile, -8 - dwAeon[0], 0, FILE_END);
			ReadFile(hFile, pvAeon, dwSize, &dwTemp, NULL);
		}
#endif
		CloseHandle(hFile);
	}
#endif
}

#ifdef AEON_SEG
PIMAGE_SECTION_HEADER AeonGetSeg(PBYTE pbBase)
{
	// Verify DOS signature
	if (((PIMAGE_DOS_HEADER) pbBase)->e_magic == IMAGE_DOS_SIGNATURE)
	{
		// Verify PE signature
		PIMAGE_NT_HEADERS pNTHdr = (PIMAGE_NT_HEADERS) (pbBase + ((PIMAGE_DOS_HEADER) pbBase)->e_lfanew);
		if (pNTHdr->Signature == IMAGE_NT_SIGNATURE)
		{
			// Lookup PE sections
			PIMAGE_SECTION_HEADER pSecHdr = (PIMAGE_SECTION_HEADER) (pNTHdr + 1);
			for (UINT i = pNTHdr->FileHeader.NumberOfSections; i; i--, pSecHdr++)
			{
				// Write back
				if (!memcmp(pSecHdr->Name, AEON_SEG, sizeof(AEON_SEG)))
				{
					return pSecHdr;
				}
			}
		}
	}
	return NULL;
}
#endif

// Save AEON variable
#ifndef AEON_SEG
VOID AeonExit(PVOID pvAeon, DWORD dwSize = sizeof(DWORD), HMODULE hModule = NULL)
#else
VOID AeonExit(HMODULE hModule = NULL)
#endif
{
	TCHAR tzPath[MAX_PATH];
	TCHAR tzNew[MAX_PATH];
	GetModuleFileName(hModule, tzPath, MAX_PATH);
	lstrcpy(tzNew, tzPath);
	lstrcat(tzNew, TEXT(".AEON"));
	CopyFile(tzPath, tzNew, FALSE);

	HANDLE hFile = CreateFile(tzNew, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
#ifndef AEON_SEG
#ifdef AEON_OVR
		SetFilePointer(hFile, -((LONG) dwSize), 0, FILE_END);
		WriteFile(hFile, pvAeon, dwSize, &dwSize, NULL);
#else
		DWORD dwTemp;
		DWORD dwAeon[2];
		SetFilePointer(hFile, -8, 0, FILE_END);
		ReadFile(hFile, &dwAeon, 8, &dwTemp, NULL);
		SetFilePointer(hFile, (dwAeon[1] == 'AEON') ? (-8 - dwAeon[0]) : 0, 0, FILE_END);
		WriteFile(hFile, pvAeon, dwSize, &dwTemp, NULL);
		dwAeon[0] = dwSize;
		dwAeon[1] = 'AEON';
		WriteFile(hFile, &dwAeon, 8, &dwTemp, NULL);
		SetEndOfFile(hFile);
#endif
#else
		HANDLE hMapping = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, GetFileSize(hFile, NULL), NULL);
		if (hMapping)
		{
			PBYTE pbFile = (PBYTE) MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
			if (pbFile)
			{
				PBYTE pbModule = hModule ? (PBYTE) hModule : (PBYTE) GetModuleHandle(NULL);
				PIMAGE_SECTION_HEADER pFileSec = AeonGetSeg(pbFile);
				PIMAGE_SECTION_HEADER pInstSec = AeonGetSeg(pbModule);
				if (pFileSec && pInstSec)
				{
					memcpy(pbFile + pFileSec->PointerToRawData, pbModule + pInstSec->VirtualAddress, pFileSec->SizeOfRawData);
				}
				UnmapViewOfFile(pbFile);
			}
			CloseHandle(hMapping);
		}
#endif
		CloseHandle(hFile);

		PROCESS_INFORMATION pi;
		STARTUPINFO si = {sizeof(STARTUPINFO)};

#ifdef _USRDLL
#ifdef _WIN32_WCE
		lstrcat(tzNew, TEXT(",AEON"));
		if (CreateProcess(TEXT("RUNDLL32.EXE"), tzNew, NULL, NULL, FALSE, 0, NULL, NULL, NULL, &pi))
#else
		wsprintf(tzPath, TEXT("RUNDLL32.EXE %s,AEON"), tzNew);
		if (CreateProcess(NULL, tzPath, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
#endif
#else
		if (CreateProcess(tzNew, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
#endif
		{
			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
		}

		//ExitProcess(0);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
