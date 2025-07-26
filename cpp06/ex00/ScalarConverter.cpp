#include "ScalarConverter.hpp"

// Tests:

// A. wrong input - does not match any types string literal
// a.af
// 0.4ff
// --0.222
// 1.f - float ending with .
// 1. - double ending with .
// '' - empty string
// .f 
// 1f - not valid string literal in cpp but can possibly handle it

// B. should print
// '\''
// - 

// prints but char is non-displayable:
// '1'
// -1
// '\n'
// 0
// -0
// +0
// 298 - checks if wrapping is handled - if not, prints *

// pseudo-literals: char and int are impossible
// when testing this, check that they print it as a converted type, not printing the string !
// nan
// +inf
// -inf
// nanf
// +inff
// -inff

// out of range during static_cast
// 2147483649.0f - float cannot cast to int - impossible (overflow)
// 2140000000000000000000000000000000000000000000000.0 - double cannot cast to float/int - impossible (overflow)

// C. should trigger error/exception
// '\j' - invalid escape sequence
// 2147483649 - < max int
// 100000000000000000000000000000000000000000000000.0f - < max float
// max double can hardly be tested since it is ~1.8 × 10^308

// ! static cast from larger type to smaller - double/float to int/char 
// ? what does setprecision do in terms of bits? why sometimes the rounding errors are there ? 

bool isPseudoLiteral(const std::string& s)
{
    return s == "nan" || s == "+inf" || s == "-inf" ||
           s == "nanf" || s == "+inff" || s == "-inff";
}

// ------------------------------------------ Char --------------------------------------------------

// I prevent wrapping - so char modulo 256 will not produce output eg 298 would be * if wrapping was allowed

// this function prevents wrapping AND checks if the char is printable
// takes in int, not char, because casting to char to pass it to this function would wrap before checking, which we do not want
bool isPrintable(char c)
{
    return std::isprint(static_cast<unsigned char>(c)); // cast to unsigned char to be safe with isprint() function
}

char parseEscapeChar(const std::string& s)
{
    switch (s[1])
    {
        case 'n':  return '\n';  // newline
        case 't':  return '\t';  // horizontal tab
        case 'v':  return '\v';  // vertical tab
        case 'b':  return '\b';  // backspace
        case 'r':  return '\r';  // carriage return
        case 'f':  return '\f';  // form feed
        case 'a':  return '\a';  // alert (bell)
        case '\\': return '\\';  // backslash
        case '\'': return '\'';  // single quote
        case '\"': return '\"';  // double quote
        case '?':  return '\?';  // question mark
        case '0':  return '\0';  // null character
    }
    throw std::invalid_argument("Invalid escape sequence");
}

// -! escape characters transform input from '\n' to "\\n", so handle this second string

bool isCharLiteral(const std::string& s)
{
    if (s.length() == 1 )
        return true;
    if (s.length() == 2 && s[0] == '\\')
        return true;
    return false;
}

void handleChar(const std::string& s)
{
    char c = s.length() == 1 ? s[0] : parseEscapeChar(s);

    if (isPrintable(c))
        std::cout << "char: " << "'" << c << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;
    std::cout << "int: " << static_cast<int>(c) << std::endl;
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "float: " <<  static_cast<float>(c) << "f" << std::endl;
    std::cout << "double: " <<  static_cast<double>(c) << std::endl;
}

// ------------------------------------------ Int --------------------------------------------------

// int → char: for too large numbers, only the lowest 8 bits are kept - the value is always int % 256

bool isIntLiteral(const std::string& s)
{
    size_t i = 0;

    if (s[i] == '-' || s[i] == '+')
        i++;
    if (i >= s.length()) 
        return false;
    while (i < s.length())
    {
        if (!std::isdigit(s[i]))
            return false;
        i++;
    }
    return true;
}

void handleInt(const std::string& s)
{
    int i;
    std::istringstream iss(s); // string stream is only safe and standard way to convert strings to numbers in c++98
    iss >> i; // reads input from string and checks for integer format and range
    if (iss.fail() || !iss.eof())
    {
        std::cerr << "Error: invalid integer input. " << std::endl;
        return ;
    }

    if (i < static_cast<int>(std::numeric_limits<char>::min()) || i > static_cast<int>(std::numeric_limits<char>::max()))
        std::cout << "char: impossible" << std::endl;
    else if (isPrintable(static_cast<char>(i)))
        std::cout << "char: " << "'" << static_cast<char>(i) << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;
    std::cout << "int: " << i << std::endl;
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "float: " << static_cast<float>(i) << "f" << std::endl;
    std::cout << "double: " <<  static_cast<double>(i) << std::endl;
}

// ------------------------------------------ Float --------------------------------------------------

// floats have to be in decimal notation, with at least one digit after the dot and with f at the end
// float → char: fractional part is discarded, int part is converted to char, but same problem as with int - higher numbers wrap with modulo 256 (only the last 8 bits are kept)

bool isFloatLiteral(const std::string& s)
{
    if (s == "nanf" || s == "+inff" || s == "-inff") 
        return true;

    if (s.empty() || s.back() != 'f')
        return false;

    std::string core = s.substr(0, s.length() - 1);
    size_t i = 0;
    bool hasDot = false;
    bool hasDigit = false;

    if (core[i] == '-' || core[i] == '+')
        i++;

    while (i < core.length())
    {
        if (core[i] == '.')
        {
            if (i == core.length() - 1 || hasDot) // prevent dot being last/multiple times in string
                return false;
            hasDot = true;
        } 
        else if (std::isdigit(core[i]))
            hasDigit = true;
        else
            return false;
        i++;
    }

    return hasDot && hasDigit;
}

    // if (isPseudoLiteral(s))
    // {
    //     std::cout << "char: impossible" << std::endl;
    //     std::cout << "int: impossible" << std::endl;
    //     std::cout << "float: " << std::showpos << f << "f" << std::endl;
    //     std::cout << "double: " << std::showpos << static_cast<double>(f) << std::endl;
    // }
    // else
    // {
void handleFloat(const std::string& s)
{
    float f;
    std::string core = s.substr(0, s.length() - 1);
    std::istringstream iss(core);
    iss >> f;
    if (iss.fail() || !iss.eof())
    {
        std::cerr << "Error: invalid float input." << std::endl;
        return ;
    }
    
    if (f < static_cast<float>(std::numeric_limits<char>::min()) || f > static_cast<float>(std::numeric_limits<char>::max()) || f != f /* NaN check */ )
        std::cout << "char: impossible" << std::endl;
    else if (isPrintable(static_cast<char>(f)))
        std::cout << "char: " << "'" << static_cast<char>(f) << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;
    double d = static_cast<double>(f); // best to compare to the float in the wider type (double) to avoid loss of precision
    if (d < static_cast<double>(std::numeric_limits<int>::min()) || d > static_cast<double>(std::numeric_limits<int>::max()) || f != f /* NaN check */ )
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(f) << std::endl;
    if (std::floor(d) == d) std::cout << std::fixed << std::setprecision(1);
    std::cout << "float: " << f << "f" << std::endl;
    std::cout << "double: " << static_cast<double>(f) << std::endl;
}

// ------------------------------------------ Double --------------------------------------------------

// double → char: fractional part is discarded, int part is converted to char, but same problem as with int - higher numbers wrap with modulo 256 (only the last 8 bits are kept)

bool isDoubleLiteral(const std::string& s)
{
    if (s == "nan" || s == "+inf" || s == "-inf") 
        return true;

    size_t i = 0;
    bool hasDot = false;
    bool hasDigit = false;

    if (s[i] == '-' || s[i] == '+')
        i++;

    while (i < s.length())
    {
        if (s[i] == '.')
        {
            if (i == s.length() - 1 || hasDot) // prevent dot being last/multiple times in string
                return false;
            hasDot = true;
        } 
        else if (std::isdigit(s[i]))
            hasDigit = true;
        else
            return false;
        i++;
    }

    return hasDot && hasDigit;
}

void handleDouble(const std::string& s)
{
    double d;
    std::istringstream iss(s);
    iss >> d;
    if (iss.fail() || !iss.eof())
    {
        std::cerr << "Error: invalid double input." << std::endl;
        return ;
    }
    
    if (d < static_cast<double>(std::numeric_limits<char>::min()) || d > static_cast<double>(std::numeric_limits<char>::max())  || d != d /* NaN check */ )
        std::cout << "char: impossible" << std::endl;
    else if (isPrintable(static_cast<int>(d)))
        std::cout << "char: " << "'" << static_cast<char>(d) << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;
    if (d < std::numeric_limits<int>::min() || d > std::numeric_limits<int>::max() || d != d /* NaN check */ ) // static_cast<float>(INT_MAX) because float cannot represent every large int exactly, so comparison must happen in float
        std::cout << "int: impossible" << std::endl;
    else 
        std::cout << "int: " << static_cast<int>(d) << std::endl;
    if (std::floor(d) == d) std::cout << std::fixed << std::setprecision(1);
    if (!isPseudoLiteral(s) && (d < -std::numeric_limits<float>::max() || d > std::numeric_limits<float>::max()))  // same as above
        std::cout << "float: impossible" << std::endl;
    else
        std::cout << "float: " << static_cast<float>(d) << "f" << std::endl;
    std::cout << "double: " << d << std::endl;
}

// ------------------------------------------ Convert --------------------------------------------------

void ScalarConverter::convert( const std::string& s)
{
    try
    {
        if (isFloatLiteral(s))
            handleFloat(s);
        else if (isDoubleLiteral(s))
            handleDouble(s);
        else if (isIntLiteral(s))
            handleInt(s);
        else if (isCharLiteral(s)) //  char is lasts so single digits as '8' match int
            handleChar(s);
        else 
            throw std::invalid_argument("Not a string literal for known types.");
    }
    catch (std::invalid_argument e)
    {
        std::cerr << "Invalid input: " << e.what() << std::endl;
    }
}