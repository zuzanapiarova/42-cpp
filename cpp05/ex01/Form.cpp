#include "Form.hpp"
#include "Bureaucrat.hpp" // include for circular dependencies - including header here and forward declaration in the Form.hpp

// ----------------------------------------- Orthodox Canonical Form ------------------------------------

Form::Form(const std::string& newName, const int newMinimumSignGrade, const int newMinimumExecutionGrade)
           : name(newName),
             minimumSignGrade(checkGrade(newMinimumSignGrade, 1, 150)),
             minimumExecutionGrade(checkGrade(newMinimumExecutionGrade, 1, 150))
{
    std::cout << "Form overload constructor called." << std::endl;
    isSigned = false;
};

Form::Form(const Form& origin)
         : name(origin.name),
           minimumSignGrade(checkGrade(origin.minimumSignGrade, 1, 150)),
           minimumExecutionGrade(checkGrade(origin.minimumExecutionGrade, 1, 150))
{
    std::cout << "Form copy constructor called." << std::endl;
    this->isSigned = origin.isSigned;
};

Form& Form::operator =(const Form& origin)
{
    std::cout << "Form copy assignment operator called." << std::endl;
    if (this != &origin)
        std::cerr << "Cannot use copy assignment on object with const members. Aborting without change." << std::endl;
    return *this;
};

std::ostream& operator <<(std::ostream& os, const Form& form)
{
    os << form.getName() << ", " << (form.getIsSigned() ? "signed" : "unsigned") << " form with minimum " << form.getMinimumSignGrade() << " signing Grade.";
    return os;
}

Form::~Form()
{
    std::cout << "Form destructor called." << std::endl;
};

// -------------------------------------------- Member Functions -----------------------------------------

// throws grade too low/high exceptions - used as checks everywhere where I accept a grade
int Form::checkGrade(int grade, int highestGrade, int lowestGrade)
{
    if (grade < highestGrade)
        throw GradeTooHighException();
    if (grade > lowestGrade)
        throw GradeTooLowException();
    return grade;
}

std::string Form::getName() const
{
    return name;
};

bool        Form::getIsSigned() const
{
    return isSigned;
};

int         Form::getMinimumSignGrade() const
{
    return minimumSignGrade;
};

int         Form::getMinimumExecutionGrade() const
{
    return minimumExecutionGrade;
};

void        Form::beSigned(const Bureaucrat& bureaucrat)
{
    if (bureaucrat.getGrade() > minimumSignGrade)
        throw GradeTooLowException();
    isSigned = true;
};