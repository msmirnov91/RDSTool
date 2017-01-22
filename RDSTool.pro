#-------------------------------------------------
#
# Project created by QtCreator 2016-12-30T16:05:02
#
#-------------------------------------------------

QT       += core

QT       -= gui

QT       += network

TARGET = RDSTool
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11

TEMPLATE = app


SOURCES += main.cpp \
    settings.cpp \
    datahandler.cpp

HEADERS += \
    settings.h \
    easylogging++.h \
    datahandler.h
