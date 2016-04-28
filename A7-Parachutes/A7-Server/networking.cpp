#include "networking.h"

Networking::Networking(QString configFile, QObject *parent)
    : QObject(parent),
      webSocketServer(new QWebSocketServer(QStringLiteral("Neverland Server"), QWebSocketServer::NonSecureMode, this)),
      clients(),
      debug()
{
    // Read in the settings for the socket from the ini file.
    QSettings* socketSettings = new QSettings(configFile, QSettings::IniFormat);
    socketSettings->beginGroup("socket");
    int port = socketSettings->value("port", 8081).toInt();
    debug = socketSettings->value("debug", false).toBool();

    // Listen on all network interfaces on the specified port.
    if (webSocketServer->listen(QHostAddress::Any, port)) {
        if (debug)
            qDebug() << "Socket Server listening on address" << webSocketServer->serverUrl().url();
        connect(webSocketServer, &QWebSocketServer::newConnection, this, &Networking::onNewConnection);
        connect(webSocketServer, &QWebSocketServer::closed, this, &Networking::closed);

        openConnectionToDatabase(configFile);
    } else {
        if (debug) {
            qDebug() << "Error starting socket server on" << webSocketServer->serverUrl().url();
            qDebug() << "Trying again.";
        }
        // If unable to connect on the specified port, automatically choose a port.
        if (webSocketServer->listen(QHostAddress::Any)) {
            if (debug) {
                qDebug() << "Socket Server listening on address" << webSocketServer->serverUrl().url();
            }
            connect(webSocketServer, &QWebSocketServer::newConnection, this, &Networking::onNewConnection);
            connect(webSocketServer, &QWebSocketServer::closed, this, &Networking::closed);

            openConnectionToDatabase(configFile);
        } else {
            if (debug) {
                qDebug() << "Unable to launch socket server.";
                Q_EMIT closed();
            }
        }
    }
}

Networking::~Networking()
{
    webSocketServer->close();
    qDeleteAll(clients.begin(), clients.end());
}

/////////////////////////////////
///////////// SLOTS /////////////
/////////////////////////////////

void Networking::onNewConnection()
{
    QWebSocket *socket = webSocketServer->nextPendingConnection();

    if (debug)
        qDebug() << "Socket connected:" << socket;

    connect(socket, &QWebSocket::textMessageReceived, this, &Networking::processTextMessage);
    connect(socket, &QWebSocket::binaryMessageReceived, this, &Networking::processBinaryMessage);
    connect(socket, &QWebSocket::disconnected, this, &Networking::socketDisconnected);

    // Add the newly connected socket to the list of clients.
    clients << socket;
}

/*!
 * \brief Processes the \a message received and sent by the client.
 * \param message
 * \sa processBinaryMessage
 */
void Networking::processTextMessage(QString message)
{
    // Get the QWebSocket that sent the signal
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    if (debug)
        qDebug() << "Message received:" << message;

    // If the socket is valid and still open
    if (client)
    {
        // Create a QJsonDocument from the received string so we can parse it:
        QJsonDocument receivedDocument = QJsonDocument::fromJson(message.toUtf8());
        // Make sure the message contains a Json Object
        if (receivedDocument.isObject())
        {
            // Convert the document to a QJsonObject:
            QJsonObject receivedObject = receivedDocument.object();
            // Look at what the client has requested through the message:
            RequestType request = RequestType(qRound(receivedObject["requestType"].toDouble()));

            if (debug)
                printJsonObject(receivedObject);

            if (request == WordList)
            {
                // Make sure the two needed key/values exist
                if (receivedObject.contains("teacher") && receivedObject.contains("level"))
                {
                    QJsonObject wordList;
                    // Write the list of words to the wordList QJsonObject
                    writeWordList(receivedObject["teacher"].toString(), receivedObject["listName"].toString(), 00000, wordList);
                    // Convert the QJsonObject to a QJsonDocument:
                    QJsonDocument responseDocument(wordList);
                    // Send the response message
                    client->sendTextMessage(responseDocument.toJson(QJsonDocument::Compact));
                } else {
                    if (debug)
                        qDebug() << "Error! Unknown JSON Document:" << message;
                    //
                }
            }
        } else {
            if (debug)
                qDebug() << "Error! Unknown JSON Document:" << message;
            // TODO: Send error message to client.
        }

//        client->sendTextMessage(message);
//        client->sendTextMessage(testJson());
    }
}

void Networking::processBinaryMessage(QByteArray message)
{
    // Get the QWebSocket that sent the signal
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    if (debug)
        qDebug() << "Binary Message received:" << message;
    // If the socket is valid and still open, send the message.
    if (client)
    {
//        client->sendBinaryMessage(message);
    }
}

void Networking::socketDisconnected()
{
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    if (debug)
        qDebug() << "Socket Disconnected:" << client;
    if (client)
    {
        clients.removeAll(client);
        client->deleteLater();
    }
}

///////////////////////////////////
///////////// PRIVATE /////////////
///////////////////////////////////

/*!
 * \brief Networking::openConnectionToDatabase
 */
void Networking::openConnectionToDatabase(QString configFile)
{
    QSettings* dbSettings = new QSettings(configFile, QSettings::IniFormat);
    dbSettings->beginGroup("database");
    db = new MySQLWrapper();
    db->setHost(dbSettings->value("host").toString().toStdString().c_str());
    db->setUsername(dbSettings->value("username").toString().toStdString().c_str());
    db->setPassword(dbSettings->value("password").toString().toStdString().c_str());
    db->setDatabaseName(dbSettings->value("schema").toString().toStdString().c_str());
    db->open();
}

/*!
 * \brief Queries the database for the list of words.
 * \return
 */
void Networking::writeWordList(QString teacher, QString listName, int level, QJsonObject &json)
{
    // Create root JSON Object:
    QJsonObject jsonWordList;

    // Add the key "name" and its value.
    jsonWordList["name"] = listName;

    // Query the database for a list of words:
    QList<QString> wordList = db->getTeacherWordsByLevel(teacher, level);
    // Add the words to the list of words:
    QJsonArray wordArray;
    for (QString word : wordList)
    {
        wordArray.append(word);
    }
    // Add the key "list" and its value is the array.
    jsonWordList["list"] = wordArray;

    // Add the root JSON object to the given JSON object.
    json["wordList"] = jsonWordList;
}

/*!
 * \brief Prints out the first dimension of the json object for debugging.
 * \param json
 */
void Networking::printJsonObject(QJsonObject &json)
{
    qDebug() << "---------------------JSON Object------------------------";
    /// Three different ways of looping through a QJsonObject:
//    for(QJsonValue value : json)
//    {
//        qDebug() << value;
//    }
//    Q_FOREACH(const QJsonValue &value, json)
//    {
//        qDebug() << value;
//    }
    for(QJsonObject::iterator itr = json.begin(); itr != json.end(); ++itr)
    {
        qDebug() << "key:" << itr.key();
        qDebug() << "value:" << itr.value();
    }
    qDebug() << "--------------------------------------------------------";
}


/*!
 * \brief Used to test sending JSON documents between client and server.
 * \return a compact json string.
 */
QString Networking::testJson()
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

    // incase of string value get value and convert into string
    qWarning() << tr("QJsonObject[appName] of description: ") << item["description"];
    qDebug() << "--------------------------------------------------------";
    QJsonValue subObject = item["description"];
    qWarning() << subObject.toString();
    qDebug() << "--------------------------------------------------------";

    // incase of array get array and convert into string
    qWarning() << tr("QJsonObject[appName] of value: ") << item["imp"];
    qDebug() << "--------------------------------------------------------";
    QJsonArray subArray = item["imp"].toArray();
    qWarning() << subArray[1].toString();

    qDebug() << "-------------------------------------------------------------------------------------";

    return document.toJson(QJsonDocument::Compact);
    // http://stackoverflow.com/questions/15893040/how-to-create-read-write-json-files-in-qt5
    // http://stackoverflow.com/questions/28181627/how-to-convert-a-qjsonobject-to-qstring
}
