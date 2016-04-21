#ifndef NETWORKING_H
#define NETWORKING_H

#include <QObject>
#include <QtWebSockets/QWebSocket>

class Networking : public QObject
{
    Q_OBJECT
public:
    explicit Networking(const QUrl &url_, bool debug_ = false, QObject *parent = 0);

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);
    void onBinaryMessageReceived(QByteArray data);

private:
    QWebSocket webSocket;
    QUrl url;
    bool debug;
};

#endif // NETWORKING_H
