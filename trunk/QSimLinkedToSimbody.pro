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
# -------------------------------------------------------------------------- *
# List of additional include and library paths for Simbody.
# INCLUDEPATH  - is the location of directory with .h header files
# QMAKE_LIBDIR - is the location of directory with .a files (formerly LIBPATH)
# LIBS         - contains libraries you want to use in application
#                Note: LIBS are found along QMAKE_LIBDIR (formerly LIBPATH).
# Note: Enclose names in paths in quotes if there are spaces, e.g., "/Program Files"
#--------------------------------------------------------------------


#--------------------------------------------------------------------
# Windows only commands here
#--------------------------------------------------------------------
win32{

   INCLUDEPATH  += /Simbody/include
   QMAKE_LIBDIR += /Simbody/lib

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
   #-----------------------------------------------------------------
   # Ensure .dlls are in the executable's folder (best) or listed on computer's
   # PATH environment variable, e.g. C:\Simbody\bin is on PATH.
   #-----------------------------------------------------------------
}

#--------------------------------------------------------------------
# MacOSx only commands here
#--------------------------------------------------------------------
macx{

   INCLUDEPATH  += /usr/local/SimTK/include
   QMAKE_LIBDIR += /usr/local/SimTK/lib
   QMAKE_LFLAGS += -m32
   QMAKE_CFLAGS += -m32
   QMAKE_CXXFLAGS += -m32

#  LIBS         += pthread
#  LIBS         += SimTKlapack

   CONFIG( release, debug|release ){
   LIBS         += -lSimTKsimbody
   LIBS         += -lSimTKmath
   LIBS         += -lSimTKcommon
   }

   CONFIG( debug, debug|release ){
   LIBS         += -lSimTKsimbody_d
   LIBS         += -lSimTKmath_d
   LIBS         += -lSimTKcommon_d
   }

   #-----------------------------------------------------------------
   # The actual name of the library on Mac/Linux start with libThenNameOfActualLibrary then .so
   # gcc -L/usr/bin/Simbody/lib  specifies the path to the library.
   # gcc -lactualNameOfLibraryFile designates a library to link with.
   # Ensure .so files are in the executable's folder (best) or listed on computer's
   # DYLD_LIBRARY_PATH environment variable, e.g. /Simbody/bin is on DYLD_LIBRARY_PATH
   # Sherm says LIBS += SimTKsimbody will recursively include the ones it depends on (all).
   # Alternate way to get gcc to link libraries is: LIBS += -L/usr/local/SimTK/lib -lSimTKsimbody -lSimTKmath  -lSimTKcommon
   #-----------------------------------------------------------------
}

#--------------------------------------------------------------------
# Linux only commands here
#--------------------------------------------------------------------
unix:!macx{

   QMAKE_LFLAGS += -m32
   QMAKE_CFLAGS += -m32
   QMAKE_CXXFLAGS += -m32

   CONFIG( release, debug|release ){
   LIBS         += -lSimTKsimbody
   LIBS         += -lSimTKmath
   LIBS         += -lSimTKcommon
   }

   CONFIG( debug, debug|release ){
   LIBS         += -lSimTKsimbody_d
   LIBS         += -lSimTKmath_d
   LIBS         += -lSimTKcommon_d
   }

   #-----------------------------------------------------------------
   # The actual name of the library on Mac/Linux start with libThenNameOfActualLibrary then .so
   # gcc -L/usr/bin/Simbody/lib  specifies the path to the library.
   # gcc -lactualNameOfLibraryFile designates a library to link with.
   # Ensure .so files are in the executable's folder (best) or listed on computer's
   # LD_LIBRARY_PATH environment variable, e.g. /Simbody/bin is on LD_LIBRARY_PATH
   # Sherm says LIBS += SimTKsimbody will recursively include the ones it depends on (all).
   #-----------------------------------------------------------------
}



