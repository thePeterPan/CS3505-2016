#Created By Boqian Yao Tue Apr 26, 2016.


TARGET = webServer
TEMPLATE = app
QT = core network
CONFIG += console

HEADERS += \
           src/requestmapper.h \


SOURCES += src/main.cpp \
           src/requestmapper.cpp \

#---------------------------------------------------------------------------------------
# The following lines include the sources of the QtWebAppLib library
#---------------------------------------------------------------------------------------
include(httpserver/httpserver.pri)

RESOURCES += \
    res.qrc

