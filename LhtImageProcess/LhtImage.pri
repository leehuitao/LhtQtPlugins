HEADERS += \
    $$PWD/LhtQtImage/lht_qt_imagefunc.h

SOURCES += \
    $$PWD/LhtQtImage/lht_qt_imagefunc.cpp

#DEFINES += BUILD_OPENCV_IMAGE
contains(DEFINES, BUILD_OPENCV_IMAGE) {
    include($$PWD/LhtQtOpencvConversion/LhtQtOpencvConversion.pri)
}

