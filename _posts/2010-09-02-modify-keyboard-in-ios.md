---
date: 2010-09-02 11:00:55+00:00
layout: post
title: 在 iPhone/iPad 中随意修改数字键盘按钮
thread: 516
categories: 文档
tags: iOS 编程
---

一、起因  
  
iPhone 的键盘，特别是数字键盘，往往不能满足程序的输入需要。最典型的例子就是在数字键盘上添加一个“.”，用来输入小数点。安装 iPhone SDK 官方的观点，如果要使用小数点键盘，那只好使用数字和符号键盘，但那样没个按键很小，且不需要的按键太多。  
<!-- more -->  
  
二、现有方案  
  
针对这种情况，最早的解决方案，请参考这里：[http://www.cnblogs.com/mac_arthur/archive/2010/05/18/1738363.html](http://www.cnblogs.com/mac_arthur/archive/2010/05/18/1738363.html)。使用的是 以下代码来检测一个 Notification。  


[[NSNotificationCenter defaultCenter] addObserver:self   
                                         selector:@selector(addCustomKeyBoardButton)  
                                                name:UIKeyboardWillShowNotification  
                                              object:nil];

  
  
这种方法，在 iOS 4.0 后失效了，原因有两个，一是UIKeyboardWillShowNotification的时候，键盘根本没有创建出来;另外，Class Name 也被外包了一层，叫做UIPeripheralHostView。  
  
于是又有了一种改进的方案，请看这里：[http://www.neoos.ch/news/46-development/54-uikeyboardtypenumberpad-and-the-missing-return-key](http://www.neoos.ch/news/46-development/54-uikeyboardtypenumberpad-and-the-missing-return-key)。主要的改进是在UIKeyboardDidShowNotification的通知消息中来修改键盘。但正如作者所说，这里有个不完美的情况，只能等键盘动画显示完成之后，才能添加显示我们的东西，视觉效果不好。  
  
三、改进方案  
  
经过试验，找到一个比较完美的方案：在 UITextField 的becomeFirstResponder和resignFirstResponder中修改键盘。  
  
定以一个类，假如叫做 KBCustomTextField : UITextField，在这个类中加入一下代码：  


  
//  
- (BOOL)becomeFirstResponder  
{  
 BOOL ret = [super becomeFirstResponder];  
 [self modifyKeyView:@"NumberPad-Empty" display:@"." represent:@"." interaction:@"String"];  
 return ret;  
}  
  
//  
- (BOOL)resignFirstResponder  
{  
 BOOL ret = [super resignFirstResponder];  
 [self modifyKeyView:@"NumberPad-Empty" display:nil represent:nil interaction:@"None"];  
 return ret;  
}  


  
  
modifyKeyView 的实现可以参看附件。我使用的是循环查找UIKBKeyView类，这是Apple 的 Private API（私有API的声明可以在这里找：[http://github.com/kennytm/iphone-private-frameworks/tree/master/UIKit/](http://github.com/kennytm/iphone-private-frameworks/tree/master/UIKit/)），不确信能否通过 App Store 的审核：）  
  
更近一步地，我完善了一下 KBCustomTextField，通过这个类，非常方便地就可以做到自定义输入键盘：  
  
[KBCustom.zip](/assets/1283431378_9792baf4.zip)  
  
1. 使用小数点和数字键盘：非常简单，只要在 IB 中把 UITextField 的类改成KBCustomTextField，就OK了，不用一行代码，效果如下图：  
[![](/assets/1283431378_38117112.png)](/assets/1283431378_38117112.png)  
  
2. 在键盘的按键上添加一个文字按钮（并指定处理动作）：设置KBCustomTextField.kbDelegate，实现这两个函数即可：  
  


  
// [Yonsm] Handle keyboard show  
- (void)keyboardShow:(KBCustomTextField *)sender  
{  
 [sender addCustomButton:@"NumberPad-Empty" title:@"DONE" target:self action:@selector(onButton:)];  
}  
  
// [Yonsm] Handle keyboard hide  
- (void)keyboardHide:(KBCustomTextField *)sender  
{  
 [sender delCustomButton:@"NumberPad-Empty"];  
}  


  
[![](/assets/1283431378_98952583.png)](/assets/1283431378_98952583.png)  
  
3. 更近一步地，这两个 Delegate 函数中，你只要通过 name 来查找到想要修改的 UIKBKeyView，就可以随便修改它。name 可以通过 KBCustomTextField 的#define _LOG_KEY_VIEW来列出所有的按键名称。name 为 nil 则找任何的 UIKBKeyView（可以用他的 .superview 来找到整个键盘View，做更多的处理）。  
[![](/assets/1283431378_246664d4.png)](/assets/1283431378_246664d4.png)  
  
  
下面是 iPhone 数字键盘的前面10个按键（后面忘了打出来了：）  
  


  
Found View: UIPeripheralHostView  
Found View: UIKeyboardAutomatic  
Found View: UIKeyboardImpl  
Found View: UIKeyboardLayoutStar  
Found View: UIKBKeyplaneView  
Found View: UIKBKeyView  
 name=NumberPad-1  representedString=1  displayString=1  displayType=NumberPad  interactionType=String  displayRowHint=Row1  
Found View: UIKBKeyView  
 name=NumberPad-2  representedString=2  displayString=2/ABC  displayType=NumberPad  interactionType=String  displayRowHint=Row1  
Found View: UIKBKeyView  
 name=NumberPad-3  representedString=3  displayString=3/DEF  displayType=NumberPad  interactionType=String  displayRowHint=Row1  
Found View: UIKBKeyView  
 name=NumberPad-4  representedString=4  displayString=4/GHI  displayType=NumberPad  interactionType=String  displayRowHint=Row2  
Found View: UIKBKeyView  
 name=NumberPad-6  representedString=6  displayString=6/MNO  displayType=NumberPad  interactionType=String  displayRowHint=Row2  
Found View: UIKBKeyView  
 name=NumberPad-7  representedString=7  displayString=7/PQRS  displayType=NumberPad  interactionType=String  displayRowHint=Row3  
Found View: UIKBKeyView  
 name=NumberPad-8  representedString=8  displayString=8/TUV  displayType=NumberPad  interactionType=String  displayRowHint=Row3  
Found View: UIKBKeyView  
 name=NumberPad-9  representedString=9  displayString=9/WXYZ  displayType=NumberPad  interactionType=String  displayRowHint=Row3  
Found View: UIKBKeyView  
 name=NumberPad-Empty &nbs;
p;representedString=  displayString=  displayType=NumberPad  interactionType=None  displayRowHint=Row4

  
  
代码对 iPad 也有效，当然 Key Name 和  Type 不一样，下面是 iPad 数字键盘的Log：  
  


Found View: UIPeripheralHostView  
Found View: UIKeyboardAutomatic  
Found View: UIKeyboardImpl  
Found View: UIKeyboardLayoutStar  
Found View: UIKBKeyplaneView  
Found View: UIKBKeyView  
 name=Digit-1  representedString=1  displayString=1  displayType=String  interactionType=String-Popup  displayRowHint=Row1  
Found View: UIKBKeyView  
 name=Digit-2  representedString=2  displayString=2  displayType=String  interactionType=String-Popup  displayRowHint=Row1  
Found View: UIKBKeyView  
 name=Digit-3  representedString=3  displayString=3  displayType=String  interactionType=String-Popup  displayRowHint=Row1  
Found View: UIKBKeyView  
 name=Digit-4  representedString=4  displayString=4  displayType=String  interactionType=String-Popup  displayRowHint=Row1  
Found View: UIKBKeyView  
 name=Digit-5  representedString=5  displayString=5  displayType=String  interactionType=String-Popup  displayRowHint=Row1  
Found View: UIKBKeyView  
 name=Digit-6  representedString=6  displayString=6  displayType=String  interactionType=String-Popup  displayRowHint=Row1  
Found View: UIKBKeyView  
 name=Digit-7  representedString=7  displayString=7  displayType=String  interactionType=String-Popup  displayRowHint=Row1  
Found View: UIKBKeyView  
 name=Digit-8  representedString=8  displayString=8  displayType=String  interactionType=String-Popup  displayRowHint=Row1  
Found View: UIKBKeyView  
 name=Digit-9  representedString=9  displayString=9  displayType=String  interactionType=String-Popup  displayRowHint=Row1  
Found View: UIKBKeyView  
 name=Digit-0  representedString=0  displayString=0  displayType=String  interactionType=String-Popup  displayRowHint=Row1  
Found View: UIKBKeyView  
 name=Hyphen-Minus  representedString=-  displayString=-  displayType=String  interactionType=String-Popup    
Found View: UIKBKeyView  
 name=Solidus  representedString=/  displayString=/  displayType=String  interactionType=String-Popup  displayRowHint=Row2  
Found View: UIKBKeyView  
 name=Colon  representedString=:  displayString=:  displayType=String  interactionType=String-Popup  displayRowHint=Row2  
Found View: UIKBKeyView  
 name=Semicolon  representedString=;  displayString=;  displayType=String  interactionType=String-Popup    
Found View: UIKBKeyView  
 name=Left-Parenthesis  representedString=(  displayString=(  displayType=String  interactionType=String-Popup    
Found View: UIKBKeyView  
 name=Right-Parenthesis  representedString=)  displayString=)  displayType=String  interactionType=String-Popup    
Found View: UIKBKeyView  
 name=Primary-Currency-Sign  representedString=$  displayString=$  displayType=DynamicString  interactionType=String-Popup  
Found View: UIKBKeyView  
 name=Ampersand  representedString=&  displayString=&  displayType=String  interactionType=String-Popup    
Found View: UIKBKeyView  
 name=Commercial-At  representedString=@  displayString=@  displayType=String  interactionType=String-Popup    
Found View: UIKBKeyView  
 name=Full-Stop  representedString=.  displayString=.  displayType=String  interactionType=String-Popup    
Found View: UIKBKeyView  
 name=Comma  representedString=,  displayString=,  displayType=String  interactionType=String-Popup  displayRowHint=Row3  
Found View: UIKBKeyView  
 name=Question-Mark  representedString=?  displayString=?  displayType=String  interactionType=String-Popup    
Found View: UIKBKeyView  
 name=Exclamation-Mark  representedString=!  displayString=!  displayType=String  interactionType=String-Popup    
Found View: UIKBKeyView  
 name=Apostrophe  representedString='  displayString=’  displayType=String  interactionType=String-Popup    
Found View: UIKBKeyView  
 name=Quotation-Mark  representedString="  displayString=”  displayType=String  interactionType=String-Popup    
Found View: UIKBKeyView  
 name=Delete-Key  representedString=Delete  displayString=delete  displayType=Delete  interactionType=Delete    
Found View: UIKBKeyView  
 name=Return-Key  representedString=  
interactionType=Return  displayRowHint=Row2  
Found View: UIKBKeyView  
 name=Undo-Key  representedString=undo  displayString=undo  displayType=Command  interactionType=Undo  displayRowHint=Row3  
Found View: UIKBKeyView  
 name=More-Key  representedString=More  displayString=more  displayType=More  interactionType=More  displayRowHint=Row4  
Found View: UIKBKeyView  
 name=Unlabeled-Space-Key  representedString=   displayString=  displayType=Space  interactionType=Space    
Found View: UIKBKeyView  
 name=More-Key  representedString=More  displayString=more  displayType=More  interactionType=More  displayRowHint=Row4  
Found View: UIKBKeyView  
 name=Dismiss-Key  representedString=Dismiss  displayString=Dismiss  displayType=Dismiss  interactionType=Dismiss    
Found View: UIKBKeyView  
 name=Shift-Key  representedString=Shift  displayString=shift  displayType=Shift  interactionType=Shift  displayRowHint=Row3  
Found View: UIKBKeyView  
 name=Shift-Key  representedString=Shift  displayString=shift  displayType=Shift  interactionType=Shift  displayRowHint=Row3
