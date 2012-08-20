PROJECTNAME = Route Me

TARGET = routeme

TEMPLATE = app

QT += declarative network

INCLUDEPATH = .
DESTDIR = ../

CONFIG += mobility
MOBILITY += location

HEADERS += \
    routegeomap.h \
    routemapitem.h \
    routeme.h \
    routemeserver.h \
    serviceprovider.h \
    routepositioninfo.h \
    routecoordinateitem.h

SOURCES += \
    routegeomap.cpp \
    routemapitem.cpp \
    routeme.cpp \
    routemeserver.cpp \
    serviceprovider.cpp \
    routepositioninfo.cpp \
    routecoordinateitem.cpp \
    main.cpp

RESOURCES += qml.qrc

contains(MEEGO_EDITION, harmattan) {
    DEFINES += MEEGO_EDITION_HARMATTAN
    target.path = /opt/src/bin
}

INSTALLS += target

OTHER_FILES += \
    qml/*
