---
date: 2007-04-02 05:47:53+00:00
layout: post
title: 用 ZLib 解压缩 TAR GZ 的最简单的过程和代码
thread: 301
categories: 代码
tags: 编程
---

看代码，不多说，应该很简单，由于 ZLib 的可移植性，所以在 PC 和 Windows Mobile 下不加修改即可便已通过。<!-- more -->详细代码下载可以参考 CeleSetup 的帖子。  
  
`
#include "UniBase.h"  
#include "ZLib/ZLib.h"  
#pragma comment(lib, "ZLib/ZLib.lib")  
  
// Values used in typeflag field  
#define REGTYPE       '0'       // regular file  
#define AREGTYPE      '\0'      // regular file  
#define LNKTYPE       '1'       // link  
#define SYMTYPE       '2'       // reserved  
#define CHRTYPE       '3'       // character special  
#define BLKTYPE       '4'       // block special  
#define DIRTYPE       '5'       // directory  
#define FIFOTYPE      '6'       // FIFO special  
#define CONTTYPE      '7'       // reserved  
  
//  GNU tar extensions  
#define GNUTYPE_DUMPDIR   'D'       // file names from dumped directory  
#define GNUTYPE_LONGLINK  'K'       // long link name  
#define GNUTYPE_LONGNAME  'L'       // long file name  
#define GNUTYPE_MULTIVOL  'M'       // continuation of file from another volume  
#define GNUTYPE_NAMES   'N'       // file name that does not fit into main hdr  
#define GNUTYPE_SPARSE    'S'       // sparse file  
#define GNUTYPE_VOLHDR    'V'       // tape/volume hdr  
  
  
#define MAX_BLOCK 512  
#define MAX_FNAME 100  
  
struct TARHDR  
{  
 CHAR name[100];               //   0  
 CHAR mode[8];                 // 100  
 CHAR uid[8];                  // 108  
 CHAR gid[8];                  // 116  
 CHAR size[12];                // 124  
 CHAR mtime[12];               // 136  
 CHAR chksum[8];               // 148  
 CHAR typeflag;                // 156  
 CHAR linkname[100];           // 157  
 CHAR magic[6];                // 257  
 CHAR version[2];              // 263  
 CHAR uname[32];               // 265  
 CHAR gname[32];               // 297  
 CHAR devmajor[8];             // 329  
 CHAR devminor[8];             // 337  
 CHAR prefix[155];             // 345  
};  
  
typedef union _TARBUF  
{  
 TARHDR hdr;  
 CHAR buf[MAX_BLOCK];  
}  
TARBUF, *PTARBUF;  
  
  
// Convert octal digits to INT  
INT GetOct(PSTR p,INT iWidth)  
{  
 INT iResult = 0;  
 while (iWidth--)  
 {  
   CHAR c = *p++;  
   if (c == 0)  
   {  
     break;  
   }  
   if (c == ' ')  
   {  
     continue;  
   }  
   if (c < '0' || c > '7')  
   {  
     return -1;  
   }  
   iResult = iResult * 8 + (c - '0');  
 }  
 return iResult;  
}  
  
INT XTar(PTSTR ptzCmd)  
{  
 PTSTR ptzOutDir = ptzCmd;  
 for (; *ptzOutDir; ptzOutDir++)  
 {  
   if (*ptzOutDir == ',')  
   {  
     *ptzOutDir++ = 0;  
     break;  
   }  
 }  
  
 CHAR szPath[MAX_BLOCK];  
 UStrToAStr(szPath, ptzCmd, MAX_PATH);  
 gzFile gz = gzopen(szPath,"rb");  
 if (!gz)  
 {  
   return -1;  
 }  
  
 INT iGetHeader = 1;  
 INT iRemaining = 0;  
 BOOL bFail = FALSE;  
 HANDLE hFile = NULL;  
 TCHAR tzName[MAX_PATH];  
 do  
 {  
   TARBUF buf;  
   INT iLen = gzread(gz, &buf;, MAX_BLOCK);  
   if (iLen < 0)  
   {  
     return -2;  
   }  
  
   // Always expect complete blocks to process the tar information.  
   if (iLen != MAX_BLOCK)  
   {  
     bFail = TRUE;  
     iRemaining = 0;  
   }  
  
   // If we have to get a tar header  
   if (iGetHeader >= 1)  
   {  
     // if we met the end of the tar or the end-of-tar block, we are done  
     if (iLen == 0 || buf.hdr.name[0] == 0)  
     {  
       break;  
     }  
  
     if (iGetHeader == 1)  
     {  
       UAStrToStr(tzName, buf.hdr.name, MAX_PATH);  
       UStrRep(tzName, '/', '\\');  
     }  
     else  
     {  
       iGetHeader = 1;  
     }  
  
     // Act according to the type flag  
     switch (buf.hdr.typeflag)  
     {  
     case DIRTYPE:  
       TCHAR tzPath[MAX_PATH];  
       UStrPrint(tzPath, TEXT("%s\\%s\\"), ptzOutDir, tzName);  
       UDirCreate(tzPath);  
       break;  
  
     case REGTYPE:  
     case AREGTYPE:  
       iRemaining = GetOct(buf.hdr.size, 12);  
       if (iRemaining == -1)  
       {  
         bFail = TRUE;  
         break;  
       }  
       else  
       {  
         UStrPrint(tzPath, TEXT("%s\\%s"), ptzOutDir, tzName);  
         UDirCreate(tzPath);  
         hFile = UFileOpen(tzPath, UFILE_WRITE);  
       }  
       iGetHeader = 0;  
       break;  
  
     case GNUTYPE_LONGLINK:  
     case GNUTYPE_LONGNAME:  
       iRemaining = GetOct(buf.hdr.size, 12);  
       if (iRemaining < 0 || iRemaining >= MAX_BLOCK)  
       {  
         bFail = TRUE;  
         break;  
       }  
       iLen = gzread(gz, szPath, MAX_BLOCK);  
       if (iLen < 0)  
       {  
         return -4;  
       }  
       if (szPath[MAX_BLOCK - 1] != 0 || (INT) strlen(szPath) > iRemaining)  
       {  
   
      bFail = TRUE;  
         break;  
       }  
       iGetHeader = 2;  
       break;  
     }  
   }  
   else  
   {  
     UINT uSize = (iRemaining > MAX_BLOCK) ? MAX_BLOCK : iRemaining;  
     if (hFile)  
     {  
       UFileWrite(hFile, &buf;, uSize);  
     }  
     iRemaining -= uSize;  
   }  
  
   if (iRemaining == 0)  
   {  
     iGetHeader = 1;  
     if (hFile)  
     {  
       UFileClose(hFile);  
       hFile = NULL;  
     }  
   }  
 }  
 while (!bFail);  
  
 gzclose(gz);  
 return 0;  
}
`