#include "obstacle.h"

Obstacle::Obstacle() : QRect()
{
    this->setX(rand() % ((WINDOW_WIDTH - OBSTACLE_WIDTH) - 100 + 1) + 100);
    this->setY(rand() % ((WINDOW_HEIGHT - OBSTACLE_HEIGHT) - 0 + 1) + 0);
    _vx = rand() % (OBSTACLE_MAX_VEL - OBSTACLE_MIN_VEL + 1) + OBSTACLE_MIN_VEL;
    _vy = rand() % (OBSTACLE_MAX_VEL - OBSTACLE_MIN_VEL + 1) + OBSTACLE_MIN_VEL;

    if (rand() % 2)
        _vx *= -1;
    if (rand() % 2)
        _vy *= -1;

    this->setWidth(OBSTACLE_WIDTH);
    this->setHeight(OBSTACLE_HEIGHT);
}

Obstacle::~Obstacle()
{
    //delete this;
}

void Obstacle::update()
{
    this->moveTop(this->y() + _vy);
    this->moveLeft(this->x() + _vx);

    /* Wall collision bounce */
    if (this->center().y() <= 0)
        _vy *= -1;
    if (this->center().x() <= 0)
        _vx *= -1;
    if (this->center().y() >= WINDOW_HEIGHT)
        _vy *= -1;
    if (this->center().x() >= WINDOW_WIDTH)
        _vx *= -1;


}

void Obstacle::paint(QPainter & painter) const
{
    painter.fillRect(this->x(), this->y(), OBSTACLE_WIDTH, OBSTACLE_HEIGHT, Qt::red);
}
