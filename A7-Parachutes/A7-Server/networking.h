#ifndef NETWORKING_H
#define NETWORKING_H

#include <QObject>
#include <QList>
#include <QByteArray>
#include <QSettings>
#include <QDebug>
#include <QFile>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

//#include <QtWebSockets/QWebSocketServer>
#include "QtWebSockets/qwebsocketserver.h"
//#include <QtWebSockets/QWebSocket>
#include "QtWebSockets/qwebsocket.h"

class Networking : public QObject
{
    Q_OBJECT
public:
    explicit Networking(QString configFile, QObject *parent = Q_NULLPTR);
    ~Networking();

    QString getJsonDocument();

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

private:
    QWebSocketServer *webSocketServer;
    QList<QWebSocket *> clients;
    bool debug;
};

#endif // NETWORKING_H
