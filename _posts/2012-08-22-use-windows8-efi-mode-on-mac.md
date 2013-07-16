---
date: 2012-08-22 23:53:11+00:00
layout: post
title: 用 EFI 模式跳过Bootcamp安 装Windows 8 到 Mac
thread: 558
categories: 文档
tags: Mac 折腾
---

——附上安装Windows 8的步骤（2012.08.23更新）—— 

**Mac系列用EFI模式（非BootCamp）安装Win8，就3、4句话：**

**1.在OS X下用磁盘工具调整好Mac使用的空间，预留空闲空间（但不要创建分区，此时只有一个Mac分区(和一个隐藏的EFI分区)，为纯GPT磁盘）；**

**2. 弄个U盘（或者移动硬盘的一个分区）格式化为FAT32，把Win8安装盘释放上去；**

**3.按Option选U盘启动，安装时选择预留的空闲空间，直接下一步安装（不用创建分区） ；**

**（4. 如果遇到重启后黑屏，那么时驱动的问题，此时用Win8启动盘启动，用修复->命令行模式->删掉显卡驱动程序，如Intel的是 ig*.sys）。**

目前遇到的问题是显卡不支持，但可以用Microsoft Basic Video Driver，Windows 评分为悲催的3分——但刚刚发现2011 的MacBook Pro竟然能驱动起来，是Intel HD3000。

<!-- more -->

通过几天的折腾，得出这个结论，终于不用再隔靴抓痒的感觉了。

但Windows 7竟然不行。包括使用 Windows 7 的 boot.wim/install.wim 替换 Windows 8 的相应文件，均不可以。

Windows 7 的boomgr.efi无法被Mac识别，Windows 8的却可以。

____

参考了各种文章，做了各种尝试，证实确实Windows7不行，原因是 Mac系列的EFI版本为1.1，Windows7却需要2.0。万恶的是Mac系列的EFI固件更新的版本好现在都是2.x，实际上这个2.x只是苹果自己的版本号，不是EFI规范的版本号（依然是使用EFI规范1.1）。

http://webcache.googleusercontent.com/search?q=cache:qSac_SCBRWgJ:darobins.wordpress.com/2009/10/04/native-uefi-windows-7-boot-on-mac-mini/+EFI+Shell+1.1+Mac&cd=10&hl=zh-CN&ct=clnk

要么苹果升级支持EFI 2.0，要么装Windows 8，看来，苹果还是不如微软更靠得住⋯⋯
<del>1. 准备好 Windows 8 安装盘：</del>
<del>   1）强烈不建议刻盘，直接用U盘或者移动硬盘即可（但移动硬盘要装换成GPT格式会丢失数据哦）;</del>

<del>   2）用工具（如DiskGen或者Paragon之类的）把U盘重新初始化为GPT分区（Hyrid GPT也可以好像，这样通用性更广泛了，但在Mac下格式化成 Hyrid GPT，我尝试了，但似乎不行，具体我忘了）;</del>

<del>   3）重建一个FAT32分区;</del>

<del>   4）直接把 Windows 8 的ISO的内容，复制到U盘上。</del>

<del>   5）没有了，看到了么，不需要 bootsect 之类的了，因为 EFI （至少Mac系类的EFI）是直接引导GPT分区中 /efi/boot/bootx64.efi 文件的。引导分区只能是 FAT/FAT32（这似乎是EFI的规范，但苹果的EFI同时支持HPFS）。 </del>

<del>2. 在 Mac 下准备好磁盘空间：在 磁盘工具 中，调整小Mac的分区，或者删除掉之前你正在使用的 BootCamp 分区，总之，留下一片可用空间来装 Windows 8——但是记住，不要分区，留空（让Windows 8来分区）。</del>

<del>3. 把U盘插入，按Option 启动，选择U盘的黄色图标 EFI Boot，可以用纯 EFI 方式启动安装盘。</del>

<del>4. 安装选择分区的时候，在刚才的空闲磁盘空间中创建分区（这里有一点，似乎原来苹果的第一个EFI分区要删除掉才能安装，我是在安装过程分区的时候删除了，如果不删除，似乎会提示说不能安装，因为要创建MSR分区）。最后创建分区后会有至少4个Windows分区：MSR（保留，没用的）、ESP（Windows启动文件所在，前面提到过EFI无法放在NTFS分区上）、Recovery（Windows恢复环境）、NTFS主分区。</del>

<del>5. 剩下的，正常安装下去，安装好后启动速度大大快过BootCamp（跳过了Mac第一个EFI分区的EFI to BIOS 模拟层），运行速度似乎也更快了。</del>

<del>6. MacBook上部分驱动目前工作不正常（无论是否Bootcamp），比如光线感应（亮度自动很暗，悲催）。</del>
