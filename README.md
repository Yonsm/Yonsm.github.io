[Yonsm.NET](http://www.yonsm.net) 的博客

本博客运行于 [Jekyll](http://jekyllrb.com) @ [GitHub](http://github.com/Yonsm/NET)，博客模板修改自 [WebFrog](http://webfrogs.me/) 的博客。本博客模板已经全部通用化，使用极其简单。


## 安装

1. [Fork](https://github.com/Yonsm/NET/fork) [http://github.com/Yonsm/NET](http://github.com/Yonsm/NET)。

2. 所有个人相关的配置都在 _config.yml 中，修改其中内容：
  * markdown: rdiscount ***（建议不修改）***
  * permalink: /:title/ ***固定链接（建议别修改）***
	* url: http://yonsm.net ***网站链接***
	* name: Yonsm.NET ***网站名***
	* author: Yonsm ***作者***
	* qq: 123018 ***用于关于页面的QQ号(可选)***
	* email: Yonsm@msn.com ***电子邮件***
	* duoshuo: yonsm ***多说评论帐号***
	* beian:  浙ICP备12026616号 ***备案号(可选)***
	* cnzz: 119959 ***站长统计(可选)***
	* weibo: 1885061391 ***用于关于页面微博帐号***
	* github: Yonsm ***GitHub帐号***
	* pygments: true ***语法高亮（建议不修改）***
	* safe: true ***安全模式（建议不修改）***
	* paginate: 20 ***首页分页***
	* truncate: 300 ***首页文章摘要字数（省略则不显示摘要，摘要风格尚需进一步美化，建议不使用）***
	* about: "这里是我的博客。" ***关于介绍页面的内容***

3. 删除掉 _posts 目录下的所有文章，然后创建你的文章即可。

所有安装操作均可在浏览器中线操作，不需要在本地做任何额外工作。

## 迁移

**如果你不需要迁移，请跳过此步骤**

如果你之前在使用 WordPress，可以非常完美地导入到此博客中，分类、标签、评论都能完美迁移。

1. 安装 多说 插件来转移评论。
2. 安装 WP Slug 插件并批量编辑更新文章，以便生成英文的固定链接。
3. 可以使用 exitwp 导入文章。
4. 用文本编辑器批量替换所有导出文章中的 **wordpress_id:** 为 **thread:**，以便关联文章和多说评论。
5. 如果以前的 WordPress 固定链接是 **/post/123** 这种格式，迁移后链接依然能正常工作（实际上是 404 页面做了转跳处理）。

迁移需要在本地座比较多的准备工作，详细步骤略过，请仔细操作。

## 使用

* 点击 Powered by 里面的 **Po** 撰写新文章；点击 **ed** 编辑当前页面。
* 虽然可以用在线的编辑器来编辑和发布文章，但为了批量修改方便，还是推荐 Check Out 后修改。

Yonsm

2013-07-17
