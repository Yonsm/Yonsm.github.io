---
date: 2012-05-08 18:29:17+00:00
layout: post
title: 自动转发特定网站到路由器GoAgent，实现客户端零配置
thread: 678
categories: 文档
tags: 折腾 路由器
---

关于自动指定出口有完美方案了！在路由器上跑GoAgent，路由器的防火墙规则能自动把U2B的HTTP请求往Go~Agent上劫持转发，这样相当于是和“指定出口”功能差不多功能的智能路由了（不过不是VPN路由，是HTTP代理而已）

以 YouTube 为例：<!-- more -->

1. 先DNSMasQ防止域名解析的IP变换或被污染：

address=/c.youtube.com/**173.194.5.118** 》》这个IP随便写一个永远不会访问的IP（可以用justping来解析正确的IP）
address=/youtube.com/ytimg.com/203.208.46.178 》》这个用Host访问￥ouTube，不需要代理就能访问（这个不属于本文的内容，不明白请忽略）

2. 然后添加防火墙脚本：
iptables -t nat -I PREROUTING  -i br0 -p tcp -d **173.194.5.118** --dport 80 -j REDIRECT --to-ports 8087

3. 这样配置后，客户端不用做任何配置，访问YouTube的时候，网页内容自动用过host就能直接访问，视频内容被解析到**173.194.5.118**这个IP地址，然后这个地址的指定端口80被iptables自动劫持到路由器的8087端口，即Go4gent代理。

已测试PC上浏览器和Android上浏览器均可不用做任何设置即可访问并播放￥ouTube。哈哈
Androide上￥ouTube客户端似乎不行，可能走的不是80端口HTTP方式。想来iphone客户端和网页版都不行，可能都是没走HTTP方式而是使用专用控件的方式走其他渠道，有待继续分析（只要是HTTP方式，就可以搞定，有可能是其它服务器）。

4. 类似的方法可以用来自动转发其它的网站，只要在Dnsmasq上增加域名即可，太完美了,如：
address=/c.youtube.com/bbc.co.uk/**111.111.111.111**

（如果还要访问改域名的其它网站，请不要添加DNSMasq的偷懒的方法，而是增加一个防火墙脚本：ptables -t nat -I PREROUTING  -i br0 -p tcp -d **111.111.111.111** --dport 80 -j REDIRECT --to-ports 8087，IP地址换成正确的IP地址，如果IP被污染，则自己用DNSMasq或者8.8.8.8解析一下）

我这个“指定出口”做的精妙吧，真正实现了客户端零配置，哈哈……

在路由器上安装GoAgent的方法请看：[在 3.5MB 空闲空间的路由器上部署 Python + GoAgent）](/2012/04/09/3-5mb-router-deployed-on-ultra-small-free-space-pythongoagent-the-case-of-tomato-dualwan-wr500v/)

论坛帖子请看：[http://bbs.dualwan.cn/viewthread.php?tid=278761](http://bbs.dualwan.cn/viewthread.php?tid=278761)

上文中所称路由器为 Tomato DualWAN，但对于有iptables命令的 Linux类路由器包括DDWRT/OpenWRT等均有参考意义。

 

**总结一下，终于找到一个比较好的方案了**

**按优先级如下：**

**1. 能直接访问的网站——如国内网站；**
** 2. 能通过修改host直接访问的，如youtube、facebook、google（twitter之前行，现在似乎不行了，转到下面这种方法）；**
** 3. 不能直接访问的HTTP网站，如bbc中文网，通过DNSMasQ批量劫持转到GoAgent。**
** 4. 最难的是HTTPS网站，这个不能劫持，只能手动设置代理来访问，如访问很慢的amazon.com登录（这里我们假设根本不能访问吧），这种网站HTTPS较少，所需证书不多，自己整理一下这些证书放到路由器的/opt/etc/goagent/certs下，HTTPS的问题也解决了。**
