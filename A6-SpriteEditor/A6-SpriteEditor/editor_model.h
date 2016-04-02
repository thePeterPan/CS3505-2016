#ifndef EDITOR_MODEL_H
#define EDITOR_MODEL_H

// Qt Graphics Objects
#include <QObject>
#include <QWidget>
// Other Qt Objects
#include <QColor>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QException>

#include "sprite.h"

class editor_model : public QObject
{
    Q_OBJECT
public:
    explicit editor_model(QObject *parent = 0);

    // Indicates the state of the main view. e.g. if the main view
    // is currently playing the animation at the given speed.
    enum AnimatorState: unsigned int
    {
        PLAYING,
        PAUSED
    };
    void setAnimatorState(AnimatorState state);
    AnimatorState getAnimatorState();

    // Indicates the current tool that the user has selected.
    enum Tool: unsigned int
    {
        BRUSH,
        FILL_BUCKET,
        ERASER,
        ROTATE,
        PAN,
        MIRROR
    };
    void setCurrentTool(Tool tool);
    Tool getCurrentTool();

    // Unnecessary (maybe)
    void setSprite(Sprite* sprite);
    Sprite* getSprite();

    // Frames:
    void nextFrame();
    void prevFrame();
    // void addFrameAt(int index);
    // void deleteFrameAt(int index);

    // Playback Speed
    void setPlaybackSpeed(int speed);
    int getPlaybackSpeed();

    // Save/load file methods
    QString getFilePath();
    void saveSpriteToFile(QString path);
    void loadSpriteFromFile(QString path);

private:
    // State variables:
    AnimatorState current_state;
    QString file_path;
    Tool current_tool;
    int playback_speed;

    // Sprite object
    Sprite* sprite_main;

    // Move to sprite:
    int current_frame_index;

signals:
    void modelUpdated(Sprite* sprite);

public slots:
};

#endif // EDITOR_MODEL_H
