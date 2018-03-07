/*
###############################################################################
#                                                                             #
# Author: Alexander Emanuelsson                                               #
#                                                                             #
# Project: https://github.com/alexemanuelol/Avoid-Trouble-Game.git            #
#                                                                             #
###############################################################################
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

void Player::checkSafe(Safezone* safezone)
{
    /* Check if player is inside safezone */
    if (safezone->contains(this->topLeft()) &&
        safezone->contains(this->topRight()) &&
        safezone->contains(this->bottomRight()) &&
        safezone->contains(this->bottomLeft()))
        _isSafe = true;
    else
        _isSafe = false;
}

bool Player::checkCollision(Obstacle * obstacles, int obstacleSize)
{
    /* Collision detect of player and obstacles */
    for (int i = 0; i < obstacleSize; i++)
    {
        if ((this->contains(obstacles[i].topLeft()) ||
             this->contains(obstacles[i].topRight()) ||
             this->contains(obstacles[i].bottomLeft()) ||
             this->contains(obstacles[i].bottomRight()) ||
             this->contains(obstacles[i].center())) && !_isSafe)
            return false;
    }
    return true;
}

bool Player::checkVictoryDoor(QRect * victoryDoor)
{
    /* Check if player has reached the victory door */
    if (victoryDoor->contains(QPoint(this->x() + PLAYER_WIDTH/2, this->y() + PLAYER_HEIGHT/2)))
        return true;
    else
        return false;
}
