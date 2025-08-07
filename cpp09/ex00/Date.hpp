#ifndef DATE_HPP
# define DATE_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <exception>
#include <fstream>
#include <algorithm>
#include <map>

class Date
{
    private:
        int _year;
        int _month;
        int _day;

    public:
        Date();
        Date(int year, int month, int day);
        Date(const Date& origin);
        Date& operator =(const Date& origin);
        bool operator <(const Date& other) const;
        bool operator ==(const Date& other) const;
        ~Date();

        int getYear() const ;
        int getMonth() const ;
        int getDay() const ;

        class DateNotExistException;

};

std::ostream& operator<<(std::ostream& os, const Date& date);

class Date::DateNotExistException : public std::exception
{
    public:
        const char* what() const throw() ;
};


#endif