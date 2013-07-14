---
author: Yonsm
comments: true
date: 2004-10-09 04:40:42+00:00
layout: post
slug: reposted-based-on-mmx-instruction-set-programming
title: '[转载]基于MMX指令集的程序设计'
wordpress_id: 156
categories:
- 文档
---

**一、MMX技术简介**

　　Intel 公司的MMX（多媒体增强指令集）技术可以大大提高应用程序对二维三维图形和图象的处理能力。Intel MMX技术可用于对大量数据和复杂数组进行的复杂处理，使用MMX技术可处理的数据基本单位可以是字节（byte）、字（word），或者是双字（double-word）。

　　Visual Studio .NET 2003提供了对MMX指令集特性的支持，从而可以不必编写汇编代码，直接使用C++代码就可以实现MMX指令的功能。通过参考Intel软件说明书（Intel Software manuals）[1]以及阅读MSDN中有关MMX编程技术的主题会使你更好地把握MMX编程的要点。

<!-- more -->　　MMX技术实现了单道指令多道数据流（SIMD，single-instruction, multiple-data）的执行模式。考虑下面一个需要编程完成的任务，在一个字节（BYTE）数组中使其中每一个元素加上一个数，在传统的程序中，实现这个功能的算法如下：
    
    for each b in array // 对数组中的每一个元素b<br></br>{<br></br>	b = b + n; // 加上一个数n<br></br>}<br></br>

　　下面看看它的实现细节：
    
    for each b in array // 对数组中的每一个元素b<br></br>{<br></br>	把b加载到寄存器中<br></br>	把此寄存器中的数加上n<br></br>	把所得寄存器中的结果放回内存<br></br>}<br></br>

　　具有MMX指令集支持的处理器有八个64位的寄存器，每一个寄存器可以存放8个字节（byte）、4个字(word)或2个双字(double-word)。MMX技术同时提供了一个MMX指令集，其中的指令可以可以把一个数值（其类型可以是字节、字或双字）加载到这些MMX寄存器中，在寄存器中进行算术或逻辑运算，然后把寄存器中的结果放回内存存储单元。上面的例子采用MMX技术后的算法是这样的：
    
    for each 8 members in array //把数组中的8个字节（其中一个字节为数组中的一个单位）作为一组取出<br></br>{<br></br>	把这8个字节加载到MMX寄存器中<br></br>	通过一个CPU指令执行周期把这个寄存器中的8个字节都加上n<br></br>	把寄存器中计算的结果写回内存<br></br>}<br></br>

　　C++编程人员不必直接使用MMX指令集中的指令访问这些MMX寄存器。你可以使用64位的数据类型__m64和一系列C++函数来进行相关的算术和逻辑运算。而决定程序使用哪个MMX寄存器以及代码优化是C++编译器的任务。

　　Visual C++ MMXSwarm [4]是MSDN中提供的一个很好的使用MMX技术进行图象处理的例子，它包含了一些封装好了的类简化了使用MMX技术的操作，并向你展示了对各种不同格式图象进行处理的操作（如单色24位象素RGB、32位象素RGB等）。本文只是对使用Visual C++实现MMX程序设计的简单介绍。如果你感兴趣的话，可以参看MSDN上MMXSwarm的例子。

**二、MMX程序设计详细介绍**

**1.包含的头文件**

　　所有的MMX指令集函数在emmintrin.h文件中定义：
    
    #include <emmintrin.h></emmintrin.h><br></br>

　　因为程序中用到的MMX处理器指令是由编译器决定，所以它并没有相关的.lib库文件。

**2.__m64 数据类型**

　　这种类型的变量可用作MMX指令的操作数，它不能被直接访问。_m64类型的变量被自动分配为8个字节的字长。

**3.CPU对MMX指令集的支持**

　　如果你的CPU能够具有了MMX指令集，你就可以使用Visual Studio .NET 2003提供的对MMX指令集支持的C++函数库了，你可以查看MSDN中的一个Visual C++ CPUID[3]的例子，它可以帮你检测你的CPU是否支持SSE、MMX指令集或其它的CPU功能。

**4.饱和算法（Saturation Arithmetic）和封装模式（Wraparound Mode）**

　　MMX技术支持一种叫做saturating arithmetic（饱和算法）的计算模式。在饱和模式下，当计算结果发生溢出（上溢或下溢）时，CPU会自动去掉溢出的部分，使计算结果取该数据类型表示数值的上限值（如果上溢）或下限值（如果下溢）。饱和模式的计算用于对图象的处理。

　　下面的例子能够让你理解饱和模式和封装模式的区别。如果一个字节(BYTE)类型变量的值为255，然后将其值加一。在封装模式下，相加结果为0（去掉进位）；在饱和模式下，结果为255。饱和模式用类似的方法来处理下溢出，比如对于一个字节数据类型的数在饱和模式下，1减2的结果为0（而不是-1）。每一个MMX算术指令都有这两种模式：饱和模式和封装模式。本文所要讨论的项目只使用饱和模式下的MMX指令。

**三、MMX8 演示项目**

　　MMX8是一个单文档界面（SDI）的应用程序，用来对每象素8位的单色位图进行简单处理。源图象和处理后的图象会在窗体中显示出来。新建的ATL（活动模版库）类 Cimage用来从资源中提取图象并在窗体中显示出来。程序要对图象进行两种处理操作：图象颜色反相和改变图象的亮度。每一种处理操作可以用下面几种方法之中其中的一种来实现：

  * 纯C++代码；
  * 使用C++的MMX功能函数的代码；
  * 使用MMX汇编指令的代码。

　　对图象进行处理计算的时间会显示在状态栏中。

　　用纯C++实现的图象颜色反相函数：
    
    void CImg8Operations::InvertImageCPlusPlus(BYTE* pSource, BYTE* pDest, int nNumberOfPixels)<br></br>{<br></br>	for ( int i = 0; i < nNumberOfPixels; i++ )<br></br>	{<br></br>		*pDest++ = 255 - *pSource++;<br></br>	}<br></br>}<br></br>

　　为了查询使用C++ MMX指令函数的方法，需要参考Intel软件说明书（Intel Software manuals）中有关MMX汇编指令的说明，首先我是在第一卷的第八章找到了MMX相关指令的大体介绍，然后在第二卷找到了有关这些MMX指令的详细说明，这些说明有一部分涉及了与其特性相关的C++函数。然后我通过这些MMX指令对应的C++函数查找了MSDN中与其相关的说明。在MMX8示例程序中用到的MMX指令和相关的C++函数见下表：

**实现的功能**
**对应的MMX汇编指令**
**Visual C++.NET中的MMX函数**

清除MMX寄存器中的内容，即初始化（以避免和浮点数操作发生冲突）
emms
_mm_empty

将两个64位数中对应的（8个）无符号（8位）字节同时进行减法操作
psubusb
_mm_subs_pu8

将两个64位数中对应的（8个）无符号（8位）字节同时进行加法操作
paddusb
_mm_adds_pu8

　　用Visual C++.NET的MMX指令函数实现图象颜色反相的函数：
    
    void CImg8Operations::InvertImageC_MMX(BYTE* pSource, BYTE* pDe
    st, int nNumberOfPixels)<br></br>{<br></br>	__int64 i = 0;<br></br>	i = ~i; // 0xffffffffffffffff<br></br>	int nLoop = nNumberOfPixels/8;	// 每次循环处理8个象素<br></br>	__m64* pIn = (__m64*) pSource;	// 输入的字节数组指针<br></br>	__m64* pOut = (__m64*) pDest;	// 输出的字节数组指针<br></br>	__m64 tmp;		// 临时工作变量<br></br>	_mm_empty();	// 执行MMX指令：emms，初始化MMX寄存器<br></br>	__m64 n1 = Get_m64(i);<br></br>	for ( int i = 0; i < nLoop; i++ )<br></br>	{<br></br>		tmp = _mm_subs_pu8 (n1 , *pIn); // 饱和模式下的无符号减法，对每一个字节执行操作：tmp = n1 - *pIn<br></br>		*pOut = tmp;<br></br>		pIn++; // 取下面的8个象素点<br></br>		pOut++;<br></br>	}<br></br>	_mm_empty(); // 执行MMX指令：emms，清除MMX寄存器中的内容<br></br>}<br></br>__m64 CImg8Operations::Get_m64(__int64 n)<br></br>{<br></br>	union __m64__m64<br></br>	{<br></br>		__m64 m;<br></br>		__int64 i;<br></br>	} mi;<br></br>	mi.i = n;<br></br>	return mi.m;<br></br>}<br></br>

　　虽然这个函数在非常短的时间就执行完成了，但我记录了这3种方法需要的时间，以下是在我的计算机上运行的结果：　　

  * 纯C++代码 43毫秒
  * 使用C++的MMX指令函数的代码 26毫秒
  * 使用MMX汇编指令的代码 26毫秒

　　上面的图象处理时间必须在程序Release优化编译后执行时才能体现出很好的效果。

　　而改变图象的亮度我采用了最简单的方法：对图象中的每一个象素的颜色值进行加减运算。相对前面的处理函数而言，这样的转换函数有些复杂，因为我们需要把处理过程分成两种情况，一种是增加象素颜色值，另一种是减少象素颜色值。

　　用纯C++函数实现的改变图象亮度的函数：
    
    void CImg8Operations::ChangeBrightnessCPlusPlus(BYTE* pSource, BYTE* pDest, int nNumberOfPixels, int nChange)<br></br>{<br></br>	if ( nChange > 255 )<br></br>		nChange = 255;<br></br>	else if ( nChange < -255 )<br></br>		nChange = -255;<br></br>	BYTE b = (BYTE) abs(nChange);<br></br>	int i, n;<br></br>	if ( nChange > 0 ) //增加象素颜色值<br></br>	{<br></br>		for ( i = 0; i < nNumberOfPixels; i++ )<br></br>		{<br></br>			n = (int)(*pSource++ + b);<br></br>			if ( n > 255 )<br></br>				n = 255;<br></br>			*pDest++ = (BYTE) n;<br></br>		}<br></br>	}<br></br>	else //减少象素颜色值<br></br>	{<br></br>		for ( i = 0; i < nNumberOfPixels; i++ )<br></br>		{<br></br>			n = (int)(*pSource++ - b);<br></br>			if ( n < 0 )<br></br>				n = 0;<br></br>			*pDest++ = (BYTE) n;<br></br>		}<br></br>	}<br></br>}<br></br>

　　用Visual C++.NET的MMX指令函数实现的改变图象亮度函数：
    
    void CImg8Operations::ChangeBrightnessC_MMX(BYTE* pSource, BYTE* pDest, int nNumberOfPixels, int nChange)<br></br>{<br></br>	if ( nChange > 255 )<br></br>		nChange = 255;<br></br>	else if ( nChange < -255 )<br></br>		nChange = -255;<br></br>	BYTE b = (BYTE) abs(nChange);<br></br>	__int64 c = b;<br></br>	for ( int i = 1; i <= 7; i++ )<br></br>	{<br></br>		c = c << 8;<br></br>		c |= b;<br></br>	}<br></br>	int nNumberOfLoops = nNumberOfPixels / 8; // 在一次循环中处理8个象素<br></br>	__m64* pIn = (__m64*) pSource;	// 输入的字节数组<br></br>	__m64* pOut = (__m64*) pDest;	// 输出的字节数组<br></br>	__m64 tmp;		// 临时工作变量<br></br>	_mm_empty();	// 执行MMX指令：emms<br></br>	__m64 nChange64 = Get_m64(c);<br></br>	if ( nChange > 0 )<br></br>	{<br></br>		for ( i = 0; i < nNumberOfLoops; i++ )<br></br>		{<br></br>			tmp = _mm_adds_pu8(*pIn, nChange64); // 饱和模式下的无符号加法，对每一个字节执行操作：tmp = *pIn + nChange64<br></br>			*pOut = tmp;<br></br>			pIn++; // 取下面8个象素<br></br>			pOut++;<br></br>		}<br></br>	}<br></br>	else<br></br>	{<br></br>		for ( i = 0; i < nNumberOfLoops; i++ )<br></br>		{<br></br>			tmp = _mm_subs_pu8(*pIn, nChange64); // 饱和模式下的无符号减法，对每一个字节执行操作：tmp = *pIn - nChange64<br></br>			*pOut = tmp;<br></br>			pIn++; // 取下面8个象素<br></br>			pOut++;<br></br>		}<br></br>	}<br></br>	_mm_empty(); // 执行MMX指令：emms<br></br>}<br></br>

　　注意参数nChange的符号每次调用函数时在循环体外只检查一次，而不是放在循环体内，那样会被检查成千上万次。下面是在我的计算机上处理图象花费的时间：　　

  * 纯C++代码 49毫秒
  * 使用C++的MMX指令函数的代码 26毫秒
  * 使用MMX汇编指令的代码 26毫秒

**四、MMX32 演示项目**

　　MMX32项目可对32位象素的RGB图象进行处理。进行的图象处理工作是图象颜色反相操作和更改图象颜色的平衡度（将象素点的每一种颜色乘以一定的值）操作。

　　MMX的乘法实现起来比加减法复杂得多，因为乘法运算通常得出的结果的位数不再是以前位数的大小。比如，如果乘法的操作数有一个字节（8位的BYTE）大小，那么结果会达到一个字（16位的WORD）大小。这需要额外的转换，并且使用MMX汇编指令和C++代码进行图象转换花费时间的差别不是很大（时间差为5-10%）。

　　用Visual C++.NET的MMX指令函数实现的更改图象颜色平衡度的函数：
    
    void CImg32Operations::ColorsC_MMX(BYTE* pSource, BYTE* pDest, int nNumberOfPixels, float fRedCoefficient, float fGreenCoefficient, float fBlueCoefficient)<br></br>{<br></br>	int nRed = (int)(fRedCoefficient * 256.0f);<br></br>	int nGreen = (int)(fGreenCoefficient * 256.0f);<br></br>	int nBlue = (int)(fBlueCoefficient * 256.0f);<br></br>	// 设置相乘系数<br></br>	__int64 c = 0;<br></br>	c = nRed;<br></br>	c = c << 16;<br></br>	c |= nGreen;<br></br>	c = c << 16;<br></br>	c |= nBlue;<br></br>	__m64 nNull = _m_from_int(0);	// null<br></br>	__m64 tmp = _m_from_int(0);		// 临时工作临时变量初始化<br></br>	_mm_empty(); // 清空MMX寄存器。<br></br>	__m64 nCoeff = Get_m64(c);<br></br>	DWORD* pIn = (DWORD*) pSource;	// 输入双字数组<br></br>	DWORD* pOut = (DWORD*) pDest;	// 输出双字数组<br></br>	for ( int i = 0; i < nNumberOfPixels; i++ )<br></br>	{<br></br>		tmp = _m_from_int(*pIn); // tmp = *pIn (在tmp的低32位写入数据)<br></br>		tmp = _mm_unpacklo_pi8(tmp, nNull ); //将tmp中低位的4个字节转化为字，字的高位用nNull中对应位上的位值填充。<br></br>		tmp = _mm_mullo_pi16 (tmp , nCoeff); //将tmp中的每一个字相乘，将相乘结果的高位送到nCoeff，在tmp中只保留每个结果的低位。<br></br>		tmp = _mm_srli_pi16 (tmp , 8); // 将tmp中的每一个字右移8位，相当于除以256<br></br>		tmp = _mm_packs_pu16 (tmp, nNull); // 使用饱和模式将tmp中的结果做如下处理：将tmp中的4个字转化为4个字节，并将这4个字节写到tmp中的低32位中。同时，将nNull中的4个字转化为4个字节，并将这4个字节写到tmp的高32位中。<br></br>		*pOut = _m_to_int(tmp); // *pOut = tmp (将tmp低32位的数据放入pOut数组中)<br></br>		pIn++;<br></br>		pOut++;<br></br>	}<br></br>	_mm_empty();<br></br>}<br></br>

　　你可以参看示例项目的源代码了解有关此项目的更多的细节。

**五、SSE2 技术**

　　SSE2技术包含有一个类似MMX中对整数操作的指令集，同时也包含128位的SSE寄存器组。比如，用SSE2技术实现更改图象颜色平衡度能够比用纯C++代码实现此功能在效率上有很大提升。SSE2同时是SSE技术的扩展，比如它不仅可以单精度浮点数数组，而且能够处理双精度浮点数数据类型的数组。用C++实现的MMXSwarm 示例项目不仅使用了MMX指令函数，而且使用了SSE2指令对整型数操作的函数。

**六、参考文档**

  1. Intel软件说明书（Intel Software manuals）：[http://developer.intel.com/design/archives/processors/mmx/index.htm](http://developer.intel.com/design/archives/processors/mmx/index.htm) 。
  2. MSDN中有
