######################################################################
# Automatically generated by qmake (2.01a) ?? ?? 25 17:33:14 2011
######################################################################

include ( ../config.pri )
TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
INCLUDEPATH += ../include/ffmpeg/include

# Input
HEADERS += AvCore.h  ../include/IAvCore.h mytest.h
SOURCES += AvCore.cpp  main.cpp mytest.cpp

win32{
FFMPEG_PATH = $$AV_BASE_DIR/include/ffmpeg
LIBS += $$FFMPEG_PATH/lib/avformat.lib 
LIBS += $$FFMPEG_PATH/lib/avcodec.lib
}

unix{
FFMPEG_PATH = $$AV_BASE_DIR/include/ffmpeg
LIBS += -L$$FFMPEG_PATH/lib -lavformat 
LIBS += -L$$FFMPEG_PATH/lib -lavcodec
}
 

CONFIG( debug,debug|release ){
AV_DEST_BIN_DIR = $$AV_BASE_DIR/bin/avcore/debug
OBJECTS_DIR = $$AV_BASE_DIR/tmp/avcore/debug
MOC_DIR = $$AV_BASE_DIR/tmp/avcore/debug
RCC_DIR = $$AV_BASE_DIR/tmp/avcore/debug
}
else{
AV_DEST_BIN_DIR = $$AV_BASE_DIR/bin/avcore/release
OBJECTS_DIR = $$AV_BASE_DIR/tmp/avcore/release
MOC_DIR = $$AV_BASE_DIR/tmp/avcore/release
RCC_DIR = $$AV_BASE_DIR/tmp/avcore/release
}