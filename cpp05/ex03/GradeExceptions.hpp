#ifndef GRADE_EXCEPTIONS_HPP
# define GRADE_EXCEPTIONS_HPP

#include <exception>

class GradeTooHighException : public std::exception
{
    public:
        const char* what() const throw();
};

class GradeTooLowException : public std::exception
{
    public:
        const char* what() const throw();
};

class FormNotSignedException : public std::exception
{
    public:
        const char* what() const throw();
};

#endif