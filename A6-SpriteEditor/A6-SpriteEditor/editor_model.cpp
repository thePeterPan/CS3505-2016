#include "editor_model.h"

editor_model::editor_model(QObject *parent) :
    QObject(parent),
    current_state(PAUSED),
    file_path(""),
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
}

editor_model::Tool editor_model::getCurrentTool()
{
    return current_tool;
}


//// Sprite Methods ////

void editor_model::setSprite(Sprite *sprite)
{
    this->sprite_main = sprite;
}

Sprite* editor_model::getSprite()
{
    return sprite_main;
}


//// Frame Methods ////

void editor_model::nextFrame()
{
    sprite_main->nextFrame();
}

void editor_model::prevFrame()
{
    sprite_main->prevFrame();
}

void editor_model::addFrame()
{
    sprite_main->addFrameAfterCurrentIndex();
}

void editor_model::removeFrame()
{
    sprite_main->removeCurrentFrame();
}

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
    emit modelUpdated();
}

QString editor_model::getFilePath()
{
    return file_path;
}
