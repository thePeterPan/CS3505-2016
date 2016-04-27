#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <QObject>
#include <QSettings>

#include "staticfilecontroller.h"
#include "httplistener.h"

class WebServer : public QObject
{
    Q_OBJECT
public:
    explicit WebServer(QString configFile, QObject *parent = 0);
    ~WebServer();

signals:

public slots:

private:
    bool debug;

    QSettings* docrootSettings;
    QSettings* listenerSettings;
    StaticFileController* staticFC;
    HttpListener* httpListener;
};

#endif // WEBSERVER_H
