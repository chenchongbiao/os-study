QT       += core dbus


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = server
TEMPLATE    = app

HEADERS += \
    server.h

SOURCES += \
    server.cpp \
    main.cpp
