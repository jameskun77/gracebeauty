######################################################################
# Automatically generated by qmake (2.01a) ?? ?? 11 16:37:44 2017
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
INCLUDEPATH += depends/directx-apr2006/include

#LIBS += -Ldepends/directx-apr2006/lib/release
QMAKE_LIBDIR += depends/directx-apr2006/lib/release

LIBS += d3d9.lib
LIBS += d3dx9.lib

DEFINES  -= UNICODE    //去除

# Input
FORMS += mainwindow.ui

HEADERS  += mainwindow.h
HEADERS  += CommonUtil.h
HEADERS  += D3DEffect.h
HEADERS  += D3DRender.h

SOURCES  += main.cpp
SOURCES  += mainwindow.cpp
SOURCES  += CommonUtil.cpp
SOURCES  += D3DEffect.cpp
SOURCES  += D3DRender.cpp
