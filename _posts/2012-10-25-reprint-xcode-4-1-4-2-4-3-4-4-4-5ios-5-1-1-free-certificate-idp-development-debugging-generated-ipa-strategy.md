---
author: Yonsm
comments: true
date: 2012-10-25 05:44:36+00:00
layout: post
published: false
slug: reprint-xcode-4-1-4-2-4-3-4-4-4-5ios-5-1-1-free-certificate-idp-development-debugging-generated-ipa-strategy
title: '[转载]Xcode 4.1/4.2/4.3/4.4/4.5 + iOS 5.1.1免证书(iDP)开发+真机调试+生成IPA全攻略'
wordpress_id: 786
categories:
- 文档
---

开发环境使用的是目前为止最新的稳定版软件：Mac OS X Lion 10.7 + Xcode 4.1


目前Xcode 4.2 Preview版也已经发布，据说其修改方法跟4.1非常类似，只改动了一行代码，请参看参考文章的第二篇。本文仍以4.1版本为例。




更新：现在Xcode 4.2正式版和iOS 5均已发布，下面补充上4.2的修改方法。（2011-10-24）




各步骤会标明版本，比如（Xcode4.1请执行）和（Xcode4.2请执行），4.2.1的修改方法与4.2完全相同




未标明的步骤为两个版本均需执行的步骤！




更新：现在Xcode 4.3已发布，修改方法类似，Xcode 4.3的修改步骤将以（Xcode4.3请执行）标出（2012-2-7）




更新：现在Xcode 4.3.2和iOS 5.1.1完美越狱均已发布，本文及时进行了更新。修改方法类似，Xcode 4.3.2的修改步骤将以（Xcode4.3.2请执行）标出（2012-5-28）




更新：Mountain Lion + Xcode 4.4已发布，本人尚未安装，但在评论中看到已经有朋友测试成功，这里祝贺这些朋友！（2012年8月5日）




**_更新：Xcode 4.5 for Mountain Lion已发布。本人已经更新并亲测破解成功。Xcode 4.5将原来XML格式的plist文件变成了二进制格式，故修改方法略有不同，具体操作已在文中给出，请各位朋友测试！（2012年10月2日更新）_**




**_<!-- more -->
_**




**_2012年2月7日更新：_**




**_目前本人已经测试并证实有效的平台有_**




**_Xcode 4.1：_**




**_iPod touch 4 iOS 4.3.3_**




**_
_**




**_Xcode 4.2：_**




**_iPod touch 4 iOS 4.3.3_**




**_iPod touch 4 iOS 5.0_**




**_iPod touch 4 iOS 5.0.1_**




**_
_**




**_Xcode 4.2.1：_**




**_iPod touch 4 iOS 4.3.3_**




**_iPod touch 4 iOS 5.0.1_**




**_iPhone 4S iOS 5.0.1(5A406)_**




**_
_**




**_Xcode 4.3(2012年2月7日更新)_**




**_iPhone 4S iOS 5.0.1(5A406)_**




**_
_**




**_Xcode 4.3.2(2012年5月28日更新）_**




**_iPhone 4S iOS 5.1.1_**




**_
_**




**_Xcode 4.4.1 for Mountain Lion(2012年9月26日更新)_**




**_iPhone 4S iOS 5.1.1_**




**_
_**




**_Xcode 4.5 for Mountain Lion(2012年10月2日更新）_**




**_iPhone 4S iOS 5.1.1_**




**_
_**




**_另外，操作系统的版本貌似对调试影响不大，这期间用过的系统有Mac OS X 10.6~10.8.2，都没有问题。_**




**_
_**




当然您需要先越狱您的设备并通过Cydia安装AppSync





本文参考了多篇文章，综合其中的方法，并修正其中的错误，整理而成。




未经许可，请勿转载。本文首次发表于http://kqwd.blog.163.com/




参考的文章有：




http://laolang.cn/back-end-develop/helloworld-iphone-developer.html




http://ccmos.tw/blog/2011/06/30/xcode4-port-program-to-idevice-without-idp/




_http://www.cnblogs.com/flyingzl/articles/2207717.html_




众所周知，在Xcode上开发的程序只能在模拟器中运行，如果要放到真机上则要花费99美金购买开发者证书iDP。这严重阻碍了我等草根开发者探索的脚步。写个小程序，同学间分享一下这个小小的愿望都不能满足，自然不能善罢甘休。




在没有iDP的情况下，要想将程序放到iPhone上调试，并最终发布IPA用于分享，需要以下几个步骤：




1.自己为自己颁发一个证书用于为生成的程序签名




2.修改工程配置以及Xcode的配置文件和二进制文件以阻止其验证和签名




3.通过自定义生成步骤，用伪造的证书为应用程序签名




4.使用一点小trick来生成IPA文件







1.创建证书




创建证书的过程比较简单，打开实用工具-钥匙串访问。然后在菜单栏里点击钥匙串访问-证书助理-创建证书来打开向导。第一个步骤比较重要，必须要把名称命名为iPhone Developer，将类型设定为代码签名，将"让我覆盖这些默认值"选中。之后的步骤无需更改，一路点击“确定”和“继续”来完成这个向导就可以。







![Xcode 4.1免证书(iDP)开发+真机调试+生成IPA全攻略 - 月下独酌 - 锦瑟华年](http://img.ph.126.net/jAeRPNeRgkVMEhzbZMhIHA==/1295629317816035869.png)







2.修改Xcode的配置文件和二进制文件




下面的步骤稍微有点繁琐，您应该了解UNIX命令行的基本操作，并了解一种命令行文本编辑器，本文使用的是vim。尽管这里会给出完整的代码，但是关于修改和保存代码的基本操作，不再赘述。下面的操作请先**将Xcode按Command+Q完全关闭**。




(1)修改配置文件




进入目录并备份原文件**_（4.1、4.2、4.3在这里主要的差别是SDK的目录名不同）_**







**_（Xcode4.1请执行）_cd /Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS4.3.sdk/**




**_（Xcode4.2请执行）_****cd /Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS5.0.sdk/**




**_（Xcode4.3请执行）_****cd ****/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS5.0.sdk**




**_（Xcode4.3.2请执行）_****cd ****/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS5.1.sdk**




**_（Xcode4.5请执行）_****cd /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS6.0.sdk**




**
**




**sudo cp SDKSettings.plist SDKSettings.plist.orig**




进行编辑**（Xcode 4.5之前）**




**sudo vim SDKSettings.plist**







将以下两段中的YES改为NO







<key>CODE_SIGNING_REQUIRED</key>




<string>**YES**</string>




和




<key>ENTITLEMENTS_REQUIRED</key>




<string>**YES**</string>










**Xcode 4.5的plist格式不再为XML，而是改为了Apple自己的二进制格式，我们使用Xcode本身来编辑这个plist文件，命令是**




**sudo /Applications/Xcode.app/Contents/MacOS/Xcode ./SDKSettings.plist**




**会启动Xcode的图形界面，我们展开_DefaultProperties_分支，将下面的_CODE_SIGNING_REQUIRED_和_ENTITLEMENTS_REQUIRED_两个属性改为_NO_**







下面修改另外一个文件




进入目录并备份原文件







**_（Xcode4.1/4.2请执行）_****cd /Developer/Platforms/iPhoneOS.platform/**




**_（Xcode4.3/4.4/4.5请执行）_****cd /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform**




**
**




备份




**sudo cp Info.plist Info.plist.orig**




进行编辑




**sudo vim Info.plist**







将全部的**XCiPhoneOSCodeSignContext** 修改成 **XCCodeSignContext**，网上的大部分文章说有2处，但我找到了3处，可能是Xcode 4.1要多一处？**_（Xcode 4.2/4.3/4.3.2也有三处）_**总之都改掉了。提示：在在vim中输入/要搜索的内容来搜索，按n键是搜索下一处。







**（Xcode 4.5)**编辑命令如下




**sudo /Applications/Xcode.app/Contents/MacOS/Xcode /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Info.plist**




Xcode 4.5也有三处，分别在DefaultProperties分支下、RuntimeRequirements分支下和OverrideProperties分支下。







(2)二进制补丁




#在桌面上建立script这个脚本







**cd ~/Desktop**




**vim script**







#**_(Xcode 4.1执行)_**在编辑器中输入如下内容







**#!/bin/bash**




**cd /Developer/Platforms/iPhoneOS.platform/Developer/Library/Xcode/Plug-ins/iPhoneOS Build System Support.xcplugin/Contents/MacOS/**




**dd if=iPhoneOS Build System Support of=working bs=500 count=255**




**printf "xc3x26x00x00" >> working**




**/bin/mv -n iPhoneOS Build System Support iPhoneOS Build System Support.original**




**/bin/mv working iPhoneOS Build System Support**




**chmod a+x iPhoneOS Build System Support**







#**_(Xcode 4.2执行)_**在编辑器中输入如下内容







**#!/bin/bash**




**cd /Developer/Platforms/iPhoneOS.platform/Developer/Library/Xcode/PrivatePlugIns/iPhoneOS Build System Support.xcplugin/Contents/MacOS/**




**dd if=iPhoneOS Build System Support of=working bs=500 count=255**




**printf "xc3x26x00x00" >> working**




**/bin/mv -n iPhoneOS Build System Support iPhoneOS Build System Support.original**




**/bin/mv working iPhoneOS Build System Support**




**chmod a+x iPhoneOS Build System Support**







保存并退出。（4.1和4.2在这里的区别也是目录名不同，就是代码中绿色的部分。4.1是**Plug-ins**而4.2是**PrivatePlugIns**）




授予这个脚本执行权限并执行它







**chmod 777 script**




**./script**







正常的话应该输出(具体的数字可能有差别)







**231+1 records in**




**231+1 records out**




**115904 bytes transferred in 0.001738 secs (66694555 bytes/sec)**







#**(Xcode 4.3注意)在Xcode 4.3版本中，我没有找到****iPhoneOS Build System Support.xcplugin****这个插件，因此我跳过了这个步骤，并且最终也成功的进行了联机调试。因此我个人认为Xcode 4.3没有必要执行“二进制补丁”这一步骤。请各位朋友测试~！**




#**(Xcode 4.3.2/4.4/4.5注意)在Xcode 4.3.2版本中，我们可以找到****iPhoneOS Build System Support.xcplugin，但我没有修改它，仍然可以进行联机调试。这个修改步骤是从Xcode 3.X中继承过来的，我们有理由猜测，在Xcode 4.x版本中，已经不需要修改这个文件了。（2012年5月28日更新）**




**
**




至此，对SDK中配置文件和二进制文件的修改就完成了







3.准备自定义的生成后脚本




连接互联网后执行




_**#(Xcode 4.1/4.2执行)**_







**mkdir /Developer/iphoneentitlements401**




**cd /Developer/iphoneentitlements401**




**curl -O http://www.alexwhittemore.com/iphone/gen_entitlements.txt**




**mv gen_entitlements.txt gen_entitlements.py**




**chmod 777 gen_entitlements.py**







**
**




**_#(Xcode 4.3/4.4/4.5执行)_**




**mkdir /Applications/Xcode.app/Contents/Developer/iphoneentitlements**




**cd ****/Applications/Xcode.app/Contents/Developer/iphoneentitlements**







**curl -O http://www.alexwhittemore.com/iphone/gen_entitlements.txt**




**mv gen_entitlements.txt gen_entitlements.py**




**chmod 777 gen_entitlements.py**







**
**




**热心网友Ringo_D指出，这里可能涉及到权限问题。我做的时候貌似没有出啥问题，如果您在执行这段代码时遇到Permission denied提示的话，请将相应的语句前面加上sudo以获取超级权限。（2012年6月15日更新）**







如果您已经联网，则请直接转到步骤4，如果您没有联网，那么请在相应目录手动创建gen_entitlements.py并授予其执行权限，这个文件的内容为







#!/usr/bin/env python










import sys




import struct










if len(sys.argv) != 3:




print "Usage: %s appname dest_file.xcent" % sys.argv[0]




sys.exit(-1)










APPNAME = sys.argv[1]




DEST = sys.argv[2]










if not DEST.endswith('.xml') and not DEST.endswith('.xcent'):




print "Dest must be .xml (for ldid) or .xcent (for codesign)"




sys.exit(-1)










entitlements = """




<?xml version="1.0" encoding="UTF-8"?>




<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">




<plist version="1.0">




<dict>




    <key>application-identifier</key>




    <string>%s</string>




    <key>get-task-allow</key>




    <true/>




</dict>




</plist>




""" % APPNAME










f = open(DEST,'w')




if DEST.endswith('.xcent'):




f.write("xfaxdex71x71")




f.write(struct.pack('>L', len(entitlements) + 8))




f.write(entitlements)




f.close()










4.修改工程设置




**特别注意：本阶段之前的修改配置文件、准备脚本等，只需要做一次。但本阶段的操作，对每个需要真机调试的工程都要做一遍。**




**这个步骤的主要作用是支持真机调试，如果不做这个步骤，仍然可以通过步骤5来生成ipa在真机上运行，但是无法使用Xcode内置的调试器对在真机上运行的程序进行单步跟踪。如果您的程序在点击Run真机调试时秒退，请检查此步骤是否正确完成。**


(1)禁用Xcode自动的签名操作






将工程配置中所有的Code Signing选项全部设为Don't Code Sign，如图。可能需要先点击“All”让这个选项显示出来







![Xcode 4.1免证书(iDP)开发+真机调试+生成IPA全攻略 - 月下独酌 - 锦瑟华年](http://img.ph.126.net/COoAQeLE26iWVlMtNEei5A==/2529052665762129796.png)







(2)添加自定义的生成后脚本




在Build Phases中添加一个Phase，右下角的Add Build Phase，然后单击Add Run Script，输入以下脚本




**_（对于Xcode 4.1/4.2）_**







**export CODESIGN_ALLOCATE=/Developer/Platforms/iPhoneOS.platform/Developer/usr/bin/codesign_allocate**




**if [ "${PLATFORM_NAME}" == "iphoneos" ] || [ "${PLATFORM_NAME}" == "ipados" ]; then**




**/Developer/iphoneentitlements401/gen_entitlements.py "my.company.${PROJECT_NAME}" "${BUILT_PRODUCTS_DIR}/${WRAPPER_NAME}/${PROJECT_NAME}.xcent";**




**codesign -f -s "iPhone Developer" --entitlements "${BUILT_PRODUCTS_DIR}/${WRAPPER_NAME}/${PROJECT_NAME}.xcent" "${BUILT_PRODUCTS_DIR}/${WRAPPER_NAME}/"**




**fi**










**_（对于Xcode 4.3/4.4/4.5）_**










export CODESIGN_ALLOCATE=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/usr/bin/codesign_allocate




if [ "${PLATFORM_NAME}" == "iphoneos" ] || [ "${PLATFORM_NAME}" == "ipados" ]; then




/Applications/Xcode.app/Contents/Developer/iphoneentitlements/gen_entitlements.py "my.company.${PROJECT_NAME}" "${BUILT_PRODUCTS_DIR}/${WRAPPER_NAME}/${PROJECT_NAME}.xcent";




codesign -f -s "iPhone Developer" --entitlements "${BUILT_PRODUCTS_DIR}/${WRAPPER_NAME}/${PROJECT_NAME}.xcent" "${BUILT_PRODUCTS_DIR}/${WRAPPER_NAME}/"




fi







**
**










如图所示：







![Xcode 4.1免证书(iDP)开发+真机调试+生成IPA全攻略 - 月下独酌 - 锦瑟华年](http://img.ph.126.net/bBJubN8gFr5KAzCSvFEqvA==/672162244401931959.png)







至此配置全部完成，下面就可以插上iPhone，重新选择生成目标来测试一下在线调试了！如果是第一次使用该设备调试，请先在Organizer中将设备切换为开发模式，具体操作请见常见问题5。













5.旁门左道生成IPA文件




如果我的程序调试好了，怎么才能发给别人用呢？正常情况下IPA文件是从Xcode的Organizer中输出的，但是我们没有证书，这样输出会产生错误。我们只能用个小trick来完成这个操作了。




先将代码生成为Release目标，然后打开工程的输出文件夹，通常情况下这个目录是




**/Users/你的用户名/Library/Developer/Xcode/DerivedData/以工程名打头的文件夹/Build/Products/Release-iphoneos**




很纠结吧~这个目录下有个.app的文件，就是生成的程序了。把这个.app拖到iTunes中，它会出现在应用程序那个列表中，然后再把它从iTunes的那个列表中拖出来（比如拖到桌面），发生了什么？哈哈，它就这样变成.ipa了！




把这个.ipa发给朋友，大家就可以跟您一起分享这个程序了。







文章发表以来点击量已经超过了5000次，也收到了不少热心博友的反馈和疑问。现加以整理，列为常见问题。感谢大家的关注！（2011年12月2日）







**常见问题：**




**不成功的先看这里！！本文点击量超过6000，无数网友亲测成功，如果您失败了基本可以确定是您没有严格按照文中的方法操作，下面列出常见问题，切望各位朋友提问前先看看！！（2011年12月14日）**




**
**




**1. 我是初学者，请问什么是权限？执行权限（x权限）是什么意思？什么是脚本？如何加执行权限？sudo是什么命令？vim是什么，如何在vim中保存更改？你说的目录我没找到怎么办？我有些步骤没看明白，能不能加QQ交流？**







**解答：首先感谢您关注我的博客。这里要提醒各位初学者朋友，Xcode提供了非常完善的模拟器调试环境，模拟器调试要比真机调试方便得多，也简单得多，使用模拟器调试程序是iOS开发的常态。真机调试通常是在产品快要完工时才进行的，看一下程序在实际机器上的视觉效果等等。还有依赖于加速度计的程序要测试一下加速度计的程序有没有问题。所以初学者并不需要一开始就进行真机调试。初学者配置真机调试的主要目的可能并非学习技术，而是满足好奇心、追求成就感甚至是为了向朋友炫耀等等。而这些目的并不值得您花费这么大的精力来阅读本文。**




**因此本文是给有一定基础的朋友看的，各种命令是免不了的。UNIX中的基本命令比如cp，mv，cd，chmod，sudo啥的还有vim编辑器，如果您都没听说过，强烈建议您不要尝试本文提到的修改。一旦改错了轻则Xcode挂掉，重则系统崩溃。****如果遇到解决不了的问题欢迎留言询问，务必给出详细的错误信息，否则无法判断。****博主恕不解答类似于如何执行脚本代码，如何赋予执行权限，如何使用vim编辑器（如何保存）等与iOS开发无关的UNIX基础问题。博主非常乐意以文会友，结识有思想、有创意、有技术的大牛。博主也会不定时到博客上对热心网友提出的问题进行简单的解答。但并没有充足的时间通过QQ对文中的步骤进行手把手的解释和指导。这里先向有这种需求的朋友说声抱歉了！**







**
**




**2. 各种错误，错误信息中包含“No such file or directory”这句话**




**解答：错误信息的含义非常清楚，就是“没有这个文件或者目录”。这类错误通常是由于您拷贝代码时不全或者开发环境安装错误等问题导致的。请再次检查报错的目录是否存在，检查代码与本文给出的是否严格一致，各种检查吧~总之是低级错误**




**
**




**3. 联机调试时程序秒退，或者无法安装到设备，或者任何时候报错，错误信息中包含“code signing”、“CERT”、“signature”或者“certificate”字样的（最常见的错误！！）**




**解答：证书错误或者签名错误，这种问题就不要问了，肯定是因为您没有严格文中的步骤做。提醒您检查的地方有(1)有没有设置为Don't Code signing (2)生成后事件的代码是否已经正确粘贴 (3)那个Python脚本是否已经成功执行 (4)设备是否已经越狱并安装AppSync (5)第一步的iPhone Developer证书是否已经正确创建**




**其中最可能出问题的就是生成后事件代码（文中的那个Run Script）没有正确执行。可能是您忘记了添加Run Script并粘贴那段代码，也可能是您没复制全，或者复制到了啥特殊字符导致执行出错。查看那个script的执行结果的方法是在Xcode左侧的侧边栏里，点最靠右的一个标签（Show the Log navigator），看最近的一个Build日志（不是Debug日志），找到一行Run custom shell script "Run Script"那一行，正常情况下那一行跟其他行一样，是不能展开的。如果那一行左边有个小箭头，点击后能展开的话，说明执行出错，展开后的信息即为出错的信息。请认真查看错误信息并修正脚本中的错误。如果Build日志里根本没有****Run custom shell script "Run Script"，那说明您忘记添加Build script了。。。（2012年2月9日更新）**




**_补充：Run Script经常报的一条错误是“replacing existing signature_****_”。。。这个提示的意思是“替换已有的签名”，出现这个提示的原因是，你并没有成功的阻止Xcode使用默认的方法为应用程序签名。因为这个破解的原理就是阻止Xcode为app签名，而用script中的自定义过程手动为app签名。当script为app签名时，发现app已经被Xcode签名过了，就会报这个错误。出这个错误后提醒您检查的地方有两个（1）SDKSettings.plist中需要修改的地方是否已经正确修改 （2）工程设置里是否将那5个签名的选项全部设为Don't Code signing （2012年6月15日更新）_**




**
**




**4. iPad能用吗？**




**解答：我没有iPad，所以没法准确回答。但从热心博友的回复来看，iPad无疑是可以用的。**




**如果要用ipad 需要把第四步脚本文件里的 platform_name == iphones 换成platform_name == ipads 不然会报错的~ （感谢博友xyishao的建议）**




**感谢qingcheng89提出的改进意见，现在来看上述代码可以直接支持iPad而无需修改，请各位朋友测试。（2012年2月9日更新）**




**
**




**5. 为什么我的Build for Archiving选项是灰色的？**




**解答：是因为您没有把设备插到电脑上。虽然这个问题挺蠢的，但我曾经也有过这个疑问，哈哈~~ **







**经热心网友xc7296815提醒，设备未开启开发模式也会导致Build for Archiving不可用。开启开发模式的方法是：插上设备，点Xcode右上角的Organizer图标，选中您的设备，看一下设备名称左侧的小灯是什么颜色的。若是灰色代表未开启开发模式。此时在右边窗口中点击“****Use for Development****” 即可。若是黄色请重新插拔设备，若是绿色代表设备已经开启开发模式(2011年12月25日)**




**关于启用开发模式的补充：点击Use for Development后，会要求输入Apple ID，这里点击取消即可。这时启用设备开发模式的进程会立即终止。设备名称旁边应该有一个黄灯。此时重新插拔设备，Organizer中会出现一个进度条，等这个进度条跑完，小灯就会变成绿色，开发模式已经启用。(2012年5月28日更新)**




_**再补充：最近经常有人提问说，无论怎么搞，Organizer中的灯始终是黄色的。这种情况几乎可以百分之百的确定是您的Xcode版本不够高。如果您的设备是iOS 5.1.1，则必须使用Xcode 4.3.2或以上版本。同样的道理，iOS 5.0.1对应Xcode 4.3.1，iOS 5.0对应Xcode 4.3……（2012年6与5日更新）**_




**
**




**6.我的iOS版本/Xcode版与你的不同，能用吗？**




**解答：本人测试过的环境和设备已经在文章开头给出。其他环境我没有测试过，也没有条件测试，因此当您的环境与我的不同时，别问我可不可用，您可以试一下，然后把结果告诉我，也为其他的网友提供方便，在此先谢谢您了！**




**
**




**7.真机调试时出现****Error launching remote program: failed to get the task for process xxx错误（2012年1月26日更新）**




**解答：我在调试中貌似没有遇到过这个问题，但是不少网友指出会有这个问题，谁来告诉我什么情况下会出这个问题呢？如果您遇到了这个问题，请阅读Apple官方的帮助文档http://developer.apple.com/library/ios/#qa/qa1710/_index.html**




**2012年2月1日更新：有网友指出该错误是由于权限设置错误导致的。由于我使用了跟报错的那位网友完全相同的环境，而在操作过程中并没有遇到这个错误，所以基本可以确定是您没有按步骤操作造成的，请您再次检查整个过程，尤其是热心网友提出的下载脚本并修改执行权限的部分。**




**经本人测试，如果该错误出现在编译运行之后，且现象为设备上的程序闪退，则是由于签名错误导致的，这是由于您没有严格按照上述步骤来做导致的，请参考常见问题3.（2012年2月9日更新）**







转自：[http://kqwd.blog.163.com/blog/static/4122344820117191351263/](http://kqwd.blog.163.com/blog/static/4122344820117191351263/)



