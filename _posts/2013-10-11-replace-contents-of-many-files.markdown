---
author: pandao
comments: false
date: 2013-10-11
layout: post
slug: replace-contents-of-many-files
title: Linux批量替换文本内容
categories:
- linux
---






1、网络上现成的资料
　　格式: sed -i "s/查找字段/替换字段/g" `grep 查找字段 -rl 路径`

　　linux sed 批量替换多个文件中的字符串

　　sed -i "s/oldstring/newstring/g" `grep oldstring -rl yourdir`

　　例如：替换/home下所有文件中的www.admin99.net为admin99.net

　　sed -i "s/www.admin99.net/admin99.net/g" `grep www.admin99.net -rl /home`

　　exp:sed -i "s/shabi/$/g" `grep shabi -rl ./`

2、自己额外附加

　　2.1 将文件1.txt内的文字“garden”替换成“mirGarden”

　　# sed -i "s/garden/mirGarden/g" 1.txt   //sed -i 很简单

　　2.2 将当前目录下的所有文件内的“garden”替换成“mirGarden”

　　## sed -i "s/garden/mirGarden/g" `ls` //其实也就是ls出多个文件名而已
