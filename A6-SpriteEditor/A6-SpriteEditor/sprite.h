#ifndef SPRITE_H
#define SPRITE_H

// Qt Graphics Objects
#include <QObject>
#include <QList>
// Other Qt Objects
#include <QString>

#include "frame.h"

class sprite : public QObject
{
    Q_OBJECT
public:
    explicit sprite(QObject *parent = 0);
    explicit sprite(int width_, int height_, QString title, QObject * parent = 0);

    int getAnimationLength();
//    frame getFrame(int index);
//    frame addFrame();
    void removeFrameAt(int index);
    int getWidth();
    int getHeight();
    bool getFileSavedStatus();
    void setFileSavedStatus(bool status);
    void save(string path);
    string toString();

private:
    QList<Frame*> frames;
    int width;
    int height;

    bool file_saved;
    QString sprite_title;

signals:

public slots:

};

#endif // SPRITE_H
