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
#include <QKeyEvent>

#include "defines.h"
#include "obstacle.h"

class Safezone;
class Player : public QRect
{
public:
    Player(int x, int y, int velocity);
    ~Player();

    void paint(QPainter & painter) const;

    bool update(QRect* safezone, Obstacle* obstacles, int obstacleSize);
    void updateKeyStates(int key, bool value);
    void updateSafe(QRect* safezone);
    void updatePos();

    bool checkCollision(Obstacle * obstacles, int obstacleSize);
    bool checkInsideVictoryDoor(QRect * victoryDoor);

    bool getSafe()              { return _isSafe; }
    void setSafe(bool isSafe)   { _isSafe = isSafe; }

    bool getStuck()             { return _isStuck; }
    void setStuck(bool isStuck) { _isStuck = isStuck; }

private:
    int _speedDiv;
    int _speedDivCounter = 0;
    bool _isSafe;
    bool _isStuck;

    bool _keyUp = false;
    bool _keyLeft = false;
    bool _keyDown = false;
    bool _keyRight = false;
};

#endif /* PLAYER_H */
