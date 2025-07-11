#include <iostream>
#include <string>
#include <fstream>

std::string replaceString(const std::string& line, const std::string& s1, const std::string& s2)
{
    std::string result;
    size_t pos = 0;
    size_t found;

    if (s1.length() == 0)
        return line;
    found = line.find(s1, pos);
    if (found == std::string::npos)
    {
        return line;
    }
    while (found != std::string::npos)
    {
        result += line.substr(pos, found - pos);
        result += s2;
        pos = found + s1.length();
        found = line.find(s1, pos);
    }
    result += line.substr(pos);
    return result;
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        std::cerr << "Invalid arguments: ./replace <filename> <s1> <s2>" << std::endl;
        return 1;
    }
    const std::string filename = argv[1];
    const std::string s1 = argv[2];
    const std::string s2 = argv[3];

    std::ifstream inputFile(filename);
    if (!inputFile)
    {
        std::cerr << filename << ": file does not exist or other error." << std::endl;
        inputFile.close();
        return 1;
    }

    std::string output_filename = filename + ".replace";
    std::ofstream outputFile(output_filename);
    if (!outputFile)
    {
        std::cerr << output_filename << ": file cannot be opened or created or other error." << std::endl;
        outputFile.close();
        return 1;
    }
    
    std::string line;
    while (std::getline(inputFile, line))
        outputFile << replaceString(line, s1, s2) << std::endl;

    inputFile.close();
    outputFile.close();
    return 0;
}