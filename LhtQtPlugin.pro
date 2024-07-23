QT       += core gui network

QMAKE_CXXFLAGS += /utf-8
QMAKE_LFLAGS += /utf-8

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20
# 编译相机模块由于版本不同，需要的库函数也不同这里不进行编译，需要的话请修改头文件、lib以及bin文件后进行编译
#DEFINES += BUILD_CAMERA
contains(DEFINES, BUILD_CAMERA) {
    include($$PWD/LhtCamera/LhtCamera.pri)
}

# 编译SQL模块由于数据库版本不同，需要的库函数也不同这里不进行编译，需要的话请修改头文件、lib以及bin文件后进行编译
#DEFINES += BUILD_SQL
contains(DEFINES, BUILD_SQL) {
    include($$PWD/LhtSql/LhtSql.pri)
}

# 编译GRPC的库比较大，这里不编译，需要的话将GRPC下的压缩包解压后，将lib放到lht-qt-plugins\LhtGrpc文件夹下，将bin中所有的文件放到exe路径下
#DEFINES += BUILD_GRPC
contains(DEFINES, BUILD_GRPC) {
    include($$PWD/LhtGrpc/LhtGrpc.pri)
}

#DEFINES += BUILD_ENCODE
contains(DEFINES, BUILD_ENCODE) {
    include($$PWD/LhtEncode/LhtEncode.pri)
}
include($$PWD/LhtLog/LhtLog.pri)
include($$PWD/LhtFile/LhtFile.pri)
include($$PWD/LhtGui/LhtGui.pri)
include($$PWD/LhtImageProcess/LhtImage.pri)
include($$PWD/LhtNetwork/LhtNetwork.pri)
include($$PWD/LhtThread/LhtThread.pri)
include($$PWD/LhtModel/LhtModel.pri)

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    LhtExamples/lht_examples.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    LhtExamples/lht_examples.h \
    mainwindow.h

FORMS += \
    LhtExamples/lht_examples.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
