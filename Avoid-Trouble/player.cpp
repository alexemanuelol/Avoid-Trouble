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

Player::Player(int x, int y, int speedDiv) : QRect(x, y, PLAYER_WIDTH, PLAYER_HEIGHT)
{
    _speedDiv = MAX_SPEED - speedDiv;
}

Player::~Player()
{
}

void Player::paint(QPainter & painter) const
{
    painter.fillRect(*this, Qt::white);                         /* Paint the player */
}

bool Player::update(QRect* safezone, Obstacle* obstacles, int obstacleSize)
{
    bool gameActive;

    updateSafe(safezone);                                       /* Update if player is in safezone */
    gameActive = checkCollision(obstacles, obstacleSize);       /* Check collision with obstacles */
    updatePos();                                                /* Update player position */

    return gameActive;
}

void Player::updateKeyStates(int key, bool value)
{
    /* Check key press */
    switch (key)
    {
    case Qt::Key_Up:
    case Qt::Key_W:
        _keyUp = value;
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        _keyLeft = value;
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        _keyDown = value;
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        _keyRight = value;
        break;
    default:
        break;
    }
}

void Player::updateSafe(QRect* safezone)
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

void Player::updatePos()
{
    if (_speedDivCounter != _speedDiv)
    {
        _speedDivCounter++;
        return;
    }

    if (_isStuck)
    {
        _speedDivCounter = 0;
        return;
    }

    if (_keyUp && _keyLeft)                                     /* Move "North west" */
    {
        if (x() > 0)
        {
            moveLeft(x() - 1);
        }
        if (y() > 0)
        {
            moveTop(y() - 1);
        }
    }
    else if (_keyUp && _keyRight)                               /* Move "North east" */
    {
        if (x() < (APP_WIDTH - PLAYER_WIDTH))
        {
            moveLeft(x() + 1);
        }
        if (y() > 0)
        {
            moveTop(y() - 1);
        }
    }
    else if (_keyDown && _keyLeft)                              /* Move "South west" */
    {
        if (x() > 0)
        {
            moveLeft(x() - 1);
        }
        if (y() < (APP_HEIGHT - PLAYER_HEIGHT))
        {
            moveTop(y() + 1);
        }
    }
    else if (_keyDown && _keyRight)                             /* Move "South east" */
    {
        if (x() < (APP_WIDTH - PLAYER_WIDTH))
        {
            moveLeft(x() + 1);
        }
        if (y() < (APP_HEIGHT - PLAYER_HEIGHT))
        {
            moveTop(y() + 1);
        }
    }
    else if (_keyUp && y() > 0)                                 /* Move "North" */
    {
        moveTop(y() - 1);
    }
    else if (_keyLeft && x() > 0)                               /* Move "West" */
    {
        moveLeft(x() - 1);
    }
    else if (_keyDown && y() < (APP_HEIGHT - PLAYER_HEIGHT))    /* Move "South" */
    {
        moveTop(y() + 1);
    }
    else if (_keyRight && x() < (APP_WIDTH - PLAYER_WIDTH))     /* Move "East" */
    {
        moveLeft(x() + 1);
    }

    _speedDivCounter = 0;
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

bool Player::checkInsideVictoryDoor(QRect * victoryDoor)
{
    /* Check if player has reached the victory door */
    if (victoryDoor->contains(QPoint(x() + PLAYER_WIDTH/2, y() + PLAYER_HEIGHT/2)))
    {
        return true;
    }

    return false;
}
