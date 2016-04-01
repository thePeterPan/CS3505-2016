#include "editor_model.h"

editor_model::editor_model(QObject *parent) :
    QObject(parent), brush_color(QColor::fromRgb(255, 255, 255)), current_frame_index(0),
    current_state(PAUSED), current_tool(BRUSH), playback_speed(1), file_path("")
{
}

void editor_model::setBrushColor(QColor color)
{
    brush_color = color;
}

void editor_model::setSprite(Sprite *sprite)
{
    this->sprite_main = sprite;
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

void editor_model::setTool(Tool tool)
{
    current_tool = tool;
}

editor_model::Tool editor_model::getTool()
{
    return current_tool;
}

void editor_model::setPlaybackSpeed(int speed)
{
    playback_speed = speed;
}

void editor_model::saveSpriteToFile(QString path)
{
    QFile file(path);
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        qDebug() << sprite_main->getFrames().size();
        qDebug() << sprite_main->toString();
        stream << sprite_main->toString();
    }

    file_path = path;
}

void editor_model::loadSpriteFromFile(QString path)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) {
        //error
    }
    QTextStream in(&file);
    int numberOfFrames, width, height;
    int currentX = 0;
    int currentY = 0;
    QString size = in.readLine();
    QStringList sizes = size.split(" ");
    width = sizes[0].toInt();
    height = sizes[1].toInt();
    sprite_main = new Sprite(width,height,"Sprite");

    QString num_frames = in.readLine();
    numberOfFrames = num_frames.toInt();

    while(!in.atEnd()){
        int lineCount = 0;
        Frame* f = new Frame(width,height);
        sprite_main->addFrame(f);
        while(lineCount < height){
            currentX = 0;
            qDebug() << "Number of frames: " << sprite_main->getFrames().size();
            QString line = in.readLine();
            QStringList numbers = line.split(" ");
            for(int i = 0; i < numbers.size() - 4; i += 4){
                int red = numbers[i].toInt();
                int green = numbers[i+1].toInt();
                int blue = numbers[i+2].toInt();
                int alpha = numbers[i+3].toInt();
                QColor color(red,green,blue,alpha);
                f->setPixelColor(currentX,currentY,color);
                currentX++;
            }
            currentY++;
            lineCount++;
        }

    }
    emit modelUpdated(sprite_main);
}

QString editor_model::getFilePath()
{
    return file_path;
}
