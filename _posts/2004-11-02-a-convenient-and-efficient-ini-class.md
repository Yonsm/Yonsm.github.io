---
date: 2004-11-02 03:49:02+00:00
layout: post
title: 构造一个方便高效 INI 类
thread: 125
categories: 文档
---

   Windows API 本身已经为我们写好了操作 INI 的函数，但是有时候用起来可能不是很方便。把这些 API 简单封装一下，将会大大方便我们读写 INI 文件。

    网上 INI 类多如牛毛。不过我个人认为，实在没有必要每个 INI 操作都真的去调用 INI 类中的函数。下面看看我写的充分使用 inline 和 C++ 省却参数构造的 CIni 类:<!-- more -->
    
    <br></br>////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////<br></br>// 预处理<br></br>#pragma once<br></br>#include <windows.h></windows.h>
    
    #define INI_Main TEXT("Main")<br></br>////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////<br></br>// CIni 类<br></br>class CIni<br></br>{<br></br>public:<br></br>    // INI 文件名<br></br>    TCHAR m_tzFileName[MAX_PATH];
    
    public:<br></br>    // 初始化配置文件<br></br>    inline CIni()<br></br>    {<br></br>        GetModuleFileName(NULL, m_tzFileName, MAX_PATH);<br></br>        lstrcpy(m_tzFileName + lstrlen(m_tzFileName) - 4, TEXT(".ini"));<br></br>    }
    
        // 初始化配置文件<br></br>    inline CIni(PCTSTR ptzFileName)<br></br>    {<br></br>        lstrcpy(m_tzFileName, ptzFileName);<br></br>    }
    
        // 获取整数<br></br>    inline UINT GetInt(PCTSTR ptzKeyName, INT iDefault = 0, PCTSTR ptzSectionName = INI_Main)<br></br>    {<br></br>        return GetPrivateProfileInt(ptzSectionName, ptzKeyName, iDefault, m_tzFileName);<br></br>    }
    
        // 设置整数<br></br>    inline BOOL SetInt(PCTSTR ptzKeyName, INT iValue = 0, PCTSTR ptzSectionName = INI_Main)<br></br>    {<br></br>        TCHAR tzString[16];
    
            wsprintf(tzString, TEXT("%d"), iValue);<br></br>        return WritePrivateProfileString(ptzSectionName, ptzKeyName, tzString, m_tzFileName);<br></br>    }
    
        // 获取字符串<br></br>    inline DWORD GetString(PCTSTR ptzKeyName, PTSTR ptzReturnedString,<br></br>        DWORD dwSize = MAX_PATH, PCTSTR ptzDefault = NULL, PCTSTR ptzSectionName = INI_Main)<br></br>    {<br></br>        return GetPrivateProfileString(ptzSectionName, ptzKeyName, ptzDefault, ptzReturnedString,<br></br>            dwSize, m_tzFileName);<br></br>    }
    
        // 设置字符串<br></br>    inline BOOL SetString(PCTSTR ptzKeyName, PCTSTR ptzString = NULL, PCTSTR ptzSectionName = INI_Main)<br></br>    {<br></br>        return WritePrivateProfileString(ptzSectionName, ptzKeyName, ptzString, m_tzFileName);<br></br>    }
    
        // 获取结构<br></br>    inline BOOL GetStruct(PCTSTR ptzKeyName, PVOID pvStruct, UINT uSize, PCTSTR ptzSectionName = INI_Main)<br></br>    {<br></br>        return GetPrivateProfileStruct(ptzSectionName, ptzKeyName, pvStruct, uSize, m_tzFileName);<br></br>    }
    
        // 设置结构<br></br>    inline BOOL SetStruct(PCTSTR ptzKeyName, PVOID pvStruct, UINT uSize, PCTSTR ptzSectionName = INI_Main)<br></br>    {<br></br>        return WritePrivateProfileStruct(ptzSectionName, ptzKeyName, pvStruct, uSize, m_tzFileName);<br></br>    }
    
        // 获取节<br></br>    inline DWORD GetSection(PTSTR ptzReturnBuffer, DWORD dwSize, PCTSTR ptzSectionName = INI_Main)<br></br>    {<br></br>        return GetPrivateProfileSection(ptzSectionName, ptzReturnBuffer, dwSize, m_tzFileName);<br></br>    }
    
        // 设置节<br></br>    inline DWORD SetSection(PCTSTR ptzString, PCTSTR ptzSectionName = INI_Main)<br></br>    {<br></br>        return WritePrivateProfileSection(ptzSectionName, ptzString, m_tzFileName);<br></br>    }
    
        // 获取节名<br></br>    inline DWORD GetSectionNames(PTSTR ptzReturnBuffer, DWORD dwSize)<br></br>    {<br></br>        return GetPrivateProfileSectionNames(ptzReturnBuffer, dwSize, m_tzFileName);<br></br>    }<br></br>};<br></br>////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////<br></br>

    一个 INI 文件为一个 CIni 对象。使用举例如下: 

  
    CIni iniMain;   // 使用默认 INI 名称，即与 EXE 仅仅是扩展名不同。

    CIni iniSel(TEXT("F:Sel.ini")); // 指定 INI 路径

  
    TCHAR tzText[MAX_PATH];  
    COLORREF crTextColor;

    crTextColor = iniMain.GetInt(INI_TextColor);  
    iniMain.SetInt(INI_TextColor, crTextColor);  
    iniMain.GetString(INI_PicturesPath, tzText);  
    iniMain.SetString(INI_PicturesPath, TEXT("F:My Pictures"));  
    iniSel.SetStruct(INI_WindowRect, &rtWindow, sizeof(RECT));  
  


  

    当然，如果一个程序中只操作一个 INI 文件，这个类也可以改成静态类 (只要在每个函数和变量前加上 static，非常简单)。

下载: [CIni](http://yonsm.reg365.com/up/1099311280.rar)
