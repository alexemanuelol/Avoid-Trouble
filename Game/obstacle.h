#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "defines.h"
#include "player.h"

#include <QPainter>
#include <QRect>

class Obstacle
{
public:
    Obstacle();
    ~Obstacle();

    void update();
    void paint(QPainter & painter) const;

    void setX(int x) { _x = x; }
    void setY(int y) { _y = y; }
    void setVelX(float vx) { _vx = vx; }
    void setVelY(float vy) { _vy = vy; }

    int getX()      { return _x; }
    int getY()      { return _y; }
    float getVelX()    { return _vx; }
    float getVelY()    { return _vy; }

    QRect* getObstacle() {return _body; }

private:
    int _x, _y;
    float _vx, _vy;
    QRect* _body;
};

#endif // OBSTACLE_H
