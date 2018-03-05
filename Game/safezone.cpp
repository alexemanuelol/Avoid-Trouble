#include "safezone.h"

Safezone::Safezone(int x, int y, int width, int height) : QRect(x, y, width, height)
{

}

Safezone::~Safezone()
{
    //delete this;
}

void Safezone::paint(QPainter & painter) const
{
    painter.fillRect(*this, Qt::gray);
}
