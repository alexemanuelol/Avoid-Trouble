#ifndef PLAYER_H
#define PLAYER_H

#include "defines.h"

#include <QPainter>
#include <QRect>

class Player : public QRect
{
public:
    Player(int x, int y, int velocity);
    ~Player();

    void paint(QPainter & painter) const;

    void setVel(int velocity) { _velocity = velocity; }
    int getVel()    { return _velocity; }

private:
    int _velocity;
};

#endif // PLAYER_H
