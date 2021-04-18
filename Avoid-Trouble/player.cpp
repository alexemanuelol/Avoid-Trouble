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

#include "player.h"

Player::Player(int x, int y, int velocity) : QRect(x, y, PLAYER_WIDTH, PLAYER_HEIGHT)
{
    _velocity = velocity;
}

Player::~Player()
{
    /* Delete */
}

void Player::paint(QPainter & painter) const
{
    /* Paint the player */
    painter.fillRect(*this, Qt::white);
}

void Player::updateSafe(Safezone* safezone)
{
    /* Check if player is inside safezone */
    if (safezone->contains(topLeft()) &&
        safezone->contains(topRight()) &&
        safezone->contains(bottomRight()) &&
        safezone->contains(bottomLeft()))
        _isSafe = true;
    else
        _isSafe = false;
}

bool Player::checkCollision(Obstacle * obstacles, int obstacleSize)
{
    /* Collision detect of player and obstacles */
    for (int i = 0; i < obstacleSize; i++)
    {
        if ((contains(obstacles[i].topLeft()) ||
             contains(obstacles[i].topRight()) ||
             contains(obstacles[i].bottomLeft()) ||
             contains(obstacles[i].bottomRight()) ||
             contains(obstacles[i].center())) && !_isSafe)
            return false;
    }
    return true;
}

bool Player::checkVictoryDoor(QRect * victoryDoor)
{
    /* Check if player has reached the victory door */
    if (victoryDoor->contains(QPoint(x() + PLAYER_WIDTH/2, y() + PLAYER_HEIGHT/2)))
        return true;
    else
        return false;
}
