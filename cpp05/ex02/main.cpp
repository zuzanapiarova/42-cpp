#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"

int main(void)
{
    Bureaucrat a("Anna", 10);
    Bureaucrat b("Bob", 20);
    AForm c("Work Contract", 20, 10);
    AForm d("Car Contract", 20, 10);
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

    return 0;
}
