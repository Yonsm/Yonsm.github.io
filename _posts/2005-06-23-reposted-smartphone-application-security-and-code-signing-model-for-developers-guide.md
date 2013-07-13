---
author: Yonsm
comments: true
date: 2005-06-23 23:05:26+00:00
layout: post
slug: reposted-smartphone-application-security-and-code-signing-model-for-developers-guide
title: '[转贴]Smartphone 应用程序安全与代码签名模型开发人员实用指南'
wordpress_id: 36
categories:
- 文档
---

MSDN 中文: [http://www.microsoft.com/china/MSDN/library/Mobility/pocketpc/2k3smartphonesecurity.mspx](http://www.microsoft.com/china/MSDN/library/Mobility/pocketpc/2k3smartphonesecurity.mspx)

<!-- more -->

# Smartphone 应用程序安全与代码签名模型开发人员实用指南

## 

发布日期： 2/28/2005 | 更新日期： 2/28/2005

James Pratt  
Microsoft

适用于：  
Microsoft® Windows® Powered Smartphone 2002  
Windows Mobile™ 2003 software for Smartphones  
Windows Mobile 2003 Second Edition software for Smartphones  
Microsoft ActiveSync®  
Microsoft Visual Studio® .NET 2003  
Microsoft eMbedded Visual C++® version 3.0  
Microsoft eMbedded Visual C++ version 4.0

**摘要：**本文介绍应用程序开发人员必须了解的有关 Smartphone 应用程序安全模型的内容、以及当某款基于 Windows Mobile 的 Smartphone 推向市场时移动运营商所拥有的不同策略选择。

![*](http://www.microsoft.com/library/gallery/templates/MNP2.Common/images/3squares.gif)

##### 本页内容

[![摘要](http://www.microsoft.com/library/gallery/templates/MNP2.Common/images/arrow_px_down.gif)](http://www.microsoft.com/china/MSDN/library/Mobility/pocketpc/2k3smartphonesecurity.mspx#EHAA)
[摘要](http://www.microsoft.com/china/MSDN/library/Mobility/pocketpc/2k3smartphonesecurity.mspx#EHAA)

[![应用程序安全背景](http://www.microsoft.com/library/gallery/templates/MNP2.Common/images/arrow_px_down.gif)](http://www.microsoft.com/china/MSDN/library/Mobility/pocketpc/2k3smartphonesecurity.mspx#EGAA)
[应用程序安全背景](http://www.microsoft.com/china/MSDN/library/Mobility/pocketpc/2k3smartphonesecurity.mspx#EGAA)

[![代码签名实践](http://www.microsoft.com/library/gallery/templates/MNP2.Common/images/arrow_px_down.gif)](http://www.microsoft.com/china/MSDN/library/Mobility/pocketpc/2k3smartphonesecurity.mspx#EFAA)
[代码签名实践](http://www.microsoft.com/china/MSDN/library/Mobility/pocketpc/2k3smartphonesecurity.mspx#EFAA)

[![小结](http://www.microsoft.com/library/gallery/templates/MNP2.Common/images/arrow_px_down.gif)](http://www.microsoft.com/china/MSDN/library/Mobility/pocketpc/2k3smartphonesecurity.mspx#EEAA)
[小结](http://www.microsoft.com/china/MSDN/library/Mobility/pocketpc/2k3smartphonesecurity.mspx#EEAA)

[![附录 A：受保护的注册表项](http://www.microsoft.com/library/gallery/templates/MNP2.Common/images/arrow_px_down.gif)](http://www.microsoft.com/china/MSDN/library/Mobility/pocketpc/2k3smartphonesecurity.mspx#EDAA)
[附录 A：受保护的注册表项](http://www.microsoft.com/china/MSDN/library/Mobility/pocketpc/2k3smartphonesecurity.mspx#EDAA)

[![附录 B：特权 API 列表](http://www.microsoft.com/library/gallery/templates/MNP2.Common/images/arrow_px_down.gif)](http://www.microsoft.com/china/MSDN/library/Mobility/pocketpc/2k3smartphonesecurity.mspx#ECAA)
[附录 B：特权 API 列表](http://www.microsoft.com/china/MSDN/library/Mobility/pocketpc/2k3smartphonesecurity.mspx#ECAA)

## 摘要

Microsoft™ 基于 Windows Mobile 的 Smartphone 是根据数字代码签名实现应用程序安全模型的。希望以基于 Windows Mobile 的 Smartphone 为目标的应用程序开发人员需要了解 Smartphone 应用程序安全模型、以及当某款基于 Windows Mobile 的 Smartphone 推向市场时移动运营商所拥有的不同策略选择。

如果您是一位了解构建 Pocket PC 或 Smartphone 应用程序的 Smartphone 开发人员，并且还在构建 Pocket PC 和/或 Smartphone 安装包 (.cab)，本文将提供您所需的一切，以帮助您了解 Smartphone 应用程序安全模型、特权与非特权应用程序的不同之处、如何确定您的应用程序是否需要特权信任、如何配置进行 Smartphone 开发的开发环境，以及如何通过代码签名供应商进行应用程序签名。

[![返回页首](http://www.microsoft.com/library/gallery/templates/MNP2.Common/images/arrow_px_up.gif)](http://www.microsoft.com/china/MSDN/library/Mobility/pocketpc/2k3smartphonesecurity.mspx#top)[返回页首](http://www.microsoft.com/china/MSDN/library/Mobility/pocketpc/2k3smartphonesecurity.mspx#top)

## 应用程序安全背景

[_Mobile2Market FAQ_](http://msdn.microsoft.com/mobility/windowsmobile/partners/mobile2market/faq.aspx) 提供了一个非常不错的针对应用程序安全与代码签名的高级指南。在阅读本文之前，您可能希望阅读 Mobile2Market FAQ，以便为您提供有价值的背景知识。

**数字代码签名**

数字代码签名是一种验证数字内容来源的方式。在 Windows Mobile 领域中，有时会将它与徽标认证混淆。徽标认证是验证某个 Windows Mobile 应用程序是否符合一组实现 Windows Mobile 应用程序的指导原则的过程。当前的指导原则可以在 [_Mobile2Market __站点_](http://msdn.microsoft.com/mobility/windowsmobile/partners/mobile2market/)上找到。经过认证的应用程序在应用程序中和它的包装上都标有“Designed for Windows Mobile”徽标。“Designed for Windows Mobile”徽标不担保应用程序是由它声明的软件供应商构建的，也不担保如果它由该软件供应商构建，它没有在软件供应商发出它和您接收到它的这段时间内遭到恶意篡改。而代码签名确实提供了这些担保。

让人感到不解的是，数字代码签名既使用数字证书，又有一个单独的徽标认证程序。其实，这两者有完全不同的目的和目标。

**究竟为什么要进行数字代码签名？**

数字代码签名不是基于 Windows Mobile 的 Smartphone 所独有的。每次 Microsoft® Internet Explorer 询问您是否希望安装 Active X® 控件，然后询问您是否希望“信任来自 X 公司的内容”时，应用程序是在要求您决定是否信任内容提供商。Internet Explorer 断言相关的包在签名后没有更改过。如果您信任该来源，那么您就可以信任该应用程序，因为它来源于一个经过验证的源。代码签名将验证数字内容的来源以及自从它签名后没有更改过的事实。

**用于**** Smartphone ****的**** Windows ****Mobile********软件的应用程序安全**

通过禁止用户从一个未知源安
