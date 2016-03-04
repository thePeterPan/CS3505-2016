#include "game_model.h"

#include <ctime>    // time()

game_model::game_model(QObject *parent) :
    QObject(parent) { }

/**
 * @brief game_model::~game_model
 */
game_model::~game_model() { }

/**
 * Tried to put this in the constructor, but I assume that the constructor gets
 * called before the signals and slots are connected, therefore this is needed
 * to be called after the everything gets connected.

 * @brief game_model::gameStart
 */
void game_model::gameStart()
{
    srand((unsigned)time(0));

    // Reset sequence
    sequence.clear();
    add_color_to_sequence();
    add_color_to_sequence();

    // Reset all stats.
    current_sequence_progress = 0;
    display_sequence_delay = 800;
    total_number_of_rounds = 0;
    total_moves = 0;

    // Tell the view to initialize in start mode:
    game_state = gameState::Start;
    emit signalStateChange(game_state);
}

/**
 * @brief game_model::add_color_to_sequence
 */
void game_model::add_color_to_sequence()
{
//    srand((unsigned)time(0));
//    int floor = 0, ceiling = 20, range = (ceiling - floor);
//    int rnd = floor + int((range * rand()) / (RAND_MAX + 1.0));

//    qDebug() << "test";

    int rnd = rand() % 4;

    switch(rnd)
    {
    case 0:
        sequence << "blue";
        break;
    case 1:
        sequence << "red";
        break;
    case 2:
        sequence << "green";
        break;
    case 3:
        sequence << "yellow";
        break;
    default:
        sequence << "error";
    }
}

/**
 * @brief game_model::checkSequenceNext
 * @param color
 */
void game_model::checkSequenceNext(QString color)
{
    // If the given color matches the current location of the sequence
    if (sequence[current_sequence_progress] == color)
    {
        // Add to the stat counters
        ++current_sequence_progress;
        ++total_moves;
        // Tell the
        emit signalProgressBarUpdate(current_sequence_progress);

        if (current_sequence_progress == (int) sequence.size())
        {
            current_sequence_progress = 0;
            nextRound();
        }
    }
    else
    {
        // if next color does not match pattern emit lose signal
        game_state = gameState::GameOver;
        emit signalStateChange(game_state);
    }
}

/**
 * @brief game_model::nextRound
 */
void game_model::nextRound()
{
    qDebug() << "Next Round!";

    add_color_to_sequence();
    // speed up the sequence display
    display_sequence_delay -= 50;
    ++total_number_of_rounds;
    // Give the player a little bit of time to get ready.
    game_state = gameState::DisplaySequence;
    QTimer::singleShot(1000, this, [=]() { emit signalStateChange(game_state); });
}

/**
 * @brief game_model::nextState
 * @param restartGame
 */
void game_model::nextState(bool restartGame)
{
    if (restartGame || game_state == gameState::GameOver)
    {
        // If we receive a command to restart the game, or if the game is over
        // restart the game.
        gameStart();
        return;
    }
    // Otherwise, move to the next state of the game and tell the view.
    ++game_state;
    emit signalStateChange(game_state);
}

/**
 * @brief game_model::getSequence
 * @return
 */
QStringList game_model::getSequence()
{
    return sequence;
}

/**
 * @brief game_model::getDisplaySequenceDelay
 * @return
 */
int game_model::getDisplaySequenceDelay()
{
    return display_sequence_delay;
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
