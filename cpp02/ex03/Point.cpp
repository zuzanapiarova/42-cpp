#include "Point.hpp"

Point::Point() : x(), y()
{
    // std::cout << "Point default constructor called" << std::endl;
};

Point::Point(const float new_x, const float new_y) : x(new_x), y(new_y)
{
    // std::cout << "Point overload constructor called" << std::endl;
};

Point::Point(const Point& origin) : x(origin.x), y(origin.y)
{
    // std::cout << "Point copy constructor called" << std::endl;
};

// cannot be allowed - class Point has const members
Point& Point::operator = (const Point& origin)
{
    std::cout << "Point copy assignment operator called" << std::endl;
    (void) origin;
    std::cerr << "Assignment not allowed: Point has const members." << std::endl;
    return *this;
}

Point::~Point()
{
    // std::cout << "Point destructor called" << std::endl;
};

const Fixed& Point::getX( void ) const
{
    return x;
}

const Fixed& Point::getY( void ) const
{
    return y;
}