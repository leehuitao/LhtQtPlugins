#epoll
unix:!macx {
SOURCES += \
    $$PWD/Epoll/lht_epoll_server1.cpp \
    $$PWD/Epoll/lht_epoll_server2.cpp
}
#iocp
win32 {

}

HEADERS += \
    $$PWD/MemoryPool/lht_memory_pool.h

SOURCES += \
    $$PWD/MemoryPool/lht_memory_pool.cpp


