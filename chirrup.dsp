# Microsoft Developer Studio Project File - Name="chirrup" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=chirrup - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "chirrup.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "chirrup.mak" CFG="chirrup - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "chirrup - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "chirrup - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/comm/chirrup", UOAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "chirrup - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\xmlRPC" /I "." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FD /c
# SUBTRACT CPP /Fr /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 xmlRPC.lib libpng.lib zlib.lib /nologo /version:2.3 /subsystem:windows /machine:I386 /libpath:"..\xmlRPC\Release" /libpath:"..\zlib\projects\visualc6\Win32_LIB_Release" /libpath:"..\libpng\projects\visualc6\Win32_LIB_Release"
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "chirrup - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /GX /Zi /Od /I "..\xmlRPC" /I "." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 xmlRPC.lib libpngd.lib zlibd.lib /nologo /version:2.3 /subsystem:windows /incremental:no /debug /machine:I386 /pdbtype:sept /libpath:"..\xmlRPC\Debug" /libpath:"..\zlib\projects\visualc6\Win32_LIB_Debug" /libpath:"..\libpng\projects\visualc6\Win32_LIB_Debug"

!ENDIF 

# Begin Target

# Name "chirrup - Win32 Release"
# Name "chirrup - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutDlg.cpp
# ADD CPP /I "..\libpng" /I "..\zlib"
# End Source File
# Begin Source File

SOURCE=.\BlogIDSelectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\png2bmp\bmp2png.c
# ADD CPP /I "..\libpng" /I "..\zlib"
# End Source File
# Begin Source File

SOURCE=.\BrowserWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\capture.cpp
# End Source File
# Begin Source File

SOURCE=.\ChannelWassr.cpp
# End Source File
# Begin Source File

SOURCE=.\chirrup.cpp
# End Source File
# Begin Source File

SOURCE=.\chirrup.rc
# End Source File
# Begin Source File

SOURCE=.\chirrupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CImage.cpp
# End Source File
# Begin Source File

SOURCE=.\CJaikuManager.cpp
# End Source File
# Begin Source File

SOURCE=.\CManager.cpp
# End Source File
# Begin Source File

SOURCE=.\png2bmp\common.c
# ADD CPP /I "..\libpng" /I "..\zlib"
# End Source File
# Begin Source File

SOURCE=.\CService.cpp
# End Source File
# Begin Source File

SOURCE=.\CTabDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\CTabDialog2.cpp
# End Source File
# Begin Source File

SOURCE=.\CTwitterManager.cpp
# End Source File
# Begin Source File

SOURCE=.\DirectMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\DirectMessageList.cpp
# End Source File
# Begin Source File

SOURCE=.\DropTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\flickr.c
# End Source File
# Begin Source File

SOURCE=.\FriendDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\gyazo.c
# End Source File
# Begin Source File

SOURCE=.\haruFm.cpp
# End Source File
# Begin Source File

SOURCE=.\hatenaFotolife.c
# End Source File
# Begin Source File

SOURCE=.\hatenaHaiku.cpp
# End Source File
# Begin Source File

SOURCE=.\http.cpp
# End Source File
# Begin Source File

SOURCE=.\InputPinDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\jaiku.cpp
# End Source File
# Begin Source File

SOURCE=.\JaikuAuthSelectDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\mogo2.cpp
# End Source File
# Begin Source File

SOURCE=.\parameter.cpp
# End Source File
# Begin Source File

SOURCE=.\png2bmp\png2bmp.c
# ADD CPP /I "..\libpng" /I "..\zlib"
# End Source File
# Begin Source File

SOURCE=.\ProceedingDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\proxy.cpp
# End Source File
# Begin Source File

SOURCE=.\RichEditEx.cpp
# End Source File
# Begin Source File

SOURCE=.\savePNG.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingFlickr.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingGyazo.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingHaruFm.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingHatena.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingHatenaHaiku.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingJaiku.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingMogo2.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingProxy.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingTimelog.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingTumblr.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingTwitter.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingUploadWassr.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingWassr.cpp
# End Source File
# Begin Source File

SOURCE=..\xmlRPC\misc\strncmpi.c
# End Source File
# Begin Source File

SOURCE=..\bookey\timelocal.c
# End Source File
# Begin Source File

SOURCE=.\timelog.cpp
# End Source File
# Begin Source File

SOURCE=.\tumblr.c
# End Source File
# Begin Source File

SOURCE=.\TumblrEditDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\twitStar.c
# End Source File
# Begin Source File

SOURCE=.\twitter.cpp
# End Source File
# Begin Source File

SOURCE=.\TwitterAuthSelectDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\twitterTimeline.cpp
# End Source File
# Begin Source File

SOURCE=.\UploadImageDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\utility.c
# End Source File
# Begin Source File

SOURCE=.\wassr.cpp
# End Source File
# Begin Source File

SOURCE=.\widechar.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\BlogIDSelectDlg.h
# End Source File
# Begin Source File

SOURCE=.\png2bmp\bmphed.h
# End Source File
# Begin Source File

SOURCE=.\capture.h
# End Source File
# Begin Source File

SOURCE=.\ChannelWassr.h
# End Source File
# Begin Source File

SOURCE=.\chirrup.h
# End Source File
# Begin Source File

SOURCE=.\chirrupDlg.h
# End Source File
# Begin Source File

SOURCE=.\CImage.h
# End Source File
# Begin Source File

SOURCE=.\CJaikuManager.h
# End Source File
# Begin Source File

SOURCE=.\CManager.h
# End Source File
# Begin Source File

SOURCE=.\png2bmp\common.h
# End Source File
# Begin Source File

SOURCE=.\CService.h
# End Source File
# Begin Source File

SOURCE=.\CTabDialog.h
# End Source File
# Begin Source File

SOURCE=.\CTabDialog2.h
# End Source File
# Begin Source File

SOURCE=.\CTwitterManager.h
# End Source File
# Begin Source File

SOURCE=.\defaultImage.h
# End Source File
# Begin Source File

SOURCE=.\DirectMessage.h
# End Source File
# Begin Source File

SOURCE=.\DirectMessageList.h
# End Source File
# Begin Source File

SOURCE=.\DropTarget.h
# End Source File
# Begin Source File

SOURCE=.\flickr.h
# End Source File
# Begin Source File

SOURCE=.\FriendDialog.h
# End Source File
# Begin Source File

SOURCE=.\gyazo.h
# End Source File
# Begin Source File

SOURCE=.\haruFm.h
# End Source File
# Begin Source File

SOURCE=.\hatenaFotolife.h
# End Source File
# Begin Source File

SOURCE=.\hatenaHaiku.h
# End Source File
# Begin Source File

SOURCE=.\http.h
# End Source File
# Begin Source File

SOURCE=.\InputPinDialog.h
# End Source File
# Begin Source File

SOURCE=.\jaiku.h
# End Source File
# Begin Source File

SOURCE=.\JaikuAuthSelectDialog.h
# End Source File
# Begin Source File

SOURCE=.\mogo2.h
# End Source File
# Begin Source File

SOURCE=.\parameter.h
# End Source File
# Begin Source File

SOURCE=.\paramForThread.h
# End Source File
# Begin Source File

SOURCE=.\ProceedingDialog.h
# End Source File
# Begin Source File

SOURCE=.\proxy.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RichEditEx.h
# End Source File
# Begin Source File

SOURCE=.\SettingDialog.h
# End Source File
# Begin Source File

SOURCE=.\SettingFlickr.h
# End Source File
# Begin Source File

SOURCE=.\SettingGyazo.h
# End Source File
# Begin Source File

SOURCE=.\SettingHaruFm.h
# End Source File
# Begin Source File

SOURCE=.\SettingHatena.h
# End Source File
# Begin Source File

SOURCE=.\SettingHatenaHaiku.h
# End Source File
# Begin Source File

SOURCE=.\SettingJaiku.h
# End Source File
# Begin Source File

SOURCE=.\SettingMogo2.h
# End Source File
# Begin Source File

SOURCE=.\SettingProxy.h
# End Source File
# Begin Source File

SOURCE=.\SettingTimelog.h
# End Source File
# Begin Source File

SOURCE=.\SettingTumblr.h
# End Source File
# Begin Source File

SOURCE=.\SettingTwitter.h
# End Source File
# Begin Source File

SOURCE=.\SettingUploadWassr.h
# End Source File
# Begin Source File

SOURCE=.\SettingWassr.h
# End Source File
# Begin Source File

SOURCE=.\timelog.h
# End Source File
# Begin Source File

SOURCE=.\tumblr.h
# End Source File
# Begin Source File

SOURCE=.\TumblrEditDialog.h
# End Source File
# Begin Source File

SOURCE=.\twitStar.h
# End Source File
# Begin Source File

SOURCE=.\twitter.h
# End Source File
# Begin Source File

SOURCE=.\TwitterAuthSelectDialog.h
# End Source File
# Begin Source File

SOURCE=.\twitterTimeline.h
# End Source File
# Begin Source File

SOURCE=.\UploadImageDialog.h
# End Source File
# Begin Source File

SOURCE=.\utility.h
# End Source File
# Begin Source File

SOURCE=.\wassr.h
# End Source File
# Begin Source File

SOURCE=.\widechar.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\balloon.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bloglines.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cat.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chirrup.bmp
# End Source File
# Begin Source File

SOURCE=.\chirrup.exe.manifest
# End Source File
# Begin Source File

SOURCE=.\res\chirrup.ico
# End Source File
# Begin Source File

SOURCE=.\res\chirrup.rc2
# End Source File
# Begin Source File

SOURCE=.\res\chirrup2.ico
# End Source File
# Begin Source File

SOURCE=.\res\cur00001.cur
# End Source File
# Begin Source File

SOURCE=.\res\default_profile_image_mini.bmp
# End Source File
# Begin Source File

SOURCE=.\res\default_profile_image_normal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\delicious.bmp
# End Source File
# Begin Source File

SOURCE=.\res\digg.bmp
# End Source File
# Begin Source File

SOURCE=.\res\favotter.bmp
# End Source File
# Begin Source File

SOURCE=.\res\flickr.bmp
# End Source File
# Begin Source File

SOURCE=.\res\google.bmp
# End Source File
# Begin Source File

SOURCE=.\res\googleGroups.bmp
# End Source File
# Begin Source File

SOURCE=.\res\gyazo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\haruFm.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hatenaBookmark.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hatenaFotolife.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hatenaGroup.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hatenaHaiku.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hatenaStar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon_mixi001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\jaiku.bmp
# End Source File
# Begin Source File

SOURCE=.\res\livedoor.bmp
# End Source File
# Begin Source File

SOURCE=.\res\livedoorClip.bmp
# End Source File
# Begin Source File

SOURCE=.\res\magnolia.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mogo2.bmp
# End Source File
# Begin Source File

SOURCE=".\res\powered-by-twitter-sig.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\thumb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\timelog.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tumblr.bmp
# End Source File
# Begin Source File

SOURCE=.\res\twitterFanWiki.bmp
# End Source File
# Begin Source File

SOURCE=.\res\twitterFavicon.bmp
# End Source File
# Begin Source File

SOURCE=.\res\twitterSearch.bmp
# End Source File
# Begin Source File

SOURCE=.\res\twitterSNS.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wassr.bmp
# End Source File
# Begin Source File

SOURCE=.\res\yahoo.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\dist.bat
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
