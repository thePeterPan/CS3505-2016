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

            if (debug)
                printJsonObject(receivedObject);

            if (receivedObject.contains("requestType"))
            {
                // Look at what the client has requested through the message:
                RequestType request = RequestType(qRound(receivedObject["requestType"].toDouble()));

                if (request == WordList)
                {
                    // Make sure the two needed key/values exist
                    if (receivedObject.contains("teacher") && receivedObject.contains("level"))
                    {
                        QJsonObject wordList;
                        // Write the list of words to the wordList QJsonObject
                        writeWordList(receivedObject["teacher"].toString(), receivedObject["level"].toInt(), wordList);
                        // Convert the QJsonObject to a QJsonDocument:
                        QJsonDocument responseDocument(wordList);
                        // Send the response message
                        client->sendTextMessage(responseDocument.toJson(QJsonDocument::Compact));
                    }
                    else
                    {
                        if (debug)
                            qDebug() << "Error! Invalid Word List:" << message;
                        //
                    }
                }
                else if (request == Login)
                {
                    if (receivedObject.contains("username") && receivedObject.contains("password"))
                    {
                        QJsonObject login;

                        writeLogin(receivedObject["username"].toString(), receivedObject["password"].toString(), login);

                        QJsonDocument responseDocument(login);

                        client->sendTextMessage(responseDocument.toJson(QJsonDocument::Compact));
                    }
                }
                else if (request == UsernameCheck)
                {
                    if (receivedObject.contains("username"))
                    {
                        QJsonObject loginAvailable;
                        writeLoginAvailable(receivedObject["username"].toString(), loginAvailable);
                        QJsonDocument responseDocument(loginAvailable);
                        client->sendTextMessage(responseDocument.toJson(QJsonDocument::Compact));
                    }
                }
                else if (request == Signup)
                {
                    if (receivedObject.contains("username") && receivedObject.contains("password") && receivedObject.contains("firstName") && receivedObject.contains("lastName") && receivedObject.contains("teacher"))
                    {
                        QJsonObject signup;
                        writeSignup(receivedObject["username"].toString(), receivedObject["password"].toString(), receivedObject["firstName"].toString(), receivedObject["lastName"].toString(), receivedObject["teacher"].toString(), signup);
                        QJsonDocument responseDocument(signup);
                        client->sendTextMessage(responseDocument.toJson(QJsonDocument::Compact));
                    }
                }
                else if (request == IsTeacher)
                {
                    if (receivedObject.contains("username"))
                    {
                        QJsonObject signup;
                        writeIsTeacher(receivedObject["username"].toString(), signup);

                        QJsonDocument responseDocument(signup);
                        client->sendTextMessage(responseDocument.toJson(QJsonDocument::Compact));
                    }
                }
                else if (request == UserInfo)
                {
                    if (receivedObject.contains("username"))
                    {
                        QJsonObject info;
                        writeUserInfo(receivedObject["username"].toString(), info);

                        QJsonDocument responseDocument(info);
                        client->sendTextMessage(responseDocument.toJson(QJsonDocument::Compact));
                    }
                }
                else if (request == NewScoreLevel)
                {
                    if (receivedObject.contains("username") && receivedObject.contains("score") && receivedObject.contains("level"))
                    {
                        QJsonObject success;
                        qDebug() << "about to write new score";
                        writeNewScore(receivedObject["username"].toString(), receivedObject["level"].toInt(), receivedObject["score"].toInt(), success);

                        QJsonDocument responseDocument(success);
                        client->sendTextMessage(responseDocument.toJson(QJsonDocument::Compact));
                    }
                }
                else
                {
                    if (debug)
                        qDebug() << "ERROR! Unkown Enum RequestType type:" << request;
                }
            }
            else if(receivedObject.contains("webrequest"))
            {
                if (receivedObject["webrequest"].toObject().contains("teacher"))
                {
//                    QJsonObject test;
//                    test["teacherName"] = "test name";

                    QString teacherName = receivedObject["webrequest"].toObject()["teacher"].toString();

                    QJsonObject rootObject;
                    if (debug)
                        qDebug() << "Writing teacher stats from database.";
                    writeTeacherStats(teacherName, rootObject);

//                    QJsonArray teststudentArray;
//                    for (int i = 0; i < 10; ++i)
//                    {
//                        QJsonArray student;
//                        student.append("student" + QString::number(i));
//                        student.append(QString::number(i*2));
//                        student.append(QString::number(i*4));
//                        teststudentArray.append(student);
//                    }
//                    test["students"] = teststudentArray;

                    QJsonDocument responseDocument(rootObject);
                    client->sendTextMessage(responseDocument.toJson(QJsonDocument::Compact));

                    if (debug)
                        qDebug() << "Responded: " << responseDocument.toJson(QJsonDocument::Compact);
                }
            }
            else
            {
                if (debug)
                    qDebug() << "Error! Unknown request type.";
            }
        }
        else
        {
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
void Networking::writeWordList(QString teacher, int level, QJsonObject &json)
{
    // Create root JSON Object:
    QJsonObject jsonWordList;

    // Add the key "name" and its value.
    jsonWordList["name"] = level;

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
 * \brief Queries the database whether the provided login, password pair are correct
 * \param login
 * \param password
 * \param json
 */
void Networking::writeLogin(QString login, QString password, QJsonObject &json)
{
    QJsonObject jsonUserAccess;
    bool isTeacher = false;
    bool loginCorrect = db->loginCorrect(login, password);
    if(loginCorrect)
        isTeacher = db->isTeacher(login);
    jsonUserAccess["accessGranted"] = loginCorrect;
    jsonUserAccess["username"] = login;
    jsonUserAccess["isTeacher"] = isTeacher;
    json["userAccess"] = jsonUserAccess;
}

/*!
 * \brief Queries the database if the username is taken
 * \param login
 * \param json
 */
void Networking::writeLoginAvailable(QString login, QJsonObject &json)
{
    json["usernameIsAvailable"] = db->usernameAvailable(login);
}

/*!
 * \brief Inserts the new user into the database
 * \param login
 * \param password
 * \param first
 * \param last
 * \param teacher
 * \param json
 */
void Networking::writeSignup(QString login, QString password, QString first, QString last, QString teacher, QJsonObject &json)
{
    QJsonObject jsonUserAccess;
    jsonUserAccess["accessGranted"] = db->usernameAvailable(login);
    jsonUserAccess["username"] = login;
    json["userAccess"] = jsonUserAccess;
    if(teacher.length() > 0)
        db->insertNewStudent(login, first, last, password, teacher);
    else
        db->insertNewTeacher(login,first,last,password);
}

void Networking::writeIsTeacher(QString teacher, QJsonObject &json)
{
    QJsonObject jsonIsTeacher;
    jsonIsTeacher["username"] = teacher;
    jsonIsTeacher["isTeacher"] = db->isTeacher(teacher);
    json["isTeacher"] = jsonIsTeacher;
}

void Networking::writeUserInfo(QString login, QJsonObject &json)
{
    QJsonObject jsonUserInfo;
    jsonUserInfo["username"] = login;
    QList<QString> name = db->getFirstAndLastName(login);
    if (name.length() != 2)
    {
        json["success"] = false;
        return;
    }
    jsonUserInfo["first"] = name[0];
    jsonUserInfo["last"] = name[1];
    jsonUserInfo["teacher"] = db->getTeacher(login);
    jsonUserInfo["level"] = db->getUserCurrentLevel(login);
    jsonUserInfo["highScore"] = db->getUserScore(login);
    json["userInfo"] = jsonUserInfo;
}

void Networking::writeNewScore(QString login, int level, int highScore, QJsonObject &json)
{
    if (db->usernameAvailable(login))
    {
        json["success"] = false;
    }
    else
    {
        qDebug() << "updating mysql database";
        db->updateUserLevelAndScore(login, level, highScore);
        json["success"] = true;
    }
}

void Networking::writeTeacherStats(QString teacherName, QJsonObject &json)
{
    json["teacherName"] = teacherName;

    QList<QList<QString>> teacherStatsList = db->getTeacherStats(teacherName);

    QJsonArray resultingStudentList;
    for (QList<QString> individualStudents : teacherStatsList)
    {
        QJsonArray student;
        student = QJsonArray::fromStringList(individualStudents);
        resultingStudentList.append(student);
    }

    json["students"] = resultingStudentList;
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
