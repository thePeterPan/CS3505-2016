#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <QQueue>
#include <QObject>
#include "Box2D/Box2D.h"



class gameLogic : public QObject
{
    Q_OBJECT

public:
    explicit gameLogic(QObject *parent = 0, float scale = 100.0f);
    float getXPos();
    float getYPos();
    b2World* World;
    b2World* getWorld();
    void testSignals();

private:
    void setUpBox2D();
    b2Vec2 position;
    void CreateGround(float width, float height);
    void CreateBox(float x, float y, float width, float height, float friction = .8, float restitution = .6, float density = 1.3);

    float SCALE;

    b2Vec2 Gravity;
    QString currentWord;
    int currentWordIndex;
    QQueue<QString> words;

signals:
    void newWord(QString word);
    void newLevel(int level);
    void failed();
    void victory();

public slots:
    void newLetterTyped(char letter);

};

#endif // GAMELOGIC_H
