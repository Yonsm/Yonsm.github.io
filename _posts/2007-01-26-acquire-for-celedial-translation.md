---
date: 2007-01-26 08:52:09+00:00
layout: post
title: 原来老外也有人在做“英化”，CeleDial Translation?
thread: 289
categories: 日志
---

今天搜索Himalaya，一不小心看到一个帖子：[http://buzzdev.net/index.php?option=com_phorum&Itemid;=125&phorum;_query=read,26,28684](http://buzzdev.net/index.php?option=com_phorum&Itemid=125&phorum_query=read,26,28684)，仔细一看竟然在讨论“英化”CeleDial。只不过跟中文用户的“汉化”相比，老外似乎作的也太累、太神了——不会中文，竟然也能从中文翻译成英文，下面是部分文字（大致意思是不懂中文，查找资源Unicode，根据 Unicode 算出中文字符，在到翻译网站把中文翻译成英文……我看了一下很多词句翻译甚至比我翻译的还准确，汗！忒神了吧）：  
  


  
_TofClock, it is a really nice work. Where have you learn Chinese?    
Regards,   
Oki_  
  
i'ne never learn chinese ...   
  
just , i hex edit all resources and copy the unicode like this :   
  
hex resource is ffff020073518e4e   
  
ffff0200 is anything but 73518e4e is unicode 5173 and 4e8e   
  
convert in decimal you have 关 and 于   
  
go to [www.chinese-tools.com] to get chines caracters from this unicode   
and go to [www2.worldlingo.com] to get english translation ...   
  
but this literal translation and the real work is to retrieve the real words ...   


  
  
  
下面竟然有人给了这么高的评价，美滋滋地说。其实CeleDial最棒的地方在于整合的精妙构思和强大方便的中文搜索能力——可惜他们都不上中文搜索啦……  
  


  
In my opinion, celedial is way better then anything I know, its light, its simple and fast... but this dialparser hv 2 limitation, first, only 3 digit, and second I dont undestand chinnese, so I'll wait for ur wwe translation tof... this celedial is so much like the Crossbow smartdial style... simple... 

  
  
  
过段时间或许会出正式版本了，支持会有些新的功能，也会提供英文版本，可能还有法文或其它。SP版本暂时没那么快。据说 WM6 内置了智能拨号，我一看原来根本不是 MS t提供的，很可能是O2 的，但据用户反映，差不多是鸡肋——与CeleDial的强大与方便相比较而言。  
  
Here you English guys can download CeleDial English Beta version:  
  
[/assets/CeleDialENU.CAB](/assets/CeleDialENU.CAB)  
  
It can support PPC2003/WM5.0 in most of PPC phone device.  And, I'll release the formal version in the future. If you want to translate it into you own language, just [contact me](mailto:yonsm@163.com), please.  
  
The following message may be need for customize your own mapping table (e.g. French Name in Contacts).  
  


  
....  
So you need a extrenal mapping table for your French Name. Just do that to enable External Mapping Table:  
  
1. Create a Unicode text file named CeleDial.txt.  
2. Fill the French Characters to Alpha Characters mapping line by line:   
a àâä  
e éèêê  
and so on.  
3. Put this text file into CeleDial's Folder (e.g. \Program Files\CeleDial\CeleDial.txt)  
4. Reboot your device to enable the external mapping table.  
  
5. Send your mapping table to me, if possible:)  
....  

