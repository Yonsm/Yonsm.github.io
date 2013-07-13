---
author: Yonsm
comments: true
date: 2005-10-16 21:30:14+00:00
layout: post
slug: anycon-to-dial-multiple-adsl-connections-to-significantly-improve-network-speed
title: AnyCon - 拨通多个 ADSL 连接，大幅度提升网络速度
wordpress_id: 17
categories:
- 文档
---

我这里指的是杭州的 ADSL，特点是，不支持绑定多重连接到同一个 IP 地址。但是可以同一个用户名密码拨通多个连接。

  


大致步骤：

<!-- more -->  


  1. 安装 RASPPPoE，设置 PPPoE 协议属性，启用多个"线数（WAN 端点）"（虚拟设备），如2-4个。重新启动系统。
  2. 建立多个 PPPoE 拨号连接，每个都能拨成功，此时已获取多个IP地址。但是，这并没有任何用处，因为绝大部分软件作为客户端上网时，都不会指定绑定某个 IP 地址的，系统总是选择最后拨通的那个连接来访问。气死！
  3. 为了解决问题，就要使每个连接之前，自动轮番绑定所有可能的 IP。
  4. 经过测试，发现简单绑定根本没用，千找万找，找不到原因。后来问朋友 Yicho，测试路由表的问题。原来，没拨通一个连接，系统（？）自动在 Route Table 增加一个入口，METRIC = 1 (跃点数，不太懂)，且把前面的连接的路由入口的 METRIC 自动往前递增。导致这些连接无法使用！
  5. 为了解决上面的问题，必须在拨号成功之后修改路由表，代码如下： 
    
    // 使用 IP Helper API 添加（如果已存在则为修改）拨号连接路由<br></br> VOID SetRoute()<br></br> {<br></br>     UINT i, j;<br></br>     DWORD dwSize = 0;<br></br>     GetIpAddrTable(NULL, &dwSize, TRUE);<br></br>     PMIB_IPADDRTABLE p = (PMIB_IPADDRTABLE) new BYTE[dwSize];<br></br>     if (p)<br></br>     {<br></br>         if (GetIpAddrTable(p, &dwSize, TRUE) == NO_ERROR)<br></br>         {<br></br>             MIB_IPFORWARDROW ifEntry = { 0 };<br></br>             ifEntry.<font color="#e00000">dwForwardMetric1 = 1</font>;<br></br>             ifEntry.dwForwardProto = 3;<br></br>             ifEntry.dwForwardType = 3;<br></br>             ifEntry.dwForwardAge = -1;<br></br>             DWORD dwAddr[MAX_RAS];<br></br>             UINT uNumAddr = GetRasAddress(dwAddr);<br></br>             for (i = 0; i < p->dwNumEntries; i++)<br></br>             {<br></br>                 for (j = 0; j < uNumAddr; j++)<br></br>                 {<br></br>                     if (dwAddr[j] == p->table<i>.dwAddr)<br></br>                     {<br></br>                         ifEntry.dwForwardIfIndex = p->table<i>.dwIndex;<br></br>                         ifEntry.dwForwardNextHop = p->table<i>.dwAddr;<br></br> <br></br>                         CreateIpForwardEntry(&ifEntry);<br></br>                         break;<br></br>                     }<br></br>                 }<br></br>             }<br></br>         }<br></br>         delete[] p;<br></br>     }<br></br> }<br></br> 

  6. 通过以下几种方法，强制客户段轮番绑定所有可用的 IP： 
    * HOOK 每个进程的 connect/WSAConnect 函数，在它之前 bind。
    * 通过 WSP SPI 提供 WSPConnect 函数，过滤 Connect 调用，在它之前 bind。
    * 替换 WS2_32.dll 截获 WSAConnect/connect 调用，在它之前 bind。
    * 其它方法，已 Cancel。
  7. 每种方法各有利弊，最终还是 WSP SPI 的方法最最好。但是这存在一个问题，对于已经绑定的连接，理论上我们不应该绑定它，否则可能导致此连接无法使用（？是吗？我猜测的，因为 CuteFTP 不能接收控制数据）。
  8. 我写了个 WSP TCP 过滤器，过滤 Connect 调用。对 UDP 连接提速效果。还好所有的下载几乎都是 TCP 的。FTP 除外！
  9. ……细节好多，说也说不完。 

已比较完美，用 WSP SPI 实现。暂无心情写具体过程和方法。

  


日后再详细叙述。抱歉！

  


下载 [AnyCon 1.0.52.120](up/AnyCon%201.0.52.120.rar) (使用方法：RegSvr32.dll AnyCon.lll，注销请使用/u参数)，注意，可能导致有些网络程序（如 CuteFTP PASV 模式）无法使用，此时，只要注销AnyCon.dll即可。

  


_已过时，请看CoBind_

  

