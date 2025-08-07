#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"

// ----------------------------------------- Orthodox Canonical Form ------------------------------------

PresidentialPardonForm::PresidentialPardonForm() : AForm("Presidential Pardon Form", 25, 5), target("Unassigned")
{
    std::cout << "PresidentialPardonForm default constructor called for target " << target << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const std::string& target)
    : AForm("Presidential Pardon Form", 25, 5), target(target)
{
    std::cout << "PresidentialPardonForm constructor called for target " << target << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& origin)
    : AForm(origin), target(origin.target)
{
    std::cout << "PresidentialPardonForm copy constructor called." << std::endl;
}

PresidentialPardonForm& PresidentialPardonForm::operator =(const PresidentialPardonForm& origin)
{
    std::cout << "PresidentialPardonForm copy assignment operator called." << std::endl;
    if (this != &origin)
        std::cerr << "Cannot use copy assignment on object with const members. Aborting without change." << std::endl;
    return *this;
}

PresidentialPardonForm::~PresidentialPardonForm()
{
    std::cout << "PresidentialPardonForm destructor called for target " << target << std::endl;
}

// ------------------------------------------- Member Functions -----------------------------------------

const std::string& PresidentialPardonForm::getTarget() const
{
    return target;
};

bool PresidentialPardonForm::execute(const Bureaucrat& executor) const 
{
    if (!getIsSigned())
    {
        throw AForm::FormNotSignedException();
    }
    if (executor.getGrade() > getMinimumExecutionGrade())
    {
        throw AForm::GradeTooLowException();
    }
    std::cout << target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
    return true;
}