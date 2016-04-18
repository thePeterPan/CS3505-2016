QT += core network
QT -= gui

CONFIG += c++11

TARGET = A7-Server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    echoserver.cpp \
    tcpserver.cpp \
    webrequesthandler.cpp

HEADERS += \
    echoserver.h \
    tcpserver.h \
    webrequesthandler.h

DISTFILES += \
    index.html \
    echoclient.html \
    A7-Server.ini

include(QtWebApp/QtWebApp.pro)

# If building on travis, add "CONFIG+=travis" to qmake command options.
# This is a hack to prevent travis build errors because the COPY_DIR command below
# causes errors when it copies files into the exact same directory.
!travis {
    # Source: http://stackoverflow.com/questions/19066593/copy-a-file-to-build-directory-after-compiling-project-with-qt
    # Source: http://dragly.org/2013/11/05/copying-data-files-to-the-build-directory-when-working-with-qmake/
    # Windows copy issues: http://stackoverflow.com/questions/18860769/how-reference-qt-creator-current-build-directory-from-qt-project-file
    copyini.commands = $(COPY_DIR) $$system_path($$PWD/"$$TARGET".ini) $$system_path($$OUT_PWD)
    copydocroot.commands = $(COPY_DIR) $$system_path($$PWD/docroot) $$system_path($$OUT_PWD/docroot)
    first.depends = $(first) copyini copydocroot
    export(first.depends)
    export(copyini.commands)
    export(copydocroot.commands)
    QMAKE_EXTRA_TARGETS += first copyini copydocroot
}

win32|macx {
    QT += websockets
}
unix:!macx {
    include(QtWebSockets/websockets.pro)
}
