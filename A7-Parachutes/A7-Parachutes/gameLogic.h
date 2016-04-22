#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <QQueue>
#include <QObject>
#include "Box2D/Box2D.h"


class gameLogic : public QObject
{
    Q_OBJECT

public:
    explicit gameLogic(QObject *parent = 0);
    float getXPos();
    float getYPos();
    b2World* World;
    b2World* getWorld();
    void testSignals();
    void getWordsFromDatabase();

private:
    void setUpBox2D();
    b2Vec2 position;
    void CreateGround(b2World& World, float X, float Y);
    void CreateBox(b2World& World, int MouseX, int MouseY); // Spawns a box at MouseX, MouseY
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
