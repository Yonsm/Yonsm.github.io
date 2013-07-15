---
date: 2012-08-31 23:18:54+00:00
layout: post
title: '[转载]Developing without Provisioning Profile'
thread: 763
categories: 文档
tags: iOS 编程
---

To develop for the devices one should first obtain a provisioning profile by joining the iPhone Developer Program (which costs $99). However, some simple tricks can be used to make Xcode compile and debug on jailbroken devices without provisioning profiles.

These steps are only tested for Xcode 3.2.x/iPhone SDK 3.x and Xcode 4.3.x/iPhone SDK 5.x. If for some reason you are stuck with Xcode 3.1.x, try [[1]](http://iphonesdkdev.blogspot.com/2009/06/use-xcode-312-to-build-sdk-30-app-to-30.html).<!-- more -->




### Compiling


Performing these steps allows you to use Xcode to compile any applications and deploy it yourself.



	
  * **1.** Create a self-signed code-signing certificate with the name “iPhone Developer” on the “login” (default) keychain using Keychain Access[[1]](http://www.iphonedevwiki.net/index.php/Xcode#cite_note-0).

	
  * **2.** Open /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Info.plist (4.2 or below: /Developer/Platforms/iPhoneOS.platform/Info.plist)

	
  * **3.** Replace all occurrences of XCiPhoneOSCodeSignContext by XCCodeSignContext. There are three of them (XCode Version 3.2.4+).

	
  * **4.** Save the file and restart Xcode.


If you upgrade the iPhone SDK, you need to perform steps 2 – 4 again.




### Replacing codesign with ldid


These steps are necessary for debugging, since the entitlement can no longer be inserted by performing steps 1 – 4. To actually debug your app, make sure you have add -gta to **Other Code Signing Flags** of your target.



	
  * **5.** Make sure you have ldid on your Mac[[2]](http://www.iphonedevwiki.net/index.php/Xcode#cite_note-1). Place a copy in /usr/local/bin.

	
  * **6.** Create the Python script /usr/local/bin/ldid3.py. Make it executable. Fill it with:









    
    #!/usr/bin/env python
    
    from sys import argv
    from subprocess import check_call
    from os.path import basename, splitext, join
    from tempfile import NamedTemporaryFile
    
    app = argv[-1]
    obj_path = join(app, splitext(basename(app))[0])
    
    if '-gta' not in argv:
        check_call(['/usr/local/bin/ldid', '-S', obj_path])
    else:
        with NamedTemporaryFile() as f:
            f.write("""
    <!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
    <plist version="1.0">
      <dict>
        <key>get-task-allow</key>
        <true/>
      </dict>
    </plist>
            """)
            check_call(['/usr/local/bin/ldid', '-S' + f.name, obj_path])











	
  * **7.** Open iPhoneCodeSign.xcspec.

	
    * For Xcode 4.3 the file is at: /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/Library/Xcode/PrivatePlugIns/iPhoneOS Build System Support.xcplugin/Contents/Resources/iPhoneCodeSign.xcspec

	
    * For Xcode 4.2 the file is at: /Developer/Platforms/iPhoneOS.platform/Developer/Library/Xcode/PrivatePlugIns/iPhoneOS Build System Support.xcplugin/Contents/Resources/iPhoneCodeSign.xcspec

	
    * For older versions the file is at: /Developer/Platforms/iPhoneOS.platform/Developer/Library/Xcode/Plug-ins/iPhoneOS Build System Support.xcplugin/Contents/Resources/iPhoneCodeSign.xcspec




	
  * **8.** Replace the line saying CommandLine = "/usr/bin/codesign" with CommandLine = "/usr/local/bin/ldid3.py". It should be around line 12.

	
  * **9.** Save the file and restart Xcode.


If you upgrade the iPhone SDK, you need to perform steps 8 – 9 again.




### Allowing apps with invalid signatures to be installed


These steps allow you to install an unsigned app to the device. This method only works for iOS 4.0 or above.



	
  * **10.** Create a file /var/mobile/tdmtanf on the device, to enable Apple's "TDMTANF bypass" in installd (warning: doing so will also put you in a sandboxed GameCenter[[3]](http://www.iphonedevwiki.net/index.php/Xcode#cite_note-2)).


If you upgrade the firmware, you need to do step 10 again.




## References





	
  1. [↑](http://www.iphonedevwiki.net/index.php/Xcode#cite_ref-0) Procedures can be found in [http://developer.apple.com/mac/library/documentation/Security/Conceptual/CodeSigningGuide/Procedures/Procedures.html](http://developer.apple.com/mac/library/documentation/Security/Conceptual/CodeSigningGuide/Procedures/Procedures.html)

	
  2. [↑](http://www.iphonedevwiki.net/index.php/Xcode#cite_ref-1) If not, you can install from Fink unstable, compile it from git://git.saurik.com/ldid.git, or just download [https://github.com/downloads/rpetrich/ldid/ldid.zip](https://github.com/downloads/rpetrich/ldid/ldid.zip)

	
  3. [↑](http://www.iphonedevwiki.net/index.php/Xcode#cite_ref-2)[https://discussions.apple.com/thread/2745420?start=0&tstart=0](https://discussions.apple.com/thread/2745420?start=0&tstart=0)


转自：[iPhoneDev Wiki](http://www.iphonedevwiki.net/index.php/Xcode#Developing_without_Provisioning_Profile)，大宝库
