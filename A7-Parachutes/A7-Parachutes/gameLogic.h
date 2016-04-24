#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <QQueue>
#include <QObject>
#include "Box2D/Box2D.h"
#include <QString>
#include <QList>
#include "temporarysprite.h"


class gameLogic : public QObject
{
    Q_OBJECT

public:
    explicit gameLogic(QObject *parent = 0, float scale = 100.0f);
    float getXPos();
    float getYPos();
    b2World* World;
    void paintWorld(QPainter * painter);
    b2World* getWorld();
    void testSignals();
    void getWordsFromDatabase(int level);

private:
    void setUpBox2D();
    b2Vec2 position;
    void CreateGround(float x, float y, float width, float height);
    void CreateBox(QString letter, float x, float y, float width, float height, float friction = .8, float restitution = .6, float density = 1.3);

    float SCALE;

    b2Vec2 Gravity;
    QString currentWord;
    int currentWordIndex;
    QQueue<QString> words;
    QList<TemporarySprite> sprites;
    int currentLevel;

signals:
    void newWord(QString word);
    void newLevel(int level);
    void failed();
    void victory();

public slots:
    void newLetterTyped(QChar letter);

};

#endif // GAMELOGIC_H
