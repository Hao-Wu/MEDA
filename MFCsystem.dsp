# Microsoft Developer Studio Project File - Name="MFCsystem" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MFCsystem - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MFCsystem.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MFCsystem.mak" CFG="MFCsystem - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MFCsystem - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MFCsystem - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MFCsystem - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "MFCsystem - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MFCsystem - Win32 Release"
# Name "MFCsystem - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\affine.cpp
# End Source File
# Begin Source File

SOURCE=.\Bigint.cpp
# End Source File
# Begin Source File

SOURCE=.\Caeser.cpp
# End Source File
# Begin Source File

SOURCE=.\DES.cpp
# End Source File
# Begin Source File

SOURCE=.\Des2.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog1.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog10.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog11.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog12.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog13.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog2.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog3.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog4.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog6.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog7.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog8.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog9.cpp
# End Source File
# Begin Source File

SOURCE=.\FileInOut.cpp
# End Source File
# Begin Source File

SOURCE=.\Gfl.cpp
# End Source File
# Begin Source File

SOURCE=.\IDEA.CPP
# End Source File
# Begin Source File

SOURCE=.\MFCsystem.cpp
# End Source File
# Begin Source File

SOURCE=.\MFCsystem.rc
# End Source File
# Begin Source File

SOURCE=.\MFCsystemDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Multiliteral.cpp
# End Source File
# Begin Source File

SOURCE=.\MyFileDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MyRsa.cpp
# End Source File
# Begin Source File

SOURCE=.\Permutation.cpp
# End Source File
# Begin Source File

SOURCE=.\playfair.cpp
# End Source File
# Begin Source File

SOURCE=.\RC4.cpp
# End Source File
# Begin Source File

SOURCE=.\RSA.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Window.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\affine.h
# End Source File
# Begin Source File

SOURCE=.\BigInt.h
# End Source File
# Begin Source File

SOURCE=.\Caeser.h
# End Source File
# Begin Source File

SOURCE=.\DES.H
# End Source File
# Begin Source File

SOURCE=.\Des2.h
# End Source File
# Begin Source File

SOURCE=.\Dialog1.h
# End Source File
# Begin Source File

SOURCE=.\Dialog10.h
# End Source File
# Begin Source File

SOURCE=.\Dialog11.h
# End Source File
# Begin Source File

SOURCE=.\Dialog12.h
# End Source File
# Begin Source File

SOURCE=.\Dialog13.h
# End Source File
# Begin Source File

SOURCE=.\Dialog2.h
# End Source File
# Begin Source File

SOURCE=.\Dialog3.h
# End Source File
# Begin Source File

SOURCE=.\Dialog4.h
# End Source File
# Begin Source File

SOURCE=.\Dialog6.h
# End Source File
# Begin Source File

SOURCE=.\Dialog7.h
# End Source File
# Begin Source File

SOURCE=.\Dialog8.h
# End Source File
# Begin Source File

SOURCE=.\Dialog9.h
# End Source File
# Begin Source File

SOURCE=.\FileInOut.h
# End Source File
# Begin Source File

SOURCE=.\Gfl.h
# End Source File
# Begin Source File

SOURCE=.\global.h
# End Source File
# Begin Source File

SOURCE=.\head.h
# End Source File
# Begin Source File

SOURCE=.\IDEA.H
# End Source File
# Begin Source File

SOURCE=.\MFCsystem.h
# End Source File
# Begin Source File

SOURCE=.\MFCsystemDlg.h
# End Source File
# Begin Source File

SOURCE=.\Multiliteral.h
# End Source File
# Begin Source File

SOURCE=.\MyFileDialog.h
# End Source File
# Begin Source File

SOURCE=.\Permutation.h
# End Source File
# Begin Source File

SOURCE=.\playfair.h
# End Source File
# Begin Source File

SOURCE=.\RC4.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RSA.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Vigenere.cpp
# End Source File
# Begin Source File

SOURCE=.\Window.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\a.bmp
# End Source File
# Begin Source File

SOURCE=.\res\a.bmp
# End Source File
# Begin Source File

SOURCE=.\b.bmp
# End Source File
# Begin Source File

SOURCE=.\c.bmp
# End Source File
# Begin Source File

SOURCE=.\d.bmp
# End Source File
# Begin Source File

SOURCE=.\Picture\DES_EBOX.bmp
# End Source File
# Begin Source File

SOURCE=.\Picture\DES_IP.bmp
# End Source File
# Begin Source File

SOURCE=.\Picture\DES_pbox.bmp
# End Source File
# Begin Source File

SOURCE=.\Picture\DES_PC1.bmp
# End Source File
# Begin Source File

SOURCE=.\Picture\DES_PC2.bmp
# End Source File
# Begin Source File

SOURCE=.\duowenzi.bmp
# End Source File
# Begin Source File

SOURCE=.\Picture\duowenzi.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MFCsystem.ico
# End Source File
# Begin Source File

SOURCE=.\res\MFCsystem.rc2
# End Source File
# Begin Source File

SOURCE=.\res\qqq.bmp
# End Source File
# Begin Source File

SOURCE=.\Picture\wenzi.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
