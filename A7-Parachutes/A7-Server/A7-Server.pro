QT += core websockets
QT -= gui

CONFIG += c++11

TARGET = A7-Server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    echoserver.cpp

HEADERS += \
    echoserver.h

DISTFILES += \
    echoclient.html
