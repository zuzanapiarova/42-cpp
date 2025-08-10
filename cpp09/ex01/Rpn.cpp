#include "Rpn.hpp"

bool Rpn::_isValidInt(const std::string &s)
{
    char    *endptr;
    errno = 0; // reset errno before call
    long    value = std::strtol(s.c_str(), &endptr, 10);

    // check conversion succeeded and parsed the whole string - if not, it encountered non-numeric character
    if (*endptr != '\0')
        throw std::invalid_argument("Invalid argument.");
    // check no overflow and value fits in int
    if ((errno == ERANGE) || value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max()) 
        throw std::runtime_error("Overflow error.");
    return true;
}

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
            if (_isValidInt(token))
            {
                s.push(std::atoi(token.c_str()));
                continue ;
            }
            throw std::runtime_error("Invalid argument.");
        }
        if (s.size() < 2) throw std::runtime_error("Wrong expression format.");
        n2 = s.top();
        s.pop();
        n1 = s.top();
        s.pop();
        if (token == "+") s.push(Rpn::_add(n1, n2));
        else if (token == "-") s.push(Rpn::_subtract(n1, n2));
        else if (token == "*") s.push(Rpn::_multiply(n1, n2));
        else if (token == "/") s.push(Rpn::_divide(n1, n2));
    }
    if (s.size() != 1) throw std::runtime_error("Wrong expression format.");
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