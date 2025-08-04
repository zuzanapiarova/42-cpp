#include "BitcoinExchange.hpp"
#include <iostream>

// tests:
// a. parsing
// invalid format like 000-12-01
// month > 12, month < 0
// day > 31, day < 0
// year < 0
// value not between 0-100 (can be floats)
// add priestupny rok handling ? 
// check in priceDatabase if date already exists
// no amount in the second db


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

void     calculateValues(std::ifstream& ammountsDatabase, std::map<Date, double>& pricesMap)
{
    std::string line;
    std::getline(databaseFile, line); // read the first line which is column names
    while (std::getline(databaseFile, line))
    {
        unsigned int year, month, day;
        float ammount;
        if(sscanf(line.c_str(), "%u-%u-%u | %f", &year, &month, &day, &ammount) != 4)

    }
}


std::map<Date, double> populateMap(std::ifstream& pricesDatabase)
{
    std::map<Date, double> pricesMap;
    std::string line;

    std::getline(pricesDatabase, line); // read the first line which is column names
    while (std::getline(pricesDatabase, line))
    {
        unsigned int year, month, day;
        double value;
        if (sscanf(line.c_str(), "%u-%u-%u,%lf", &year, &month, &day, &value) != 4) // checks
        {
            std::cout << "Fail in check DB format" << std::endl;
            throw ("Invalid prices database. Missing parameters.");
        }
        try
        {
            Date d(year, month, day);
            // protect if date already exists ? 
            if (pricesMap[d])
                throw("Prices database has duplicate dates.");
            pricesMap[d] = value;

        }
        catch (std::exception& e)
        {
            std::cerr << "Omitting date " << year << "-" << month << "-" << day << ": " << e.what() << std::endl;
        }
    }

    return pricesMap;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Invalid arguments. Program expects ./btc <database_file>" << std::endl; 
        return 1;
    }
    std::ifstream pricesDatabase("data.csv");
    std::ifstream ammountsDatabase(argv[1]);
    if (!pricesDatabase || !ammountsDatabase)
    {
        std::cout << "Error opening databases." << std::endl;
        return 1;
    }
    try
    {
        std::map<Date, double> pricesMap = populateMap(pricesDatabase);
        pricesDatabase.close();
        // for (std::map<Date, double>::iterator it = pricesMap.begin(); it != pricesMap.end(); ++it)
        //  std::cout << it->first << " => " << it->second << "\n";
        calculateValues(ammountsDatabase, pricesMap);
    }
    catch(std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    




    return 0;
}