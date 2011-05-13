@echo off
rem ------------------------------------------------------------------
rem    File:  qmakeQSim.bat   (created by Paul Mitiguy)
rem Purpose:  Simplifies invoking qmake on Windows PC computers.
rem    Use:   At the command (cmd.exe) prompt, type  qmakeQSim.bat
rem           which creates QSim.vcproj file in another directory.
rem ------------------------------------------------------------------
rem Note:     On Windows 32-bit, _may_ have to set the environment variables:
rem           PATH        add  C:\Qt\4.7.2\bin\
rem           Otherwise, try calling Qt's qmake  with a full path, e.g.,
rem           C:\Qt\4.7.2\bin\qmake
rem ------------------------------------------------------------------
rem Note:     The following environment variable was recommended to be
rem           set, by I did not find it necessary.
rem           QMAKESPEC   to   win32-msvc2008
rem ------------------------------------------------------------------
rem This assumes a parallel set of folders.
rem 1st folder  QSimSourceCode    contains trunk (that contains source code).
rem 2nd folder  QSimCompilerMisc  contains build folders (debug/release).
rem ------------------------------------------------------------------
@echo on
echo .
cd ..\..\QSimCompilerMisc
qmake  ..\QSimSourceCode\trunk\QSim.pro
cd ..\QSimSourceCode\trunk
@echo.
@echo  Created  ..\..\QSimCompilerMisc\QSim.vcproj  
@echo.


