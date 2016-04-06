#include "editor_model.h"

EditorModel::EditorModel(QObject *parent) :
    QObject(parent),
    currentState(PAUSED),
    filePath(""),
    brushColor(QColor::fromRgb(0, 0, 0)),
    currentTool(BRUSH),
    playbackSpeed(1) { }

/**
 * @brief EditorModel::~EditorModel
 */
EditorModel::~EditorModel()
{
    delete spriteMain;
}

//// Animator State ////

/**
 * @brief EditorModel::setAnimatorState
 * sets the state passed in as the currentState
 * @param state
 */
void EditorModel::setAnimatorState(AnimatorState state)
{
    currentState = state;
}
/**
 * @brief EditorModel::getAnimatorState
 * returns the currentState
 * @return
 */
EditorModel::AnimatorState EditorModel::getAnimatorState()
{
    return currentState;
}

//// Current Tool ////

/**
 * @brief EditorModel::setCurrentTool
 * sets the tool that is selected to currentTool
 * @param tool
 */
void EditorModel::setCurrentTool(Tool tool)
{
    currentTool = tool;
    emit toolChanged(currentTool);
}

/**
 * @brief EditorModel::getCurrentTool
 * returns the tool that is selected
 * @return
 */
EditorModel::Tool EditorModel::getCurrentTool()
{
    return currentTool;
}

//// Sprite Methods ////

/**
 * @brief EditorModel::setSprite
 * sets this sprite to the sprite that is being edited
 * @param sprite
 */
void EditorModel::setSprite(Sprite *sprite)
{
    this->spriteMain = sprite;
}

/**
 * @brief EditorModel::getSprite
 * returns the sprite that is being edited
 * @return
 */
Sprite* EditorModel::getSprite()
{
    return spriteMain;
}

//// Drawing Methods ////

/**
 * @brief EditorModel::paintCommand
 * this method directs the program to the appropiate drawing method
 * depending on the tool selected
 * @param x
 * @param y
 */
void EditorModel::paintCommand(int x, int y)
{
    if(currentTool == EditorModel::BRUSH) {
        drawSquare(x, y);
    } else if (currentTool == EditorModel::FILL_BUCKET) {
        fillBucket(x, y);
    } else if (currentTool == EditorModel::MIRROR) {
        drawMirror(x, y);
    } else if (currentTool == EditorModel::ERASER) {
        eraseSquare(x, y);
    }
    emit fileSaved(false);
}

/**
 * @brief GraphicsScene::drawSquare
 * Draws a square onto the canvas at the x and y pixel positions.
 * Aka. for the paint brush tool.
 * @param x
 * @param y
 * @param color
 */
void EditorModel::drawSquare(int x, int y)
{
    if((x < 0) | (y < 0) | (x >= spriteMain->getWidth()) | (y >= spriteMain->getHeight()))
        return;

    spriteMain->setPixelColorAtCurrentFrame(x, y, brushColor);

    emit squareUpdated(x, y);
}

/**
 * @brief EditorModel::eraseSquare
 * "erases"(sets it to black and completely transparent)
 *  the square located at (x,y)
 * @param x
 * @param y
 */
void EditorModel::eraseSquare(int x, int y)
{
    if((x < 0) | (y < 0) | (x >= spriteMain->getWidth()) | (y >= spriteMain->getHeight()))
        return;

    spriteMain->setPixelColorAtCurrentFrame(x, y, QColor(0, 0, 0, 0));

    emit squareUpdated(x, y);
}

/**
 * @brief EditorModel::fillBucket
 * recursively draws squares in the area contained around the point (x,y)
 * @param x
 * @param y
 */
void EditorModel::fillBucket(int x, int y)
{
    QColor prev = spriteMain->getPixelColorAtCurrentFrame(x, y);

    if(prev == brushColor)
        return;

    drawSquare(x, y);

    int width = spriteMain->getWidth();
    int height = spriteMain->getHeight();

    int x1 = x - 1;
    int x2 = x + 1;
    int y1 = y - 1;
    int y2 = y + 1;
    if(x1 >= 0 && spriteMain->getPixelColorAtCurrentFrame(x1, y) == prev)
            fillBucket(x1, y);

    if(x2 < width && spriteMain->getPixelColorAtCurrentFrame(x2, y) == prev)
            fillBucket(x2, y);

    if(y1 >= 0 && spriteMain->getPixelColorAtCurrentFrame(x, y1) == prev)
            fillBucket(x, y1);

    if(y2 < height && spriteMain->getPixelColorAtCurrentFrame(x, y2) == prev)
            fillBucket(x, y2);
}

/**
 * @brief EditorModel::drawMirror
 * handles the drawing of symmetric points
 * @param x
 * @param y
 */
void EditorModel::drawMirror(int x, int y)
{
    drawSquare(x, y);
    drawSquare(spriteMain->getWidth() - 1 - x, y);
}

/**
 * @brief EditorModel::rotateScene
 * rotates the scene
 * @param direction
 */
void EditorModel::rotateScene(bool direction)
{
    spriteMain->rotateCurrentFrame(direction);
    emit sceneUpdated();
    emit fileSaved(false);
}

/**
 * @brief EditorModel::flipSceneOrientation
 * calls the flipCurrentFrameOrientation method in the sprite class
 * and emits the sceneUpdated signal
 * @param orientation
 */
void EditorModel::flipSceneOrientation(bool orientation)
{
    spriteMain->flipCurrentFrameOrientation(orientation);
    emit sceneUpdated();
    emit fileSaved(false);
}

/**
 * @brief EditorModel::invertSceneColors
 * calls the invertCurrentFrameColor method in the sprite class
 * and emits the sceneUpdated signal
 */
void EditorModel::invertSceneColors()
{
    spriteMain->invertCurrentFrameColor();
    emit sceneUpdated();
    emit fileSaved(false);
}

//// Frame Methods ////

/**
 * @brief EditorModel::nextFrame
 * calls the nextFrame method in the sprite class and emits update signals
 */
void EditorModel::nextFrame()
{
    spriteMain->nextFrame();
    emit sceneUpdated();
    emit frameUpdated(spriteMain->getCurrentFrameIndex(), spriteMain->getAnimationLength());
}

/**
 * @brief EditorModel::prevFrame
 * calls the prevFrame method in the sprite class and emits udpate signals
 */
void EditorModel::prevFrame()
{
    spriteMain->prevFrame();
    emit sceneUpdated();
    emit frameUpdated(spriteMain->getCurrentFrameIndex(), spriteMain->getAnimationLength());
}

/**
 * @brief EditorModel::addFrame
 * calls the addFrameAfterCurrentIndex method in the sprite class
 * and emits update signals
 */
void EditorModel::addFrame()
{
    spriteMain->addFrameAfterCurrentIndex();
    emit sceneUpdated();

    emit frameUpdated(spriteMain->getCurrentFrameIndex(), spriteMain->getAnimationLength());
    emit fileSaved(false);
}

/**
 * @brief EditorModel::removeFrame
 * calls the removeCurrentFrame method in the sprite class
 * and emits update signals
 */
void EditorModel::removeFrame()
{
    spriteMain->removeCurrentFrame();
    emit sceneUpdated();

    emit frameUpdated(spriteMain->getCurrentFrameIndex(), spriteMain->getAnimationLength());
    emit fileSaved(false);
}

/**
 * @brief EditorModel::setCurrentFrame
 * sets the currentFrame and emits updated signals
 * @param index
 */
void EditorModel::setCurrentFrame(int index)
{
    if (index == spriteMain->getCurrentFrameIndex())
        return;
    spriteMain->setCurrentFrame(index);
    emit sceneUpdated();
    emit frameUpdated(spriteMain->getCurrentFrameIndex(), spriteMain->getAnimationLength());
}

//// Brush Color ////

void EditorModel::setBrushColor(QColor color)
{
    brushColor = color;
}

//// Playback Speed ////

/**
 * @brief EditorModel::setPlaybackSpeed
 * sets the playbackSpeed
 * @param speed
 */
void EditorModel::setPlaybackSpeed(int speed)
{
    playbackSpeed = speed;
}

/**
 * @brief EditorModel::getPlaybackSpeed
 * returns the playbackSpeed
 * @return
 */
int EditorModel::getPlaybackSpeed()
{
    return playbackSpeed;
}

//// Saving/loading ////

/**
 * @brief EditorModel::getFileSavedStatus
 * returns the fileSaved status
 * @return
 */
bool EditorModel::getFileSavedStatus()
{
    return fileIsSaved;
}

/**
 * @brief EditorModel::setFileSavedStatus
 * sets the fileSaved status
 * @param status
 */
void EditorModel::setFileSavedStatus(bool status)
{
    fileIsSaved = status;
}

/**
 * @brief EditorModel::getFilePath
 * returns the filePath
 * @return
 */
QString EditorModel::getFilePath()
{
    return filePath;
}

/**
 * @brief EditorModel::saveToFile
 * saves the sprite to a file
 * @param path
 */
void EditorModel::saveToFile(QString path)
{
    QFile file(path);
    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << spriteMain->toString();
    }

    filePath = path;
    emit fileSaved(true);
}

/**
 * @brief EditorModel::loadSpriteFromFile
 * loads an already existing sprite to be edited
 * @param path
 */
void EditorModel::loadSpriteFromFile(QString path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        //error
        return;
    }
    QTextStream in(&file);

    // Get the wdith and the height from the file.
    QStringList widthAndHeight = in.readLine().split(" ");
    int height = widthAndHeight[0].toInt();
    int width = widthAndHeight[1].toInt();

    // Initialize a new sprite
    spriteMain = new Sprite(width, height);

    // Get the number of frames.
    QString num_frames = in.readLine();
    int numberOfFrames = num_frames.toInt();
    int currentFrame = 0;
    // Loop through the remainder of the lines in the file.
    while (currentFrame < numberOfFrames)
    {
        // The following loop encompasses a single frame.
        int currentY = 0;
        while (currentY < height)
        {
            int currentX = 0;
            QString line = in.readLine();
            QStringList numbers = line.split(" ");

            // Loop through the line to set the colors on one row.
            for (int i = 0; i <= numbers.size() - 4; i += 4)
            {
                QColor color(
                        numbers[i+0].toInt(),
                        numbers[i+1].toInt(),
                        numbers[i+2].toInt(),
                        numbers[i+3].toInt());

                spriteMain->setPixelColorAtCurrentFrame(currentX, currentY, color);

                ++currentX;
            }
            ++currentY;
        }

        // Check to see if there are more frames, if so, increment counter
        // and add a frame.
        if (!in.atEnd())
        {
            spriteMain->addFrameAfterCurrentIndex();
        }
        currentFrame++;
    }

    filePath = path;

    // Reset current frame back to 0,
    // which automatically emits signal to update frame status and scene
    setCurrentFrame(0);

    emit sceneUpdated();

    emit frameUpdated(spriteMain->getCurrentFrameIndex(),spriteMain->getAnimationLength());
    emit fileSaved(true);
}

/**
 * @brief EditorModel::exportSpriteAsGIF
 * exports the sprite as a GIF
 * @param path
 */
void EditorModel::exportSpriteAsGIF(QString path)
{
    QFileInfo file(path);
    QString directory = file.dir().path();
    QString fileBaseName = file.baseName();
    QString extension = file.completeSuffix();

    QList<QImage*> imageList(spriteMain->getFramesAsImages());

    // If using a temporary directory:
    QString temporaryDirectory = "tmp/";
    file.dir().mkdir(temporaryDirectory);


    // Get the number of padded zeroes we need
    int zeroPadding = QString::number(imageList.size()).length();

    // Create a sequence of images from the frames and put them in the temporary folder:
    for (int index = 0; index < imageList.size(); ++index)
    {
        QString imageIndex = QString("%1").arg(index, zeroPadding, 10, QChar('0'));
        extension = "png"; // **Temporary**
        QString fullFramesFilePath = directory + "/" + temporaryDirectory + fileBaseName + "-" + imageIndex + "." + extension;

        imageList.at(index)->save(fullFramesFilePath, "PNG");
    }

    // Make sure that the convert binary exists on the system:
    QFileInfo convertFileInfo("/usr/bin/convert");
    if (convertFileInfo.exists())
    {
        // If it exists, convert them to a gif with the following command structure:
        // convert -delay 5 filename-*.png animated.gif
        QString fullFrameFilesPath = directory + "/" + temporaryDirectory + fileBaseName + "-*." + extension;
        extension = "gif";
        QString fullExportFilePath = directory + "/" + fileBaseName + "." + extension;

        QProcess _CONVERT;
        QString process = "convert";
        QStringList parameter_list;
        QString delay = QString::number(100.0/ (double) playbackSpeed);
        parameter_list << "-dispose" << "background" << "-delay" << delay << fullFrameFilesPath << fullExportFilePath;

        _CONVERT.start(process, parameter_list);
        if (!(_CONVERT.waitForFinished()))
            qDebug() << "Conversion failed:" << _CONVERT.errorString();
        else
            qDebug() << "Conversion output:" << _CONVERT.readAll();

        // Was going to add code to delete 'tmp' folder, but I find that a little dangerous.
    }
}

/**
 * @brief EditorModel::newSprite
 * Clears the filepath.
 */
void EditorModel::newSprite()
{
    filePath = "";
}

/**
 * @brief EditorModel::iterateThroughFrames
 * iterates through the frames of the sprite
 */
void EditorModel::iterateThroughFrames()
{
    this->setCurrentFrame(0);
    for (int i = 1; i < spriteMain->getAnimationLength(); i++)
    {
        QTimer::singleShot(i * (1000.0/ (double) playbackSpeed), this, SLOT(moveToNextFrame()));
    }
}

/**
 * @brief EditorModel::moveToNextFrame
 * moves the currentGrame to the next frame
 */
void EditorModel::moveToNextFrame()
{
    if (spriteMain->getCurrentFrameIndex() >= spriteMain->getAnimationLength() - 1)
    {
        return;
    }
    else
    {
        this->setCurrentFrame(spriteMain->getCurrentFrameIndex() + 1);
    }
}
