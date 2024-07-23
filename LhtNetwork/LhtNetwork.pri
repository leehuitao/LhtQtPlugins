
#DEFINES += BUILD_BOOST
contains(DEFINES, BUILD_BOOST) {
    include($$PWD/BoostTcpServer/BoostTcpServer.pri)
}
#DEFINES += BUILD_MQTT
contains(DEFINES, BUILD_MQTT) {
    include($$PWD/Mqtt/Mqtt.pri)
}
