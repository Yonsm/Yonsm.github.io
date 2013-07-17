[Yonsm.NET](http://www.yonsm.net) 的博客

本博客运行于 [Jekyll](http://jekyllrb.com) @ [GitHub](http://github.com/Yonsm/NET)，博客模板修改自 [WebFrog](http://webfrogs.me/) 的博客。

***安装设置***
本博客模板已经全部通用化，使用极其简单：

1. [Fork](https://github.com/Yonsm/NET/fork) [http://github.com/Yonsm/NET](http://github.com/Yonsm/NET)。
2. 所有个人相关的配置都在 _config.yml 中，修改其中内容：

* markdown: rdiscount *（建议不修改）*
* permalink: /:title/ *固定链接（建议别修改）*
* url: http://yonsm.net *网站链接*
* name: Yonsm.NET *网站名*
* author: Yonsm *作者*
* qq: 123018 *QQ号(可选)*
* email: Yonsm@msn.com *电子邮件*
* duoshuo: yonsm *多说评论帐号*
* beian:  浙ICP备12026616号 *备案号(可选)*
* cnzz: 119959 *站长统计(可选)*
* weibo: 1885061391 *微博帐号*
* github: Yonsm *GitHub帐号*
* pygments: true *语法高亮（建议不修改）*
* safe: true *安全模式（建议不修改）*
* paginate: 20 *首页分页*
* truncate: 300 *首页文章摘要字数（省略则不显示摘要，摘要风格尚需进一步美化，建议不使用）*
* about: "这里是我的博客。" *关于介绍页面的内容*

3. 删除掉 _posts 目录下的所有文章，然后创建你的文章即可。

***导入 WordPress 的文章***

1. 安装 多说 插件来转移评论。
2. 安装 WP Slug 插件并批量编辑更新文章，以便生成英文的固定链接。
3. 可以使用 exitwp 导入文章。
4. 用文本编辑器批量替换所有导出文章中的 **wordpress_id:** 为 **thread:**。

分类、标签、评论都能完美迁移。

***使用说明***

* 点击 Powered by 里面的 **Po** 撰写新文章；点击 **ed** 编辑当前页面。
