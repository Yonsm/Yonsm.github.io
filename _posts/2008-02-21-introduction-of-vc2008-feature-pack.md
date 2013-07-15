---
date: 2008-02-21 19:03:41+00:00
layout: post
title: '[转载]千呼万唤始出来的 Visual C++ 2008 Feature Pack 介绍'
thread: 403
categories: 文档
tags: 编程
---

  
**缘起：**  
  
自Visual C++ 5.0 6.0 以来一直遭人诟病的是什么？ 过于简单的界面控件！  
作为一个以Visual C++ 作为开发工具的程序员，遇到最郁闷的事情是什么？ 开发一个具有漂亮界面的程序！！  
Visual C++ 不是真正意义上的RAD(Rapidly Application Development)工具的主要原因是什么？ 还是因为没有丰富的界面控件！！！  
  
  
无数的Visual C++程序员为了那几个单调、简单Visual C++的控件苦恼着；而无数的Visual C++程序员由因为这个界面问题而大发其财。BCG Library、Magic Skin 这些专门为解决程序界面问题的库顺势而生。想必绝大多数用Visual C++写成的程序在商业化之前都会经过这些界面库的修饰。使用标准的MFC，想给菜单项加个图标都得通过自己派生一个类来做的情况下，你还指望自己能包揽程序的界面开发么？说老实话，measure这个单词就是那时候记住的。(MeasureItem 和 DrawItem 这两个可重载的函数是MFC给程序员预留的扩展界面的接口。)  
  
自Visual C++ 6.0 以后，一直强调用户体验的Microsoft 也坐不住了。Visual Studio 2002 、2003的平面风格，给大家耳目一新的感觉，引领了时代潮流。而后的 Office 2003 界面一时间也是独领风骚。可是这些界面库都是MS自己留着用，从没想到拿出来。终于，终于在Visual Studio 2005 里面，.NET 程序员可以毫不费力的使用Office 2003 风格的界面控件了。TextBox控件也衍生出了很多小弟弟，限制某些字符的输入，也不用去响应TextChanged、KeyDown等事件了。但是Visual C++程序员肯定是再一次的失望了。在这几个版本的Visual Studio 中我没有看到MFC的本质的提升(添加CImage 类不能算是大幅度改进。其实对于图像操作，VC程序员们早就自力更生自己解决了。)   
  
2008年01月07日，MS总算是没有忘记这些使用Visual C++的老朋友。推出了 Visual C++ Feature Pack Beta 下载。这次的Feature Pack 是专门针对VC 库的一个扩充。扩充分为两方面，一方面是MFC 的界面控件库；另一方面是对ISO C++ Standard 2003 标准的扩充。  
  
**部署：  
**  
部署这个东东可是有点不容易哦！部署这个东东首先需要的是耐心，其次还是耐心，最后给自己找本书看吧，不然你呆呆的盯着电脑一下午可能会疯掉。  
首先需要到微软的[下载中心](http://www.microsoft.com/downloads) 下载 [Visual C++ Feature Pack Beta](http://www.microsoft.com/Downloads/details.aspx?familyid=D466226B-8DAB-445F-A7B4-448B326C48E7&displaylang=en) 下载这个303M的大家伙一定得挑个黄道吉日，沐浴净身，！@#￥%……  
而后，你需要在机器上安装了英文版的Visual Studio 2008。别的语种Feature Pack不支持，看样子也装不上。2005？ Visual C++ 开发组的某个人在Blog上说可以(引用原文* Older versions of VC (e.g. VC8).)，可是下载中心上没这么说。自己看着办吧。 VS_Setup.exe 运行以后生成那个安装脚本的时间，相比大家心里有数吧？大家应该在安装 VS2005 的时候就领教过了。  
  
接着，接着就该安装这个Feature Pack 了吧？错！你以为安装了Visual Studio 2008 就没事儿啦？一定要完全安装才可以！完全安装VS2008哦！就连SQL Sever 2005 Express 和 水晶报表的基本组件也不能少！ 偶就是吃了这个亏，结果导致Feature Pack 安装到一半的时候出现错误回滚。错误如下：  
  
Returning IDOK. INSTALLMESSAGE_ERROR [Error [1].An installation package for the product [2] cannot be found. Try the installation again using a valid copy of the installation package '[3]'.: 1706Microsoft Visual Studio Team System 2008 Team Suite - ENU]  
[1/15/2008, 7:38:27] (HotIron::CMspExternalUiHandler::UiHandler) Returning IDOK. INSTALLMESSAGE_ACTIONSTART [Action 15:38:27: Rollback. Rolling back action:]  
[1/15/2008, 7:39:12] (HotIron::MspInstallerT > > > >::PerformMsiOperation>Patch (VS90-VCFeaturePack-Beta-KB945273-x86x64-ENU.msp) install failed on product (Microsoft Visual Studio Team System 2008 Team Suite - ENU). Msi Log: [Visual C++ 2008 Beta Feature Pack - KB945273_20080115_073311988-Msi0.txt](file:///C:/Users/Michael%20Lee.Michael-Lee/AppData/Local/Temp/Visual%20C++%202008%20Beta%20Feature%20Pack%20-%20KB945273_20080115_073311988-Msi0.txt)  
[1/15/2008, 7:39:12] (HotIron::MspInstallerT > > > >::PerformMsiOperation>MsiApplyMultiplePatches returned 0x643  


[[1/15/2008, 7:39:12] Entering Function: HotIron::MspInstallerT > > > >::Rollback...  
](file:///C:/Users/Michael%20Lee.Michael-Lee/AppData/Local/Temp/Visual%20C++%202008%20Beta%20Feature%20Pack%20-%20KB945273_20080115_073311988.html#)

当时试了几次都这样。结果在偶彻底晕之前想起了Google，还不错，MSDN论坛上有个伙计说，VS2008必须得完全安装。My God，偶把以前没装的VC for IA64装上了，再试，失败。 我把没装的Visual Basic 装上了，再试，还是失败。直到我彻底缴枪把SQL Server 2005 Express 和水晶报表基本组件也选上了，才确保无恙。My God!，更新和拷贝几个VC文件夹下的文件干啥还要水晶报表？在这装装卸卸期间，您手上的书就派上用场了。啊？想上网？ Visual Studio 在更新、安装、卸载期间IE是不能使用的，还是看书吧。  
  
各位记住！想安装Visual C++ Feature Pack Beta 一定要完完全全的安装VS 2008，一点儿都不能少！  
  
确认之后，就可以运行Feature Pack的安装包了，请注意，如果您是Vista，千万别忘了"Run as Administrator"。运行后，HotfixInstaller服务将启动，并安装Feature Pack更新。安装过程顺利的话大概也要20分钟以上的时间，您还得勤盯着点儿，HotfixInstaller服务有可能没有原因的挂在那里长时间不动(不是Not Responding状态)。不用害怕，只要直接在Task Manager中结束掉进程，并重新运行安装包就可以了。(上帝保佑，阿弥陀佛@#￥%……)  
  
**初探：  
**终于搞定了，看看效果吧。唉，天色已晚，不打算自己写程序了。从下载中心找到了 [Visual C++ 2008 Sample Library](http://www.microsoft.com/Downloads/details.aspx?familyid=01AE159F-08CD-495B-8BF4-A48CC395AD7B&displaylang=en) 这个快，5M，下载，安装。  
  
在\Microsoft Visual Studio 9.0\Samples\1033 下找到AllVCLanguageSamples.zip 展开，找到Feature Pack 文件夹，打开里面的工程编译。终于看到Feature Pack 支持后界面了！下图是基于Feature Pack 库开发的仿Outlook界面：  
![](http://www.cnblogs.com/images/cnblogs_com/michaellee/OutlookDemo2.jpg)  
  
漂亮吧？ 这可不是用非微软提供的函数库实现的哦！在Feature Pack例子里面有一个叫做New Control的工程。编译后，您可以看到所有Feature Pack已经实现好的界面控件。  
  
先是按钮控件组：  
![](http://www.cnblogs.com/images/cnblogs_com/michaellee/NewControl_Buttons.jpg)  
  
类型非常丰富，比CButtonST毫不逊色，赞一个！  
接着是颜色选
