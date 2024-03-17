HEADERS += \
    $$PWD/connection_pool_abstract.hpp \
    $$PWD/connection_pool_mysql.hpp \
    $$PWD/dbio.hpp \
    $$PWD/dbio_mysql.hpp

SOURCES += \
    $$PWD/connection_pool_mysql.cpp \
    $$PWD/dbio_mysql.cpp

INCLUDEPATH += $$PWD/../include/

LIBS += -L$$PWD/../lib/debug/ -llibboost_chrono-vc142-mt-gd-x64-1_78 -llibboost_date_time-vc142-mt-gd-x64-1_78 -llibboost_filesystem-vc142-mt-gd-x64-1_78 -llibboost_locale-vc142-mt-gd-x64-1_78
LIBS += -L$$PWD/../lib/debug/  -llibboost_regex-vc142-mt-gd-x64-1_78 -llibboost_system-vc142-mt-gd-x64-1_78 -llibboost_thread-vc142-mt-gd-x64-1_78
LIBS +=  -llibcurl -llibeay32 -llibmysql -lssleay32
