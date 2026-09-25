#include "BitcoinExchange.hpp"
#include "Date.hpp"

#include <string>
#include <iostream>
#include <exception>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Invalid arguments. Program expects ./btc <database_file>" << std::endl; 
        return 1;
    }
    try
    {
        BitcoinExchange origin("data.csv"); // test overloaded constructor
        BitcoinExchange copy(origin);       // test copy constructor
        // BitcoinExchange assign;             // test default constructor - should error
        // copy = origin;                      // test copy assignment operator (should not change assign object, since it has const members)

        copy.getPricesForDates(argv[1]);

    }
    catch(std::exception& e)
    {
        std::cerr << "Main Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
};