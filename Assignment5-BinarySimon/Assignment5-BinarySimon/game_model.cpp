#include "game_model.h"

#include <iostream>

game_model::game_model(QObject *parent) :
    QObject(parent),
    progress(0)
{
    // Start off with a two patterns.
    srand(10);
    add_to_pattern();
    add_to_pattern();

    // create new timer
    timer = new QTimer(this);
    // setup signal and slots
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
}

game_model::~game_model()
{
    delete timer;
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
    timer->start(1000);
}

void game_model::timerSlot()
{
    incrementProgressBar();
}

void game_model::add_to_pattern()
{
//    srand((unsigned)time(0));
//    int floor = 0, ceiling = 20, range = (ceiling - floor);
//    int rnd = floor + int((range * rand()) / (RAND_MAX + 1.0));

//    qDebug() << "test";

    int rnd = rand() %2;

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
