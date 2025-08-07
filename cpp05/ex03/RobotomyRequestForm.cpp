#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"

//------------------------------------------ Orthodox Canonical Form ------------------------------------

RobotomyRequestForm::RobotomyRequestForm() : AForm("RobotomyRequestForm", 72, 45), target("Unassigned")
{
    std::cout << "RobotomyRequestForm default constructor called for target " << target << std::endl;
};

RobotomyRequestForm::RobotomyRequestForm(const std::string& newTarget)
    : AForm("RobotomyRequestForm", 72, 45), target(newTarget)
{
    std::cout << "RobotomyRequestForm constructor called for target " << target << std::endl;
};

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& origin)
    : AForm(origin), target(origin.target)
{
    std::cout << "RobotomyRequestForm copy constructor called." << std::endl;
};

RobotomyRequestForm& RobotomyRequestForm::operator =(const RobotomyRequestForm& origin)
{
    std::cout << "RobotomyRequestForm copy assignment operator called." << std::endl;
    if (this != &origin)
        std::cerr << "Cannot use copy assignment on object with const members. Aborting without change." << std::endl;
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
        throw AForm::FormNotSignedException();
    if (executor.getGrade() > getMinimumExecutionGrade())
        throw AForm::GradeTooLowException();
    
    std::cout << "BZZRRZZZTTT... * and other drilling noises *" << std::endl;

    srand(time(NULL));  // seed with current time - rand uses an internal state that starts at a fixed value unless you change it with srand
    int num = rand();
    // std::cout << num << std::endl;
    if (num % 2 == 0)
        std::cout << target << " has been robotomized successfully!" << std::endl;
    else
        std::cout << target << " robotomy failed." << std::endl;

    return true;
}