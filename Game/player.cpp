#include "player.h"

Player::Player(int x, int y, int velocity)
{
    _x = x;
    _y = y;
    _velocity = velocity;
    _body = new QRect(x, y, PLAYER_WIDTH, PLAYER_HEIGHT);
}

Player::~Player()
{
    delete _body;
}

void Player::paint(QPainter & painter) const
{
    painter.fillRect(_x, _y, PLAYER_WIDTH, PLAYER_HEIGHT, Qt::white);
}
