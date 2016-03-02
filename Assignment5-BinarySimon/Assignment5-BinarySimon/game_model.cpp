#include "game_model.h"

game_model::game_model(QObject *parent) :
    QObject(parent),
    progress(0)
{
    add_to_pattern();
    add_to_pattern();
}

game_model::~game_model()
{

}

void game_model::incrementProgressBar()
{
    // increment the progress bar
    progress += 1;
    // tell the view that the progress has been updated
    emit signalProgress(progress);
}

void game_model::addToPattern(char color)
{
    pattern.push_back(color);
}

void game_model::timerEvent(QTimerEvent *event)
{
//    qDebug() << "Timer ID:" << event->timerId();
}

void game_model::startTimer()
{
//    startTimer(100);
}

void game_model::add_to_pattern()
{
    int num = rand() % 1;
//    srand((unsigned)time(0));
    srand(20);
    int floor = 0, ceiling = 20, range = (ceiling - floor);
    int rnd = floor + int((range * rand()) / (RAND_MAX + 1.0));

    while(true)
    {
//        rnd = floor + int((range * rand()) / (RAND_MAX + 1.0));
        num = rand() % 4;
    }
    switch(rnd)
    {
    case 0:
        pattern.push_back('b');
        break;
    case 1:
        pattern.push_back('r');
        break;
    default:
        pattern.push_back('g');
    }

}
