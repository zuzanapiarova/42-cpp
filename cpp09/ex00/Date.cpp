#include "Date.hpp"

bool isLeapYear(int year)
{
    return (year % 4 == 0);
};

bool checkDate(unsigned int year, unsigned int month, unsigned int day)
{
    if (year < 0)
        return false;
    if (month > 12 || month <= 0)
        return false;
    bool shortMonth = 0;
    if (month == 2 || month == 4 || month == 6 || month == 9 || month == 11)
        shortMonth = true;
    if (day <= 0 || day > 31 || (shortMonth && day > 30) || (month == 2 && day > 29))
        return false;
    if (day > 28 && month == 2 && !isLeapYear(year))
        return false;
    return true;
};

Date::Date() : _year(0), _month(1), _day(1)
{
    // std::cout << "Date default constructor called - set to 0." <<std::endl;
};

Date::Date(int year, int month, int day)
{
    // std::cout << "Date overload constructor called. " <<std::endl;
    if (checkDate(year, month, day) == false)
        throw Date::DateNotExistException();
    _year = year;
    _month = month;
    _day = day;
};

Date::Date(const Date& origin) : _year(origin._year), _month(origin._month), _day(origin._day)
{
    // std::cout << "Date copy constructor called. " <<std::endl;
};

Date& Date::operator =(const Date& origin)
{    
    // std::cout << "Date copy assignment operator called. " <<std::endl;
    if (this != &origin)
    {
        _year = origin._year;
        _month = origin._month;
        _day = origin._day;
    }
    return *this;
};

bool Date::operator <(const Date& other) const
{
    if (_year != other._year) return _year < other._year;
    if (_month != other._month) return _month < other._month;
    return _day < other._day;
};

bool Date::operator ==(const Date& other) const
{
    return (_year == other._year && _month == other._month && _day == other._day);
};

Date::~Date()
{
    // std::cout << "Date destructor called. " <<std::endl;
};

const char* Date::DateNotExistException::what() const throw() 
{
    return "Not a valid date.";
};

std::ostream& operator<<(std::ostream& os, const Date& date)
{
    std::cout << std::fixed << std::setprecision(2);
    os << date.getYear() << "-";
    if (date.getMonth() < 10) os << "0";
    os << date.getMonth() << "-";
    if (date.getDay() < 10) os << "0";
    os << date.getDay();
    return os;
};

int Date::getYear() const
{
    return _year;
};

int Date::getMonth() const
{
    return _month;
};

int Date::getDay() const 
{
    return _day;
};