#include "Point.hpp"

Point::Point() : x(0), y(0)
{
    // std::cout << "Default constructor called" << std::endl;
};

Point::Point(const float new_x, const float new_y) : x(new_x), y(new_y)
{
    // std::cout << "Overload constructor called" << std::endl;
};

Point::Point(const Point& origin) : x(origin.x), y(origin.y)
{
    // std::cout << "Copy constructor called" << std::endl;
};

Point& Point::operator = (const Point& origin)
{
    (void) origin;
    std::cerr << "Assignment not allowed: Point has const members." << std::endl;
    return *this;
}

Point::~Point() {};

const Fixed& Point::getX( void ) const
{
    return x;
}

const Fixed& Point::getY( void ) const
{
    return y;
}