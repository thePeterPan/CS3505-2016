#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <QQueue>
#include <QTimer>
#include <QObject>
#include "Box2D/Box2D.h"
#include <QString>
#include <QList>
#include "temporarysprite.h"


class gameLogic : public QObject
{
    Q_OBJECT

public:
    explicit gameLogic(QObject *parent = 0, int windowWidth = 800, int windowHeight = 635, float scale = 100.0f);
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

    float SCALE;
    int windowWidth, windowHeight;
    int xScale, yScale;

    QString currentWord;
    int currentWordIndex;
    QQueue<QString> words;
    QList<TemporarySprite> sprites;
    int currentLevel;
    int timerSeconds;
    int timerFactor = 5;
    QTimer* timer;

    bool readyToPlay = false;

signals:
    void newWord(QString word);
    void newLevel(int level);
    void failed();
    void victory();
    void updateActionTimer(QString message);


public slots:
    void newLetterTyped(QChar letter);
    void changeHeight(int);
    void changeWidth(int);
    void updateTimer();
    void startNewTimer();
    void startGame();

};

#endif // GAMELOGIC_H
