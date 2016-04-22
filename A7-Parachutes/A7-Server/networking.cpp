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
//        client->sendTextMessage(message);
        client->sendTextMessage(getJsonDocument());
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

QString Networking::getJsonDocument()
{
    qDebug() << "-------------------------------------------------------------------------------------";

    QFile file(":/sample.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString jsonString = file.readAll();
    file.close();

    qWarning() << jsonString;
    qDebug() << "--------------------------------------------------------";

    QJsonDocument document = QJsonDocument::fromJson(jsonString.toUtf8());

    QJsonObject object = document.object();
    QJsonValue value = object.value(QString("appName"));

    qWarning() << value;
    qDebug() << "--------------------------------------------------------";

    QJsonObject item = value.toObject();

    qWarning() << tr("QJsonObject of descripiton: ") << item;
    qDebug() << "--------------------------------------------------------";

    /* incase of string value get value and convert into string*/
    qWarning() << tr("QJsonObject[appName] of description: ") << item["description"];
    qDebug() << "--------------------------------------------------------";
    QJsonValue subObject = item["description"];
    qWarning() << subObject.toString();
    qDebug() << "--------------------------------------------------------";

    /* incase of array get array and convert into string*/
    qWarning() << tr("QJsonObject[appName] of value: ") << item["imp"];
    qDebug() << "--------------------------------------------------------";
    QJsonArray subArray = item["imp"].toArray();
    qWarning() << subArray[1].toString();

    qDebug() << "-------------------------------------------------------------------------------------";

    return document.toJson(QJsonDocument::Compact);
    // http://stackoverflow.com/questions/15893040/how-to-create-read-write-json-files-in-qt5
    // http://stackoverflow.com/questions/28181627/how-to-convert-a-qjsonobject-to-qstring
}
