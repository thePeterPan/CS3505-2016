#-------------------------------------------------
#
# Project created by QtCreator 2016-03-09T11:05:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = A6-SpriteEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    editor_model.cpp \
    sprite.cpp \
    frame.cpp

HEADERS  += mainwindow.h \
    editor_model.h \
    sprite.h \
    frame.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
