QT += core gui dtkwidget sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sqlite-demo
TEMPLATE = app

SOURCES += \
        main.cpp \
    widget.cpp \
    model/container.cpp \
    mapper/containermapper.cpp \
    utils/stringutils.cpp

RESOURCES +=         resources.qrc

FORMS += \
    widget.ui

HEADERS += \
    widget.h \
    model/container.h \
    mapper/containermapper.h \
    utils/stringutils.h
