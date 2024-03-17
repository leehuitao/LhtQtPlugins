HEADERS += \
    $$PWD/RegisterHandler.h \
    $$PWD/TestMethod.h \
    $$PWD/bundle_response_data.h \
    $$PWD/connections.h \
    $$PWD/io_manager.h \
    $$PWD/message_protocol.h \
    $$PWD/msghandler_repository.h \
    $$PWD/network_manager.h \
    $$PWD/parse_request_data.h \
    $$PWD/session_manager.h \
    $$PWD/sessions.h \
    $$PWD/tcp_acceptor.h \
    $$PWD/tcp_connection.h

SOURCES += \
    $$PWD/RegisterHandler.cpp \
    $$PWD/bundle_response_data.cpp \
    $$PWD/connections.cpp \
    $$PWD/io_manager.cpp \
    $$PWD/network_manager.cpp \
    $$PWD/parse_request_data.cpp \
    $$PWD/session_manager.cpp \
    $$PWD/sessions.cpp \
    $$PWD/tcp_acceptor.cpp \
    $$PWD/tcp_connection.cpp

INCLUDEPATH += $$PWD/../../LhtSql/include/
LIBS += -L$$PWD/../../LhtSql/lib/debug/ -llibboost_chrono-vc143-mt-gd-x64-1_78 -llibboost_date_time-vc143-mt-gd-x64-1_78 -llibboost_filesystem-vc143-mt-gd-x64-1_78 -llibboost_locale-vc143-mt-gd-x64-1_78
LIBS += -L$$PWD/../../LhtSql/lib/debug/  -llibboost_regex-vc143-mt-gd-x64-1_78 -llibboost_system-vc143-mt-gd-x64-1_78 -llibboost_thread-vc143-mt-gd-x64-1_78
LIBS +=  -llibcurl -llibeay32  -lssleay32


DEFINES += WIN32_LEAN_AND_MEAN
