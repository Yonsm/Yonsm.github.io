---
author: nanling
comments: true
date: 2013-01-14 15:28:33+00:00
layout: post
slug: mx2-smartbar-vs-google-navigationbar
title: MX2 SmartBar vs 谷歌 NavigationBar
wordpress_id: 171
categories:
- 日志
post_format:
- 日志
---

MX2 SmartBar vs 谷歌 NavigationBar
<!-- more -->
先是三种竖屏模式下的对比，左边为谷歌标准，右边为MX2 （由于虚拟机下无法运行Gmail，用短信代替，不影响演示的效果）








![](/assets/mx2/sms-p.png)


![](/assets/mx2/sms-p2.png)




Case 1: 用4.x的SDK编译的程序，上下两条ActionBar，SmartBar表现最佳，这也是MZ认为最值得称道之处。








![](/assets/mx2/cal-p.png)


![](/assets/mx2/cal-p2.png)




Case 2: 用4.x的SDK编译的程序，只有上面一条ActionBar，SmartBar与普通NavigationBar占用同样多的空间








![](/assets/mx2/gps-p.png)


![](/assets/mx2/gps-p2.png)




Case 3: 用2.x的SDK编译的程序（为了保证在老手机上能运行，国内绝大多数app仍采用这类SDK来编译），仍占用同样多的空间，但看看显示在右侧的三个点的菜单按钮，你觉得哪种更好？！



然后是三种横屏模式下的对比，左边为谷歌标准，右边为MX2








![](/assets/mx2/sms-l.png)


![](/assets/mx2/sms-l2.png)




Case 4: 用4.x的SDK编译的程序，上下两条ActionBar合并到上面一条，但谷歌的NavigationBar仍然占用空间，而MX2则把back显示在最左侧。








![](/assets/mx2/cal-l.png)


![](/assets/mx2/cal-l2.png)




Case 5: 用4.x的SDK编译的程序，只有上面一条ActionBar，但谷歌的NavigationBar仍然占用空间，而MX2则把back显示在最左侧。








![](/assets/mx2/gps-l.png)


![](/assets/mx2/gps-l2.png)




Case 6: 用2.x的SDK编译的程序（为了保证在老手机上能运行，国内绝大多数app仍采用这类SDK来编译），但谷歌的NavigationBar仍然占用空间，注意：这时候MX2没有显示菜单按钮，导致横屏下无法调出菜单！此时用home键手势可实现back。

结论：在上述6种常见的使用情况中，MX2至少5种情况下表现优于谷歌自己的设计，只在最后一项出问题，希望MZ能找到相应的解决方案。至于网友已经发现的其它诸如“显示不太正常、挡住程序内容”之类的BUG，相信MZ已经正在解决中。

当然，最后如何选择由你自己决定，但请善待新生事物，至少MZ的出发点是好的：尽可能的少浪费屏幕空间。。。
