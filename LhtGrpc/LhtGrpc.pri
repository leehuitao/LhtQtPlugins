
INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD


HEADERS += $$PWD/ServiceProto.pb.h \
    $$PWD/NetIO/server/HandleTest1.h \
    $$PWD/NetIO/server/handleRepository/RegisterHandler.h \
    $$PWD/NetIO/server/handleRepository/msghandler_repository.h \
    $$PWD/NetIO/server/handle_interface.h \
    $$PWD/NetIO/server/server_interface.h \
    $$PWD/QtWaitConditionThread/thread_pool_basic.h

SOURCES += $$PWD/ServiceProto.pb.cc \
    $$PWD/NetIO/server/HandleTest1.cpp \
    $$PWD/NetIO/server/handleRepository/RegisterHandler.cpp \
    $$PWD/NetIO/server/handle_interface.cpp \
    $$PWD/NetIO/server/server_interface.cpp \
    $$PWD/QtWaitConditionThread/thread_pool_basic.cpp

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += $$PWD/ServiceProto.grpc.pb.h
SOURCES += $$PWD/ServiceProto.grpc.pb.cc

SOURCES += \
    $$PWD/NetIO/net_grpc_interface.cpp
#    $$PWD/main.cpp \
#    $$PWD/mainwindow.cpp

HEADERS += \
    $$PWD/NetIO/net_grpc_interface.h
#    $$PWD/mainwindow.h

#FORMS += \
#    $$PWD/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    $$PWD/ServiceProto.proto


INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

LIBS += $$PWD/debuglib/gpr.lib
LIBS += $$PWD/debuglib/grpc.lib
LIBS += $$PWD/debuglib/grpc++_alts.lib
LIBS += $$PWD/debuglib/grpc_plugin_support.lib
LIBS += $$PWD/debuglib/grpc_unsecure.lib
LIBS += $$PWD/debuglib/grpc++_error_details.lib
LIBS += $$PWD/debuglib/grpc++_unsecure.lib
LIBS += $$PWD/debuglib/grpcpp_channelz.lib
LIBS += $$PWD/debuglib/address_sorting.lib
LIBS += $$PWD/debuglib/grpc++.lib
LIBS += $$PWD/debuglib/grpc++_reflection.lib
LIBS += $$PWD/debuglib/abseil_dll.lib
LIBS += $$PWD/debuglib/cares.lib
LIBS += -L$$PWD/debuglib/ -labseil_dll
LIBS += -L$$PWD/debuglib/ -lupb
LIBS += -L$$PWD/debuglib/ -lupb_utf8_range
LIBS += -L$$PWD/debuglib/ -lupb_collections
LIBS += -L$$PWD/debuglib/ -lupb_extension_registry
LIBS += -L$$PWD/debuglib/ -lupb_fastdecode
LIBS += -L$$PWD/debuglib/ -lupb_json
LIBS += -L$$PWD/debuglib/ -lupb_mini_table
LIBS += -L$$PWD/debuglib/ -lupb_reflection
LIBS += -L$$PWD/debuglib/ -lupb_textformat
LIBS += -L$$PWD/debuglib/ -llibcrypto
LIBS += -L$$PWD/debuglib/ -llibssl
LIBS += -L$$PWD/debuglib/ -lzlibd
LIBS += -L$$PWD/debuglib/ -lre2

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -llibprotobuf
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -llibprotobufd
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -llibprotoc
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -llibprotocd
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -llibprotobuf-lite
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -llibprotobuf-lited

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
