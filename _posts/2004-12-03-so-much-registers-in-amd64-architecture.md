---
date: 2004-12-03 21:39:54+00:00
layout: post
title: AMD64 架构，寄存器可真多啊
thread: 94
categories: 日志
---

寄存器多的一塌糊涂：16 个 8 位通用寄存器、16 个 16 位通用寄存器、16 个 32 位通用寄存器、16 个 64 位通用寄存器，8 个 MM/FP 64 位寄存器，16 个 XMM 128 位寄存器……

_下面的文字摘自 《AMD64 Architecture Programmer’s Manual Volume 1: Application Programming》_

    The AMD64 architecture introduces these new features:<!-- more -->

  * Register Extensions (see Figure 1-1 on page 2):  
- 8 new general-purpose registers (GPRs).  
- All 16 GPRs are 64 bits wide.  
- 8 new 128-bit XMM registers.  
- Uniform byte-register addressing for all GPRs.  
- A new instruction prefix (REX) accesses the extended registers.
  * Long Mode (see Table 1-1 on page 3):  
- Up to 64 bits of virtual address.  
- 64-bit instruction pointer (RIP).  
- New instruction-pointer-relative data-addressing mode.  
- Flat address space.

下面是寄存器图示和说明，均摘自 AMD64 程序员手册:

![](http://yonsm.reg365.com/up/1102052059.gif)

    In 64-bit mode, eight new GPRs are added to the eight legacy  
GPRs, all 16 GPRs are 64 bits wide, and the low bytes of all  
registers are accessible. Figure 3-3 on page 31 shows the GPRs,  
flags register, and instruction-pointer register available in 64-  
bit mode. The GPRs include:

  * Sixteen 8-bit low-byte registers (AL, BL, CL, DL, SIL, DIL, BPL, SPL, R8B, R9B, R10B, R11B,  R12B, R13B, R14B, R15B).
  * Four 8-bit high-byte registers (AH, BH, CH, DH), addressable only when no REX prefix is used.
  * Sixteen 16-bit registers (AX, BX, CX, DX, DI, SI, BP, SP, R8W, R9W, R10W, R11W, R12W, R13W, R14W, R15W).
  * Sixteen 32-bit registers (EAX, EBX, ECX, EDX, EDI, ESI, EBP, ESP, R8D, R9D, R10D, R11D, R12D, R13D, R14D, R15D).
  * Sixteen 64-bit registers (RAX, RBX, RCX, RDX, RDI, RSI, RBP, RSP, R8, R9, R10, R11, R12, R13, R14, R15).
