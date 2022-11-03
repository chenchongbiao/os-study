QT += core gui dtkwidget

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ListWidget-demo
TEMPLATE = app

SOURCES += \
        main.cpp \
    widget.cpp

RESOURCES +=         resources.qrc

FORMS += \
    widget.ui

HEADERS += \
    widget.h
