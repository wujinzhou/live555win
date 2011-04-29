AV_BASE_DIR = $$PWD 
INCLUDEPATH += $$AV_BASE_DIR/include/
CONFIG( debug,debug|release ){
AV_DEST_BIN_DIR = $$AV_BASE_DIR/bin/debug
OBJECTS_DIR = $$AV_BASE_DIR/tmp/debug
MOC_DIR = $$AV_BASE_DIR/tmp/debug
RCC_DIR = $$AV_BASE_DIR/tmp/debug
}
else{
AV_DEST_BIN_DIR = $$AV_BASE_DIR/bin/release
OBJECTS_DIR = $$AV_BASE_DIR/tmp/release
MOC_DIR = $$AV_BASE_DIR/tmp/release
RCC_DIR = $$AV_BASE_DIR/tmp/release
}
UI_DIR += $$AV_BASE_DIR/forms

win32{ 
AV_DEST_BIN_DIR = $$AV_DEST_BIN_DIR/win32
} 

unix{ 
AV_DEST_BIN_DIR = $$AV_DEST_BIN_DIR/linux
}
 DESTDIR = $$AV_DEST_BIN_DIR 

win32:debug {
     CONFIG += console
 }