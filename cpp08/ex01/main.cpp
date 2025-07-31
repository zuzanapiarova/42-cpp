#include "Span.hpp"
#include <vector>
#include <list>

int main( void )
{
    try
    {
        Span emptySpan;
        Span span(100);
        Span copiedSpan(span);
        emptySpan = span; // trying assignment operator - size should be const, then it should not work
        
        for (unsigned int i = 1; i <= 10; i++) // populating the container - no error
            span.addNumber(i);
        span.addNumber(10); // container full - error
        
        // adding range of numbers from a list
        int arr2[] = { 100, 200, 300 };
        const std::list<int> lst(arr2, arr2 + 3);
        span.addNumbers(lst.begin(), lst.end());
        std::cout << "Limit: " << span.getMaxSize() << " - current: " << span.getRealSize() << std::endl;

        // adding range of numbers from a vector
        int arr3[] = { 1, 2, 2, 2, 2};
        std::vector<int> duplicates(arr3, arr3 + 5);
        span.addNumbers(duplicates.begin(), duplicates.end());
        std::cout << "Limit: " << span.getMaxSize() << " - current: " << span.getRealSize() << std::endl;

        // checking max and min spans
        std::cout << "Max: " << span.longestSpan() << " , min: " << span.shortestSpan() << std::endl;

        // checking max and min span if there are less than 2 elements
        Span s1(1);
        s1.addNumber(10); // container full - error
        std::cout << "Max: " << s1.longestSpan() << std::endl;
        std::cout << "Min: " << s1.shortestSpan() << std::endl;
    }
    catch (const std::logic_error& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}