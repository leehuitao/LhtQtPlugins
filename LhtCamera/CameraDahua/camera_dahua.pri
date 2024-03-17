DEFINES += QT_DEPRECATED_WARNINGS


contains(QT_ARCH, i386){

}
else{
LIBS += $$PWD/Depends/x64/vs2013shared/MVSDKmd.lib\
        $$PWD/Depends/x64/vs2013shared/VideoRender.lib\
        $$PWD/Depends/x64/vs2013shared/ImageConvert.lib
}

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/Include
INCLUDEPATH += $$PWD/../include
INCLUDEPATH += $$PWD/../include/GenICam

HEADERS += \
    $$PWD/camera_dahua.h

SOURCES += \
    $$PWD/camera_dahua.cpp

