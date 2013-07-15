---
date: 2012-01-16 05:31:42+00:00
layout: post
title: '[转载]iPhone 開發教學 - 關於 Crash Report 和 dSYM 的使用'
thread: 551
categories: 文档
tags: iOS 编程
---

前幾天玩遊戲時，看到開發者請大家把 Crash Log / Crash Report / Bug Report 寄回給他，如此一來就可以偵錯，滿好奇的便也隨意在網路上找找該怎樣使用，在此便稍作筆記，並且寫一個簡單會 crash 的程式(很少人會這樣做吧 XD)。  
  
所謂的 Crash Report 是在實體機器上，執行程式時發生 crash 時，此時 iOS 會幫忙將程式出錯的相關資訊存起來，這時候用 Xcode 的 Organizer - Devices 時，可以去點選設備，並且可以查看有哪些 report 在上頭，這時候就可以稍作觀看，但是上頭記錄的資訊是有稍微類似做過保護的，只會看到類似(這是網路上收集的資訊，但我嘗試做出的 log 好像已經轉好了？)：  
<!-- more -->  
Thread 0 Crashed:  
0   libSystem.B.dylib               0x35de3ad0 0x######## + ##  
1   libSystem.B.dylib               0x35de3abe 0x######## + ##  
2   libSystem.B.dylib               0x35de3ab2 0x######## + ##  
3   libSystem.B.dylib               0x35dfad5e 0x######## + ##  
4   libSystem.B.dylib               0x35de967e 0x######## + ##  
5   libSystem.B.dylib               0x35de974c 0x######## + ##  
6   libSystem.B.dylib               0x35d5c8e0 0x######## + ##  
7   libSystem.B.dylib               0x35d5c798 0x######## + ##  
8   CoreFoundation                  0x3750022c 0x######## + ##  
9   CoreFoundation                  0x374fc206 0x######## + ##  
10  CoreFoundation                  0x37504564 0x######## + ##  
11  CoreFoundation                  0x37504406 0x######## + ##  
12  Foundation                      0x351530f0 0x######## + ##  
13  CrashTesting                    0x00002712 0x######## + ##  
14  UIKit                           0x35924fd0 0x######## + ##  
15  UIKit                           0x3591ea70 0x######## + ##  
16  UIKit                           0x358d82dc 0x######## + ##  
17  UIKit                           0x358d7b14 0x######## + ##  
18  UIKit                           0x358d73ac 0x######## + ##  
19  GraphicsServices                0x33e77c80 0x######## + ##  
20  CoreFoundation                  0x3752f5c4 0x######## + ##  
21  CoreFoundation                  0x3752f582 0x######## + ##  
22  CoreFoundation                  0x3752182e 0x######## + ##  
23  CoreFoundation                  0x37521504 0x######## + ##  
24  CoreFoundation                  0x37521412 0x######## + ##  
25  UIKit                           0x3591d54c 0x######## + ##  
26  UIKit                           0x3591a550 0x######## + ##  
27  CrashTesting                    0x0000266e 0x######## + ##  
28  CrashTesting                    0x00002620 0x######## + ##  
這時候需要使用原先編譯 app 時，在同一目錄中會產生對應的 dSYM 檔案，搭配 dwarfdump 使用才可以查詢到真正的片段程式(例如想看 line 13 的意思)：  
  
$ dwarfdump --lookup 0x00002712 -arch armv6 CrashTesting.app.dSYM/  
----------------------------------------------------------------------  
File: CrashTesting.app.dSYM/Contents/Resources/DWARF/CrashTesting (armv6)  
----------------------------------------------------------------------  
Looking up address: 0x0000000000002712 in .debug_info... found!  
  
0x00000132: Compile Unit: length = 0x000049b0  version = 0x0002  abbr_offset = 0x00000000  addr_size = 0x04  (next CU at 0x00004ae6)  
  
0x0000013d: TAG_compile_unit [1] *  
            AT_producer( "4.2.1 (Based on Apple Inc. build 5658) (LLVM build 2373.6)" )  
            AT_language( DW_LANG_ObjC )  
            AT_name( "CrashTestingAppDelegate.m" )  
            AT_entry_pc( 0x000026b4 )  
            AT_stmt_list( 0x0000006b )  
            AT_comp_dir( "/Volumes/Data/iPhoneDev/trunk/CrashTesting/CrashTesting" )  
            AT_APPLE_major_runtime_vers( 0x02 )  
  
0x00000166:     TAG_subprogram [16] *  
                AT_sibling( {0x000001d2} )  
                AT_name( "-[CrashTestingAppDelegate application:didFinishLaunchingWithOptions:]" )  
                AT_decl_file( "/Volumes/Data/iPhoneDev/trunk/CrashTesting/CrashTesting/CrashTestingAppDelegate.m" )  
                AT_decl_line( 17 )  

;               AT_prototyped( 0x01 )  
                AT_type( {0x0000015b} ( BOOL ) )  
                AT_APPLE_isa( 0x01 )  
                AT_low_pc( 0x000026b4 )  
                AT_high_pc( 0x00002780 )  
                AT_frame_base( r7 )  
  
0x000001b9:         TAG_lexical_block [5] *  
                    AT_low_pc( 0x000026c4 )  
                    AT_high_pc( 0x00002780 )  
Line table file: 'CrashTestingAppDelegate.m' line 20, column 0 with start address 0x000000000000270e  
  
Looking up address: 0x0000000000002712 in .debug_frame... found!  
  
0x00000020: FDE  
       length: 0x0000000c  
  CIE_pointer: 0x00000000  
   start_addr: 0x000026b4 -[CrashTestingAppDelegate application:didFinishLaunchingWithOptions:]  
   range_size: 0x000000cc (end_addr = 0x00002780)  
 Instructions: 0x000026b4: CFA=4294967295+4294967295  
  
因此就可以查看到 line 13 是指 CrashTestingAppDelegate.m' line 20，所以就可以去那邊追查看看。  
  
以上的例子僅需建立一個 Project (此例名為 CrashTesting)，然後在 - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions 裡頭寫一段會 crash 的程式碼(此例為 double free)：  
  
   NSString *justCrash = [[NSString alloc] initWithFormat:@"CrashTesting"];  
   [justCrash release];  
   [justCrash release];  
  
如此一來，在實機執行完並當機後，可以接上 Xcode 去 Organizer - Devices 查看：  
  
（图片省略，其实再Archive后中就能看到）  
  
而 dSYM 檔案，則是在 Xcode 編譯的地方：  
  
（图片省略，其实再Archive后中就能看到）  
  
  
點選後，就可以看到並且可以複製到習慣的工作目錄囉  
  
转自：http://changyy.pixnet.net/blog/post/29468695-iphone-%E9%96%8B%E7%99%BC%E6%95%99%E5%AD%B8---%E9%97%9C%E6%96%BC-crash-report-%E5%92%8C-dsym-%E7%9A%84%E4%BD%BF%E7%94%A8  
点评：万恶的墙，翻爬才能看到
