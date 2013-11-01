---
layout: post
title: '在 Mac OS X 下“绿色”安装 Photoshop'
category: 文档
tags: 折腾
---

在 Mac OS X 中基本上绝大部分都是“绿色”安装的（包括 iWork、Xcode 这种大型的软件），重装系统或者其它情形下（你懂的）如果需要迁移程序，那是相当地简单方便。基本上是一次性搞定所有的软件。

但东西总有例外，有几个顽固不化的东西，比如 Photoshop、Office（M$的东西安装体验一贯很尿性）、Parallels Desktop 都没法“绿色安装”。趁着 10.9 重装了一次系统，决心重新理一下软件。对于 Parallels Desktop，实在扛不住一年一升级就要重新购买序列号（去年买了8.0，今年升级到9.0还要重花钱买），决定换 VMWare Fusion；对于 Office，决定不再创建 Office 文档，反正 iWork 也能阅读 Office 文档；但对于 Photoshop，暂时实在无可替代，只好深入研究一番……，终于找到了方案，简述如下：

一、首次安装

1. 试用方式安装；

2. 升级到最新；

3. ***；

二、“绿色”迁移

1. 拷贝 /Applications/Adobe Photoshop CC；

2. 拷贝 /Library/Application Support/Adobe 以及 ~/Library/Application Support/Adobe;

3. 运行 PS，提示“Adobe Application Support 文件夹中缺少运行 Photoshop 所需的一个或多个文件。请运行 Photoshop 安装程序，并重新安装 Photoshop。”，网上非常多人反映此问题，但没有解决方案。突然转念一想，换成英文关键字搜索，发现 [Adobe 官网有篇文章](http://helpx.adobe.com/photoshop/kb/error-one-or-files-application.html)，内容比较长，说白了就是还要拷贝 /Library/ScriptingAdditions/Adobe Unit Types.osax

4. 再次运行，一切搞定收工。

终于全部软件都是“绿色”啦……