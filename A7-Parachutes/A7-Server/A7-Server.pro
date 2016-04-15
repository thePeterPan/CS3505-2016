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

# Source: http://stackoverflow.com/questions/19066593/copy-a-file-to-build-directory-after-compiling-project-with-qt
# Source: http://dragly.org/2013/11/05/copying-data-files-to-the-build-directory-when-working-with-qmake/
copyini.commands = $(COPY_DIR) $$PWD/*.ini $$OUT_PWD
copyhtml.commands = $(COPY_DIR) $$PWD/*.html $$OUT_PWD
first.depends = $(first) copyini copyhtml
export(first.depends)
export(copyini.commands)
export(copyhtml.commands)
QMAKE_EXTRA_TARGETS += first copyini copyhtml
