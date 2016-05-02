#include "networking.h"

Networking::Networking(QString configFile, QObject *parent)
    : url(), debug(true), QObject(parent)
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
    connect(&webSocket, &QWebSocket::disconnected, this, &Networking::socketClosed);
    connect(&webSocket, static_cast<void(QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error),
            [=](QAbstractSocket::SocketError error) {
            if (debug)
                qDebug() << "Error:" << error;
        });

    webSocket.open(QUrl(url));
}

Networking::~Networking() {}

/*!
 * \brief Sends a request to the server for the list of words.
 * \param teacher
 * \param listName
 */
void Networking::requestWordList(QString teacher, int level)
{
    QJsonObject requestObject;
    requestObject["requestType"] = WordList;
    requestObject["teacher"] = teacher;
    requestObject["level"] = level;

    QJsonDocument requestDocument(requestObject);
    webSocket.sendTextMessage(requestDocument.toJson(QJsonDocument::Compact));
}

void Networking::requestNextList(int level, QString teacher)
{
    requestWordList(teacher,level);
}

void Networking::requestWriteNewScore(QString username, int level, int score)
{
    QJsonObject requestObject;
    qDebug() << "writing";
    requestObject["requestType"] = NewScoreLevel;
    requestObject["username"] = username;
    requestObject["score"] = score;
    requestObject["level"] = level;

    QJsonDocument requestDocument(requestObject);
    webSocket.sendTextMessage(requestDocument.toJson(QJsonDocument::Compact));
}

void Networking::requestWriteNewUser(QString username, QString first, QString last, QString password, QString teacher)
{
    QJsonObject requestObject;
    requestObject["requestType"] = Signup;
    requestObject["username"] = username;
    requestObject["firstName"] = first;
    requestObject["lastName"] = last;
    requestObject["password"] = password;
    requestObject["teacher"] = teacher;

    QJsonDocument requestDocument(requestObject);
    webSocket.sendTextMessage(requestDocument.toJson(QJsonDocument::Compact));
}

void Networking::requestIsTeacher(QString teacher)
{
    QJsonObject requestObject;
    requestObject["requestType"] = IsTeacher;
    requestObject["username"] = teacher;

    QJsonDocument requestDocument(requestObject);
    webSocket.sendTextMessage(requestDocument.toJson(QJsonDocument::Compact));
}

void Networking::requestNameAvailable(QString username)
{
    QJsonObject requestObject;
    requestObject["requestType"] = UsernameCheck;
    requestObject["username"] = username;

    QJsonDocument requestDocument(requestObject);
    webSocket.sendTextMessage(requestDocument.toJson(QJsonDocument::Compact));
}

///
/// \brief sends a request to the server to check if the login was successful
/// \param username
/// \param password
///
void Networking::requestLogin(QString username, QString password)
{
    QJsonObject requestObject;
    requestObject["requestType"] = Login;
    requestObject["username"] = username;
    requestObject["password"] = password;

    QJsonDocument requestDocument(requestObject);
    webSocket.sendTextMessage(requestDocument.toJson(QJsonDocument::Compact));
}

void Networking::requestUserInfo(QString username)
{
    QJsonObject requestObject;
    requestObject["requestType"] = UserInfo;
    requestObject["username"] = username;
    QJsonDocument requestDocument(requestObject);
    webSocket.sendTextMessage(requestDocument.toJson(QJsonDocument::Compact));
}

/////////////////////////////////
///////////// SLOTS /////////////
/////////////////////////////////

/*!
 * \brief Networking::onConnected
 */
void Networking::onConnected()
{
    if (debug)
        qDebug() << "WebSocket connected to server:" << url;

    // Start listening for a message from the server:
    connect(&webSocket, &QWebSocket::textMessageReceived, this, &Networking::onTextMessageReceived);
    connect(&webSocket, &QWebSocket::binaryMessageReceived, this, &Networking::onBinaryMessageReceived);

//    webSocket.sendTextMessage("Client: test");
}

/*!
 * \brief Networking::onTextMessageReceived
 * \param message
 */
void Networking::onTextMessageReceived(QString message)
{
    if (debug)
        qDebug() << "Text message received" << message;

    // Convert the received message to a json document:
    QJsonDocument receivedDocument = QJsonDocument::fromJson(message.toUtf8());
    if (receivedDocument.isObject())
    {
        // convert the document to a json object:
        QJsonObject receivedObject = receivedDocument.object();
        for (QJsonObject::iterator itr = receivedObject.begin(); itr != receivedObject.end(); ++itr)
        {
            if (itr.key() == "wordList")
            {
                if (debug)
                    qDebug() << "wordList is found";
                QJsonArray wordList = itr.value().toObject()["list"].toArray();
                QList<QString> result = getWordList(wordList);
                emit newList(result);
            }
            else if (itr.key() == "userAccess")
            {
                if (debug)
                    qDebug() << "userAccess is found";
                QString username = itr.value().toObject()["username"].toString();
                bool loginSuccess = itr.value().toObject()["accessGranted"].toBool();
                bool isTeacher = itr.value().toObject()["isTeacher"].toBool();
                emit loginSuccessSignal(username,loginSuccess,isTeacher);
            }
            else if (itr.key() == "userInfo")
            {
                if(debug)
                    qDebug() << "userInfo is found";
                QString username = itr.value().toObject()["username"].toString();
                QString nameF = itr.value().toObject()["first"].toString();
                QString nameL = itr.value().toObject()["last"].toString();
                QString teacher = itr.value().toObject()["teacher"].toString();
                int level = itr.value().toObject()["level"].toInt();
                int highScore = itr.value().toObject()["highScore"].toInt();

                emit sendUserInfo(username, nameF, nameL, teacher, level, highScore);
                emit sendCurrentScore(username, level, highScore);
            }
            else if (itr.key() == "teacherList")
            {

            }
            else if (itr.key() == "usernameIsAvailable")
            {
                bool available = itr.value().toBool();
                emit sendUsernameAvailable(available);
            }else if (itr.key() == "accessGranted")
            {

            }else if (itr.key() == "gameOver")
            {

            }else if (itr.key() == "error")
            {

            }else if (itr.key() == "isTeacher")
            {
                bool isTeacher = itr.value().toObject()["isTeacher"].toBool();
                if(!isTeacher)
                    qDebug() << "not a teacher";
                else
                    qDebug() << "is a teacher";
                emit sendIsTeacher(isTeacher);
            }
        }
    } else {
        Q_EMIT receiveError(message);
        if (debug)
            qDebug() << "Error! Unkown JSON Object:" << message;
        // TODO: Send error message to server
    }
}

QList<QString> Networking::getWordList(QJsonArray &array)
{
    QList<QString> result;
    for(QJsonValue value : array)
    {
        result.push_back(value.toString());
    }
    return result;
}

/*!
 * \brief Networking::onBinaryMessageReceived
 * \param data
 */
void Networking::onBinaryMessageReceived(QByteArray data)
{
    if (debug)
        qDebug() << "Binary message received" << data;
}

/*!
 * \brief Prints out the first dimension of the json object for debugging.
 * \param json
 */
void Networking::printJsonObject(QJsonObject &json)
{
    qDebug() << "---------------------JSON Object------------------------";
    for(QJsonObject::iterator itr = json.begin(); itr != json.end(); ++itr)
    {
        qDebug() << "key:" << itr.key();
        qDebug() << "value:" << itr.value();
    }
    qDebug() << "--------------------------------------------------------";
}

void Networking::printJsonArray(QJsonArray &array)
{
    qDebug() << "---------------------JSON Array-------------------------";
    for(QJsonValue value : array)
    {
        qDebug() << "value: " << value.toString();
    }
    qDebug() << "--------------------------------------------------------";
}

/*!
 * \brief Used to test sending JSON documents between client and server.
 * \param message
 */
void Networking::testJson(QString message)
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
}

void Networking::requestCurrentHighScore(QString username){
    QJsonObject requestObject;
    requestObject["requestType"] = UserInfo;
    requestObject["username"] = username;

    QJsonDocument requestDocument(requestObject);
    webSocket.sendTextMessage(requestDocument.toJson(QJsonDocument::Compact));
}
