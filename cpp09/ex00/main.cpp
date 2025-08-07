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
        BitcoinExchange db("data.csv");
        db.printDB(); // testing
        db.getPricesForDates(argv[1]);
    }
    catch(std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
};