INCLUDEPATH += $$PWD/include/
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lopencv_world3415
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lopencv_world3415d

HEADERS += \
    $$PWD/lht_qt_opencv_conversion.h

SOURCES += \
    $$PWD/lht_qto_pencv_conversion.cpp
