#ifndef FRAME_H
#define FRAME_H

#include <QObject>
#include <QList>
#include <QColor>
#include <QVector>
#include <QString>

class Frame : public QObject
{
    //Q_OBJECT

public:
    explicit Frame(QObject *parent = 0);
    explicit Frame(QObject *parent = 0, int width_ = 0, int height_ = 0);
    ~Frame();

    void setPixelColor(int x, int y, QColor color);
    void setWholeFrameColor(QColor color);
    QColor getPixelColor(int x, int y);
    int getFrameWidth();
    int getFrameHeight();
    void rotate(bool direction);
    QString toString();

private:
    QVector<QVector<QColor>> frameMatrix;
    int width;
    int height;
/*
signals:

public slots:
*/
};

#endif // FRAME_H
