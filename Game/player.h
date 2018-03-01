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

    void update();
    void paint(QPainter & painter) const;

    void setX(int x) { _x = x; _body->setX(x); }
    void setY(int y) { _y = y; _body->setY(y); }
    void setVel(int velocity) { _velocity = velocity; }

    int getX()      { return _x; }
    int getY()      { return _y; }
    int getVel()    { return _velocity; }

    QRect* getPlayer() { return _body; }

private:
    int _x, _y;
    int _velocity;
    QRect* _body;
};

#endif // PLAYER_H
