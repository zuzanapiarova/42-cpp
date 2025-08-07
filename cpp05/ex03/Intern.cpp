#include "Intern.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern()
{
    std::cout << "Intern default constructor called." << std::endl;
}

Intern::~Intern()
{
    std::cout << "Intern destructor called." << std::endl;
}

// --------------------------------------------------------------------- Member Functions ------------------------------------------------------------------

AForm* Intern::makeShrubbery(const std::string& target) const 
{
    return new ShrubberyCreationForm(target);
}

AForm* Intern::makeRobotomy(const std::string& target) const 
{
    return new RobotomyRequestForm(target);
}

AForm* Intern::makePresidential(const std::string& target) const 
{
    return new PresidentialPardonForm(target);
}

// instead of using if-else statements, I use function pointers and corresponding form names array mapping from Module01
AForm*    Intern::makeForm(const std::string& formName, const std::string& formTarget) const
{
    const std::string formNames[] = { 
        "shrubbery creation",
        "robotomy request",
        "presidential pardon" 
    };

    AForm* (Intern::*formCreationPointers[])(const std::string& target) const = {
        &Intern::makeShrubbery,
        &Intern::makeRobotomy,
        &Intern::makePresidential
    };

    for (int i = 0; i < 3; ++i)
    {
        if (formName == formNames[i])
        {
            std::cout << "Intern created form " << formName << std::endl;
            return (this->*formCreationPointers[i])(formTarget);
        }
    }
    std::cout << "The requested form does not exist!" << std::endl;

    return NULL;
};

