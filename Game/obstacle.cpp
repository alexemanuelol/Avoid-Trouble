#include "obstacle.h"

Obstacle::Obstacle()
{
    _x = rand() % ((WINDOW_WIDTH - OBSTACLE_WIDTH) - 100 + 1) + 100;
    _y = rand() % ((WINDOW_HEIGHT - OBSTACLE_HEIGHT) - 0 + 1) + 0;
    _vx = rand() % (OBSTACLE_MAX_VEL - OBSTACLE_MIN_VEL + 1) + OBSTACLE_MIN_VEL;
    _vy = rand() % (OBSTACLE_MAX_VEL - OBSTACLE_MIN_VEL + 1) + OBSTACLE_MIN_VEL;

    if (rand() % 2)
        _vx *= -1;
    if (rand() % 2)
        _vy *= -1;

    _body = new QRect(_x, _y, OBSTACLE_WIDTH, OBSTACLE_HEIGHT);
}

Obstacle::~Obstacle()
{
    delete _body;
}

void Obstacle::update()
{
    _body->moveTop(_body->y() + _vy);
    _body->moveLeft(_body->x() + _vx);

    /* Wall collision bounce */
    if (_body->center().y() <= 0)
        _vy *= -1;
    if (_body->center().x() <= 0)
        _vx *= -1;
    if (_body->center().y() >= WINDOW_HEIGHT)
        _vy *= -1;
    if (_body->center().x() >= WINDOW_WIDTH)
        _vx *= -1;


}

void Obstacle::paint(QPainter & painter) const
{
    painter.fillRect(*_body, Qt::red);
}
