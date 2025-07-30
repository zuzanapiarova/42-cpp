#include "Fixed.hpp"
#include "Point.hpp"

// !! fix this - it creates unneccesary points always
bool bsp(const Point& a, const Point& b, const Point& c, const Point& p)
{
    float w1;
    float w2;

    w1 = (a.getX() * (c.getY() - a.getY()) + (p.getY() - a.getY())*(c.getX() - a.getX()) - p.getX() * (c.getY() - a.getY())).toFloat()
       / ((b.getY() - a.getY()) * (c.getX() - a.getY()) - (b.getX() - a.getX()) * (c.getY() - a.getY())).toFloat();
    w2 = (p.getY().toFloat() - a.getY().toFloat() - w1 * (b.getY() - a.getY()).toFloat()) / (c.getY() - a.getY()).toFloat();

    return (w1 > 0 && w2 > 0 && (w1 + w2 < 1)) ? true : false;
}