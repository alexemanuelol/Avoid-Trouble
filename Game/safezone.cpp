#include "safezone.h"

Safezone::Safezone(int x, int y, int width, int height) : QRect(x, y, width, height)
{

}

Safezone::~Safezone()
{
    /* Delete */
}

void Safezone::paint(QPainter & painter) const
{
    /* Paint the safe zone */
    painter.fillRect(*this, Qt::gray);
}

void Safezone::checkCollision(Obstacle * obstacles, int obstacleSize)
{
    /* Collision detect of safezone and obstacles */
    for (int i = 0; i < obstacleSize; i++)
    {
        // TODO, fix collision detection of safezone and obstacles
    }
}
