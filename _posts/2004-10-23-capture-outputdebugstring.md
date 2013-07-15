---
date: 2004-10-23 09:03:15+00:00
layout: post
title: 捕捉 OutputDebugString 输出的字符串
thread: 135
categories: 文档
---

在调试状态下，VC 等调试器可以捕捉程序中的 OutputDebugString 输出的信息。其实 OutputDebugString 就是往一片共享影射的内存中写入了一段数据，并创建了两个 Enevt，指明数据写入事件被触发。在非调试状态下，我们也可以通过编程实现捕捉 OutputDebugString 的输出。下面的代码演示了如何获取这些信息:<!-- more -->
    
    DWORD WINAPI CDebugTrack::TrackProc(PVOID pvParam)<br></br>{<br></br>	HANDLE hMapping = NULL;<br></br>	HANDLE hAckEvent = NULL;<br></br>	PDEBUGBUFFER pdbBuffer = NULL;<br></br>	TCHAR tzBuffer[MAX_DebugBuffer];<br></br><br></br>	_Try<br></br>	{<br></br>		// 设置初始结果<br></br>		m_dwResult = ERROR_INVALID_HANDLE;<br></br><br></br>		// 打开事件句柄<br></br>		hAckEvent = CreateEvent(NULL, FALSE, FALSE, TEXT("DBWIN_BUFFER_READY"));<br></br>		_LeaveIf(hAckEvent == NULL);<br></br><br></br>		m_hReadyEvent = CreateEvent(NULL, FALSE, FALSE, TEXT("DBWIN_DATA_READY"));<br></br>		_LeaveIf(m_hReadyEvent == NULL);<br></br><br></br>		// 创建文件映射<br></br>		hMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, MAX_DebugBuffer, TEXT("DBWIN_BUFFER"));<br></br>		_LeaveIf(hMapping == NULL);<br></br><br></br>		// 映射调试缓冲区<br></br>		pdbBuffer = (PDEBUGBUFFER) MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);<br></br>		_LeaveIf(pdbBuffer == NULL);<br></br><br></br>		// 循环<br></br>		for (m_dwResult = ERROR_SIGNAL_PENDING; (m_dwResult == ERROR_SIGNAL_PENDING); )<br></br>		{<br></br>			// 等待缓冲区数据<br></br>			SetEvent(hAckEvent);<br></br>			if (WaitForSingleObject(m_hReadyEvent, INFINITE) == WAIT_OBJECT_0)<br></br>			{<br></br>				// 如果是继续等待，否则表示主线程发出了停止信号，退出当前线程<br></br>				if (m_dwResult == ERROR_SIGNAL_PENDING)<br></br>				{<br></br>					// 添加新项<br></br>					_AStrToStr(tzBuffer, pdbBuffer->szString);<br></br>					CListView::AddDebugItem(tzBuffer, pdbBuffer->dwProcessId);<br></br>				}<br></br>			}<br></br>			else<br></br>			{<br></br>				// 等待失败<br></br>				m_dwResult = WAIT_ABANDONED;<br></br>			}<br></br>		}<br></br>	}<br></br>	_Finally<br></br>	{<br></br>		// 释放<br></br>		if (pdbBuffer)<br></br>		{<br></br>			UnmapViewOfFile(pdbBuffer);<br></br>		}<br></br><br></br>		_SafeCloseHandle(hMapping);<br></br>		_SafeCloseHandle(m_hReadyEvent);<br></br>		_SafeCloseHandle(hAckEvent);<br></br><br></br>		PostMessage(CMainWnd::m_hWnd, WM_COMMAND, IDC_DebugTrack, m_dwResult);<br></br><br></br>		// 返回结果<br></br>		return m_dwResult;<br></br>	}<br></br>}

[软件]->[DebugTrack] 下有个 [DebugTrack](http://yonsm.reg365.com/index.php?job=art&articleid=a_20041003_184430) 工具，可以非常方便地捕捉和处理 OutputDebugString 的输出，实乃程序员居家旅行、杀人灭口，必备良药……，

当然，你也可以选择 [Sysinternals](http://www.sysinternals.com/) 的 [DebugView](http://www.sysinternals.com/ntw2k/freeware/debugview.shtml)，功能更强大(可以远程监视、可以监视内核输出)，不过没有 DebugTrack 用起来方便。

有关 OutputDebugString 的深入分析，可以参看这篇文章: 请查看文章 (E文): [http://www.unixwiz.net/techtips/outputdebugstring.html](http://www.unixwiz.net/techtips/outputdebugstring.html)
