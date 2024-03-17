QT       += multimedia

#DEFINES += BUILD_OPENSSL
contains(DEFINES, BUILD_OPENSSL) {
    include($$PWD/OpenSsl/OpenSsl.pri)
}


HEADERS += \
    $$PWD/FFmpeg/aac_encode.h \
    $$PWD/FFmpeg/lht_ffmpeg_aac_encode.h \
    $$PWD/Opus/lht_opus_encode.h \
    $$PWD/Opus/opus_encode.h \
    $$PWD/QtEncode/lht_qt_encode.h \
    $$PWD/encode_basic.h \
    $$PWD/lht_callback.h \
    $$PWD/lht_define.h \
    $$PWD/thread_pool_basic.h

SOURCES += \
    $$PWD/FFmpeg/aac_encode.cpp \
    $$PWD/FFmpeg/lht_ffmpeg_aac_encode.cpp \
    $$PWD/Opus/lht_opus_encode.cpp \
    $$PWD/Opus/opus_encode.cpp \
    $$PWD/QtEncode/lht_qt_encode.cpp \
    $$PWD/encode_basic.cpp \
    $$PWD/thread_pool_basic.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lopencv_world480
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lopencv_world480d

DEFINES += __STDC_CONSTANT_MACROS
INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

LIBS += -L$$PWD/lib
LIBS += -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lswscale
LIBS += -lopus

