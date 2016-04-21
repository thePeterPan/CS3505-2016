#include "networking.h"

Networking::Networking(QString configFile, QObject *parent)
    : url(), debug(false), QObject(parent)
{
    QSettings* socketSettings = new QSettings(configFile, QSettings::IniFormat);
    socketSettings->beginGroup("socket");
    // Get the settings from the ini file.
    QString scheme = socketSettings->value("scheme", QString("ws")).toString();
    QString host = socketSettings->value("host", QString("localhost")).toString();
    int port = socketSettings->value("port", 8081).toInt();
    // Set the url to connect to
    url.setScheme(scheme);
    url.setHost(host);
    url.setPort(port);

    debug = socketSettings->value("debug", false).toBool();

    if (debug)
        qDebug() << "Attempting to connect to:" << url;

    connect(&webSocket, &QWebSocket::connected, this, &Networking::onConnected);
    connect(&webSocket, &QWebSocket::disconnected, this, &Networking::closed);
    connect(&webSocket, static_cast<void(QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error),
            [=](QAbstractSocket::SocketError error) {
            if (debug)
                qDebug() << "Error:" << error;
        });

    webSocket.open(QUrl(url));
}

void Networking::onConnected()
{
    if (debug)
        qDebug() << "WebSocket connected to server:" << url;

    // Start listening for a message from the server:
    connect(&webSocket, &QWebSocket::textMessageReceived, this, &Networking::onTextMessageReceived);
    connect(&webSocket, &QWebSocket::binaryMessageReceived, this, &Networking::onBinaryMessageReceived);

}

void Networking::onTextMessageReceived(QString message)
{

}

void Networking::onBinaryMessageReceived(QByteArray data)
{

}
