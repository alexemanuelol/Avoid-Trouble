/*
###############################################################################
#                                                                             #
# Author: Alexander Emanuelsson                                               #
#                                                                             #
# Project: https://github.com/alexemanuelol/Avoid-Trouble-Game.git            #
#                                                                             #
###############################################################################
*/

#include "safezone.h"

Safezone::Safezone(int x, int y, int width, int height) : QRect(x, y, width, height)
{
    /* Polygons are used to devide the safezone into 4 different parts
       just to easier make out at which side the obstacle hit the safezone */
    _leftPolygon    = new QPolygon();
    _topPolygon     = new QPolygon();
    _rightPolygon   = new QPolygon();
    _bottomPolygon  = new QPolygon();

    int left[] = { x, y, x, y + SAFE_ZONE_HEIGHT, x + (SAFE_ZONE_WIDTH/2), y + (SAFE_ZONE_HEIGHT/2) };
    _leftPolygon->setPoints(3, left);

    int top[] = { x, y, x + SAFE_ZONE_WIDTH, y, x + (SAFE_ZONE_WIDTH/2), y + (SAFE_ZONE_HEIGHT/2) };
    _topPolygon->setPoints(3, top);

    int right[] = { x + SAFE_ZONE_WIDTH, y, x + SAFE_ZONE_WIDTH, y + SAFE_ZONE_HEIGHT, x + (SAFE_ZONE_WIDTH/2), y + (SAFE_ZONE_HEIGHT/2) };
    _rightPolygon->setPoints(3, right);

    int bottom[] = { x, y + SAFE_ZONE_HEIGHT, x + SAFE_ZONE_WIDTH, y + SAFE_ZONE_HEIGHT, x + (SAFE_ZONE_WIDTH/2), y + (SAFE_ZONE_HEIGHT/2) };
    _bottomPolygon->setPoints(3, bottom);
}

Safezone::~Safezone()
{
    delete _leftPolygon;
    delete _topPolygon;
    delete _rightPolygon;
    delete _bottomPolygon;
}

void Safezone::paint(QPainter & painter) const
{
    /* Paint the safe zone */
    if (_safeStuckDelay == 0)
        painter.fillRect(*this, Qt::red);
    else
        painter.fillRect(*this, Qt::darkRed);

}

void Safezone::checkCollision(Obstacle * obstacles, int obstacleSize)
{
    /* Collision detect of safezone and obstacles */
    for (int i = 0; i < obstacleSize; i++)
    {
        if (getLeftPol().containsPoint(obstacles[i].center(), Qt::OddEvenFill))
            obstacles[i].changeXVel();
        else if (getTopPol().containsPoint(obstacles[i].center(), Qt::OddEvenFill))
            obstacles[i].changeYVel();
        else if (getRightPol().containsPoint(obstacles[i].center(), Qt::OddEvenFill))
            obstacles[i].changeXVel();
        else if (getBottomPol().containsPoint(obstacles[i].center(), Qt::OddEvenFill))
            obstacles[i].changeYVel();
    }
}

void Safezone::updateSafeStuck(Player * player)
{
    if (_safeStuckDelay == 0)
        player->setSafeStuck(false);
    else
    {
        player->setSafeStuck(true);
        _safeStuckDelay--;
    }
}
