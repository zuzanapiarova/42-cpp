#include "Bureaucrat.hpp"

int main(void)
{
    try
    {
        Bureaucrat a("Anna", 120);
        Bureaucrat b("Bob", 1);
        Bureaucrat c("Clara", 149);

        std::cout << a << std::endl;
        std::cout << b << std::endl;
        std::cout << c << std::endl;

        a.incrementGrade();
        b.incrementGrade();
        c.decrementGrade();
        //c.decrementGrade();

        std::cout << a << std::endl;
        std::cout << b << std::endl;
        std::cout << c << std::endl;        
    }
    catch (const Bureaucrat::GradeTooHighException& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (const Bureaucrat::GradeTooLowException& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}