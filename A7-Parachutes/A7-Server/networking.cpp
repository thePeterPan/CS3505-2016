#include "networking.h"

Networking::Networking(QString configFile, QObject *parent)
    : QObject(parent),
      webSocketServer(new QWebSocketServer(QStringLiteral("Neverland Server"), QWebSocketServer::NonSecureMode, this)),
      clients(),
      debug()
{
    QSettings* socketSettings = new QSettings(configFile, QSettings::IniFormat);
    socketSettings->beginGroup("socket");
    int port = socketSettings->value("port", 8081).toInt();
    debug = socketSettings->value("debug", false).toBool();

    if (webSocketServer->listen(QHostAddress::Any, port)) {
        if (debug)
            qDebug() << "Socket Server listening on port:" << port;
        connect(webSocketServer, &QWebSocketServer::newConnection, this, &Networking::onNewConnection);
        connect(webSocketServer, &QWebSocketServer::closed, this, &Networking::closed);
    }
}

Networking::~Networking()
{
    webSocketServer->close();
    qDeleteAll(clients.begin(), clients.end());
}

void Networking::onNewConnection()
{
    QWebSocket *socket = webSocketServer->nextPendingConnection();
    if (debug)
        qDebug() << "Socket connected:" << socket;

    connect(socket, &QWebSocket::textMessageReceived, this, &Networking::processTextMessage);
    connect(socket, &QWebSocket::binaryMessageReceived, this, &Networking::processBinaryMessage);
    connect(socket, &QWebSocket::disconnected, this, &Networking::socketDisconnected);

    clients << socket;
}

void Networking::processTextMessage(QString message)
{
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    if (debug)
        qDebug() << "Message received:" << message;
    if (client)
    {
        client->sendTextMessage(message);
    }
}

void Networking::processBinaryMessage(QByteArray message)
{
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    if (debug)
        qDebug() << "Binary Message received:" << message;
    if (client)
    {
        client->sendBinaryMessage(message);
    }
}

void Networking::socketDisconnected()
{
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    if (debug)
    {
        clients.removeAll(client);
        client->deleteLater();
    }
}
