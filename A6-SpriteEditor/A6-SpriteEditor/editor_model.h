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

    Tool current_tool;


    void setBrushColor(QColor color);
    void nextFrame();
    void prevFrame();

    void setAnimatorState(AnimatorState state);
    AnimatorState getAnimatorState();

    void setTool(Tool tool);
    Tool getTool();

    void setPlaybackSpeed(int speed);

    void saveSpriteToFile(QString path);
    void loadSpriteFromFile(QString path);
    QString getFilePath();

private:
    // State variables:
    QColor brush_color;
    int current_frame_index;
    AnimatorState current_state;
    int playback_speed;
    QString file_path;

    // Sprite object
    Sprite sprite_main;

signals:

public slots:
};

#endif // EDITOR_MODEL_H
