---
date: 2004-10-19 03:52:17+00:00
layout: post
title: 使用#定义方便控制版本号的宏
thread: 141
categories: 文档
---

    一个 VC Project 中，可能有很多地方需要用到版本号，比如 About 对话框、版本资源等。如果每次版本更改都一一去改变这些值，不但非常麻烦，而且有悖唯一原则。

    巧妙地使用宏定义，可以很好地解决这个问题。

    先来看看几个预处理操作符 ([Preprocessor Operators](http://msdn.microsoft.com/library/default.asp?url=/library/en-us/vclang/html/_predir_stringizing_operator.asp)): <!-- more -->

OperatorAction

[Stringizing operator (#)](http://msdn.microsoft.com/library/en-us/vclang/html/_predir_stringizing_operator.asp)
Causes the corresponding actual argument to be enclosed in double quotation marks

[Charizing operator (#@)](http://msdn.microsoft.com/library/en-us/vclang/html/_predir_charizing_operator.asp)
Causes the corresponding argument to be enclosed in single quotation marks and to be treated as a character (Microsoft Specific)

[Token-pasting operator (##)](http://msdn.microsoft.com/library/en-us/vclang/html/_predir_token.2d.pasting_operator.asp)
Allows tokens used as actual arguments to be concatenated to form other tokens

    简单说，# 就是使参数用引号包住，形成字符串；#@ 使参数用单引号包住，形成一个字符；## 是粘结符。这几个操作符从语言上来说比较晦涩，仔细看看 MSDN 的例子，好好理解一下。

    下面举例说一下怎么定义统一的版本宏。

    假设工程中有资源脚本文件 Resource.rc，唯一的版本号码存放在 Define.h 里。其它需要用到版本号的 CPP 文件均包含此文件。

    先看看 Define.h:
    
    #define VER_Major    2<br></br>#define VER_Minor    2<br></br>#define VER_Release    137 <br></br>#define VER_Build    1762<br></br>#define VER_Version    MAKELONG(MAKEWORD(VER_Major, VER_Minor), VER_Release)<br></br><br></br>#define _Stringizing(v)    #v<br></br>#define _VerJoin(a, b, c, d)  _Stringizing(a.b.c.d)<br></br><br></br>#define STR_BuildDate    TEXT(__DATE__)<br></br>#define STR_BuildTime    TEXT(__TIME__)<br></br>#define STR_BuilDateTime  TEXT(__DATE__) TEXT(" ") TEXT(__TIME__)<br></br>#define STR_Version    TEXT(_VerJoin(VER_Major, VER_Minor, VER_Release, VER_Build))<br></br>

    假设有了上面的定义后，就可以方便地使用 VER_Major、VER_Minor、VER_Release、VER_Build 作为版本号数字；STR_Version 作为版本字符串 (上面的例子中 STR_Version 执行宏展开后是 TEXT("2.2.137.1763") 的 TCHAR 字符串)。任何 CPP 文件中可以直接使用这些宏定义。

    资源脚本 Resource.rc  中，假设我们需要版本资源，可以首先在 Define.h 中再定义一些宏，比如:
    
    #define STR_AppName    TEXT("CuteFoto")<br></br>#define STR_Author    TEXT("Yonsm")<br></br>#define STR_Corporation    TEXT("Yonsm.NET")<br></br>#define STR_Web      TEXT("Yonsm.reg365.com")<br></br>#define STR_Email    TEXT("Yonsm@163.com")<br></br>#define STR_WebUrl    TEXT("http://") STR_Web<br></br>#define STR_EmailUrl    TEXT("mailto:") STR_Email TEXT("?Subject=") STR_AppName<br></br><br></br><br></br>#ifdef _CHS<br></br>#define STR_Description    TEXT("灵巧的批量扫描照片切割工具。")<br></br>#define STR_Copyright    TEXT("版权所有 (C) 2002-2004 ") STR_Corporation TEXT("，保留所有权利。")<br></br>#else // _CHS<br></br>#define STR_Description    TEXT("Picture cutting tool for batch-scanned photo.")<br></br>#define STR_Copyright    TEXT("Copyright (C) 2002-2004 ") STR_Corporation TEXT(". All rights reserved.")<br></br>#endif // _CHS<br></br>

    这时，我们在 Resouurc.rc 中添加版本资源——注意，不要直接添加，否则会被 VS 更改成实际的值，这样就不能达到我们的目的了。一个好的解决方法是:

  1. 在 VS IDE  中双击 Resource.rc 转到 资源视图 中，右击 Resource.rc，选择“资源包括”，在“只读符号指令”中包含 Define.h:
    
    #define APSTUDIO_HIDDEN_SYMBOLS<br></br>//……<br></br>#include "Define.h"<br></br>#include "Windows.h"<br></br>//……<br></br>#undef APSTUDIO_HIDDEN_SYMBOLS

  2. 在“编译时指令”中输入:
    
    LANGUAGE LANG_NEUTRAL, SUBLANG_DEFAULT<br></br>#pragma code_page(DEFAULT)<br></br><br></br>VS_VERSION_INFO VERSIONINFO<br></br>FILEVERSION VER_Major, VER_Minor, VER_Release, VER_Build<br></br>PRODUCTVERSION VER_Major, VER_Minor, VER_Release, VER_Build<br></br>FILEFLAGSMASK VS_FFI_FILEFLAGSMASK<br></br>FILEFLAGS 0<br></br>FILEOS VOS__WINDOWS32<br></br>FILETYPE 0<br></br>FILESUBTYPE VFT2_UNKNOWN<br></br>BEGIN<br></br>    BLOCK "StringFileInfo"<br></br>    BEGIN<br></br>        BLOCK "040004e4"<br></br>        BEGIN<br></br>            VALUE "FileVersion", STR_Version<br></br>            VALUE "FileDescription", STR_Description<br></br>            VALUE "ProductName", STR_AppName<br></br>            VALUE "ProductVersion", STR_Version<br></br>            VALUE "CompanyName", STR_Corporation<br></br>            VALUE "LegalCopyright", STR_Copyright<br></br>            VALUE "Comments", "Powered by " STR_Author "."<br></br>            VALUE "OriginalFilename", STR_AppName EXT_Exe<br></br>        END<br></br>    END<br></br>    BLOCK "VarFileInfo"<br></br>    BEGIN<br></br>        VALUE "Translation", 0x0400, 0x04e4<br></br>    END<br></br>END<br></br>

    OK，以后要更改版本号或程序信息，只要修改 Define.h 即可了。

    继续……

    Define.h 中假设 VER_Release/VER_Build 分别指 Release 号和 Build 号，如果让这两个值分别表示我们用 Release 方式编译的次数和总编译次数，多好：）为此我写了个小工具 [BPP](/assets/1098100310.rar) (Build++ 的意思)：

    首先把 BPP.exe 放在工程目录下，然后在 VC Project 属性中，Debug 方式：在“生成事件”->“预生成事件”->“命令行”中输入“BPP Define.h”，Release 方式：“BPP -Release Define.h”。这样，每次 VC 编译都会调用 BPP.exe 使 VER_Build 或 VER_Reelase 自增一。好酷酷吧……
