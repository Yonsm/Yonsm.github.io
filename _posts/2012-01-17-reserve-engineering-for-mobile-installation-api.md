---
date: 2012-01-17 04:36:25+00:00
layout: post
title: 分析 iOS 中使用 Mobile Installation 安装 IPA
thread: 553
categories: 文档
tags: iOS 逆向工程
---

iOS 中要安装一个程序，从用户角度看有几种三：

1. 类似 Cydia 这种 DEB 的方式：直接安装到 /Applications 作为系统的APP，无法长按删除（不讨论CyDelete）。

2. 类似 UCWEB/Installous 的伪 IPA 的方式：直接解包 IPA （实际上就是 ZIP）,模拟官方 IPA 的安装方式。可以理解为黑盒测试这种只管结果的模式。这个安装方式可以说是知其表而不知其里，会有N多问题，如图标可能无法刷新、IPA无法同步回 iTunes 等问题。从这个角度说，我个人不推荐大家使用 UCWEB 下载安装 IPA，也不推荐使用 Installous。

3. 官方支持的 AppStore/iTunes 安装 IPA 的模式：这就是我这里要说的 Mobile Installation Framework 的方式，这是最官方、最安全、最完美的安装 IPA 的方式。目前已知、同步推/iFunBox/iFanBox/iTools都是使用这几种方式（其中 iFanBox 应该是在我和我交流之后才搞定这个：）

Mobile Installation 是 iOS 中负责安装 IPA 的 Framework，<!-- more -->，通过 IDA 分析 /Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS5.0.sdk/System/Library/PrivateFrameworks/MobileInstallation.framework/MobileInstallation 可知它导出了以下 API：

Name Address Ordinal
---- ------- -------
_MobileInstallationArchive 00000F80
_MobileInstallationBrowse 00000FE0
_MobileInstallationCheckCapabilitiesMatch 00000BE0
_MobileInstallationCopySafeHarbors 00000CA4
_MobileInstallationInstall 00001144
_MobileInstallationLookup 00001034
_MobileInstallationLookupArchives 00000E70
_MobileInstallationProcessRestoredContainer 00000E10
_MobileInstallationRegisterSafeHarbor 00000D58
_MobileInstallationRemoveArchive 00000EC0
_MobileInstallationRemoveSafeHarbor 00000CF4
_MobileInstallationRestore 00000F20
_MobileInstallationSetDeviceCapabilities 00000C40
_MobileInstallationUninstall 00001084
_MobileInstallationUpgrade 000010E4
__MobileInstallationRebuildMap 00000B90

其中有两个 API 是非常有用的：

_MobileInstallationInstall：安装 IPA
_MobileInstallationLookup：列出已安装的 IPA

直接贴 MobileInstallationInstall 分析结果了，分析过程看前面几期：）

`
//
typedef int (*MobileInstallationInstall)(NSString *path, NSDictionary *dict, void *na, NSString *path2_equal_path_maybe_no_use);
IPAResult IPAInstall(NSString *path)
{
    void *lib = dlopen("/System/Library/PrivateFrameworks/MobileInstallation.framework/MobileInstallation", RTLD_LAZY);
    if (lib)
    {
        MobileInstallationInstall pMobileInstallationInstall = (MobileInstallationInstall)dlsym(lib, "MobileInstallationInstall");
        if (pMobileInstallationInstall)
        {
            NSString *name = [@"Install_" stringByAppendingString:path.lastPathComponent];
            NSString* temp = [NSTemporaryDirectory() stringByAppendingPathComponent:name];
            if (![[NSFileManager defaultManager] copyItemAtPath:path toPath:temp error:nil]) return IPAResultFileNotFound;

            int ret = (IPAResult)pMobileInstallationInstall(temp, [NSDictionary dictionaryWithObject:@"User" forKey:@"ApplicationType"], 0, path);
            [[NSFileManager defaultManager] removeItemAtPath:temp error:nil];
            return ret;
        }
    }
    return IPAResultNoFunction;
}

`

补充一下，之所以要拷贝IPA是因为安装IPA后可能被删除。如果安装IPA可以删除无所谓则不需要拷贝到一个新地方。

详细代码，请邮件索取 Yonsm@msn.com。
