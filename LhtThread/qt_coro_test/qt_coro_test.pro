# Please take mingw or linux g++ as compiler.
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20
QMAKE_CXXFLAGS += --std=c++20

SOURCES += \
	filedealer.cpp \
	main.cpp \
	dlgct.cpp

HEADERS += \
	dlgct.h \
	filedealer.h \
	nmcalc.h

FORMS += \
	dlgct.ui

