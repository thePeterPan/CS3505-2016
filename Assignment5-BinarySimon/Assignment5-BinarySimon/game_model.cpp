#include "game_model.h"

game_model::game_model(QObject *parent) :
    QObject(parent), game_state(gameState::Start), total_number_of_rounds(0), total_moves(0),
    current_pattern_index(0)
{
    // Start off with a two patterns.
    srand(10);
    add_to_pattern();
    add_to_pattern();

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
 * @brief game_model::add_to_pattern
 */
void game_model::add_to_pattern()
{
//    srand((unsigned)time(0));
//    int floor = 0, ceiling = 20, range = (ceiling - floor);
//    int rnd = floor + int((range * rand()) / (RAND_MAX + 1.0));

//    qDebug() << "test";

    int rnd = rand() % 2;

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

/**
 * @brief game_model::checkPattern
 * @param color
 */
void game_model::checkPattern(char color)
{
    if (pattern[current_pattern_index] == color)
    {
        ++current_pattern_index;
        if (current_pattern_index == (int) pattern.size())
        {
            emit signalPatternComplete();
        }
    }
    else
    {
        // if next color does not match pattern emit lose signal
        emit signalGameOver();
    }
}

/**
 * @brief game_model::getPattern
 * @return
 */
std::vector<char> game_model::getPattern()
{
    return pattern;
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
    } else {
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
