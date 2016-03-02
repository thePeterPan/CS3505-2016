#include "game_model.h"

game_model::game_model(QObject *parent) :
    QObject(parent),
    progress(0)
{

}

game_model::~game_model()
{

}

void game_model::incrementProgressBar()
{
    progress += 1;
    emit signalProgress(progress);
}

void game_model::emitSignal()
{
    emit signalProgress(progress);
}
