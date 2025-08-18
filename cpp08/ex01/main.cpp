#include "Span.hpp"
#include <vector>
#include <list>

int main( void )
{
    try
    {
        Span span(20000);

        // 1. default constructor - initialize empty span with size 0 and initialized container
        Span emptySpan;
        std::cout << "Limit: " << emptySpan.getMaxSize() << " - current: " << emptySpan.getRealSize() << std::endl;
        std::cout << "Max: " << emptySpan.longestSpan() << " , min: " << emptySpan.shortestSpan() << std::endl;

        // 2. overload and copy constructors
        Span copiedSpan(span);
        for (unsigned int i = 1; i <= copiedSpan.getMaxSize(); i++)
            copiedSpan.addNumber(i);
        std::cout << "Limit: " << copiedSpan.getMaxSize() << " - current: " << copiedSpan.getRealSize() << std::endl;
        std::cout << "Max: " << copiedSpan.longestSpan() << " , min: " << copiedSpan.shortestSpan() << std::endl;
        // copy assignment operator - size should be const, and it should not work - cause if size is not const, it can be set to smaller number than current number of elements
        Span newSpan;
        newSpan = span;
        
        // 3. adding range of numbers from different containers
        // a. from a list
        int arr2[] = { 100, 200, 300 };
        const std::list<int> lst(arr2, arr2 + 3);
        span.addNumbers(lst.begin(), lst.end());
        std::cout << "Limit: " << span.getMaxSize() << " - current: " << span.getRealSize() << std::endl;
        std::cout << "Max: " << span.longestSpan() << " , min: " << span.shortestSpan() << std::endl;

        // b. from a CONST vector
        const std::vector<int> constVector(10, 1);
        span.addNumbers(constVector.begin(), constVector.end());
        std::cout << "Limit: " << span.getMaxSize() << " - current: " << span.getRealSize() << std::endl;
        std::cout << "Max: " << span.longestSpan() << " , min: " << span.shortestSpan() << std::endl;

        // 4. checking max and min spans if the numbers are duplicate
        Span s(10);
        for (unsigned int i = 1; i <= 10; i++)
            s.addNumber(10);
        std::cout << "Max: " << s.longestSpan() << " , min: " << s.shortestSpan() << std::endl;

        // 5. checking max and min span if there are less than 2 elements - raises exception
        Span s1(1);
        s1.addNumber(10);
        std::cout << "Max: " << s1.longestSpan() << std::endl << "min: " << s1.shortestSpan() << std::endl;

        // 6. adding range so that size is exceeded
        Span s2(10);
        for (unsigned int i = 1; i <= 10; i++)
            s2.addNumber(i);
        s2.addNumber(11);

        // 7. creating Span with negative size
        Span negativeSpan(-2); // has to be 0 to 4294967295
        for (unsigned int i = 1; i <= 20; i++)
            negativeSpan.addNumber(i);
        std::cout << "Limit: " << negativeSpan.getMaxSize() << " - current: " << negativeSpan.getRealSize() << std::endl;
        std::cout << "Max: " << negativeSpan.longestSpan() << " , min: " << negativeSpan.shortestSpan() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}