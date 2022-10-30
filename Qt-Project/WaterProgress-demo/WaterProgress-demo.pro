QT += core gui dtkwidget

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WaterProgress-demo
TEMPLATE = app

SOURCES += \
        main.cpp \
    waterprogress.cpp \
    widget.cpp \
    utils.cpp

RESOURCES +=         resources.qrc

FORMS += \
    widget.ui

HEADERS += \
    waterprogress.h \
    widget.h \
    utils.h
