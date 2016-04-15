QT += core network # websockets
QT -= gui

CONFIG += c++11

TARGET = A7-Server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
#    echoserver.cpp \
    tcpserver.cpp \
    webrequesthandler.cpp

HEADERS += \
#    echoserver.h \
    tcpserver.h \
    webrequesthandler.h

DISTFILES += \
    index.html \
    echoclient.html \
    configfile.ini

include(QtWebApp/QtWebApp.pro)
