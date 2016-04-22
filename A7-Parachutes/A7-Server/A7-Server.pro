QT += core network
QT -= gui

CONFIG += c++11

TARGET = A7-Server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    tcpserver.cpp \
    webrequesthandler.cpp \
    mysqlwrapper.cpp \
    networking.cpp

HEADERS += \
    tcpserver.h \
    webrequesthandler.h \
    mysqlwrapper.h \
    networking.h

DISTFILES += \
    docroot/index.html \
    echoclient.html

RESOURCES += \
    resources.qrc

########## QtWebApp

include(QtWebApp/QtWebApp.pro)

# If building on travis, add "CONFIG+=travis" to qmake command options.
# This is a hack to prevent travis build errors because the COPY_DIR command below
# causes errors when it copies files into the exact same directory.
!travis {
    # Source: http://stackoverflow.com/questions/19066593/copy-a-file-to-build-directory-after-compiling-project-with-qt
    # Source: http://dragly.org/2013/11/05/copying-data-files-to-the-build-directory-when-working-with-qmake/
    # Windows copy issues: http://stackoverflow.com/questions/18860769/how-reference-qt-creator-current-build-directory-from-qt-project-file
#    copydocroot.commands = $(COPY_DIR) $$system_path($$PWD/docroot) $$system_path($$OUT_PWD/docroot)
#    first.depends = $(first) copydocroot
#    export(first.depends)
#    export(copydocroot.commands)
#    QMAKE_EXTRA_TARGETS += first copydocroot
#first: $(first) copyini copydocroot
#copyini:
#	$(COPY_DIR) /home/ppan/cs3505-github/A7-Parachutes/A7-Server/A7-Server.ini /home/ppan/cs3505-github/A7-Parachutes/build-A7-Server-Desktop-Debug
#copydocroot
#	$(COPY_DIR) /home/ppan/cs3505-github/A7-Parachutes/A7-Server/docroot /home/ppan/cs3505-github/A7-Parachutes/build-A7-Server-Desktop-Debug/docroot
}

########## QtWebSockets

win32|macx {
    QT += websockets
}
unix:!macx {
    include(QtWebSockets/websockets.pro)
}

########## MySQL Connector

INCLUDEPATH+=$$system_path($$PWD/MySQL-Connector/include)
unix:!macx {
    LIBS+=$$system_path($$PWD/MySQL-Connector/lib/unix/libmysqlcppconn-static.a)
}
win32 {
    # Not tested
    LIBS+=$$system_path($$PWD/MySQL-Connector/lib/win32/mysqlcppconn-static.lib)
}
macx {
    # not tested
    LIBS+=$$system_path($$PWD/MySQL-Connector/lib/macx/libmysqlcppconn-static.a)
}

LIBS+=-ldl # got a build error, was told to put this here, fixed, don't know why.
# Also order matters: http://stackoverflow.com/questions/19901934/strange-linking-error-dso-missing-from-command-line
