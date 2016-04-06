#ifndef FRAME_H
#define FRAME_H

#include <QObject>
#include <QList>
#include <QColor>
#include <QVector>
#include <QString>
#include <QImage>

using namespace std;

class Frame : public QObject
{
    Q_OBJECT

public:
    explicit Frame(QObject *parent = 0);
    explicit Frame(int width_, int height, QObject *parent = 0);
    ~Frame();
    Frame* clone();

    // Getters and setters
    void setPixelColor(int x, int y, QColor color);
    QColor getPixelColor(int x, int y);
    int getFrameWidth();
    int getFrameHeight();
    void setWholeFrameColor(QColor color);

    // Frame manipulation
    void rotate(bool direction);
    void flip(bool vertical);
    void invert();

    // Save to file method
    QString toString();
    QImage* toQImage();

private:
    QVector<QVector<QColor>> frameMatrix;
    int width;
    int height;

    // Helper method to save to file
    QString toRgbaString(QColor color);
    void drawRealPixelSizeToQImage(QImage* image, int x, int y, int pixelSize, QColor color);

signals:

public slots:

};

#endif // FRAME_H
