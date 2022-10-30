QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = QDBusServer
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

FORMS += \
    $$PWD/qdbusserver.ui

HEADERS += \
    $$PWD/qdbusserver.h \
    $$PWD/minfointerfaceinterface.h

SOURCES += \
    $$PWD/qdbusserver.cpp \
    $$PWD/minfointerfaceinterface.cpp \
    $$PWD/main.cpp
