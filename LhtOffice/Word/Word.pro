#-------------------------------------------------
#
# Project created by QtCreator 2018-08-30T21:44:34
#
#-------------------------------------------------

QT  += core gui
QT  += axcontainer
QT  += concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qworddemo.cpp \
    Word/qword.cpp

HEADERS  += mainwindow.h \
    qworddemo.h \
    Word/qword.h

FORMS    += mainwindow.ui \
    qworddemo.ui
