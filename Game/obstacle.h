#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QPainter>
#include <QRect>

#include "defines.h"

class Obstacle : public QRect
{
public:
    Obstacle();
    ~Obstacle();

    void paint(QPainter & painter) const;
    void update();

    void setVelX(float vx) { _vx = vx; }
    void setVelY(float vy) { _vy = vy; }

    float getVelX()    { return _vx; }
    float getVelY()    { return _vy; }

    void changeXVel()	{ _vx *= -1; }
    void changeYVel()	{ _vy *= -1; }

private:
    float _vx, _vy;
};

#endif // OBSTACLE_H
