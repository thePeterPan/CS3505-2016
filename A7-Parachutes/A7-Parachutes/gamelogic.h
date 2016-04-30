#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>
#include <QQueue>
#include <QTimer>
#include <QList>
#include <QVector>
#include <QDebug>

#include "Box2D/Box2D.h"
#include "temporarysprite.h"

class GameLogic : public QObject
{
    Q_OBJECT

public:
    explicit GameLogic(QObject *parent = 0, int windowWidth = 800, int windowHeight = 635, float scale = 100.0f);
    ~GameLogic();

    // Getter functions
    int getCurrentLevel();

    // Other methods
    void addWordsToQueue(int level); // Does this need to be public?

private:

    // Box2D //
    // Parameters
    b2World* World;
    float SCALE;
    int windowWidth, windowHeight, windowHeight2;
    int xScale, yScale;
    // Functions
    void setUpBox2D();
    void CreateGround(float x, float y, float width, float height);
    void createRoughGround();

    // Sprites //
    // Parameters
    QList<TemporarySprite> sprites;
    // Functions
    void addWordToWorld();
    b2Body * CreateBox(QString letter, float x, float y, float width, float height, float friction = .8, float restitution = .6, float density = 1.3);

    //void gameOver();

    // Words //
    // Parameters
    QString currentWord;
    QString previousWord;
    int currentWordIndex;
    QQueue<QString> words; // Used with test words
    QList<QString> fromDB;
    QStringList wordsList; // Used with word input from file
    bool fromFile;

    // Game Play //
    // Parameters
    int currentLevel;
    int timerSeconds;
    int timerFactor = 8;
    QTimer* timer;
    bool readyToPlay = false;
    int score;
    int missTypePenalty = 50;
    int completeWordReward = 100; //This Score bonus is multiplied by seconds left on the timer
    // Functions
    void scoreChanged(int score);
    void startNewTimer();

    // User Info and DB//
    QString username, firstName, lastName, teacher;
    int highScore, startingLevel;

    void sendScoreToDB();


signals:
    void newWord(QString word); // GameWindow::receiveNewWord
    void newLevel(int level);   // GameWindow::receiveNewLevel
    void failed();              // GameWindow::receiveFail
    void victory();             // GameWindow::receiveVictory
    void updateActionTimer(QString message);    // GameWindow::actionTimerUpdated
    void updateScore(QString score);            // GameWindow::scoreUpdated
    void gameOver(int level, int score);        // GameWindow::on_gameOver_triggered
    void levelCompleted(int level, int score);
    void requestWordList(int level, QString teacher);
    void sendScore(QString user, int level, int score);

public slots:
    void startGame();                   // GameWindow::readyToPlay
    void pause();                       // GameWindow::pauseGame
    void unPause();                     // GameWindow::unPauseGame
    void newLetterTyped(QChar letter);  // GameWindow::letterTyped
    void updateTimer();                 // Called by this->timer timeout()
    void addWordsFromFile(QStringList);
    void changeSize(int newWidth, int newHeight); // GameWindow::newSize
    void paintWorld(QPainter * painter);
    void receivedWordList(QList<QString> list);
    void receiveUserInfo(QString username, QString first, QString last, QString teacher, int level, int highScore);



    //void restart();

};

#endif // GAMELOGIC_H
