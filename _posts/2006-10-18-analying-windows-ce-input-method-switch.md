---
date: 2006-10-18 11:38:18+00:00
layout: post
title: MS Windows CE 输入法切换方案和代码分析
thread: 265
categories: 文档
tags: 逆向工程
---

Pocket PC 中切换输入法要等N长时间（4秒左右），稍加分析，感觉可能是CE在枚举登记过的输入法的过程中可能进行了大量的无用操作，；再仔细分析，输入法登记在 HKEY_CLASSS_ROOT\CLSID下，看情形似乎使用IsSIPInput=1的Value标志，表示这是输入法——MD这都想得出来！这下面是登记所有COM组件的地方，当然非常多条目，枚举起来肯定非常慢。  
  
不过我终于不死心，觉得MS不至于用这种方案枚举数输入法，于是狂搜 Windows CE Platform Builder  中的文件（有WinCE 源代码和OS Image Build工具和开发环境）的目录，只听到硬盘（ISO文件模拟的光盘）一阵狂响之后，终于找到文件 sipcpl.cpp，一看，果然印证我上面的猜想：<!-- more -->  
  
[codes=cpp]  
#include "cplpch.h"  
  
……  
  
// Class to travel the registry & enumerate the IMs  
class CIMEnum  
{  
private:  
   CReg m_regCLSID;  
  
public:  
   CIMEnum() {  
       // Open the CLSID key.  
       m_regCLSID.Open(HKEY_CLASSES_ROOT, RK_CLSID);  
   }   
   ~CIMEnum() {}  
  
   // Enumerate all CLSIDs that are SIPInputMethods   
   PIMENTRY GetNextIM(void)  
   {  
       #define BUFSIZE 260  
       TCHAR szTemp[BUFSIZE];  
  
       // Enumerate next CLSID, looking for input methods.  
       while(m_regCLSID.EnumKey(szTemp, BUFSIZE))  
       {  
           // Check if this CLSID has an IsSIPInputMethod key with value "1".  
           CReg regIM(m_regCLSID, szTemp);  
           CReg regIsSIP(regIM, RK_ISSIPINPUTMETHOD);  
           LPCTSTR pszIsIM = regIsSIP.ValueSZ(NULL);  
           if(pszIsIM && pszIsIM[0]=='1')  
           {                // Get the CLSID (from the CLSID string in szTemp),   
               // friendly name (default value of the szTemp key)  
               // and the default icon for the IM (DefaultIcon subkey)  
               LPCTSTR  pszIMName;  
               CLSID    clsid;  
                 
               if( (pszIMName = regIM.ValueSZ(NULL)) &&   
                   SUCCEEDED(CLSIDFromString(szTemp, &clsid;)) )  
               {  
                   PIMENTRY pIMEntry = (PIMENTRY)LocalAlloc(LPTR,   
                       sizeof(IMENTRY)+sizeof(TCHAR)*(1+lstrlen(pszIMName)));  
  
                   if(pIMEntry)  
                   {  
                       lstrcpy(pIMEntry->m_szName, pszIMName);  
                       pIMEntry->m_clsid = clsid;  
                         
                       // Get Icon if we have one  
                       CReg regIcon(regIM, RK_DEFAULTICON);  
                       if(regIcon.ValueSZ(NULL, szTemp, BUFSIZE))  
                       {  
                           int iIndex = 0;  
                           LPTSTR pszIndex = _tcschr(szTemp, ',');  
                           if(pszIndex)  
                           {  
                               *pszIndex = 0;  // Null terminate the name portion of the string  
                               iIndex=_ttol((pszIndex+1)); // get the icon index just past the ','  
                           }  
                           ExtractIconEx(szTemp, iIndex, &pIMEntry-;>m_hiconWide, &pIMEntry-;>m_hiconNarrow, 1);  
                       }  
                       return pIMEntry;  
                   }  
                   else { ASSERT(FALSE); } // OOM  
               }  
               else { ASSERT(FALSE); } // shouldn't happen unless registry data incorrect  
           }  
           // not an IM key, try next one  
       }  
       return NULL;  
   }  
};  
  
[/codes]  
  
果然把注册表 HKEY_CLASS_ROOT\CLSID全部枚举了一遍，我想即使不是PPC用户，PC上用过注册表编辑器的点开 HKEY_CLASS_ROOT\CLSID 这个键的用户肯定都深有体会，要多久时间。  
  
设置这种方案的真TMD有病、垃圾！（嗯，我是说他的做法很垃圾，不是说他人很垃圾！如果他是我的项目组成员，我非扁它不可）。一处漫不经心的设计，害得用户切换输入法变得异常不爽。要命的是，PPC上肯定要经常切换输入法（如果上网的话，切换中文输入和英文网址）。  
  
想想办法能不能解决吧，……，继续分析，找到，他这片代码最终生成在 cplmain.cpl 中，原来合并到了控制面板管理的模块中，反汇编一看，和源代码一样，修改一下，比如，从 CLXID下读取吧，当然，输入法登记的东西也要挪过来，感觉代码都能搞定了……  
  
放到机器上一试，需要替换ROM里面的文件，似乎如果是什么XIP的模块，是没法替换的，晕死，没效果，这个文件可能就是XIP就地执行的。就地处决吧，就分析到这里，暂时死心了……  
  
  
厄……自己定制个ROM，能替换着文件的话，肯定能搞定，那样切换输入法，应该能做到像PC机上那样快速了，至少不会有迟滞感觉。  

