#include "player.h"

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
