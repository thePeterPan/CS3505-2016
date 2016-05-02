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
    void requestNextList(int level, QString teacher);
    void requestLogin(QString username, QString password);
    void requestUserInfo(QString username);
    void requestWriteNewScore(QString username, int level, int score);
    void requestWriteNewUser(QString username, QString first, QString last, QString password, QString teacher);
    void requestIsTeacher(QString teacher);
    void requestNameAvailable(QString username);
    void requestCurrentHighScore(QString username);

signals:
    void loginSuccessSignal(QString, bool,bool);
    void sendUsernameAvailable(bool available);
    void sendIsTeacher(bool teacher);
    void sendUserType(bool teacher);
    void sendRegisterSuccess(bool success);
    void sendUserInfo(QString username, QString first, QString last, QString teacher, int level, int highScore);
    void sendCurrentScore(QString username, int level, int highscore);
};

#endif // NETWORKING_H
