#include "game_model.h"

game_model::game_model(QObject *parent) :
    QObject(parent), game_state(gameState::Start), total_number_of_rounds(0), total_moves(0),
    current_sequence_progress(0)
{
    // Start off with a two patterns.
    srand(10);
    add_to_sequence();
    add_to_sequence();

    // create new timer for incrementing the progress bar
    timer = new QTimer(this);
}

/**
 * @brief game_model::~game_model
 */
game_model::~game_model()
{
    delete timer;
}

/**
 * Tried to put this in the constructor, but I assume that the constructor gets
 * called before the signals and slots are connected, therefore this is needed
 * to be called after the everything gets connected.

 * @brief game_model::gameStart
 */
void game_model::gameStart()
{
    // Tell the view to initialize in start mode:
    emit signalStateChange(game_state);
}

/**
 * @brief game_model::add_to_sequence
 */
void game_model::add_to_sequence()
{
//    srand((unsigned)time(0));
//    int floor = 0, ceiling = 20, range = (ceiling - floor);
//    int rnd = floor + int((range * rand()) / (RAND_MAX + 1.0));

//    qDebug() << "test";

    int rnd = rand() % 2;

    switch(rnd)
    {
    case 0:
        sequence.push_back('b');
        break;
    case 1:
        sequence.push_back('r');
        break;
    default:
        sequence.push_back('g');
    }
}

/**
 * @brief game_model::checkSequence
 * @param color
 */
void game_model::checkSequence(char color)
{
    if (sequence[current_sequence_progress] == color)
    {
        ++current_sequence_progress;
        emit signalProgressUpdate(current_sequence_progress);

        if (current_sequence_progress == (int) sequence.size())
        {
            emit signalSequenceComplete();
        }
    }
    else
    {
        // if next color does not match pattern emit lose signal
        emit signalGameOver();
    }
}

/**
 * @brief game_model::getSequence
 * @return
 */
std::vector<char> game_model::getSequence()
{
    return sequence;
}

/**
 * @brief game_model::startTimer
 */
void game_model::startTimer()
{
    timer->start(1000);
}

/**
 * @brief game_model::nextState
 * @param restartGame
 */
void game_model::nextState(bool restartGame)
{
    if (restartGame || game_state == gameState::GameOver)
    {
        game_state = gameState::Start;
    }
    else
    {
        ++game_state;
    }
    emit signalStateChange(game_state);
}

/**
 * @brief game_model::getTotalMoves
 * @return
 */
int game_model::getTotalMoves()
{
    return total_moves;
}

/**
 * @brief game_model::getTotalNumberOfRounds
 * @return
 */
int game_model::getTotalNumberOfRounds()
{
    return total_number_of_rounds;
}
