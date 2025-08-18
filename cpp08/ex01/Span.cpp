#include "Span.hpp"

Span::Span() : _size(), _v()
{
    // std::cout << "Span default constructor called." << std::endl;
};

Span::Span(long N) : _size(static_cast<unsigned int>(N)), _v()
{
    // std::cout << "Span overload constructor called." << std::endl;
    if (N < std::numeric_limits<unsigned int>::min() || N > std::numeric_limits<unsigned int>::max())
        throw std::out_of_range("Value outside of unsigned int not allowed.");
}

Span::Span(const Span& origin) : _size(origin._size), _v(origin._v)
{
    // std::cout << "Span copy constructor called." << std::endl;
};

Span& Span::operator =(const Span& origin)
{
    // std::cout << "Span copy assignment operator called." << std::endl;
    if (this != &origin)
        std::cerr << "Cannot call copy assignment operator because of const members. Aborting without change" << std::endl;
    return *this;
};

Span::~Span()
{
    // std::cout << "Span destructor called." << std::endl;
};

unsigned int Span::getMaxSize()
{
    return _size;
}

unsigned int Span::getRealSize()
{
    return _v.size();
}

// finds smallest value distance between 2 elements in the container
unsigned int Span::shortestSpan()
{
    if (_v.size() < 2) throw std::logic_error("Container needs at least 2 elements to calculate span.");
    std::vector<int> temp = _v;
    std::sort(temp.begin(), temp.end());
    unsigned int minSpan = *(temp.begin() + 1) - *temp.begin();
    for (unsigned int i = 0; i < temp.size() - 1; ++i)
    {
        unsigned int diff = temp[i + 1] - temp[i];
        if (diff < minSpan)
            minSpan = diff;
    }
    return minSpan;
};

// finds largest value distance between 2 elements in the container
unsigned int Span::longestSpan()
{
    if (_v.size() < 2) throw std::logic_error("Container needs at least 2 elements to calculate span.");
    int min = *std::min_element(_v.begin(), _v.end());
    int max = *std::max_element(_v.begin(), _v.end());
    return max - min;
};

void Span::addNumber(int number)
{
    if (_v.size() < _size)
        _v.push_back(number);
    else
        throw std::length_error("Error: Container full.");
};

