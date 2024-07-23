QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Interface/computing_interface.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Interface/computing_interface.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L'C:/Program Files (x86)/Intel/oneAPI/ipp/2021.12/lib/' -lipps
win32: LIBS += -L'C:/Program Files (x86)/Intel/oneAPI/ipp/2021.12/lib/' -lippcore
win32: LIBS += -L'C:/Program Files (x86)/Intel/oneAPI/ipp/2021.12/lib/' -lippvm

INCLUDEPATH += 'C:/Program Files (x86)/Intel/oneAPI/ipp/2021.12/include/ipp'
DEPENDPATH += 'C:/Program Files (x86)/Intel/oneAPI/ipp/2021.12/include/ipp'
