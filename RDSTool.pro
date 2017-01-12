#-------------------------------------------------
#
# Project created by QtCreator 2016-12-30T16:05:02
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = RDSTool
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11

TEMPLATE = app


SOURCES += main.cpp \
    datatranslator.cpp \
    settings.cpp \
    xmlhandler.cpp

HEADERS += \
    datatranslator.h \
    settings.h \
    easylogging++.h \
    xmlhandler.h
