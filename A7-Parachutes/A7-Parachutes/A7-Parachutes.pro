#-------------------------------------------------
#
# Project created by QtCreator 2016-04-13T09:21:51
#
#-------------------------------------------------

QT       += core gui multimedia

CONFIG += c++11

#QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = A7-Parachutes
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    Trie/Node.cpp \
    Trie/Trie.cpp \
    leveldialog.cpp \
    gamewindow.cpp \
    sprite.cpp \
    temporarysprite.cpp \
    networking.cpp \
    windowcontroller.cpp \
    gamelogic.cpp \
    registrationdialog.cpp

HEADERS  += mainwindow.h \
    Trie/Node.h \
    Trie/Trie.h \
    leveldialog.h \
    gamewindow.h \
    sprite.h \
    temporarysprite.h \
    networking.h \
    windowcontroller.h \
    gamelogic.h \
    registrationdialog.h

FORMS    += mainwindow.ui \
    leveldialog.ui \
    registrationDialog.ui \
    gamewindow.ui


########## Box2D

include(Box2D/Box2D.pro)

########## QtWebSockets

win32|macx {
    QT += websockets
}
unix:!macx {
    include(QtWebSockets/websockets.pro)
}

RESOURCES += \
    resources.qrc

