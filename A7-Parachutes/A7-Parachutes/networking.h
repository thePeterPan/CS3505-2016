#ifndef NETWORKING_H
#define NETWORKING_H

#include <QObject>
#include <QSettings>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include "QtWebSockets/qwebsocket.h"

class Networking : public QObject
{
    Q_OBJECT
public:
    explicit Networking(QString configFile, QObject *parent = 0);
    ~Networking();

    enum RequestType {
        WordList,
        Login,
        Signup,
        GameOver,
        TeacherList,
        UsernameCheck
    };

    void requestWordList(QString teacher, QString listName);

Q_SIGNALS:
    void socketClosed();
    void receiveError(QString errorMessage);

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);
    void onBinaryMessageReceived(QByteArray data);

private:
    QWebSocket webSocket;
    QUrl url;
    bool debug;

    void printJsonObject(QJsonObject &json);
    void printJsonArray(QJsonArray &array);
    void testJson(QString message);
};

#endif // NETWORKING_H
