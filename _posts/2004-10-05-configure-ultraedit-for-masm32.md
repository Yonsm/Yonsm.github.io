---
date: 2004-10-05 16:29:54+00:00
layout: post
title: 配置 UltraEdit 为 MASM32 的IDE
thread: 163
categories: 文档
---

　　一段老文字，存此，权当存档。（主要是为 UE 的语法高亮文件 WordFile.txt 存档：）   
  
　　闲着没事，随意写一下怎样配置 UltraEdit，使之成为 MASM32 的IDE。   
  
  
一、准备工作   
  
　　这里先假设：   
　　　　1. UltraEdit 安装在 C:Program FilesUltraEdit，我的是 10.0a 汉化版；   
　　　　2. MASM32 安装在 F:MASM32。   
  
  
二、建立批处理   
  
　　先说说 MASM32 中一些命令的参数，初学者经常犯的一个错误是在编译连接的时候忘记添加库的路径。以下是   
常用的命令简介，详细情况请参见相关的命令帮助。   
  
　　1. Ml.exe /c /coff /IMASM32Include x.asm   
　　　　以上参数请注意大小写；/I参数和路径之间没有空格。   
  
　　2. Rc.exe /iMASM32Include Resource.rc   
　　　　同上，注意参数/i。   
  
　　3. Link.exe /SUBSYSTEM:Console /LIBPATH:MASM32Lib %1.OBJ   
　　　　SUBSYSTEM 是目标文件的子系统类型，一般有 Windows 和 Console；/LIBPATH 是 lib 库文件的路径。   
  
　　建立一个符合自己的 编译连接批处理文件，比如我的为 MASM32ASMBAT.bat：   
  
////////////////////////////////////////////////////////////////////////////////////////////////////   
@ECHO OFF   
  
IF NOT EXIST Masm32BinMl.Exe GOTO _NoMasm32   
  
IF EXIST %1.obj DEL %1.obj   
IF EXIST %1.asm MASM32BinMl.exe /IMASM32Include /c /coff %1.asm   
IF EXIST Resource.rc GOTO _ExistRC   
IF EXIST %1.obj MASM32BinLink.exe /SUBSYSTEM:Console /LIBPATH:MASM32Lib %1.obj   
GOTO _Done   
  
:_ExistRC   
IF NOT EXIST Resource.res MASM32BinRc.exe /iMASM32Include Resource.rc   
IF EXIST %1.obj MASM32BinLink.exe /SUBSYSTEM:Windows /LIBPATH:MASM32Lib %1.obj Resource.res   
  
:_Done:   
IF EXIST %1.obj DEL %1.obj   
GOTO :_End   
  
:_NoMasm32   
ECHO Could not find "Masm32BinMl.Exe".   
  
:_End   
////////////////////////////////////////////////////////////////////////////////////////////////////   
  
　　上面的批处理请根据实际需要修改。当然，你也可以使用 MASM32 中自带的批处理文件，但是我觉得不方便。   
  
  
三、配置 UltraEdit   
  
　　修改 UltraEdit 的语法高亮文件 Wordfile.txt，使之支持 ASM 语法高亮，附件中带有支持 ASM 语法高亮的   
Wordfile.txt，用它覆盖 UltraEdit 自带的即可。   
  
　　打开 UltraEdit，从菜单“高级”->“工具配置”添加一条外部命令：   
  
////////////////////////////////////////////////////////////////////////////////////////////////////   
命令行：F:MASM32BINBW.BAT %N   
工作目录：%P   
菜单项名称：汇编连接(&B;)   
选定“保存活动文件”   
选定“采集输出”   
选定“输出到列表方块”   
然后点“插入”   
////////////////////////////////////////////////////////////////////////////////////////////////////   
  
　　以上 %N 代表当前打开文件的名称（不包括扩展名），%P 代表当前打开文件所在的目录，这些都是宏替换，   
详细情况请参看 UltraEdit 的帮助。在“工具配置”的对话框中，还有“高级”按钮，里面可以自定义此命令的   
图标。   
  
　　最后自定义 UltraEdit 的工具栏，添加“高级”菜单下面的“工具1”等到工具栏中，以后可以从工具栏中直   
接执行这条命令。当然，也可以通过内置的热键调用这条命令：Ctrl+Shift+工具号。   
  
  
下载附件: [UEASM.rar](/assets/1097148757.rar)，包括示例 BAT 文件和 UE 的语法高亮文件 WordFile.txt。
