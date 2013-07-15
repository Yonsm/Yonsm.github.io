---
date: 2009-07-16 21:24:02+00:00
layout: post
title: 终于搞定了 BlackBerry 9530 EVDO 上网（手机+电脑Modem）
thread: 472
categories: 文档
tags: 折腾
---

朋友弄了张430多块钱的电信CDMA上网账号，想在黑莓 9530 中上网，并用作电脑的Modem上网，几经折腾，终于搞定了。<!-- more -->  
  
在此记录一下，有需要的人可以尝试。  
  
  
**1. 获取A-KEY、IMSI、ESN**  
  
A-KEY：16位的HEX数字（如E886************），用于用户鉴权，只能从电信内部人士得到（网上都这样说，暂且就这样听吧）。  
  
ESN： 是16位的HEX数字（如80******），这个可以从UIM卡中读取（用CDMA Workshop 3.41，官方下载Dem版本）。或者……把在9530中拨打 ##000000 进入查看手机的ESN，给电信内部人士，叫他重新绑定你的手机ESN到IMSI（和A-KEY？）（我就是这种方法，因为我写入UIM卡的ESN到手机失败了——注意，初始情况下，手机的ESN不是UIM卡的ESN）。  
  
IMSI： 是15位的数字（如4600309********），手机号码的内部形式，这个应该可以从UIM卡中读取（不过我是另寻途径搞得）。同时IMSI也是EVDO的上网AN/AAA账号，其实可以打10000咨询服务人员。  
  
EVDO上网密码：打10000咨询，服务小姐可能啥也不知道，就问15位的账号（就是IMSI）和16位的密码。  
  
  
**2. 写入 A-KEY、IMSI、ESN 到 9530**  
  
  
IMSI：9530中拨打##000000，进入工程模式，在IMSI_S一栏输入 IMSI然后Save即可（需重启，请耐心等待）。  
  
A-KEY：上面的方法中，貌似也能写入A-KEY，但好像不会成功的。能成功的方法，见这里：http://bbs.maxpda.com/thread-196588-1-4.html。  
  
用到的工具 CDMA Workshop 3.4.1 Demo（注意：网上的其他版本的破解版有病毒）:  
http://www.cdma-ware.com/workshop.html  
  
  
ESN：见这里：http://honeyhan.cn/200906/18_1023.html，但是，我尝试了无数次，失败了！只好另寻途径，把自己手机的ESN给电信“内部人士”，叫他帮忙用收集的ESN绑定一个新的IMSI（和A-KEY），所以我就没改变手机的ESN了。  
  
到此，应该能打电话了。  
  
  
**3. 导入ServiceBook，支持手机上网**  
  
  
具体操作：http://bbs.pgcw.com.cn/dispbbs.asp?boardid=67&id;=30495&page;=0&move;=next  
  
Service Book 我用的是这里的：http://www.52blackberry.com/viewthread.php?tid=252900  
  
WinLoader：http://chinawrc.blog.enorth.com.cn/article/242417.shtml  
  
这时候，用手机的浏览器能上网了，不过是 CDMA1X 的，速度比较慢。  
我这里，依然有个问题：自带的浏览器上网，如果久了，会突然不能上网，Google 地图等其他软件均不能上网，拔电池重启又行了。不知何故（刷151OS之前手机 中国移动 EDGE 上网一直都很稳定的，不过Service Book 不一样）。不过下文的用作电脑的调制解调器方式，很稳定，很久都OK。  
  
  
**4. 导入PRL，支持EVDO**  
  
我用到的 PRL 文件从这里下载：http://www.52blackberry.com/viewthread.php?tid=252900  
  
操作方法：http://www.52blackberry.com/viewthread.php?tid=214199  
  
补充说明：上面的操作方法语焉不详，我补充一下，必须用QPST 2.7.264 或更新的版本，以下QPST操作在更改数据之前，请首先 Read From Phone 一下。  
1) QPST Configuration 好端口后，在 Service Programming 中，ROAM页面，导入PRL文件，自动重启;  
 2) PPP Config 页面，点击 Um，User Password 都填入“card”，并勾上Req PW enc，点“Write to Phone”（不确定这步骤可能不需要，就当有多不坏菜吧）  
3) 在PPP Config 页面，点击AN，User 输入你的IMSI，密码输入EVDO的密码（前面说过的，拨打10000号可以问到，分别是15位和16为），并勾上Req PW enc，点“Write to Phone”（这部关键）。  
4) 其他操作，看这里吧 http://www.52blackberry.com/viewthread.php?tid=214199。  
5) Home SID 从这里查：http://bbs.pcpop.com/090114/4816107.html  
  
  
用到的工具 QPST 2.7.264 （注意：必须是这个版本或者更高版本，否则不能写入ROAM PRL和PPP的AN/AAA）：  
http://www.shuaji.net/down/soft/dopod/2009/2-12/down09212973261.shtml  
  
  
这时候，手机亦应能EVDO上网了，确认方法（手机启动后，一直显示 1xev，上网后也不改变，如果又变成1x，说明账号密码不对）  
  
  
**5. 设置拨号连接，支持用作电脑 Modem**  
  
1. 把手机接上电脑中，控制面板调制解调器中，选择黑莓“标准调制解调器”，属性，调制解调器初始命令（作用是启用手机的调制解调器模式）：  
AT+CGDCONT=1,"ip","ctnet"  
  
2) 新建拨号连接，设置如下（杭州的设置，其他地方应该也是这样？）：  
  
号码：#777  
用户名：ctnet@mycdma.cn  
密码：vnet.mobi  
  
然后拨号，可以看到手机顶部出现“调制解调器模式启用”的文字，小写的 1xev 也变成大写 1XEV 了。到电信网站上下载点东西看看，速度超级快（300KB/s），不过到其他网站上则可能慢一些（限速啦？）  
  
  
  
**6. 评论**  
  
电脑上下载中国电信的东西，速度竟然能达到300KB/s，下载Yonsm.NET的东西稳定保持在150KB/s以上，电信的3G才是真正的3G！TD这种垃圾，继续爱国去吧！  
  

