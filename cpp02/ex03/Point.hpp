#ifndef POINT_H
# define POINT_H

#include "Fixed.hpp"

#include <iostream>
#include <cmath>
#include <limits>

class Point
{
    private:
        const Fixed x;
        const Fixed y;

    public:
        Point();
        Point(const float new_x, const float new_y);
        Point(const Point& origin);
        Point& operator = (const Point& origin); // copy assignment operator
        ~Point();

        const Fixed& getX( void ) const ;
        const Fixed& getY( void ) const ;

};

#endif