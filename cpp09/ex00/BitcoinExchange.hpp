#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

#include <string>
#include <iostream>
#include <iomanip>
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
        Date& operator=(const Date& origin);
        bool operator<(const Date& other) const;
        ~Date();

        int getYear() const ;
        int getMonth() const ;
        int getDay() const ;
};

std::ostream& operator<<(std::ostream& os, const Date& date);

#endif