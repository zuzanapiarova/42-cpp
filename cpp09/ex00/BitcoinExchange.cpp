#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    std::cout << "Bitcoin Database default constructor called." << std::endl;
    throw BitcoinExchange::DateNotExistException();
};

BitcoinExchange::BitcoinExchange(const std::string& filename) : _filename(filename)
{
    // std::cout << "Bitcoin Database overload constructor called." << std::endl;
    std::ifstream pricesDatabase(filename.c_str());
    if (!pricesDatabase)
        throw std::runtime_error("Failed to open file.");
    _populateMap(pricesDatabase);
    pricesDatabase.close(); // redundant ? is it only alive when constructor body runs, and then is closed ? 
};

BitcoinExchange::BitcoinExchange(const BitcoinExchange& origin) : _filename(origin._filename), _pricesMap(origin._pricesMap)
{
    // std::cout << "BitcoinExchange copy constructor called." << std::endl;
};

BitcoinExchange& BitcoinExchange::operator =(const BitcoinExchange& origin)
{
    // std::cout << "BitcoinExchange copy assignment operator called." << std::endl;
    if (this != &origin)
        std::cout << "Cannot use copy assignment on object with const members. Aborting without change." << std::endl;
    return *this;
};

BitcoinExchange::~BitcoinExchange()
{    
    // std::cout << "BitcoinExchange destructor called." << std::endl;
};

const char* BitcoinExchange::DuplicateDateException::what() const throw() 
{
    return ("Trying to add duplicate date");
};

const char* BitcoinExchange::DateNotExistException::what() const throw() 
{
    return ("Date does not exist in database.");
};

const char* BitcoinExchange::InvalidFormatException::what() const throw() 
{
    return ("Invalid format. Aborting, database empty.");
};

void BitcoinExchange::_populateMap(std::ifstream& pricesDatabase)
{
    std::string  line;
    bool firstLine = true;
    while (std::getline(pricesDatabase, line))
    {
        unsigned int year, month, day;
        double value;
        if (sscanf(line.c_str(), "%u-%u-%u,%lf\n", &year, &month, &day, &value) != 4)
        {
            if (line == "date,exchange_rate" && firstLine)
            {
                firstLine = false;
                continue ;
            }
            throw BitcoinExchange::InvalidFormatException();
        }
        firstLine = false;
        try
        {
            Date d(year, month, day);
            // will line below line work if prices map is not initialized yet and this would be ther first entry? 
            if (_pricesMap.find(d) != _pricesMap.end())
                throw BitcoinExchange::DuplicateDateException();
            _pricesMap[d] = value;
        }
        catch (std::exception& e)
        {
            std::cerr << "Error: " << e.what() << ": omitting entry " << year << "-" << month << "-" << day << std::endl;
        }
    }
};

void     BitcoinExchange::getPricesForDates( const std::string& inputFile) const
{
    std::ifstream ammountsDatabase(inputFile.c_str());
    if (!ammountsDatabase)
        throw std::runtime_error("Failed to open file.");
    
    std::string line;
    bool        firstLine = true;
    unsigned int year, month, day;
    double      ammount;
    while (std::getline(ammountsDatabase, line))
    {
        try
        {
            if(sscanf(line.c_str(), "%u-%u-%u | %lf\n", &year, &month, &day, &ammount) != 4)
            {
                if (line == "date | value" && firstLine)
                {
                    firstLine = false;
                    continue ;
                }
                throw std::runtime_error("Bad format.");
                continue ;
            }
            firstLine = false;
            Date d(year, month, day);
            if (ammount < 0 || ammount > 1000)
                throw std::runtime_error("Value out of bounds.");
            double result = _getValue(d) * ammount;
            std::cout << d << " => " << result << std::endl;
        }
        catch (std::exception& e)
        {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
};

// testing
void BitcoinExchange::printDB() const
{
    for (std::map<Date, double>::const_iterator it = _pricesMap.begin(); it != _pricesMap.end(); ++it)
        std::cout << "--- " << it->first << " => " << it->second << " ---" << "\n";
};

double BitcoinExchange::_getValue(const Date& date) const
{
    std::map<Date, double>::const_iterator it = _pricesMap.lower_bound(date);
    //Exact match
    if (it != _pricesMap.end() && !(date < it->first))
        return it->second;
    // No earlier date available
    if (it == _pricesMap.begin()) 
        throw BitcoinExchange::DateNotExistException();
    --it; // no exact match, move to the previous (earlier) date
    return it->second;
};