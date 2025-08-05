#include "GradeExceptions.hpp"

const char* GradeTooHighException::what() const throw()
{
    return "Grade too high!";
};

const char* GradeTooLowException::what() const throw()
{
    return "Grade too low!";
};

const char* FormNotSignedException::what() const throw()
{
    return "Form is not signed!";
};