#ifndef NETWORKING_H
#define NETWORKING_H

#include <QObject>
#include <QSettings>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include "QtWebSockets/qwebsocket.h"

class Networking : public QObject
{
    Q_OBJECT
public:
    explicit Networking(QString configFile, QObject *parent = 0);
    ~Networking();

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);
    void onBinaryMessageReceived(QByteArray data);

private:
    QWebSocket webSocket;
    QUrl url;
    bool debug;
};

#endif // NETWORKING_H
