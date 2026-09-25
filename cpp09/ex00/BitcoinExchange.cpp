#include "BitcoinExchange.hpp"

// ----------------------------------------------------- constructors / destructors ------------------------------------------------------------------

BitcoinExchange::BitcoinExchange()
{
    throw std::runtime_error("Object initialized with default constructor. No valid database file provided.");
};

BitcoinExchange::BitcoinExchange(const std::string& dbFile) : _filename(dbFile)
{
    std::ifstream pricesDatabase(dbFile.c_str());
    if (!pricesDatabase)
        throw std::runtime_error("Failed to open provided database file.");
    _populateMap(pricesDatabase);
    pricesDatabase.close();
};

BitcoinExchange::BitcoinExchange(const BitcoinExchange& origin) : _filename(origin._filename), _pricesMap(origin._pricesMap) {};

BitcoinExchange& BitcoinExchange::operator =(const BitcoinExchange& origin)
{
    if (this != &origin)
        throw std::runtime_error("Cannot use copy assignment on object with const members. Aborting without change.");
    return *this;
};

BitcoinExchange::~BitcoinExchange() {};

// ---------------------------------------------- exceptions -------------------------------------------------------

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
    return ("Invalid format.");
};

// --------------------------------------------------- private methods -----------------------------------------------------------

// populate the map - get date-price pairs from the provided database file
void BitcoinExchange::_populateMap(std::ifstream& pricesDatabase)
{
    std::string line;
    bool        firstLine = true;

    while (std::getline(pricesDatabase, line))
    {
        unsigned int    year, month, day;
        double          value;

        try
        {
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
            Date d(year, month, day);
            // will line below line work if prices map is not initialized yet and this would be ther first entry? 
            if (_pricesMap.find(d) != _pricesMap.end())
                throw BitcoinExchange::DuplicateDateException();
            _pricesMap[d] = value;
        }
        catch (std::exception& e)
        {
            std::cerr << "DB error: " << e.what() << " Omitting entry " << line << std::endl;
        }
    }
};

double BitcoinExchange::_getValue(const Date& date) const
{   
    std::map<Date, double>::const_iterator it = _pricesMap.lower_bound(date);

    // if _priceMap does not exist - eg. when object is created with default constructor, throw exception
    if (_pricesMap.empty())
        throw std::runtime_error("Prices map is empty. Object was not initialized with a valid database file.");

    //Exact match
    if (it != _pricesMap.end() && !(date < it->first))
        return it->second;

    // No earlier date available
    if (it == _pricesMap.begin()) 
        throw BitcoinExchange::DateNotExistException();
    
    // no exact match, move to the previous (earlier) date
    --it;

    return it->second;
};

// ------------------------------------------------------- public methods ----------------------------------------------------------------

void     BitcoinExchange::getPricesForDates(const std::string& inputFile) const
{
    std::ifstream ammountsDatabase(inputFile.c_str());
    if (!ammountsDatabase)
        throw std::runtime_error("Failed to open file.");
    
    std::string  line;
    bool         firstLine = true;
    unsigned int year, month, day;
    double       ammount;

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
                throw BitcoinExchange::InvalidFormatException();
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
            std::cout << "Input file error: " << e.what() << " Ommitting entry: " << line << std::endl;
        }
    }
};

// testing
void BitcoinExchange::printDB() const
{
    for (std::map<Date, double>::const_iterator it = _pricesMap.begin(); it != _pricesMap.end(); ++it)
        std::cout << "--- " << it->first << " => " << it->second << " ---" << "\n";
};