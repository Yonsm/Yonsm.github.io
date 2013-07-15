---
date: 2011-09-09 17:03:19+00:00
layout: post
title: iMac+SSD 发烧的历程——终于烧成功啦
thread: 547
categories: 文档
tags: Mac 折腾
---

一、缘由   
两三年前就一直听说 SSD 速度多么快，但从来没有实际体验过。上个月入了一个MacBook Air，才发现原来真的是快的不行了。一直都说计算机系统的瓶颈在磁盘，果不其然。顿时萌生了在工作机器上也加SSD的想法，于是恶补各种知识：TRIM、AHCI、优化、分区对齐、测速、疑难杂症等等……。<!-- more -->  

  


（提示，很长，只是流水记录而已，看着难受的话请一目十行：）

**二、升级内存  
**  
主要的工作机器是 iMac 2010 21 寸的版本。原本iMac是4G内存，上个月刚刚升级为8G内存（现在好后悔，应该升级到 12G，现在想升级都白菜价，但已经没有插槽了），这次升级还有点小插曲，升级之后经常死机，送Apple指定的维修站，测试了将近一个星期才发现是内存的问题（我也真傻的，没怀疑到内存），应该是因为原配内存是1066Mhz，而我买的是KINGSTON 1333MHz的频率不匹配的原因（教训啊，想升内存的参考下）。就在感觉内存要浪费的时候，突然想，要么把 MacBook Pro MC700 上原配2x2G的三星内存换来试试，虽然也是1333Mhz的，但三星是苹果原配的，说不定没问题----装上去果然好了……  
**  
  
三****、牛刀小试**  


仔细看评测，发现镁光 M4 的SSD是超强性能且价格比较实惠的，同类型超强性能的OCZ V3，将近1700。镁光M4 128G 网购 1260，不过镁光SSD在大陆似乎没有真正的行货，大公司搞的似乎不正规渠道的代理。最近镁光发布了 M4 的009版本固件，连续读取速度接近500MBps/s，真的非常爽（后面实测确实能达到这个速度，真爽！）。推荐购买128G或者更大的，因为128G的写入速度理论上是64G的两倍。  
  
经了解才知，iMac 2010 21只有两个 SATA 3Gbps 的接口（2010 27和2011的所有iMac都有3个SASTA，2011的所有iMac、MAcBook Pro Air都是 6GBps），所以只能牺牲光驱或者缘由的硬盘。我一直很反感光存储，当然是拿光驱下手。SSD到手后，网购准备好了吸盘、螺丝刀套件、3M双面胶（准备黏在机壳上），拆机，老婆在一旁休息、拍照、帮忙，偶尔欣赏地鼓励两句，那个美啊哈。结果竟然没搞定：光驱的SATA线和硬盘SATA不同，需要重新买过线，接到主板上，难啊…  
  
只好再次网购SSD线和一分二的电源线（后面的参考贴有别人的图）。但实在忍不住了，决定装装在MacBook Pro上试试，替换硬盘，很快搞定了，装好系统，MAC & WIN 各64G，发现MAC下不支持TRIM，Windows下不支持AHCI，分别打补丁解决（Windows 下AHCI补丁不完美，会导致不能休眠，不能访问BootCamp控制面板，不过后面这个是都是小问题，分析一下其他电脑的Bootcamp修改了什么，自己直接修改注册表就OK）。搞定TRIM和AHCI后，秒开秒启的爽感真他妈的好，实测速度，连续读取能达到470~500M，真的是超级强啊（现在主流的3.5机械硬盘，才110M的速度）。  
  
  
**四、重装上阵  
**  


又等了好几天，需要的东西都到了，于是轻车熟路，拆iMac玻璃面板、显示屏，准备装上去。看到别人说最好不要拆主板，而是采用抬高主板的方法装SATA线。我死活也没搞定怎么抬高主板，没有找到光驱线在主板上的SATA口（硬盘的SATA在主板上很容易找到）。想拆下来，折腾的满头大汗，竟然拆了大部分螺丝后还拿不下来。  
  
此时突然想到，原本光驱的线之所以不能用，是因为光驱是SATA标准数据接口+非标准电源接口合并在一起，我**用剪刀把这个合在一起的接口剪开，直接用原来光驱的SATA数据接口；电源接口则使用硬盘的，一分为二。**后来验证了确实可行，于是又好不容易装回主板，竟然有一个螺丝似乎不对，但实在不知道哪里错了，之后将就了（真后悔早没想到用光驱SATA，那样的不但可以少买一个SATA线，还不用拆主板差点搞死了）。看看这个，被我剪开了：  
![](attachment.php?fid=55)  
  
  
接好所有的线，用3M双面胶封好光驱口，再把SSD黏在iMac内壳上，因为光驱SATA的线不够长，所以只好在不是最好的位置随便粘着，贼丑啊，我心里想这辈子最好也不要再拆开这个iMac了。看下图：  
  
![](attachment.php?fid=56)  
  
装回去，用移动硬盘上的 Mac OS X Lion 全新安装，很快搞定（发现Lion竟然不再支持自定义安装，所有语言和打印机驱动程序都装进去了，浪费1.xG，SSD空间啊，10+元/G）。TRIM Enabler、禁用SMS（突发运动传感器），禁用Spolight等优化，测试一下速度，只有 MacBook 上的一半左右，不愧是 3Gbps 和 6Gbps 差别啊----先天不足了----顿时羡慕起购买 iMac 2011 的朋友来……  
  
不过实际使用的体验速度依然非常快，Mac，Mac 启动大多数时候看不到风火轮。程序也是秒开。看别人解释说SSD的速度即使和机械硬盘一样的情况下，也比硬盘的速度感觉更快，因为小文件的随机存取速度比机械硬盘快得多。  
  
  
**五、新的问题（无光驱 Boocamp 安装 Windows）  
  
**正要满怀希望安装 Windows 7 的时候，发现没有光驱竟然无法启动安装 Win7。之前在 Mac Book 上的时候，也没用光驱而是用移动硬盘安装 Win7。在 MacBook Air 上，用移动硬盘也能启动 PE 和 Win7 安装环境(用 rEFIt 引导的)。仔细分析了一下，BootCamp 真是他妈的F**K的，只要BootCamp发现内部的硬盘分区上有 Windows 分区，就无法引导到外部磁盘上的 Windows 分区，rEFIt的Q&A上也这样说了。无奈内部磁盘的一个NTFS分区都是我的主要数据盘，删掉是不可能的，又不想再拆了。于是尝试了各种办法，包括 dd 备份数据分区的PBR，然后写入错误的数据假装"销毁"这个分区（现在想想都后怕，不过还好如预期恢复了分区：），都不能启动受到外部分区。  
  
Mac 下只能修改FAT分区，虽然我也准备了FAT分区，也用dd写入了FAT引导 GRLDR 的功能，但就是无法启动（NO GRLDR都看到了，可能写入的GRUB4DOS到PBR不齐全，又没文档参考，作罢）。最后真的各种办法都尝试了（网上别人说 MacBook 也是一样的情况），大概搞了7~8个小时（0:30~4:30，9:30~14：30，这样折腾，只是为了找到使用外部移动硬盘启动非Mac OSX 的方法）。结果还是没搞定，只好又回到早就知道的最稳打稳扎的办法----虚拟机……  
  
  
**六、最终解决  
**  
以前用VMWare，这次听说Paralles Desktop 7速度很快，虽然不是为了使用虚拟机（虚拟机和TT感觉一样隔靴抓痒），权当测试一下，发现真不好用，远不如VMWare（PD速度可能更好）。新建虚拟机，引入Bootcamp磁盘，用Win7安装盘或PE启动，格式化BootCamp磁盘，BootSect修改启动记录，关闭虚拟机，重新启动电脑，进入BootCamp分区，终于能启动啦…………  
  
提示：网上都说先安装 Windows，再修改MBR，开启AHCI。这样的结果是Windows安装过程中识别的硬盘式IDE的，之后开
启ACHI感觉不妥：我在MacBook Pro上市这样的步骤，感觉Windows启动速度在"Windows徽标动画"时特慢，即使开启了AHCI之后没变快多少（启动速度慢，但进去之后快的）。在 iMac 上我**先修改MBR，然后再安装Win7，安装时候已经开启AHCI，安装后**"Windows徽标动画"基本上只有2~3秒钟不到，Mac+Win 双双秒启……  
  
进入 Windows 测速，只有250M，先天不足，SATA 3G vs SATA 6G，接口啊……不过实际体验速度依然是一流的---- Windows 7 磁盘评分 7.8 (在 MacBook Pro上的时候是7.9，数据控也认可的数字了，哈哈)。  
  


  


**七、参考文章和工具**

**  
**

我发的威锋贴，内涵部分工具：**[http://bbs.weiphone.com/read-htm-tid-2829570.html](http://bbs.weiphone.com/read-htm-tid-2829570.html)**

  


[[HOWTO] Boot Macs with Intel Chipset in AHCI Win7 Vista XP Linux - InsanelyMac Forum](http://www.insanelymac.com/forum/index.php?showtopic=126089&hl=)
[09iMac历险记，加ssd焕发第二春| Mac综合讨论区 - iPhone 4 论坛|iPad 2 论坛|iPod Touch 4 论坛|Mac 论坛|我们的iPhone|期待iPhone5 - WeiPhone威锋网](http://bbs.weiphone.com/read-htm-tid-2409328.html)
[2011 MBP Win7下打开AHCI，完全释放SSD性能。(重新编排中。。。）| Mac综合讨论区 - iPhone 4 论坛|iPad 2 论坛|iPod Touch 4 论坛|Mac 论坛|我们的iPhone|期待iPhone5 - WeiPhone威锋网](http://bbs.weiphone.com/read-htm-tid-2090369.html)
[2011款iMAC 27"一体机添加SSD硬盘作业-多图（813/814型）| Mac综合讨论区 - iPhone 4 论坛|iPad 2 论坛|iPod Touch 4 论坛|Mac 论坛|我们的iPhone|期待iPhone5 - WeiPhone威锋网](http://bbs.weiphone.com/read-htm-tid-2655854.html)
[2011新款27寸iMac低配自行更换SSD，无菊花秒开Lion，从开机到进系统18秒| Mac综合讨论区 - iPhone 4 论坛|iPad 2 论坛|iPod Touch 4 论坛|Mac 论坛|我们的iPhone|期待iPhone5 - WeiPhone威锋网](http://bbs.weiphone.com/read-htm-tid-2611347.html)
[8,1的imac更换ssd硬盘作业成功，发现屏幕内部进灰求解| Mac综合讨论区 - iPhone 4 论坛|iPad 2 论坛|iPod Touch 4 论坛|Mac 论坛|我们的iPhone|期待iPhone5 - WeiPhone威锋网](http://bbs.weiphone.com/read-htm-tid-1467667.html)
[Guide Enabling AHCI for Windows on MBP 2011 now possible](http://www.ocztechnologyforum.com/forum/showthread.php?87950-Enabling-AHCI-for-Windows-on-MBP-2011-now-possible)
[iMac 2011 mc814改装SSD 完成，改装有难度下手需谨慎 - 【苹果网】 - MacX.cn - 苹果新闻与用户互动](http://www.macx.cn/a/a89i1930905.htm)
[iMac 27 加装SSD成功！受惠于威锋，故此来报道！| Mac综合讨论区 - iPhone 4 论坛|iPad 2 论坛|iPod Touch 4 论坛|Mac 论坛|我们的iPhone|期待iPhone5 - WeiPhone威锋网](http://bbs.weiphone.com/read-htm-tid-1522225.html)
[Intel+AMD----苹果2011款iMac全面大拆解（小心杀猫哦） - 便携电脑 - PC绝对领域---中国最专业、最真实、无水区的PC爱好者论坛 - Powered by Discuz!](http://bbs.pceva.com.cn/viewthread.php?tid=18789&highlight=iMac)
[Optimizing Mac OS X for SSD drives | Fredrik Poller](http://poller.se/2010/08/optimizing-mac-os-x-for-ssd-drives/)
[受不了imac噪音了，今儿终于换了ssd，图片流程| Mac综合讨论区 - iPhone 4 论坛|iPad 2 论坛|iPod Touch 4 论坛|Mac 论坛|我们的iPhone|期待iPhone5 - WeiPhone威锋网](http://bbs.weiphone.com/read-htm-tid-1461092.html)
[完成SSD更换、固件升级、分区、4K对齐、TRIM、AHCI一系列工作, - Mac综合讨论区](http://www.91nes.cn/thread-970873-1-1.html)
[在苹果的 Mac OS X 下使用 SSD固态硬盘，必要的相关系统优化设置手册 - 硬件/外设等综合讨论区 - U2Game.Net社区论坛](http://www.u2game.net/bbs/thread-29808-1-1.html)
  

  
另外一篇Win7下SSD优化：http://memory.it168.com/a2011/0818/1234/000001234279.shtml
还有一个优化贴，中文的：http://www.u2game.net/bbs/thread-29808-1-1.html
RAMDisk对于SSD我感觉也是及其有效的手段。

  


  


# iMac 2010 SSD vs. MacBook Pro 2011 HDD 启动速度对比（老婆随手录制的）：

  
  
  
  
  


  


**时间就是生命，SSD就是时间！**

**  
**
