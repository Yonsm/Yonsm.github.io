---
date: 2006-02-10 08:35:38+00:00
layout: post
title: naked 函数调用
thread: 175
categories: 文档
tags: Win 编程
---

正常的情况下，我们写一个 C/C++ 函数，即使是一个空函数，编译器也为我们做了不少的工作，生成了一些"必要"的代码。请看下面的函数 (为了说明问题随便写的):   


<!-- more -->  
  

    
    int Test()<br></br> { <br></br>     int iReturn;<br></br>     char szTemp[33];<br></br>     <br></br>     szTemp[0] = 'A';<br></br>     szTemp[1] = '';<br></br>     iReturn = MessageBox(NULL, szTemp, szTemp, MB_OK);<br></br>     MessageBeep(iReturn);<br></br>     return iReturn;<br></br>  }

  


下面是用 VC6 在 Release 方式下编译后的的反汇编代码:

  
  

    
    00401000   sub         esp,24h     // 增加堆栈空间存放局部变量 (24H = 36D，4 字节对齐，注意这里没有为 iReturn 分配空间)<br></br> 00401003   push        esi         // 保存要使用的重要寄存器<br></br> 00401004   lea         eax,[esp+4] // 下面是传递 MessageBox() 要使用的参数<br></br> 00401008   push        0<br></br> 0040100A   lea         ecx,[esp+8] // 编译器愚蠢，根本不用 ECX，两个都是 szTemp，两次 PUSH EAX 不得了<br></br> 0040100E   push        eax<br></br> 0040100F   push        ecx<br></br> 00401010   push        0<br></br> 00401012   mov         byte ptr [esp+14h],41h<br></br> 00401017   mov         byte ptr [esp+15h],0<br></br> 0040101C   call        dword ptr ds:[40509Ch] // 调用 MessageBox()<br></br> 00401022   mov         esi,eax     // 保存返回值到变量 iReturn 。靠！变量 iReturn 自动使用 ESI，编译器太聪明了：）<br></br> 00401024   push        esi<br></br> 00401025   call        dword ptr ds:[4050A0h] // 调用 MessageBeep()<br></br> 0040102B   mov         eax,esi     // 把变量 iReturn 交给 EAX 作为返回值<br></br> 0040102D   pop         esi         // 恢复要使用的重要寄存器<br></br> 0040102E   add         esp,24h     // 减少堆栈空间<br></br> 00401031   ret                     // 堆栈长度减 4 并返回<br></br> 

  


  
这段代码虽然很精干 (都能自动使用寄存器来保存变量了)，但是有的时候我们并不需要编译器提供这些自作主张的代码 (比如写驱动程序的时候，不过我还没遇到过这种情况，呵呵~~)，我们希望整个全部函数都是自己亲手写进去的 (BT 呀^o^)。好，请出今天的主角 ---- "naked"(怎么是裸体呀？)，欢迎！Visual C++ 的扩展关键字 naked 允许我们完全定制一个函数，废话不说了，看例子 (熬夜写的 Zzzzzz~~):

  
  

    
    __declspec(naked) int Test()<br></br> { <br></br>     __asm<br></br>     { <br></br>         SUB         ESP,24H<br></br>         PUSH        ESI<br></br>         LEA         EAX,[ESP+4]<br></br>         PUSH        0                      <br></br>         PUSH        EAX                    <br></br>         PUSH        EAX                    <br></br>         PUSH        0                      <br></br>         MOV         BYTE PTR [ESP+14H],41H <br></br>         MOV         BYTE PTR [ESP+15H],0   <br></br>         CALL        DWORD PTR [MessageBoxA] <br></br>         MOV         ESI,EAX<br></br>         PUSH        ESI                    <br></br>         CALL        DWORD PTR [MessageBeep] <br></br>         MOV         EAX,ESI<br></br>         POP         ESI<br></br>         ADD         ESP,24H<br></br>         RET<br></br>      }<br></br>  }<br></br> 

  


上面的代码是使用的 VC 的内联汇编，和 VC 编译后生成的代码完全是一样的 (很有完全控制的成就感吧^_^)。上面我们并没有又节省什么 (节省的 PUSH ECX 并不是 naked 的功劳)，但是有的时候确实需要的 (举不出例子来了，倒！)。最后随便说说注意事项:   
  
1.使用 naked 关键字需要自己构建 EBP 参数指针 (如果用到了 EBP 作为参数指针的话)；  
2.必须自己使用 RET 或 RET n 指令返回 (除非你不返回)。  


  

