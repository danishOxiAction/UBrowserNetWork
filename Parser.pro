#-------------------------------------------------
#
# Project created by QtCreator 2016-10-18T22:28:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += console

TARGET = Parser
TEMPLATE = app


SOURCES += main.cpp\
        htmlparser.cpp \
    tree.cpp

HEADERS  += htmlparser.h \
    tree.h
