QT += core gui dtkwidget

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cmd-helper
TEMPLATE = app

SOURCES += \
        main.cpp \
    mainwindow.cpp \
    bqtextbrowser.cpp

RESOURCES +=         resources.qrc

FORMS += \
    mainwindow.ui \
    bqtextbrowser.ui

HEADERS += \
    mainwindow.h \
    bqtextbrowser.h
