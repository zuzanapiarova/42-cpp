#include "Span.hpp"
#include <vector>
#include <list>

int main( void )
{
    try
    {
        // default constructor - initialize empty span with size 0 and initialized container
        Span emptySpan;
        std::cout << "Limit: " << emptySpan.getMaxSize() << " - current: " << emptySpan.getRealSize() << std::endl;

        // overload and copy constructor
        Span span(100);
        Span copiedSpan(span);

        // copy assignment operator - size should be const, and it should not work - cause if size is not const, it can be set to smaller number than current number of elements
        // Span newSpan;
        // newSpan = span;
        
        // populating the container - loop fills it fully, next one raises exception
        for (unsigned int i = 1; i <= 100; i++)
            copiedSpan.addNumber(i);
        // copiedSpan.addNumber(10);
        std::cout << "Limit: " << copiedSpan.getMaxSize() << " - current: " << copiedSpan.getRealSize() << std::endl;
        
        // adding range of numbers from a list
        int arr2[] = { 100, 200, 300 };
        const std::list<int> lst(arr2, arr2 + 3);
        span.addNumbers(lst.begin(), lst.end());
        std::cout << "Limit: " << span.getMaxSize() << " - current: " << span.getRealSize() << std::endl;

        // adding range of numbers from a CONST vector
        const std::vector<int> duplicates(10, 1);
        span.addNumbers(duplicates.begin(), duplicates.end());
        std::cout << "Limit: " << span.getMaxSize() << " - current: " << span.getRealSize() << std::endl;

        // checking max and min spans
        std::cout << "Max: " << span.longestSpan() << " , min: " << span.shortestSpan() << std::endl;

        // checking max and min spans if the numbers are the same
        Span s(10);
        for (unsigned int i = 1; i <= 10; i++)
            s.addNumber(10);
        std::cout << "Max: " << s.longestSpan() << " , min: " << s.shortestSpan() << std::endl;

        // checking max and min span if there are less than 2 elements - raises exception
        Span s1(1);
        s1.addNumber(10);
        // std::cout << "Max: " << s1.longestSpan() << std::endl;
        // std::cout << "Min: " << s1.shortestSpan() << std::endl;

        // adding range so that size is exceeded
        Span s2(10);
        for (unsigned int i = 1; i <= 10; i++)
            s2.addNumber(10);
        s2.addNumbers(duplicates.begin(), duplicates.end());
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}