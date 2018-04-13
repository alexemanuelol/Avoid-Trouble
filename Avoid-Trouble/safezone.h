/*
###############################################################################
#                                                                             #
# Author: Alexander Emanuelsson                                               #
#                                                                             #
# Project: https://github.com/alexemanuelol/Avoid-Trouble-Game.git            #
#                                                                             #
###############################################################################
*/

#ifndef SAFEZONE_H
#define SAFEZONE_H

#include <QPainter>
#include <QRect>
#include <QPolygon>

#include "defines.h"
#include "player.h"
#include "obstacle.h"

class Player;
class Safezone : public QRect
{
public:
    Safezone(int x, int y, int width, int height);
    ~Safezone();

    void        paint(QPainter & painter) const;

    void        checkCollision(Obstacle * obstacles, int obstacleSize);

    void        updateSafeStuck(Player * player);
    void        setSafeStuckDelayTime(int time)     { _safeStuckDelay = time; }

    QPolygon    getLeftPol()    const   { return *_leftPolygon; }
    QPolygon    getTopPol()     const   { return *_topPolygon; }
    QPolygon    getRightPol()   const   { return *_rightPolygon; }
    QPolygon    getBottomPol()  const   { return *_bottomPolygon; }

private:
    int         _velocity;
    int         _safeStuckDelay;
    QPolygon*   _leftPolygon;
    QPolygon*   _topPolygon;
    QPolygon*   _rightPolygon;
    QPolygon*   _bottomPolygon;
};

#endif // SAFEZONE_H
