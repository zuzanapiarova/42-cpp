#include "Bureaucrat.hpp"

int main(void)
{
    try
    {
        Bureaucrat a("Anna", 2);
        Bureaucrat b("Bob", 1);
        Bureaucrat c("Clara", 149);
        // Bureaucrat d("Daria", 160); // throws exception
        std::cout << std::endl;

        std::cout << a << std::endl;
        std::cout << b << std::endl;
        std::cout << c << std::endl;

        // testing member function logic 
        a.incrementGrade();
        // b.incrementGrade(); // throws exception
        c.decrementGrade();
        //c.decrementGrade(); // throws exception
        std::cout << std::endl;

        std::cout << a << std::endl;
        std::cout << b << std::endl;
        std::cout << c << std::endl;
        std::cout << std::endl;    

        // testing copy constructor
        Bureaucrat e(b); // was initialized to 1 by copying
        std::cout << e << std::endl << std::endl;

        // testing copy assignment operator
        Bureaucrat f("Frank", 10);
        std::cout << f << std::endl;
        f = e; // error - cannot assign object that has const members 
        std::cout << f << std::endl << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}