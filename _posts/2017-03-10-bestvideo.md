---
date: 2017-03-10 10:46:31+00:00
layout: post
title: BestVideo - ffmpeg 转码脚本 for macOS & Windows 
categories: 资源
tags: 资源
---


ffmpeg 是全能的多媒体文件转码工具，也是很多 GUI 类转码软件的后端，但实际用下来这些 GUI 转码软件经常达不到各种定制化的要求，最终还是人肉敲命令行用的靠谱。但是每次敲命令行，各种参数记不住、复杂、累。做成批量的脚本，用起来比较舒服，还可方便普通用户，一键双击批量转码。在此基础上，还能基于 macOS bash shell 和 Windows batch 脚本，做到了简单的 srt/ass 脚本编码检测并混合硬字幕功能，不妨一看：

# 功能：
1. 批量处理指定目录、当前目录、脚本目录下的 mp4|mkv|mov|avi|wmv|vob 文件（其它扩展名自行编辑添加）；
2. 处理指定文件名；
3. 混合同文件名名 srt/ass 字幕（自动检测 UTF 编码，默认 GB18030 编码）；

# 使用步骤：
1. 下载附件，解压缩；
2. （可选）修改 BestVideo.cmd 或 BestVide.sh 中的相关参数（主要是目标宽度和高度，以及其它更进一步的定制化参数修改）。
3. 把要转码的文件放在通 BestVideo.cmd 或 BestVide.sh 同一个目录；
4. （可选）如果需要硬编码字幕，确保 srt 和 ass 字幕文件和视频文件同名；
5. 双击 BestVideo.cmd （Windows）或 BestVide.sh (macOS，之前需确保 chmod +x BestVideo.sh 过)，等待转码完成；
6. 在 OUT 目录下可以找到同名视频文件。

# 下载
[下载 macOS 版](/assets/BestVideo_macOS.zip)

[下载 Windows 版](/assets/BestVideo_Win.zip)


# 脚本

macOS 版（在10.12.3测试通过）

```sh
#!/bin/sh

inTypes="mp4|mkv|mov|avi|wmv|vob"
outDir=OUT

videoWidth=720
videoHeight=338
videoLevel=3.1
videoProfile=main
videoConstantRateFactor=17

audioChannel=2
audioCodec=aac
audioBitRate=225k
audioSampleRate=44.1k

audioOptions="-acodec $audioCodec -ab $audioBitRate -ar $audioSampleRate -ac $audioChannel"
videoOptions="-s ${videoWidth}x$videoHeight -vcodec libx264 -crf $videoConstantRateFactor -profile:v $videoProfile -level $videoLevel"
cropOptions1="-vf crop=in_w:in_w*$videoHeight/$videoWidth"
cropOptions2="-vf crop=in_h*$videoWidth/$videoHeight:in_h"

CDIR=$(cd "${0%/*}"; pwd)
PATH=$CDIR:$PATH
pushd $PWD >/dev/null

if [ $# = 0 ]; then
	videoPath=.
else
	videoPath="$1"
fi

MakeVideo()
{
	if [ ! -d "$outDir" ]; then mkdir "$outDir"; fi

	subtitle="${1%.*}.ass"
	if [ ! -f "$subtitle" ]; then subtitle="${1%.*}.srt"; fi
	if [ -f "$subtitle" ]; then 
		detectedCharset=`file -b --mime-encoding "$subtitle"`
		if [[ "$detectedCharset" =~ "utf" ]]; then charsetOption=; else charsetOption=":charenc=GB18030"; fi
		echo "Subtitle: $subtitle"
		echo "Charset: $detectedCharset"
		ffmpeg -i "$1" -y $audioOptions $videoOptions $cropOptions1,subtitles="$subtitle"$charsetOption "$outDir/${1%.*}.mp4" </dev/null
		if [ $? == 1 ]; then
			ffmpeg -i "$1" -y $audioOptions $videoOptions $cropOptions2,subtitles="$subtitle"$charsetOption "$outDir/${1%.*}.mp4" </dev/null
		fi
	else
		ffmpeg -i "$1" -y $audioOptions $videoOptions $cropOptions1 "$outDir/${1%.*}.mp4" </dev/null
		if [ $? == 1 ]; then
			ffmpeg -i "$1" -y $audioOptions $videoOptions $cropOptions2 "$outDir/${1%.*}.mp4" </dev/null
		fi
	fi
}

if [ -d "$videoPath" ]; then
	cd "$videoPath"
	find -E . -iregex ".*\.($inTypes)" -maxdepth 1 | while read f ; do MakeVideo "${f##*/}" ; done
	if [ ! -d "$outDir" ]; then
		cd "$CDIR"
		find -E . -iregex ".*\.($inTypes)" -maxdepth 1 | while read f ; do MakeVideo "${f##*/}" ; done
		if [ ! -d "$outDir" ]; then
			echo "Usage: $0 [FILE|DIR|] - Empty means ./ or $CDIR"
		fi
	fi
else
	if [[ "${videoPath}" =~ "/" ]]; then cd "${videoPath%/*}"; fi
	MakeVideo "${videoPath##*/}"
fi

popd >/dev/null
```


Windows 版（在 Windows 7 下测试通过）

```bat
@ECHO OFF

SET inTypes=*.mp4 *.mkv *.mov *.avi *.wmv *.vob
SET outDir=OUT

SET videoWidth=720
SET videoHeight=338
SET videoLevel=3.1
SET videoProfile=main
SET videoConstantRateFactor=17

SET audioChannel=2
SET audioCodec=aac
SET audioBitRate=225k
SET audioSampleRate=44.1k

SET audioOptions=-acodec %audioCodec% -ab %audioBitRate% -ar %audioSampleRate% -ac %audioChannel%
SET videoOptions=-s %videoWidth%x%videoHeight% -vcodec libx264 -crf %videoConstantRateFactor% -profile:v %videoProfile% -level %videoLevel%
SET cropOptions1=-vf crop=in_w:in_w*%videoHeight%/%videoWidth%
SET cropOptions2=-vf crop=in_h*%videoWidth%/%videoHeight%:in_h

PATH=%PATH%;%~dp0
PUSHD %CD%

IF [%1]==[] (
	SET videoPath=.
) ELSE (
	SET videoPath=%1
)

IF EXIST %videoPath%\NUL (
	CD /d %videoPath%
	FOR %%I IN (%inTypes%) DO CALL :MakeVideo "%%~nxI"
) ELSE (
	CD /d %~dp1
	CALL :MakeVideo "%~nx1"
)

POPD
EXIT /b 0

:MakeVideo
	SET subtitleOptions=
	SET subtitle=%~n1.ass
	IF NOT EXIST "%subtitle%" SET subtitle=%~n1.srt
	IF NOT EXIST "%subtitle%" GOTO :endSubtitle
		SET charsetOption=
		CALL :DetectCharset "%subtitle%"
		IF NOT ERRORLEVEL 1 SET charsetOption=:charenc=GB18030
		SET subtitleOptions=",subtitles=%subtitle%:original_size=%videoWidth%x%videoHeight%%charsetOption%"
		ECHO.
		ECHO Subtitle: %subtitle%
		ECHO Charset: %detectedCharset%
	:endSubtitle

	IF NOT EXIST %outDir% MD %outDir%
	@ECHO ON
	ffmpeg -i %1 -y %audioOptions% %videoOptions% %cropOptions1%%subtitleOptions% "%outDir%\%~n1.mp4"
	IF %ERRORLEVEL% EQU 1 ffmpeg -i %1 -y %audioOptions% %videoOptions% %cropOptions2%%subtitleOptions% "%outDir%\%~n1.mp4"
	@ECHO OFF
EXIT /b 0

:DetectCharset
	SET hexFile=%~n1.hex
	CERTUTIL -f -encodehex %1 "%hexFile%" >NUL
	FOR /f "usebackq delims=" %%E IN ("%hexFile%") DO (
		SET "firstLine=%%E" >NUL
		GOTO :endFor
	)
	:endFor
	DEL /Q /F "%hexFile%" >NUL 2>&1

	ECHO %firstLine% | FIND "ef bb bf"     >NUL && SET "detectedCharset=UTF-8"     && EXIT /b 1
	ECHO %firstLine% | FIND "ff fe 00 00"  >NUL && SET "detectedCharset=UTF-32 LE" && EXIT /b 5
	ECHO %firstLine% | FIND "ff fe"        >NUL && SET "detectedCharset=UTF-16"    && EXIT /b 2
	ECHO %firstLine% | FIND "fe ff 00"     >NUL && SET "detectedCharset=UTF-16 BE" && EXIT /b 3
	ECHO %firstLine% | FIND "00 00 fe ff"  >NUL && SET "detectedCharset=UTF-32 BE" && EXIT /b 4
	SET "detectedCharset=ASCII"
EXIT /b 0
```

仅记录