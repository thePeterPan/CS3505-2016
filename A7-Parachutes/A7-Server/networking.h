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
        TeacherList,
        UsernameCheck,
        Signup,
        GameOver,
        Error,
        UserInfo,
        IsTeacher,
        NewScoreLevel,
        IncrementLevel
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

    void writeWordList(QString teacher, int level, QJsonObject &json);
    void writeLogin(QString login, QString password, QJsonObject &json);
    void writeLoginAvailable(QString login, QJsonObject &json);
    void writeSignup(QString login, QString password, QString first, QString last, QString teacher, QJsonObject &json);
    void writeIsTeacher(QString teacher, QJsonObject &json);
    void writeUserInfo(QString login, QJsonObject &json);
    void writeNewScore(QString login, int level, int highScore, QJsonObject &json);
    void writeTeacherStats(QString teacherName, QJsonObject &json);

    void printJsonObject(QJsonObject &json);
    QString jsonTest();
};

#endif // NETWORKING_H
