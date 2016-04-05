#include "editor_model.h"

editor_model::editor_model(QObject *parent) :
    QObject(parent),
    current_state(PAUSED),
    file_path(""),
    brush_color(QColor::fromRgb(0, 0, 0)),
    current_tool(BRUSH),
    playback_speed(1) { }


//// Animator State ////

void editor_model::setAnimatorState(AnimatorState state)
{
    current_state = state;
}

editor_model::AnimatorState editor_model::getAnimatorState()
{
    return current_state;
}


//// Current Tool ////

void editor_model::setCurrentTool(Tool tool)
{
    current_tool = tool;
    emit toolChanged(current_tool);
}

editor_model::Tool editor_model::getCurrentTool()
{
    return current_tool;
}

//// Should not be necessary ////
//// Sprite Methods ////

void editor_model::setSprite(Sprite *sprite)
{
    this->sprite_main = sprite;
}

Sprite* editor_model::getSprite()
{
    return sprite_main;
}

//// Drawing Methods ////

void editor_model::paintCommand(int x, int y)
{
    if(current_tool == editor_model::BRUSH) {
        drawSquare(x, y);
    } else if (current_tool == editor_model::FILL_BUCKET) {
        fillBucket(x, y);
    } else if (current_tool == editor_model::MIRROR) {
        drawMirror(x, y);
    } else if (current_tool == editor_model::ERASER) {
        eraseSquare(x, y);
    }
}

/**
 * @brief GraphicsScene::drawSquare
 * Draws a square onto the canvas at the x and y pixel positions.
 * Aka. for the paint brush tool.
 * @param x
 * @param y
 * @param color
 */
void editor_model::drawSquare(int x, int y)
{
    if((x < 0) | (y < 0) | (x >= sprite_main->getWidth()) | (y >= sprite_main->getHeight()))
        return;

    sprite_main->setPixelColorAtCurrentFrame(x, y, brush_color);

    emit squareUpdated(x, y);
}

void editor_model::eraseSquare(int x, int y)
{
    if((x < 0) | (y < 0) | (x >= sprite_main->getWidth()) | (y >= sprite_main->getHeight()))
        return;

    sprite_main->setPixelColorAtCurrentFrame(x, y, QColor(0, 0, 0, 0));

    emit squareUpdated(x, y);
}

void editor_model::fillBucket(int x, int y)
{
    QColor prev = sprite_main->getPixelColorAtCurrentFrame(x, y);

    if(prev == brush_color)
        return;

    drawSquare(x, y);


    int width = sprite_main->getWidth();
    int height = sprite_main->getHeight();

    int x1 = x - 1;
    int x2 = x + 1;
    int y1 = y - 1;
    int y2 = y + 1;
    if(x1 >= 0 && sprite_main->getPixelColorAtCurrentFrame(x1, y) == prev)
            fillBucket(x1, y);

    if(x2 < width && sprite_main->getPixelColorAtCurrentFrame(x2, y) == prev)
            fillBucket(x2, y);

    if(y1 >= 0 && sprite_main->getPixelColorAtCurrentFrame(x, y1) == prev)
            fillBucket(x, y1);

    if(y2 < height && sprite_main->getPixelColorAtCurrentFrame(x, y2) == prev)
            fillBucket(x, y2);
}

void editor_model::drawMirror(int x, int y)
{
    drawSquare(x, y);
    drawSquare(sprite_main->getWidth() - 1 - x, y);
}

void editor_model::rotateScene(bool direction)
{
    sprite_main->rotateCurrentFrame(direction);
    emit sceneUpdated();
}

void editor_model::flipSceneOrientation(bool orientation)
{
    sprite_main->flipCurrentFrameOrientation(orientation);
    emit sceneUpdated();
}

void editor_model::invertSceneColors()
{
    sprite_main->invertCurrentFrameColor();
    emit sceneUpdated();
}

//// Frame Methods ////

void editor_model::nextFrame()
{
    sprite_main->nextFrame();
    emit sceneUpdated();
    emit frameUpdated(sprite_main->getCurrentFrameIndex(), sprite_main->getAnimationLength());
}

void editor_model::prevFrame()
{
    sprite_main->prevFrame();
    emit sceneUpdated();
    emit frameUpdated(sprite_main->getCurrentFrameIndex(), sprite_main->getAnimationLength());
}

void editor_model::addFrame()
{
    sprite_main->addFrameAfterCurrentIndex();
    emit sceneUpdated();
    emit frameUpdated(sprite_main->getCurrentFrameIndex(), sprite_main->getAnimationLength());
}

void editor_model::removeFrame()
{
    sprite_main->removeCurrentFrame();
    emit sceneUpdated();
    emit frameUpdated(sprite_main->getCurrentFrameIndex(), sprite_main->getAnimationLength());
}

void editor_model::setCurrentFrame(int index)
{
    if (index == sprite_main->getCurrentFrameIndex())
        return;
    sprite_main->setCurrentFrame(index);
    emit sceneUpdated();
    emit frameUpdated(sprite_main->getCurrentFrameIndex(), sprite_main->getAnimationLength());
}

//// Brush Color ////

void editor_model::setBrushColor(QColor color)
{
    brush_color = color;
}

//QColor editor_model::getBrushColor()
//{
//    return brush_color;
//}

//// Playback Speed ////

void editor_model::setPlaybackSpeed(int speed)
{
    playback_speed = speed;
}

int editor_model::getPlaybackSpeed()
{
    return playback_speed;
}


//// Saving/loading ////

bool editor_model::getFileSavedStatus()
{
    return file_saved;
}

void editor_model::setFileSavedStatus(bool status)
{
    file_saved = status;
}

QString editor_model::getFilePath()
{
    return file_path;
}

void editor_model::saveToFile(QString path)
{
    QFile file(path);
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream << sprite_main->toString();
    }

    file_path = path;
}

void editor_model::loadSpriteFromFile(QString path)
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
    int width = widthAndHeight[0].toInt();
    int height = widthAndHeight[1].toInt();

    // Initialize a new sprite
    sprite_main = new Sprite(width, height);

    // Get the number of frames.
    QString num_frames = in.readLine();
    int numberOfFrames = num_frames.toInt();

    // Loop through the remainder of the lines in the file.
    while (!in.atEnd())
    {
        // The following loop encompasses a single frame.
        int currentY = 0;
        while (currentY < height)
        {
            int currentX = 0;
            QString line = in.readLine();
            QStringList numbers = line.split(" ");

            // Loop through the line to set the colors on one row.
            for (int i = 0; i < numbers.size() - 4; i += 4)
            {
                QColor color(
                        numbers[i+0].toInt(),
                        numbers[i+1].toInt(),
                        numbers[i+2].toInt(),
                        numbers[i+3].toInt());

                sprite_main->setPixelColorAtCurrentFrame(currentX, currentY, color);

                ++currentX;
            }
            ++currentY;
        }

        // Check to see if there are more frames, if so, increment counter
        // and add a frame.
        if (!in.atEnd())
        {
            sprite_main->addFrameAfterCurrentIndex();
        }
    }

    file_path = path;

    // Reset current frame back to 0,
    // which automatically emits signal to update frame status and scene
    setCurrentFrame(0);
}

void editor_model::exportSpriteAsGIF(QString path)
{
    QFileInfo file(path);
    QString directory = file.dir().path();
    QString fileBaseName = file.baseName();
    QString extension = file.completeSuffix();

    QList<QImage*> imageList(sprite_main->getFramesAsImages());

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
        QString delay = QString::number(100.0/ (double) playback_speed);
        parameter_list << "-dispose" << "background" << "-delay" << delay << fullFrameFilesPath << fullExportFilePath;

        _CONVERT.start(process, parameter_list);
        if (!(_CONVERT.waitForFinished()))
            qDebug() << "Conversion failed:" << _CONVERT.errorString();
        else
            qDebug() << "Conversion output:" << _CONVERT.readAll();

        // Was going to add code to delete 'tmp' folder, but I find that a little dangerous.
    }
}

void editor_model::iterateThroughFrames()
{
    this->setCurrentFrame(0);
    for (int i = 1; i < sprite_main->getAnimationLength(); i++)
    {
        QTimer::singleShot(i * (1000.0/ (double) playback_speed), this, SLOT(moveToNextFrame()));
    }
}

void editor_model::moveToNextFrame()
{
    if (sprite_main->getCurrentFrameIndex() >= sprite_main->getAnimationLength() - 1)
    {
        return;
    }
    else
    {
        this->setCurrentFrame(sprite_main->getCurrentFrameIndex() + 1);
    }
}
