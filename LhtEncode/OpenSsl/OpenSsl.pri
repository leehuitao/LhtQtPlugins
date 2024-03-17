

DEFINES += __STDC_CONSTANT_MACROS
INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

LIBS += -L$$PWD/lib
LIBS += -L$$PWD/lib/ -llibssl
LIBS += -L$$PWD/lib/ -llibcrypto
HEADERS += \
    $$PWD/lht_openssl_encode.h

SOURCES += \
    $$PWD/lht_openssl_encode.cpp
