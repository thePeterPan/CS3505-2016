QT += core websockets network
QT -= gui

CONFIG += c++11

TARGET = A7-Server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    echoserver.cpp \
    tcpserver.cpp

HEADERS += \
    echoserver.h \
    tcpserver.h

DISTFILES += \
    echoclient.html \
    configfile.ini

include(QtWebApp/qtservice/qtservice.pri)
include(QtWebApp/httpserver/httpserver.pri)
include(QtWebApp/logging/logging.pri)
include(QtWebApp/templateengine/templateengine.pri)
