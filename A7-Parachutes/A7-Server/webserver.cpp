#include "webserver.h"

WebServer::WebServer(QString configFile, QObject *parent)
    : QObject(parent)
{
    // Get server settings from ini config file:
    docrootSettings = new QSettings(configFile, QSettings::IniFormat);
    docrootSettings->beginGroup("docroot");
    listenerSettings = new QSettings(configFile, QSettings::IniFormat);
    listenerSettings->beginGroup("listener");

    // Create a static file controller.
    // This file controller just distributes files from a given directory
    staticFC = new StaticFileController(docrootSettings, parent);

    // Create and start the listener that listens for Http connections:aa
    httpListener = new HttpListener(listenerSettings, staticFC, parent);

    // Create a web request handler and start listening.
//    listenerSettings->beginGroup("listener");
//    new HttpListener(listenerSettings, new WebRequestHandler(parent), parent);
}

WebServer::~WebServer()
{
    delete docrootSettings;
    delete listenerSettings;
    delete staticFC;
    delete httpListener;
}
