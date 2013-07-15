---
date: 2012-03-03 22:02:22+00:00
layout: post
title: 在 Mac OS X 中使用 GPT vs. MBR   | 启用BCM4331的Linux支持
thread: 556
categories: 文档
tags: Mac 折腾
---

昨天差点把MacBook Pro的分区全部干掉了，折腾了一整天终于完整无损地修复了。同时搞明白了Mac系列的GPT、MBR、BootCamp分区表的林林种种。  
  
Mac 的 GPT/GUID 分区表并非纯的 GPT，而是叫做 Retained GPT或Hyrid GPT（保留/兼容/混合GPT，Paragon Partition Manager 叫法）：意即使用GPT的同时，还兼容MBR分区表。<!-- more -->但只能支持前面4个分区，包括EFI分区在内，非特殊情况下，分区越多越不利于空间利用，我个人习惯是少分区，所以MBR足够用了。  
  
假设我的硬盘分区是GUID分区表：EFI+MAC+WIN+LIN，这是种情况下WIN和LIN都是通过EFI转手（模拟BIOS）再启动的；此时EFI分区加载需要不少的时间，如果硬盘是MBR分区表格式则可以干掉这个分区，一样能启动Windows和Linux，这时候Windows将不再需要EFI支持了。这种情况下的优势是：1.启动速度快了不少（跳过了EFI模拟BIOS的部分）。这样做的唯一坏处就是Mac将不能再重新装了（只是不能重新安装，使用和升级没有任何问题，性能没有任何影响。如果要重新安装，可以破解OSInstall.pkg）。  
  
如果是磁盘空间金贵 MacBook Air 的用户，只想安装 Windows 的话，建议完全重新把硬盘初始化为 MBR 格式，干掉所有的分区，然后安装 Windows （不需要那个破烂 BootCamp 来支持）。  
  
顺便遐想了一下（未验证）：  
  
遐想1. 由于是Retained GPT，保留了MBR，如果安装Mac OS X完成后，编辑一下GPT的分区表标记（如果有的话，目前我不知道在哪），使Mac OS X认为不是GPT了（但在MBR中是正常的分区表）。要重新安装 Mac 的话，把GPT标记改回来，又可以无损地正常升级（当然前面GPT->MBR也无损的，省得现有用户重新初始化GUID）。  
  
遐想2. 由于Mac硬件是支持 EFI 的，Windows 7/8 也是支持 EFI 的，但大多数时候我们都是因为硬件仅支持BIOS或者没有使用GPT导致实际上Windows并非使用EFI来实际工作。如果跳过EFI模拟BIOS层，同时使用GPT的话，是不是Windows就直接通过Mac本身的EFI直接和硬件交互啦？（将完全没有BIOS这个东西存在于Windows运行过程中，这时运行性能是最高效的）。如果是，直接把 Windows 安装在 GPT 分区，然后想办法启动它（如果没有Mac分区，则应该是不需要想办法就能启动？），这样岂不是最完美（抛弃BootCamp这个破玩意）？等待验证中……  
  
顺便说一声：Ubuntu 本尊怎么越做用户体验越差啊。换了Linux Mint LXDE，终于清爽多了。MacBook Pro MC700上不支持BCM4331的WIFI，折腾了一番终于好了：http://www.ubuntubuzz.com/2011/10/macbook-pro-wireless-broadcom-bcm4331.html
