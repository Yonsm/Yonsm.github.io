---
date: 2009-07-30 00:25:10+00:00
layout: post
title: '[转载]OpenMP 编程指南'
thread: 473
categories: 文档
tags: 编程
---

进入多核时代后，必须使用多线程编写程序才能让各个CPU核得到利用。在单核时代，通常使用操作系统提供的API来创建线程，然而，在多核系统中，情况发生了很大的变化， 如果仍然使用操作系统API来创建线程会遇到一些问题。<!-- more -->具体来说，有以下三个问题：  
  
1）CPU核数扩展性问题  
  
多核编程需要考虑程序性能随CPU核数的扩展性，即硬件升级到更多核后，能够不修改程序就让程序性能增长，这要求程序中创建的线程数量需要随CPU核数变化，不能创建固定数量的线程，否则在CPU核数超过线程数量上的机器上运行，将无法完全利用机器性能。虽然通过一定方法可以使用操作系统API创建可变化数量的线程，但是比较麻烦，不如OpenMP方便。  
  
2）方便性问题  
  
在多核编程时，要求计算均摊到各个CPU核上去，所有的程序都需要并行化执行，对计算的负载均衡有很高要求。这就要求在同一个函数内或同一个循环中，可能也需要将计算分摊到各个CPU核上，需要创建多个线程。操作系统API创建线程时，需要线程入口函数，很难满足这个需求，除非将一个函数内的代码手工拆成多个线程入口函数，这将大大增加程序员的工作量。使用OpenMP创建线程则不需要入口函数，非常方便，可以将同一函数内的代码分解成多个线程执行，也可以将一个for循环分解成多个线程执行。  
  
3）可移植性问题  
  
目前各个主流操作系统的线程API互不兼容，缺乏事实上的统一规范，要满足可移植性得自己写一些代码，将各种不同操作系统的api封装成一套统一的接口。OpenMP是标准规范，所有支持它的编译器都是执行同一套标准，不存在可移植性问题。  
  
综上所述，在多核编程中，使用OpenMP就很有必要，下面列出以前发表在我的CSDN博客中的OpenMP文章，供大家参考。  
  
1、OpenMP并行程序设计（一）  
  
介绍OpenMP程序在并行计算时的效率，在双核CPU上效率增加了整整一倍。 [阅读全文](http://blog.csdn.net/drzhouweiming/archive/2006/08/28/1131537.aspx)  
  
2、OpenMP并行程序设计（二）  
  
1、fork/join并行执行模式的概念 2、OpenMP指令和库函数介绍 3、parallel 指令的用法 4、for指令的使用方法 5 sections和section指令的用法。[阅读全文](http://blog.csdn.net/drzhouweiming/archive/2006/09/04/1175848.aspx)  
  
3、OpenMP中的数据处理子句  
  
本文主要介绍了OpenMP中的private、firstprivate、lastprivate、threadprivate、reduction、copyin、copyprivate等数据处理子句的用法。 [阅读全文](http://blog.csdn.net/drzhouweiming/archive/2008/01/10/2033276.aspx)  
  
4、OpenMP中的任务调度  
  
本文主要介绍了OpenMP中任务调度子句schedule的使用方法。[阅读全文](http://blog.csdn.net/drzhouweiming/archive/2007/10/26/1844762.aspx)  
  
5、OpenMP创建线程中的锁及原子操作性能比较  
  
主要比较了原子操作，Windows CriticalSection， OpenMP库带的锁在单任务运行情况下和多任务运行情况下的性能情况，在多核CPU上，多任务的锁竞争花费的时间是单任务时的锁运行花费时间的18倍。锁竞争带来的效率下降完全出乎意料之外，由此也可见多核编程和单核多线程编程是有很大区别的。 [阅读全文](http://blog.csdn.net/drzhouweiming/archive/2007/07/13/1689853.aspx)  
  
6、OpenMP程序设计的两个小技巧  
  
讲述了如何动态设置线程数量以适应硬件和软件的扩展性，如何将嵌套循环并行化的技巧。 [阅读全文](http://blog.csdn.net/drzhouweiming/archive/2008/05/23/2472454.aspxx)  
  
  
  
上面列出的这些OpenMP知识，属于初步的入门知识，如果需要进一步深入掌握OpenMP或者了解其实现原理，则需要看更多的参考文献。下面列出我写的《多核计算与程序设计》一书的第3章OpenMP程序设计中的参考文献，供需要深入掌握的人参考。其中的文献【2】讲解了OpenMP的实现原理。  
  
【1】           Ananth Grama, Anshul Gupta，“并行计算导论”，张武等译，机械工业出版社，2005.01  
  
【2】           Barbara Chapman， “How OpenMP is Compiled ”，http://cobweb.ecn.purdue.edu/ParaMount/iwomp2008/documents/chapman-underthehood  
  
【3】           Bruce McMillin等，“Parallel Algorithm Fundamentals and Analysis”，http://citeseer.ist.psu.edu/mcmillin93parallel.html  
  
【4】           Common Language Infrastructure (CLI) Partitions I to VI http://www.ecma-international.org/publications/files/ECMA-ST/Ecma-335.pdf  
  
【5】           Introduction to OpenMP，A Directive-based API for Parallel Processing on Shared-memory Computers，http://scv.bu.edu/documentation/tutorials/OpenMP/  
  
【6】           Michael J. Quinn, “MPI与OpenMP并行程序设计”，陈文光等译，清华大学出版社，2004.10  
  
【7】           Mitsuhisa Sato, Shigehisa Satoh, Kazuhiro Kusano and Yoshio Tanaka, “Design of OpenMP Compiler for an SMP Cluster”,  
  
http://www.hpcs.is.tsukuba.ac.jp/~msato/pdplab/papers/ewomp99.pdf  
  
【8】           MSDN帮助材料  
  
ms-help://MS.VSCC.v80/MS.MSDN.v80/MS.VisualStudio.v80.chs/dv_vclang/html/652414c5-78ed-4b7f-8283-1a9fe4c5e78d.htm    
  
【9】           Omni OpenMP compiler, http://phase.hpcc.jp/omni/home.html.  
  
【10】       OpenMP2.0规范     http://www.openmp.org/  
  
【11】       OpenMP2.5规范     http://www.openmp.org/  
  
【12】       OpenMP: Simple, portable, scalable SMP Programming, http://www.OpenMP.org.  
  
【13】       Rudolf Eigenmann and Timothy G. mattson. “OpenMP tutorial, part 2: Advanced OpenMP.”， http://www.cise.ufl.edu/research/ParallelPatterns/sc01-omp-tut-advanced.ppt.  
  
【14】       Ruud van der Pas ，“An Introduction Into OpenMP”，http://www.nic.uoregon.edu/iwomp2005/iwomp2005_tutorial_openmp_rvdp.pdf  
  
【15】       Sanjiv Shah, Grant Haab, Paul Petersen, & Joe Throop，“Flexible Control Structures for Parallelism in OpenMP”，http://www.it.lth.se/ewomp99/papers/grant.pdf  
  
【16】       Shameem Akhter等，“多核程序设计技术－通过软件多线程提升性能”，电子工业出版社，2007.03  
  
【17】       Special issue on OpenMP and its applications. Scientific Programming, 11(2),2003.  
  
【18】       Y. Charlie Hu, Honghui Lu, Alan L. Cox, and Willy Zwaenepoel. “OpenMP for networks of SMPs”，In Proceedings of 13th International Parallel Processing Symposium and 10th Symposium on Parallel and Distributed Processing, page 302-310. IEEE Computer Society, 1999.  
  
  
转自：http://software.intel.com/zh-cn/blogs/2009/04/20/openmp-2/  
作者：Zhouweiming 周伟明  

