HEADERS += \
    $$PWD/connection_pool_redis.hpp \
    $$PWD/redis_manager.h

SOURCES += \
    $$PWD/connection_pool_redis.cpp \
    $$PWD/redis_manager.cpp

INCLUDEPATH += $$PWD/../include/

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/debug/ -lhiredis
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/debug/ -lhiredis


