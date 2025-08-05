#include "AForm.hpp"
#include "Bureaucrat.hpp" // include for circular dependencies - including header here and forward declaration in the Form.hpp

// ----------------------------------------- Orthodox Canonical Form ------------------------------------

AForm::AForm(const std::string& newName, const int newMinimumSignGrade, const int newMinimumExecutionGrade)
           : name(newName),
             minimumSignGrade(checkGrade(newMinimumSignGrade, 1, 150)),
             minimumExecutionGrade(checkGrade(newMinimumExecutionGrade, 1, 150)), 
             isSigned(false)
{
    std::cout << "Form overload constructor called." << std::endl;
};

AForm::AForm(const AForm& origin)
         : name(origin.name),
           minimumSignGrade(checkGrade(origin.minimumSignGrade, 1, 150)),
           minimumExecutionGrade(checkGrade(origin.minimumExecutionGrade, 1, 150)),
           isSigned(origin.isSigned)
{
    std::cout << "Form copy constructor called." << std::endl;
};

AForm& AForm::operator =(const AForm& origin)
{
    std::cout << "Form copy assignment operator called." << std::endl;
    if (this != &origin)
        std::cerr << "Cannot use copy assignment on object with const members. Aborting without change." << std::endl;
    return *this;
};

std::ostream& operator <<(std::ostream& os, const AForm& form)
{
    os << form.getName() << ", " << (form.getIsSigned() ? "signed" : "unsigned") << " form with minimum " << form.getMinimumSignGrade() << " signing Grade.";
    return os;
}

AForm::~AForm()
{
    std::cout << "Form destructor called." << std::endl;
};

// -------------------------------------------- Member Functions -----------------------------------------

// throws grade too low/high exceptions - used as checks everywhere where I accept a grade
int AForm::checkGrade(int grade, int highestGrade, int lowestGrade)
{
    if (grade < highestGrade)
        throw GradeTooHighException();
    if (grade > lowestGrade)
        throw GradeTooLowException();
    return grade;
}

const std::string& AForm::getName() const
{
    return name;
};

bool        AForm::getIsSigned() const
{
    return isSigned;
};

int         AForm::getMinimumSignGrade() const
{
    return minimumSignGrade;
};

int         AForm::getMinimumExecutionGrade() const
{
    return minimumExecutionGrade;
};

void        AForm::beSigned(const Bureaucrat& bureaucrat)
{
    if (bureaucrat.getGrade() > minimumSignGrade)
        throw GradeTooLowException();
    isSigned = true;
};