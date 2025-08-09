#ifndef SCALAR_CONVERTER_HPP
# define SCALAR_CONVERTER_HPP

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
        ScalarConverter(const ScalarConverter& origin);
        ScalarConverter& operator =(const ScalarConverter& origin);
        ~ScalarConverter();

    public:
        static void convert( const std::string& s);

};

#endif