#include "Rpn.hpp"

int Rpn::_add(int a, int b)
{
    if ((b > 0 && a > std::numeric_limits<int>::max() - b) ||
        (b < 0 && a < std::numeric_limits<int>::min() - b))
        throw std::runtime_error("Overflow error.");
    return a + b;
};

int Rpn::_subtract(int a, int b)
{
    // Check for overflow: a - b
    if ((b > 0 && a < std::numeric_limits<int>::min() + b) ||
        (b < 0 && a > std::numeric_limits<int>::max() + b))
        throw std::runtime_error("Overflow error.");
    return a - b;
};

int Rpn::_multiply(int a, int b)
{
    if (a > 0 && b > 0)
        if (a > std::numeric_limits<int>::max() / b) throw std::runtime_error("Overflow error.");
    if (a > 0 && b < 0)
        if (b < std::numeric_limits<int>::min() / a) throw std::runtime_error("Overflow error.");
    if (a < 0 && b > 0)
        if (a < std::numeric_limits<int>::min() / b) throw std::runtime_error("Overflow error.");
    if (a < 0 && b < 0)
        if (a < std::numeric_limits<int>::max() / b) throw std::runtime_error("Overflow error.");
    return a * b;
};
int Rpn::_divide(int a, int b)
{
    if (b == 0) throw std::runtime_error("Division by zero");
    if (a == std::numeric_limits<int>::min() && b == -1) throw std::runtime_error("Overflow error.");
    return  a / b;
};

void Rpn::_calculate( void )
{
    std::stack<int>     s;
    std::istringstream  iss(_expression);
    std::string         token;
    int                 n1;
    int                 n2;

    while (iss >> token)
    {
        if (token != "+" && token != "-" && token != "*" && token != "/")
        {
            int res;
            std::istringstream iss(token); // string stream is only safe and standard way to convert strings to numbers in c++98
            iss >> res; // reads input from string and checks for integer format and range
            if (iss.fail() || !iss.eof()) throw std::invalid_argument("Invalid integer input."); // iss sets flags if reading from string goes wrong
            if (res < std::numeric_limits<int>::min() || res > std::numeric_limits<int>::max()) throw std::out_of_range("Value outside of unsigned int not allowed."); // we only want positive integers
            s.push(std::atoi(token.c_str()));
            continue ;
        }
        if (s.size() < 2) throw std::runtime_error("Wrong expression format."); // throws error if first two are not numbers
        n2 = s.top();
        s.pop();
        n1 = s.top();
        s.pop();
        if (token == "+") s.push(Rpn::_add(n1, n2));
        else if (token == "-") s.push(Rpn::_subtract(n1, n2));
        else if (token == "*") s.push(Rpn::_multiply(n1, n2));
        else if (token == "/") s.push(Rpn::_divide(n1, n2));
    }
    if (s.size() != 1) throw std::runtime_error("Wrong expression format."); // throws exception if there is anything extra in the expression that does not fit the format
    _result = (s.top());
};

Rpn::Rpn() 
{
    // std::cout << "Rpn default constructor called." << std::endl;
    throw std::runtime_error("Default constructor would create empty stack.");
};
Rpn::Rpn(const std::string& exp)
{
    // std::cout << "Rpn overload constructor called." << std::endl;
    if (exp.empty()) throw std::runtime_error("Empty expression");
    _expression = exp;
    _calculate();
};

Rpn::Rpn(const Rpn& origin) : _expression(origin._expression), _result(origin._result)
{
    // std::cout << "Rpn default constructor called." << std::endl;
}
Rpn& Rpn::operator =(const Rpn& origin)
{
    // std::cout << "Rpn default constructor called." << std::endl;
    if (this != &origin)
    {
        _expression = origin._expression;
        _result = origin._result;
    }
    return *this;
};

Rpn::~Rpn()
{
    // std::cout << "Rpn destructor called." << std::endl;
};

int Rpn::getResult()
{
    return _result;
}