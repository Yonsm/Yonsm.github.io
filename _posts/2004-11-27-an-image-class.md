---
date: 2004-11-27 07:43:01+00:00
layout: post
title: 一个图像类
thread: 101
categories: 代码
---

下载: [CImage](/assets/1101483036.rar) (6 KB)

  


不是 MS 的 CImage：）功能不多，仅仅是为了 CuteFoto 够用而已。为图像处理方便，内部数据格式为 DIB 24。

<!-- more -->  


支持以下功能:

  


  * 打开 BMP/GIF/JPG 文件。
  * 显示图图像。
  * 保存或局部保存为 BMP 24。
  * 支持一次 Undo 操作。

支持以下图像处理:

  


  * 缩放图像。
  * 翻转图像。
  * 旋转图像。
  * 去色。
  * 曝光。
  * 浮雕。
  * 颜色调整。
  * 边缘检测。

// CImage 类声明  
class CImage  
{  
protected:  
   // 成员变量  
   UINT m_uWidth;                  // 图像宽度  
   UINT m_uHeight;                 // 图像高度  
   PBYTE m_pbBits;                 // 图像数据指针  
   DOUBLE m_dScale;                // 用于绘制图像的缩放系数

  


   UINT m_uBackupWidth;            // 备份图像宽度  
   UINT m_uBackupHeight;           // 备份图像高度  
   PBYTE m_pbBackupBits;           // 备份图像数据指针

  


   TCHAR m_tzFileName[MAX_PATH];   // 当前图像文件名称

  


public:  
   // 构造函数  
   CImage();  
     
   // 析构函数  
   virtual inline CImage::~CImage();  
     
   // 获取图像宽度  
   inline UINT GetWidth();

  


   // 获取图像高度  
   inline UINT GetHeight();

  


   // 获取绘制宽度  
   inline UINT GetScaleWidth();

  


   // 获取图像高度  
   inline UINT GetScaleHeight();

  


   // 获取用于绘制图像的缩放系数  
   inline DOUBLE GetScale();

  


   // 获取用于绘制图像的缩放系数  
   inline VOID SetScale(DOUBLE dScale = 1);

  


   // 获取当前图像的文件名，返回值指向文件名缓冲区指针，允许被更改  
   inline PTSTR GetFileName();

  


   // 获取一行图像所占的字节数  
   inline UINT GetPitch();

  


   // 获取图像所占的字节数  
   inline UINT GetSize();

  


   // 获取第 y 行的图像数据指针  
   inline PBYTE GetBits();

  


   // 获取第 y 行的图像数据指针  
   inline PBYTE GetBits(UINT y);

  


   // 获取第 (x, y) 点的图像数据指针  
   inline PBYTE GetBits(UINT x, UINT y);

  


   // 获取 BITMAPINFOHEADER 信息  
   inline VOID GetBih(PBITMAPINFOHEADER pbihInfo);

  


   // 创建图像。返回 TRUE 表示成功，将更新图像数据；返回 FALSE 表示失败，原有图像数据不会被更改  
   inline BOOL Create(UINT uWidth, UINT uHeight, const PBYTE pbBits = NULL);

  


   // 附加图像。返回 TRUE 表示成功，将更新图像数据；返回 FALSE 表示失败，原有图像数据不会被更改  
   inline BOOL Attach(UINT uWidth, UINT uHeight, PBYTE pbBits);

  


   // 销毁图像数据  
   inline VOID Destroy();

  


   // 获取备份图像宽度  
   inline UINT GetBackupWidth();

  


   // 获取备份图像高度  
   inline UINT GetBackupHeight();

  


   // 获取备份图像数据  
   inline PBYTE GetBackupBits();

  


   // 备份图像数据  
   inline VOID Backup();

  


   // 恢复图像数据  
   inline VOID Restore();

  


   // 销毁备份图像数据  
   inline VOID DestroyBackup();

  


   // 读取、保存及绘制图像  
   BOOL Load(PCTSTR ptzFileName);  
   BOOL Save(PCTSTR ptzFileName, LPCRECT prtRect = NULL);  
   VOID Draw(HDC hDC, INT iLeft = 0, INT iTop = 0);

  


   // 图像变换  
   VOID Stretch(UINT uWidth, UINT uHeight);  
   VOID FlipHorizon();  
   VOID FlipVertical();  
   VOID Rotate(UINT uAngle, COLORREF crColor = 0x00FFFFFF);

  


   // 图像处理  
   VOID Decolourize();  
   VOID Expose(BYTE bValue = 128);  
   VOID Emboss();  
   VOID Adjust(INT iRed, INT iGreen, INT iBlue);

  


   // 边缘检测  
   VOID Fringe(BYTE bValue = 64);  
};

  
  

