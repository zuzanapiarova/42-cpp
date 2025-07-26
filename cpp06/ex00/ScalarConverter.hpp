#ifndef SCALAR_CONVERTER_H
# define SCALAR_CONVERTER_H

#include <iostream>
#include <string>
#include <limits>
#include <cmath> 
#include <iomanip> //setprecision
#include <sstream> // string streams

class ScalarConverter
{
    private:
        ScalarConverter();

    public:
        static void convert( const std::string& s);

};

#endif