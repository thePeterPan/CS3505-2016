#include "networking.h"

Networking::Networking(const QUrl &url_, bool debug_, QObject *parent)
    : url(url_), debug(debug_), QObject(parent)
{
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
