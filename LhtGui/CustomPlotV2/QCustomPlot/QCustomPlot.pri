QT       += printsupport opengl
DEFINES += QCUSTOMPLOT_USE_OPENGL

HEADERS += \
    $$PWD/qcustomplot.h

SOURCES += \
    $$PWD/qcustomplot.cpp

HEADERS += \
    $$PWD/include/GL/freeglut.h \
    $$PWD/include/GL/freeglut_ext.h \
    $$PWD/include/GL/freeglut_std.h \
    $$PWD/include/GL/freeglut_ucall.h \
    $$PWD/include/GL/glut.h

CONFIG(debug, debug | release) {
    LIBS += -L$$PWD/lib/debug -lfreeglut_staticd
    LIBS += -L$$PWD/lib/debug -lfreeglutd
}

CONFIG(release, debug | release) {
    LIBS += -L$$PWD/lib/release -lfreeglut_static
    LIBS += -L$$PWD/lib/release -lfreeglut
}
