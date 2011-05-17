#    File: QSim.pro
# Purpose: Creates compiler files (e.g., makefile or .vcproj file).
#    Info: http://doc.trolltech.com/4.2/qmake-tutorial.html
# -------------------------------------------------------------------------- *
# QSim was developed with support from Simbios (the NIH National Center      *
# for Physics-Based Simulation Biological Structures at Stanford) under NIH  *
# Roadmap for Medical Research grant U54 GM072970 and from NCSRR (National   *
# Center for Simulation in Rehabilitation Research) under NIH research       *
# infrastructure grant R24 HD065690.                                         *
#                                                                            *
# Portions copyright (c) 2011 the Authors and/or and Stanford University.    *
# Authors: Paul Mitiguy                                                      *
# Contributors: Ayman Habib, Michael Sherman                                 *
#                                                                            *
# Permission is hereby granted, free of charge, to any person obtaining a    *
# copy of this software and associated documentation files (the "Software"), *
# to deal in the Software without restriction, including without limitation  *
# the rights to use, copy, modify, merge, publish, distribute, sublicense,   *
# and/or sell copies of the Software, and to permit persons to whom the      *
# Software is furnished to do so, subject to the following conditions:       *
#                                                                            *
# This sentence, the above copyright and permission notices, and the         *
# following disclaimer shall be included in all copies or substantial        *
# portions of the Software.                                                  *
#                                                                            *
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
# FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL   *
# THE AUTHORS, CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,    *
# DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR      *
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE  *
# USE OR OTHER DEALINGS IN THE SOFTWARE.                                     *
# -------------------------------------------------------------------------- *
#   Use 1:  To generate the makefile someName.mak for use with gcc or name:
#           qmake -o makefile QSim.pro
#   Use 2:  To generate a Microsoft Visual Studio vcproj file:
#           qmake -tp -vc     QSim.pro
# ------------------------------------------------------------------

# ------------------------------------------------------------------
# TEMPLATE = app      Creates a Makefile to build an application.
# TEMPLATE = lib      Creates a Makefile to build a library.
# TEMPLATE = vcapp    Creates a Visual Studio Project file to build an application.
# TEMPLATE = vclib    Creates a Visual Studio Project file to build a library.
# CONFIG += windows   (full windows  application when TEMPLATE = app)
# CONFIG += console   (basic console application when TEMPLATE = app)
#--------------------------------------------------------------------
# Platform-specific settings.
# win32  enabled for Windows platforms
# unix   enabled for Unix platforms - including macx
# macx   enabled for Unix platforms - and MacOS platforms
#--------------------------------------------------------------------
win32{             # Windows only commands here

   TEMPLATE   = vcapp    # Change vcapp to app if not using Microsoft Visual Studio.
   INCLUDEPATH  += /Qt/4.7.2/include/

   # DEF_FILE   .def file to be linked against for the application.
   # RC_FILE     resource file for the application.
   # RES_FILE    resource file to be linked against for the application.
   # Note:       On Windows 32-bit, _may_ have to set environment variables:
   #             QMAKESPEC   to   win32-msvc2008
   #             PATH        add  C:\Qt\4.7.2\bin\
}
#---------------------------------------------
else macx{         # MacOSx only commands here
   TEMPLATE   = app
   INCLUDEPATH += /Library/Frameworks/
}
#---------------------------------------------
else unix:!macx{   # Linux only commands here
   TEMPLATE   = app
}

#--------------------------------------------------------------------
# Target on Windows is QSim.exe.  On Macintosh/Linux is QSim.
#--------------------------------------------------------------------
TARGET    = QSim
CONFIG    += windows
CONFIG    += debug_and_release  # debug  or  release  or  debug_and_release
CONFIG    += warn_on            # warn_on  or  warn_off

#--------------------------------------------------------------------
# Configuration settings.
# CONFIG += qt  ensures qmake adds the relevant libraries for linking.
#               ensures build lines are included for moc (Meta Object Compiler).
#               ensures build lines are included for uic (User Interface Compiler).
# CONFIG += qt  includes core and gui by default.
# core:         QtCore module contains core non-GUI functionality. All other Qt modules rely on this module.
# gui:          QtGui  module extends QtCore with GUI functionality.
# network:      QtNetwork module allows easy-to-use portable TCP/IP clients and servers.
#               High level classes include QHttp and QFtp that implement specific application-level protocols, and
#               lower-level classes such as QTcpSocket, QTcpServer, and QUdpSocket.
# opengl:       QtOpenGL makes it easy to use OpenGL (rendering 3D graphics) in Qt applications.
#               QtOpenGL widget class opens an OpenGL display buffer where the OpenGL API renders content.
# sql:          QtSql provides data-aware widgets and seamless database integration to Qt.
# svg:          QtSvd provides Scalable Vector Graphics (SVG 1.1) is a language for 2D graphics in XML and 3GPP mobile phones.
# xml:          QtXml module provides C++ implementations of SAX (event-based tandard interface for XML parsers, see http://www.saxproject.org) and
#               DOM (maps XML document to a tree structure, see http://www.w3.org/DOM/ and QtDom classes)
#--------------------------------------------------------------------
CONFIG    += qt
CONFIG    += core       # Qtcore module is included by default with CONFIG += qt
CONFIG    += gui        # Qtgui modules is included by default with CONFIG += qt
#  CONFIG    += network # QtNetwork module (TCP/IP, http, and sockets)
#  CONFIG    += opengl  # QtOpenGL module  (3D Rendering graphics)
#  CONFIG    += sql     # QtSql module     (Database)
#  CONFIG    += svg     # QtSvg module
#  CONFIG    += xml     # QtXml module


#--------------------------------------------------------------------
# List of additional paths e.g., for Qt header and library files.
# INCLUDEPATH - is the location of directory with header files
# LIBPATH     - is the location of directory with *.a files
# LIBS        - contains libraries you want to use in application
#               Note: LIBS are found along QMAKE_LIBDIR (formerly LIBPATH).
# Note: Enclose names in paths in quotes if there are spaces, e.g., "/Program Files"
#--------------------------------------------------------------------
# Header files for source code
#--------------------------------------------------------------------
HEADERS      += ./QSimSourceCode/CppStandardHeaders.h
HEADERS      += ./QSimSourceCode/QSimGenericFunctions.h
HEADERS      += ./QSimSourceCode/QSimGui.h
HEADERS      += ./QSimSourceCode/QSimStartSimulation.h
HEADERS      += ./QSimSourceCode/QSimMainWindow.h

#--------------------------------------------------------------------
# Source code  (cpp)
#--------------------------------------------------------------------
SOURCES      += ./QSimSourceCode/QSimGui.cpp
SOURCES      += ./QSimSourceCode/QSimMain.cpp
SOURCES      += ./QSimSourceCode/QSimStartSimulationGui.cpp
SOURCES      += ./QSimSourceCode/QSimStartSimulationNoGui.cpp
SOURCES      += ./QSimSourceCode/QSimMainWindow.cpp

#--------------------------------------------------------------------
# List of additional include and library paths for Simbody.
# If using Simbody (not OpenSim API), ensure folder containing Simbody .dlls are
# on Windows computer's PATH environment variable, e.g. C:\Simbody\bin is on PATH.
#--------------------------------------------------------------------
include(QSimLinkedToSimbody.pro)
include(QSimLinkedToOpenSimAPI.pro)



