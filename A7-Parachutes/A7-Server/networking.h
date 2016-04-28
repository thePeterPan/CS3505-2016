#ifndef NETWORKING_H
#define NETWORKING_H

#include <QObject>
#include <QList>
#include <QByteArray>
#include <QSettings>
#include <QDebug>
#include <QFile>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"

#include "mysqlwrapper.h"

class Networking : public QObject
{
    Q_OBJECT
public:
    explicit Networking(QString configFile, QObject *parent = Q_NULLPTR);
    ~Networking();

    QString testJson();

    enum RequestType {
        WordList,
        Login,
        Signup,
        GameOver,
        TeacherList,
        UsernameCheck
    };

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

    MySQLWrapper *db;
    void openConnectionToDatabase(QString configFile);
    // TODO: check for if database did not connect.

    void writeWordList(QString teacher, QString listName, int level, QJsonObject &json);
    void printJsonObject(QJsonObject &json);
    QString jsonTest();
};

#endif // NETWORKING_H
