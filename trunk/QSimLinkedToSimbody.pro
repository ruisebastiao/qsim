#    File: QSimLinkedToSimbody.pro
# Purpose: Includes files needed to link to Simbody (headers and libraries)
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
# ------------------------------------------------------------------
# List of additional include and library paths for Simbody.
# INCLUDEPATH - is the location of directory with header files
# LIBPATH     - is the location of directory with *.a files
# LIBS        - contains libraries you want to use in application
#               Note: LIBS are found along QMAKE_LIBDIR (formerly LIBPATH).
# Note: Enclose names in paths in quotes if there are spaces, e.g., "/Program Files"
#--------------------------------------------------------------------
# Ensure folder containing OpenSimAPI .dlls are on computer's PATH
# environment variable, e.g. C:\Simbody\bin is on PATH.
#--------------------------------------------------------------------
INCLUDEPATH  += /Simbody/include/
QMAKE_LIBDIR += /Simbody/lib/

#--------------------------------------------------------------------
# Platform-specific settings.
# win32  enabled for Windows platforms
# unix   enabled for Unix platforms - including macx
# macx   enabled for Unix platforms - and MacOS platforms
#--------------------------------------------------------------------
win32{
   # Windows only commands here
   LIBS         += pthreadVC2.lib
   LIBS         += SimTKlapack.lib

   CONFIG( release, debug|release ){
   LIBS         += SimTKsimbody.lib
   LIBS         += SimTKmath.lib
   LIBS         += SimTKcommon.lib
   }

   CONFIG( debug, debug|release ){
   LIBS         += SimTKsimbody_d.lib
   LIBS         += SimTKmath_d.lib
   LIBS         += SimTKcommon_d.lib
   }
}
#---------------------------------------------
else macx{         # MacOSx only commands here
}
#---------------------------------------------
else unix:!macx{   # Linux only commands here
}



