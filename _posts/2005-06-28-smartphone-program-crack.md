---
date: 2005-06-28 01:34:28+00:00
layout: post
title: Smartphone 程序的 Crack
thread: 34
categories: 文档
---

今天成功地上演了我的第一次 SP 破解秀——把一个好久前就想 PJ 的 SP 软件给搞定了。总结一下，步骤如下：

  1. 目标程序：来电通 1.03，时间限制，国产软件，破解结果仅供自己享用（过期后主要功能仍可使用，感谢作者的大度，所以我就不公布了：）

  2. 需要准备的工具：IDA，DumpROM（PC 上使用，用于解出 SP 系统DLL），FiziFetch （我写的尚未发布的工具，用于读取物理内存/ROM），UltraEdit，数字签名工具。

  3. 用 FiziFetch 和 DumpROM 提取系统 DLL，包括 CoreDLL.dll、AygShell.dll 等（具体请参看另一篇文章，待写）。

  4. 使用 IDA 反汇编目标程序，记得导入系统 DLL 的导出符号，这样才有助于分析程序行为（如果全是导出地址，根本没法分析、揣摩）。

  5. 凭经验+细心+运气+毅力+意识+……，经过多次分析、测试，发现有两处关键位置保存有程序运行天数的信息（一个是注册表的 HKCUSoftwareMicrosoftWindowsCurrentVersionExplorerIconUnderline，一个是 StorageWindowsFontsSystem.fon 文件），只要删除这两个位置的信息，程序就是认为没有运行过，可以再次运行 30 天了：）

  6. 在 IDA 中找到写入文件和注册表的位置，把这些地方的功能 Cancel 掉（把 ARM 指令 BNE 改称 B，强制转跳）。只更改两个字节。

  7. 用资源编辑器 ResHacker 修改一下资源，写入“时限破解: Yonsm.zj.com”，然后用特权模式签个名吧，不然无法运行（有关数字签名，请参看我 BLOG 上的另一篇文章），呵呵~~

OK，这下好了，来电秀成了全功能版本，永不过期……

Smartphone 的加密一般都很简单，入了这个门槛就容易啦——我可全是自己琢磨的啊……现在网上的没有参考资料特少，有关破解的根本没有，晕！

P.S. Smartphone 的程序也太简单了，可是国内的软件都在卖钱，晕倒！也太没共享精神了……看看人家老外的 BetaPlayer……
