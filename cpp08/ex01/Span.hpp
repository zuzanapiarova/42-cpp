#ifndef SPAN_H
# define SPAN_H

#include <iostream>
#include <exception>
#include <string>
#include <algorithm>
#include <vector>
#include <limits>

class Span
{
    private:
        const unsigned int  _size;
        std::vector<int>    _v;

    public:
        Span();
        Span(long N);
        Span(const Span& origin);
        Span& operator=(const Span& origin);
        ~Span();

        void addNumber(int number);
        unsigned int shortestSpan();
        unsigned int longestSpan();
        unsigned int getMaxSize();
        unsigned int getRealSize();

        template <typename IT>
        void addNumbers(IT first, IT last);

};

template <typename IT>
void Span::addNumbers(IT first, IT last)
{
    if (_v.size() + std::distance(first, last) >= _size) throw std::runtime_error("Resulting container would exceed maximum elements.");
    _v.insert(_v.end(), first, last);
};

#endif