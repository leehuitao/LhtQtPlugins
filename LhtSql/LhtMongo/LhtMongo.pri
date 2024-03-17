HEADERS += \
    $$PWD/connection_pool_mongodb.hpp \
    $$PWD/mongodb_manager.h

SOURCES += \
    $$PWD/connection_pool_mongodb.cpp \
    $$PWD/mongodb_manager.cpp

INCLUDEPATH += $$PWD/../include/

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/ -lbson-1.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/ -lbson-1.0


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/ -lmongoc-1.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/ -lmongoc-1.0

