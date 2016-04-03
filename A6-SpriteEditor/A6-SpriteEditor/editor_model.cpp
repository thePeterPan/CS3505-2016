#include "editor_model.h"

editor_model::editor_model(QObject *parent) :
    QObject(parent),
    current_state(PAUSED),
    file_path(""),
    current_tool(BRUSH),
    playback_speed(1),
    current_frame_index(0) { }

void editor_model::setSprite(Sprite *sprite)
{
    this->sprite_main = sprite;
}

Sprite* editor_model::getSprite()
{
    return sprite_main;
}

/**
 * Moves the model to the next frame by incrementing the current_frame_index. If
 * the incremented index is greater than or equal to the length of the number of
 * frames in the sprite, then reset the index back to 0.
 *
 * @brief editor_model::nextFrame
 */
void editor_model::nextFrame()
{
    if (++current_frame_index >= sprite_main->getAnimationLength())
        current_frame_index = 0;
}

/**
 * Moves the model to the previous frame by decrementing the index. If the index
 * is decremented to less than 0, reset the index to the end of the list of frames.
 * @brief editor_model::prevFrame
 */
void editor_model::prevFrame()
{
    if (--current_frame_index < 0)
        current_frame_index = sprite_main->getAnimationLength() - 1;
}

void editor_model::setAnimatorState(AnimatorState state)
{
    current_state = state;
}

editor_model::AnimatorState editor_model::getAnimatorState()
{
    return current_state;
}

void editor_model::setCurrentTool(Tool tool)
{
    current_tool = tool;
}

editor_model::Tool editor_model::getCurrentTool()
{
    return current_tool;
}

void editor_model::setPlaybackSpeed(int speed)
{
    playback_speed = speed;
}

int editor_model::getPlaybackSpeed()
{
    return playback_speed;
}

void editor_model::saveSpriteToFile(QString path)
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
    if(!file.open(QIODevice::ReadOnly)) {
        //error
        return;
    }
    file_path = path;
    QTextStream in(&file);
    int numberOfFrames, width, height;
    int currentX = 0;
    int currentY = 0;
    QString size = in.readLine();
    QStringList sizes = size.split(" ");
    width = sizes[0].toInt();
    height = sizes[1].toInt();
    sprite_main = new Sprite(width,height);

    QString num_frames = in.readLine();
    numberOfFrames = num_frames.toInt();

    while(!in.atEnd())
    {
        int lineCount = 0;
        sprite_main->addFrameAfterCurrentIndex();
        while(lineCount < height)
        {
            currentX = 0;
            QString line = in.readLine();
            QStringList numbers = line.split(" ");

            for(int i = 0; i < numbers.size() - 4; i += 4)
            {
                int red   = numbers[i+0].toInt();
                int green = numbers[i+1].toInt();
                int blue  = numbers[i+2].toInt();
                int alpha = numbers[i+3].toInt();
                QColor color(red, green, blue, alpha);
                sprite_main->setPixelColorAtCurrentFrame(currentX, currentY, color);
                ++currentX;
            }
            ++currentY;
            ++lineCount;
        }

    }
    emit modelUpdated(sprite_main);
}

QString editor_model::getFilePath()
{
    return file_path;
}
