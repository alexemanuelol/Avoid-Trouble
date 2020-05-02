/*
###############################################################################
#                                                                             #
# Author: Alexander Emanuelsson                                               #
#                                                                             #
# Project: https://github.com/alexemanuelol/Avoid-Trouble-Game.git            #
#                                                                             #
###############################################################################
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <QPainter>
#include <QRect>

#include "defines.h"
#include "safezone.h"
#include "obstacle.h"

class Safezone;
class Player : public QRect
{
public:
    Player(int x, int y, int velocity);
    ~Player();

    void    paint(QPainter & painter) const;

    void    updateSafe(Safezone* safezone);
    bool    checkCollision(Obstacle * obstacles, int obstacleSize);
    bool    checkVictoryDoor(QRect * victoryDoor);

    void    setVel(int velocity)            { _velocity = velocity; }
    int     getVel()                        { return _velocity; }

    void 	setSafe(bool isSafe)			{ _isSafe = isSafe; }
    bool	getSafe()						{ return _isSafe; }

    void    setSafeStuck(bool safeStuck)    { _isSafeStuck = safeStuck; }
    bool    getSafeStuck()                  { return _isSafeStuck; }

private:
    int     _velocity;
    bool    _isSafe;
    bool    _isSafeStuck;
};

#endif // PLAYER_H
