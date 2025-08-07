#include "BitcoinExchange.hpp"

BitcoinDatabase::BitcoinDatabase()
{
    std::cout << "Bitcoin Database default constructor called." << std::endl;
    throw BitcoinDatabase::DateNotExistException();
};

BitcoinDatabase::BitcoinDatabase(const std::string& filename) : _filename(filename)
{
    std::cout << "Bitcoin Database overload constructor called." << std::endl;
    std::ifstream pricesDatabase(filename.c_str());
    if (!pricesDatabase)
        throw std::runtime_error("Database file does not exist.");
    _populateMap(pricesDatabase);
    pricesDatabase.close(); // redundant ? is it only alive when constructor body runs, and then is closed ? 
};

BitcoinDatabase::BitcoinDatabase(const BitcoinDatabase& origin) : _filename(origin._filename), _pricesMap(origin._pricesMap)
{
    std::cout << "BitcoinDatabase copy constructor called." << std::endl;
};

BitcoinDatabase& BitcoinDatabase::operator =(const BitcoinDatabase& origin)
{
    std::cout << "BitcoinDatabase copy assignment operator called." << std::endl;
    if (this != &origin)
        std::cout << "Cannot use copy assignment on object with const members. Aborting without change." << std::endl;
    return *this;
};

BitcoinDatabase::~BitcoinDatabase()
{    
    std::cout << "BitcoinDatabase destructor called." << std::endl;
};

const char* BitcoinDatabase::DuplicateDateException::what() const throw() 
{
    return ("Trying to add duplicate date.");
};

const char* BitcoinDatabase::DateNotExistException::what() const throw() 
{
    return ("Date does not exist in database.");
};

const char* BitcoinDatabase::InvalidFormatException::what() const throw() 
{
    return ("Date does not exist in database.");
};

void BitcoinDatabase::_populateMap(std::ifstream& pricesDatabase)
{
    std::string line;

    std::getline(pricesDatabase, line); // read the first line which is column names
    while (std::getline(pricesDatabase, line))
    {
        unsigned int year, month, day;
        double value;
        if (sscanf(line.c_str(), "%u-%u-%u,%lf", &year, &month, &day, &value) != 4)
            throw BitcoinDatabase::InvalidFormatException();
        try
        {
            Date d(year, month, day);
            // will line below line work if prices map is not initialized yet and this would be ther first entry? 
            if (_pricesMap.find(d) != _pricesMap.end())
                throw BitcoinDatabase::DuplicateDateException();
            _pricesMap[d] = value;
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << ": omitting entry " << year << "-" << month << "-" << day << std::endl;
        }
    }
};

void     BitcoinDatabase::calculateValues( const std::string& inputFile) const
{
    std::ifstream ammountsDatabase(inputFile.c_str());
    if (!ammountsDatabase)
        throw std::runtime_error("Failed to open file.");
    std::string line;
    std::getline(ammountsDatabase, line); // read the first line which is column names - ERROR: what it only has one or no lines ? 
    while (std::getline(ammountsDatabase, line))
    {
        unsigned int year, month, day;
        double ammount;
        if(sscanf(line.c_str(), "%u-%u-%u | %lf", &year, &month, &day, &ammount) != 4)
        {
            // check negative value
            // check too big value
            // else it is other format error
            std::cout << "Error: Bad format." << std::endl;
        }
        else 
        {
            try
            {
                if (ammount < 0 || ammount > 1000)
                    throw std::runtime_error("Value out of bounds.");
                Date d(year, month, day);
                double result = getValue(d) * ammount; // what if this is out of bounds for double ? 
                std::cout << d << " => " << result << std::endl;
            }
            catch (std::exception& e)
            {
                std::cout << "Error: " << e.what() << std::endl;
            };
        }
    }
}

// temporary / testing
void BitcoinDatabase::printDB() const
{
    for (std::map<Date, double>::const_iterator it = _pricesMap.begin(); it != _pricesMap.end(); ++it)
        std::cout << it->first << " => " << it->second << "\n";
};

double BitcoinDatabase::getValue(const Date& date) const
{
    std::map<Date, double>::const_iterator it = _pricesMap.lower_bound(date);

    //Exact match
    if (it != _pricesMap.end() && !(date < it->first))
        return it->second;

    // No earlier date available
    if (it == _pricesMap.begin()) 
        throw BitcoinDatabase::DateNotExistException();
    
    // Case 2: No exact match,M\ move to the previous (earlier) date
    --it; // 
    return it->second;
};