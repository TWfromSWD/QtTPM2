#-------------------------------------------------
#
# Project created by QtCreator 2015-11-11T22:23:54
#
#-------------------------------------------------

QT       += core gui
QT       += network

TARGET = qttpm2
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    tpm2_net.cpp

HEADERS += \
    tpm2_net.h \
    tpm2_constants.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
