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
    FtpUploader/ftpuploader.cpp \
    FtpUploader/ftpuploadersettings.cpp \
    FileMaker/filemaker.cpp \
    FileMaker/filemakersettings.cpp \
    TextReplacer/textreplacer.cpp \
    TextReplacer/textreplacersettings.cpp \
    mainsettings.cpp \
    data.cpp \
    Translator/translator.cpp

HEADERS += \
    easylogging++.h \
    FtpUploader/ftpuploader.h \
    FtpUploader/ftpuploadersettings.h \
    FileMaker/filemaker.h \
    FileMaker/filemakersettings.h \
    TextReplacer/textreplacer.h \
    TextReplacer/textreplacersettings.h \
    mainsettings.h \
    data.h \
    Translator/translator.h
