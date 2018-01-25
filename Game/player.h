#ifndef PLAYER_H
#define PLAYER_H

#include "defines.h"

#include <QPainter>
#include <QRect>

class Player
{
public:
    Player(int x, int y, int velocity);
    ~Player();

    void paint(QPainter & painter) const;

    void setX(int x) { _x = x; }
    void setY(int y) { _y = y; }
    void setVel(int velocity) { _velocity = velocity; }

    int getX()      { return _x; }
    int getY()      { return _y; }
    int getVel()    { return _velocity; }

private:
    int _x, _y;
    int _velocity;
    QRect* _body;
};

#endif // PLAYER_H
