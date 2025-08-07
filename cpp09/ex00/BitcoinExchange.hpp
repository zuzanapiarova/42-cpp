#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <exception>

#include "Date.hpp"

class BitcoinExchange
{
    private:
        const std::string       _filename;
        std::map<Date, double>  _pricesMap;
        void                    _populateMap(std::ifstream& pricesDatabase);
        double                  _getValue(const Date& key) const ;

    
    public:
        BitcoinExchange();
        BitcoinExchange(const std::string& filename);
        BitcoinExchange(const BitcoinExchange& origin);
        BitcoinExchange& operator =(const BitcoinExchange& origin);
        ~BitcoinExchange();

        void    getPricesForDates( const std::string& inputFile) const ;
        void    printDB() const ;

        class DuplicateDateException;
        class DateNotExistException;
        class InvalidFormatException;
};

class BitcoinExchange::DuplicateDateException : public std::exception
{
    public:
        const char* what() const throw() ;
};

class BitcoinExchange::DateNotExistException : public std::exception
{
    public:
        const char* what() const throw() ;
};

class BitcoinExchange::InvalidFormatException : public std::exception
{
    public:
        const char* what() const throw() ;
};

#endif