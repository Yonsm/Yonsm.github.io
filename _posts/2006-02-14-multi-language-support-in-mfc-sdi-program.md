---
date: 2006-02-14 08:48:31+00:00
layout: post
title: 在 MFC SDI 程序中实现多语言程序界面
thread: 178
categories: 文档
tags: Win 编程
---

今天举个例子，说说怎样使用 [CLanguage](read.php?177) 类，在 MFC SDI 程序中实现多语言程序界面。 

  


因为 MFC 包装了一些字符串显示处理，所以与 Win32 工程中可能有一点点不一样。主要有两个地方:

<!-- more -->  
  


  * 因为语言列表菜单项是动态生成的，MFC 的机制导致这些菜单项是不可用的。所以必须在 Update Command UI 的时候，使语言列表菜单项可用。 
  * 菜单提示是 CFrameWnd 实现的，我们必须重载他的 GetMenuString()，用 CLanguage 的 TranslateString() 替换它的 AfxLoadString() 载入资源字符串。 

下面说说简要的步骤吧:

  


  1. 把 Language.h/cpp 加入到工程的，在 cpp 中 #include "StdAfx.h"。 
  2. 定义一个全局变量 g_hInst，在 InitInstance() 中使它赋值为资源模块句柄 (一般为 theApp.m_hInstance)。 
  3. InitInstance() 中 调用 CLanguage::Initialize() 确定当前要使用的语言。 
  4. CMainFrame::OnCreate() 中调用 CLanguage::TranslateMenu() 翻译主菜单。 
  5. 重载 CFrameWnd::GetMenuString()，用 CLanguage::TranslateString() 替换它的 AfxLoadString() 载入资源字符串。 
  6. 每个对话框的 OnInitdialog() 中调用 CLanguage::TranslateDialog() 翻译对话框。 
  7. 其它与 Win32 工程一样……

另外，如果在 MDI 中使用，可能稍有不一样，因为我在另一篇文章中说过，Popup Menu 的 位置不能改变。所以，每次切换语言的时候，必须使所有的 MDI 子窗口不要最大化 (因为最大化会在主菜单中加入一个图标菜单，那样 Popup 位置就变了)……

  


看代码吧……  


  


下载: [SdiML](/assets/1101305671.rar) (34K，Visual C++ 6 项目) 

  

