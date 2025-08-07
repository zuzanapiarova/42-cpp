#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main(void)
{
    // 1. testing creation of the forms by intern
    Intern i;
    std::cout << std::endl;
    
    AForm* first = i.makeForm("shrubbery creation", "Garden");
    AForm* second = i.makeForm("robotomy request", "Smart Robot");
    AForm* third = i.makeForm("presidential pardon", "Pardoned person");
    std::cout << std::endl;

    std::cout << *first << std::endl;
    std::cout << *second << std::endl;
    std::cout << *third << std::endl;
    std::cout << std::endl;

    // 2. testing forms being usable by bureaucrats
    Bureaucrat a("Anna", 1);
    a.signForm(*first);
    a.signForm(*second);
    a.signForm(*third);
    std::cout << std::endl;

    a.executeForm(*first);
    a.executeForm(*second);
    a.executeForm(*third);
    std::cout << std::endl;

    delete first;
    delete second;
    delete third;

    return 0;
}
