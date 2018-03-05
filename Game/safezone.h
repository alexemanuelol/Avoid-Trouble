#ifndef SAFEZONE_H
#define SAFEZONE_H

#include "defines.h"

#include <QPainter>
#include <QRect>

class Safezone : public QRect
{
public:
    Safezone(int x, int y, int width, int height);
    ~Safezone();

    void paint(QPainter & painter) const;

private:
    int _velocity;
};

#endif // SAFEZONE_H
