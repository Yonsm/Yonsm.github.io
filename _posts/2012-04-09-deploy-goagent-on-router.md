---
date: 2012-04-09 12:24:25+00:00
layout: post
title: 在 3.5MB 空闲空间的路由器上部署 Python + GoAgent
thread: 645
categories: 文档
tags: 折腾 路由器
---

在 3.5MB 超小空闲空间的路由器上部署 Python + GoAgent（以Tomato DualWAN WR500V 为例）
（以Tomato DualWAN WR500V 为例，WR500V 用户不想看废话的话请直接跳到“四、使用”开始看即可）

一、来由


    GoAgent 是利用 Google App Engine 的网络代理，速度超快，U2B之类的播放及其流畅，秒杀大部分VPN。介绍就不详说了，具体自己 Google 吧……




   GoAgent 客户端（准确说是中继）是用 Python 实现的，可以在 Mac OS X、Windows、Android、iOS、WebOS 上运行，然后再设置浏览器的代理为本地 GoAgent 端口。但是要让每个访问点上部署 GoAgent 是非常麻烦的事情（如 iOS、Android 等）；即时是 Windows 和 Mac OS X，每次都使用都要打开一个多余的尾巴，想想就麻烦。有没有更好的解决方案呢？




   当然有！最合适的部署的角色服务器就是在路由器上。搜索一下 GoAgent OpenWRT 或者 GoAgent Tomato，有很多教程可以参考。基本的步骤是安装 ipkg/opkg，安装 python、openssl，然后上传 GoAgent 的文件，然后少量设置就行了。


<!-- more -->
二、存储空间


   我在使用的路由器 Tomato DualWAN 的 WR500V，只有 8M Flash，查看了一下空间使用，才用了3.xM，还有 4M+ 的空间那里去了呢？赶紧问了了一下路由器的生产商，答复了是在路由器 Web 控制台->系统管理->JFSS设置，启用并格式化，就能获得 3.5M 左右的可用空间——敢情说以前这么大的空间都闲着，真是浪费啊老大……




   空间有了，准备开干。然后立马给了个下马威，ipkg 安装后就花费了将近 2M 空间，安装 python 的时候发现 *_mipsel.ipk 有 14 M+，包括其它的依赖，解压缩后竟然有 70M+（共 6498 个文件）。这对于那些有 USB 口的路由器来说，随手插上一个 U 盘或移动硬盘什么的，毫无压力，但对于我这种只有 8M Flash 的路由器来说，压力山大啊……




   对于万能的终极动手折腾控来说，办法总是比困难多。于是想办法尝试，最终真的搞定了，在 3.5M 闲置空间内安装上了 GoAgent 1.8.0，让所有的电脑啊、手机啊、高清播放机啊神马的都可以轻松享受 GoAgent 带来的快感（部署 PAC 等会更方便）。本文典型地适用于有 8M Flash 且其中有 3.5M+ 空间剩余的可以刷 OpenWRT、Tomato、DD-WRT 的路由器（如果 8M Flash 刷固件后，空间不足 3.5M，可以寻找或者自己 DIY 精简版固件），特别是 Tomato DualWAN WR500V 用户可以照搬步骤和超级 Python 包。


三、折腾细节


1. Tomato DualWAN WR500V 支持 CIFS 客户端，即可以在路由器上映射 Samba （简单理解为类似 Windows 网络共享）的路径，如此一来，我们可以临时性地获得一个超大的“外援”空间。映射后，telnet 上去发现 /cifs1 已经可以用了。




2. 执行 mount -o bind /cifs1 /opt 让 /opt 绑定到远端可用空间上。




3. 安装 ipkg、然后 ipkg install python openssl 等，然后上传 GoAgent 然后测试运行无误（此步骤网上有很多教程，如参考：http://bbs.dualwan.cn/viewthread.php?tid=229261）




4. 上面步骤完成后发现总共耗费了 70M+ 空间（6498 个文件，似乎），好了，大刀阔斧地删减文件，做到最终减少到了 7M 多一点（光这个步骤就几乎花费了我超过 4 个小时的时间，Hacker、Cracker、Geeker 的成功之道：耐心+运气+经验）。




5. 前文所述格式化装载 JFFS，df -h 查看只有 3.5M，网上查了一下得知 JFFS 是支持压缩的，cp -a /cifs1 /jffs，一阵忐忑后，发现全部拷贝进去了（正好压缩了 50% 左右），/jffs 上只剩下 150K 左右空间空闲了，真险啊……




6. 执行 mount -o bind /jffs /opt 重新绑定 /opt 到内部的 JFFS 空间上，再次执行 GoAgent，成功，太棒了。




7. 剩下的收尾工作，卸磨杀驴，把 CIFS 取消掉（毕竟外援是靠不住的，并非 7×24 小时开机）；设置自动运行等，打包分享，搞定手工。


四、使用


   如果你是 WR500V 用户（或者其它 mipsel 架构的 CPU 的路由器或者高清播放机均可），可以直接用我导出的专用于 GoAgent 的 Python 包。特点：只有 JFFS 压缩后仅占用 3.5M 空间；TGZ 打包，部署后直接可用。缺点：删除了GoAgent cert 下的所有证书（实在没空间来保留这 1M 多的证书了），不知道访问那些 HTTPS 网站是否会有问题，尚未验证（似乎没遇到问题）。下面是 WR500V 用户使用的步骤：




1. 在 WR500V WEB 控制台->系统管理->JFFS设置，启用，格式化，得到 /jffs 空间。“挂载后执行 ”处输入“mount -o bind /jffs /opt”，以便 /opt 指向 JFFS 空间。




2. 下载附件，上传文件 opt.tgz 到路由器上：




1）在 系统管理->访问设置 把 SSH 和 Telnet 访问打开（如果没打开的话）。




2）用 WinSCP 等软件以 SCP 协议登陆路由，把 opt.tgz 整个压缩包传到 /tmp 目录下




3）用 Putty 或 Telnet 登录到路由器，输入：




cd /opt
tar -zxvf /tmp/opt.tgz。




3. 解压缩完成后，执行一下 /opt/goagent.autorun 看看有没有成功的信息，如果有即成功了。




4. 修改 /opt/etc/goagent/proxy.ini 中的 jeanzvpn 为你的 Google App Engine 的 App ID（为了测试你就用我的临时用一下吧，但完成后请自己申请和部署 GoAgent，切记，否则有 1G 流量限制，人多大家用的话一下就用完了）。




5. 重启路由器，万事 OK（重启后自动挂载 JFFS，绑定到 /opt，绑定后自动执行 /jffs/goagent.autorun，这个是从 Tomato USB 官网找到的自动运行的方法）。




6. 要使用 GoAgent 翻墙，请选择下面的任意一种方式：




1). 设置浏览器代理为路由器地址，端口 8087;




2).设置浏览器或或者 iPhone 自动代理脚本为 http://192.168.1.1:8087/goagent.pac（默认已经在 8087 端口开启 GoAgent PAC 服务，如果路由器的 IP 地址不是 192.168.1.1，请先修改 goagent.pac 的 127.0.0.1 为 路由器的地址）；




3). Chrome 用户还可以用 Switchy Sharp 插件。


五、后话


   实际使用后用 top 命令查看 CPU 和内存占用：单个客户端普通网页浏览的话，CPU基本上 5% 以下，初始响应速度似乎不如 Windows 和 Mac OS X 的 GoAgent 快；看 YouTube 视频的话，CPU 大概会在 5~10%之间，非常流畅。没有启用 swap 空间，内存占用和稳定性完全无问题。


By Yonsm
2012.04.16
感谢所有工具和参考文章作者

 

下载：

[https://hdweb.googlecode.com/svn/goagent.tgz](https://hdweb.googlecode.com/svn/goagent.tgz) (2.0.2版本，**尝试使用后请立即替换AppID**，未确认U2B是否可自动)

[http://115.com/file/c2c4nlla#GoAgent-1.8.11-On-opt.tar](http://115.com/file/c2c4nlla#GoAgent-1.8.11-On-opt.tar) （1.8.11版本，自己升级的话直接替换GA的文件即可）

[http://115.com/file/e7n69oyv#](http://115.com/file/e7n69oyv#)（1.8.2 版本，已去除 logging 功能，已复用同一个线程/端口来做代理和PAC服务 ）

[From SkyDrive](https://skydrive.live.com/redir.aspx?cid=d6cd6f1068e2bffd&resid=D6CD6F1068E2BFFD!311&parid=D6CD6F1068E2BFFD!116&authkey=!AP2H5RyjU8UdIxg) （1.8.0 版）

DualWan BBS 相关讨论：[http://bbs.dualwan.cn/viewthread.php?tid=266521](http://bbs.dualwan.cn/viewthread.php?tid=266521)

更进一步的应用，自动转发指定网站到GA：[http://bbs.dualwan.cn/viewthread.php?tid=278761](http://bbs.dualwan.cn/viewthread.php?tid=278761)


> iptables -t nat -I PREROUTING -i br0 -p tcp -d 12.34.56.78 --dport 80 -j REDIRECT --to-ports 8087
iptables -I INPUT -p tcp --dport 8087 -j ACCEPT

 

DNSMasQ 配置：[http://115.com/file/dpjlsv6j#dnsmasq.conf](http://115.com/file/dpjlsv6j#dnsmasq.conf)
