#-------------------------------------------------
#
# Project created by QtCreator 2016-02-25T21:14:14
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Assignment5-BinarySimon
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    game_model.cpp

HEADERS  += mainwindow.h \
    game_model.h

FORMS    += mainwindow.ui

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/E:/msvc2013_64/lib/ -llibEGL
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/E:/msvc2013_64/lib/ -llibEGLd

#INCLUDEPATH += $$PWD/E:/msvc2013_64/include
#DEPENDPATH += $$PWD/E:/msvc2013_64/include

