---
date: 2006-02-13 08:43:59+00:00
layout: post
title: 用 INI 文件实现程序多语言界面
thread: 177
categories: 文档
tags: Win 编程
---

**一、优点**

  


比起使用资源 DLL 实现多语言程序，INI 方式的具有更多的扩展性，任何一个普通用户都可以做出任何一种语言界面。

  


**二、功能**

  


为了做到完美的多语言程序，我们设计一个 CLanguage 静态类 (因为是静态类，改为 C 代码只要一点简单的工作)，应该实现如下功能：

<!-- more -->  


  * 每个语言一个 INI 文件 (特别地，把语言文件扩展名定为 .lng，符合 INI 格式)。 
  * 没有外部语言情况下，使用程序内置的默认语言。 
  * 能动态切换到任何一种语言 (包括内置语言)，而不是告诉用户切换语言要重新启动程序。 
  * 没有选择语言的状态下 (比如程序刚安装)，自动根据当前用户环境选择语言文件 (如果有的话，没有则使用默认语言)。 
  * 列出程序目录下的 .lng 文件，并加入到菜单中。 
  * 不同的语言可能造成界面上不同的显示效果，所以应该允许在语言文件中指定字体 (程序的资源中还应该考虑不同语言的情况，如 Static Text 控件是否够宽，以容纳其它语言的文本)。 
  * 使原有的程序做尽量少的改动，加入 CLanguage 后，作少量改动即可实现多语言。 
  * 可以定义 #define _MAKELANG 宏，这样编译后，使程序自动生成语言文件。 
  * 支持 UNICODE 方式编译。

**三、实现**

  


先想想，程序中与语言相关的文本有哪些……，嗯……，不过就如下四个嘛：

  


  * 常量文本 (任何在代码中的 UI 文本)。 
  * 资源文本。 
  * 菜单文本。 
  * 对话框文本。

一个一个来，各个击破：

  


1. 常量文本: 放在语言文件的 [Text] 节中，每个文本对应一个 ID。程序中使用到常量文本的时候，如果语言文件中存在该 ID 的文本，则使用它，否则，使用内部的常量文本。

  


2. 资源文件: 放在语言文件的 [String] 节中，这个最简单了，就使用资源文本的 ID。原来所有使用 LoadString 的地方，改用 CLanguage::TraslateString，即现尝试从语言文件中载入文本。

  


3. 菜单文本: 放在语言文件的 [%菜单资源名%] 节中。当菜单被载入后，调用 CLanguage::TranslateMenu 翻译菜单。菜单的处理有点麻烦。如果菜单是命令项，则使用命令 ID 作为标识，如果是弹出项，则使用位置作为标识 (因此弹出菜单的位置不能改变，不过这点很容易做到)。另外，切换到内置语言的时候，需要重新载入菜单资源中的菜单文本，这个实现起来挺麻烦的，还要考虑是 MENU 还是 MENUEX 资源。嘿嘿，不过我都实现就是了，只管直接使用 :) ……

  


4. 对话框文本: 和菜单的实现方式差不多。对话框初始化后，调用 CLanguage::TranslateDialog 翻译对话框上的文本。对话框上的控件必须具有 ID (在此对话框内唯一，因为 不能再使用 IDC_STATIC 这种 ID 了)。同菜单一样，对话框也有切换到内置语言的问题，不过这里我忽略了它，因为我假设切换语言是在主窗口中进行，此时没有任何对话框显示的。如果是基于对话框的程序，可以仿造菜单的代码写一个从对话框资源中载入文本的代码，不过挺烦、难的，还是算了吧，变通一下，想法子重新 DialogBox 一遍，嘿嘿，搞定……

  


好了，开始写代码……

  


.......

  


**四、使用**

  


呵呵~~，搞定，Clanguage 部分声明如下:

  


// 初始化语言，返回确定要使用的语言  
static LANGID Initialize();

  


// 列出语言到菜单中  
static UINT List(HMENU hMenu);

  


// 设置语言  
static VOID Set(HMENU hMenu, UINT uLang);

  


// 获取语言描述，比如语言是谁翻译制作什么的  
static PTSTR GetDescription(HMENU hMenu, UINT uLang);

  


// 获取常量文本  
static PTSTR TranslateText(PCTSTR ptzName, PCTSTR ptzDefault = NULL);

  


// 获取常量文本，并替换特殊字符 (替换换行和零字符，有时候要用到，比如多行文本，又比如 GetOpenFileName 使用到的 Filter 字符串列表，需要替换零字符)  
static PTSTR TranslateTextEx(PCTSTR ptzName, PCTSTR ptzDefault = NULL);

  


// 获取资源字符串  
static PTSTR TranslateString(UINT uResID);

  


// 更新菜单  
static VOID TranslateMenu(HMENU hMenu, PCTSTR ptzResName);

  


// 更新对话框  
static VOID TranslateDialog(HWND hWnd, PCTSTR ptzResName);

  


常量文本因为需要指定关联 ID，所以应该放在一起 (即使不是多语言，也应该养成习惯，把所有的字符串放在一起，用宏来引用这些字符串) 。在 Language.h 中，我定义了如下四个宏，下面是其中两个:

  


#define _Lang(n, a) CLanguage::TranslateText(TEXT(#n), TEXT(a))  
#define _LangEx(n, a) CLanguage::TranslateTextEx(TEXT(#n), TEXT(a)) // 多行文本或字符串组

  


比如用到以下常量字符串，都放在 Define.h 中吧:

  


#define LNG_Ready _Lang(0, "Ready.")  
#define LNG_BmpFilter _LangEx(1, "Bitmap Files(*.bmp)*.bmp")  
... (等等，ID 不重复，为了美观，连续递增比较好看:)

  


  
具体使用看代码吧，三言两句讲不清楚，还有不少注意事项的，挺晚的了，我要看看电视睡觉了……

  


下载: [MultiLang](/assets/1101221272.rar) (32 KB，包括示例代码和可重用 CLanguage 静态类)

  

