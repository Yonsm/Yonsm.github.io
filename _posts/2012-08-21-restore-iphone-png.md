---
date: 2012-08-21 07:31:23+00:00
layout: post
title: 真正能还原/修复 iPhone PNG 的有效方法
thread: 734
categories: 文档
tags: iOS 编程
---

iPhone/iPad 的 IPA 包中的  PNG 文件在编译时默认会做特殊处理（应该是以便硬件加速解码？），有时候需要“参考”下第三方的 PNG 图片的时候带来了巨大的麻烦：一直流传着各种方法和工具，分别是 Windows 下的 FixPng、Mac下的iPhone PNG Fix、Python脚本修复、PNG Nomalizer（[http://www.beyondcow.com/pngnormalizer/](http://www.beyondcow.com/pngnormalizer/)），在线修复（[http://www.raisedtech.com/iphone-ipa-png/](http://www.raisedtech.com/iphone-ipa-png/)）等等这种各样。实际用下来基本上对于现在的 IPA 文件中的 PNG 多半有很多图片无法还原。

解铃还须系铃人，为了真正解决这个问题，我们还是从 iOS 设备上入手吧：

<!-- more -->1.先拿到 IPA 解出所有的 PNG；

2.编译到我们的程序 iOS App 中；

3.在程序中枚举所有的 PNG，装载，重新保存为 PNG——此时生成的 PNG 就是通用格式的 PNG 啦，真正解决了问题：

{% highlight objc linenos %}

//
BOOL UIUtil::NormalizePngFile(NSString *dst, NSString *src)
{
    NSString *dir = dst.stringByDeletingLastPathComponent;
    if ([[NSFileManager defaultManager] fileExistsAtPath:dir] == NO)
    {
        [[NSFileManager defaultManager] createDirectoryAtPath:dir withIntermediateDirectories:YES attributes:nil error:nil];
    }
    
    UIImage *image = [UIImage imageWithContentsOfFile:src];
    if (image == nil) return NO;
    
    NSData *data = UIImagePNGRepresentation(image);
    if (data == nil) return NO;
    
    return [data writeToFile:dst atomically:NO];
}

//
void UIUtil::NormalizePngFolder(NSString *dst, NSString *src)
{
    NSArray *files = [[NSFileManager defaultManager] subpathsAtPath:src];
    for (NSString *file in files)
    {
        if ([file.lowercaseString hasSuffix:@".png"])
        {
            NormalizePngFile([dst stringByAppendingPathComponent:file], [src stringByAppendingPathComponent:file]);
        }
    }
}
{% endhighlight %}


4.拷贝出这些 PNG 来即可。

上面仅仅时代码片段，可以完善一下，可以写个小程序，输入 IPA 的地址直接把图片还原出来。

