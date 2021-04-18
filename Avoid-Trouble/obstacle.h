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

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QPainter>
#include <QRect>
#include <QColor>

#include "defines.h"

class Obstacle : public QRect
{
public:
    Obstacle();
    ~Obstacle();

    void    paint(QPainter & painter) const;
    void    update();

    void    setVelX(float vx)   { _vx = vx; }
    void    setVelY(float vy)   { _vy = vy; }

    float   getVelX()           { return _vx; }
    float   getVelY()           { return _vy; }

    void    changeXVel()        { _vx *= -1; }
    void    changeYVel()        { _vy *= -1; }

private:
    QColor*     _color;
    float       _vx, _vy;
    float       _vxCounter = 1, _vyCounter = 1;
    int         _changeDirDelay = 0;
    bool        _readyToChangeDir = true;
};

#endif // OBSTACLE_H
