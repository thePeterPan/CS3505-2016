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
    float getXPos();
    float getYPos();
    int getCurrentLevel();
    b2World* World;
    void paintWorld(QPainter * painter);
    b2World* getWorld();
    void testSignals();
    void getWordsFromDatabase(int level);

private:
    void setUpBox2D();
    void addWordToWorld();
    b2Vec2 position;
    void CreateGround(float x, float y, float width, float height);
    void CreateBox(QString letter, float x, float y, float width, float height, float friction = .8, float restitution = .6, float density = 1.3);
    void createRoughGround();
    void scoreChanged(int score);
    //void gameOver();

    float SCALE;
    int windowWidth, windowHeight, windowHeight2;
    int xScale, yScale;

    QString currentWord;
    int currentWordIndex;
    QQueue<QString> words;
    QList<TemporarySprite> sprites;
    int currentLevel;
    int timerSeconds;
    int timerFactor = 5;
    QTimer* timer;
    int score;
    int missTypePenalty = 50;
    int completeWordReward = 100; //This Score bonus is multiplied by seconds left on the timer

    bool readyToPlay = false;

signals:
    void newWord(QString word);
    void newLevel(int level);
    void failed();
    void victory();
    void updateActionTimer(QString message);
    void updateScore(QString score);
    void gameOver();


public slots:
    void newLetterTyped(QChar letter);
    void changeSize(int newWidth, int newHeight);
    void updateTimer();
    void startNewTimer();
    void startGame();
    void pause();
    void unPause();
    //void restart();

};

#endif // GAMELOGIC_H
