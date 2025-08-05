#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(void)
{
    try
    {
        Bureaucrat a("Anna", 20);
        Bureaucrat b("Bob", 20);
        Form c("Work Contract", 20, 10);
        Form d("Car Contract", 20, 10);
        std::cout << std::endl;

        std::cout << b << std::endl;
        b.signForm(c); // works - Bob has access
        std::cout << c << std::endl << std::endl;
    
        b.decrementGrade();
        std::cout << b << std::endl;
        b.signForm(d); // does not work - Bob has not access anymore
        std::cout << d << std::endl << std::endl;
    
        std::cout << a << std::endl;
        a.signForm(d); // works - Anna has enough access
        std::cout << d << std::endl << std::endl;
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
