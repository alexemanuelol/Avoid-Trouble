#ifndef SAFEZONE_H
#define SAFEZONE_H

#include <QPainter>
#include <QRect>

#include "defines.h"
#include "obstacle.h"

class Safezone : public QRect
{
public:
    Safezone(int x, int y, int width, int height);
    ~Safezone();

    void paint(QPainter & painter) const;

    void checkCollision(Obstacle * obstacles, int obstacleSize);

private:
    int _velocity;
};

#endif // SAFEZONE_H
