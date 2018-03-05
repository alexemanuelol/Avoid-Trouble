#include "player.h"
#include "obstacle.h"
#include <iostream>

Player::Player(int x, int y, int velocity) : QRect(x, y, PLAYER_WIDTH, PLAYER_HEIGHT)
{
    _velocity = velocity;
}

Player::~Player()
{
    //delete this;
}

void Player::paint(QPainter & painter) const
{
    //painter.fillRect(this->x(), this->y(), PLAYER_WIDTH, PLAYER_HEIGHT, Qt::white);
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
    // TODO: FIX COLLISION DETECT FOR OBSTACLES AND PLAYER
    /* Collision detect of player and obstacles */
    for (int i = 0; i < obstacleSize; i++)
    {
        if ((this->contains(obstacles[i].topLeft()) ||
             this->contains(obstacles[i].topRight()) ||
             this->contains(obstacles[i].bottomLeft()) ||
             this->contains(obstacles[i].bottomRight()) ||
             this->contains(obstacles[i].center())) && !_isSafe)
            return false;
        else
            return true;
    }
}
