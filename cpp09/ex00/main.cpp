#include "BitcoinExchange.hpp"
#include "Date.hpp"

#include <string>
#include <iostream>
#include <exception>


// bool checkDatabaseFormat(std::ifstream& databaseFile, char sep)
// {
//     std::string line;
//     std::getline(databaseFile, line); // read the first line which is column names
//     while (std::getline(databaseFile, line))
//     {
//         unsigned int year, month, day;
//         float value;
//         int expressionResult;
//         if (sep == '|')
//             expressionResult = sscanf(line.c_str(), "%u-%u-%u | %f", &year, &month, &day, &value);
//         else
//             expressionResult = sscanf(line.c_str(), "%u-%u-%u,%f", &year, &month, &day, &value);
//         if (expressionResult != 4 || checkDate(year, month, day) == false || value < 0 || value > 1000) // checks
//         {
//             std::cout << "Fail in check DB format" << std::endl;
//             return 1;
//         }
//     }
//     return 0;
// }

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
        db.printDB(); // printing testing 
        db.getPricesForDates(argv[1]);
    }
    catch(std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
};