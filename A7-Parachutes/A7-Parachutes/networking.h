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

    void requestWordList(QString teacher, int level);

Q_SIGNALS:
    void socketClosed();
    void receiveError(QString errorMessage);
    void newList(QList<QString> list);

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);
    void onBinaryMessageReceived(QByteArray data);

private:
    QWebSocket webSocket;
    QUrl url;
    bool debug;
    QList<QString> getWordList(QJsonArray &array);
    void printJsonObject(QJsonObject &json);
    void printJsonArray(QJsonArray &array);
    void testJson(QString message);

public slots:
    void requestNextList(int level);
};

#endif // NETWORKING_H
