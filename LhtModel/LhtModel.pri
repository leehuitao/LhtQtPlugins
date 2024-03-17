#epoll
unix:!macx {
SOURCES += \
    $$PWD/Epoll/lht_epoll_server1.cpp \
    $$PWD/Epoll/lht_epoll_server2.cpp
}
#iocp
win32 {

}


