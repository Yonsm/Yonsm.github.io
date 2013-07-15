---
date: 2008-09-04 19:23:30+00:00
layout: post
title: IME Support for RichInk
thread: 430
categories: 文档
tags: WM 编程
---

一般来说，PPC 下有两种输入法，一种是 SIP （如梅花输入法） 一种是 IME（如A4的数字硬键盘输入法）。  
  
最近把 RichInk 移植到 SP 中，发现不能激活 IME 输入。IME 是 IMM 管理的，，经过分析发现 RichInk 在PPC下也不支持 IME 的，仅支持 SIP输入。但SP下的输入法没有 SIP 的，一般都是IME的<!-- more -->（少量不正规的输入法也不是IME的，是乱来的，比如以前很炮火的无敌快手，但现在估计没人用了）。  
  
我在 WM6下看到一个 Shell函数 SHSetImeMode。于是尝试SubClass RichInk，发现只有在WM_IIME_SETCONTEXT的时候调用 SHSetImeMode，才能搞定。  
  
终于有点眉目，但是 WM5/2003都没有这个函数。于是我又反汇编看了一下这个函数在 Aygshell.dll 中的实现，得出代码如下：  
  
 HIMC hImc = ImmGetContext(m_hRichInk);  
 if (hImc)  
 {  
   if (!ImmGetOpenStatus(hImc))  
   {  
     ImmSetOpenStatus(hImc, TRUE);  
     ImmEscape(NULL, hImc, IME_ESC_PRIVATE_FIRST, NULL);  
   }  
 }  
  
就这样搞定了，关键是ImmEscape（...IME_ESC_PRIVATE_FIRST...），一个私有的系统标识，要这个才能把输入法指示图标显示出  
  
以前我也尝试过 ImmSetOpenStatus，其实已经打开输入法了，但就是不能现实 IME 的图标，所以根本就没察觉。我倒！
