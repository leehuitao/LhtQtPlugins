DEFINES += QT_DEPRECATED_WARNINGS


win32: LIBS += -L$$PWD/../lib/ -lMvCameraControl
LIBS += $$PWD/../lib/MvCameraControl.lib
INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include
INCLUDEPATH += $$PWD/../include/GenICam
DEPENDPATH += $$PWD/../include/GenICam


HEADERS += \
$$PWD/camera_hik.h

SOURCES += \
$$PWD/camera_hik.cpp
