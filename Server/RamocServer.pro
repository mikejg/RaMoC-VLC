#-------------------------------------------------
#
# Project created by QtCreator 2017-04-23T20:08:39
#
#-------------------------------------------------

QT       += core gui network sql dbus phonon4qt5

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RamocServer
target.path = /usr/bin/
INSTALLS += target

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -Wno-reorder

SOURCES += database.cpp\
        insertMovies.cpp\
        lastfm.cpp\
        log.cpp\
        main.cpp\
        mainwindow.cpp\
        vlc_process.cpp\
        server.cpp\
        socket.cpp\
        player.cpp\
        omx_process.cpp

HEADERS  += constants.h\
            database.h\
            insertMovies.h\
            lastfm.h\
            log.h\
            mainwindow.h\
            vlc_process.h\
            server.h\
            socket.h\
            player.h\
            omx_process.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
LIBS += -L/usr/lib \
    -ltag
LIBS += -L/usr/lib \
    -lqjson
INCLUDEPATH += /usr/include/taglib
