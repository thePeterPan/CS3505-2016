#-------------------------------------------------
#
# Project created by QtCreator 2016-04-13T09:21:51
#
#-------------------------------------------------

QT       += core gui websockets

QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = A7-Parachutes
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    Trie/Node.cpp \
    Trie/Trie.cpp \
    echoclient.cpp

HEADERS  += mainwindow.h \
    Trie/Node.h \
    Trie/Trie.h \
    echoclient.h

FORMS    += mainwindow.ui
