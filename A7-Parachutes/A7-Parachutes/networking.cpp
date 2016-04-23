#include "networking.h"

Networking::Networking(QString configFile, QObject *parent)
    : url(), debug(false), QObject(parent)
{
    // Get the settings from the ini file.
    QSettings* socketSettings = new QSettings(configFile, QSettings::IniFormat);
    socketSettings->beginGroup("socket");
    QString scheme = socketSettings->value("scheme", QString("ws")).toString();
    QString host = socketSettings->value("host", QString("localhost")).toString();
    int port = socketSettings->value("port", 8081).toInt();
    debug = socketSettings->value("debug", false).toBool();

    // Set the url to connect to
    url.setScheme(scheme);
    url.setHost(host);
    url.setPort(port);

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

Networking::~Networking() {}

void Networking::onConnected()
{
    if (debug)
        qDebug() << "WebSocket connected to server:" << url;

    // Start listening for a message from the server:
    connect(&webSocket, &QWebSocket::textMessageReceived, this, &Networking::onTextMessageReceived);
    connect(&webSocket, &QWebSocket::binaryMessageReceived, this, &Networking::onBinaryMessageReceived);

    webSocket.sendTextMessage("Client: test");
}

void Networking::onTextMessageReceived(QString message)
{
    qDebug() << "Message Received:" << message;

    QJsonDocument document = QJsonDocument::fromJson(message.toUtf8());

    qDebug() << "-------------------------------------------------------------------------------------";

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
}

void Networking::onBinaryMessageReceived(QByteArray data)
{
    qDebug() << "Binary message received" << data;
}
