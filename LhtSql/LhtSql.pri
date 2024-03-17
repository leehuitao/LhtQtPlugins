include($$PWD/LhtHiredis/LhtHiredis.pri)
include($$PWD/LhtMongo/LhtMongo.pri)
include($$PWD/LhtMysql/LhtMysql.pri)

DEFINES += WIN32_LEAN_AND_MEAN

HEADERS += \
    $$PWD/LhtBoostIO/io_manager.h

SOURCES += \
    $$PWD/LhtBoostIO/io_manager.cpp
