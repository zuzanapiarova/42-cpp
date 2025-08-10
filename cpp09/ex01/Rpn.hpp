# pragma once

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <cmath>
#include <limits>
#include <stack>
#include <algorithm>

class Rpn
{
    private:
        std::string     _expression;
        int             _result;
        int             _add(int n1, int n2);
        int             _subtract(int n1, int n2);
        int             _multiply(int n1, int n2);
        int             _divide(int n1, int n2);
        bool            _isValidInt(const std::string &s);
        void            _calculate();
        
    public:
        Rpn();
        Rpn(const std::string& exp);
        Rpn(const Rpn& origin);
        Rpn& operator =(const Rpn& origin);
        ~Rpn();

        int getResult();

};