HEADERS += \
    $$PWD/glog_example.h

SOURCES += \
    $$PWD/glog_example.cpp

DEFINES += GLOG_USE_GLOG_EXPORT
INCLUDEPATH += $$PWD/include/

CONFIG(debug, debug | release) {
    LIBS += -L$$PWD/lib/debug -lglogd
}

CONFIG(release, debug | release) {
    LIBS += -L$$PWD/lib/release -lglog
}
