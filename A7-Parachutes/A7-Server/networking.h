#ifndef NETWORKING_H
#define NETWORKING_H

#include <QObject>
#include <QList>
#include <QByteArray>
#include <QSettings>
#include <QDebug>

//QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
//QT_FORWARD_DECLARE_CLASS(QWebSocket)
#include "QtWebSockets/QWebSocketServer"
#include "QtWebSockets/QWebSocket"

class Networking : public QObject
{
    Q_OBJECT
public:
    explicit Networking(QString configFile, QObject *parent = Q_NULLPTR);
    ~Networking();

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
