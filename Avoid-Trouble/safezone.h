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
