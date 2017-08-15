YAAW
====

汉化修改版的 YAAW，添加转到离线下载网站的链接。

Yet Another Aria2 Web Frontend in pure HTML/CSS/Javascirpt.

No HTTP server, backend or server-side program. All you need is just a browser.

<br />

Usage
-----
1. Run aria2 with RPC enabled
> `aria2c --enable-rpc --rpc-listen-all=true --rpc-allow-origin-all`
> with 'JSON-RPC PATH' like `http://hostname:port/jsonrpc`
>
> Recommend: Set `--rpc-secret=<secret>` if you are using aria2 1.18.4(or higher) with 'JSON-RPC PATH' like `http://token:secret@hostname:port/jsonrpc`
>
> Set `--rpc-user=<username>` `--rpc-passwd=<passwd>` if you are using aria2 1.15.2(or higher) with 'JSON-RPC PATH' like `http://username:passwd@hostname:port/jsonrpc`

2. Visit **index.html**.

3. Change "JSON-RPC Path" setting if "Internal server error" occurred.

4. Yonsm's startup script for aria2c:
#!/bin/sh

case "$1" in
	start)
		echo "Starting aria2c daemon..."
		if [ ! -r /opt/etc/aria.task ]; then touch /opt/etc/aria.task; fi
		/opt/bin/aria2c --dir=/shares/Media/Downloads --file-allocation=falloc --event-poll=select --disable-ipv6 --enable-rpc --rpc-listen-port=6800 --rpc-listen-all --rpc-listen-all=true --rpc-allow-origin-all=true --max-concurrent-downloads=5 --max-connection-per-server=5 --continue=true --save-session=/opt/etc/aria.task --input-file=/opt/etc/aria.task --rpc-user=admin --rpc-passwd=asdf --daemon=true
		;;
	stop)
		echo "Shutting down aria2c daemon..."
		killall aria2c
		;;
	restart)
		$0 stop
		sleep 2
		$0 start
		;;
	*)
		echo $"Usage: $0 {start|stop|restart}"
esac

5. Yonsm's modification for yaaw: you can specify your rpc url on location search, e.g.
http://hdweb.googlecode.com/svn/MBL/opt/share/yaaw/index.html?http://192.168.1.1:6800/jsonrpcs


Tips
----
* All your settings on web is temporary. **Settings will be lost after aria2 restarted.**
* Tasks(including which is not finished) will be lost after aria2 restarted. Using `--save-session=SOME/WHERE` and reload with `--continue=true --input-file=SOME/WHERE` to continue.
* Using `$HOME/.aria2/aria2.conf` to save your options.
* For more infomations about aria2, visit [Aria2 Manual](http://aria2.sourceforge.net/manual/en/html/)
* YAAW also support websocket! Set JSON-RPC PATH with `ws://hostname:port/jsonrpc`.
* Pre-spicify or save JSON-PRC PATH as bookmark with `http://binux.github.io/yaaw/demo/#path=http://hostname:port/jsonrpc`

Components
----------
+ [Bootstrap](http://twitter.github.com/bootstrap/)
+ [mustache.js](https://github.com/janl/mustache.js)
+ [jQuery](http://jquery.com/)
+ [jQuery Storage](http://archive.plugins.jquery.com/project/html5Storage)
+ [JSON RPC 2.0 jQuery Plugin](https://github.com/datagraph/jquery-jsonrpc)

License
-------
yaaw is licensed under GNU Lesser General Public License.
You may get a copy of the GNU Lesser General Public License from http://www.gnu.org/licenses/lgpl.txt

favicon.ico by [fangke](http://fangke.im/)
