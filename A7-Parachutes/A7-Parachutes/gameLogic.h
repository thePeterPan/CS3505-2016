#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Box2D/Box2D.h"


class gameLogic
{
public:
    gameLogic();
    float getXPos();
    float getYPos();
    b2World* World;
    b2World* getWorld();

private:
    void setUpBox2D();
    b2Vec2 position;
    void CreateGround(b2World& World, float X, float Y);
    void CreateBox(b2World& World, int MouseX, int MouseY); // Spawns a box at MouseX, MouseY
    float SCALE;
    b2Vec2 Gravity;

};

#endif // GAMELOGIC_H
