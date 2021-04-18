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
