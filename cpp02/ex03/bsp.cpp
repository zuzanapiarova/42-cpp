#include "Fixed.hpp"
#include "Point.hpp"

bool bsp( Point const a, Point const b, Point const c, Point const p )
{
    float w1;
    float w2;

    w1 = (a.getX() * (c.getY() - a.getY()) + (p.getY() - a.getY())*(c.getX() - a.getX()) - p.getX() * (c.getY() - a.getY())).toFloat()
       / ((b.getY() - a.getY()) * (c.getX() - a.getY()) - (b.getX() - a.getX()) * (c.getY() - a.getY())).toFloat();
    w2 = (p.getY().toFloat() - a.getY().toFloat() - w1 * (b.getY() - a.getY()).toFloat()) / (c.getY() - a.getY()).toFloat();

    return (w1 > 0 && w2 > 0 && (w1 + w2 < 1)) ? true : false;
}