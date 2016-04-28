QT += core network
QT -= gui

CONFIG += c++11

TARGET = A7-Server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    mysqlwrapper.cpp \
    networking.cpp \
    webserver.cpp

HEADERS += \
    mysqlwrapper.h \
    networking.h \
    webserver.h

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
#    include(QtWebSockets/websockets.pro)
    QT += websockets
}

########## MySQL Connector

include(MySQL-Connector/MySQL-Connector.pro)

LIBS+=-ldl # got a build error, was told to put this here, fixed, don't know why.
# Also order matters: http://stackoverflow.com/questions/19901934/strange-linking-error-dso-missing-from-command-line

########## Boost

win32 {
    INCLUDEPATH += C:\boost
    LIBS += C:\boost\bin\boost\bin.v2\libs
}
