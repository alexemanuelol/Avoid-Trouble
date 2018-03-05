#ifndef PLAYER_H
#define PLAYER_H

#include "defines.h"
#include "obstacle.h"
#include "safezone.h"

#include <QPainter>
#include <QRect>

class Player : public QRect
{
public:
    Player(int x, int y, int velocity);
    ~Player();

    void paint(QPainter & painter) const;

    void checkSafe(Safezone* safezone);
    bool checkCollision(Obstacle * obstacles, int obstacleSize);

    void setVel(int velocity) { _velocity = velocity; }
    int getVel()    { return _velocity; }

    bool isSafe()   { return _isSafe; }

private:
    int _velocity;
    bool _isSafe;
};

#endif // PLAYER_H
