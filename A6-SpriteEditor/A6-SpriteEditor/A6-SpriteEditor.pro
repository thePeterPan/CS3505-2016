#-------------------------------------------------
#
# Project created by QtCreator 2016-03-09T11:05:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = A6-SpriteEditor
TEMPLATE = app

DEFINES += QTCOLORWIDGETS_STATICALLY_LINKED


SOURCES += main.cpp\
        mainwindow.cpp \
    editor_model.cpp \
    sprite.cpp \
    frame.cpp \
    graphicsscene.cpp \
    newfiledialog.cpp \
    helpdialog.cpp \
    previewscene.cpp

HEADERS  += mainwindow.h \
    editor_model.h \
    sprite.h \
    frame.h \
    graphicsscene.h \
    newfiledialog.h \
    helpdialog.h \
    previewscene.h

FORMS    += mainwindow.ui \
    newfiledialog.ui \
    helpdialog.ui

RESOURCES += \
    resources.qrc

include(Qt-Color-Widgets/color_widgets.pri)
