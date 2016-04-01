#ifndef FRAME_H
#define FRAME_H

#include <QObject>
#include <QList>
#include <QColor>
#include <QVector>
#include <QString>

using namespace std;

class Frame : public QObject
{
    Q_OBJECT
public:
    explicit Frame(QObject *parent = 0);
    explicit Frame(int width_, int height, QObject *parent = 0);
    ~Frame();

    void setPixelColor(int x, int y, QColor color);
    void setWholeFrameColor(QColor color);
    QColor getPixelColor(int x, int y);
    int getFrameWidth();
    int getFrameHeight();
    void rotate(bool direction);
    void flip(bool vertical);
    QString toString();
    void invert();

private:
    QVector<QVector<QColor>> frameMatrix;
    int width;
    int height;
    QString toRgbaString(QColor color);

signals:

public slots:

};

#endif // FRAME_H
