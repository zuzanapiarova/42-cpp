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
    
    AForm* first = i.makeForm("shrubbery creation", "Garden");
    AForm* second = i.makeForm("robotomy request", "Smart Robot");
    AForm* third = i.makeForm("presidential pardon", "Pardoned person");

    // 2. testing forms being usable by bureaucrats
    Bureaucrat a("Anna", 1);
    a.signForm(*first);
    a.signForm(*second);
    a.signForm(*third);

    a.executeForm(*first);
    a.executeForm(*second);
    a.executeForm(*third);

    delete first;
    delete second;
    delete third;

    return 0;
}
