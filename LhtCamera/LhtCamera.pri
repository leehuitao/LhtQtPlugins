HEADERS += \
    $$PWD/camera_base.h

SOURCES += \
    $$PWD/camera_base.cpp

include($$PWD/CameraDahua/camera_dahua.pri)
include($$PWD/CameraHik/camera_hik.pri)
include($$PWD/CameraOpt/camera_opt.pri)

INCLUDEPATH += $$PWD/include/
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lopencv_world3415
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lopencv_world3415d
