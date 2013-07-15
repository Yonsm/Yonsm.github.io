---
date: 2011-05-12 19:52:49+00:00
layout: post
title: '[转载]导入通讯录到 iPhone Simulator'
thread: 541
categories: 文档
tags: iOS 编程
---

Using your own address book in the iPhone Simulator  
<!-- more -->  
Jailbroken iPhone with OpenSSH:  
  
  
scp mobile@192.168.1.10:~/Library/AddressBook/* ~/Library/Application\ Support/iPhone\ Simulator/User/Library/AddressBook  
  
  
Non-jailbroken iPhone:  
  
#!/bin/bash  
  
cd ~/Library/Application\ Support/MobileSync/Backup  
backup=`ls -t1 | sed -n '1p'` # most recent backup  
for f in "$backup"/*.mdinfo; do  
   grep -q "Library/AddressBook/AddressBook.sqlitedb" $f  
   if [ $? -eq 0 ]; then  
       addressbook=`basename $f .mdinfo`  
       cp -v "`pwd`/$backup/$addressbook.mddata" ~/Library/Application\ Support/iPhone\ Simulator/User/Library/AddressBook/AddressBook.sqlitedb  
       exit $?  
   fi  
done  
  
echo "Address Book not found in iPhone backup" >&2  
exit 1  
  
  
  
转自：http://0xced.blogspot.com/2009/01/using-your-own-address-book-in-iphone.html  
修正：新版本（如iOS SDK 4.3.2）的通讯录数据在~/Library/Application\ Support/iPhone\ Simulator/4.3.2/Library/AddressBook中，而不是User目录。  

