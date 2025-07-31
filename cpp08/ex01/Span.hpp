#ifndef SPAN_H
# define SPAN_H

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

class Span
{
    private:
        std::vector<int> v;

    public:
        Span();
        Span(unsigned int N);
        Span(const Span& origin);
        Span operator=(const Span& origin);
        ~Span();

        void addNumber(int number);
        void addNumbers();
        void shortestSpan();
        void longestSpan();
    
};

#endif