/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
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
