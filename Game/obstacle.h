#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "defines.h"
#include "player.h"

#include <QPainter>
#include <QRect>

class Obstacle : public QRect
{
public:
    Obstacle();
    ~Obstacle();

    void update();
    void paint(QPainter & painter) const;

    void setVelX(float vx) { _vx = vx; }
    void setVelY(float vy) { _vy = vy; }

    float getVelX()    { return _vx; }
    float getVelY()    { return _vy; }

private:
    float _vx, _vy;
};

#endif // OBSTACLE_H
