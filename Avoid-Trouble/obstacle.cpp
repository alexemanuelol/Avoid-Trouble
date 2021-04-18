/*
###############################################################################
#                                                                             #
# Author: Alexander Emanuelsson                                               #
#                                                                             #
# Project: https://github.com/alexemanuelol/Avoid-Trouble-Game.git            #
#                                                                             #
###############################################################################
*/

#include "obstacle.h"

Obstacle::Obstacle() : QRect()
{
    /* Set color of the obstacle */
    _color = new QColor(100, (unsigned char) rand(), (unsigned char) rand());

    /* Set a random starting position and random velocity */
    setX(rand() % ((WINDOW_WIDTH - OBSTACLE_WIDTH) - 100 + 1) + 100);
    setY(rand() % ((WINDOW_HEIGHT - OBSTACLE_HEIGHT) - 0 + 1) + 0);

    _vx = rand() % (OBSTACLE_MAX_VEL - OBSTACLE_MIN_VEL + 1) + OBSTACLE_MIN_VEL;
    _vy = rand() % (OBSTACLE_MAX_VEL - OBSTACLE_MIN_VEL + 1) + OBSTACLE_MIN_VEL;

    /* Randomize the direction ( positive or negative velocity) */
    if (rand() % 2)
        _vx *= -1;
    if (rand() % 2)
        _vy *= -1;

    setWidth(OBSTACLE_WIDTH);
    setHeight(OBSTACLE_HEIGHT);
}

Obstacle::~Obstacle()
{
    delete _color;
}

void Obstacle::update()
{
    /* Delay to avoid fast change in direction */
    /*if (!_readyToChangeDir)
        _changeDirDelay++;
    if (_changeDirDelay == OBSTACLE_CHANGE_DIR_DELAY)
    {
        _changeDirDelay = 0;
        _readyToChangeDir = true;
    }*/

    /* Move the obstacle */
    if (_vxCounter == _vx)
    {
        moveLeft(x() + 1);
        _vxCounter = 1;
    }
    else
    {
        _vxCounter += 1;
    }

    if (_vyCounter == _vy)
    {
        moveTop(y() + 1);
        _vyCounter = 1;
    }
    else
    {
        _vyCounter += 1;
    }

    /* Wall collision bounce */
    if (center().y() <= 0)
        changeYVel();
    if (center().x() <= 0)
        changeXVel();
    if (center().y() >= WINDOW_HEIGHT)
        changeYVel();
    if (center().x() >= WINDOW_WIDTH)
        changeXVel();
}

void Obstacle::paint(QPainter & painter) const
{
    /* Paint the obstacle */
    painter.fillRect(*this, *_color);
}
