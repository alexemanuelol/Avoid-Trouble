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
    int spawnBorder = 10;

    /* Set color of the obstacle */
    _color = new QColor(100, (unsigned char) rand(), (unsigned char) rand());

    /* Set a random starting position */
    setX(SAFE_ZONE_WIDTH + spawnBorder + (rand() % ((APP_WIDTH - spawnBorder) - SAFE_ZONE_WIDTH + spawnBorder + 1)));
    setY(spawnBorder + (rand() % ((APP_HEIGHT - spawnBorder) - spawnBorder + 1)));

    /* Set random speed */
    _speedDivX = OBS_MIN_SPEED + (rand() % (OBS_MAX_SPEED - OBS_MIN_SPEED + 1));
    _speedDivY = OBS_MIN_SPEED + (rand() % (OBS_MAX_SPEED - OBS_MIN_SPEED + 1));

    /* Randomize the direction ( positive or negative velocity) */
    _dirX = (rand() % 2) ? 1 : -1;
    _dirY = (rand() % 2) ? 1 : -1;

    /* Set size */
    setWidth(OBS_WIDTH);
    setHeight(OBS_HEIGHT);
}

Obstacle::~Obstacle()
{
    delete _color;
}

void Obstacle::paint(QPainter & painter) const
{
    painter.fillRect(*this, *_color);
}

void Obstacle::update()
{
    /* Move the obstacle */
    if (_speedDivCounterX == _speedDivX)
    {
        _speedDivCounterX = 0;
        moveLeft(x() + _dirX);
    }
    else
    {
        _speedDivCounterX += 1;
    }

    if (_speedDivCounterY == _speedDivY)
    {
        _speedDivCounterY = 0;
        moveTop(y() + _dirY);
    }
    else
    {
        _speedDivCounterY += 1;
    }

    /* Wall collision bounce */
    if (topLeft().y() < 0)
    {
        changeDirY();
        moveTop(y() + (_dirY * 2));
    }
    else if (bottomRight().y() > APP_HEIGHT)
    {
        changeDirY();
        moveTop(y() + (_dirY * 2));
    }

    if (topLeft().x() < SAFE_ZONE_WIDTH)
    {
        changeDirX();
        moveLeft(x() + (_dirX * 2));
    }
    else if (bottomRight().x() > APP_WIDTH)
    {
        changeDirX();
        moveLeft(x() + (_dirX * 2));
    }
}

