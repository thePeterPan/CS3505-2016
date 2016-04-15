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
    A7-Server.ini

include(QtWebApp/QtWebApp.pro)

contains($$PWD, $$OUT_PWD) { } else {
    # Source: http://stackoverflow.com/questions/19066593/copy-a-file-to-build-directory-after-compiling-project-with-qt
    # Source: http://dragly.org/2013/11/05/copying-data-files-to-the-build-directory-when-working-with-qmake/
    copyini.commands = $(COPY_DIR) $$PWD/*.ini $$OUT_PWD
    copydocroot.commands = $(COPY_DIR) $$PWD/docroot $$OUT_PWD
    first.depends = $(first) copyini copydocroot
    export(first.depends)
    export(copyini.commands)
    export(copydocroot.commands)
    QMAKE_EXTRA_TARGETS += first copyini copydocroot
}
