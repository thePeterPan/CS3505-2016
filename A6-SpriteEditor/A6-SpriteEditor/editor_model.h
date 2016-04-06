#ifndef EDITOR_MODEL_H
#define EDITOR_MODEL_H

// Qt Graphics Objects
#include <QObject>
#include <QWidget>
// Other Qt Objects
#include <QColor>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include <QDebug>
#include <QException>
#include <QList>
#include <QProcess>
#include <QTimer>

#include "sprite.h"

class EditorModel : public QObject
{
    Q_OBJECT

public:
    explicit EditorModel(QObject *parent = 0);
    ~EditorModel();

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
        MIRROR
    };
    void setCurrentTool(Tool tool);
    Tool getCurrentTool();


    void setSprite(Sprite* sprite);
    Sprite* getSprite();

    // Drawing Methods (a few more in private)
    void rotateScene(bool direction);
    void flipSceneOrientation(bool orientation);
    void invertSceneColors();
    void paintCommand(int x, int y);

    // Frames:
    void nextFrame();
    void prevFrame();
    void addFrame();
    void removeFrame();
    void setCurrentFrame(int index);

    // Brush Color
    void setBrushColor(QColor color);
//    QColor getBrushColor();

    // Playback Speed
    void setPlaybackSpeed(int speed);
    int getPlaybackSpeed();

    // Save/load file methods
    bool getFileSavedStatus();
    void setFileSavedStatus(bool status);
    QString getFilePath();
    void saveToFile(QString path);
    void loadSpriteFromFile(QString path);
    void exportSpriteAsGIF(QString path);
    void newSprite();

    // play button preview
    void iterateThroughFrames();

private:
    // State variables:
    AnimatorState currentState;
    QString filePath;
    bool fileIsSaved;
    QColor brushColor;
    Tool currentTool;
    int playbackSpeed;

    // Sprite object
    Sprite* spriteMain;

    // Drawing methods more:
    void drawSquare(int x, int y);
    void fillBucket(int x, int y);
    void drawMirror(int x, int y);
    void eraseSquare(int x, int y);

signals:
    void sceneUpdated();
    void squareUpdated(int x, int y);
    void frameUpdated(int currentFrame, int numOfFrames);
    void toolChanged(Tool new_tool);

    void fileSaved(bool status);

public slots:
    void moveToNextFrame();
};

#endif // EDITOR_MODEL_H
