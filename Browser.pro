#-------------------------------------------------
#
# Project created by QtCreator 2016-10-20T18:38:53
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Browser
TEMPLATE = app


SOURCES += main.cpp \
    exceptions.cpp \
    logs.cpp \
    parser.cpp \
    tree.cpp \
    Kernel/http_request.cpp \
    Forms/mainwindow.cpp \
    Forms/tab.cpp

HEADERS  += \
    exceptions.h \
    logs.h \
    node.h \
    parser.h \
    tree.h \
    Kernel/http_request.h \
    Forms/mainwindow.h \
    Forms/tab.h

FORMS += \
    Forms/mainwindow.ui \
    Forms/tab.ui
