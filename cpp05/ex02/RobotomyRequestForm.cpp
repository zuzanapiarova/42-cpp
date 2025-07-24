#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"

//------------------------------------------ Orthodox Canonical Form ------------------------------------

RobotomyRequestForm::RobotomyRequestForm(const std::string& newTarget)
    : AForm("RobotomyRequestForm", 72, 45), target(newTarget)
{
    std::cout << "RobotomyRequestForm constructor called for target " << target << std::endl;
};

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& origin)
    : AForm("RobotomyRequestForm", 72, 45), target(origin.target)
{
    std::cout << "RobotomyRequestForm copy constructor called." << std::endl;
    *this = origin;
};

RobotomyRequestForm& RobotomyRequestForm::operator =(const RobotomyRequestForm& origin)
{
    std::cout << "RobotomyRequestForm copy assignment operator called." << std::endl;
    if (this != &origin)
    {
        AForm::operator=(origin);
        target = origin.target;
    }
    return *this;
};

RobotomyRequestForm::~RobotomyRequestForm()
{
    std::cout << "RobotomyRequestForm destructor called for target " << target << std::endl;
};

//---------------------------------------------- Member Functions ------------------------------------

const std::string& RobotomyRequestForm::getTarget() const
{
    return target;
};

bool    RobotomyRequestForm::execute(const Bureaucrat& executor ) const 
{
    if (!getIsSigned())
    {
        throw AForm::FormNotSignedException();
    }
    if (executor.getGrade() > getMinimumExecutionGrade())
    {
        throw AForm::GradeTooLowException();
    }
    std::cout << "Bzzzzzz... " << target << " has been robotomized successfully 50% of the time!" << std::endl;
    return true;
}