#ifndef BUREAUCRAT_H
# define BUREAUCRAT_H

#include <string>
#include <iostream>

#include "AForm.hpp"

class Bureaucrat
{
    private:
        const std::string   name;
        int                 grade;
    
    public:
        class GradeTooLowException;
        class GradeTooHighException;

        Bureaucrat(const std::string& new_name, const int new_grade);
        Bureaucrat(const Bureaucrat& origin);
        Bureaucrat& operator =(const Bureaucrat& origin);
        ~Bureaucrat();

        std::string getName() const;
        int         getGrade() const;
        void        incrementGrade();
        void        decrementGrade();    
        void        signForm(AForm& form) const;
        void        executeForm(const AForm& form) const;  

};

std::ostream& operator << (std::ostream& os, const Bureaucrat& bureaucrat);

class Bureaucrat::GradeTooHighException : public std::exception
{
    public:
        const char* what() const throw() ;
};

class Bureaucrat::GradeTooLowException : public std::exception
{
    public:
        const char* what() const throw() ;
};

#endif