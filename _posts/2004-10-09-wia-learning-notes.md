---
date: 2004-10-09 04:56:47+00:00
layout: post
title: WIA 学习笔记
thread: 155
categories: 文档
---

**一、 WIA 简介**  
**1．关于 WIA  
**WIA 是 Windows Image Acquisition 的简称，当前可用版本是 WIA 1.0，它是 Windows Millennium Edition (Windows Me) 或者更高版本的 Windows 系统中提供的数字图像获取服务，同时它也能用于管理数字图像设备。<!-- more -->

  


WIA 接口既是应用程序接口（WIA API），又是设备驱动程序接口（WIA DDI），下面要讲述的都是有关 WIA API 的内容。

  


通过 WIA API，应用程序可以：

  


  * 运行在强壮稳定的环境中；
  * 最大可能地减少协同配合问题；
  * 枚举可用的图像获取设备；
  * 同时连接多个设备；
  * 用标准的、可扩展的方式查询设备属性；
  * 用标准的、高性能的传送机制获取数据；
  * 在数据传送过程中维持图像属性；
  * 获取大量的设备事件通知消息。

**2．WIA 架构  
**WIA 是使用进程外（Out of process）服务实现的 COM 组件，和大多数进程外服务程序不同的是，WIA 通过提供自己的数据传送机制（IWiaDataTransfer 接口），避免了图像数据传送过程中的性能损失。高性能的 IWiaDataTransfer 接口使用共享内存来传送数据给客户程序。

  


WIA 有三个主要的组件：Device Manager，Minidriver Service Library 和 Device Minidriver。

  


  * Device Manager: 枚举图像设备，获取设备属，为设备建立事件和创建设备对象；
  * Minidriver Service Library: 执行所有设备无关的服务；
  * Device Minidriver 解释映射: WIA 属性和命令到特定的设备。

**二、 使用WIA**  
**1．选择设备**  
应用程序既可以用 WIA 内置的对话框来选择设备，也可以不使用 WIA 的用户界面。下面的程序将弹出一个 WIA 选择设备对话框：

  

    
    #include  #pragma comment (lib, "WiaGuid.lib")  int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {     HRESULT hResult;     IWiaItem *pItemRoot;     IWiaDevMgr *pWiaDevMgr;      CoInitialize(NULL);      __try     {         // Create WIA Device Manager instance         pWiaDevMgr = NULL;         hResult = CoCreateInstance(CLSID_WiaDevMgr, NULL, CLSCTX_LOCAL_SERVER, IID_IWiaDevMgr, (void**) &pWiaDevMgr);         if (hResult != S_OK)         {             MessageBox(NULL, "Error: CoCreateInstance().", NULL, MB_ICONSTOP);             __leave;         }          // Display a WIA select device dialog         pItemRoot = NULL;         hResult = pWiaDevMgr->SelectDeviceDlg(NULL, 0, WIA_SELECT_DEVICE_NODEFAULT, NULL, &pItemRoot);          // User canceled         if (hResult == S_FALSE)         {             MessageBox(NULL, "User canceled.", NULL, MB_ICONINFORMATION);             __leave;         }         // No device available         else if (hResult == WIA_S_NO_DEVICE_AVAILABLE)         {             MessageBox(NULL, "No device available.", NULL, MB_ICONINFORMATION);             __leave;         }          // OK, Then ..........      }     __finally     {         // Release COM interface.         if (pItemRoot)             pItemRoot->Release();          if (pWiaDevMgr)             pWiaDevMgr->Release();          CoUninitialize();     }     return 0; }

**2．获取图像到文件中  
**WIA 获取图像非常简单，直接调用 IWiaDevMgr::GetImageDlg()，它集成了 Select Device 和 Select Image 对话框，在传送图像的时候还会自动出现一个进度指示对话框，下面是一个例子：

  

    
    // ... // Create WIA Device Manager object. hResult = CoCreateInstance(CLSID_WiaDevMgr, NULL, CLSCTX_LOCAL_SERVER, IID_IWiaDevMgr, (void**) &pWiaDevMgr); if (hResult == S_OK) {     // Get a image.     hResult = pWiaDevMgr->GetImageDlg(hWnd, 0, WIA_DEVICE_DIALOG_SINGLE_IMAGE, WIA_INTENT_MAXIMIZE_QUALITY, NULL, wszFilename, &guidFormat);     // ...... } // ...... 

不过由于 IWiaDevMgr::GetImageDlg() 是以图片文件的形式返回数据的，有的时候并不能满足我们的需要，这时候我们就需要使用 IWiaDataTransfer 接口来传送图片。

  


**3．获取内存中的图像数据**  
在 IWiaDevMgr::SelectDeviceDlg() 之后，可以用它返回的 RootItem 对象的 IWiaItem::DeviceDlg() 方法显示一个对话框浏览 WIA 设备中图片，请看下面的例子：

  

    
    // ...... // Display a WIA dialog box to the user to prepare for image acquisition. hResult = pRootItem->DeviceDlg(hWnd, 0, WIA_INTENT_MAXIMIZE_QUALITY, &cItem, &ppWiaItems); if (hResult == S_OK) {     for (i = 0; i < cItem; i++)     {         // ......         // ppWiaItems<i>     } } // ...... 

IWiaItem::DeviceDlg() 返回选取的图片总数和每个图片的 WiaItem 指针，我们可以用用 IWiaDataTransfer 接口来传送图片。在传送每个 WiaItem 数据之前，应该先调用 IID_IWiaPropertyStorage 接口设置相应的属性：

  

    
    // ...... // Get the IWiaPropertyStorage interface so we can set required properties. hResult = pWiaItem->QueryInterface(IID_IWiaPropertyStorage, (void**) &pWiaPropertyStorage); if (hResult == S_OK) {     // Prepare PROPSPECs and PROPVARIANTs for setting the media type and format.     psPropSpec[0].ulKind = PRSPEC_PROPID;     psPropSpec[0].propid = WIA_IPA_FORMAT;     psPropSpec[1].ulKind = PRSPEC_PROPID;     psPropSpec[1].propid = WIA_IPA_TYMED;      guidOutputFormat = WiaImgFmt_MEMORYBMP;     pvPropVariant[0].vt = VT_CLSID;     pvPropVariant[0].puuid = &guidOutputFormat;     pvPropVariant[1].vt = VT_I4;     pvPropVariant[1].lVal = TYMED_CALLBACK;      // Set the properties.     hResult = pWiaPropertyStorage->WriteMultiple(sizeof(pvPropVariant) / sizeof(pvPropVariant[0]), psPropSpec, pvPropVariant, WIA_IPA_FIRST);      // ...... } // ......

如果用 IWiaDataTransfer 接口传送数据，我们还需要自己写代码实现 IWiaDataCallback 接口，其中 在我们的 IWiaDataCallback::BandedDataCallback() 中可以接收到数据，例如：

  

    
    // [Summary] Recieve data transfer status notifications. HRESULT CALLBACK CWiaDataCallback::BandedDataCallback(LONG lMessage, LONG lStatus, LONG lPercentComplete, LONG lOffset, LONG lLength, LONG lReserved, LONG lResLength, BYTE *pbData) {     PWIA_DATA_CALLBACK_HEADER pHeader = NULL;      switch (lMessage) &nbs;
    p;   {     case IT_MSG_DATA_HEADER:     // The data header contains the image's final size.         pHeader = (PWIA_DATA_CALLBACK_HEADER) pbData;         if ((pHeader) && (pHeader->lBufferSize))         {             // Save the buffer size.             m_nBufferLength = pHeader->lBufferSize;              // Allocate a block of memory to hold the image.             m_pBuffer = (PBYTE) HeapAlloc(GetProcessHeap(), 0, m_nBufferLength);             if (m_pBuffer == NULL)                 return S_FALSE;         }         break;      case IT_MSG_DATA:         // Make sure a block of memory has been created.         if (m_pBuffer)         {             // Copy the new band.             CopyMemory(m_pBuffer + lOffset, pbData, lLength);              // Increment the counter.             m_nBytesTransfered += lLength;         }         break;      case IT_MSG_TERMINATION:         // Notify that we complete to recive a image.         break;      default:         break;     }      return S_OK; }

然后，我们就可以用 IWiaDataTransfer 接口来传送数据了：

  

    
    // ... // Create our callback class. pCallback = new CWiaDataCallback(hWnd); if (pCallback) {     // Get the IWiaDataCallback interface from our callback class.     hResult = pCallback->QueryInterface(IID_IWiaDataCallback, (void**) &pWiaDataCallback);     if (hResult == S_OK)     {         // Perform the transfer.         wdtiTransferInfo.ulSize = sizeof(WIA_DATA_TRANSFER_INFO);         hResult = pWiaDataTransfer->idtGetBandedData(&wdtiTransferInfo, pWiaDataCallback);         // ......     }     // ...... } // ...... 

**三、后话**

  


WIA 是 Windows ME 及其以后的操作系统中提供的，Windows 98/2000 均不支持 WIA，因此需要在较新版本的 MSDN Library 中才有 WIA 文档。WIA 1.0 在 MSDN 的文档地址是：[http://msdn.microsoft.com/library/default.asp?url=/library/en-us/wia/wia/overviews/startpage.asp](http://msdn.microsoft.com/library/default.asp?url=/library/en-us/wia/wia/overviews/startpage.asp)，或者按目录：MSDN Library -> 图形和多媒体 -> Windows 图像获取 -> WIA 1.0。

  


另外，因为 Visual C++ 6.0 中没有 WIA 库，所以需要使用 Visual Studio.NET 2002/2003 编译 WIA 程序。  


  

