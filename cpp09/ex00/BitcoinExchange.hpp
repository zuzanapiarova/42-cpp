#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <exception>

#include "Date.hpp"

class BitcoinDatabase
{
    private:
        const std::string       _filename;
        std::map<Date, double>  _pricesMap;
        void                    _populateMap(std::ifstream& pricesDatabase);

    
    public:
        BitcoinDatabase();
        BitcoinDatabase(const std::string& filename);
        BitcoinDatabase(const BitcoinDatabase& origin);
        BitcoinDatabase& operator =(const BitcoinDatabase& origin);
        ~BitcoinDatabase();

        void     calculateValues( const std::string& inputFile) const ;
        double getValue(const Date& key) const ;
        void printDB() const;// temporary

        class DuplicateDateException;
        class DateNotExistException;
        class InvalidFormatException;
};

class BitcoinDatabase::DuplicateDateException : public std::exception
{
    public:
        const char* what() const throw() ;
};

class BitcoinDatabase::DateNotExistException : public std::exception
{
    public:
        const char* what() const throw() ;
};

class BitcoinDatabase::InvalidFormatException : public std::exception
{
    public:
        const char* what() const throw() ;
};



#endif